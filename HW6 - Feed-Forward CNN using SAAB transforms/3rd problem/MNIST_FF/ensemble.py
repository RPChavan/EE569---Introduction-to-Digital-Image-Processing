# -*- coding: utf-8 -*-
"""
Created on Sun Apr 28 15:01:26 2019

@author: Hp
"""
import pickle
import numpy as np
from sklearn.decomposition import PCA
from sklearn.svm import SVC
import data


fr=open('llsr_feature1.pkl','rb')  
feature1 = pickle.load(fr)
fr.close()


fr=open('llsr_feature1_test.pkl','rb')  
feature1_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature2.pkl','rb')  
feature2 = pickle.load(fr)
fr.close()


fr=open('llsr_feature2_test.pkl','rb')  
feature2_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature3.pkl','rb')  
feature3 = pickle.load(fr)
fr.close()


fr=open('llsr_feature3_test.pkl','rb')  
feature3_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature4.pkl','rb')  
feature4 = pickle.load(fr)
fr.close()


fr=open('llsr_feature4_test.pkl','rb')  
feature4_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature5.pkl','rb')  
feature5 = pickle.load(fr)
fr.close()


fr=open('llsr_feature5_test.pkl','rb')  
feature5_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature6.pkl','rb')  
feature6 = pickle.load(fr)
fr.close()


fr=open('llsr_feature6_test.pkl','rb')  
feature6_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature7.pkl','rb')  
feature7 = pickle.load(fr)
fr.close()


fr=open('llsr_feature7_test.pkl','rb')  
feature7_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature8.pkl','rb')  
feature8 = pickle.load(fr)
fr.close()


fr=open('llsr_feature8_test.pkl','rb')  
feature8_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature9.pkl','rb')  
feature9 = pickle.load(fr)
fr.close()


fr=open('llsr_feature9_test.pkl','rb')  
feature9_test = pickle.load(fr)
fr.close()

fr=open('llsr_feature10.pkl','rb')  
feature10 = pickle.load(fr)
fr.close()


fr=open('llsr_feature10_test.pkl','rb')  
feature10_test = pickle.load(fr)
fr.close()




feature_train = np.column_stack((feature1,feature2,feature3,feature4,feature5,feature6,feature7,feature8,feature9,feature10))
feature_test = np.column_stack((feature1_test,feature2_test,feature3_test,feature4_test,feature5_test,feature6_test,feature7_test,feature8_test,feature9_test,feature10_test))

train_images, train_labels, test_images, test_labels, class_list = data.import_data("0-9")
train_labels = train_labels[:6000]
test_labels = test_labels[:6000]

feature1_test = feature1_test[:6000]

pca = PCA(n_components=10)
pca.fit(feature_train)

feature_train = pca.transform(feature_train)


feature_test = pca.transform(feature_test)



obj = SVC(gamma='auto')
obj.fit(feature_train, train_labels)

predicted_train = obj.predict(feature_train)
predicted_test = obj.predict(feature_test)

count = 0;
for i in range(len(train_labels)):
    if(train_labels[i] == predicted_train[i]):
        count += 1;
        


training_accuracy = (count/len(train_labels))*100;

print("The training accuracy for  with SVM is-",training_accuracy)

count = 0;
for i in range(len(test_labels)):
    if(test_labels[i] == predicted_test[i]):
        count += 1;

testing_accuracy = (count/len(test_labels))*100;

print("The testing accuracy for  with SVM is-",testing_accuracy)


