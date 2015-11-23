#include "../headers/ProdMatr.h"


typedef struct CompanionMatrix CompanionMatrix;

typedef struct CMatrix CMatrix;



//int chooseMatrix(ProductMatrices * prodMat, Eigenstruct * eigenstruct, int V);

void createCompanionMatrix(ProductMatrices * startProdMatr, CompanionMatrix ** compMatr);

void printCompanionMatrix(CompanionMatrix * compMatr);

void deleteCompanionMatrix(CompanionMatrix ** compMatr);

void createCMatrix(ProductMatrices * startProdMatr, CMatrix ** compMatr);

void printCMatrix(CMatrix * compMatr);

void deleteCMatrix(CMatrix ** compMatr);

int get_Companiondim(CompanionMatrix * comp);

double ** get_Companionmatrix(CompanionMatrix * comp);

int get_Cdim(CMatrix * c);

double ** get_CmatrixY(CMatrix * c);

double ** get_Cmatrix(CMatrix * comp);
