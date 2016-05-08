#include <stdio.h>
#include "CalculNumeric.h"

f1 DefinirFuncioF();
double f(double);

int main(){
	double x, tol=1.e-6, *Polin, *N, X[181], Y[181];
	int i, n=4;
	char s[80];
	f1 g, g1;
	N=NodesEquiespaiats(x, 2, n);
	Polin=PolinomiInterpoladorSplinesLU(N, AvaluarFuncio(f,N,n), n);
	for (i=0; i<181; i++){
		X[i]=-0.989+i*0.011;
		Y[i]=AvaluarSplines(N,Polin, X[i]);
	}
	sprintf(s, "prova");
	DibuixarGrafica(X, Y, 181, s);
	g=DefinirFuncioF();
	g1=MultiplicarFuncioEscalar(f, 5.);
	x=Newton(g, g1, 1.5, tol);
	printf("\n%.10g\n\n", x);
}

double f(double x){
	return sqrt((64-15*x*x)/(4-x*x))/4;
}

f1 DefinirFuncioF(){
	double L, *N, *Polin, tol=1.e-6;
	int n=4;
	L=4*QuadraturaGaussChebyschev(f, 0., 2., 9);
	double h(double x){
		N=NodesEquiespaiats(x, 2, n);
		Polin=PolinomiInterpoladorSplinesGaussSeidel(N, AvaluarFuncio(f,N,n), tol, n);
		return L-5*IntegracioPolinomiSplines(N, Polin, n-1);
	}
	return h;
}