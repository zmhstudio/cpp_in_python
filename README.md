
## 主要函数参考
* PyObject* Py_BuildValue(char *format, ...)
    把C++的变量转换成一个Python对象。常用的格式有：
    Verb    PythonType  C-Type
    i       int         int
    l       long        long
    d       float       double
    D       complex     Py_Complex*
    c       str         char
    s       str         char*
    S       str         PyStringObject*
    O       <any>       PyObject*
    
## 编译指令
g++ -g -o interface ./interface.cpp -I${HOME}/anaconda3/include/python3.8 -lpython3.8 -L${HOME}/anaconda3/lib/ -Wl,-rpath=${HOME}/anaconda3/lib/