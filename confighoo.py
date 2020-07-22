#!/usr/bin/python3
import urllib.request
import sys
import logging
import tempfile
import os
import re
import json
import argparse
import shutil
import stat

from zipfile import ZipFile

libindex = {
    'win32': {
        'x64': {
            'generic': [
                {
                    'name': 'clang',
                    'version': '10.0.0',
                    'url': 'https://www.dropbox.com/s/04oglvnci4x00fa/clang-10.0.0-x64-windows-release.zip?dl=1',
                    'defs': {
                        'CMAKE_C_COMPILER': '$$HOME$$/bin/clang-cl.exe',
                        'CMAKE_CXX_COMPILER': '$$HOME$$/bin/clang-cl.exe',
                    }
                }
            ],
            'debug': [
                {
                    'name': 'antlr4-runtime-cpp',
                    'version': '4.8',
                    'url': 'https://www.dropbox.com/s/fkfcvxxoml9mzaa/antlr4-4.8-x64-windows-debug.zip?dl=1'
                }
            ],
            'release': [
                {
                    'name': 'antlr4-runtime-cpp',
                    'version': '4.8',
                    'url': 'https://www.dropbox.com/s/c08fuwh63upe1ux/antlr4-4.8-x64-windows-release.zip?dl=1'
                }
            ]
        }
    },
    'linux': {
        'x64': {
            'generic': [
                {
                    'name': 'clang',
                    'version': '10.0.0',
                    'url': 'https://www.dropbox.com/s/fb7qtvh3t03e7zs/clang-10.0.0-x64-linux-release.zip?dl=1',
                    'defs': {
                        'CMAKE_C_COMPILER': '$$HOME$$/bin/clang',
                        'CMAKE_CXX_COMPILER': '$$HOME$$/bin/clang++',
                    },
                    'execs': [
                        '$$HOME$$/bin/clang',
                        '$$HOME$$/bin/clang++'
                    ]
                },
            ],
            'debug': [
                {
                    'name': 'antlr4-runtime-cpp',
                    'version': '4.8',
                    'url': 'https://www.dropbox.com/s/9vz3tmurvqhztqx/antlr4-4.8-x64-linux.zip?dl=1'
                }
            ],
            'release': [
                {
                    'name': 'antlr4-runtime-cpp',
                    'version': '4.8',
                    'url': 'https://www.dropbox.com/s/9vz3tmurvqhztqx/antlr4-4.8-x64-linux.zip?dl=1'
                }
            ]
        }
    }
}

SIZE_ONE_MB = 1048576


def nomalizeSlash(p: str):
    if sys.platform == 'win32':
        p = p.replace('\\', '/')
    return p


def mkpkgrelpath(dir, root):
    pkgrelpath = os.path.relpath(dir, root)
    pkgrelpath = os.path.normpath(pkgrelpath)
    pkgrelpath = os.path.normcase(pkgrelpath)
    pkgrelpath = nomalizeSlash(pkgrelpath)
    return pkgrelpath


def mkpkgdir(root, package, arch, buildtype, platform):
    pkgdir = os.path.join(root, package['name'])
    pkgdir = os.path.join(pkgdir, package['version'])
    pkgdir = os.path.join(pkgdir, arch)
    if package['generic']:
        pkgdir = os.path.join(pkgdir, 'generic')
    else:
        pkgdir = os.path.join(pkgdir, buildtype)
    pkgdir = os.path.join(pkgdir, platform)
    if not os.path.exists(pkgdir):
        os.makedirs(pkgdir)
    return pkgdir


def extractpkg(pkgzip, pkgdest, fname):
    with ZipFile(pkgzip, 'r') as zfp:
        entries = zfp.infolist()
        totoalentries = len(entries)
        extractedentries = 0
        for entry in entries:
            zfp.extract(entry, pkgdest)
            entrydest = os.path.join(pkgdest, entry.filename)
            entrydest = nomalizeSlash(entrydest)
            if entry.is_dir():
                if not os.path.exists(entrydest):
                    os.makedirs(entrydest)
            else:
                zfp.extract(entry, pkgdest)
            extractedentries += 1
            progress = (extractedentries / totoalentries)
            percent = "{:3.2%}".format(progress)
            print("[extract %s %s]" % (fname, percent))


def preparepkg(dir, relpath):
    pkgdirvar = "\"${CMAKE_SOURCE_DIR}/packages/%s\"" % relpath
    cmakefilepath = os.path.join(dir, 'package.cmake')

    if not os.path.exists(cmakefilepath):
        raise Exception(
            "cmake include file '%s' does not exists." % cmakefilepath)
    contents = []
    processedlines = []
    with open(cmakefilepath, 'r') as cfp:
        contents = cfp.readlines()
    for content in contents:
        content = content.replace('$$PKGDIR$$', pkgdirvar)
        processedlines.append(content)
    with open(cmakefilepath, 'w') as cfp:
        cfp.writelines(processedlines)


