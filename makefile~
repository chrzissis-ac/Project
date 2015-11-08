GCCC= gcc -c
GCCO= gcc -o
RMVF= rm -f

EXEC1= prog
OBJS1= Sylvester.o SimplePoly.o ComplexPoly.o Routines.o Vector.o ProdMatr.o main.o

all: final1
	$(RMVF) $(OBJS1)
final1: $(OBJS1)
	$(GCCO) $(EXEC1) $(OBJS1)

Routines.o: ./functions/Routines.c
	$(GCCC) ./functions/Routines.c
	
ComplexPoly.o: ./functions/ComplexPoly.c
	$(GCCC) ./functions/ComplexPoly.c
	
SimplePoly.o: ./functions/SimplePoly.c
	$(GCCC) ./functions/SimplePoly.c

Sylvester.o: ./functions/Sylvester.c
	$(GCCC) ./functions/Sylvester.c

ProdMatr.o: ./functions/ProdMatr.c
	$(GCCC) ./functions/ProdMatr.c

Vector.o: ./functions/Vector.c
	$(GCCC) ./functions/Vector.c

main.o: ./main/main.c
	$(GCCC) ./main/main.c
clean:
	$(RMVF) $(OBJS1) $(EXEC1) 
