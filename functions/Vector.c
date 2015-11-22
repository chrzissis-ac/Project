#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/Vector.h"
#include "../headers/SimplePoly.h"
#include "../headers/ComplexPoly.h"

typedef double * Poly;
struct Polyonym{
	Poly matrix;
	char var;
	int d;
};

struct Vector{
	Polyonym * matrix;
	int dim;
};

//---------------------------------------------------------Vector struct management----------------------------------------------------------------

void createStableVector(Vector * vector, double * input, int dim, char c){
	if(dim<=0){printf("Dimension must be greater than 0!\n");return;}
	int i=0;
	Polyonym2 * ZeroPoly=NULL;
	createpolyonym("0", &ZeroPoly, 0, 0);
	vector->dim=dim;
	vector->matrix=NULL;
	vector->matrix=malloc(sizeof(Polyonym)*dim);
	if(vector->matrix==NULL){perror("Vector matrix malloc!");exit(0);}
	while(i<dim){
		create1polyonym(ZeroPoly, &((vector->matrix)[i]), c, 0);
		change1polyonym(&((vector->matrix)[i]),0,input[i]);
		i++;
	}
	deletepoly2(ZeroPoly);
}

// createZeroVector() creates a zero-vector 'vector' with dimension 'dim' and variable 'v'
void createZeroVector(Vector ** vector, int dim, char v){
	if(dim<=0){printf("Dimension must be greater than 0!\n");return;}
	int i=0;
	Polyonym2 * ZeroPoly=NULL;
	createpolyonym("0", &ZeroPoly, v, 0);
	srand(time(NULL));
	(*vector)=NULL;
	(*vector)=malloc(sizeof(Vector));
	if((*vector)==NULL){perror("Vector malloc!");exit(0);}
	(*vector)->dim=dim;
	(*vector)->matrix=NULL;
	(*vector)->matrix=malloc(sizeof(struct Polyonym)*dim);
	if((*vector)->matrix==NULL){perror("Vector matrix malloc!");exit(0);}
	while(i<dim){
		create1polyonym(ZeroPoly, &((*vector)->matrix[i]), v, 0);
		i++;
	}
	deletepoly2(ZeroPoly);
}

// createRandVector() creates a random-value 'vector' with dimension 'dim'
void createRandVector(Vector ** vector, int dim){
	if(dim<=0){printf("Dimension must be greater than 0!\n");return;}
	int i=0;
	Polyonym2 * ZeroPoly=NULL;
	createpolyonym("0", &ZeroPoly, 0, 0);
	srand(time(NULL));
	(*vector)=NULL;
	(*vector)=malloc(sizeof(Vector));
	if((*vector)==NULL){perror("Vector malloc!");exit(0);}
	(*vector)->dim=dim;
	(*vector)->matrix=NULL;
	(*vector)->matrix=malloc(sizeof(Polyonym)*dim);
	if((*vector)->matrix==NULL){perror("Vector matrix malloc!");exit(0);}
	while(i<dim){
		create1polyonym(ZeroPoly, &((*vector)->matrix[i]), 'x', 0);
		change1polyonym(&((*vector)->matrix[i]),0,rand()%250);
		i++;
	}
	deletepoly2(ZeroPoly);
}

// createInputVector() creates a 'vector' from stdin
void createInputVector(Vector ** vector){
	int i=0,dim=0;
	char temp[300];
	printf("Give Vector dimension\n");
	fgets(temp,300,stdin);
	dim=atoi(temp);
	if(dim<=0){printf("Dimension must be greater than 0!\n");return;}
	Polyonym2 * ZeroPoly=NULL;
	createpolyonym("0", &ZeroPoly, 0, 0);
	srand(time(NULL));
	(*vector)=NULL;
	(*vector)=malloc(sizeof(Vector));
	if((*vector)==NULL){perror("Vector malloc!");exit(0);}
	(*vector)->dim=dim;
	(*vector)->matrix=NULL;
	(*vector)->matrix=malloc(sizeof(Polyonym)*dim);
	if((*vector)->matrix==NULL){perror("Vector matrix malloc!");exit(0);}
	while(i<dim){
		create1polyonym(ZeroPoly, &((*vector)->matrix[i]), 'x', 0);
		printf("Give Vector coordinate no. %d\n",i+1);
		fgets(temp,300,stdin);
		change1polyonym(&((*vector)->matrix[i]),0,atoi(temp));
		i++;
	}
	deletepoly2(ZeroPoly);
}

// createFileVector() creates a 'vector' from 'inputfile'
void createFileVector(Vector ** vector, char * inputfile){
	FILE * file=NULL;
	file=fopen(inputfile,"r");
	if(file==NULL){perror("Input Vector file!");return;}
	int i=0,dim=0;
	char temp[300];
	fgets(temp,300,file);
	dim=atoi(temp);
	if(dim<=0){printf("Dimension must be greater than 0!\n");fclose(file);return;}
	Polyonym2 * ZeroPoly=NULL;
	createpolyonym("0", &ZeroPoly, 0, 0);
	srand(time(NULL));
	(*vector)=NULL;
	(*vector)=malloc(sizeof(Vector));
	if((*vector)==NULL){perror("Vector malloc!");exit(0);}
	(*vector)->dim=dim;
	(*vector)->matrix=NULL;
	(*vector)->matrix=malloc(sizeof(Polyonym)*dim);
	if((*vector)->matrix==NULL){perror("Vector matrix malloc!");exit(0);}
	while(i<dim){
		create1polyonym(ZeroPoly, &((*vector)->matrix[i]), 'x', 0);
		fgets(temp,300,file);
		change1polyonym(&((*vector)->matrix[i]),0,atoi(temp));
		i++;
	}
	deletepoly2(ZeroPoly);
	fclose(file);
}

// printVector() prints the matrix of 'vector'
void printVector(Vector * vector){
	if(vector==NULL){printf("Vector to print is NULL!\n");return;}
	int i=0;
	printf("Vector with dimension %d:\n\n",vector->dim);
	while(i<vector->dim){
		printf("|");
		print1polyonym(&(vector->matrix[i]));
		printf("\t|\n");
		i++;
	}
}

// deleteVector() frees the memory that was allocated for 'vector'
void deleteVector(Vector * vector){
	if(vector==NULL){return;}
	int i=0;
	while(i<vector->dim){
		delete1matrix(&(vector->matrix[i]));
		i++;
	}
	free(vector->matrix);
	free(vector);
}

void deleteVector_static(Vector * vector){
	if(vector==NULL){return;}
	int i=0;
	while(i<vector->dim){
		delete1matrix(&(vector->matrix[i]));
		i++;
	}
	free(vector->matrix);
}

// getVectordim() returns the dimension of 'vector'
int getVectordim(Vector * vector){return vector->dim;}
