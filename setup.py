from setuptools import setup
import re

with open('requirements.txt') as f:
    requirements = f.read().splitlines()

with open('pydanmaku/__init__.py') as f:
    version = re.search(r'^__version__\s*=\s*[\'"]([^\'"]*)[\'"]', f.read(), re.MULTILINE).group(1)

if not version:
    raise RuntimeError('version is not set')

with open('README.md') as f:
    readme = f.read()

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
)