def installpkg(root, relpath):
    pkgcmakefile = "packages/%s/package.cmake" % relpath
    cmkinc = "INCLUDE(\"${CMAKE_SOURCE_DIR}/%s\")" % pkgcmakefile

    cmkindexpath = os.path.join(root, 'index.cmake')
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
    print("[installed %s]" % pkgcmakefile)


def encachepkg(root, url, home):
    pkgindexfile = os.path.join(root, 'index.json')
    if not os.path.exists(pkgindexfile):
        with open(pkgindexfile, 'wt') as fp:
            pkgentry = json.dumps({
                url: {
                    'dir': home,
                    'modified_time': os.path.getmtime(home)
                }
            }, indent=4)
            fp.write(pkgentry)
            fp.close()
    else:
        pkgentries = None
        with open(pkgindexfile, 'rt') as fp:
            pkgentries = json.load(fp)
            pkgentries[url] = {
                'dir': home,
                'modified_time': os.path.getmtime(home)
            }
            fp.close()
        with open(pkgindexfile, 'wt') as fp:
            json.dump(pkgentries, fp, indent=4)
            fp.close()
    print('[cached %s]' % home)


def downloadpkg(packageurl):
    with urllib.request.urlopen(packageurl) as pkgres:
        if pkgres.getcode() != 200:
            logging.error("failed to download package from %s" % packageurl)
            return None, None, False

        contentlen = int(pkgres.getheader('Content-Length'))
        filename = pkgres.getheader('Content-Disposition')
        pattern = re.compile(
            '(attachment\\; filename\\=\\")([\w\d\\-\\.]+)(\\")')
        filename = pattern.match(filename).group(2)

        downloadedlen = 0
        with tempfile.NamedTemporaryFile('w+b', delete=False) as fp:
            pkgfile = fp.name
            buffer = pkgres.read(SIZE_ONE_MB)
            while 0 < len(buffer):
                downloadedlen += len(buffer)
                fp.write(buffer)
                percent = "{:3.2%}".format(downloadedlen / contentlen)
                print("[download %s  %s]" % (filename, percent))
                buffer = pkgres.read(SIZE_ONE_MB)
        if contentlen == downloadedlen:
            return pkgfile, filename, True
        else:
            return None, None, False


def chkpkgexists(root, url):
    indexfile = os.path.join(root, 'index.json')
    if not os.path.exists(indexfile):
        return False
    else:
        indexdata = {}
        with open(indexfile, 'rt') as fp:
            indexdata = json.load(fp)
            fp.close()
        if indexdata is None:
            return False
        entry = indexdata.get(url)
        if entry is None:
            return False
        entrydir = entry.get('dir')
        modifiedtime = entry.get('modified_time')

        if entrydir is None or modifiedtime is None:
            return False

        if not os.path.exists(entrydir):
            return False

        mtime = os.path.getmtime(entrydir)
        return mtime == modifiedtime


def mkbuilddir(rootdir, arch, build_type, platform):
    builddir = os.path.join(rootdir, "out")
    builddir = os.path.join(builddir, arch)
    builddir = os.path.join(builddir, build_type)
    builddir = os.path.join(builddir, platform)
    builddir = nomalizeSlash(builddir)
    return builddir


def runconfig(build_type, builddir, cmake_defs, rootdir):
    cmkbuildType = "Debug"
    if build_type == "release":
        cmkbuildType = "Release"

    installdir = os.path.join(builddir, "dist")
    installdir = nomalizeSlash(installdir)
    gn = 'NMake Makefiles'
    if sys.platform == 'linux':
        gn = 'Unix Makefiles'

    configcmd = "cmake -G \"%s\" -B \"%s\" " % (gn, builddir)
    configcmd += "-DCMAKE_INSTALL_PREFIX=\"%s\" " % installdir
    configcmd += "-DCMAKE_BUILD_TYPE=%s " % cmkbuildType
    for cmakedef in cmake_defs:
        configcmd += "-D%s=\"%s\" " % (cmakedef, cmake_defs[cmakedef])
    configcmd = configcmd.strip()
    configcmd += " %s" % nomalizeSlash(rootdir)
    print(configcmd)
    exitcode = os.system(configcmd)
    if 0 != exitcode:
        raise Exception(
            "Error while trying to configure using '%s'" % configcmd)
    else:
        print('successfully configured')
        print('[BuildDir %s]' % builddir)


