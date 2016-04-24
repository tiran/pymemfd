pymemfd -- memfd_create wrapper for Python
==========================================

This modules provides a Python wrapper for the new memfd_create() syscall
and the new file-sealing fcntl() operators.

Low level interface
-------------------

memfd.memfd_create(name, flags) -> int

memfd.MFD_ALLOW_SEALING

memfd.MFD_CLOEXEC

memfd.F_ADD_SEALS

memfd.F_GET_SEALS

memfd.F_SEAL_SEAL

memfd.F_SEAL_GROW

memfd.F_SEAL_SHRINK

memfd.F_SEAL_WRITE


High level interfaces
---------------------

memfd.open(name, \*, flags=MFD_CLOEXEC, mode='wb+', buffering=0, closefd=True,
           \*\*kwargs) -> io.FileIO

memfd.F_SEAL_ALL

memfd.MFD_ALLOW_SEALING_CLOEXEC

More
----

http://man7.org/linux/man-pages/man2/memfd_create.2.html

https://dvdhrm.wordpress.com/tag/memfd/
