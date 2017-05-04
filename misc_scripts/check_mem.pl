#!/usr/bin/perl

######################################################################################################
# Usage:
# 
# Below will tell the script to watch the ./Project3 executable's memory usage every 15 minutes
#
# > squeue -u <user_name>  (find the compute node your job is running on, in this case, it's cn19)
#             JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
#           5241204       all test_vir     rmr5  R    4:26:39      1 cn19
#
# > ssh cn19 (change this based on the node your job is running on)
# > perl check_mem.pl Project3 15m
# 
# Output should loook like this:
# ------------------------------
# [rmr5@cn19 /scratch/rmr5 ]$ perl check_mem.pl Project3 15m
# Getting process ID for Project3...
# Found 88607
# VmSize: 33777520 kB
# VmPeak: 33777520 kB
# Thu May  4 10:34:16 MST 2017
#
######################################################################################################

# Arguments
my $job_tag = $ARGV[0];
my $timeout = $ARGV[1];

# Variables
my $pID;
my $uID;
my $run = 1;
my $vmsize;
my $vmpeak;

# Get the process ID 
print "Getting process ID for $job_tag...\n";
my @lines = `ps -ef | grep $job_tag`;

foreach my $line (@lines) {
    next if ($line =~ m/perl/);
    next if ($line =~ m/grep/);
    if ($line =~ m/^(\S+)\s+(\d+)\s+/) {
	$uID = $1;
	$pID = $2;
    } else {
	die "Could not find pID within $line";
    }
}

print "Found $pID for user $uID\n";

# Infinite loop, will run until script is killed
while ($run) {
    # VmSize
    my $vms = `grep VmSize /proc/$pID/status`;
    if ($vms =~ m/^VmSize\:\s+(\d+\s+\S+)\s*$/) {
	$vmsize = $1;
    } elsif ($vms =~ m/No such file/) {
	$run = 0;
	print "Final Run stats:\n";
	&output();
    } else {
	print "ERROR: unknown error occurred, no pID or VmSize detected!\n";
	&output();
    }
    
    # VmPeak
    my $vmp = `grep VmPeak /proc/$pID/status`;
    if ($vmp =~ m/^VmPeak\:\s+(\d+\s+\S+)\s*$/) {
	$vmpeak = $1;
    } elsif ($vms =~ m/No such file/) {
	$run = 0;
	print "Final Run stats:\n";
	&output();
    } else {
	print "ERROR: unknown error occurred, no pID or VmPeak detected!\n";
	&output();
    }
    
    # Could do an occasional pull for this, like 1 per second
    #my $input = <STDIN>;
    #print $input;
    &output();
    `sleep $timeout`;
}

sub output {
    print "VmSize: $vmsize\n";
    print "VmPeak: $vmpeak\n";
    print `date`;
}
