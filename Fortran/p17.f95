PROGRAM p17
	IMPLICIT NONE
	REAL a,b,c,x,y,z,f1
	data c /5.0/

	f1(x,y)=a+b*x**2+c*y
	
	a=1
	b=2
	z=f1(2.,2.)
	PRINT *, 'f1(2.,2.) = ', z

	z=f1(b,b)
	PRINT *, 'f1(b,b) = ', z

	z=f2(2.,2.)
	PRINT *, 'f2(2.,2.) = ', z

	z=f2(b,b)
	PRINT *, 'f2(b,b) = ', z

	CONTAINS
	function f2(x,y)
	real x, y, f2
	f2 = a + b*x**2 + c*y
	RETURN
	END FUNCTION f2
END PROGRAM p17
