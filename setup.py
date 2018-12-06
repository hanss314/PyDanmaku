from setuptools import setup
from distutils import util
from distutils.core import Extension


with open('requirements.txt') as f:
    requirements = f.read().splitlines()

version = '0.0.1'

if not version:
    raise RuntimeError('version is not set')

with open('README.md') as f:
    readme = f.read()

lib_deps=['GLEW', 'glfw', 'freeimage']
# on macos GL and GLU are part of framework OpenGL and are no libraries
if not 'macosx' in util.get_platform():
    lib_deps.extend(['GL', 'GLU'])

pydanmaku = Extension('_pydanmaku',
    include_dirs=['/usr/include/python3.7m'],
    library_dirs=[],
    libraries=lib_deps,
    sources=[
        'src/danmaku.cpp',
        'src/bullet.cpp',
        'src/renderer.cpp',
        'src/laser.cpp',
        'src/common/shader.cpp',
        'src/common/png.cpp',
        'src/common/trig.cpp',
        'src/group.cpp',
        'src/player.cpp'
    ],
)


setup(
    name='pydanmaku',
    author='hanss314',
    url='https://github.com/hanss314/PyDanmaku',
    version=version,
    packages=['pydanmaku'],
    license='MIT',
    description='A Danmaku engine written in python',
    long_description=readme,
    include_package_data=True,
    install_requires=requirements,
    ext_modules=[pydanmaku],
    data_files=[
        ('pydanmaku/shaders', ['pydanmaku/shaders/frag.shader', 'pydanmaku/shaders/vert.shader'])
    ],
)
