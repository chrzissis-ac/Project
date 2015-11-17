GCCC= gcc -c
GCCO= gcc -o
RMVF= rm -f

EXEC1= prog
OBJS1= Sylvester.o SimplePoly.o ComplexPoly.o Routines.o Vector.o ProdMatr.o CompanionMatrix.o main.o

all: cl final1
	$(RMVF) $(OBJS1)

cl:
	clear;clear;

final1: $(OBJS1)
	$(GCCO) $(EXEC1) $(OBJS1) -llapacke -lblas

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

CompanionMatrix.o: ./functions/CompanionMatrix.c
	$(GCCC) ./functions/CompanionMatrix.c

main.o: ./main/main.c
	$(GCCC) ./main/main.c

clean: cl
	$(RMVF) $(OBJS1) $(EXEC1) 
