#include <stdio.h>
#include <math.h>

int main(){
	int i;
	double x;
	/*la idea és donar molts nombres similars amb una variança prou petita això provocarà errors de eliminació
	en el mètode de un bucle*/
	for (i=0; i<100; i++){
		x=10000+sin(i)/100;
		printf("%lf\n", x);
	}
}