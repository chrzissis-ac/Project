#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>

#include "../headers/Routines.h"
#include "../headers/Vector.h"
#include "../headers/Sylvester.h"
#include "../headers/SimplePoly.h"


typedef double * Poly;
struct Polyonym{
	Poly matrix;
	char var;
	int d;
};

struct Sylvester{
	Polyonym ** matrix;
	int dim;
	char hidden;
	int degree;
};


//---------------------------------------------------------Sylvester struct management----------------------------------------------------------------

// createsylvester() creates a Sylvester struct  ('sylvester') and its matrix is filled with single-variable Polyonym structs that derive from 'p1' and 'p2' or from a zero-value Polyonym2 struct
void createsylvester (Sylvester ** sylvester, Polyonym2 * p1, Polyonym2 * p2) {
int degP1x=0, degP2x=0, degP1y=0, degP2y=0, dim=0, maxX=0, maxY=0, counter1=0, counter2=0, i=0, j=0, m=0, n=0;
	char hidden;
	Polyonym2 * ZeroPoly=NULL;
	createpolyonym2("0", &ZeroPoly, 0);
	(*sylvester)=NULL;
	(*sylvester)=malloc(sizeof(struct Sylvester));
	if ((*sylvester)==NULL) {perror("Sylvester malloc!");exit(0);}
	degP1x=getDegree2(p1, 'x');
	degP2x=getDegree2(p2, 'x');
	degP1y=getDegree2(p1, 'y');
	degP2y=getDegree2(p2, 'y');
	if (degP1x>=degP2x) {
		maxX=degP1x;
	}
	else {
		maxX=degP2x;
	}
	if (degP1y>=degP2y) {
		maxY=degP1y;
	}
	else {
		maxY=degP2y;
	}
	if (maxX>=maxY) {
		hidden='y';
		dim=degP1x+degP2x;
	}
	else {
		hidden='x';
		dim=degP1y+degP2y;
	}
	(*sylvester)->hidden=hidden;
	(*sylvester)->dim=dim;
	printf("-Sylvester:\n");	
	printf("Dimension is: %d and the ", (*sylvester)->dim);
	if (hidden=='x') {
		if (degP1x>=degP2x && degP2y!=0 ) {
			(*sylvester)->degree=degP1x;
		}
		else {
			(*sylvester)->degree=degP2x;
		}
	}
	else {
		if (degP1y>=degP2y && degP2x!=0 ) {
			(*sylvester)->degree=degP1y;
		}
		else {
			(*sylvester)->degree=degP2y;
		}
	}
	printf("hidden variable is %c with degree %d\n",hidden,(*sylvester)->degree);
	printf("---------------------------------------------\n");
	(*sylvester)->matrix=NULL;
	(*sylvester)->matrix=malloc(sizeof(Polyonym *)*dim);
	if ((*sylvester)->matrix==NULL) {perror("Sylvester matrix malloc!");exit(0);}
	for (i=0 ; i<dim ; i++) {
		(*sylvester)->matrix[i]=NULL;
		(*sylvester)->matrix[i]=malloc(sizeof(Polyonym)*dim);
		if ((*sylvester)->matrix[i]==NULL) {perror("Sylvester matrix malloc!");exit(0);}
	}
	counter1=0;
	counter2=0;
	m=dim-1;
	for (i=0 ; i<dim ; i++) {
		n=dim-1;
		if ((*sylvester)->hidden=='x') {
			if (i<degP2y) {
				if (counter1==0) {
					for (j=0 ; j<=degP1y ; j++) {
						create1polyonym(p1, &((*sylvester)->matrix[m][n]), 'y', j);
						n--;
					}
					for (j=degP1y+1 ; j<degP1y+degP2y ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'y', 0);
						n--;
					}
				}
				else {
					for(j=0 ; j<counter1 ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'y', 0);
						n--;
					}
					for (j=counter1 ; j<=degP1y+counter1 ; j++) {
						create1polyonym(p1, &((*sylvester)->matrix[m][n]), 'y', j-counter1);
						n--;
					}
					for (j=degP1y+counter1+1 ; j<degP1y+degP2y ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'y', 0);
						n--;
					}
				}
				counter1++;
			}
			else {
				if (counter2==0) {
					for (j=0 ; j<=degP2y ; j++) {
						create1polyonym(p2, &((*sylvester)->matrix[m][n]), 'y', j);
						n--;
					}
					for (j=degP2y+1 ; j<degP1y+degP2y ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'y', 0);
						n--;
					}
				}
				else {
					for(j=0 ; j<counter2 ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'y', 0);
						n--;
					}
					for (j=counter2 ; j<=degP2y+counter2 ; j++) {
						create1polyonym(p2, &((*sylvester)->matrix[m][n]), 'y', j-counter2);
						n--;
					}
					for (j=degP2y+counter2+1 ; j<degP1y+degP2y ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'y', 0);
						n--;
					}
				}
				counter2++;
			}
		}
		else {
			if (i<degP2x) {
				if (counter1==0) {
					for (j=0 ; j<=degP1x ; j++) {
						create1polyonym(p1, &((*sylvester)->matrix[m][n]), 'x', j);
						n--;
					}
					for (j=degP1x+1 ; j<degP1x+degP2x ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'x', 0);
						n--;
					}
				}
				else {
					for(j=0 ; j<counter1 ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'x', 0);
						n--;
					}
					for (j=counter1 ; j<=degP1x+counter1 ; j++) {
						create1polyonym(p1, &((*sylvester)->matrix[m][n]), 'x', j-counter1);
						n--;
					}
					for (j=degP1x+counter1+1 ; j<degP1x+degP2x ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'x', 0);
						n--;
					}
				}
				counter1++;
			}
			else {
				if (counter2==0) {
					for (j=0 ; j<=degP2x ; j++) {
						create1polyonym(p2, &((*sylvester)->matrix[m][n]), 'x', j);
						n--;
					}
					for (j=degP2x+1 ; j<degP1x+degP2x ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'x', 0);
						n--;
					}
				}
				else {
					for(j=0 ; j<counter2 ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'x', 0);
						n--;
					}
					for (j=counter2 ; j<=degP2x+counter2 ; j++) {
						create1polyonym(p2, &((*sylvester)->matrix[m][n]), 'x', j-counter2);
						n--;
					}
					for (j=degP2x+counter2+1 ; j<degP1x+degP2x ; j++) {
						create1polyonym(ZeroPoly, &((*sylvester)->matrix[m][n]), 'x', 0);
						n--;
					}
				}
				counter2++;
			}
		}
		m--;
	}
	deletepoly2(ZeroPoly);
	return;
}

