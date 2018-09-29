import numpy as np
import tensorflow as tf


def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b
    return c


def py_np_add(arr_a, arr_b):
    print('begin add_np_arr in python. a:{}, b:{}'.format(arr_a, arr_b))
    return arr_a + arr_b

def print_np_arr(arr):
    print(arr)
    

def test_tf():
    tensor_a = tf.constant(5, dtype= tf.int32)
    with tf.Session() as sess:
        np_a = sess.run([tensor_a])
        print('python: {}'.format(np_a))
        return np_a