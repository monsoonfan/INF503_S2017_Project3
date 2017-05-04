#!/bin/bash
#SBATCH --job-name=test_virus_reads_jc
#SBATCH --output=/scratch/jc3464/test_virus_reads.txt
#SBATCH --time=24:00:00
#SBATCH --workdir=/home/jc3464/INF503/IN503_S2017_Project3/misc_scripts
#SBATCH --mem=60000

# load a module, for example
module load gcc/6.2.0

# start testing
date
/home/rmr5/INF503/project/INF503_S2017_Project3/code/Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 9000000000 test.out /home/rmr5/INF503/project/INF503_S2017_Project3/data/TableSizeViruses.txt
date
