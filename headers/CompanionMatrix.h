#include "../headers/ProdMatr.h"

typedef struct CompanionMatrix CompanionMatrix;

typedef struct CompanionMatrixB CompanionMatrixB;

void createCompanionMatrix(ProductMatrices * startProdMatr, CompanionMatrix ** compMatr);

void printCompanionMatrix(CompanionMatrix * compMatr);

void deleteCompanionMatrix(CompanionMatrix ** compMatr);

void createCompanionMatrixB(ProductMatrices * startProdMatr, CompanionMatrixB ** compMatr);

void printCompanionMatrixB(CompanionMatrixB * compMatr);

void deleteCompanionMatrixB(CompanionMatrixB ** compMatr);
