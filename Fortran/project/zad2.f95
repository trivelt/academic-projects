PROGRAM zadanie2
! Data: 2 czerwca 2015
! Autor: Maciej Michalec
    IMPLICIT NONE
    INTEGER, PARAMETER :: rdp=SELECTED_REAL_KIND(15)
    INTEGER, PARAMETER :: idp=SELECTED_INT_KIND(15)
    REAL(KIND=rdp), PARAMETER :: pi=3.14159265358979323846264338327950288_rdp    
    INTEGER, PARAMETER :: n = 10000000
    REAL(KIND=rdp) :: a=0, b=pi, result, dx, rand
    INTEGER :: i

    CALL init_random_seed()
    dx = b - a
    DO i = 1, n
        CALL RANDOM_NUMBER(rand)
        result = result + SIN(a + (rand*dx) )
    END DO
    result = dx * result / n
    WRITE(*,*) "Calka z sin(x) w przedziale [0, PI] = ", result
    
    
    CONTAINS
        SUBROUTINE init_random_seed()
                INTEGER :: i, n, clock
                INTEGER, DIMENSION(:), ALLOCATABLE :: seed
                
                CALL RANDOM_SEED(SIZE = n)
                ALLOCATE(seed(n))
                
                CALL SYSTEM_CLOCK(COUNT=clock)
                
                seed = clock + 37 !* (/ (i-1, i = 1, n) / )
                CALL RANDOM_SEED(PUT = seed)
                
                DEALLOCATE(seed)
        END SUBROUTINE
END PROGRAM zadanie2
