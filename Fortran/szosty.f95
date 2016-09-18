PROGRAM szosty
IMPLICIT NONE

CHARACTER(LEN=10) :: date
CHARACTER(LEN=2) :: month

WRITE(UNIT=*, FMT=*) "napisz date w formacie yyyy-mm-dd"
READ(UNIT=*, FMT=*) date
month = date(6:7) ! podstawa do zmiennej month 6. i 7. znak ze zmiennej date
WRITE(UNIT=*, FMT="(A10)") month

SELECT CASE(month)
CASE("03":"05")
WRITE(UNIT=*, FMT="(A12)") "to wiosna"
CASE("06", "07", "08")
WRITE(UNIT=*, FMT="(A12)") "to lato"
CASE DEFAULT
WRITE(UNIT=*, FMT="(A25)") "to ani wiosna ani lato"
END SELECT

STOP
END PROGRAM szosty