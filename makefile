GCCC= gcc -c
GCCO= gcc -o
RMVF= rm -f

EXEC1= prog
OBJS1= Sylvester.o SimplePoly.o ComplexPoly.o Routines.o Vector.o ProdMatr.o CompanionMatrix.o Solution.o main.o
testOBJS= testCompanionMatrix.o testComplexPoly.o testProdMatr.o testSimplePoly.o testSolution.o testSylvester.o testVector.o
testEXEC= testComplexPoly testSimplePoly testSylvester testProdMatr testVector testCompanionMatrix testSolution

all: cl final1
	$(RMVF) $(OBJS1)

clean: cl
	$(RMVF) $(OBJS1) $(testOBJS) $(EXEC1) $(testEXEC)

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

Solution.o: ./functions/Solution.c
	$(GCCC) ./functions/Solution.c

main.o: ./main/main.c
	$(GCCC) ./main/main.c





test: cl test_final
	$(RMVF) $(OBJS1) $(testOBJS) 

test_final: $(testOBJS) $(OBJS1)
	$(GCCO) testComplexPoly testComplexPoly.o ComplexPoly.o SimplePoly.o -lcunit;
	$(GCCO) testSimplePoly testSimplePoly.o ComplexPoly.o SimplePoly.o -lcunit;
	$(GCCO) testSylvester testSylvester.o Sylvester.o ComplexPoly.o SimplePoly.o Vector.o -lcunit;
	$(GCCO) testProdMatr testProdMatr.o ProdMatr.o SimplePoly.o ComplexPoly.o Routines.o -llapacke -lblas -lcunit;
	$(GCCO) testVector testVector.o Vector.o SimplePoly.o ComplexPoly.o -lcunit;
	$(GCCO) testCompanionMatrix testCompanionMatrix.o CompanionMatrix.o Routines.o ProdMatr.o SimplePoly.o ComplexPoly.o -llapacke -lblas -lcunit;
	$(GCCO) testSolution testSolution.o Solution.o Vector.o CompanionMatrix.o ProdMatr.o SimplePoly.o ComplexPoly.o Routines.o -llapacke -lblas -lcunit;
	
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
