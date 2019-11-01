import sys
from urllib import request
from urllib.error import URLError
from os import path
from os import mkdir
from zipfile import ZipFile

packages = {
    'win32': [
        {
            'name': 'antlr4-runtime-cpp-4.7.2-mingw.zip',
            'url': 'https://bitbucket.org/benoybose/hoolang/downloads/antlr4-runtime-cpp-4.7.2-mingw.zip',
            'path': ['packages', 'libs']
        },
        {
            'name': 'boost-1.70.0-mingw.zip',
            'url': 'https://bitbucket.org/benoybose/hoolang/downloads/boost-1.70.0-mingw.zip',
            'path': ['packages', 'libs']
        },
        {
            'name': 'antlr4-runtime-cpp-4.7.2-win.zip',
            'url': 'https://bitbucket.org/benoybose/hoolang/downloads/antlr4-runtime-cpp-4.7.2-win.zip',
            'path': ['packages', 'libs']
        }
    ]
}

if __name__ == '__main__':
    platform = sys.platform
    print('Getting library and tool files for %s.' % platform)
    root_dir = path.abspath(__file__)
    root_dir = path.dirname(root_dir)
    temp_dir = path.join(root_dir, 'downloads')
    if not path.exists(temp_dir):
        mkdir(temp_dir)
    platform_packages = packages[platform]
    for pkg in platform_packages:
        pkg_name = pkg['name']
        pkg_url = pkg['url']
        pkg_file = path.join(temp_dir, pkg_name)
        pkg_path = root_dir
        for part in pkg['path']:
            pkg_path = path.join(pkg_path, part)
        try:
            print('Pulling %s' % pkg_url)
            result = request.urlretrieve(pkg_url, pkg_file)
            with ZipFile(pkg_file) as pkg_zip:
                print('Extracting to %s' % pkg_name)
                pkg_zip.extractall(pkg_path)
        except URLError as e:
            print('Failed to download %s.' % pkg_file)
            print(e)
        except Exception as e:
            print('Failed to download %s.' % pkg_file)
            print(e)
