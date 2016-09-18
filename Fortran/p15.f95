PROGRAM p15
	IMPLICIT NONE
	REAL, DIMENSION(2:10,-30:30, 0:10) :: t, y, tplusy
	t = 2.0
	y = 3.0 ! podstawienie do wsztstkich elementow macierzy
	tplusy = t+y ! operacja dodawania wartosci odpowiednich elementow
	PRINT *, tplusy
	STOP
END PROGRAM p15