// copysylvester() copies a Sylvester struct ('source') to another Sylvester struct ('target')
static void copysylvester(Sylvester ** target, Sylvester * source){
	int i=0,j=0;
	(*target)=NULL;
	(*target)=malloc(sizeof(Sylvester));
	if((*target)==NULL){printf("Sylvester copy malloc!");exit(0);}
	(*target)->degree=source->degree;
	(*target)->hidden=source->hidden;
	(*target)->dim=source->dim;
	
	(*target)->matrix=NULL;
	(*target)->matrix=malloc(sizeof(Polyonym *)*(*target)->dim);
	if ((*target)->matrix==NULL) {perror("Sylvester matrix malloc!");exit(0);}
	for (i=0 ; i<(*target)->dim ; i++) {
		(*target)->matrix[i]=NULL;
		(*target)->matrix[i]=malloc(sizeof(Polyonym)*(*target)->dim);
		if ((*target)->matrix[i]==NULL) {perror("Sylvester matrix malloc!");exit(0);}
		for(j=0;j<(*target)->dim;j++){
			copy1polyonym(&((*target)->matrix[i][j]),&(source->matrix[i][j]));
		}
	}
}

// printsylvester() prints the matrix of 'sylvester'
void printsylvester (Sylvester * sylvester) {
	int dim=0, i=0, j=0;
	dim=sylvester->dim;
	printf("---------------------------------------------\n");
	printf("The Sylvester Matrix is:\n\n");
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			print1polyonym(&(sylvester->matrix[i][j]));
			printf("|\t");
		}
		printf("\n");
	}
	printf("\n");
	printf("Grade is: %d\n", sylvester->degree);
	printf("With dimensions %dx%d\n",sylvester->dim,sylvester->dim);
	printf("---------------------------------------------\n");
	return;
}
//Given a value, calculates the sylvester's determinant with the use of LAPACKE_dgetrf
double SylvesterDeterminant(Sylvester * sylv, double value, int print){
	int i=0,j=0;
	int dim=sylv->dim;
	double ** matrix=NULL;
	double * matrix1d;
	double det=1;
	int * ipiv=NULL;
	
	matrix=malloc(sizeof(double*)*dim);
	if(matrix==NULL){perror("Det matrix malloc 1D");exit(0);}
	for(i=0;i<dim;i++){
		matrix[i]=malloc(sizeof(double)*dim);
		if(matrix[i]==NULL){perror("Det matrix malloc 2D");exit(0);}
	}
	ipiv=LAPACKE_malloc(sizeof(int) * (dim*(dim>=6) + 6*(dim<6)) );
	if(ipiv==NULL){perror("ipiv malloc comp matrx creation");exit(0);}
	
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			matrix[i][j]=get_polyonymvalue(&(sylv->matrix[i][j]), value);
		}
	}
	
	if(print==1){
		for(i=0;i<dim;i++){

			for(j=0;j<dim;j++){
				printf("%.5f|\t",matrix[i][j]);
			}
			printf("\n");
		}

	}
	from2Dto1D_double(matrix, &matrix1d, dim, dim);
	LAPACKE_dgetrf(LAPACK_ROW_MAJOR, dim, dim, matrix1d, dim, ipiv);
	for(i=0;i<dim;i++){
			det=det*( (ipiv[i]==(i+1)) + (-1)*(ipiv[i]!=(i+1)) ) *(matrix1d[i*dim+i]);
	}
	free(matrix1d);
	LAPACKE_free(ipiv);
	for(i=0;i<dim;i++){free(matrix[i]);}
	free(matrix);
	return det;
}
// destroysylvester() frees the memory that was allocated for 'sylvester'
void destroysylvester (Sylvester ** sylvester) {
	int dim=0, i=0, j=0;
	dim=(*sylvester)->dim;
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			delete1matrix(&((*sylvester)->matrix[i][j]));
		}
		free((*sylvester)->matrix[i]);
	}
	free((*sylvester)->matrix);
	free(*sylvester);

	return;
}

