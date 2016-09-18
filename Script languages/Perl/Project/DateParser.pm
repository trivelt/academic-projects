# Maciej Michalec, grupa 2
package DateParser;
$debug=0;

sub parse_date
{
    print "Parsuje date $_[0]\n" if($debug);
    $type = ${_[1]};
    my @splittedArg = split("=", ${_[0]});
    $date = ${splittedArg[1]};
    my @splittedDate = split("-", $date);
    my $size = @splittedDate;
    if($size != 3)
    {
        die "Blad: nieprawidlowa data $type: $date\n";
    }
    my $dateObject = eval {
        Time::Piece->strptime($date, "%Y-%m-%d")
        } or die "Blad: nieprawidlowa data $type: $date \n";
    
    return $dateObject;
}

1;
