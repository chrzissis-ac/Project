#include "../headers/ProdMatr.h"

typedef struct CompanionMatrix CompanionMatrix;

typedef struct CMatrix CMatrix;

typedef struct Eigenstruct Eigenstruct;

void createEigenstruct(Eigenstruct ** eigenstruct);

void deleteEigenstruct(Eigenstruct ** eigenstruct);

void printEigenstruct(Eigenstruct * eigenstruct);

int chooseMatrix(ProductMatrices * prodMat, Eigenstruct * eigenstruct, int V);

void createCompanionMatrix(ProductMatrices * startProdMatr, CompanionMatrix ** compMatr);

void printCompanionMatrix(CompanionMatrix * compMatr);

void deleteCompanionMatrix(CompanionMatrix ** compMatr);

void createCMatrix(ProductMatrices * startProdMatr, CMatrix ** compMatr);

void printCMatrix(CMatrix * compMatr);

void deleteCMatrix(CMatrix ** compMatr);

void solver(Eigenstruct * eigen);
