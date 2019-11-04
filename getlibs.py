#!/usr/bin/env python3
import sys
from urllib import request
from urllib.error import URLError
from os import path
from os import mkdir
from os import unlink
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
            'name': 'antlr4-tool-java.zip',
            'url': 'https://bitbucket.org/benoybose/hoolang/downloads/antlr4-tool-java.zip',
            'path': ['packages', 'tools']
        }
    ],
    'linux': [
        {
            'name': 'antlr4-runtime-cpp-4.7.2-linux.zip',
            'url': 'https://bitbucket.org/benoybose/hoolang/downloads/antlr4-runtime-cpp-4.7.2-linux.zip',
            'path': ['packages', 'libs']
        },
        {
            'name': 'boost-1.70.0-linux.zip',
            'url': 'https://bitbucket.org/benoybose/hoolang/downloads/boost-1.70.0-linux.zip',
            'path': ['packages', 'libs']
        },
        {
            'name': 'antlr4-tool-java.zip',
            'url': 'https://bitbucket.org/benoybose/hoolang/downloads/antlr4-tool-java.zip',
            'path': ['packages', 'tools']
        },
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
                print('Extracting \'%s\'' % pkg_name)
                pkg_zip.extractall(pkg_path)
            unlink(pkg_file)
        except URLError as e:
            print(e)
            unlink(pkg_path)
            unlink(pkg_file)
        except Exception as e:
            print(e)
            unlink(pkg_path)
            unlink(pkg_file)
