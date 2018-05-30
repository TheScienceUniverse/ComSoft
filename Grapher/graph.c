/*
 * Consult the Help Page: help.txt in the same directory
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.1415629
#define N 250

double mxx, mxy;

//...Please return a NON_INFINITE Value...
	//(Please don't send DIVIDE_BY_ZERO)
double f(double x){ 
	return sin(2*x)*cos(x);
}

double mod(double x);
int x2gx(double x), y2gy(double x);
double gx2x(int x);

int main(void){
	int s;		// CLI Status
	FILE *fp;	// File Pointer

	if((fp=fopen("xy.txt","w+"))==NULL){
		perror("File opening ERROR\n");
		exit(1);
	}

	double lr,ur,x,fx;
	int i;
	
	printf("Lower Range := ");
	scanf("%lf",&lr);
	printf("Upper Range := ");
	scanf("%lf",&ur);

	mxx=mod((mod(lr)>mod(ur))?lr:ur);
	printf("MxX := %lf\n",mxx);

	mxy=f(lr);

	lr=x2gx(lr), ur=x2gx(ur);
	printf("%d %d\n",(int)lr,(int)ur);

	for(i=lr+1; i<=ur; i++){
		x=gx2x(i);
		fx=f(x);
		if(mxy<fx)
			mxy=fx;
//		printf("%d\t%lf\t%lf\n",i,x,fx);
	}
	printf("MxY := %lf\n",ceil(mxy));

	mxy=ceil(mxy);
	printf("%d %d\n",x2gx(mxx),y2gy(mxy));

	for(i=lr; i<=ur; i++){
		x=gx2x(i);
		fx=f(x);
//		printf("%d %lf %lf %d\n",i,x,fx,y2gy(fx));
		fprintf(fp,"%d %d\n",i+N,N-y2gy(fx));
	}
	fclose(fp);

	s=system("javac plot.java");
	s=system("java plot xy.txt");
	s=system("rm *.class xy.txt");

	return 0;
}
double mod(double x){
	return (x<0)?-x:x;
}
int x2gx(double x){
	return (int)(N*x/mxx);
}
int y2gy(double y){
	return (int)(N*y/mxy);
}
double gx2x(int gx){
	return mxx*gx/N;
}
