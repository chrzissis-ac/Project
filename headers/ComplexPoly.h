typedef struct Polyonym2  Polyonym2;

double polyonymtryvalue(Polyonym2 * poly, double vx, double vy);

void createpolyonym2(char * function, Polyonym2 ** poly, int d);

void deletepoly2(Polyonym2 * poly);

void printpolymatrix(Polyonym2 * polyonym);

void printpoly(Polyonym2 * polyonym);

void printpoly_byvar(Polyonym2 * polyonym, char v);

int getDegree2(Polyonym2 * poly, char v);

int get_polymatrix2(Polyonym2 * poly,int i,int j);


