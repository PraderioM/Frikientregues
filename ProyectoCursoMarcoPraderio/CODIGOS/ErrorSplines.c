#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CalculNumeric.h"

double f(double);
double ErrorIntegracionPorSplines(double*, double*, double, int);

int main(){
	double *N, *Polin, tol, h, error;
	int i;
	// Pedimos por pantalla la longitud de los intervalos interpoladores de Splines.
	printf("Introduce la longitud entre los nodos consecutivos utilizados para construir el polinomio ");
	printf("interpolador cúbico natural de Splines:");
	scanf("%lf", &h);
	printf("Introduce la distancia entre el extremo superior de la integral y el 2:");
	scanf("%lf", &tol);
	h=fabs(h); //evitamos imputs que puedan causar problemas.
	tol=fabs(tol); //evitamos imputs que puedan causar problemas.
	int n=abs((2-tol)/h); //calculamos el número total de nodos.
	N=NodesEquiespaiats(0, 2-tol, n); //definimos los nodos.
	Polin=PolinomiInterpoladorSplinesGaussSeidel(N, AvaluarFuncio(f,N,n), 1.e-8, n);//calculamos el polinomio.
	error=ErrorIntegracionPorSplines(N, Polin, tol, n); //calculamos el error de integración.
	printf("\nEl error cometido aproximando la integral de 0 a 2 de sqrt(1+(f'(x))²) mediante la integral ");
	printf("de 0 a %g del polinomio interpolador cúbico natural de splines con distància %g ", (2-tol), h);
	printf("entre sus nodos está acotado por %g.\n\n", error);
	return 0;
}

/*esta función és la función sqrt(1+(f'(x))²) definida en la práctica.*/
double f(double x){
	return sqrt((64-15*x*x)/(4-x*x))/4;
}

/*Esta función calcula el error cometido al integrar f de 0 a 2-tol utilizando el polinomio interpolador
  por splines obtenido a partir de los n nodos de guardados en N.*/
double ErrorIntegracionPorSplines(double* N, double* Polin, double tol, int n){
	double sumaerror=0, errormax, error, d, x;
	int i, j, m=3;
	for (i=0; i<(n-1); i++){
		errormax=0;
		d=N[i+1]-N[i]; //guardamos la distancia entre los nodos (serà siempre la misma).
		x=N[i]+d/(m+2); //guardamos el primer punto en el que miraremos la diferencia.
		for (j=0; j<m; j++){//buscamos en cada intervalos entre m valores el que se aleja mas del valor real.
			error=fabs(f(x)-AvaluarSplines(N, Polin, x));//miramos la diferencia.
			if (error==NAN){
				printf("Error distancia a dos demasiado pequeña\n");
			}
			if (error>errormax){//actualizamos el error máximo.
				errormax=error;
			}
			x+=d/(m+2);//miramos el siguiente punto.
		}
		sumaerror+=d*errormax;
	}
	sumaerror+=sqrt((tol*(4+tol*(30-tol*15)))/(4-tol))/2;//sumamos la cota del error de truncamiento.
	return sumaerror; //devolvemos una cota del error de integración.
}