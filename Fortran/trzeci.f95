PROGRAM trzeci
OPEN(UNIT=66, FILE="data_1", STATUS="OLD", ACTION="WRITE", POSITION="APPEND")
! plik o nazwie data_1 ma status OLD - nalezy go utworzyc przed uruchomieniem programu
WRITE(UNIT=66, FMT=*) "witaj"
STOP
END PROGRAM trzeci