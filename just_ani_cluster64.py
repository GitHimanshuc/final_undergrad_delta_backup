import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
plt.rcParams['animation.ffmpeg_path'] = '/home/ug/15/ughima/ffmpeg'
import matplotlib.animation as animation
import numpy as np
import os
from datetime import datetime
import shutil
import re
# import random
# from time import sleep




re_maxtime = re.compile(r'#define maxtime.*?([0-9.-]+)')
re_dt = re.compile(r'#define deltaT.*?([0-9.-]+)')
re_dx = re.compile(r'#define deltaX.*?([0-9.-]+)')
re_mean = re.compile(r'#define n_mean.*?([0-9.-]+)')
re_sizex = re.compile(r'const int spacex.*?([0-9.-]+);')

with open('./params.h') as f:
    for line in f:
        match = re_maxtime.match(line)
        match2 = re_dt.match(line)
        match3 = re_mean.match(line)
        match4 = re_dx.match(line)
        match5 = re_sizex.match(line)
        if match:
            maxtime = match.group(1)
        if match2:
            dt = match2.group(1)
        if match3:
            n_mean = match3.group(1)
        if match4:
            dx = match4.group(1)
        if match5:
            sizex = match5.group(1)


simtime = float(maxtime) * float(dt)  # (milliseconds)

num_procs = 64
space = int(sizex)
run_number = 10
spacey = space


location = "/localscratch/ughima/"+str(num_procs)+"procs/data/"



root_save_folder = "/home/ug/15/ughima/tissue/"+datetime.now().strftime("%Y-%m-%d__%H:%M:%S")
os.mkdir(root_save_folder)
shutil.copyfile("./main.c", root_save_folder+"/main.c")
shutil.copyfile("./params.h",root_save_folder+"/params.h")


for subdir,dirs,files in os.walk(location):
    for folder in dirs:
        data_folder=os.path.join(location,folder)

        save_folder=root_save_folder+"/"+folder

        os.mkdir(save_folder)  #makes folder with names like run1 





        mat_files = []
        mat_data = {}
        tse_files = []
        tse_data = {}
        n_files = []
        n_data = {}




        for i in range(num_procs):
            mat_files.append(data_folder + "/"+"MAT"+ str(i)+".dat")
            tse_files.append(data_folder + "/"+"TserE" + "{:02}".format(i)+".dat")
            n_files.append(data_folder + "/"+"N_data" + str(i)+".dat")

            
        for i in range(num_procs):
            mat_data[i] = np.loadtxt(mat_files[i])
            tse_data[i] = np.loadtxt(tse_files[i])
            n_data[i] = np.loadtxt(n_files[i])

        plt.plot(tse_data[0][0:-100], tse_data[0][100:])
        plt.title("Poincare Plot of 0th Processor")
        plt.savefig("Poin_plot.png")
        shutil.move("./Poin_plot.png", save_folder+"/Poin_plot.png")
        plt.close()

 
        plt.imshow(np.vstack(tuple(x[1] for x in n_data.items())))
        plt.title("Distribution of myocytes in the tissue")
        plt.colorbar()
        plt.savefig('N_dist.png')
        shutil.move("./N_dist.png", save_folder+"/N_dist.png")
        plt.close()




        # f, arr_plots = plt.subplots(num_procs,1,figsize=(1,1*num_procs))



        # for i in range(num_procs):
        #     arr_plots[i].plot(tse_data[i])
        #     if i==0:
        #         arr_plots[0].set_title("top")




        # for ax in arr_plots.flat:
        #     ax.set(ylabel = 'Potential (nV)', xlabel = 'time (some_unit)')
        #     ax.label_outer()

        plt.plot(tse_data[0])
        plt.title("TSE for 0th Processor")
        plt.ylabel('Potential (mV)')
        plt.xlabel("number of iterations / " +
                   "Sim-time {0} (seconds)".format(simtime/1000))


        plt.savefig('TSE.png')
        plt.close()
        shutil.move("./TSE.png",save_folder+"/TSE.png")




        cols_per_pro = (int)(space/num_procs)

        number_of_frames = (int)(mat_data[0].shape[0]/cols_per_pro)
        # print(number_of_frames)
        frames = np.zeros((number_of_frames , space , spacey))

        for i in range(number_of_frames):
            
            frames[i] = np.vstack(tuple(mat_data[j][i*cols_per_pro:(i+1)*cols_per_pro, :] for j in range(num_procs)))
            # frames[i] = np.vstack((mat_data[0][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[1][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[2][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[3][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[4][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[5][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[6][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[7][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[8][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[9][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[10][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[11][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[12][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[13][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[14][i*cols_per_pro:(i+1)*cols_per_pro,:],
            #                        mat_data[15][i*cols_per_pro:(i+1)*cols_per_pro,:])) 



        fig = plt.figure()


        ims = []

        a = 2
        for i in range((int)(number_of_frames/a)):

            im = plt.imshow(frames[a*i],vmin = -55,vmax = 30, animated=True)
            # print("Done ",i)
            if i == 0:
              plt.colorbar()
              plt.xlabel("Sim-time {0} (seconds)".format(simtime/1000))
              plt.ylabel("Size of sample : {0} (cm)".format(float(sizex)*float(dx)))

            ims.append([im])



        # ani = animation.ArtistAnimation(fig, ims, interval=50, blit=True,
        #                                 repeat_delay=1000)

        intver = simtime/number_of_frames*a

        ani = animation.ArtistAnimation(fig, ims, interval=intver, blit=True,repeat=False)

        ani.save('video.mp4')
        plt.close()
        shutil.move("./video.mp4",save_folder+"/video.mp4")







