#include <stdio.h>
#include <math.h>

int main(){
	int i;
	double a, b, aux, s;
	a=0.5;
	b=2;
	for (i=0; i<1000; i++){
		aux=(a+b)/2;
		s=(sin(a)-a*a/2)*(sin(aux)-aux*aux/2);
		if (s>0){
			a=aux;
		}
		else if (s=0){
			printf("l'arrel és exactament %.12g\n", aux);
			return 0;
		}
		else{
			b=aux;
		}
	}
	printf("l'arrel és %.12g amb 1000 iteracions\n", a);
}