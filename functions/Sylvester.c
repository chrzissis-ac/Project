#include <stdio.h>
#include <stdlib.h>

#include "../headers/Vector.h"
#include "../headers/Sylvester.h"
#include "../headers/SimplePoly.h"


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

struct Sylvester{
	Polyonym ** matrix;
	int dim;
	char hidden;
	int degree;
};


//---------------------------------------------------------Sylvester struct management----------------------------------------------------------------

// createsylvester() creates a Sylvester struct  ('sylvester') and its matrix is filled with single-variable Polyonym structs that derive from 'p1' and 'p2' or from a zero-value Polyonym2 struct
void createsylvester (Sylvester ** sylvester, Polyonym2 * p1, Polyonym2 * p2) {
int degP1x, degP2x, degP1y, degP2y, dim, maxX, maxY, counter1, counter2, i, j, m, n;
	char hidden;
	Polyonym2 * ZeroPoly=NULL;
	createpolyonym("0", &ZeroPoly, 0, 0);
	(*sylvester)=NULL;
	(*sylvester)=malloc(sizeof(struct Sylvester));
	if ((*sylvester)==NULL) {perror("Sylvester malloc!");exit(0);}
	degP1x=getDegree2(p1, 'x');
	degP2x=getDegree2(p2, 'x');
	degP1y=getDegree2(p1, 'y');
	degP2y=getDegree2(p2, 'y');
	//hidden=choosevar_bydeg(degP1x, degP1y, degP2x, degP2y);
	//printf("hidden by func: %c\n", hidden);
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
	printf("Dimension is: %d\n", (*sylvester)->dim);
	if (hidden=='x') {
		if (degP1x>degP2x || degP2x!=0) {
			(*sylvester)->degree=degP1x;
		}
		else {
			(*sylvester)->degree=degP2x;
		}
	}
	else {
		if (degP1y>degP2y || degP2y!=0) {
			(*sylvester)->degree=degP1y;
		}
		else {
			(*sylvester)->degree=degP2y;
		}
	}

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
void copysylvester(Sylvester ** target, Sylvester * source){
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
	printf("Sylvester matrix is:\n\n");
	int dim, i, j;
	dim=sylvester->dim;
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
	return;
}

// destroysylvester() frees the memory that was allocated for 'sylvester'
void destroysylvester (Sylvester ** sylvester) {
	int dim, i, j;
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