#include "Sylvester.h"

typedef struct ProductMatrices ProductMatrices;

int createProdMatr (Sylvester * sylvester, ProductMatrices **  prodMat);

void destroyProdMatr (ProductMatrices * prodMat);

void printProdMatr(ProductMatrices * prodMat, int in);

int changeofvar3(ProductMatrices ** finl, ProductMatrices * prodMat,int allow, int t[4]);

int get_Productdim(ProductMatrices * prod);

double get_Productk(ProductMatrices * prod);

char get_Producthidden(ProductMatrices * prod);

int get_Productdegree(ProductMatrices * prod);
