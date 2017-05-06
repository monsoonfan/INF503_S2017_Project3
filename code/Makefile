# Need to 'module load gcc/6.2.0'
build:
	g++ -o Project3 stdafx.cpp FileReader.cpp HashMap.cpp Word.cpp Project3Main.cpp

build_and_run: build
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta 5000 test.out ../data/TableSizeViruses.txt ../data/TableSizeQueries.txt

run_v.%:
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta $* test.out ../data/TableSizeViruses.txt ../data/TableSizeQueries.txt

run_b.%:
	./Project3 /common/contrib/classroom/inf503/project_3/large_test/bacterial_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta $* test.out ../data/TableSizeViruses.txt ../data/TableSizeQueries.txt

br.%: build
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta $* test.out ../data/TableSizeViruses.txt ../data/TableSizeQueries.txt

test.%:
	./Project3 /common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta /common/contrib/classroom/inf503/project_3/small_test/test_reads.fasta $* test.out ../data/TableSizeSmall.txt ../data/TableSizeQueries.txt
