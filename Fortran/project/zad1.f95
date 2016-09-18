PROGRAM zadanie1
! Data: 2 czerwca 2015
! Autor: Maciej Michalec
    IMPLICIT NONE
    INTEGER, DIMENSION(:), ALLOCATABLE :: numbers
    INTEGER :: n, IOStatus

    WRITE(*,*) "Ile liczb chcesz wpisac?"
    READ(*,*, IOSTAT=IOStatus) n
    IF(IOStatus /= 0) THEN
        WRITE(*,*) "Input error"
        RETURN
    END IF 
    
    ALLOCATE(numbers (1:n))    
    WRITE(*,*) "Wpisz poszczegolne liczby, rozdzielajac je spacjami lub przecinkami"    
    READ(*,*, IOSTAT=IOStatus) numbers
    IF(IOStatus /= 0) THEN
        WRITE(*,*) "Input error"
        RETURN
    END IF     

    WRITE(*,*) "Liczby przed sortowaniem = ", numbers
    CALL sort(numbers, n)
    WRITE(*,*) "Liczby po sortowaniu = ", numbers    
    
    CONTAINS
    
        INTEGER FUNCTION  findMinimum(list, startElement, lastElement)
            IMPLICIT  NONE
            INTEGER, DIMENSION(1:), INTENT(IN) :: list
            INTEGER, INTENT(IN) :: startElement, lastElement
            INTEGER  :: minimum, pos, i

            minimum  = list(startElement)
            pos = startElement
            DO i = startElement+1, lastElement
                IF (list(i) < minimum) THEN
                    minimum = list(i)
                    pos = i
                END IF
            END DO
            findMinimum = pos
        END FUNCTION  findMinimum
        
        
        SUBROUTINE  swap(a, b)
            IMPLICIT  NONE
            INTEGER, INTENT(INOUT) :: a, b
            INTEGER :: temp

            temp = a
            a = b
            b = temp
        END SUBROUTINE  swap        

    
        SUBROUTINE sort(list, size)
            IMPLICIT NONE
            INTEGER, DIMENSION(1:), INTENT(INOUT) :: list
            INTEGER, INTENT(IN) :: size
            INTEGER :: i, pos
            
            DO i = 1, size-1
                pos = findMinimum(list, i, size)
                CALL Swap(list(i), list(pos))
            END DO
        END SUBROUTINE sort

END PROGRAM zadanie1
