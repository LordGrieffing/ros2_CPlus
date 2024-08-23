from setuptools import find_packages
from setuptools import setup

setup(
    name='practice_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('practice_interfaces', 'practice_interfaces.*')),
)
