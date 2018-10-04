from setuptools import setup
from distutils.core import Extension
import re

with open('requirements.txt') as f:
    requirements = f.read().splitlines()

with open('pydanmaku/__init__.py') as f:
    version = re.search(r'^__version__\s*=\s*[\'"]([^\'"]*)[\'"]', f.read(), re.MULTILINE).group(1)

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
                    'src/danmaku.cpp',
                    'src/bullet.cpp',
                    'src/renderer.cpp,'
                    'src/common/shader.cpp',
                    'src/common/png.cpp',
                    'src/common/trig.cpp'
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
