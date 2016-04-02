#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

int potenceof2(int);

int main(){
	int i, n;
	double a, b, c, s, aux, Aitken[1000];
	a=1;
	b=1/sqrt(2);
	s=1/2;
	Aitken[0]=2*a/s;
	i=0;
	n=-1;
	while (fabs(Aitken[i]-M_PI)>ZERO && i<1000){
		i++;
		aux=a;
		a=(a+b)/2;
		b=sqrt(aux*b);
		c=a*a-b*b;
		s-=potenceof2(i)*c;
		Aitken[i]=2*a/s;
		if (n==-1 && fabs(Aitken[i]-M_PI)>fabs(Aitken[i-1]-M_PI)){
			printf("En el iterado número %d el error ha empezado a crecer pasando de %.16g a %.16g\n", i, fabs(Aitken[i-1]-M_PI), fabs(Aitken[i]-M_PI));
			n=1;
		}
		else if(n==1 && fabs(Aitken[i]-M_PI)<fabs(Aitken[i-1]-M_PI)){
			printf("En el iterado número %d el error ha empezado a decrecer pasando de %.16g a %.16g\n", i, fabs(Aitken[i-1]-M_PI), fabs(Aitken[i]-M_PI));
			n=-1;	
		}
	}
	n=i;
	printf("En el iterado número %d obtenemos el valor \n%.16g\nEl cual aproxima pi con un ", n, Aitken[i]);
	printf("error de %g", fabs(Aitken[i]-M_PI));
	printf("Además haciendo realizando la operación (p_n-pi)/(p_{n-1}-pi)^2 con los 3 mètodos previos a la ");
	printf("convergéncia obtenemos:\n");
	for (i=n-4; i<n; i++){
		a=(Aitken[i+1]-M_PI)/((Aitken[i]-M_PI)*(Aitken[i]-M_PI));
		printf("%g\n", a);
	}
	printf("Como podemos observar los resultados obtenidos son mu similares y podemos por lo tanto deducir que ");
	printf("existe el límite de n que tiende a infinito de (p_n-pi)/(p_{n-1}-pi)^2 i por lo tanto el orden de ");
	printf("convergéncia és cuadràtico");
	i=0;
	while (fabs(Aitken[i]-M_PI)>ZERO && i<n-2){
		Aitken[i]=(Aitken[i]*Aitken[i+2]-Aitken[i+1]*Aitken[i+1])/(Aitken[i+2]-2*Aitken[i+1]+Aitken[i]);
		i++;
	}
	if (i==n-2){
		printf("El método de acceleración de Aitken no ha funcionado.\n");
	}
	else{
		printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
		printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	}

}

int potenceof2(int n){
	int i, p=1;
	for (i=0; i<n; i++){
		p*=2;
	}
	return p;
}