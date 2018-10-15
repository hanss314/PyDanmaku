from setuptools import setup
from distutils import util
from distutils.core import Extension
import re

with open('requirements.txt') as f:
    requirements = f.read().splitlines()

version = '0.0.1b'

if not version:
    raise RuntimeError('version is not set')

with open('README.md') as f:
    readme = f.read()

lib_deps=['GLEW', 'glfw', 'freeimage']
# on macos GL and GLU are part of framework OpenGL and are no libraries
if not 'macosx' in util.get_platform():
    lib_deps.append(['GL', 'GLU'])

pydanmaku = Extension('pydanmaku',
                include_dirs=['-I/usr/include/python3.7m'],
                library_dirs=[],
                libraries=lib_deps,
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
      data_files=[
          ('images', ['pydanmaku/images/amulet.png']),
          ('shaders', ['pydanmaku/shaders/frag.shader', 'pydanmaku/shaders/vert.shader'])
          ],
)
