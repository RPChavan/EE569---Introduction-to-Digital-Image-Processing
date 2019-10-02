# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 19:33:57 2019

@author: Hp
"""

import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import inv
import math as mt
import cv2
#Function to read color the image
def reading_image(Image):
    Image_raw = open(Image,'rb').read()
    Image_raw = np.frombuffer(Image_raw,np.uint8)
    Image_matrix = Image_raw[0:Row_Size*Column_Size*3]
    Image_matrix = np.reshape(Image_matrix, (Row_Size,Column_Size,3))
    return Image_matrix;

Row_Size = 1024;
Column_Size = 768;
Input_image1 = reading_image('river1.raw')
plt.imshow(Input_image)
plt.show()

Row_Size = 1024;
Column_Size = 768;
Input_image2 = reading_image('river2.raw')
plt.imshow(Input_image2)
plt.show()

#Converting it to gray scale
Gray1 = cv2.cvtColor(Input_image1,cv2.COLOR_RGB2GRAY)
Gray2 = cv2.cvtColor(Input_image2,cv2.COLOR_RGB2GRAY)

sift = cv2.xfeatures2d.SIFT_create()
#Finding the keypoints and descriptors
kp1, des1 = sift.detectAndCompute(Gray1,None)
kp2, des2 = sift.detectAndCompute(Gray2,None)
# BFMatcher with default params
bf = cv2.BFMatcher()
matches = bf.match(des1,des2)


#Finding the largest l2 norm
l2list = [];
upper = len(des1);
for i in range(0,upper):
    l2list.append(np.linalg.norm(des1[i,:]));
l = l2list[0];

#Sorting
for i in range(1, upper-1):
    if(l2list[i] > l):
        l = l2list[i];
        index = i;
        
        
Output = np.zeros((1300,1300));
Output  = cv2.drawMatches(Input_image1,kp1,Input_image2,kp2,[matches[index]],Output,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
plt.figure(num=1, figsize=(10, 10))
plt.imshow(Output)
plt.show()

Output = np.zeros((1300,1300));
Output  = cv2.drawMatches(Gray1,kp1,Gray2,kp2,[matches[index]],Output,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
plt.figure(num=1, figsize=(10, 10))
plt.imshow(Output)
plt.show()

Output_1 = np.zeros((1300,1300));
Output_1=cv2.drawKeypoints(Gray1,kp1,Output_1,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
plt.figure(num=1, figsize=(10, 10))

plt.imshow(Output_1)

Output_2 = np.zeros((1300,1300));
Output_2=cv2.drawKeypoints(Gray2,kp2,Output_2,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
plt.figure(num=1, figsize=(10, 10))

plt.imshow(Output_2)

Output_3 = np.zeros((1300,1300));
matches = bf.match(des1,des2)
#matches = sorted(matches, key = lambda x:x.distance)
# Draw first 10 matches.
Output_3 = cv2.drawMatches(Input_image1,kp1,Input_image2,kp2,matches,Output_3, flags=2)
plt.figure(num=1, figsize=(10, 10))

plt.imshow(Output_3)