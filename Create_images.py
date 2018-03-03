#coding:utf-8
import numpy as np  
import os  
import cv2    
import random 
import shutil
#----Parameters ----# 
IMG_NUM=60
Len=448
Width=448
R_target=30
Noise_level=0.20
Label_num=20
Pixel_max=250
Max_ratio=4  # max(back:target) = 1:4

#makedir 
path = "../JPEGIMS"

#clear old files
if((os.path.exists(path))):     
    shutil.rmtree(path)
os.mkdir(path)
 
print('Images will be save at :',path)
for i in range(0,IMG_NUM):
    #Create images 
    Label=random.randrange(1,Label_num+1) 
    p=((Max_ratio-1)/(float)(Label_num))*Label+1
    background_pixelval=Pixel_max*1/(1+p)
    target_pixelval=Pixel_max*p/(1+p)

    #background 
    img = np.zeros((Len,Width,1), np.uint8)     
    img.fill(background_pixelval)  

    #target
    x_target =random.randrange(R_target,Len-R_target)
    y_target = random.randrange(R_target,Width-R_target)
    #cv2.circle(img, (224, 224), 63, 250, -1) 
    cv2.circle(img,(x_target,y_target),R_target,target_pixelval,-1)

    #add noise 
    for x in range(0,Len):
        for y in range(0,Width):
            img[x,y,0]=img[x,y,0]*(1+(random.random()-0.5)*2*Noise_level)
    
    #output images
    cv2.imwrite(path+"/"+(str)(Label)+"_"+(str)(i)+".jpg",img) 
        
#show
#print(x_target,y_target,'\n')
#cv2.imshow('image',img)
#cv2.waitKey(0)    
#cv2.destroyAllWindows()
