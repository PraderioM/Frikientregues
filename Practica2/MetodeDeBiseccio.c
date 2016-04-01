#include <stdio.h>
#include <math.h>

#define ZERO 1.e-16

double f(double);

int main(){
	int i;
	double a, b, aux, s;
	a=2;
	b=8;
	if (f(a)>f(b)){
		aux=b;
		b=a;
		a=aux;
	}
	i=0;
	while (fabs(b-a)>ZERO && i<100){
		printf("%.16g", fabs(b-a));
		aux=(a+b)/2;
		s=f(aux);
		if (s>0){
			b=aux;
		}
		else if (s=0){
			printf("l'arrel és exactament %.16g\n", aux);
			return 0;
		}
		else{
			a=aux;
		}
		i++;
	}
	printf("Amb %d iteracions hem arribat al resultat\n%.16g\n amb una precisió de %.16g\n", i, aux, fabs(b-a));
}

double f(double x){
	return pow(x,3)-x-400;
}