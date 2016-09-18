#!/usr/bin/perl
# Maciej Michalec, grupa 2
use File::stat;

$debug=1;

if ( @ARGV < 1 )
{
    print "Za malo argumentow. Prosze nazwe lub nazwy plikow oraz opcjonalnie inne parametry. \n";
    exit 1;
}

$realNumbersParameter = 0;
$intNumbersParameter = 0;
@files = ();
@linesCounters = ();
@wordsCounters = ();
@bytesCounters = ();

foreach my $arg (@ARGV)
{
    if($arg eq "-l")
    {
        $intNumbersParameter = 1;
    }
    elsif ($arg eq "-i")
    {
        $realNumbersParameter = 1;
    }
    else
    {
        @files = (@files, $arg);
    }
}

foreach my $file (@files)
{
    print "-- Reading file: " . $file . " --\n" if($debug);
    open(FILE, $file) || cannot_read($file);
    
    my $linesCounter = 0;
    my $wordsCounter = 0;    
    my $bytesCounter = stat($file)->size;    
    @text = <FILE>;
    foreach my $line (@text) 
    {
        $linesCounter++;
        @words = split(" ", $line);
        $wordsCounter += @words;
    }
    @linesCounters = (@linesCounters, $lineCounter);
    @wordsCounters = (@wordsCounters, $wordsCounter);
    @bytesCounters = (@bytesCounters, $bytesCounter);        
    #push(@linesCounters, $linesCounter);
    #push(@wordsCounters, $wordsCounter);
    #push(@bytesCounters, $bytesCounter);
    print "  " . $linesCounter . "  " . $wordsCounter . " " . $bytesCounter . " " . $file . "\n" if ($debug);   
            
    print "-- Closing file ". $file . " --\n" if($debug);
    close(FILE);
}


if ($intNumbersParameter == 1)
{
    # wypisz liczniki liczb calkowitych
}

if ($realNumbersParameter == 1)
{
    # wypisz liczniki liczb rzeczywistych
}

if ($intNumbersParameter == 0 and $realNumbersParamter == 0)
{
    my $totalLines = 0;
    my $totalWords = 0;
    my $totalBytes = 0;
    my $i = 0;
    foreach $file (@files)
    {
        print "  " . $linesCounters[i] . "  " . $wordsCounters[i] . " " . $bytesCounters[i+1] . " " . $file . "\n";    

        $totalLines += $linesCounters[i];
        $totalWords += $wordsCounters[i];
        $totalBytes += $bytesCounters[i+1];
        $i++;
    }
        print "  " . $totalLines . "  " . $totalWords . " " . $totalBytes . " razem\n";        
    # wypisz podstawowe liczniki
}

exit 0;

sub cannot_read {
    print "Cannot read file " . @_[0] . "\n";
}
