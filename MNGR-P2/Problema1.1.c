#include <stdio.h>
#include <math.h>

/*Aquest programa està pensat per evaluar numèricament el resultat de la operació
a=(20+\sqrt(32397)/9)^{1/3}+(20-\sqrt(32397)/9)^{1/3}
en precisió simple i doble*/
int main(){
	/*Declaramos las variables donde guardaremos los resultados*/
	double x;
	float y;
	/*calculamos los resultados*/
	x=sqrt(32397.);
	y=sqrt(32397.);
	x=pow(20+x/9,1./3)+pow(20-x/9,1./3);
	y=pow(20+y/9,1./3)+pow(20-y/9,1./3);
	/*los imprimimos por pantalla*/
	printf("\nPara calcular la raiz real del polinomio P(x)=x³-x-40 aplicaremos la siguiente fórmula de Cardano Vieta dada por\n");
	printf("a=(20+\\sqrt(32397)/9)^{1/3}+(20-\\sqrt(32397)/9)^{1/3}\n");
	printf("Esperamos que esta fórmula de un error de cancelacion al hacer la operación 20-\\sqrt(32397)/9\n");
	printf("Tras aplicar la fórmula obtenemos\n\n%.10g\n\ncon precisión doble y\n\n%.10g\n\ncon precisión simple.\n\n",x,y);

}