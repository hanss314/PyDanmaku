from setuptools import setup
import re

version = '0.0.1a1'

with open('requirements.txt') as f:
    requirements = f.read().splitlines()

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
