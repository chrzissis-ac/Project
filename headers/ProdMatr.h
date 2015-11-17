#include "Sylvester.h"

typedef struct ProductMatrices ProductMatrices;

void createProdMatr (Sylvester * sylvester, ProductMatrices **  prodMat);

void destroyProdMatr (ProductMatrices * prodMat);

void printProdMatr(ProductMatrices * prodMat, int in);

void printProdMatr_int(ProductMatrices * prodMat, int in);

int calculate_K(ProductMatrices * prodMat);

int changeofvar3(ProductMatrices ** finl, ProductMatrices * prodMat);

void multProdMatr(ProductMatrices ** target, Polyonym * poly, ProductMatrices * prodMat, int g);

void addProdMatr(ProductMatrices ** target, ProductMatrices * matrix1, ProductMatrices * matrix2);

void create_newProd(ProductMatrices ** finl, ProductMatrices * prodMat);
