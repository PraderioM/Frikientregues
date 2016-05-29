#include <stdio.h>
#include <math.h>
#define a 2.
#define f1a (2*cos(2)+sin(2))

double f(double);
double F(double);
double ExtrapolacioRichardson(double*, int*, double, int);

int main(){
	double h=0.1, errant=10, X[100];
	int i=0, N[100];
	/*Mirem en quin entorn del 0 la avaluació de F(x) comença a presentar erros.*/
	while (fabs(F(h)-f1a)<errant && i<100){
		X[i]=F(h);
		/*mirem el error comés i el guardem en errant.*/
		errant=fabs(X[i]-f1a);
		h/=2;
		N[i]=4+2*i;
		i++;
	}
	printf("El calcul de F comença a donar errors en la seva evaluació al voltant del 0 a partir ");
	printf("del iterat %d on s'avalua F en el punt %g\n", i, h);
	h=ExtrapolacioRichardson(X, N, 0.5, i);
	printf("Aplicant la extrapolació de Richardson amb %d dades inicials obtenim la aproximació ", i);
	printf("de f'(2) donada per\n%.12g\nMentres que el valor real és\n%.12g\n\n", h, f1a);
	return 0;
}

/*Aquesta funció evalua la funció f definida en el exercici.*/
double f(double x){
	return x*sin(x);
}

/*Aquesta funció evalua la funció F definida en el exercici.*/
double F(double h){
	return (f(a-2*h)-8*f(a-h)+8*f(a+h)-f(a+2*h))/(12*h);
}

/*Aquesta funció agafa com a parametres un vector (X) de double de dimensió n que te per entrades els valors
  X[i]=f(q^i*h). Essent f la funció de la cual volem aproximar el 0. També pren com a arguments el vector N
  on estan guardts els ordres dels primers n-1 exponents (p_i) en el desenvolupament
  f(h)=f(0)+a_1h^{p_1}+a_2h^{p_2}+....
  El valor q esmentat anteriorment i la dimensió n esmentada anteriorment. Després d'aplicar extrapolació de
  Richardson i modificar el vector X torna el resultat de la extrapolació,*/
double ExtrapolacioRichardson(double* X, int* N, double q, int n){
	double pot=1;
	int i, j, k, exponent=0;
	/*apliquem l'algorisme*/
	for (i=n-2; i>-1; i--){
		/*calculem la potencia de q corresponent al iterat*/
		for (j=0; j<(N[n-2-i]-exponent); j++){
			pot*=q;
		}
		exponent=N[n-2-i]; //cambiem l'exponent de la potencia de q guardada actualent.
		for (j=0; j<i+1; j++){ //calculem els termes del següent iterat.
			X[j]=X[j]+(X[j]-X[j+1])/(pot-1);
		}
	}
	return X[0];
}