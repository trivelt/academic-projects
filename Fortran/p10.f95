PROGRAM p10
	IMPLICIT NONE
	INTEGER :: i,j,p,q,r,x,n,m
	
	PRINT *, "start=1, stop=10, increment=1"
	DO i=1,10
	PRINT *, i
	END DO
	PRINT *

	PRINT *, "start=20, stop=50, increment=5"
	DO j=20,50,5
	PRINT *, j
	END DO
	PRINT *

	PRINT *, "start=7, stop=19, increment=4"
	DO p=7,19,4
	PRINT *, p
	END DO
	PRINT *

	PRINT *, "start=4, stop=5, increment=6"
	DO q=4,5,6
	PRINT *, q
	END DO
	PRINT *

STOP
END PROGRAM p10
