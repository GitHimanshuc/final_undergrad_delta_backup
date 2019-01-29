#!/bin/bash 
#PBS -N tissue_run64
#PBS -l nodes=4:ppn=16:regular
#PBS -l walltime=24:00:00
#PBS -e /home/ug/15/ughima/tissue/error64.log

source $HOME/.bashrc
cd $HOME/tissue
mpicc main.c -lm
rm -r /localscratch/${USER}/64procs/data/run*
cd /localscratch/${USER}/64procs
rm /localscratch/${USER}/64procs/*
cp $HOME/tissue/* .
#cp $HOME/tissue/a.out /localscratch/ughima

NPROCS=`wc -l < $PBS_NODEFILE`
HOSTS=`cat $PBS_NODEFILE | uniq | tr '\n' "," | sed 's|,$||'` 
mpirun -np $NPROCS --host $HOSTS $HOME/tissue/a.out > /home/ug/15/ughima/tissue/output64.log


python ./just_ani_cluster64.py
