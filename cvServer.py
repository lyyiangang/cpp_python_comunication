#
#   Hello World server in Python
#   Binds REP socket to tcp://*:5555
#   Expects b"Hello" from client, replies with b"World"
#

import time
import numpy as np
import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

wh_msg = socket.recv()
wh_np = np.frombuffer(wh_msg, dtype = np.int32)
print('server said: width:{}, height:{}'.format(wh_np[0], wh_np[1]))

socket.send(b't')
print('server said: t')

img_msg = socket.recv()
img_np = np.frombuffer(img_msg, dtype=np.uint8)
print('server said: data:{},{}...'.format(img_np[0], img_np[1]))

print('done')