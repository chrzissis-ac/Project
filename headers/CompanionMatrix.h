#include "../headers/ProdMatr.h"

typedef struct CompanionMatrix CompanionMatrix;

typedef struct CMatrix CMatrix;

int chooseMatrix(ProductMatrices * prodMat, CompanionMatrix ** compMatr, CMatrix ** cMatr, int V);

void createCompanionMatrix(ProductMatrices * startProdMatr, CompanionMatrix ** compMatr);

void printCompanionMatrix(CompanionMatrix * compMatr);

void deleteCompanionMatrix(CompanionMatrix ** compMatr);

void createCMatrix(ProductMatrices * startProdMatr, CMatrix ** compMatr);

void printCMatrix(CMatrix * compMatr);

void deleteCMatrix(CMatrix ** compMatr);