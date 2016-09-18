#!/usr/bin/perl
# Maciej Michalec, grupa 2
use MarksChecker qw/check_mark/;

$debug=0;


if ( @ARGV < 1 )
{
    print "Za malo argumentow. Prosze nazwe lub nazwy plikow zawierajacych oceny studentow.\n";
    exit 1;
}

@files = @ARGV;

foreach my $file (@files)
{
    print "-- Reading file: " . $file . " --\n" if($debug);
    open(FILE, $file) || cannot_read($file);    
    my %students = ();
    
    @text = <FILE>;
    foreach my $line (@text) 
    {
        @student = split(" ", $line);
        if (@student != 3)
            {
                print STDERR "# Nieprawidlowy wpis: " . $line;
                next;
            }
#        print "* Wpis\n";
        my $imie = @student[0];
        my $nazwisko = @student[1];
        my $ocena_txt = @student[2];
        my $nazwisko_imie = lc $nazwisko . "_" . lc $imie;
#        print "\tIdentyfikator: " . $nazwisko_imie . "\n";
#        print "\tImie: " . $imie . "\n";
#        print "\tNazwisko: " . $nazwisko . "\n";
        $ocena = MarksChecker::check_mark($ocena_txt);
#        print "\tOcena: " . $ocena . "\n";
                
        if ($ocena != "ERROR")
        {
            if (! exists $students{$nazwisko_imie})
            {
                $students{$nazwisko_imie} = [];
            }

#            print "\tObecne oceny: " . "@{ $students{$nazwisko_imie} }" . "\n";
#            print "\n";
            push @{ $students{$nazwisko_imie} }, $ocena;
        }
    }        
    
    my @studenci = sort keys %students;
    print "\n === $file ===\n";
    $sredniaGrupy = 0;
    for my $student (@studenci) {
        @names = split("_", $student);
        $imie = ucfirst lc @names[1];
        $nazwisko = ucfirst lc @names[0];

        my $srednia = 0;
        foreach my $ocena (@{$students{$student}})
        {
            $srednia += $ocena;
        }
        $srednia /= @{$students{$student}};
        $srednia = sprintf("%.2f", $srednia);
        print  "$nazwisko $imie [@{$students{$student}}]: $srednia \n";
        $sredniaGrupy += $srednia;
    }
    $sredniaGrupy /= @studenci;
    $sredniaGrupy = sprintf("%.2f", $sredniaGrupy);
    print "Srednia grupy: $sredniaGrupy\n";
                
    print "-- Closing file ". $file . " --\n" if($debug);
    close(FILE);
}


sub cannot_read {
    print "Cannot read file " . @_[0] . "\n";
}

