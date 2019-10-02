# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 20:59:07 2019

@author: Hp
"""

# -*- coding: utf-8 -*-
"""
Created on Tue Mar 12 20:28:08 2019

@author: Rakshitha Panduranga
"""

import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import inv
import math as mt
from sklearn import decomposition
import pandas as pd
from sklearn.cluster import KMeans
from scipy import stats

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


#Function to apply Boundary Extension
def boundary_extension(Image,n):
    Ext_image = np.zeros((Row_Size+(2*n),Column_Size+(2*n)))
    #Complete image
    #Ext_image = np.pad(Image,n,'reflect');
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
            Ext_image[i][j] = Image[Row_Size-1][j-n];
    #Right columns
    for j in range(Column_Size+n, Column_Size+(2*n)):
        for i in range(n,(Row_Size+n)):
            Ext_image[i][j] = Image[i-n][Column_Size-1];
    #Corners
    for i in range(0,n):
        for j in range(0,n):
            Ext_image[i][j] = Image[0][0];

    for i in range(0,n):
        for j in range(Column_Size+n,Column_Size+(2*n)):
            Ext_image[i][j] = Image[0][Column_Size-1];

    for j in range(0,n):
        for i in range(Row_Size+n,Row_Size+(2*n)):
            Ext_image[i][j] = Image[Row_Size-1][0];

    for j in range(Column_Size+n, Column_Size+(2*n)):
        for i in range(Row_Size+n, Row_Size+(2*n)):
            Ext_image[i][j] = Image[Row_Size-1][Column_Size-1];
    
    return Ext_image;


#Function to get the squared image
def image_square(Image):
    for i in range(0,Row_Size):
        for j in range(0,Column_Size):
            Image[i][j] = (abs(Image[i][j]));
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

#Function to get Energy for each feature
def getting_energy_feature(Image):
    upper = int(np.ceil(Window_Size/2));
    lower = int(np.floor(Window_Size/2));
    Energy_feature = [];
    for i in range(n2,Row_Size+n2):
        for j in range(n2,Column_Size+n2):
                intermediate = Image[(i-lower):(i+upper),(j-lower):(j+upper)];
                intermediate2 = abs(intermediate);
                final = np.mean(intermediate2)
                Energy_feature.append(final); 
    return Energy_feature;
        


def getting_25D(Ext_image):
    Average_Energy = np.zeros((samples,features));
    #law1
    Image_Law = law_filter_application(Ext_image,L5L5);
   # print(Image_Law[0:10,0:10]);
    #print("*********");
    Ext_image1 = boundary_extension(Image_Law,n2);
    #print(Ext_image1[0:10,0:10]);
    #print("*********");
    Average_Energy_image1 = getting_energy_feature(Ext_image1);
   # print(Average_Energy_image1);
   # print("*********");
    #law2
    Image_Law = law_filter_application(Ext_image,L5E5);
    Ext_image2 = boundary_extension(Image_Law,n2);
    Average_Energy_image2 = getting_energy_feature(Ext_image2);
    print("her1");
    #law3
    Image_Law = law_filter_application(Ext_image,L5S5);
    Ext_image3 = boundary_extension(Image_Law,n2);
    Average_Energy_image3 = getting_energy_feature(Ext_image3);

    #law4
    Image_Law = law_filter_application(Ext_image,L5W5);
    Ext_image4 = boundary_extension(Image_Law,n2);
    Average_Energy_image4 = getting_energy_feature(Ext_image4);

    #law5
    Image_Law = law_filter_application(Ext_image,L5R5);
    Ext_image5 = boundary_extension(Image_Law,n2);
    Average_Energy_image5 = getting_energy_feature(Ext_image5);
    print("here2")
    #law6
    Image_Law = law_filter_application(Ext_image,E5L5);
    Ext_image6 = boundary_extension(Image_Law,n2);
    Average_Energy_image6 = getting_energy_feature(Ext_image6);

    #law7
    Image_Law = law_filter_application(Ext_image,E5E5);
    Ext_image7 = boundary_extension(Image_Law,n2);
    Average_Energy_image7 = getting_energy_feature(Ext_image7);
    
    #law8
    Image_Law = law_filter_application(Ext_image,E5S5);
    Ext_image8 = boundary_extension(Image_Law,n2);
    Average_Energy_image8 = getting_energy_feature(Ext_image8);
    
    #law9
    Image_Law = law_filter_application(Ext_image,E5W5);
    Ext_image9 = boundary_extension(Image_Law,n2);
    Average_Energy_image9 = getting_energy_feature(Ext_image9);
    
    #law10
    Image_Law = law_filter_application(Ext_image,E5R5);
    Ext_image10 = boundary_extension(Image_Law,n2);
    Average_Energy_image10 = getting_energy_feature(Ext_image10);

    #law11
    Image_Law = law_filter_application(Ext_image,S5L5);
    Ext_image11 = boundary_extension(Image_Law,n2);
    Average_Energy_image11 = getting_energy_feature(Ext_image11);
    print("getting 25d _ 2")
    #law12
    Image_Law = law_filter_application(Ext_image,S5E5);
    Ext_image12 = boundary_extension(Image_Law,n2);
    Average_Energy_image12 = getting_energy_feature(Ext_image12);
    print("getting 25d _ 2")

    #law13
    Image_Law = law_filter_application(Ext_image,S5S5);
    Ext_image13 = boundary_extension(Image_Law,n2);
    Average_Energy_image13 = getting_energy_feature(Ext_image13);
    print("getting 25d _ 2")

    #law14
    Image_Law = law_filter_application(Ext_image,S5W5);
    Ext_image14 = boundary_extension(Image_Law,n2);
    Average_Energy_image14 = getting_energy_feature(Ext_image14);
    print("getting 25d _ 2")

    
    #law15
    Image_Law = law_filter_application(Ext_image,S5R5);
    Ext_image15 = boundary_extension(Image_Law,n2);
    Average_Energy_image15 = getting_energy_feature(Ext_image15);
    print("getting 25d _ 2")

    #law16
    Image_Law = law_filter_application(Ext_image,W5L5);
    Ext_image16 = boundary_extension(Image_Law,n2);
    Average_Energy_image16 = getting_energy_feature(Ext_image16);
    print("getting 25d _ 2")
    #law17
    Image_Law = law_filter_application(Ext_image,W5E5);
    Ext_image17 = boundary_extension(Image_Law,n2);
    Average_Energy_image17 = getting_energy_feature(Ext_image17);
    print("getting 25d _ 2")
    #law18
    Image_Law = law_filter_application(Ext_image,W5S5);
    Ext_image18 = boundary_extension(Image_Law,n2);
    Average_Energy_image18 = getting_energy_feature(Ext_image18);
    print("getting 25d _ 2")
    
    #law19
    Image_Law = law_filter_application(Ext_image,W5W5);
    Ext_image19 = boundary_extension(Image_Law,n2);
    Average_Energy_image19 = getting_energy_feature(Ext_image19);
    print("getting 25d _ 2")
    #law20
    Image_Law = law_filter_application(Ext_image,W5R5);
    Ext_image20 = boundary_extension(Image_Law,n2);
    Average_Energy_image20 = getting_energy_feature(Ext_image20);
    print("getting 25d _ 2")

    #law21
    Image_Law = law_filter_application(Ext_image,R5L5);
    Ext_image21 = boundary_extension(Image_Law,n2);
    Average_Energy_image21 = getting_energy_feature(Ext_image21);
    print("getting 25d _ 2")
    #law22
    Image_Law = law_filter_application(Ext_image,R5E5);
    Ext_image22 = boundary_extension(Image_Law,n2);
    Average_Energy_image22 = getting_energy_feature(Ext_image22);
    print("getting 25d _ 2")
    #law23
    Image_Law = law_filter_application(Ext_image,R5S5);
    Ext_image23 = boundary_extension(Image_Law,n2);
    Average_Energy_image23 = getting_energy_feature(Ext_image23);
    print("getting 25d _ 2")
    #law24
    Image_Law = law_filter_application(Ext_image,R5W5);
    Ext_image24 = boundary_extension(Image_Law,n2);
    Average_Energy_image24 = getting_energy_feature(Ext_image24);
    print("getting 25d _ 2")
    #law25
    Image_Law = law_filter_application(Ext_image,R5R5);
    Ext_image25 = boundary_extension(Image_Law,n2);
    Average_Energy_image25 = getting_energy_feature(Ext_image25);
    print("getting 25d _ 2")
    Average_Energy = np.column_stack((Average_Energy_image1,Average_Energy_image2,Average_Energy_image3,
                          Average_Energy_image4,Average_Energy_image5,Average_Energy_image6,
                          Average_Energy_image7,Average_Energy_image8,Average_Energy_image9,
                          Average_Energy_image10,Average_Energy_image11,Average_Energy_image12,
                          Average_Energy_image13,Average_Energy_image14,Average_Energy_image15,
                          Average_Energy_image16,Average_Energy_image17,Average_Energy_image18,
                          Average_Energy_image19,Average_Energy_image20,Average_Energy_image21,
                          Average_Energy_image22,Average_Energy_image23,Average_Energy_image24,
                          Average_Energy_image25));
    return Average_Energy;

'''#Function to get Feature Normalisation
def feature_normalisation(Image):
    Feature_norm = np.zeros((samples,features));
    for j in range(0,features):
        for i in range(0,samples):
            Feature_norm[i][j] = (Image[i][j]/Image[i][0] );
    return Feature_norm;'''
    
#Function to get Feature Normalisation
def feature_normalisation(Image):
    Feature_norm = np.zeros((samples,features));
    
    for j in range(0,features):
        Mean = np.mean(Image[:,j]);
        Sd = (np.var(Image[:,j]))**(1/2);
        for i in range(0,samples):
            Feature_norm[i][j] = ((Image[i][j] - Mean)/Sd);
    return Feature_norm;

#Variable declarations
Row_Size = 510;
Column_Size = 510;
Window_Size = 9;
n1 = 2;
n2 = 4;
features = 25;
samples = 510*510;
Output_image = np.zeros((Row_Size,Column_Size));

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

#Function to do PCA
def PCA(Image):
    pca = decomposition.PCA(n_components=3)
    pca.fit(Image)
    Feature_components = pca.transform(Image)
    return Feature_components;

#Function to do k-means clustering
def kmeans_clustering(Components):
    kmeans = KMeans(n_clusters=7)
    kmeans.fit(Components)
    labels = kmeans.predict(Components)
    return labels;

#Function to denote the segemented regions
def denote_segmentation(Image):
    for i in range(0,Row_Size):
        for j in range(0, Column_Size):
            if(Segmented_matrix[i][j] == 0):
                Output_image[i][j] = 0;
            elif(Segmented_matrix[i][j] == 1):
                Output_image[i][j] = 42;
            elif(Segmented_matrix[i][j] == 2):
                Output_image[i][j] = 84;
            elif(Segmented_matrix[i][j] == 3):
                Output_image[i][j] = 126;
            elif(Segmented_matrix[i][j] == 4):
                Output_image[i][j] = 168;
            elif(Segmented_matrix[i][j] == 5):
                Output_image[i][j] = 210;
            elif(Segmented_matrix[i][j] == 6):
                Output_image[i][j] = 255;
    return Output_image;

#Reading the image
Input_image = reading_image('comb.raw')
#Boundary extension of the image
Ext_image = boundary_extension(Input_image,n1);
#Applying the law filters
Average_Feature = getting_25D(Ext_image);

Feature_norm = feature_normalisation(Average_Feature); 

Feature_Components = PCA(Feature_norm);

Labels = kmeans_clustering(Feature_Components);

Segmented_matrix = np.reshape(Labels, (Row_Size,Column_Size));

Output_image = denote_segmentation(Segmented_matrix);

n3 = 19;
Boundou_ext_image = boundary_extension(Output_image,n3);

final = np.zeros((Row_Size,Column_Size))
lowerout= int(np.floor(n3));
upperout = int(np.ceil(n3));
for i in range(n3,Row_Size+n3):
    for j in range(n3,Column_Size+n3):
           intermediate_out = Boundou_ext_image[(i-lowerout):(i+upperout),(j-lowerout):(j+upperout)];
           var,g = stats.mode(intermediate_out,axis = None);
           x = var[0]
           final[i-n3][j-n3] = int(x);
           
           
        
plt.matshow(final,cmap='gray')         