# Need to 'module load gcc/6.2.0'
build:
	g++ -o Project3 stdafx.cpp FileReader.cpp HashMap.cpp Word.cpp Project3Main.cpp

build_and_run: build
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 5000 test.out ../data/TableSize.txt

run.%:
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta $* test.out ../data/TableSize.txt
