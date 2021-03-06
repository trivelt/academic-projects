#!/usr/bin/perl
# Maciej Michalec, grupa 2

use Scalar::Util qw(looks_like_number);
$debug=0;

#my $numberOfArgs = $#ARGV + 1;
#if ( $numberOfArgs < 3 )
if ( @ARGV < 4 )
{
    print "Za malo argumentow. Prosze podac separator, dwie liczby i liste plikow. \n";
    exit 1;
}

$sep = $ARGV[0];
$n1 = $ARGV[1];
$n2 = $ARGV[2];
@files = @ARGV[3..@ARGV-1];
if ($debug) {
    print "# separator=" . $sep . "\n";
    print "# n1=".$n1.", n2=".$n2."\n";
    print "# Number of files " . @files . "\n";
}

if ( ! are_positive_numbers($n1, $n2))
{
    print "Dwa pierwsze argumenty musza byc liczbami dodatnimi\n";
    exit 1;
}

if($n1 > $n2)
{
($n1, $n2) = ($n2, $n1);
}

foreach my $file (@files)
{
    print "-- Reading file: " . $file . " --\n" if($debug);
    open(FILE, $file) || cannot_read($file);
    @text = <FILE>;
    foreach my $line (@text) 
    {
        @words = split($sep, $line);
        foreach my $word (@words[$n1-1..$n2-1])
        {
            print trim($word) . " "
        }
        print "\n";
        #print "# " . $line if($debug);
    }
    print "-- Closing file ". $file . " --\n" if($debug);
    close(FILE);
}


exit 0;


sub cannot_read {
    print "# Cannot read file " . @_[0] . "\n" if($debug);
}

sub are_positive_numbers {
    my $n1 = @_[0];
    my $n2 = @_[1];
    if ( !looks_like_number($n1) || !looks_like_number($n2))
    {
        return 0;
    }
    elsif ($n1 < 0 || $n2 < 0)
    {
        return 0;
    }
    return 1;
}

sub trim {
    my $s = shift;
    $s =~ s/^\s+|\s+$//g;
    return $s
};
