#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "../parser.h"


static PyObject* generate_seqdia(PyObject* self, PyObject* args) {

    PyObject *strings;
    int string_len;
    char *opt;
    bool is_text = false;

    if (!PyArg_ParseTuple(args, "O|s", &strings, &opt))
        return NULL;

    if (opt != NULL && !strcmp(opt, "al"))
        is_text = true;

    string_len = PyObject_Length(strings);

    if (string_len < 0)
        return NULL;

    set_style(is_text);

    for (int l = 0; l < string_len; l++) {
        PyObject *line;
        line = PyList_GetItem(strings, l);
        char *c_line = PyUnicode_AsUTF8(line);

        parse_line(c_line, l);
    }

    render();

    if (failed_at != -1)
        return Py_BuildValue("i", failed_at);

    PyObject* result = PyList_New(result_list_size);
    for (int i = 0; i < result_list_size; i++)
    {
        PyObject* parsed_line = Py_BuildValue("s", PY_list_result[i]);
        PyList_SetItem(result, i, parsed_line);
    }

    return result;
}

static PyObject* seqdia_wrapper(PyObject* self, PyObject* args) {
    PyObject *temp = generate_seqdia(self, args);
    clear_temps();
    return temp;
}

static PyMethodDef SeqdiaMethods[] = {
    {"generate_from_array", seqdia_wrapper, METH_VARARGS, "parse line"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef seqdiamodule = {
    PyModuleDef_HEAD_INIT,
    "seqdia",
    "draw sequence diagram",
    -1,
    SeqdiaMethods
};

PyMODINIT_FUNC PyInit_seqdia(void)
{
    return PyModule_Create(&seqdiamodule);
}
