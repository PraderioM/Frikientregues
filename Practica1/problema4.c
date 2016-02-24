#include <stdio.h>

int main(){
	int i, n;
	float y;
	double x;
	n=6000;
	printf ("\nAnem a calcular una aproximació numérica de la sèrie S=sum_{k=0}^{infty}(-1)^{k+1}/k² que sabem dona");
	printf (" com a resultat el valor pi²/12=0.822467033424113...\n");
	printf ("Per fer-ho sumarem els primers %d termes de tres formes diferents i amb precisio simple i doble.\n", 2*n);
	printf ("La primera forma de fer-ho serà sumant els termes en ordre creixent obtenint aixis el següents resultats");
	y=0;
	x=0;
	for (i=2; i<=2*n; i+=2){
		y-=1./(i*i);
		x-=1./(i*i);
	}
	for (i=2*n-1; i>=1; i-=2){
		y+=1./(i*i);
		x+=1./(i*i);
	}
	printf ("\n\n%f\nEn el cas de la precisió simple\n%.9f\nEn el cas de la precisió doble.\n",y,x);
	printf ("\nLa segona forma de fer-ho serà sumant els termes en ordre decreixent obtenint aixis el següents resultats");
	y=0;
	x=0;
	for (i=1; i<=2*n-1; i+=2){
		y+=1./(i*i);
		x+=1./(i*i);
	}
	for (i=2*n; i>=2; i-=2){
		y-=1./(i*i);
		x-=1./(i*i);
	}
	printf ("\n\n%f\nEn el cas de la precisió simple\n%.9f\nEn el cas de la precisió doble.\n",y,x);
	printf ("\nLa tercera forma de fer-ho serà sumant de forma creixent en mòdul.");
	printf (" i finalment sumar els dos resultats\n");
	y=0;
	x=0;
	double s=-1;
	for (i=2*n; i>=1; i--){
		y+=s/(i*i);
		x+=s/(i*i);
		s=-s;
	}
	printf ("\n\n%f\nEn el cas de la precisió simple\n%.9f\nEn el cas de la precisió doble.\n",y,x);
}