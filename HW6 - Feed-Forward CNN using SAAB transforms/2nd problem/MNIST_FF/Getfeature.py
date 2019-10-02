import pickle
import numpy as np
import data
import saab
import keras
import sklearn
import cv2
from skimage import color
from skimage import io
from scipy import linalg
import matplotlib.pyplot as plt


def main():
    # load data
    fr = open('pca_params.pkl', 'rb')
    pca_params = pickle.load(fr)
    fr.close()

    # read data
    #train_images, train_labels, class_list = data.import_data("0-9")
    train_img1 = color.rgb2gray(io.imread('1.png'))
    train_img2 = color.rgb2gray(io.imread('2.png'))
    train_img3 = color.rgb2gray(io.imread('3.png'))
    train_img4 = color.rgb2gray(io.imread('4.png'))
    train_images = train_img4
    #train_images  = train_img1;
    train_images=train_images.reshape(1,32,32,1)
    

    print('Training image size: dtype: ', train_images.shape, train_images.dtype)
    #print('Testing_image size:', test_images.shape)
    

    # Training
    print('--------Training--------')
    train_red = train_images
    
    feature,pca_params = saab.initialize(train_red, pca_params)
    
    n,h,w,c = np.shape(feature)
    
    # 60000x400 (16*5*5)
    feature = feature.reshape(feature.shape[0], -1)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    print ('feature.dtype: {}'.format(feature.dtype))
    feat = {}
    feat['feature'] = feature
    
    #Reconstructing  the image
    
    feature = np.reshape(feature,(n,h,w,c))
    trans = np.reshape(feature,(h*w,-1))
    
    stages = [1,0];
    
    for i in stages:
        DC_comp = pca_params['Layer_%d/dc'%i]
        f_expect = pca_params['Layer_%d/feature_expectation'%i]
        kernels = pca_params['Layer_%d/kernel'%i]
        kernelst_inv = np.linalg.pinv(np.transpose(kernels))

        
        if (i == 0):
            trans = np.reshape(trans,( 64, 8 ))
            spc = np.matmul(trans,kernelst_inv)
        else:
            kernels_shape = np.shape(kernels)
            e = np.zeros( ( 1, kernels_shape[0] ) )
            e[0 ,0 ] = 1
            bias_factor = pca_params['Layer_%d/bias'%i]
            
            trans += e*bias_factor;
            spcwb = np.matmul(trans,kernelst_inv)
            spc = spcwb - ((np.sqrt(128))*bias_factor)
            
        s_p = spc + f_expect
        s_p_shape = np.shape(s_p)
        h = int(np.sqrt(s_p_shape[0]))
        w = int(np.sqrt(s_p_shape[0]))
        s_p = s_p.reshape(1, h, w, -1)
        
        s_p_t = [0,1,3,5,2,4,6,7]
        
        if (i == 0):
            s_p_bef = [1,8,8,1,1,4,4,1]
            s_p = np.reshape(s_p,(s_p_bef))
            p = s_p.transpose(s_p_t).reshape(1,32,32,1)
            trans = p;
        else:
            s_p_bef = [1,2,2,1,1,4,4,8]
            s_p = np.reshape(s_p,(s_p_bef))
            p = s_p.transpose(s_p_t).reshape(1,8,8,8)
            trans = p;
            
    trans = np.reshape(trans,(32,32))
    
    plt.imshow(trans,cmap = 'gray')
    
    #PSNR calculation
    def PSNR_cal(I_image,y_image):
        den = 0;
        for i in range(0,32):
            for j in range(0,32):
                den += (y_image[i][j] - I_image[i][j])**2;
        factor = (1/(32*32));
        mse = factor*den;
        psnr = 10*np.log10((255*255)/mse);
        return psnr;
    psnr = PSNR_cal(train_img4,trans)
                
    
    
    print("The psnr is" ,psnr)
    
    '''#Reconstructing  the image
    
    feature = np.reshape(feature,(n,h,w,c))
    trans = np.reshape(feature,(h*w,-1))
    
    stages = [1,0];
    
    for i in stages:
        DC_comp = pca_params['Layer_%d/dc'%i]
        f_expect = pca_params['Layer_%d/feature_expectation'%i]
        kernels = pca_params['Layer_%d/kernel'%i]
        kernelst_inv = np.linalg.pinv(np.transpose(kernels))

        
        if (i == 0):
            trans = np.reshape(trans,( 64, 4 ))
            spc = np.matmul(trans,kernelst_inv)
        else:
            kernels_shape = np.shape(kernels)
            e = np.zeros( ( 1, kernels_shape[0] ) )
            e[0 ,0 ] = 1
            bias_factor = pca_params['Layer_%d/bias'%i]
            
            trans += e*bias_factor;
            spcwb = np.matmul(trans,kernelst_inv)
            spc = spcwb - ((np.sqrt(64))*bias_factor)
            
        s_p = spc + f_expect
        s_p_shape = np.shape(s_p)
        h = int(np.sqrt(s_p_shape[0]))
        w = int(np.sqrt(s_p_shape[0]))
        s_p = s_p.reshape(1, h, w, -1)
        
        s_p_t = [0,1,3,5,2,4,6,7]
        
        if (i == 0):
            s_p_bef = [1,8,8,1,1,4,4,1]
            s_p = np.reshape(s_p,(1,8,8,1,1,4,4,1))
            p = s_p.transpose(s_p_t).reshape(1,32,32,1)
            trans = p;
        else:
            s_p_bef = [1,2,2,1,1,4,4,4]
            s_p = np.reshape(s_p,(1,2,2,1,1,4,4,4))
            p = s_p.transpose(s_p_t).reshape(1,8,8,4)
            trans = p;
            
    trans = np.reshape(trans,(32,32))
    
    plt.imshow(trans,cmap = 'gray')
    
    #PSNR calculation
    def PSNR_cal(I_image,y_image):
        den = 0;
        for i in range(0,32):
            for j in range(0,32):
                den += (y_image[i][j] - I_image[i][j])**2;
        factor = (1/(32*32));
        mse = factor*den;
        psnr = 10*np.log10((255*255)/mse);
        return psnr;
    psnr = PSNR_cal(train_img4,trans)
                
    
    
    print("The psnr is" ,psnr)'''
        
    # save data
    fw = open('feat.pkl', 'wb')
    pickle.dump(feat, fw)
    fw.close()


if __name__ == '__main__':
    main()