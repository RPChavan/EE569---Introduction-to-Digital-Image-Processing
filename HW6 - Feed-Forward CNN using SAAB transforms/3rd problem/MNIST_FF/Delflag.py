#raksy
# -*- coding: utf-8 -*-
"""
Created on Sat Apr 27 18:53:07 2019

@author: Hp
"""

from tensorflow.python.platform import flags
import tensorflow as tf

def del_all_flags(FLAGS):
    flags_dict = FLAGS._flags()
    keys_list = [keys for keys in flags_dict]
    for keys in keys_list:
        FLAGS.__delattr__(keys)

del_all_flags(tf.flags.FLAGS)