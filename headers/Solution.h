typedef struct Gen_eigensol Gen_eigensol;

typedef struct eigensol eigensol;

void createSolution(Gen_eigensol ** solution, int dim, double * eigenValue, double * eigenVector,char c);

void destroyGen_eigensol(Gen_eigensol ** solution);

void printGen_eigensol(Gen_eigensol * solution);
