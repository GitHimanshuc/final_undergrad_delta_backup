#!/bin/bash 
#PBS -N tissue_run32
#PBS -l nodes=1:ppn=32:large
#PBS -l walltime=24:00:00
#PBS -e /home/ug/15/ughima/tissue/error32.log

source $HOME/.bashrc
cd $HOME/tissue
mpicc main.c -lm
rm -r /localscratch/${USER}/32procs/data/run*
rm /localscratch/${USER}/32procs/*
cd /localscratch/${USER}/32procs
cp $HOME/tissue/* .

NPROCS=`wc -l < $PBS_NODEFILE`
HOSTS=`cat $PBS_NODEFILE | uniq | tr '\n' "," | sed 's|,$||'` 
mpirun -np $NPROCS --host $HOSTS ./a.out > /home/ug/15/ughima/tissue/output32.log


python ./just_ani_cluster32.py
