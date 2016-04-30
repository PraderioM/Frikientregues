#include <stdio.h>
#include "Interpolacio.h"

double f(double);
double* longitudintervalos(double*, int);
double* calculodelamu(double*, int);
double* calculodelalanda(double*, int);
double* calculodelad(double*, double*, int);
double* construirdiagonales(double*, double*, int);
double* construirmatriz(double*, double*, int);
double* calculobeta(double*, double*, double*, int);
double* calculodelta(double*, double*, int);
double EvaluarSplines(double*, double*, double*, double*, double*, double, int);

int main(){
	double *x1,*x2,*y1,*y2,*h1,*h2,*mu1,*mu2, *diagonal, *matriz1, *matriz2, *m1, *m2,*landa1,*landa2,*d1,*d2,*beta1,*beta2,*delta1,*delta2, X[181], *fx, px1[181], px2[181]; 
	int i, k;
	char s[80];
	printf("Cuantos nodos tienes?");
	scanf("%d",&k);
	x1=NodesChebyschev(-1, 1, k);
	x2=NodesEquiespaiats(-1,1, k);
	y1=AvaluarFuncio(f , x1, k);
	y2=AvaluarFuncio(f , x2, k);
	h1=longitudintervalos(x1,k);
	h2=longitudintervalos(x2,k);
	mu1=calculodelamu(h1,k);
	mu2=calculodelamu(h2,k);
	landa1=calculodelalanda(h1,k);
	landa2=calculodelalanda(h2,k);
	d1=calculodelad(h1,y1,k);
	d2=calculodelad(h2,y2,k);

	matriz1=construirmatriz(landa1, mu1, k);
	matriz2=construirmatriz(landa2, mu2, k);
	m1=ResoldreSistemaLineal(matriz1, d1, k-2);
	m2=ResoldreSistemaLineal(matriz2, d2, k-2);

	//diagonal=construirdiagonales(mu1, mu2, k);
	//m1=ResoldreMatriuTridiagonal(diagonal, landa1, mu1, d1, k-2);
	//m2=ResoldreMatriuTridiagonal(diagonal, landa2, mu2, d2, k-2);
	
	beta1=calculobeta(y1,h1,m1,k);
	beta2=calculobeta(y2,h2,m2,k);
	delta1=calculodelta(h1,m1,k);
	delta2=calculodelta(h2,m2,k);
	/*construimos el vector de puntos donde evaluaremos f y los polinomios interpoladores*/
	X[0]=-0.989;
	for (i=1; i<181; i++){
		X[i]=X[i-1]+0.011;
	}
	/*Avaluem f en els punts de X*/
	fx=AvaluarFuncio(f, X, 181);
	for (i=0; i<181; i++){
		px1[i]=EvaluarSplines(x1, y1, beta1, m1, delta1 , X[i], k);
		px1[i]=fabs(px1[i]-fx[i]);
		px2[i]=EvaluarSplines(x2, y2, beta2, m2, delta2 , X[i], k);
		px2[i]=fabs(px2[i]-fx[i]);
	}
	sprintf(s, "Error Splines Chebyschev");
	DibuixarGrafica(X, px1, 181, s);
	sprintf(s, "Error Splines equidistantes");
	DibuixarGrafica(X, px2, 181, s);
	return 0;
}

double f(double x){
	return 1/(1+25*x*x);
}

double* longitudintervalos(double* x, int n){
	double* ampli;
	int i;
	ampli=malloc((n-1)*sizeof(double));
	for (i=0; i<n-1; i++){
		ampli[i]=x[i+1]-x[i];
	}
	return ampli;
}

double* calculodelamu(double* x,int n){
	double* ampli;
	int i;
	ampli=malloc((n-2)*sizeof(double));
	for (i=0; i<n-2; i++){
		ampli[i]=x[i]/(x[i+1]+x[i]);
	}
	return ampli;
}

double* calculodelalanda(double* x,int n){
	double* ampli;
	int i;
	ampli=malloc((n-2)*sizeof(double));
	for (i=0; i<n-2; i++){
		ampli[i]=x[i+1]/(x[i+1]+x[i]);
	}
	return ampli;
}

double* calculodelad(double* h,double* y,int n){
	double* ampli;
	int i;
	ampli=malloc((n-2)*sizeof(double));
	for (i=0; i<n-2; i++){
		ampli[i]=6*((y[i+2]-y[i+1])/h[i+1]-(y[i+1]-y[i])/h[i])/(h[i]+h[i+1]);
	}
	return ampli;
}

double* construirmatriz(double* landa, double* mu, int n){
	int i;
	double *ampli;
	ampli=malloc((n-2)*(n-2)*sizeof(double));
	for (i=0; i<(n-2)*(n-2); i++){
		ampli[i]=0;
	}
	for (i=0; i<(n-3); i++){
		ampli[(n-2)*i+i]=2;
		ampli[(n-2)*i+i+1]=landa[i];
		ampli[(n-2)*(i+1)+i]=mu[i+1];
	}
	ampli[(n-2)*(n-2)-1]=2;
	return ampli;
}

double* construirdiagonales(double* mu1, double* mu2, int n){
	double* ampli;
	int i;
	ampli=malloc((n-2)*sizeof(double));
	for(i=0;i<n-3;i++){
		ampli[i]=2;
		mu1[i]=mu1[i+1];
		mu2[i]=mu2[i+1];
	}
	ampli[n-2]=2;
	return ampli;
}

double* calculobeta(double* y,double* h,double* m,int n){
	double* ampli;
	int i;
	ampli=malloc((n-1)*sizeof(double));
	for (i=1; i<n-2; i++){
		ampli[i]=(y[i+1]-y[i])/h[i]-h[i]*(2*m[i-1]+m[i])/6;
	}
	ampli[0]=(y[1]-y[0])/h[0]-h[0]*m[0]/6;
	ampli[n-2]=(y[n-1]-y[n-2])/h[n-2]-h[n-2]*m[n-3]/3;
	return ampli;
}

double* calculodelta(double* h,double* m,int n){
	double* ampli;
	int i;
	ampli=malloc((n-1)*sizeof(double));
	for (i=1; i<n-2; i++){
		ampli[i]=(m[i]-m[i-1])/(6*h[i]);
	}
	ampli[0]=m[0]/(6*h[0]);
	ampli[n-2]=-m[n-3]/(6*h[n-2]);
	return ampli;
}

double EvaluarSplines(double* X, double* y, double* beta, double* m, double* delta, double x, int n){
	int i=0;
	double res, gamma;
	while (X[i]<x){
		i++;
	}
	if (i==n){
		printf("shit\n\n");
	}
	i--;
	if (i==0 || i==(n-1)){
		gamma=0;
	}
	else{
		gamma=m[i-1]/2;
	}
	res=x-X[i];
	res=y[i]+res*(beta[i]+res*(gamma+res*delta[i]));
	return res;
}