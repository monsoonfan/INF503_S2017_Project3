#!/bin/bash
#SBATCH --job-name=test_virus_reads
#SBATCH --output=/scratch/rmr5/project/test_virus_reads.log
#SBATCH --time=1:00:00
#SBATCH --workdir=/scratch/rmr5/project
#SBATCH --mem=2000

# load a module, for example
module load gcc/6.2.0

# HW1 P2.c
date
./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 5000000 test.out
date
