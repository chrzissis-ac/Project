#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/SimplePoly.h"
#include "../headers/ComplexPoly.h"
#include "../headers/Sylvester.h"
#include "../headers/ProdMatr.h"
#include "../headers/Vector.h"
#include "../headers/CompanionMatrix.h"

void main(int argc,char ** argv){
	printf("---------------------------------------------\n");
	srand(time(NULL));
	char v;
	int in=0;
	int changevar=0;
	int problemisGen=0;
	char temp[300];
	char * function1=NULL;
	int d1=0, dx1=0, dy1=0;
	char * function2=NULL;
	int d2=0, dx2=0, dy2=0;
	double k=0;
	int V=7,i=0,t=0;
	Polyonym2 * polyonym1=NULL;
	Polyonym2 * polyonym2=NULL;
	Sylvester * sylvester=NULL;
	Sylvester * sylvester2=NULL;
	ProductMatrices * prodMatr=NULL;
	ProductMatrices * point=NULL;
	ProductMatrices * new=NULL;
	Eigenstruct * eigenstruct=NULL;
	Vector * vector=NULL;
	Vector * fin=NULL;
	FILE * file=stdin;
	i=0;
	while(i<argc){
		if(strcmp(argv[i],"-generate")==0 && i!=argc-3){
			file=fopen(argv[i+3],"w+");
			if(file==NULL){perror("Could not create input file!");exit(0);}
			else{generatefunctions(atoi(argv[i+1]),atoi(argv[i+2]),file);}
		}
		else if(strcmp(argv[i],"-read")==0 && i!=argc-1){
			file=fopen(argv[i+1],"r");
			if(file==NULL){
				perror("Could not find file!");
				file=stdin;
			}
		}
		else if(strcmp(argv[i],"-solve")==0 && i!=argc-1){
			V=atoi(argv[i+1]);
		}
		i++;

	}
	if(file==NULL){
		printf("Wrong arguments!\n");
		printf("Could not create input file!\n");exit(0);
	}
	
	input(file,&d1,&function1);
	input(file,&d2,&function2);

	createpolyonym2(function1,&polyonym1,d1);
	createpolyonym2(function2,&polyonym2,d2);
	createsylvester(&sylvester, polyonym2, polyonym1);	

	if(createProdMatr(sylvester, &prodMatr)==-1){
		printsylvester(sylvester);
		deletepoly2(polyonym1);
		deletepoly2(polyonym2);
		free(function1);
		free(function2);
		fclose(file);
		destroysylvester(&sylvester);
		return;
	}
	
	changevar=changeofvar3(&new,prodMatr);
	createEigenstruct(&eigenstruct);
	chooseMatrix(new, eigenstruct, V);
	point=prodMatr;
	
	

	do{
		menushow(&in);
		if(in==-1){printsylvester(sylvester);}
		else if(in==-3){
			createInputVector(&vector);
			Svmult(sylvester, vector, &fin);
		}
		else if(in==-5){
			if(point==prodMatr){point=new;}
			else{point=prodMatr;}
		}
		else if(in==-6){
			printEigenstruct(eigenstruct);
		}
		else if(in==-4){
			printf("Wrong input! Please read the instructions and try again!\n");
		}
		else if(in>=0){printProdMatr(point,in);}
	}while(in!=-2);


	deleteEigenstruct(&eigenstruct);

	deletepoly2(polyonym1);
	deletepoly2(polyonym2);
	free(function1);
	free(function2);
	if(prodMatr!=NULL){destroyProdMatr(prodMatr);}
	if(changevar==1){destroyProdMatr(new);}
	fclose(file);
	destroysylvester(&sylvester);
}
