#!/bin/bash
#SBATCH --job-name=test_file_preprossing
#SBATCH --output=/scratch/rmr5/project/test_file_preprossing.log
#SBATCH --time=1:00:00
#SBATCH --workdir=/scratch/rmr5/project
#SBATCH --mem=8000

# load a module, for example
module load gcc/6.2.0

# start testing - trying to read ~36 million lines of virus data file
# there are about 2.6 G bases - we can only read 2.1G into an array
# I think the solution is vectors, but for now, let's just live with the 2.1G base limitation
# Had to read a long int instead of int/uint
date
#/home/rmr5/INF503/project/INF503_S2017_Project3/code/Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 3800100100 test.out /home/rmr5/INF503/project/INF503_S2017_Project3/data/TableSizeSmall.txt
/home/rmr5/INF503/project/INF503_S2017_Project3/code/Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 2130900900 test.out /home/rmr5/INF503/project/INF503_S2017_Project3/data/TableSizeSmall.txt
date

# RESULTS:
#Info: 28000000 lines so far...
#  2080000000 bases...
#  2090000000 bases...
#  2100000000 bases...
#  2110000000 bases...
#  2120000000 bases...
#  2130000000 bases...
#Done, processed 28793157 lines of /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta
#Total of 2130925962 bases read from 1456044 sequences
#9733195 were swapped from non-ACGT to 'N'
#Total of 2107629530 words were stored

#Sat May  6 11:44:52 MST 2017

#Final Run stats:
#VmSize: 2098336 kB
#VmPeak: 2098336 kB
#Sat May  6 11:45:14 MST 2017

