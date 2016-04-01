#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

double f(double);

int main(){
	int i, n;
	double a, b, Aitken[1000] s;
	a=2;
	b=8;
	Aitken[0]=a;
	i=0;
	while (fabs(b-a)>ZERO && i<1000){
		Aitken[i+1]=b;
		b=a-f(a)*(b-a)/(f(b)-f(a));
		a=Aitken[i+1];
		i++;
	}
	n=i;
	if (n==1000){
		printf("Aplicando el método de la secante para encontrar raices del polinomio P(x)=x³-x-400 partiendo de ");
		printf("los valores iniciales x_0=2 y x_1=8 no llegamos a una sucesión convergente.\n\n");
		return 0;
	}
	printf("\nCon %d iteraciones hemos llegado al resultado\n%.16g\nCon una precisión de %.16g\n", i, b, fabs(b-a));
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta successión perqué no tiene suficientes iterados.\n");
		return 0;
	}
	i=0;
	while (fabs(Aitken[i]-b)>ZERO && i<n-2){
		Aitken[i]=(Aitken[i]*Aitken[i+2]-Aitken[i+1]*Aitken[i+1])/(Aitken[i+2]-2*Aitken[i+1]+Aitken[i]);
		i++;
	}
	if (i==n-2 && n>2){
		printf("El mètode d'acceleració de Aitken no ha logrado acelerar la sucesión.\n");
		return 0;
	}
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	return 0;
}


//fem una funció que avalui la funció que volem en un punt i retorni el seu valor
double f(double x){
	return pow(x,3)-x-400;
}