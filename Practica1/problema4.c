#include <stdio.h>

int main(){
	int i, n;
	float y;
	double x;
	n=6000;
	/*Imprimim per pantalla una descripció del primer mètode que farem servir per sumar els termes de la série
	S=sum_{k=0}^{infty}(-1)^{k+1}/k²*/
	printf ("\nAnem a calcular una aproximació numérica de la sèrie S=sum_{k=0}^{infty}(-1)^{k+1}/k² que sabem dona");
	printf (" com a resultat el valor pi²/12=0.822467033424113...\n");
	printf ("Per fer-ho sumarem els primers %d termes de tres formes diferents i amb precisio simple i doble.\n", 2*n);
	printf ("La primera forma de fer-ho serà sumant els termes en ordre creixent obtenint aixis el següents resultats");
	/*Apliquem el mètode descrit realitzant el càlcul amb precisió simple (y) i doble (x)*/
	y=0;
	x=0;
	/*Sumem els termes negatius de forma decreixent en mòdul*/
	for (i=2; i<=2*n; i+=2){
		y-=1./(i*i);
		x-=1./(i*i);
	}
	/*continuem sumant els termes positiu de forma creixent en mòdul*/
	for (i=2*n-1; i>=1; i-=2){
		y+=1./(i*i);
		x+=1./(i*i);
	}
	/*Mostrem per pantalla els resultats obtinguts mostrant 9 decimals en el cas de la precisió doble*/
	printf ("\n\n%f\nEn el cas de la precisió simple\n%.9f\nEn el cas de la precisió doble.\n",y,x);
	/*Imprimim per pantalla una descripció del segón mètode que farem servir per sumar els termes de la série
	S=sum_{k=0}^{infty}(-1)^{k+1}/k²*/
	printf ("\nLa segona forma de fer-ho serà sumant els termes en ordre decreixent obtenint aixis el següents resultats");
	y=0;
	x=0;
	/*Sumem els termes positius de forma decreixent en mòdul*/
	for (i=1; i<=2*n-1; i+=2){
		y+=1./(i*i);
		x+=1./(i*i);
	}
	/*continuem sumant els termes negatius de forma creixent en mòdul*/
	for (i=2*n; i>=2; i-=2){
		y-=1./(i*i);
		x-=1./(i*i);
	}
	/*Mostrem per pantalla els resultats obtinguts mostrant 9 decimals en el cas de la precisió doble*/
	printf ("\n\n%f\nEn el cas de la precisió simple\n%.9f\nEn el cas de la precisió doble.\n",y,x);
	/*Imprimim per pantalla una descripció del tercer mètode que farem servir per sumar els termes de la série
	S=sum_{k=0}^{infty}(-1)^{k+1}/k²
	Que consisteix en sumar abans tots els termes de forma decreixent en mòdul. Això hauria d'evotar errors de 
	cancelació en quant el resultat de la sèrie sempre seria positiva i el nombre que es restaria seria
	sempre menys similar a la suma i per tant no podria causar errors de cancelació (cosa que no seria certa si
	fessim la suma de forma creixent en mòdul.*/
	printf ("\nLa tercera forma de fer-ho serà sumant els termes de la sèrie de forma decreixent en mòdul.\n");
	y=0;
	x=0;
	double s=-1;
	for (i=1; i<=2*n; i++){
		y+=s/(i*i);
		x+=s/(i*i);
		s=-s;
	}
	/*Mostrem per pantalla els resultats obtinguts mostrant 9 decimals en el cas de la precisió doble*/
	printf ("\n\n%f\nEn el cas de la precisió simple\n%.9f\nEn el cas de la precisió doble.\n",y,x);
}