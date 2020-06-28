import urllib.request
import sys
import argparse
import logging
import tempfile
import os
import re

from zipfile import ZipFile

libindex = {
    'win32': [
        {
            'name': 'antlr4-runtime-cpp',
            'version': '4.8',
            'compiler': 'msvc142',
            'arch': 'x64',
            'url': 'https://www.dropbox.com/s/eigwzfu8l45748e/antlr4-runtime-cpp-4.8-x64-windows-msvc142.zip?dl=1'
        },
        {
            'name': 'boost',
            'version': '1.73',
            'compiler': 'msvc142',
            'arch': 'x64',
            'url': 'https://www.dropbox.com/s/m5ymgzp3kmuiqxr/boost-1.73.0-x64-windows-msvc142.zip?dl=1'
        }
    ],
    'linux': [

    ]
}

COMPILER_WINDOWS = 'msvc142'
COMPILER_LINUX = 'gnu'
SIZE_ONE_MB = 1048576

def nomalizeSlash(p: str):
    if sys.platform == 'win32':
        p = p.replace('\\', '/')
    return p

def main():
    try:
        rootdir = os.path.dirname(os.path.abspath(__file__))
        pkgroot = os.path.join(rootdir, 'packages')
        if not os.path.exists(pkgroot):
            os.makedirs(pkgroot)

        args = argparse.ArgumentParser('getpackages')
        args.add_argument('--platform', help='platform for which the packages are required to get')
        args.add_argument('--arch', help='cpu architecture of the platform like x86, x64')
        args.add_argument('--compiler', help='compiler that created the package')
        a = args.parse_args()
        
        platform = None
        arch = None

        if a.platform is None:
            platform = sys.platform
        else:
            platform = a.platform
            if libindex.get(platform) is None:
                logging.warning("since '%s' is an invalid platform, falling back to '%s'." % (platform, sys.platform))
                platform = sys.platform

        packages = libindex.get(platform)
        if packages is None:
            raise Exception("no packages found for platform '%s'" % platform)

        if a.arch is None:
            if sys.maxsize == (2**63 - 1):
                arch = 'x64'
            elif sys.maxsize == (2 ** 31 - 1):
                arch = 'x86'
            else:
                raise Exception("unsupported architecture '%s'" % arch)
        else:
            arch = a.arch
            if arch != 'x64' and arch != 'x86':
                raise Exception("invalid architecture '%s'" % arch)

        compiler = a.compiler
        if compiler is None:
            if platform == 'win32':
                compiler = COMPILER_WINDOWS
            elif platform == 'linux':
                compiler = COMPILER_LINUX
            else:
                raise Exception('compiler cannot be identified')
        else:
            compiler = a.compiler

        packages = [p for p in packages if p['arch'] == arch]
        packages = [p for p in packages if p['compiler'] == compiler]
        
        if len(packages) == 0:
            logging.warning('no packages found.')
            sys.exit(1)

        for package in packages:
            packageurl = package['url']
            print("downloading package '%s'" % packageurl)
            pkgfile = None
            filename = None
            with urllib.request.urlopen(packageurl) as pkgres:
                if pkgres.getcode() != 200:
                    logging.error("failed to download package from %s" % packageurl)
                    continue
                contentlen = int(pkgres.getheader('Content-Length'))
                filename = pkgres.getheader('Content-Disposition')
                pattern = re.compile('(attachment\\; filename\\=\\")([\w\d\\-\\.]+)(\\")')
                filename = pattern.match(filename).group(2)

                downloadedlen = 0
                with tempfile.NamedTemporaryFile('w+b', delete=False) as fp:
                    pkgfile = fp.name
                    buffer = pkgres.read(SIZE_ONE_MB)
                    while 0 < len(buffer):
                        downloadedlen += len(buffer)
                        fp.write(buffer)
                        percent = "{:3.2%}".format(downloadedlen / contentlen)
                        print("[%s | %s]" % (filename, percent))
                        buffer = pkgres.read(SIZE_ONE_MB)
            print('download completed')
            print("extracting package '%s'" % filename)
            pkgdir = os.path.join(pkgroot, package['name'])
            pkgdir = os.path.join(pkgdir, package['version'])
            pkgdir = os.path.join(pkgdir, package['arch'])
            pkgdir = os.path.join(pkgdir, package['compiler'])
            if not os.path.exists(pkgdir):
                os.makedirs(pkgdir)
            pkgrelpath = os.path.relpath(pkgdir, pkgroot)
            pkgrelpath = os.path.normpath(pkgrelpath)
            pkgrelpath = os.path.normcase(pkgrelpath)
            pkgrelpath = nomalizeSlash(pkgrelpath)
            pkgdirvar = "\"${CMAKE_SOURCE_DIR}/packages/%s\"" % pkgrelpath
            cmakefilepath = os.path.join(pkgdir, 'package.cmake')

            with ZipFile(pkgfile, 'r') as zfp:
                zfp.extractall(pkgdir)
                print('extracted')

            if not os.path.exists(cmakefilepath):
                raise Exception("cmake include file '%s' does not exists." % cmakefilepath)
            contents = []
            processedlines = []
            with open(cmakefilepath, 'r') as cfp:
                contents = cfp.readlines()
            for content in contents:
                content = content.replace('$$PKGDIR$$', pkgdirvar)
                processedlines.append(content)
            with open(cmakefilepath, 'w') as cfp:
                cfp.writelines(processedlines)

            cmkinc = "INCLUDE(\"${CMAKE_SOURCE_DIR}/packages/%s/package.cmake\")" % pkgrelpath
            cmkindexpath = os.path.join(pkgroot, 'index.cmake')
            if not os.path.exists(cmkindexpath):
                with open(cmkindexpath, 'w') as ifp:
                    ifp.write('# index of all packages to be included\n')
                    ifp.close()
            includedlines = []
            with open(cmkindexpath, 'r') as ifp:
                includedlines = ifp.read().splitlines()
                ifp.close()

            if cmkinc in includedlines:
                logging.warning("package is found already included in index")
            else:
                includedlines.append(cmkinc)
                with open(cmkindexpath, 'w') as ifp:
                    for includedline in includedlines:
                        ifp.write(includedline)
                        ifp.write('\n')
                    ifp.close()

    except Exception as e:
        logging.error(e)

if __name__ == "__main__":
    main()