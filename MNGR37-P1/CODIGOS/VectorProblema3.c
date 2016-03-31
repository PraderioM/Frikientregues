#include <stdio.h>
#include <math.h>
/*Aquest programa genera una llista de n dades que ens serveixen per respondre a les preguntes del problema 3*/
int main(){
	int i, n;
	double x, mig, A;
	A=0.001;
	mig=10000;
	n=1000;
	/*la idea és donar molts nombres similars (n haurà de ser gran) amb una variança prou petita (A haurà de ser petita)
	 això provocarà errors de cancelaciò en el mètode de un bucle que es notaràn mes si el valor mig és més gran 
	 (mig haurà de ser gran) en cuant els errors de cancelació augmente en error relatiu*/
	for (i=0; i<n; i++){
		/*Per fer-ho senzillament generarem nombres al voltant de mig i que estàn com a molt a distància 2*A 
		entre ells tal i com indica la amplitud del sinus*/
		x=mig+A*sin(i);
		/*Els imprimirem tots desde el terminal indicarem que es guardin en un fitxer.*/
		printf("%lf\n", x);
	}
}