import urllib.request
import sys
import logging
import tempfile
import os
import re

from zipfile import ZipFile

libindex = {
    'win32': [
        {
            'name': 'clang',
            'version': '10.0.0',
            'arch': 'x64',
            'url': 'https://www.dropbox.com/s/2f7f1kgds3sygc8/clang-10.0.0-win.zip?dl=1'
        },
        {
            'name': 'antlr4-runtime-cpp',
            'version': '4.8',
            'arch': 'x64',
            'url': 'https://www.dropbox.com/s/ud09ta6eboe2kd2/antlr4-runtime-cpp-4.8-x64-windows-clang.zip?dl=1'
        }
    ],
    'linux': [

    ]
}

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
        
        platform = sys.platform
        arch = None

        packages = libindex.get(platform)
        if packages is None:
            raise Exception("no packages found for platform '%s'" % platform)

        if sys.maxsize == (2**63 - 1):
            arch = 'x64'
        elif sys.maxsize == (2 ** 31 - 1):
            arch = 'x86'
        else:
            raise Exception("unsupported architecture '%s'" % arch)

        packages = [p for p in packages if p['arch'] == arch]
        
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