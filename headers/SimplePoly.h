#include "ComplexPoly.h"

typedef struct Polyonym Polyonym;

void create1polyonym(Polyonym2 * polyonym2, Polyonym * polyonym, char v, int point);

void copy1polyonym(Polyonym * target,Polyonym * source);

void add1polyonyms(Polyonym * trgt, Polyonym * polyonym1, Polyonym * polyonym2);

void multiply1polyonym(Polyonym * trgt, Polyonym * polyonym1,int m);

void delete1matrix(Polyonym * poly);

void delete1polyonym(Polyonym * poly);

void print1polyonym(Polyonym * poly);

int get1Degree(Polyonym * poly);

int get1NumByDegree(Polyonym * poly, int targetDeg);

char get1var(Polyonym * poly);

void change1polyonym(Polyonym * poly,int grade,int in);
