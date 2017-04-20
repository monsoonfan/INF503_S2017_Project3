# Need to 'module load gcc/6.2.0'
build:
	g++ -o Project3 FileReader.cpp Project3Main.cpp

build_and_run: build
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 5000 test.out

run.%:
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta $* test.out
