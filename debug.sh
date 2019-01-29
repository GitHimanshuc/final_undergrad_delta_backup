#!/bin/bash 
#PBS -N tissue_debug
#PBS -l nodes=1:ppn=16:debug
#PBS -l walltime=2:00:00
#PBS -e /home/ug/15/ughima/tissue/errordebug.log


source $HOME/.bashrc
cd $HOME/tissue
mpicc main.c -lm
rm -r /localscratch/${USER}/debug/data/run*
cd /localscratch/${USER}/debug
rm /localscratch/${USER}/debug/*
cp $HOME/tissue/* .

NPROCS=`wc -l < $PBS_NODEFILE`
HOSTS=`cat $PBS_NODEFILE | uniq | tr '\n' "," | sed 's|,$||'` 
mpirun -np $NPROCS --host $HOSTS ./a.out > /home/ug/15/ughima/tissue/outputdebug.log


echo calling python
python ./just_ani_cluster16.py
echo called python  

