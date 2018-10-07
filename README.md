# a simple example show how to call python script in a cpp file. 
sure you can use tensorflow code in your python script.

# To user zeroMQ, you need download libzmq here.https://github.com/zeromq/libzmq/tree/master
# zeroMQ request&reply mode: https://learning-0mq-with-pyzmq.readthedocs.io/en/latest/pyzmq/patterns/client_server.html

# code introduction.
1. ```hwclient.c``` and ```hwserver2.c``` are copied from zmq exampele. From which you will 
learn how to send and receive data via port.
2. ```cvClient.c``` and ```cvServer.py``` show how to read a picture and send it to a python script
server.
3. ```proto_zmq_server.py``` and ```proto_zmq_client.c``` show how to send message via protocol buffer library. 

4. ```cpp_call_python_tf_example.cpp``` show how to do data exchange between python and cpp. In this example, cpp code will load ```py_test.py``` and invoke it's inner function.
5. ```cpp_socket_client.c``` and ```cpp_socket_server.c``` show how to operate socket via basic c api.