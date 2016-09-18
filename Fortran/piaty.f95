PROGRAM p5
    IMPLICIT NONE
    INTEGER :: i,k
    DO I=1, 10
	DO k=1,12,5 ! petla od 1 do 12 z krokiem 5
	WRITE(UNIT=*, FMT=*) i,k
	END DO
    END DO
    STOP
    END PROGRAM