//-----------------------------------Sylvester x Vector multiplication------------------------------------------------------------
struct Vector{
	Polyonym * matrix;
	int dim;
};
// Svmult() multiplies mathematically the matrix of 'sylvester' with the matrix of 'vector'
void Svmult(Sylvester * sylvester, Vector * vector, Vector ** fin){
	if(vector->dim!=sylvester->dim){
		printf("Multiplication impossible due to different matrix dimensions!\n");
		deleteVector(vector);
		return;
	}
	int i=0,j=0;
	char v='x';
	if(sylvester->hidden=='x'){v='y';}
	Sylvester * temp=NULL;
	copysylvester(&temp, sylvester);
	for(i=0;i<temp->dim;i++){
		for(j=0;j<temp->dim;j++){
			multiply1polyonym(&(temp->matrix[i][j]), &(temp->matrix[i][j]),(vector->matrix[j]).matrix[0]);
		}
	}
	printVector(vector);
	createZeroVector(fin, vector->dim, v);
	for(i=0;i<temp->dim;i++){
		for(j=0;j<temp->dim;j++){
			add1polyonyms(&((*fin)->matrix[i]), &((*fin)->matrix[i]), &(temp->matrix[i][j]));
		}
	}
	printVector(*fin);
	destroysylvester(&temp);
	deleteVector(vector);
	deleteVector(*fin);
}


