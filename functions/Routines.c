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
void generatefunctions(int dx,int dy, FILE * file){
	int i=0,j=0,a=0,degx=0,degy=0;
	int setx=0,sety=0,setf=0;
	char func[300*(dx+1)*(dy+1)];
	char temp[300*(dx+1)*(dy+1)];
	char temp2[30*(dx+1)*(dy+1)];
	int synt=0;
	srand(time(NULL));
	
while(a<2){	
	i=0;j=0;setx=0;sety=0;synt=0;setf=0;
	degx=0;degy=0;
	strcpy(func,"");
	strcpy(temp,"");
	while(i<=dx){
		j=0;
		while(j<=dy){
			if(rand()%4<1 || ( (setx==0 || sety==0) && i==dx && j==dy && a==1 ) || (setf==0 && i==dx && j==dy)){
				setf=1;
				if(i>=degx){degx=i;}
				if(j>=degy){degy=j;}
				if(i==dx){setx=1;}
				if(j==dy){sety=1;}
				if(rand()%2==0){
					strcat(temp,"+");
				}
				else{strcat(temp,"-");}
				while((synt=(rand()%250))<=0);
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
	fprintf(file,"%d\n",degx);
	fprintf(file,"%d\n",degy);
	fprintf(file,"%s\n",func);
	a++;
}
	fseek(file,0,SEEK_SET);
}

// input() reads and stores in 'function' a double-variable polyonym with known degrees for x and y
void input(FILE * file,int * dx,int * dy,char ** function){
	char temp[300];
	if(temp==NULL){perror("Function temp allocation");exit(0);}
	(*function)=NULL;
	(*function)=malloc(sizeof(char)*300*((*dx)+1)*((*dy)+1));
	if((*function)==NULL){perror("Function allocation");exit(0);}

	if(file==stdin){printf("Give degree of x\n");}
	fgets(temp,300,file);
	(*dx)=atoi(temp);

	if(file==stdin){printf("Give degree of y\n");}
	fgets(temp,300,file);
	(*dy)=atoi(temp);

	if(file==stdin){printf("Give function f\n");}
	strcpy(temp,"");
	fgets(*function,300*((*dx)+1)*((*dy)+1),file);
}

// menushow() shows a multitude of options that are associated with the usage of the program
void menushow(int * input){
	char temp[300];
	printf("Give:\n");
	printf("1-\"S\" to print Sylvester Matrix!\n");
	printf("2-Any number \"#\" to print the corresponding Sylvester Matrix to the given Grade\n");
	printf("3-\"V\" for Vector multiplication\n");
	printf("4-\"T\" to terminate\n");
	fgets(temp,300,stdin);
	if(strcmp(temp,"S\n")==0 || strcmp(temp,"S")==0 || strcmp(temp,"s\n")==0 || strcmp(temp,"s")==0){
		*input=-1;
		printf("The Sylvester Matrix is:\n\n");
	}
	else if(strcmp(temp,"T\n")==0 || strcmp(temp,"T")==0 || strcmp(temp,"t\n")==0 || strcmp(temp,"t")==0){
		*input=-2;
		printf("Terminating\n");
	}
	else if(strcmp(temp,"V\n")==0 || strcmp(temp,"V")==0 || strcmp(temp,"v\n")==0 || strcmp(temp,"v")==0){
		*input=-3;
	}
	else if( (atoi(temp)==0 &&  strcmp(temp,"0\n")!=0)   ){
		*input=-4;
		printf("Wrong input! Please read the instructions and try again!\n");
	}
	else{*input=atoi(temp);}
}