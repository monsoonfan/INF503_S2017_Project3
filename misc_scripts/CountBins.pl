#!/packages/perl/5.22.0/bin/perl

################################################################################################
# CountBins.pl
#
# 4/11/17
# rmr5
# INF503, spring 2017
#
# Simple script to count the number of GI's and Tax ID's for the virus/bacteria
# sample data provided to project #3
################################################################################################
my $virus_file = "/common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta";
my $bact_file = "/common/contrib/classroom/inf503/project_3/large_test/bacterial_seqs.fasta";

open(VF,"<$virus_file") or die "Couldn't open $virus_file!\n";
open(BF,"<$bact_file") or die "Could not open $bact_file!\n";

# Count the Virus info and report
my $line_count = 0;
my %GI_V;
my %TaxID_V;

while(<VF>) {
    $line_count++;
    if (/>(\d+)-(\d+)/) {
	$GI_V{$1} = "";
	$TaxID_V{$2} = "";
    }
}

print "Done reading $line_count lines of $virus_file";
print "Unique key reports for viruses:\n";
my $GI_size = (scalar(keys %GI_V));
my $TI_size = (scalar(keys %TaxID_V));
print "   GI    = $GI_size\n";
print "   TaxID = $TI_size\n";

# Count the Bacteria info and report
$line_count = 0;
my %GI_B;
my %TaxID_B;

while(<BF>) {
    $line_count++;
    if (/>(\d+)-(\d+)/) {
	$GI_B{$1} = "";
	$TaxID_B{$2} = "";
    }
}

print "\n";
print "Done reading $line_count lines of $bact_file";
print "For bacteria:\n";
my $GI_B_size = (scalar(keys %GI_B));
my $TI_B_size = (scalar(keys %TaxID_B));
print "   GI    = $GI_B_size\n";
print "   TaxID = $TI_B_size\n";
