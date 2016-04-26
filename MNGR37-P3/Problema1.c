#include <stdio.h>
#include <math.h>
#include "Interpolacio.h"

double f(double);
double* CalcularDiferencia(double*, double*, double*, int, int);


/*El objetivo de este programa és realizar los calculos relacionados con el problema 1 de la pràctica 3
  Para ello haremos uso de la libreria Interpolacio.h la cual debe estar en la misma carpeta que este programa
  para que se pueda compilar*/
int main(){
	/*els vectors fx i px guardaran respectivamente los resultados de evaluar la función f i los polinomios
	interpoladores en los puntos guardados en X i descritos en el ejercicio.*/
	double *fx, *px, X[181];
	/*en el vector N guardaremos los nodos en los que se interpola.*/
	double *N;
	/*s guardarà los títulos de las gràficas.*/
	char s[80];
	int i, n;
	/*construimos el vector de puntos donde evaluaremos f y los polinomios interpoladores*/
	for (i=0; i<181; i++){
		X[i]=-0.989+i*0.011;
	}
	/*Avaluem f en els punts de X*/
	fx=AvaluarFuncio(f, X, 181);
	n=4;
	while (n<65){
		/*Calculamos los nodos equiespaiados*/
		N=NodesEquiespaiats(-1,1,n);
		/*calculamos la diferencia entre el polinomio interpolador y la función*/
		px=CalcularDiferencia(N, X, fx, n, 181);
		/*dibujamos la gràfica*/
		sprintf(s,"Polinomio Interpolador con %d nodos equiespaiados",n); //escribimos el título de la gràfica.
		DibuixarGrafica(X,px,181, s);
		/*Calculamos los nodos de Chebyschev*/
		N=NodesChebyschev(-1,1,n);
		/*calculamos la diferencia entre el polinomio interpolador y la función*/
		px=CalcularDiferencia(N, X, fx, n, 181);
		/*dibujamos la gràfica*/
		sprintf(s, "Polinomio Interpolador con %d nodos de Chebyschev",n); //escribimos el título de la gràfica
		DibuixarGrafica(X,px,181, s);
		n*=2;
	}
	return 0;
}

/*hacemos una función que actue como la función de R a R presentada en el ejercicio f(x)=1/(1+25x²)*/
double f(double x){
	return 1/(1+25*x*x);
}

/*esta función se encarga de calular el polinomio interpolador para unos puntos dados, calcular el valor del
polinomio en otro conjunto de puntos y calcular el valor absoluto de la diferencia entre el valor del polinomio y
el de la función en esos puntos.
Toma como parametros los puntos donde interpolar, los puntos donde mirar la diferencia, el valor de la función en estos
puntos y dos enteros que indican la cantidad de puntos*/
double* CalcularDiferencia(double* N, double* X, double* fx, int n, int m){
	double *px, *P;
	int i;
	px=malloc(m*sizeof(double));
		/*Calculamos el polinomio interpolador de Hermite utilizando los puntos de N para interpolar*/
		P=PolinomiInterpoladorHermite(N, AvaluarFuncio(f,N,n),n, 0);
		/*calculamos |f(x)-p(x)| para los puntos guardados en X*/
		for (i=0; i<m; i++){
			px[i]=AvaluarPolinomi(P, n, X[i]);
			px[i]=fabs(px[i]-fx[i]);
		}
	return px;
}