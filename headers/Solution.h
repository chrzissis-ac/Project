#include "../headers/CompanionMatrix.h"
#include "../headers/ComplexPoly.h"

typedef struct Gen_eigensol Gen_eigensol;

typedef struct eigensol eigensol;

typedef struct Gen_sol Gen_sol;

typedef struct sol sol;

typedef struct Eigenstruct Eigenstruct;

void deleteEigenstruct(Eigenstruct ** eigenstruct);

void printEigenstruct(Eigenstruct * eigenstruct);

void solver(Eigenstruct * eigen, Gen_eigensol ** solution, Gen_sol ** GSol);

void destroyGen_eigensol(Gen_eigensol ** solution);

void printGen_eigensol(Gen_eigensol * solution);

int chooseMatrix(ProductMatrices * prodMat, Eigenstruct ** eigenstruct, int V);

void deleteGen_sol(Gen_sol ** GSol);

void printGen_sol(Gen_sol * GSol,Polyonym2 * poly1,Polyonym2 * poly2,int imag_flag);

void changevarback(Gen_sol ** GSol, int t[4]);
