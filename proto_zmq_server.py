#
#   Hello World server in Python
#   Binds REP socket to tcp://*:5555
#   Expects b"Hello" from client, replies with b"World"
#

import time
import numpy as np
import zmq
import cpp_py_exchange_data_pb2

msgToServer = cpp_py_exchange_data_pb2.MsgToServer()

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

msgToServer= msgToServer.FromString(socket.recv())
print('server recive: mode:{}, width:{}, height:{}'.format(msgToServer.Mode,\
    msgToServer.width, msgToServer.height))

msgToClient = cpp_py_exchange_data_pb2.MsgToClient()
msgToClient.width = msgToServer.width
msgToClient.height = msgToServer.height
msgToClient.actionType = "this is action type string sent from server"
print('server: buffer size:{}'.format(msgToClient.ByteSize()))
socket.send(msgToClient.SerializeToString())

# socket.send(b't')
# print('server said: t')

# img_msg = socket.recv()
# img_np = np.frombuffer(img_msg, dtype=np.uint8)
# print('server said: data:{},{}...'.format(img_np[0], img_np[1]))

print('done')