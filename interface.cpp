/*
 * @Description : 
 * @FilePath    : /cpppython/interface.cpp
 * @Author      : qxairobot@163.com
 * @Date        : 2021-08-28 20:47:14
 * @LastEditTime: 2021-08-30 10:43:22
 * @Refer to    : https://github.com/QixuanAI
 */

#include <Python.h>
#include <iostream>
#include <cstdlib>

long PythonAdd(long a, long b)
{
    PyObject *pModule, *pFunc, *pArgs, *pReturnValue;
    pModule = PyImport_ImportModule("interface");
    pFunc = PyObject_GetAttrString(pModule, "Add");
    if (!pFunc || !PyCallable_Check(pFunc))
        throw("can't find function [Add]");
    //参数进栈
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(a));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", b));
    //调用函数
    pReturnValue = PyObject_CallObject(pFunc, pArgs);
    //处理返回值
    long ret = PyLong_AsLong(pReturnValue);
    Py_DECREF(pReturnValue);
    return ret;
}

void PythonMinMax(int n, int *min, int *max)
{
    PyObject *pModule, *pFunc, *pArgs, *pList, *pReturnValue;
    pModule = PyImport_ImportModule("interface");
    pFunc = PyObject_GetAttrString(pModule, "MinMax");
    if (!pFunc || !PyCallable_Check(pFunc))
        throw("can't find function [Add]");
    //参数进栈
    pArgs = PyTuple_New(1);
    pList = PyList_New(n);
    std::cout << "generate random list:";
    for (int i = 0; i < n; i++)
    {
        auto v = PyLong_FromLong(rand() % 100);
        PyList_SET_ITEM(pList, i, v);
        std::cout << PyLong_AS_LONG(PyList_GET_ITEM(pList, i)) << ",";
    }
    std::cout << std::endl;
    PyTuple_SetItem(pArgs, 0, pList);
    //调用函数
    pReturnValue = PyObject_CallObject(pFunc, pArgs);
    //处理返回值
    if (!PyTuple_Check(pReturnValue))
        throw("return value is not a tuple!");
    *min = PyLong_AS_LONG(PyTuple_GetItem(pReturnValue, 0));
    *max = PyLong_AS_LONG(PyTuple_GET_ITEM(pReturnValue, 1));
    Py_DECREF(pReturnValue);
    return;
}

int PythonList(long n, int list[])
{
    PyObject *pModule, *pFunc, *pArgs, *pReturnValue;
    pModule = PyImport_ImportModule("interface");
    pFunc = PyObject_GetAttrString(pModule, "List");
    if (!pFunc || !PyCallable_Check(pFunc))
        throw("can't find function [List]");
    // 参数进栈
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(n));
    //调用函数
    pReturnValue = PyObject_CallObject(pFunc, pArgs);
    //处理返回值
    if (!PyList_Check(pReturnValue))
        throw("return value is not a list!");
    int rN = PyList_Size(pReturnValue); //返回的数组长度
    for (int i = 0; i < rN; i++)
    {
        auto tmp = PyList_GetItem(pReturnValue, i);
        list[i] = _PyLong_AsInt(tmp);
    }
    Py_DECREF(pReturnValue);
    return rN;
}

int PythonSquareList(long n, int slist[][5])
{
    PyObject *pModule, *pFunc, *pArgs, *pReturnValue;
    pModule = PyImport_ImportModule("interface");
    pFunc = PyObject_GetAttrString(pModule, "SquareList");
    if (!pFunc || !PyCallable_Check(pFunc))
    {
        throw("can't find function [SquareList]");
    }
    // 参数进栈
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(n));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 5));
    //调用函数
    pReturnValue = PyObject_CallObject(pFunc, pArgs);
    if (!PySequence_Check(pReturnValue))
        throw("return value is not a sequence!");
    int rN = PySequence_Size(pReturnValue); //获取数组长度
    for (int i = 0; i < rN; i++)
    {
        auto tmp = PySequence_GetItem(pReturnValue, i);
        if (!PySequence_Check(pReturnValue))
            throw("return value is not a square sequence!");
        if (PySequence_Size(tmp) != 5)
            throw("return 2-dim size is not 5!");
        for (int j = 0; j < 5; j++)
        {
            int v = _PyLong_AsInt(PySequence_GetItem(tmp, j));
            slist[i][j] = v;
        }
    }
    return rN;
}

int main(void)
{
    // 初始化Python
    Py_Initialize();
    // 检查初始化是否成功
    if (!Py_IsInitialized())
    {
        return -1;
    }
    // 添加当前路径
    PyRun_SimpleString("import sys"); //把输入的字符串作为Python代码直接运行，返回0表示成功，-1表示有错
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString("print('python', sys.version[:5], 'imported')");
    PyRun_SimpleString("print('python path:', sys.executable)");
    std::cout << std::endl;

    //实参为两个数值，返回值为一个数值
    auto ret = PythonAdd(3, 5);
    std::cout << "PythonAdd Return: " << ret << std::endl;
    std::cout << std::endl;

    //实参为列表，返回值为Tuple
    int min, max;
    PythonMinMax(10, &min, &max);
    std::cout << "PythonMinMax Return: " << min << "," << max << std::endl;
    std::cout << std::endl;

    //实参为一个数值，返回值为一维数组
    int list[10];
    int n1 = PythonList(10, list);
    std::cout << "return list length:" << n1 << ",list:";
    for (int i = 0; i < n1; i++)
    {
        std::cout << list[i] << ",";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //实参为两个数值，返回值为多维数组
    const int N = 2;
    int slist[2][5];
    int n2 = PythonSquareList(2, slist);
    std::cout << "return list length:" << n2 << ",list:" << std::endl;
    for (int i = 0; i < n2; i++)
    {
        std::cout << "\t";
        for (int j = 0; j < 5; j++)
        {
            std::cout << slist[i][j] << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}