PROGRAM zadanie3
! Data: 2 czerwca 2015
! Autor: Maciej Michalec
    IMPLICIT NONE
    REAL, DIMENSION(3, 4) :: mainMatrix
    INTEGER :: i

    DO i = 1, 3
        WRITE(*,*) "Wpisz cztery wspolczynniki rownania numer ", i
        READ(*,*) mainMatrix(i, 1), mainMatrix(i, 2), mainMatrix(i, 3), mainMatrix(i, 4)
    END DO
    
    WRITE(*,*) mainMatrix

END PROGRAM zadanie3
