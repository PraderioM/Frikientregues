#include <stdio.h>
#include <math.h>

int main(){
	int i;
	double x;
	/*la idea és donar molts nombres similars amb una variança prou petita això provocarà errors de eliminació
	en el mètode de un bucle*/
	for (i=0; i<100; i++){
		/*Per ferho senzillament generarem nombres al voltant del 10000 i que estàn com a molt a distància 2/1000 
		entre ells tal i com indica la amplitud del sinus*/
		x=10000+sin(i)/1000;
		/*Els imprimirem tots desde el terminal indicarem que es guardin en un fitxer.*/
		printf("%lf\n", x);
	}
}