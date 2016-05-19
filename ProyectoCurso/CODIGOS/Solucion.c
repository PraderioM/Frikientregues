#include <stdio.h>
#include "CalculNumeric.h"


#define tol 1.e-8
double f(double);
#define L 2*QuadraturaGaussChebyschev(f, -2., 2., 9) //aqui calculamos la longitud de la elipse.
double g(double);
double g1(double);
double h(double);

int main(){
	printf("Calculando la longitud de la elipse obtenemos como resultado\nL=%.10g\n\n", L);
	printf("El punto encontrado aproximando las integrales mediante integracion de polinomios ");
	/*Mostramos el cero de la función g obtenido aplicando el método de Newton con tolerancia 1.e-6.*/
	printf("de Splines es\n%.10g\n\n", Newton(g, g1, 0.5, 1.e-6));
	printf("Otra aproximación obtenida calculando las integrales mediante el método de quadratura ");
	/*Mostramos el cero de la función h obtenido aplicando el método de Newton con tolerancia 1.e-6.*/
	printf("de Gauss-Chebyschev viene dada por\n%.10g\n\n", Newton(h, g1, 0.5, 1.e-6));
	return 0;
}

/*esta función és la función sqrt(1+(f'(x))²) definida en la práctica.*/
double f(double x){
	return sqrt((64-15*x*x)/(4-x*x))/4;
}

/*esta funçión és la derivada de la función F definida en la pràctica.*/
double g1(double x){
	return 5*f(x);
}

/*esta funció aproxima por Splines la función F(x) definida en el problema.*/
double g(double x){
	double *N, *Polin, tol1=1.e-3; //tol1 sirve para que el último nodo interpolador se distancie del 2.
	int i;
	int n=abs(100*(2-tol1-x)); //calculamos el número total de nodos.
	N=NodesEquiespaiats(x, 2-tol1, n); //Definimos los nodos.
	Polin=PolinomiInterpoladorSplinesGaussSeidel(N, AvaluarFuncio(f,N,n), tol, n);//calculamos el polinomio.
	return L-5*IntegracioPolinomiSplines(N, Polin, n-1);//integramos el polinomio y devolvemos el resultado.
}

/*esta funciónaproxima mediante el método de cuadratura de Gauss-Chebyschev con 9 nodos la función F(x)
definida en el problema*/
double h(double x){
	return L-5*QuadraturaGaussChebyschev(f, x, 2., 113);
}