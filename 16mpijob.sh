#!/bin/bash 
#PBS -N tissue_run16
#PBS -l nodes=1:ppn=16:typical
#PBS -l walltime=24:00:00
#PBS -e /home/ug/15/ughima/tissue/error16.log

source $HOME/.bashrc
cd $HOME/tissue
mpicc main.c -lm
rm -r /localscratch/${USER}/16procs/data/run*
cd /localscratch/${USER}/16procs
rm /localscratch/${USER}/16procs/*
cp $HOME/tissue/* .

NPROCS=`wc -l < $PBS_NODEFILE`
HOSTS=`cat $PBS_NODEFILE | uniq | tr '\n' "," | sed 's|,$||'` 
mpirun -np $NPROCS --host $HOSTS ./a.out > /home/ug/15/ughima/tissue/output16.log


python ./just_ani_cluster16.py

