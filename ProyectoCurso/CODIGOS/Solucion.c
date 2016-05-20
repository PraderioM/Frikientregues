#include <stdio.h>
#include "CalculNumeric.h"


#define tol 1.e-8 //este parametro nos sirve como condición de parada para el método de Gauss-Seidel.
double f(double);
#define L 2*QuadraturaGaussChebyschev(f, -2., 2., 503) //aqui calculamos la longitud de la elipse.
double g(double);
double g1(double);
double h(double);
double h1(double);

int main(){
	printf("Calculando la longitud de la elipse obtenemos como resultado\nL=%.10g\n\n", L);
	printf("El punto encontrado aproximando las integrales mediante integracion de polinomios ");
	/*Mostramos el cero de la función g obtenido aplicando el método de Newton con tolerancia 1.e-6.*/
	printf("de Splines es\n%.10g\n\n", Newton(g, g1, 0.5, 1.e-6));
	printf("Reformulando la funcion L_{EA}(x) tal y como se indica en la memoria obtenemos ");
	/*Mostramos el cero de la función h obtenido aplicando el método de Newton con tolerancia 1.e-6.*/
	printf("\n%.10g\n\nAproximando las integrales haciendo uso de ", Newton(h, g1, 0.5, 1.e-6));
	printf("polinomios interpoladores de Splines y\n%.10g\n\nAproximando ", Newton(h1, g1, 0.5, 1.e-6));
	printf("las integrales mediante cuadratura de Gauss-Chebyschev\n\n");
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
	double *N, *Polin, h=1.e-3, tol1=1.e-4;//tol1 sirve para separar el último nodo interpolador del 2.
	int i;
	int n=abs((2-tol1-x)/h); //calculamos el número total de nodos.
	N=NodesEquiespaiats(x, 2-tol1, n); //Definimos los nodos.
	Polin=PolinomiInterpoladorSplinesGaussSeidel(N, AvaluarFuncio(f,N,n), tol, n);//calculamos el polinomio.
	return L-5*IntegracioPolinomiSplines(N, Polin, n-1);//integramos el polinomio y devolvemos el resultado.
}

/*esta funció aproxima por Splines la función F(x) reformulada como F(x)=5int_{0}^xg(t)dt -L/4.*/
double h(double x){
	double *N, *Polin, h=0.5e-2;
	int i;
	int n=abs(x/h); //calculamos el número total de nodos.
	N=NodesEquiespaiats(0, x, n); //Definimos los nodos.
	Polin=PolinomiInterpoladorSplinesGaussSeidel(N, AvaluarFuncio(f,N,n), tol, n);//calculamos el polinomio.
	return 5*IntegracioPolinomiSplines(N, Polin, n-1)-L/4;//integramos el polinomio y devolvemos el resultado.
}

/*esta función aproxima mediante el método de cuadratura de Gauss-Chebyschev con 9 nodos la función F(x)
reformulada como F(x)=(5/2)int_{-x}^xg(t)dt -L/4*/
double h1(double x){
	return 5*QuadraturaGaussChebyschev(f, -x, x, 1115)/2-L/4;
}