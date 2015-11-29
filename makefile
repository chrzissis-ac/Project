GCCC= gcc -c
GCCO= gcc -o
RMVF= rm -f

EXEC1= prog
OBJS1= Sylvester.o SimplePoly.o ComplexPoly.o Routines.o Vector.o ProdMatr.o CompanionMatrix.o Solution.o main.o
testOBJS= testCompanionMatrix.o testComplexPoly.o testProdMatr.o testSimplePoly.o testSolution.o testSylvester.o testVector.o

clean: cl
	$(RMVF) $(OBJS1) $(EXEC1) 

cl:
	clear;clear;


all: cl final1
	$(RMVF) $(OBJS1)

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

Solution.o: ./functions/Solution.c
	$(GCCC) ./functions/Solution.c

main.o: ./main/main.c
	$(GCCC) ./main/main.c





test: cl test_final
	$(RMVF) $(OBJS1) $(testOBJS) 

test_final: $(testOBJS) $(OBJS1)
	$(GCCO) testComplexPoly testComplexPoly.o ComplexPoly.o;
	$(GCCO) testSimplePoly testSimplePoly.o SimplePoly.o;
	$(GCCO) testSylvester testSylvester.o Sylvester.o;
	$(GCCO) testProdMatr testProdMatr.o ProdMatr.o -llapacke -lblas;
	$(GCCO) testVector testVector.o Vector.o;
	$(GCCO) testCompanionMatrix testCompanionMatrix.o CompanionMatrix.o -llapacke -lblas;
	$(GCCO) testSolution testSolution.o Solution.o -llapacke -lblas;
	
testComplexPoly.o: ./test/testComplexPoly.c
	$(GCCC) ./test/testComplexPoly.c
	
testSimplePoly.o: ./test/testSimplePoly.c
	$(GCCC) ./test/testSimplePoly.c

testSylvester.o: ./test/testSylvester.c
	$(GCCC) ./test/testSylvester.c

testProdMatr.o: ./test/testProdMatr.c
	$(GCCC) ./test/testProdMatr.c

testVector.o: ./test/testVector.c
	$(GCCC) ./test/testVector.c

testCompanionMatrix.o: ./test/testCompanionMatrix.c
	$(GCCC) ./test/testCompanionMatrix.c

testSolution.o: ./test/testSolution.c
	$(GCCC) ./test/testSolution.c
