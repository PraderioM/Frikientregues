#include <stdio.h>
#include <math.h>

double f(double);
double g(double);


//el objetivo de esta función és el de aplicar el metodo para calcular raices expuesto en el apartado 4 de la práctica 2.
int main(){
	double x,c,aux,a,b, error;
	int k, i;
	printf("Introduce el número del que quieres aproximar la raíz (más grande que 1); ");
	scanf("%lf", &x);
	printf("Introduce el número de productos que quieres calcular (número entero): ");
	scanf("%d",&k);
	c=x-1;
	aux=1;
	//calculamos k iterados del producto.
	for (i = 0; i < k; i++){
		a=g(c);
		b=f(c);
		c=a;
		aux=aux*b;
	}
	//calculamos una cota del error haciendo uso de la cota vista en el apartado 4.6
	error=(a/2)*ceil(sqrt(1+c));
	//mostramos por pantalla los resultados.
	printf("El valor aproximado de la raiz de %g és: %.16g\n\n", x, aux);
	printf("El error en el cálculo de la raíz es:%.16g\n\n ", error);
	return 0;
}



/*esta función toma como valor de entrada un número x i devuelve el resultado de la operación
(7x³+56x²+112x+64)/(x³+24x²+80x+64)*/
double f(double x){
	x=(7*x*x*x+56*x*x+112*x+64)/(x*x*x+24*x*x+80*x+64);
	return x;
}

/*esta función toma como valor de entrada un número x i devuelve el resultado de la operación
(1+x)/(f(x))²-1
donde la función f és la que està definida previamente en este mismo programa.*/
double g(double x){
	x=(1+x)/((f(x))*(f(x)))-1;
    return x;
}