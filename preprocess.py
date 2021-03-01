#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import os
import numpy as np
import pandas as pd
import glob
from pathlib import Path

datapath = './data/'
metapath = datapath + 'metadata/'
trainpath = datapath + 'train/'
testpath = datapath + 'test/'


# In[ ]:


# Extract testing files, buildings and sites:
os.system(f'grep SiteID {testpath}/* > test_buildings.txt' )


# In[2]:



test_buildings = pd.read_csv('test_buildings.txt',sep='\t',header=None,names=['file','building','site'])
test_buildings['file'] = test_buildings['file'].apply(lambda x: x[:-2])
test_buildings['building'] = test_buildings['building'].apply(lambda x: x[7:])

# How many buildings in the testing set?
buildings = np.unique(test_buildings['building'])
print('There are',len(buildings),'buildings in the testing set.')

test_buildings.head()


# Floor dictionary as defined by Devin in his nice work @ https://www.kaggle.com/devinanzelmo/wifi-features

# In[3]:


floors = {"B3":-3,"B2":-2,"B1":-1,"F1":0,"1F":0,"F2":1,"2F":1,"F3":2,"3F":2,"F4":3,"4F":3,
          "F5":4,"5F":4,"F6":5,"6F":5,"F7":6,"7F":6,"F8":7,"8F": 7,"F9":8,"9F":8,"F10":9}

# Other floors:
floorsB = {"B":0,"BF":1,"BM":2}
floorsG = {"G":0}
floorsM = {"M":0}
floorsP = {"P1":0,"P2":1}
floorsL = {"LG2":-2,"LG1":-1,"LG":0,"LM":0,"L1":1,"L2":2,"L3":3,"L4":4,"L5":5,"L6":6,"L7":7,"L8":8,"L9":9,"L10":10,"L11":11}


# In[4]:


er=os.system("g++ src/1_preprocess.cpp -std=c++11 -o bin/preprocess")
if(er): print("Error")


# In[ ]:


# Fix data quality issues and reformat dataset:
os.system('mkdir -p data/pre/train')
for building in os.listdir(trainpath):
    for floor in os.listdir(trainpath+building):
        path_filenames = list(Path(trainpath+building+f'/{floor}/').resolve().glob("*.txt"))
        for path_filename in path_filenames:
            if floor in floors:
                er=os.system(f'./bin/preprocess {path_filename} data/pre/train {building} {floors[floor]}')
            if(er): print("Error:",path_filename)
    print(f'done for {building}')


# In[ ]:
