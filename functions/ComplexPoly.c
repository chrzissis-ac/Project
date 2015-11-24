#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/ComplexPoly.h"

typedef int ** Poly2;
struct Polyonym2{
	Poly2 matrix;
	int dx;
	int dy;
};

//----------------------------------------------------------Polyonyma of 2 variables management-----------------------------------------------
static void gradeparser(char * func, int d, int * maxdx, int * maxdy){
	*maxdx=0;
	*maxdy=0;
	int i=0,a=0,s=0;
	int dx=0,dy=0;
	char temp[300];
	char deg[300];
	while(func[i]!='\0'){
		if(func[i]=='x'){
			if(func[i+1]=='^'){
				strcpy(deg,"");
				i=i+2;a=0;s=i;
				while(func[s+a]>='0' && func[s+a]<='9'){a++;}
				strcpy(deg,"");
				strncpy(deg,&(func[s]),a);
				dx=atoi(deg);
				i=s+a-1;
			}
			else{dx=1;}
			if(dx>=*maxdx){*maxdx=dx;}
		}
		else if(func[i]=='y'){
			if(func[i+1]=='^'){
				strcpy(deg,"");
				i=i+2;a=0;s=i;
				while(func[s+a]>='0' && func[s+a]<='9'){a++;}
				strcpy(deg,"");
				strncpy(deg,&(func[s]),a);
				dy=atoi(deg);
				i=s+a-1;
			}
			else{dy=1;}
			if(dy>=*maxdy){*maxdy=dy;}
		}
		i++;
	}
	if((*maxdx)+(*maxdy)!=d){printf("The right Function Grade is %d\n",(*maxdx)+(*maxdy));}
}

// parser() chooses the variable with the lowest degree that derives from 'func', along with its polyonimial grades dx, dy for x and y respectively, and stores the function and its degree in 'polyonym'
static void parser(char * func , Polyonym2 * polyonym){
	if(func[strlen(func)]=='\n'){
		func[strlen(func)]='\0';	//Delete change of line
	}
	else if(func[strlen(func)-1]=='\n'){
		func[strlen(func)-1]='\0';	//Delete change of line
	}

	int i=0,s=0,a=0,b=0,j=0,set=0;
	int length=strlen(func)+1;
	int dx=0,dy=0;
	char var='0', pros='+';
	char synt[300];
	char deg[300];

	i=0;
	if(func[0]!='+' && func[0]!='-'){synt[0]='+';j=1;}
	while(i<length){
		if(func[i]==' ' || func[i]=='*'){}
		else if(func[i]=='x'){
			if(func[i+1]=='^'){
				strcpy(deg,"");
				i=i+2;a=0;s=i;
				while(func[s+a]>='0' && func[s+a]<='9'){a++;}
				strcpy(deg,"");
				strncpy(deg,&(func[s]),a);
				dx=atoi(deg);
				i=s+a-1;
			}
			else{dx=1;}
		}
		else if(func[i]=='y'){
			if(func[i+1]=='^'){
				strcpy(deg,"");
				i=i+2;a=0;s=i;
				while(func[s+a]>='0' && func[s+a]<='9'){a++;}
				strcpy(deg,"");
				strncpy(deg,&(func[s]),a);
				dy=atoi(deg);
				i=s+a-1;
			}
			else{dy=1;}
		}
		else if(   (func[i]=='\0') || (func[i]=='+' || func[i]=='-')  ){
			if(j==1 && (synt[0]=='+' || synt[0]=='-') ){
				synt[j]='1';
				j++;
			}
			set=1;
			synt[j]='\0';
			(polyonym->matrix)[dx][dy]=atoi(synt);
			strcpy(synt,"");
			dx=0;dy=0;
			synt[0]=func[i];
			j=1;
		}
		else{
			synt[j]=func[i];
			j++;
		}
		i++;
	}
}
// createpolyonym() creates a Polyonym2 struct ('poly') with 'v' as its variable that derives from 'function'
static void createpolyonym(char * function, Polyonym2 ** poly, int dx, int dy){
	Polyonym2 * polyonym;
	int i=0, j=0;
	polyonym=NULL;
	polyonym=malloc(sizeof(struct Polyonym2));
	if(polyonym==NULL){perror("malloc poly2");exit(0);}
	polyonym->matrix=NULL;
	polyonym->matrix=malloc(sizeof(int*)*(dx+1));
	if(polyonym->matrix==NULL){perror("malloc matrix poly2 1D");exit(0);}
	while(i<=dx){
		(polyonym->matrix)[i]=NULL;
		(polyonym->matrix)[i]=malloc(sizeof(int)*(dy+1));
		if((polyonym->matrix)[i]==NULL){perror("malloc matrix 2D");exit(0);}
		i++;
	}
	i=0;j=0;
	while(i<=dx){
		j=0;
		while(j<=dy){
			(polyonym->matrix)[i][j]=0;
			j++;
		}
		i++;
	}
	
	polyonym->dx=dx;
	polyonym->dy=dy;
	parser(function , polyonym);
	(*poly)=polyonym;
}

double polyonymtryvalue(Polyonym2 * poly, double vx, double vy){
	int i,j;
	double value=0.0;
	double tempx,tempy;
	tempx=1.0;
//	if(vx==0.0){tempx=0.0;}
	for(i=0;i<=(poly->dx);i++){
		tempy=1.0;
		
		for(j=0;j<=(poly->dy);j++){
		//	printf("value[a]= %f,tempx=%f,tempy=%f\n",value,tempx,tempy);
			value=value+poly->matrix[i][j]*tempx*tempy;
		//	printf("value[b]= %f,tempx=%f,tempy=%f\n",value,tempx,tempy);
			tempy=tempy*vy;
		}
		tempx=tempx*vx;
	}
	return value;
}


void createpolyonym2(char * function, Polyonym2 ** poly, int d){
	int dx=0, dy=0;
	gradeparser(function, d, &dx, &dy);
	createpolyonym(function, poly, dx, dy);

}

// deletepoly2() frees the memory that was allocated for 'poly'
void deletepoly2(Polyonym2 * poly){
	int i=0;
	while(i<=poly->dx){
		free(poly->matrix[i]);
		i++;
	}
	free(poly->matrix);
	free(poly);

}



// printpolymatrix() prints the matrix of 'polyonym' where every row[i] corresponds to the coefficient of y^i and every column[j] corresponds to coefficient of x^j
void printpolymatrix(Polyonym2 * polyonym){
	int i=0,j=0;
	while(i<=polyonym->dy){
		j=0;
		printf("\n Y^%d=>\t",i);
		while(j<=polyonym->dx){
			printf("%d|\t",polyonym->matrix[j][i]);
			j++;
		}
		i++;
	}
	printf("\n");
}

// printpoly() prints 'polyonym' according to the following format c0 +- c1 y +- c2 x +- c3 y x +- ... +- ck y^a1 x^a2 (no spaces in output)
void printpoly(Polyonym2 * polyonym){
	int i=0,j=0;
	while(i<=polyonym->dy){
		j=0;
		while(j<=polyonym->dx){
			if(polyonym->matrix[j][i]!=0){
				if(polyonym->matrix[j][i]>0){printf("+");}
				if(polyonym->matrix[j][i]!=1){printf("%d",polyonym->matrix[j][i]);}
				if(j!=0){
					printf("x");
					if(j!=1){printf("^%d",j);}
				}
				if(i!=0){
					printf("y");
					if(i!=1){printf("^%d",i);}
				}
			}
			j++;
		}
		i++;
	}
	printf("\n");
}

// printpoly_byvar() prints 'polyonym' according to the following format c0 +- c1 y +- c2 'v' +- c3 y 'v' +- ... +- ck y^a1 'v'^a2 (no spaces in output)
void printpoly_byvar(Polyonym2 * polyonym, char v){
int i=0,j=0,set=0;
	printf("\n");
		if(v=='y'){
		while(i<=polyonym->dy){
				j=0;
				set=0;
				printf("\nDegree %d:\n",i);
				while(j<=polyonym->dx){
					if(polyonym->matrix[j][i]>0){printf("+");}
					if(polyonym->matrix[j][i]!=0){
						set=1;
						if(polyonym->matrix[j][i]!=1||(polyonym->matrix[j][i]==1 && j==0)){printf("%d",polyonym->matrix[j][i]);}
						if(j!=0){
							printf("x");
							if(j!=1){printf("^%d",j);}
						}
					}
					j++;
				}
				if(set==0){printf("0");}
				i++;
			}
		}
		if(v=='x'){
		while(j<=polyonym->dx){
				i=0;
				set=0;
				printf("\nDegree %d:\n",j);
				while(i<=polyonym->dy){
					if(polyonym->matrix[j][i]>0){printf("+");}
					if(polyonym->matrix[j][i]!=0){
						set=1;
						if(polyonym->matrix[j][i]!=1 ||(polyonym->matrix[j][i]==1 && i==0)){printf("%d",polyonym->matrix[j][i]);}
						if(i!=0){
							printf("y");
							if(i!=1){printf("^%d",i);}
						}
					}
					i++;
				}
				if(set==0){printf("0");}
				j++;
			}
		}
	printf("\n");
}

// getDegree2() returns the degree of 'v'
int getDegree2(Polyonym2 * poly, char v){
	if (v=='x') {
		return poly->dx;
	}
	else {
		return poly->dy;
	}
}

// get_polymatrix2() returns value of position ( 'i' , 'j' ) in matrix
int get_polymatrix2(Polyonym2 * poly,int i,int j){
	return poly->matrix[i][j];
}
