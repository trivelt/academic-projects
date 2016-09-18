package MarksChecker;
use Scalar::Util qw(looks_like_number);

sub check_mark
{
    my $mark = @_[0];

    if ($mark =~ m/^\d*[.]?\d*$/)
    {
        return $mark;
    }
    elsif ($mark =~ m/^[+]{1}\d*$/ or $mark =~ m/^\d*[+]{1}$/)
    {
        return int($mark) + 0.25
    }
    elsif ($mark =~ m/^[-]{1}\d*$/ or $mark =~ m/^\d*[-]{1}$/)
    {
        $mark = abs(int($mark));
        return int($mark) - 0.25;
    }
    else
    {
        return "ERROR";
    }
}


1;
