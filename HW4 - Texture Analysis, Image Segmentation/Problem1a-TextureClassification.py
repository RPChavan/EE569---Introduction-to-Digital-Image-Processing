# -*- coding: utf-8 -*-
"""
Created on Sat Mar  9 16:02:45 2019

@author: Rakshitha Panduranga
"""
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
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

#Function to find the tensor product
def creating_law_filters(a,b):
    ten_product = np.tensordot(a,b,axes=0);
    return ten_product;


#Function to get mean and subtract the mean
def mean_subtraction(Image):
    Mean_image = np.mean(Image);
    Subtracted_Image = np.zeros((Row_Size,Column_Size))
    for i in range(0,Row_Size):
        for j in range(0,Column_Size):
            Subtracted_Image[i][j] = Image[i][j] - Mean_image;
    
    return Subtracted_Image; 


#Function to apply Boundary Extension
def boundary_extension(Image):
    Ext_image = np.zeros((Row_Size+(2*n),Column_Size+(2*n)))
    #Complete image
    for i in range(n,(Row_Size+n)):
        for j in range(n,(Column_Size+n)):
            Ext_image[i][j] = Image[i-n][j-n];
    #Upper rows    
    for i in range(0,n):
        for j in range(n, (Column_Size+n)):
            Ext_image[i][j] = Image[0][j-n];
    #Left columns
    for j in range(0,n):
        for i in range(n, (Row_Size+n)):
            Ext_image[i][j] = Image[i-n][0];
    #Bottom rows
    for i in range(Row_Size+n, (Row_Size+(2*n))):
        for j in range(n,(Column_Size+n)):
            Ext_image[i][j] = Image[127][j-n];
    #Right columns
    for j in range(Column_Size+n, Column_Size+(2*n)):
        for i in range(n,(Row_Size+n)):
            Ext_image[i][j] = Image[i-n][127];
    #Corners
    for i in range(0,n):
        for j in range(0,n):
            Ext_image[i][j] = Image[0][0];

    for i in range(0,n):
        for j in range(Column_Size+n,Column_Size+(2*n)):
            Ext_image[i][j] = Image[0][127];

    for j in range(0,n):
        for i in range(Row_Size+n,Row_Size+(2*n)):
            Ext_image[i][j] = Image[127][0];

    for j in range(Column_Size+n, Column_Size+(2*n)):
        for i in range(Row_Size+n, Row_Size+(2*n)):
            Ext_image[i][j] = Image[127][127];
    
    return Ext_image;


#Function to get the squared image
def image_square(Image):
    for i in range(0,Row_Size):
        for j in range(0,Column_Size):
            Image[i][j] = ((Image[i][j])**2);
    return Image;


#Function to apply the Law Filters
def law_filter_application(Ext_image,Law_filter):
    Law_applied = np.zeros((Row_Size,Column_Size))
    for i in range(2, Row_Size+2):
        for j in range(2, Column_Size+2):
            m = 0;
            k = 0;
            l = 0;
            for k in range(i-2, i+3):
                n = 0;
                for l in range(j-2, j+3):
                    Law_applied[i-2][j-2] = Law_applied[i-2][j-2] + (Ext_image[k][l]*Law_filter[m][n]);
                    n += 1 ;
                m += 1 ;
    return Law_applied;   
 
