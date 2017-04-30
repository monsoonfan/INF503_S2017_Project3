#!/bin/bash
#SBATCH --job-name=INF503project3_JC
# the name of your job
#SBATCH --output=/home/jc3464/INF503/INF503_S2017_Project3/docs/TableSize.txt
#SBATCH --time=0-6:00:00
#SBATCH --workdir=/home/jc3464/INF503/homework7/
#SBATCH --mem=10000


module load perl

 srun perl /home/jc3464/INF503/INF503_S2017_Project3/misc_scripts/CountBins.pl

