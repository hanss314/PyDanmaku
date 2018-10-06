from setuptools import setup
from distutils.core import Extension
import re

with open('requirements.txt') as f:
    requirements = f.read().splitlines()

version = '0.0.1b' 

if not version:
    raise RuntimeError('version is not set')

with open('README.md') as f:
    readme = f.read()

pydanmaku = Extension('pydanmaku',
                include_dirs=['-I/usr/include/python3.7m'],
                library_dirs=[],
                libraries=['GL', 'GLU', 'GLEW', 'glfw', 'freeimage'],
                data_files=['images/amulet.png', 'shaders/frag.shader', 'shaders/vert.shader'],
                sources=[
                    'pydanmaku/src/danmaku.cpp',
                    'pydanmaku/src/bullet.cpp',
                    'pydanmaku/src/renderer.cpp',
                    'pydanmaku/src/common/shader.cpp',
                    'pydanmaku/src/common/png.cpp',
                    'pydanmaku/src/common/trig.cpp'
                ],
            )

setup(name='pydanmaku',
      author='hanss314',
      url='https://github.com/hanss314/PyDanmaku',
      version=version,
      packages=['pydanmaku'],
      license='MIT',
      description='A Danmaku engine written in python',
      long_description=readme,
      include_package_data=True,
      install_requires=requirements,
      ext_modules= [pydanmaku],
)
