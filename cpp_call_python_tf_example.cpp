//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
//tx2:    /home/nvidia/.local/lib/python3.5/site-packages/numpy/core/include
//vm: /usr/lib/python3/dist-packages/numpy/core/include
#include <numpy/arrayobject.h>
//vm: /usr/include/python3.5m/
#include <Python.h>

using namespace std;

int Init_Numpy()
{
    import_array();
}
void Test_np_and_tf()
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    std::string pyFile = "py_test";
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    Init_Numpy();
    pName = PyUnicode_DecodeFSDefault(pyFile.c_str());
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) 
    {
        //test numpy function
        {
            pFunc = PyObject_GetAttrString(pModule, "py_np_add");
            std::vector<float> arrA = { 1, 9 }, arrB = { 9, 11 };
            npy_intp dims[1] = { 2 };
            if (pFunc && PyCallable_Check(pFunc))
            {
                pArgs = PyTuple_New(2);
                PyTuple_SetItem(pArgs, 0, PyArray_SimpleNewFromData(sizeof(dims) / sizeof(dims[0]), dims, NPY_FLOAT, arrA.data()));
                PyTuple_SetItem(pArgs, 1, PyArray_SimpleNewFromData(sizeof(dims) / sizeof(dims[0]), dims, NPY_FLOAT, arrB.data()));
                pValue = PyObject_CallObject(pFunc, pArgs);
                Py_DECREF(pArgs);

                if (pValue != NULL)
                {
                //    PyArrayObject* arrResult  = (PyArrayObject*)PyArray_FROM_OTF(pValue, NPY_FLOAT, NPY_INOUT_ARRAY);
                //    assert(arrResult != nullptr);
                   int nDim = PyArray_NDIM(pValue);
                   assert(nDim == 1);
                   std::cout << "dim size:" << nDim  <<".dim";
                   npy_intp* outputDim = PyArray_DIMS(pValue);
                   std::for_each(outputDim, outputDim + nDim, [](auto& val){std::cout<<" "<<val;});
                   std::cout<<endl;
                //    float* ptr =  (float*)PyArray_GetPtr(arrResult, 0);
                //    std::cout<<"token 1"<<std::endl;
                //     for(int ii = 0; ii<outputDim[0]; ++ii)
                //         {
                //             std::cout<<ptr[ii]<<" ";
                //         }
                    //PyArray_GETPTR1(pValue, 0)
                   Py_DECREF(pValue);
                //    cout<<"token 1";
                }
                else
                {
                   Py_DECREF(pFunc);
                   Py_DECREF(pModule);
                   PyErr_Print();
                   std::cout << "Call failed" << std::endl;
                   return;
                }
            }
            else
            {
                if (PyErr_Occurred())
                    PyErr_Print();
                std::cout << "Cannot find function" << std::endl;
            }
            Py_XDECREF(pFunc);
            Py_DECREF(pModule);
        }
    }
    else 
    {
        PyErr_Print();
        std::cout << "Failed to load " << pyFile << std::endl;
    }
    Py_Finalize();
}

int main(int argc, char *argv[])
{
    Test_np_and_tf();
    cout<<"all done"<<endl;   
}