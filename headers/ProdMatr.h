#include "Sylvester.h"

typedef struct ProductMatrices ProductMatrices;

void createProdMatr (Sylvester * sylvester, ProductMatrices **  prodMat);

void destroyProdMatr (ProductMatrices * prodMat);

void printProdMatr(ProductMatrices * prodMat, int in);
