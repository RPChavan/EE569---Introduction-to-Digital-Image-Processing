# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 19:40:57 2019

@author: Hp
"""

import cv2
import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import inv
import math as mt
from sklearn import decomposition
import pandas as pd
from sklearn.cluster import KMeans

#Function to read the image
def reading_image(Image):
    Image_raw = open(Image,'rb').read()
    Image_raw = np.frombuffer(Image_raw,np.uint8)
    Image_matrix = Image_raw[0:Row_Size*Column_Size]
    Image_matrix = np.reshape(Image_matrix, (Row_Size,Column_Size))
    return Image_matrix;

Row_Size = 28;
Column_Size = 28;
Input_image1 = reading_image('zero_1.raw')
Input_image2 = reading_image('zero_2.raw')
Input_image3 = reading_image('zero_3.raw')
Input_image4 = reading_image('zero_4.raw')
Input_image5 = reading_image('zero_5.raw')
Input_image6 = reading_image('one_1.raw')
Input_image7 = reading_image('one_2.raw')
Input_image8 = reading_image('one_3.raw')
Input_image9 = reading_image('one_4.raw')
Input_image10 = reading_image('one_5.raw')
Test_image = reading_image('eight.raw')

extractor = cv2.xfeatures2d.SIFT_create()
kp1, des1 = extractor.detectAndCompute(Input_image1,None)
kp2, des2 = extractor.detectAndCompute(Input_image2,None)
kp3, des3 = extractor.detectAndCompute(Input_image3,None)
kp4, des4 = extractor.detectAndCompute(Input_image4,None)
kp5, des5 = extractor.detectAndCompute(Input_image5,None)
kp6, des6 = extractor.detectAndCompute(Input_image6,None)
kp7, des7 = extractor.detectAndCompute(Input_image7,None)
kp8, des8 = extractor.detectAndCompute(Input_image8,None)
kp9, des9 = extractor.detectAndCompute(Input_image9,None)
kp10, des10 = extractor.detectAndCompute(Input_image10,None)
kptest, destest = extractor.detectAndCompute(Test_image,None)

des = np.zeros((54,128))

des[0:12,:] = des1;
des[12:20,:] = des2;
des[20:22,:] =des3;
des[22:34,:] = des4;
des[34:41,:] = des5;
des[41:43,:] =des6;
des[43:46,:] =des7;
des[46:49,:] =des8;
des[49:54,:] = des9;

#Function to do k-means clustering
def kmeans_clustering(des,destest):
    kmeans = KMeans(n_clusters=2)
    kmeans.fit(des)
    labels = kmeans.predict(destest)
    return labels,kmeans;

Labels,kmeans = kmeans_clustering(des,destest);

plt.hist(Labels)
