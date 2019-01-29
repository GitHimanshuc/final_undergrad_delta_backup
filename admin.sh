
#!/bin/bash 
#PBS -N tissue_run2
#PBS -l nodes=1:ppn=16:typical
#PBS -l walltime=24:00:00
#PBS -e /home/ug/15/ughima/tissue/error.log

cd /localscratch/${USER}
cp $HOME/tissue/* .
source $HOME/.bashrc

NPROCS=`wc -l < $PBS_NODEFILE`
HOSTS=`cat $PBS_NODEFILE | uniq | tr '\n' "," | sed 's|,$||'` 
mpirun -np $NPROCS --host $HOSTS ~/miniconda3/bin/python3 ./a.out > /home/ug/15/ughima/tissue/output.log


python ./just_ani_cluster16.py
