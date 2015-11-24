#include "../headers/CompanionMatrix.h"
typedef struct Gen_eigensol Gen_eigensol;

typedef struct eigensol eigensol;

typedef struct Gen_sol Gen_sol;

typedef struct sol sol;

typedef struct Eigenstruct Eigenstruct;

void createEigenstruct(Eigenstruct ** eigenstruct);

void deleteEigenstruct(Eigenstruct ** eigenstruct);

void printEigenstruct(Eigenstruct * eigenstruct);

void solver(Eigenstruct * eigen, Gen_eigensol ** solution);

void createSolution(Gen_eigensol ** solution, int dim, double * realSolution, double * imaginarySolution,double * betaSolution, double * eigenVector,char c);

void destroyGen_eigensol(Gen_eigensol ** solution);

void printGen_eigensol(Gen_eigensol * solution);

int chooseMatrix(ProductMatrices * prodMat, Eigenstruct * eigenstruct, int V);

void createGen_sol(Gen_eigensol * eigensol,Gen_sol ** GSol);
