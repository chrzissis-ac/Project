#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// choosevar_bydeg() returns the variable with the highest degree
char choosevar_bydeg(int dx1, int dy1,int dx2, int dy2){
	int dx,dy;
	dx=(dx1>=dx2)*dx1+(dx1<dx2)*dx2;
	dy=(dy1>=dy2)*dy1+(dy1<dy2)*dy2;
	if(dx>=dy){return 'x';}
	else{return 'y';}
}

// choosehidden_bydeg() returns the variable with the lowest degree
char choosehidden_bydeg(int dx1, int dy1,int dx2, int dy2){
	int dx,dy;
	dx=(dx1>=dx2)*dx1+(dx1<dx2)*dx2;
	dy=(dy1>=dy2)*dy1+(dy1<dy2)*dy2;
	if(dx>=dy){return 'y';}
	else{return 'x';}
}

// generatefunctions() creates random functions according to the following format c0 +- c1 y +- c2 x +- c3 y x +- ... +- ck y^a1 x^a2 (no spaces in output) and stores them in 'file'
void generatefunctions(int d1,int d2, FILE * file){
	int dx,dy,d;
	d=d1*(d1>=d2)+d2*(d2>d1);
	dx=rand()%(d1+1);
	dy=d1-dx;
	int i=0,j=0,a=0,degx=0,degy=0;
	int setx=0,sety=0,setf=0;
	char func[300*(d+1)*(d+1)];
	char temp[300*(d+1)*(d+1)];
	char temp2[30*(d+1)*(d+1)];
	int synt=0;
	d=d1;
while(a<2){	
	i=0;j=0;setx=0;sety=0;synt=0;setf=0;
	degx=0;degy=0;
	strcpy(func,"");
	strcpy(temp,"");

	if(a==1){
		d=d2;
		dx=rand()%(d+1);
		dy=d-dx;
	}
	while(i<=dx){
		j=0;
		while(j<=dy){
			if(rand()%4<2 || ( (setx==0 || sety==0) && i==dx && j==dy ) || (setf==0 && i==dx && j==dy)){
				setf=1;
				if(i>=degx){degx=i;}
				if(j>=degy){degy=j;}
				if(i==dx){setx=1;}
				if(j==dy){sety=1;}
				if(rand()%2==0){
					strcat(temp,"+");
				}
				else{strcat(temp,"-");}
				while((synt=(rand()%30))<=0);
				if(synt!=1){
					strcpy(temp2,"");
					sprintf(temp2,"%d",synt);
					strcat(temp,temp2);
				}
				if(i!=0){
					strcat(temp,"x");
					if(i!=1){
						strcpy(temp2,"");
						sprintf(temp2,"^%d",i);
						strcat(temp,temp2);
					}
				}
				if(j!=0){
					strcat(temp,"y");
					if(j!=1){
						strcpy(temp2,"");
						sprintf(temp2,"^%d",j);
						strcat(temp,temp2);
					}
				}
				strcat(func,temp);
				strcpy(temp,"");
			}
			j++;
		}
		i++;
	}
//	fprintf(file,"%d\n",d);
	fprintf(file,"%s\n",func);
	a++;
}
	fseek(file,0,SEEK_SET);
}

// input() reads and stores in 'function' a double-variable polyonym with known degrees for x and y
void input(FILE * file,int * d,char ** function){
	char temp[300];
	if(temp==NULL){perror("Function temp allocation");exit(0);}
	(*function)=NULL;
	(*function)=malloc(sizeof(char)*300*((*d)+1)*((*d)+1));
	if((*function)==NULL){perror("Function allocation");exit(0);}

	if(file==stdin){
		printf("Give degree of function\n");
		fgets(temp,300,file);
		(*d)=atoi(temp);
	}
	if(file==stdin){printf("Give function f\n");}
	strcpy(temp,"");
	fgets(*function,300*((*d)+1)*((*d)+1),file);
}

// menushow() shows a multitude of options that are associated with the usage of the program
void menushow(int * input){
	char temp[300];
	printf("Give:\n");
	printf("1-\"S\" to print Sylvester Matrix!\n");
	printf("2-Any number \"#\" to print the corresponding Sylvester Matrix to the given Grade\n");
	printf("3-\"V\" for Vector multiplication\n");
	printf("4-\"O\" In case there is a change of variable, start printing the other matrix for each given No\n");
	printf("5-\"C\" Print Companion matrix or Generalized Eigenproblem Matrices\n");
	printf("6-\"T\" to terminate\n");
	fgets(temp,300,stdin);
	if(strcmp(temp,"S\n")==0 || strcmp(temp,"S")==0 || strcmp(temp,"s\n")==0 || strcmp(temp,"s")==0){
		*input=-1;
	}
	else if(strcmp(temp,"T\n")==0 || strcmp(temp,"T")==0 || strcmp(temp,"t\n")==0 || strcmp(temp,"t")==0){
		*input=-2;
	}
	else if(strcmp(temp,"V\n")==0 || strcmp(temp,"V")==0 || strcmp(temp,"v\n")==0 || strcmp(temp,"v")==0){
		*input=-3;
	}
	else if(strcmp(temp,"O\n")==0 || strcmp(temp,"O")==0 || strcmp(temp,"o\n")==0 || strcmp(temp,"o")==0){
		*input=-5;
	}
	else if(strcmp(temp,"C\n")==0 || strcmp(temp,"C")==0 || strcmp(temp,"c\n")==0 || strcmp(temp,"c")==0){
		*input=-6;
	}
	else if( (atoi(temp)==0 &&  strcmp(temp,"0\n")!=0)   ){
		*input=-4;
	}
	else{*input=atoi(temp);}
}


void from2Dto1D_double(double ** source, double ** target, int dimx, int dimy){
	int i=0,j=0;
	(*target)=NULL;
	(*target)=malloc(sizeof(double)*dimx*dimy);
	if((*target)==NULL){perror("malloc 2Dto1D conversion");exit(0);}
	while(i<dimx){
		j=0;
		while(j<dimy){
			(*target)[i*dimy+j]=source[i][j];
			j++;
		}
		i++;
	}

}



void from1Dto2D_double(double * source, double *** target, int dimx, int dimy){
	int i=0,j=0;
	(*target)=NULL;
	(*target)=malloc(sizeof(double)*dimx);
	if((*target)==NULL){perror("malloc 1Dto2D conversion 1D");exit(0);}
	for (i=0 ; i<dimx ; i++) {
		(*target)[i]=NULL;
		(*target)[i]=malloc(sizeof(double)*dimy);
		if ((*target)[i]==NULL) {perror("malloc 1Dto2D conversion 2D");exit(0);}
	}
	i=0;
	while(i<dimx){
		j=0;
		while(j<dimy){
			(*target)[i][j]=source[i*dimy+j];
			j++;
		}
		i++;
	}
}
