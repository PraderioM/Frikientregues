#include <stdio.h>
#include "CalculNumeric.h"


#define tol 1.e-8
double f(double);
#define L 2*QuadraturaGaussChebyschev(f, -2., 2., 9) //aqui calculamos la longitud de la elipse.
double g(double);
double g1(double);

int main(){
	double x;
	x=Newton(g, g1, 0.4, tol);
	printf("El punto encontrado és");
	printf("\n%.10g\n\n", x);
	printf("En este punto la función F definida en el problema vale\n");
	printf("%.10g\n\n", g(x));
	return 0;
}

/*esta función és la funció sqrt(1+(f'(x))²) definida en la práctica.*/
double f(double x){
	return sqrt((64-15*x*x)/(4-x*x))/4;
}

/*esta funçión és la derivada de la función F definida en la pràctica.*/
double g1(double x){
	return 5*f(x);
}

/*esta funció representa la función F(x) definida en el intervalo.*/
double g(double x){
	double *N, *Polin, tol1=1.e-3;
	int n=abs(100*(2-tol1-x));
	N=NodesEquiespaiats(x, 2-tol1, n);
	Polin=PolinomiInterpoladorSplinesGaussSeidel(N, AvaluarFuncio(f,N,n), tol, n);
	return L-5*IntegracioPolinomiSplines(N, Polin, n-1);
}