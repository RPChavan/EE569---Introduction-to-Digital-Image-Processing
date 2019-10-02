
from tensorflow.python.platform import flags
import pickle
import data
import saab
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

flags.DEFINE_string("output_path", None, "The output dir to save params")
flags.DEFINE_string("use_classes", "0-9", "Supported format: 0,1,5-9")
flags.DEFINE_string("kernel_sizes", "3,3", "Kernels size for each stage. Format: '3,3'")
flags.DEFINE_string("num_kernels", "2,8", "Num of kernels for each stage. Format: '4,10'")
flags.DEFINE_float("energy_percent", None, "Energy to be preserved in each stage")
flags.DEFINE_integer("use_num_images", 6000, "Num of images used for training")
FLAGS = flags.FLAGS

def main():
	# read data
    train_images, train_labels, test_images, test_labels, class_list = data.import_data(FLAGS.use_classes)
    print('Training image size:', train_images.shape)
    print('Testing_image size:', test_images.shape)

    train_images = train_images[:6000]
    train_labels = train_labels[:6000]
    kernel_sizes=saab.parse_list_string(FLAGS.kernel_sizes)
    if FLAGS.num_kernels:
    	num_kernels=saab.parse_list_string(FLAGS.num_kernels)
    else:
    	num_kernels=None
    energy_percent=FLAGS.energy_percent
    use_num_images=FLAGS.use_num_images
    print('Parameters:')
    print('use_classes:', class_list)
    print('Kernel_sizes:', kernel_sizes)
    print('Number_kernels:', num_kernels)
    print('Energy_percent:', energy_percent)
    print('Number_use_images:', use_num_images)
    
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
    
    Row_Size = 32;
    Column_Size = 32;
    Window_Size = 5;
    n1 = 2
    features = 25;
    samples = 32*32;
    
    
    L5 = np.array([1, 4, 6, 4, 1]);      #Level
    E5 = np.array([-1, -2, 0, 2, 1]);    #Edge
    S5 = np.array([-1, 0, 2, 0, -1]);    #Spot
    W5 = np.array([-1, 2, 0, -2, 1]);    #Wave
    R5 = np.array([1, -4, 6, -4, 1]);
    
    #L5S5 = creating_law_filters(L5,S5);
    L5W5 = creating_law_filters(L5,W5);
    
    #Reading the image
    for i in range(0,6000):
        Input_image = train_images[i,:,:,0]
        #Boundary extension of the image
        Ext_image = boundary_extension(Input_image,n1);
        #Applying the law filters
        
        train_images[i,:,:,0] = law_filter_application(Ext_image,L5S5);
        
    '''train_img1 = color.rgb2gray(io.imread('1.png'))
    Input_image = train_img1
        #Boundary extension of the image
    Ext_image = boundary_extension(Input_image,n1);
        #Applying the law filters
        
    train_img1 = law_filter_application(Ext_image,L5S5)
    plt.matshow(train_img1,cmap='gray') '''  
    
    

    pca_params=saab.multi_Saab_transform(train_images, train_labels,
    	                 kernel_sizes=kernel_sizes,
    	                 num_kernels=num_kernels,
    	                 energy_percent=energy_percent,
    	                 use_num_images=use_num_images,
    	                 use_classes=class_list)
    # save data
    fw=open('pca_params.pkl','wb')    
    pickle.dump(pca_params, fw)    
    fw.close()

    # load data
    fr=open('pca_params.pkl','rb')  
    data1=pickle.load(fr)
    print(data1)
    fr.close()

if __name__ == '__main__':
	main()

















