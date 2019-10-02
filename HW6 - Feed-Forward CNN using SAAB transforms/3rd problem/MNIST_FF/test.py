import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import inv
import math as mt
from sklearn import decomposition
import pandas as pd
from sklearn.cluster import KMeans
import cv2
from skimage import color
from skimage import io
from scipy import linalg
import matplotlib.pyplot as plt
import data

def creating_law_filters(a,b):
    ten_product = np.tensordot(a,b,axes=0);
    return ten_product;



def law_filter_application(Ext_image,Law_filter):
    Law_applied = np.zeros((Row_Size,Column_Size))
    for i in range(2, Row_Size-2):
        for j in range(2, Column_Size-2):
            m = 0;
            k = 0;
            l = 0;
            for k in range(i-2, i+3):
                n = 0;
                for l in range(j-2, j+3):
                    Law_applied[:i-2][:j-2] = Law_applied[:i-2][:j-2] + (Ext_image[:k][:l]*Law_filter[m][n]);
                    n += 1 ;
                m += 1 ;
    return Law_applied;  

Row_Size = 32;
Column_Size = 32;
Window_Size = 5;
n1 = 2
features = 25;
samples = 32*32;
train_image = np.zeros((Row_Size,Column_Size));

L5 = np.array([1, 4, 6, 4, 1]);      #Level
E5 = np.array([-1, -2, 0, 2, 1]);    #Edge
S5 = np.array([-1, 0, 2, 0, -1]);    #Spot
W5 = np.array([-1, 2, 0, -2, 1]);    #Wave
R5 = np.array([1, -4, 6, -4, 1]);

L5S5 = creating_law_filters(L5,S5);
#L5W5 = creating_law_filters(L5,W5);


train_images, train_labels, test_images, test_labels, class_list = data.import_data("0-9")
print('Training image size:', train_images.shape)
print('Testing_image size:', test_images.shape)

train_images = train_images[:6000]
train_labels = train_labels[:6000]
#Reading the image
for i in range(0,6000):
    Input_image = train_images[:i]
    #Boundary extension of the image
  
    #Applying the law filters
    
    train_images[:i] = law_filter_application(Input_image,L5S5);'''
    
train_img1 = color.rgb2gray(io.imread('1.png'))
Input_image = train_img1
    #Boundary extension of the image
Ext_image = boundary_extension(Input_image,n1);
    #Applying the law filters'''
    
#train_img1 = law_filter_application(Ext_image,L5S5)
plt.matshow(train_img1,cmap='gray')         
    









