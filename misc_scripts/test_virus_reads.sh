#!/bin/bash
#SBATCH --job-name=test_virus_reads
#SBATCH --output=/scratch/rmr5/project/test_virus_reads.log
#SBATCH --time=24:00:00
#SBATCH --workdir=/scratch/rmr5/project
#SBATCH --mem=600000

# load a module, for example
module load gcc/6.2.0

# HW1 P2.c
date
/home/rmr5/INF503/project/INF503_S2017_Project3/code/Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 9000000000 test.out /home/rmr5/INF503/project/INF503_S2017_Project3/data/TableSizeViruses.txt
date
