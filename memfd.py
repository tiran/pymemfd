# Copyright (c) 2016 Christian Heimes
# The MIT License (MIT)
# see LICENSE for details

from fcntl import fcntl as _fcntl
from io import open as _open
from os import close as _close

from _pymemfd import (
    F_ADD_SEALS, F_GET_SEALS,
    F_SEAL_GROW, F_SEAL_SEAL, F_SEAL_SHRINK, F_SEAL_WRITE,
    MFD_ALLOW_SEALING, MFD_CLOEXEC,
    memfd_create
)

F_SEAL_ALL = F_SEAL_SEAL | F_SEAL_SHRINK | F_SEAL_GROW | F_SEAL_WRITE
MFD_ALLOW_SEALING_CLOEXEC = MFD_CLOEXEC | MFD_ALLOW_SEALING


def getseals(fd):
    """Get seals"""
    return _fcntl(fd, F_GET_SEALS)


def addseals(fd, op):
    """Add seals"""
    return _fcntl(fd, F_ADD_SEALS, op)


def open(name, *, flags=MFD_CLOEXEC, mode='wb+', buffering=0, closefd=True,
         **kwargs):
    """Open a new memfd

    By default the new memfd is CLOEXEC, binary, open for unbuffered reading
    and writing.
    """
    fd = memfd_create(name, flags)
    try:
        f = _open(fd, mode=mode, buffering=buffering, closefd=True, **kwargs)
    except Exception:
        if not closefd:
            _close(fd)
        raise
    f.name = 'memfd:{}'.format(name)
    return f
