/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(_pymemfd_memfd_create__doc__,
"memfd_create($module, name, flags=0, /)\n"
"--\n"
"\n"
"Create a memory file descriptor\n"
"\n"
"Returns a file descriptors");

#define _PYMEMFD_MEMFD_CREATE_METHODDEF    \
    {"memfd_create", (PyCFunction)_pymemfd_memfd_create, METH_VARARGS, _pymemfd_memfd_create__doc__},

static int
_pymemfd_memfd_create_impl(PyModuleDef *module, char *name, int flags);

static PyObject *
_pymemfd_memfd_create(PyModuleDef *module, PyObject *args)
{
    PyObject *return_value = NULL;
    char *name = NULL;
    int flags = 0;
    int _return_value;

    if (!PyArg_ParseTuple(args, "es|i:memfd_create",
        "ascii", &name, &flags))
        goto exit;
    _return_value = _pymemfd_memfd_create_impl(module, name, flags);
    if ((_return_value == -1) && PyErr_Occurred())
        goto exit;
    return_value = PyLong_FromLong((long)_return_value);

exit:
    /* Cleanup for name */
    if (name)
       PyMem_FREE(name);

    return return_value;
}
/*[clinic end generated code: output=64a57658b336fcfa input=a9049054013a1b77]*/
