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
	int V=7;
	Polyonym2 * polyonym1=NULL;
	Polyonym2 * polyonym2=NULL;
	Sylvester * sylvester=NULL;
	Sylvester * sylvester2=NULL;
	CompanionMatrix * compMatr=NULL;
	CMatrix * cMatr=NULL;
	ProductMatrices * prodMatr=NULL;
	ProductMatrices * point=NULL;
	ProductMatrices * new=NULL;
	Vector * vector=NULL;
	Vector * fin=NULL;
	FILE * file=stdin;
	if(argc==5 && strcmp(argv[1],"-generate")==0 ){
		file=fopen(argv[4],"w+");
		if(file==NULL){perror("Could not create input file!");file=stdin;}
		else{generatefunctions(atoi(argv[2]),atoi(argv[3]),file);}
	}
	else if(argc==3 && strcmp(argv[1],"-read")==0 ){
		file=fopen(argv[2],"r");
		if(file==NULL){
			perror("Could not find file!");
			file=stdin;
		}
	}
	else if(argc>1){printf("Wrong arguments!\n");}

	input(file,&d1,&function1);
	input(file,&d2,&function2);

	createpolyonym2(function1,&polyonym1,d1);
	createpolyonym2(function2,&polyonym2,d2);
	createsylvester(&sylvester, polyonym2, polyonym1);
	createProdMatr(sylvester, &prodMatr);

	changevar=changeofvar3(&new,prodMatr);
	problemisGen=chooseMatrix(new, &compMatr, &cMatr, V);
	point=prodMatr;
	if(problemisGen==0){printf("\n----------\nProblem is Standard!\n----------\n");}
	else if(problemisGen==1){printf("\n----------\nProblem is Generalized!\n----------\n");}
	
	if(problemisGen==-1){
		printsylvester(sylvester);
		deletepoly2(polyonym1);
		deletepoly2(polyonym2);
		free(function1);
		free(function2);
		destroyProdMatr(prodMatr);
		fclose(file);
		destroysylvester(&sylvester);
		return;
	}

	do{
		menushow(&in);
		//system("clear");
		if(in==-1){printsylvester(sylvester);}
		else if(in==-3){
			createInputVector(&vector);
			Svmult(sylvester, vector, &fin);
		}
		else if(in==-5){
			if(point==prodMatr){point=new;}
			else{point=prodMatr;}
		}
		else if(in==-4){
			printf("Wrong input! Please read the instructions and try again!\n");
		}
		else if(in>=0){printProdMatr_int(point,in);}
	}while(in!=-2);


	if(problemisGen==0){deleteCompanionMatrix(&compMatr);}
	else{deleteCMatrix(&cMatr);}

	deletepoly2(polyonym1);
	deletepoly2(polyonym2);
	free(function1);
	free(function2);
	destroyProdMatr(prodMatr);
	if(changevar==1){destroyProdMatr(new);}
	fclose(file);
	destroysylvester(&sylvester);
}
