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
	while (fabs(b-a)>ZERO && i<1000){
		aux=a-f(a)*(b-a)/(f(b)-f(a));
		s=f(aux);
		if (s>0){
			a=aux;
		}
		else if (s==0){
			printf("l'arrel és exactament %.16g llevat del error de representació.\n", aux);
			return 0;
		}
		else{
			b=aux;
		}
		i++;
	}
	printf("Amb %d iteracions hem arribat al resultat\n%.16g\n amb una precisió de %.16g\n", i, aux, fabs(b-a));
}


//fem una funció que avalui la funció que volem en un punt i retorni el seu valor
double f(double x){
	return pow(x,3)-x-400;
}