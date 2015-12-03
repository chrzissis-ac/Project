#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/SimplePoly.h"
#include "../headers/ComplexPoly.h"
#include "../headers/Sylvester.h"
#include "../headers/ProdMatr.h"
#include "../headers/Vector.h"
#include "../headers/CompanionMatrix.h"
#include "../headers/Solution.h"

void main(int argc,char ** argv){
	system("clear");
	printf("---------------------------------------------\n");
	srand(time(NULL));
	char v=0;
	int in=0;
	int changevar=0;
	int problemisGen=0;
	char temp[300];
	char inf[300];
	char * function1=NULL;
	int d1=-1, dx1=0, dy1=0;
	char * function2=NULL;
	int d2=-1, dx2=0, dy2=0;
	double k=0,D=0,det=0;
	int V=7,i=0,t=0;
	int read=-1;
	int cv=0,pdr=0,dc=0;
	int taf[4];
	Polyonym2 * polyonym1=NULL;
	Polyonym2 * polyonym2=NULL;
	Sylvester * sylvester=NULL;
	Sylvester * sylvester2=NULL;
	ProductMatrices * prodMatr=NULL;
	ProductMatrices * point=NULL;
	ProductMatrices * new=NULL;
	Eigenstruct * eigenstruct=NULL;
	Gen_eigensol * eigensolution = NULL;
	Gen_sol * GSol=NULL;
		
	
	Vector * vector=NULL;
	Vector * fin=NULL;
	FILE * file=stdin;
	strcpy(inf,"output.txt");
	i=0;
	while(i<argc){
		if(strcmp(argv[i],"-generate")==0 && i!=argc-5){
			read=0;
		}
		else if(strcmp(argv[i],"-read")==0 && i!=argc-1){
			read=1;
		}
		else if(strcmp(argv[i],"-cv")==0){
			cv=1;
		}
		else if((strcmp(argv[i],"-i")==0 || strcmp(argv[i],"-o")==0) && i!=argc-1){
			strcpy(inf,"");
			strcpy(inf,argv[i+1]);
		}
		else if(strcmp(argv[i],"-solve")==0 && i!=argc-1){
			V=atoi(argv[i+1]);
		}
		else if(strcmp(argv[i],"-print_direct_roots")==0){
			pdr=1;
		}
		else if(strcmp(argv[i],"-dc")==0){
			dc=1;
		}
		else if(strcmp(argv[i],"-d1")==0 && i!=argc-1){
			d1=atoi(argv[i+1]);
		}
		else if(strcmp(argv[i],"-d2")==0 && i!=argc-1){
			d2=atoi(argv[i+1]);
		}
		i++;

	}
	if(read==1){
		file=fopen(inf,"r");
		if(file==NULL){perror("Could not find file!");exit(0);}
	}
	else if(read==0){
		file=fopen(inf,"w+");
		if(file==NULL){perror("Could not create input file!");exit(0);}
	}
	if((d1<0 || d2 <0) && file!=stdin ){
		printf("Wrong arguments!\n");
		exit(0);
	}
	if(read==0){generatefunctions(d1,d2,file);}
	input(file,&d1,&function1);
	input(file,&d2,&function2);

	createpolyonym2(function1,&polyonym1,d1);
	createpolyonym2(function2,&polyonym2,d2);
	printf("---------------------------------------------\n");
	createsylvester(&sylvester, polyonym2, polyonym1);
	i=0;
	while(det==0 && i<3){
		if(i!=0){D=rand()%30;}
		det=SylvesterDeterminant(sylvester, D, 0);
		i++;
	}
	if(det!=0){
		printf("---------------------------------------------\n");
		printf("Sylvester Matrix for %.1f is: \n",D);
		SylvesterDeterminant(sylvester, D, 1);
		printf("with Determinant = %f\n",det);
		printf("---------------------------------------------\n");
	}
	if(createProdMatr(sylvester, &prodMatr)==-1 || det==0){
		printsylvester(sylvester);
		deletepoly2(polyonym1);
		deletepoly2(polyonym2);
		free(function1);
		free(function2);
		fclose(file);
		destroysylvester(&sylvester);
		return;
	}
	
	changevar=changeofvar3(&new,prodMatr,cv,taf);
	chooseMatrix(new, &eigenstruct, V);
	solver(eigenstruct, &eigensolution, &GSol);
	if(pdr){
		printGen_sol(GSol,NULL,NULL,0);
	}
	changevarback(&GSol, taf);
	
	if(dc==1){double_check(GSol,polyonym1,polyonym2);}
	point=prodMatr;
	//printf("Value is %f\n",polyonymtryvalue(polyonym2, 0.019728, -148651.84)-polyonymtryvalue(polyonym1, 0.019728, -148651.84));
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
		else if(in==-7){
			printGen_eigensol(eigensolution);
		}
		else if(in==-8){
			printGen_sol(GSol,polyonym1,polyonym2,0);
		}
		else if(in==-9){
			printGen_sol(GSol,polyonym1,polyonym2,1);
		}
		else if(in==-4){
			printf("Wrong input! Please read the instructions and try again!\n");
		}
		else if(in>=0){printProdMatr(point,in);}
	}while(in!=-2);


	deleteEigenstruct(&eigenstruct);
	destroyGen_eigensol(&eigensolution);
	deleteGen_sol(&GSol);
	deletepoly2(polyonym1);
	deletepoly2(polyonym2);
	free(function1);
	free(function2);
	if(prodMatr!=NULL){destroyProdMatr(prodMatr);}
	if(changevar==1){destroyProdMatr(new);}
	fclose(file);
	destroysylvester(&sylvester);
}
