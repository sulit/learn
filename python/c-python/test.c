/*================================================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   filename:test.c
 *   author:sulit sulitsrc@163.com
 *   modify date,time:2015-05-26 10:20
 *   discription:
 *
 *================================================================*/

#include <Python.h>


static PyObject *mytest(PyObject * self)
{
	PyObject *t;
	PyObject *ret;

	t = PyTuple_New(2);
	ret = PyTuple_New(2);
	PyTuple_SetItem(t, 0, PyInt_FromLong(1L));
	PyTuple_SetItem(t, 1, PyString_FromString("two"));

	return Py_BuildValue("O", t);
}

static PyMethodDef mytestMethods[] = {
	{"mytest", (PyCFunction) mytest, METH_NOARGS, "mytest"},
};

PyMODINIT_FUNC initmytest()
{

	//初始模块
	PyObject *m = Py_InitModule("mytest", mytestMethods);
	if (m == NULL)
		return;
}
