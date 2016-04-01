#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

double f(double);

int main(){
	int i, n;
	double a, b, Aitken[1000], s, error;
	a=2;
	b=8;
	Aitken[0]=a;
	if (f(a)>f(b)){
		Aitken[0]=b;
		b=a;
		a=Aitken[0];
	}
	error=fabs(b-a);
	i=1;
	while (error>ZERO && i<1001){
		Aitken[i]=(a+b)/2;
		s=f(Aitken[i]);
		if (s>0){
			b=Aitken[i];
		}
		else if (s==0){
			printf("la raiz és %.16g con únicamente error de representación\n", aux);
			i++;
			break;
		}
		else{
			a=Aitken[i];
		}
		error/=2;
		i++;
	}
	n=i-1;
	printf("\n\nAplicando el mètodo de la bisección y con %d iteraciones hemos llegado al resultat\n%.16g\n", n, Aitken[n]);
	printf("Con una precisió de %.16g\n\n", error);
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta successión perqué no tiene suficientes iterados.\n");
		return 0;
	}
	b=Aitken[n];
	i=0;
	while (fabs(Aitken[i]-b)>ZERO && i<n-2){
		Aitken[i]=(Aitken[i]*Aitken[i+2]-Aitken[i+1]*Aitken[i+1])/(Aitken[i+2]-2*Aitken[i+1]+Aitken[i]);
		i++;
	}
	if (i==n-2){
		printf("El mètode d'acceleració de Aitken no ha logrado acelerar la sucesión.\n");
		return 0;
	}
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	return 0;
}

double f(double x){
	return pow(x,3)-x-400;
}