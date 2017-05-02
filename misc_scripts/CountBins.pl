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
#my $virus_file = "../data/virus_first_100";
my $bact_file = "/common/contrib/classroom/inf503/project_3/large_test/bacterial_seqs.fasta";
#my $bact_file = "../data/virus_first_100";
my $log_file = "CountBins.log";

open(VF,"<$virus_file") or die "Couldn't open $virus_file!\n";
open(BF,"<$bact_file") or die "Could not open $bact_file!\n";
open(LOG,">$log_file") or die "Could not open $log_file\n";

# Count the Virus info and report
printBoth("Reading $virus_file...\n", LOG);
my $line_count = 0;
my $gi_count = 0;
my $taxID_word_count = 0;
my $gi_word_count = 0;
my %GI_V;
my %TaxID_V;
my $tax_id = 0;
my $DEBUG = 0;

while(<VF>) {
    $line_count++;
    if (/>(\d+)-(\d+)/) {
	$GI_V{$1} = "";
	$tax_id = $2;
	$gi_count++;
	$TaxID_V{$tax_id}{num_genomes} = $TaxID_V{$tax_id}{num_genomes} + 1;

	print "DBG: storing tax_id: $tax_id, has $TaxID_V{$tax_id}{num_genomes} genomes\n" if ($DEBUG);
	print "DBG: num_chars so far: $TaxID_V{$tax_id}{char_count}\n" if ($DEBUG);
    }
    if (/^([A-Y]*)$/) {
	my $num_chars = length($1);
	$TaxID_V{$tax_id}{char_count} = $TaxID_V{$tax_id}{char_count} + $num_chars;
	print "DBG: tax_id: $tax_id, num_chars: $num_chars, char_count: $TaxID_V{$tax_id}{char_count}\n" if ($DEBUG);
    }
}

printBoth("Done reading $line_count lines of $virus_file, found $gi_count genomes\n", LOG);
printBoth("Unique key reports for viruses:\n", LOG);
my $GI_size = (scalar(keys %GI_V));
my $TI_size = (scalar(keys %TaxID_V));
printBoth("   GI    = $GI_size\n", LOG);
printBoth("   TaxID = $TI_size\n", LOG);

# Report the number of words per TaxID
foreach my $tkey (keys %TaxID_V) {
    $taxID_word_count = $TaxID_V{$tkey}{char_count} - ($TaxID_V{$tkey}{num_genomes} * 16);
    print "     $tkey($TaxID_V{$tkey}{num_genomes}): $taxID_word_count\n";
}    

# Count the Bacteria info and report
printBoth("Reading $bact_file...\n", LOG);
$line_count = 0;
$gi_count = 0;
my %GI_B;
my %TaxID_B;

while(<BF>) {
    $line_count++;
    if (/>(\d+)-(\d+)/) {
	$GI_B{$1} = "";
	$tax_id = $2;
	$gi_count++;
	$TaxID_B{$tax_id}{num_genomes} = $TaxID_B{$tax_id}{num_genomes} + 1;

	print "DBG: storing tax_id: $tax_id, has $TaxID_B{$tax_id}{num_genomes} genomes\n" if ($DEBUG);
	print "DBG: num_chars so far: $TaxID_B{$tax_id}{char_count}\n" if ($DEBUG);
    }
    if (/^([A-Y]*)$/) {
	my $num_chars = length($1);
	$TaxID_B{$tax_id}{char_count} = $TaxID_B{$tax_id}{char_count} + $num_chars;
	print "DBG: tax_id: $tax_id, num_chars: $num_chars, char_count: $TaxID_B{$tax_id}{char_count}\n" if ($DEBUG);
    }
}

printBoth("\n", LOG);
printBoth("Done reading $line_count lines of $bact_file, found $gi_count genomes\n", LOG);
printBoth("For bacteria:\n", LOG);
my $GI_B_size = (scalar(keys %GI_B));
my $TI_B_size = (scalar(keys %TaxID_B));
printBoth("   GI    = $GI_B_size\n", LOG);
printBoth("   TaxID = $TI_B_size\n", LOG);

# Report the number of GI's per TaxID
foreach my $tkey (keys %TaxID_B) {
    $taxID_word_count = $TaxID_B{$tkey}{char_count} - ($TaxID_B{$tkey}{num_genomes} * 16);
    print "     $tkey($TaxID_B{$tkey}{num_genomes}): $taxID_word_count\n";
}    

close (VF, BF, LOG);

sub printBoth {
    my $text = shift @_;
    my $FH = shift @_;

    print STDOUT $text;
    print $FH $text;
}
