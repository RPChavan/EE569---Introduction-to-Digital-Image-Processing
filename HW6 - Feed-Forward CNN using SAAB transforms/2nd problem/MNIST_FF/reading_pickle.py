#raksy old
# -*- coding: utf-8 -*-
"""
Created on Sat Apr 27 11:28:50 2019

@author: Hp
"""
import pickle

fr3 = open('pca_params.pkl','rb')
pca_params = pickle.load(fr3)
fr4 = open('feat.pkl', 'rb')
saab_coof = pickle.load(fr4)