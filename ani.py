import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import os
import shutil
from datetime import datetime
# import random
# from time import sleep


num_procs = 16
space = 128
run_number = 1
spacey = space


location = "/localscratch/ughima/data/"


run1 = location + "run1/TserE00.dat"
data1 = np.loadtxt(run1)
fig = plt.figure()
plt.plot(data1)
fig.savefig('TSE.png')


mat_files = []
mat_data = {}


for i in range(num_procs):
    mat_files.append(location +"run" + str(run_number) + "/"+"MAT"+ str(i)+".dat")
for i in range(num_procs):
    mat_data[i] = np.loadtxt(mat_files[i])


# ##################################################################################



cols_per_pro = (int)(space/num_procs)

number_of_frames = (int)(mat_data[0].shape[0]/cols_per_pro) 

frames = np.zeros((number_of_frames , space , spacey))

for i in range(number_of_frames):
    
    frames[i] = np.vstack((mat_data[0][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[1][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[2][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[3][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[4][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[5][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[6][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[7][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[8][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[9][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[10][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[11][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[12][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[13][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[14][i*cols_per_pro:(i+1)*cols_per_pro,:],
                           mat_data[15][i*cols_per_pro:(i+1)*cols_per_pro,:]))   
    
    
# ###############################################################################################    
    


fig = plt.figure()


ims = []

a = 2
for i in range((int)(number_of_frames/a)):

    im = plt.imshow(frames[a*i], animated=True,vmin = -55,vmax = 30)
    if i==0:
        plt.colorbar()
	
    ims.append([im])
    
    

# ani = animation.ArtistAnimation(fig, ims, interval=50, blit=True,
#                                 repeat_delay=1000)

ani = animation.ArtistAnimation(fig, ims, interval=100, blit=True,repeat = False)

ani.save('./video.gif')


a ="/home/ug/15/ughima/tissue/"+ datetime.now().strftime("%Y-%m-%d__%H:%M:%S")
os.mkdir(a)


shutil.copyfile("./main.c", a+"/main.c")
shutil.copyfile("./params.h",a+"/params.h")
shutil.move("./video.gif",a+"/video.gif")
shutil.move("./TSE.png",a+"/TSE.png")





print("All Done.")
