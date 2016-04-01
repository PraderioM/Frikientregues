#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

double g(double);

int main(){
	int i, n;
	double x, error;
	x=2;
	Aitken[0]=x;
	error=1;
	i=0;
	while (error>ZERO && i<1001){
		error=g(x);
		x-=error;
		Aitken[i]=x;
		i++;
	}
	n=i-1;
	if (n==1000){
		printf("Aplicando el método de Newton para encontrar raices del polinomio P(x)=x³-x-400 partiendo de ");
		printf("x_0=2 no llegamos a una sucesión convergente.");
		return 0;
	}
	printf("\nAplicando el mètodo de Newton y con %d iteraciones hemos llegado al resultat\n%.16g\ncon ", n, x);
	printf("una precisión de %.16g\n\n", error);
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta successión perqué no tiene suficientes iterados.\n");
		return 0;
	}
	i=0;
	while (fabs(Aitken[i]-x)>ZERO && i<n-2){
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

double g(double x){
	return (pow(x,3)-x-400)/(3*pow(x,2)-1);
}