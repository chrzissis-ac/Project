typedef struct Polyonym2  Polyonym2;

void createpolyonym(char * function, Polyonym2 ** poly, int dx, int dy);

void deletepoly2(Polyonym2 * poly);//

void parser(char * func , Polyonym2 * polyonym);

void printpolymatrix(Polyonym2 * polyonym);

void printpoly(Polyonym2 * polyonym);

void printpoly_byvar(Polyonym2 * polyonym, char v);

int getDegree2(Polyonym2 * poly, char v);

int get_polymatrix2(Polyonym2 * poly,int i,int j);
