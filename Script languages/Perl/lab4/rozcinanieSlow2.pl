#!/usr/bin/perl
# Maciej Michalec, grupa 2
use Scalar::Util qw(looks_like_number);
$debug=0;

#my $numberOfArgs = $#ARGV + 1;
#if ( $numberOfArgs < 3 )
if ( @ARGV < 3 )
{
    print "Za malo argumentow. Prosze podac dwie liczby i liste plikow. \n";
    exit 1;
}

$n1 = $ARGV[0];
$n2 = $ARGV[1];
@files = @ARGV[2..@ARGV-1];
if ($debug) {
    print "# n1=".$n1.", n2=".$n2."\n";
    print "# Number of files " . @files . "\n";
}

if ( ! are_positive_numbers($n1, $n2))
{
    print "Dwa pierwsze argumenty musza byc liczbami dodatnimi\n";
    exit 1;
}


foreach my $file (@files)
{
    print "-- Reading file: " . $file . " --\n" if($debug);
    open(FILE, $file) || cannot_read($file);
    @text = <FILE>;
    $counter=0;
    foreach my $line (@text) 
    {
        $counter += 1;
        @words = split(" ", $line);
        $word_1 = @words[$n1-1];
        $word_2 = @words[$n2-1];
        if ( @words < $n1 or @words < $n2) 
        {
            print STDERR $file . ":" . $counter . ": blad zakresu\n";
        }
        else
        {
            print $word_1 . " " . $word_2 . "\n";
        }
        print "# " . $line if($debug);
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