def main():
    try:
        arch = None
        if sys.maxsize == (2**63 - 1):
            arch = 'x64'
        elif sys.maxsize == (2 ** 31 - 1):
            arch = 'x86'
        else:
            raise Exception("unsupported architecture '%s'" % arch)
        platform = sys.platform

        argparser = argparse.ArgumentParser()
        argparser.add_argument('--build-type', default='debug', action='store',
                               help='build type could be either Debug or Release')
        argparser.add_argument('--arch', default=arch, action='store',
                               help='architecture could be x64 or x86')
        argparser.add_argument('--platform', default=platform, action='store',
                               help='platform could be win32 or linux')
        argparser.add_argument('--build', action='store_true',
                               help='initiate the build for present configuration')
        argparser.add_argument('--clean', action='store_true',
                               help='clean the build before do configure')
        argparser.add_argument('--test', action='store_true',
                               help='test the build')
        args = argparser.parse_args()

        build_type = args.build_type.lower()
        arch = args.arch.lower()
        platform = args.platform.lower()
        buildflag = args.build
        cleanflag = args.clean
        testflag = args.test
        print("[%s-%s-%s]" % (arch, platform, build_type))

        rootdir = os.path.dirname(os.path.abspath(__file__))
        pkgroot = os.path.join(rootdir, 'packages')
        if not os.path.exists(pkgroot):
            os.makedirs(pkgroot)

        packages = libindex.get(platform)
        if packages is None:
            raise Exception("no packages found for platform '%s'" % platform)

        packages = packages.get(arch)
        if packages is None:
            raise Exception("no packages found for arch '%s" % arch)

        genericpkgs = packages.get('generic')
        packages = packages.get(build_type)
        if packages is None:
            raise Exception(
                "no packages found for build type '%s'" % build_type)

        if len(packages) == 0:
            logging.warning('no packages found.')

        if not genericpkgs is None:
            if len(genericpkgs) > 0:
                for gpkg in genericpkgs:
                    gpkg['generic'] = True

                for pkg in packages:
                    pkg['generic'] = False
                    genericpkgs.append(pkg)
                packages = genericpkgs

        cmake_defs = {}
        for package in packages:
            packageurl = package['url']
            pkgdir = mkpkgdir(pkgroot, package, arch, build_type, platform)
            pkgrelpath = mkpkgrelpath(pkgdir, pkgroot)
            pkghome = os.path.join(pkgroot, pkgrelpath)
            pkghome = nomalizeSlash(pkghome)

            if not chkpkgexists(pkgroot, packageurl):
                pkgfile, filename, downloadok = downloadpkg(packageurl)
                if not downloadok:
                    raise Exception('download failed for %s' % packageurl)
                extractpkg(pkgfile, pkgdir, filename)
                preparepkg(pkgdir, pkgrelpath)
                installpkg(pkgroot, pkgrelpath)
                encachepkg(pkgroot, packageurl, pkghome)
            else:
                print('[exists %s-%s]' % (package['name'], package['version']))

            defs = package.get('defs')
            print('checking definitions')
            if not defs is None:
                print('definitions found')
                for defkey in defs:
                    defval = defs[defkey]
                    defval = defval.replace('$$HOME$$', pkghome)
                    cmake_defs[defkey] = defval
                    print('[def %s = %s]' % (defkey, defval))
            else:
                print('no definitions found')

            print('checking executables')
            execs = package.get('execs')
            if not execs is None:
                print('executables found')
                for path in execs:
                    path = path.replace('$$HOME$$', pkghome)
                    print('[chmod +x %s]' % path)
                    os.chmod(path, stat.S_IRWXU)                    
            else:
                print('no executables found')

        builddir = mkbuilddir(rootdir, arch, build_type, platform)
        print('[BuildDir %s]' % builddir)

        if cleanflag:
            if os.path.exists(builddir):
                shutil.rmtree(builddir)

        cmkcache = os.path.join(builddir, 'CMakeCache.txt')
        if (not os.path.exists(cmkcache)) and os.path.exists(builddir):
            print('[removedir %s]' % builddir)
            shutil.rmtree(builddir)

        print('running configuration')
        runconfig(build_type, builddir, cmake_defs, rootdir)
        if testflag:
            buildflag = True

        if buildflag:
            buildcmd = 'cmake --build %s' % builddir
            print(buildcmd)
            exitcode = os.system(buildcmd)
            if 0 != exitcode:
                raise Exception('build failed')
        
        if testflag:
            testcmd = 'cmake --build %s --target test' % builddir
            print(buildcmd)
            exitcode = os.system(testcmd)
            if 0 != exitcode:
                raise Exception('test failed')

    except Exception as e:
        logging.error(e)
        sys.exit(-1)


if __name__ == "__main__":
    main()
