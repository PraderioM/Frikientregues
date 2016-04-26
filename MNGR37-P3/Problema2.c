#include <stdio.h>
#include "Interpolacio.h"

double Bessel(double);

/*el objetivo de este programa és aplicar el Algorismo de Neville con interpolación inversa para encontrar x_0
  tal que f(x_0)=0 donde f és la función desconocida presentada en el problema 2.*/
int main(){
	double X[12], Y[12], *X1, *Y1, x;
	int i, n;
	X[0]=0.281818559374385;
	X[1]=0.223890779141236;
	X[2]=0.166606980331990;
	X[3]=0.110362266922174;
	X[4]=0.055539784445602;
	X[5]=0.002507683297244;
	X[6]=-0.048383776468198;
	X[7]=-0.096804954397038;
	X[8]=-0.142449370046012;
	X[9]=-0.185036033364387;
	X[10]=-0.224311545791968;
	X[11]=-0.260051954901934;
	for (i=0; i<12; i++){
		Y[i]=1.9+0.1*i;
	}
	for (n=2; n<7; n+=2){
		X1=malloc(n*sizeof(double));
		Y1=malloc(n*sizeof(double));
		for (i=0; i<n; i++){
			X1[i]=X[i+6];
			Y1[i]=Y[i+6];
		}
		x=AlgorismeNeville(X1, Y1, 0., n);
		printf("\nEl resultado obtenido aplicando interpolación inversa de grado %d interpolando valores", (n-1));
		printf(" negativos de J_0(x) más próximos al cambio de signo de la función és\n%.16g\n", x);
		x=Bessel(x);
		printf("En este punto la función de Bessel de primera especie de orden 0 vale\n%g\n", x);
	}
	printf("\n");
	for (n=2; n<7; n+=2){
		X1=malloc(n*sizeof(double));
		Y1=malloc(n*sizeof(double));
		for (i=0; i<n; i++){
			X1[i]=X[i+6-n];
			Y1[i]=Y[i+6-n];
		}
		x=AlgorismeNeville(X1, Y1, 0., n);
		printf("\nEl resultado obtenido aplicando interpolación inversa de grado %d interpolando valores", (n-1));
		printf(" positivos de J_0(x) más próximos al cambio de signo de la función és\n%.16g\n", x);
		x=Bessel(x);
		printf("En este punto la función de Bessel de primera especie de orden 0 vale\n%g\n", x);
	}
	X[0]=0.166606980331990;
	X[1]=0.110362266922174;
	X[2]=0.055539784445602;
	X[3]=-0.048383776468198;
	X[4]=-0.096804954397038;
	X[5]=-0.185036033364387;
	Y[0]=2.1;
	Y[1]=2.2;
	Y[2]=2.3;
	Y[3]=2.5;
	Y[4]=2.6;
	Y[5]=2.8;
	printf("\n");
	for (n=2; n<7; n+=2){
		X1=malloc(n*sizeof(double));
		Y1=malloc(n*sizeof(double));
		for (i=0; i<n; i++){
			X1[i]=X[i+3-n/2];
			Y1[i]=Y[i+3-n/2];
		}
		x=AlgorismeNeville(X1, Y1, 0., n);
		printf("\nEl resultado obtenido aplicando interpolación inversa de grado %d interpolando valores", (n-1));
		printf(" de J_0(x) simétricos alrededor del cambio de signo de la función és\n%.16g\n", x);
		x=Bessel(x);
		printf("En este punto la función de Bessel de primera especie de orden 0 vale\n%g\n", x);
	}
}

/*escribimos la función de Bessel de primera especie de orden 0.*/
double Bessel(double x){
	return (1-x*x/4+x*x*x*x/64);
}