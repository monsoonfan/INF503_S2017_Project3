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
#
# Usage:
# prompt> module load perl
# prompt> perl CountBins.pl
################################################################################################
my $virus_file = "/common/contrib/classroom/inf503/project_3/small_test/viral_seqs.fasta";
my $bact_file = "/common/contrib/classroom/inf503/project_3/large_test/bacterial_seqs.fasta";
my $log_file = "CountBins.log";

open(VF,"<$virus_file") or die "Couldn't open $virus_file!\n";
open(BF,"<$bact_file") or die "Could not open $bact_file!\n";
open(LOG,">$log_file") or die "Could not open $log_file\n";

# Count the Virus info and report
printBoth("Reading $virus_file...\n", LOG);
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

printBoth("Done reading $line_count lines of $virus_file\n", LOG);
printBoth("Unique key reports for viruses:\n", LOG);
my $GI_size = (scalar(keys %GI_V));
my $TI_size = (scalar(keys %TaxID_V));
printBoth("   GI    = $GI_size\n", LOG);
printBoth("   TaxID = $TI_size\n", LOG);

# Count the Bacteria info and report
printBoth("Reading $bact_file...\n", LOG);
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

printBoth("\n", LOG);
printBoth("Done reading $line_count lines of $bact_file\n", LOG);
printBoth("For bacteria:\n", LOG);
my $GI_B_size = (scalar(keys %GI_B));
my $TI_B_size = (scalar(keys %TaxID_B));
printBoth("   GI    = $GI_B_size\n", LOG);
printBoth("   TaxID = $TI_B_size\n", LOG);

close (VF, BF, LOG);

sub printBoth {
    my $text = shift @_;
    my $FH = shift @_;

    print STDOUT $text;
    print $FH $text;
}
