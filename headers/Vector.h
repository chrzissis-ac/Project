#include "SimplePoly.h"

typedef struct Vector Vector;


void createInputVector(Vector ** vector);

void createZeroVector(Vector ** vector, int dim,char v);

void createStableVector(Vector * vector, double * input, int dim, char c);

void deleteVector(Vector * vector);

void deleteVector_static(Vector * vector);

void printVector(Vector * vector);

int getVectordim(Vector * vector);
