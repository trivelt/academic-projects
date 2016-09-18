#!/usr/bin/perl
# Maciej Michalec, grupa 2
use File::Find

$debug = 0;

%dirList = ();
%patternList = ();

@currentDirList = (); # lista katalogow dla aktualnie definiowanego wzorca
@currentPatternList = (); # lista aktualnie definiowanych wzorcow
$expectedDirname = 0;
$expectedPattern = 0;
$expectedDFlag = 1;
$currentPatternSet = 0;
$patternsCounter = 0;
@files = ();
foreach my $arg (@ARGV)
{
    if($arg eq "-d")
    {
        if($currentPatternSet == 1)
        {
            print "Podano kolejny raz flage -d. Dodaje poprzedni wzorzec dla i=" . $patternsCounter . "\n" if($debug);
            @dirList{$patternsCounter} = [];
            @patternList{$patternsCounter} = [];
            foreach my $dir (@currentDirList)
            {
                push @{ $dirList{$patternsCounter} }, $dir;
            }
            foreach my $dir (@currentPatternList)
            {
                push @{ $patternList{$patternsCounter} }, $dir;
            }
            $patternsCounter = $patternsCounter + 1;

            @currentDirList = ();
            @currentPatternList = ();
        }
        else
        {
            print "Podano flage -d\n" if($debug);   
        }
        $expectedDirname = 1;
        $expectedPattern = 0;
        $expectedDFlag = 0;
        $currentPatternSet = 0;
    }
    else
    {
        if($expectedDirname == 1)
        {
            print "Podano nazwe kartoteki: " . $arg . "\n" if($debug);
            push @currentDirList, $arg;    
            $expectedDirname = 0;
            $expectedPattern = 1;
            $expectedDFlag = 1;         
        }
        elsif($expectedPattern == 1)
        {
            print "Podano wzorzec: " . $arg . "\n" if($debug);
            push @currentPatternList, $arg;
            $currentPatternSet = 1;
            $expectedPattern = 1;
            $expectedDFlag = 1;  
        }
        elsif($expectedDFlag == 1 and $patternsList == 0)
        {
            break;
        }
    }
}

if($currentPatternSet == 1)
{
            @dirList{$patternsCounter} = [];
            @patternList{$patternsCounter} = [];
            foreach my $dir (@currentDirList)
            {
                push @{ $dirList{$patternsCounter} }, $dir;
            }
            foreach my $dir (@currentPatternList)
            {
                push @{ $patternList{$patternsCounter} }, $dir;
            }
    print "Koniec petli for, dodaje wzorzec dla i=" . $patternsCounter . "\n" if($debug);
}

print "Patterns counter: " . $patternsCounter . "\n" if($debug);

print "\n\n" if($debug);

$size = keys %patternList;
print "Size: " . $size . "\n" if($debug);
for (my $i=0; $i < $size; $i++)
{
    $totalCounter = 0;
    print "= Wzorce: ";
    foreach my $pattern(@{$patternList{$i}})
    {
        print $pattern . " ";
    }
    print "=\n";
    
    foreach my $dir(@{$dirList{$i}})
    {
        $localCounter = 0;
        #@files = <$dir*>;
        @files=();
        
        find(\&add_files, $dir);
        foreach $file (@files)
        {
            print $file . "\n" if($debug);
            open(FILE, $file) || cannot_read($file);    
            
            @text = <FILE>;
            foreach my $line(@text)
            {
                foreach my $pattern(@{$patternList{$i}})
                {
                    if($line =~ /$pattern/)
                    {
                        $localCounter += 1;
                    }
                }
            }
        }
        print "Poszukuje w katalogu " . $dir . "\n" if($debug);
        print "\t* " . $dir . ": " . $localCounter . "\n";
        $totalCounter += $localCounter;
    }
    print "\n" if($debug);
    print "\t* Lacznie: " . $totalCounter . "\n";

    
}

sub cannot_read {
    print "Cannot read file " . @_[0] . "\n" if($debug);
}


sub add_files
{
    push @files, $File::Find::name;
}
