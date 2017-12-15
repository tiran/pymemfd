#!/usr/bin/env python3

# Copyright (c) 2016 Christian Heimes
# The MIT License (MIT)
# see LICENSE for details

from distutils.core import setup
from distutils.extension import Extension


ext = Extension("_pymemfd",
                ["_pymemfd.c"],
                depends=["clinic/_pymemfd.c.h"])


long_description = []
with open("README.md") as f:
    long_description.append(f.read())
with open("CHANGES.md") as f:
    long_description.append(f.read())


setup(
    name="pymemfd",
    version="0.2dev",
    ext_modules=[ext],
    py_modules=["memfd"],
    author="Christian Heimes",
    author_email="christian@python.org",
    maintainer="Christian Heimes",
    maintainer_email="christian@python.org",
    url="https://github.com/tiran/pymemfd",
    keywords="memfd memfd_create",
    platforms="Linux",
    license="Apache 2.0",
    description="memfd_create interface for Linux",
    long_description="\n".join(long_description),
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: Apache Software License",
        "License :: OSI Approved :: Python Software Foundation License",
        "Natural Language :: English",
        "Operating System :: POSIX :: Linux",
        "Programming Language :: C",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.4",
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3 :: Only",
        "Programming Language :: Python :: Implementation :: CPython",
    ],
)
