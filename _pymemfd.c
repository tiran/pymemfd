/* Copyright (c) 2016 Christian Heimes
 * The MIT License (MIT)
 * see LICENSE for details
 */

#include "Python.h"

#include <unistd.h>
#include <sys/syscall.h>
#include <linux/fcntl.h>


/* linux/memfd.h */
#ifndef MFD_CLOEXEC

/* flags for memfd_create(2) (unsigned int) */
#define MFD_CLOEXEC             0x0001U
#define MFD_ALLOW_SEALING       0x0002U

#endif /* MFD_CLOEXEC */


/* fcntl.h */
#ifndef F_ADD_SEALS

/*
 * Set/Get seals
 */
#define F_ADD_SEALS     (F_LINUX_SPECIFIC_BASE + 9)
#define F_GET_SEALS     (F_LINUX_SPECIFIC_BASE + 10)

/*
 * Types of seals
 */
#define F_SEAL_SEAL     0x0001  /* prevent further seals from being set */
#define F_SEAL_SHRINK   0x0002  /* prevent file from shrinking */
#define F_SEAL_GROW     0x0004  /* prevent file from growing */
#define F_SEAL_WRITE    0x0008  /* prevent writes */
/* (1U << 31) is reserved for signed error codes */

#endif /* F_ADD_SEALS */


static int _pymemfd_syscall_memfd_create(const char *name, unsigned int flags)
{
    return syscall(__NR_memfd_create, name, flags);
}


#include "clinic/_pymemfd.c.h"


/*[clinic input]
module _pymemfd
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=a11fcd744ac341bf]*/


/*[clinic input]
_pymemfd.memfd_create -> int

    name: str(encoding='ascii')
    flags: int() = 0
    /

Create a memory file descriptor

Returns a file descriptors
[clinic start generated code]*/

static int
_pymemfd_memfd_create_impl(PyModuleDef *module, char *name, int flags)
/*[clinic end generated code: output=bd4922591b709b18 input=f584ab789e7251c1]*/
{
    int fd;

    if (flags < 0 || flags > UINT32_MAX) {
        PyErr_SetString(PyExc_ValueError, "flags out of range");
        return NULL;
    }

    fd = _pymemfd_syscall_memfd_create(name, (unsigned int)flags);

    if (fd < 0) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }
    return fd;
}


static struct PyMethodDef pymemfd_functions[] = {
    _PYMEMFD_MEMFD_CREATE_METHODDEF
    {NULL, NULL}
};


PyDoc_STRVAR(pymemfd__doc__,
"Wrapper for Linux syscall memfd_create");


static struct PyModuleDef pymemfd_module = {
    PyModuleDef_HEAD_INIT,
    "_pymemfd",
    pymemfd__doc__,
    -1,
    pymemfd_functions,
    NULL,
    NULL,
    NULL,
    NULL
};


PyMODINIT_FUNC
PyInit__pymemfd(void)
{
    PyObject *m;

    m = PyModule_Create(&pymemfd_module);
    if (m == NULL) {
        return NULL;
    }

    PyModule_AddIntMacro(m, MFD_CLOEXEC);
    PyModule_AddIntMacro(m, MFD_ALLOW_SEALING);
    PyModule_AddIntMacro(m, F_ADD_SEALS);
    PyModule_AddIntMacro(m, F_GET_SEALS);
    PyModule_AddIntMacro(m, F_SEAL_SEAL);
    PyModule_AddIntMacro(m, F_SEAL_SHRINK);
    PyModule_AddIntMacro(m, F_SEAL_GROW);
    PyModule_AddIntMacro(m, F_SEAL_WRITE);

    return m;
}