def getting_25D(Ext_image):
    Average_Energy = [];

    #law1
    Image_Law = law_filter_application(Ext_image,L5L5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    #law2
    Image_Law = law_filter_application(Ext_image,L5E5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    
    #law3
    Image_Law = law_filter_application(Ext_image,L5S5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    #law4
    Image_Law = law_filter_application(Ext_image,L5W5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law5
    Image_Law = law_filter_application(Ext_image,L5R5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law6
    Image_Law = law_filter_application(Ext_image,E5L5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law7
    Image_Law = law_filter_application(Ext_image,E5E5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    
    #law8
    Image_Law = law_filter_application(Ext_image,E5S5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    
    #law9
    Image_Law = law_filter_application(Ext_image,E5W5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    
    #law10
    Image_Law = law_filter_application(Ext_image,E5R5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law11
    Image_Law = law_filter_application(Ext_image,S5L5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law12
    Image_Law = law_filter_application(Ext_image,S5E5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    

    #law13
    Image_Law = law_filter_application(Ext_image,S5S5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law14
    Image_Law = law_filter_application(Ext_image,S5W5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    
    #law15
    Image_Law = law_filter_application(Ext_image,S5R5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));



    #law16
    Image_Law = law_filter_application(Ext_image,W5L5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    
    #law17
    Image_Law = law_filter_application(Ext_image,W5E5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law18
    Image_Law = law_filter_application(Ext_image,W5S5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law19
    Image_Law = law_filter_application(Ext_image,W5W5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law20
    Image_Law = law_filter_application(Ext_image,W5R5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law21
    Image_Law = law_filter_application(Ext_image,R5L5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law22
    Image_Law = law_filter_application(Ext_image,R5E5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law23
    Image_Law = law_filter_application(Ext_image,R5S5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law24
    Image_Law = law_filter_application(Ext_image,R5W5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));


    #law25
    Image_Law = law_filter_application(Ext_image,R5R5);
    Average_Energy.append((sum(sum(abs(Image_Law))))/(128*128));

    
    return Average_Energy;


#Function to get Feature Normalisation
def feature_normalisation(Image):
    Feature_norm = np.zeros((samples,features))
    for j in range(0,features):
        for i in range(0,samples):
            Feature_norm[i][j] = ((Image[i][j] - np.mean(Image[i,:]))/((np.std(Image[i,:]))));
    return Feature_norm;

#Function to do PCA
def PCA(Image):
    pca = decomposition.PCA(n_components=3)
    pca.fit(Image)
    Feature_components = pca.transform(Image)
    return Feature_components;


#Function to do k-means clustering
def kmeans_clustering(Components):
    kmeans = KMeans(n_clusters=4)
    kmeans.fit(Components)
    labels = kmeans.predict(Components)
    return labels;


#Variable declarations
Average_Energy_image1 = []; 
Row_Size = 128;
Column_Size = 128;
samples = 12;
features = 25;
n = 2;

#Creation of Law Filters
L5 = np.array([1, 4, 6, 4, 1]);      #Level
E5 = np.array([-1, -2, 0, 2, 1]);    #Edge
S5 = np.array([-1, 0, 2, 0, -1]);    #Spot
W5 = np.array([-1, 2, 0, -2, 1]);    #Wave
R5 = np.array([1, -4, 6, -4, 1]);    #Ripple

L5L5 = creating_law_filters(L5,L5);
L5E5 = creating_law_filters(L5,E5);
L5S5 = creating_law_filters(L5,S5);
L5W5 = creating_law_filters(L5,W5);
L5R5 = creating_law_filters(L5,R5);

E5L5 = creating_law_filters(E5,L5); 
E5E5 = creating_law_filters(E5,E5);
E5S5 = creating_law_filters(E5,S5);
E5W5 = creating_law_filters(E5,W5);
E5R5 = creating_law_filters(E5,R5);

S5L5 = creating_law_filters(S5,L5);
S5E5 = creating_law_filters(S5,E5);
S5S5 = creating_law_filters(S5,S5);
S5W5 = creating_law_filters(S5,W5);
S5R5 = creating_law_filters(S5,R5);

W5L5 = creating_law_filters(W5,L5);
W5E5 = creating_law_filters(W5,E5);
W5S5 = creating_law_filters(W5,S5);
W5W5 = creating_law_filters(W5,W5);
W5R5 = creating_law_filters(W5,R5);

R5L5 = creating_law_filters(R5,L5);
R5E5 = creating_law_filters(R5,E5);
R5S5 = creating_law_filters(R5,S5);
R5W5 = creating_law_filters(R5,W5);
R5R5 = creating_law_filters(R5,R5);

#Image1
#Reading the image
Input_image1 = reading_image('texture1.raw')
#Subtraction of means
Subtracted_image1 = mean_subtraction(Input_image1);
Ext_image1 = boundary_extension(Subtracted_image1);
Average_Energy_image1 = getting_25D(Ext_image1);

#Image2
#Reading the image
Input_image2 = reading_image('texture2.raw')
#Subtraction of means
Subtracted_image2 = mean_subtraction(Input_image2);
#Boundary extension of the image
Ext_image2 = boundary_extension(Subtracted_image2);
#Applying the law filters
Average_Energy_image2 = getting_25D(Ext_image2);

#Image3
#Reading the image
Input_image3 = reading_image('texture3.raw')
#Subtraction of means
Subtracted_image3 = mean_subtraction(Input_image3);
#Boundary extension of the image
Ext_image3 = boundary_extension(Subtracted_image3);
#Applying the law filters
Average_Energy_image3 = getting_25D(Ext_image3);

#Image4
#Reading the image
Input_image4 = reading_image('texture4.raw')
#Subtraction of means
Subtracted_image4 = mean_subtraction(Input_image4);
#Boundary extension of the image
Ext_image4 = boundary_extension(Subtracted_image4);
#Applying the law filters
Average_Energy_image4 = getting_25D(Ext_image4);

#Image5
#Reading the image
Input_image5 = reading_image('texture5.raw')
#Subtraction of means
Subtracted_image5 = mean_subtraction(Input_image5);
#Boundary extension of the image
Ext_image5 = boundary_extension(Subtracted_image5);
#Applying the law filters
Average_Energy_image5 = getting_25D(Ext_image5);

#Image6
#Reading the image
Input_image6 = reading_image('texture6.raw')
#Subtraction of means
Subtracted_image6 = mean_subtraction(Input_image6);
#Boundary extension of the image
Ext_image6 = boundary_extension(Subtracted_image6);
#Applying the law filters
Average_Energy_image6 = getting_25D(Ext_image6);

#Image7
#Reading the image
Input_image7 = reading_image('texture7.raw')
#Subtraction of means
Subtracted_image7 = mean_subtraction(Input_image7);
#Boundary extension of the image
Ext_image7 = boundary_extension(Subtracted_image7);
#Applying the law filters
Average_Energy_image7 = getting_25D(Ext_image7);

#Image8
#Reading the image
Input_image8 = reading_image('texture8.raw')
#Subtraction of means
Subtracted_image8 = mean_subtraction(Input_image8);
#Boundary extension of the image
Ext_image8 = boundary_extension(Subtracted_image8);
#Applying the law filters
Average_Energy_image8 = getting_25D(Ext_image8);

#Image9
#Reading the image
Input_image9 = reading_image('texture9.raw')
#Subtraction of means
Subtracted_image9 = mean_subtraction(Input_image9);
#Boundary extension of the image
Ext_image9 = boundary_extension(Subtracted_image9);
#Applying the law filters
Average_Energy_image9 = getting_25D(Ext_image9);

#Image10
#Reading the image
Input_image10 = reading_image('texture10.raw')
#Subtraction of means
Subtracted_image10 = mean_subtraction(Input_image10);
#Boundary extension of the image
Ext_image10 = boundary_extension(Subtracted_image10);
#Applying the law filters
Average_Energy_image10 = getting_25D(Ext_image10);

#Image11
#Reading the image
Input_image11 = reading_image('texture11.raw')
#Subtraction of means
Subtracted_image11 = mean_subtraction(Input_image11);
#Boundary extension of the image
Ext_image11 = boundary_extension(Subtracted_image11);
#Applying the law filters
Average_Energy_image11 = getting_25D(Ext_image11);

#Image12
#Reading the image
Input_image12 = reading_image('texture12.raw')
#Subtraction of means
Subtracted_image12 = mean_subtraction(Input_image12);
#Boundary extension of the image
Ext_image12 = boundary_extension(Subtracted_image12);
#Applying the law filters
Average_Energy_image12 = getting_25D(Ext_image12);


Feature_Set = np.stack((Average_Energy_image1,Average_Energy_image2,Average_Energy_image3,
                          Average_Energy_image4,Average_Energy_image5,Average_Energy_image6,
                          Average_Energy_image7,Average_Energy_image8,Average_Energy_image9,
                          Average_Energy_image10,Average_Energy_image11,Average_Energy_image12));


                        
Feature_norm = feature_normalisation(Feature_Set);

Feature_Components = PCA(Feature_norm);

Labels = kmeans_clustering(Feature_Components);


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

'''3 = red
1 = blue
2 = green
0 = yellow'''

ax.scatter(Feature_Components[0,0], Feature_Components[0,1], Feature_Components[0,2] ,c='r', marker='o')
ax.scatter(Feature_Components[1,0], Feature_Components[1,1], Feature_Components[1,2] ,c='y', marker='o')
ax.scatter(Feature_Components[2,0], Feature_Components[2,1], Feature_Components[2,2] ,c='b', marker='o')
ax.scatter(Feature_Components[3,0], Feature_Components[3,1], Feature_Components[3,2] ,c='g', marker='o')
ax.scatter(Feature_Components[4,0], Feature_Components[4,1], Feature_Components[4,2] ,c='r', marker='o')
ax.scatter(Feature_Components[5,0], Feature_Components[5,1], Feature_Components[5,2] ,c='g', marker='o')
ax.scatter(Feature_Components[6,0], Feature_Components[6,1], Feature_Components[6,2] ,c='r', marker='o')
ax.scatter(Feature_Components[7,0], Feature_Components[7,1], Feature_Components[7,2] ,c='y', marker='o')
ax.scatter(Feature_Components[8,0], Feature_Components[8,1], Feature_Components[8,2] ,c='b', marker='o')
ax.scatter(Feature_Components[9,0], Feature_Components[9,1], Feature_Components[9,2] ,c='b', marker='o')
ax.scatter(Feature_Components[10,0], Feature_Components[10,1], Feature_Components[10,2] ,c='y', marker='o')
ax.scatter(Feature_Components[11,0], Feature_Components[11,1], Feature_Components[11,2] ,c='g', marker='o')


plt.show();


