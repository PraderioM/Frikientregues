#include <stdio.h>
#include "CalculNumeric.h"

double f(double);

int main(){
	printf("Calculando la longitud de la elipse obtenemos como resultado\nL=%.10g\n\n", 2*QuadraturaGaussChebyschev(f, -2., 2., 9));
	return 0;
}

/*esta función és la función sqrt(1+(f'(x))²) definida en la práctica.*/
double f(double x){
	return sqrt((64-15*x*x)/(4-x*x))/4;
}