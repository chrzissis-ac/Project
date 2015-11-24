#include "SimplePoly.h"
#include "Vector.h"

typedef struct Sylvester Sylvester;

void createsylvester (Sylvester ** sylvester, Polyonym2 * p1, Polyonym2 * p2);

void printsylvester (Sylvester * sylvester);

void destroysylvester (Sylvester ** sylvester);

void Svmult(Sylvester * sylvester, Vector * vector, Vector ** fin);
