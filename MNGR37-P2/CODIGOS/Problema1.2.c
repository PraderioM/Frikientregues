#include <stdio.h>
#include <math.h>
/*Necessitarem assignació dinàmica de memòria*/
#include <stdlib.h>
/*definim dos variables que ens indicaran 8 decimals correctes i 16 decimals correctes respectivament.*/
#define ZERO1 (1.e-8)/2
#define ZERO2 (1.e-16)/2

void imprimirsolucion(double, double, float, float, int);

/*Este progra està pensado para aplicar el metodo de Newton para encontrar la raiz real
del polinomio el P(x)=x³-x-40 tomando como raiz inicial el valor x_0=2*/
int main(){
	//Realizaremos el calculo con precisión doble y simple
	double x, diferenciax;
	float y, diferenciay;
	int i, n, seguirx, seguiry;
	printf("\nCalculemos la raiz real del polinomio P(x)=x³-x-40 aplicando el mètodo de Newton ");
	printf("empezando en el punto x=2 hemos calculado teoricamente que para obtener ");
	printf("la raiz con 8 decimales correctos (suponiendo operaciones exactas) són necesarias 26 iteraciones ");
	printf("mientras que para obtener la raiz con 16 decimales correctos (suponiendo operaciones exactas) ");
	printf("són necesarias 49 iteraciones. No obstante estos calculos no tienen en cuenta errores en la ");
	printf("operación que se manifestarán en la diferencia entre los resultados obtenidos con precisión ");
	printf("simple y con precisión doble.\n\n");
	printf("Comprobemos los resultados teoricos de forma numèrica.\n");
	printf("Para hacerlo calcularemos la sucesión hasta que la diferencia en valor absoluto entre un iterado y el ");
	printf("iterado sucesivo sea menor que 10^{-8}/2 o que 10^{-16}/2 y nos detendremos cuando se den estas ");
	printf("dos condiciones.\nEstas condiciones de parada són suicientes dado que el método empleado és cuadràtico.");
	x=2.;
	y=2.;
	//seguimos hasta obtener los decimales correctos que deseamos con las dos precisiones esto se cumplirà cuando
	//seguirx=2 i seguiry=2 que son inicialente 0.
	seguirx=0;
	seguiry=0;
	//iniciamos la cuenta a 0 iteraciones.
	i=0;
	while (seguirx!=2 || seguiry!=2){
		//hacemos las itereaciones i guardamos la diferencia entre una iteración
		//y la siguiente en las variables diferenciax y diferenciay
		diferenciax=x;
		x=(2*x*x*x+40)/(3*x*x-1);
		diferenciax=fabs(diferenciax-x);
		diferenciay=y;
		y=(2*y*y*y+40)/(3*y*y-1);
		diferenciay=fabs(diferenciay-y);
		//marcamos que se ha hecho una iteración.
		i++;
		//si la diferència en las x o en las y és mas pequeña que un determinado valor lo mostramos por pantalla
		//8 decimales correctos con precision doble
		if (fabs(diferenciax)<ZERO1 && seguirx==0){
			printf("\nEn la iteración número %d obtenemos 8 decimales correctos ", i);
			printf("en el calculo con doble precisión donde hemos llegado al valor\n%.10g\n\n", x);
			seguirx++;
		}
		//16 decimales correctos con precision doble
		if (fabs(diferenciax)<ZERO2 && seguirx==1){
			printf("\nEn la iteración número %d obtenemos 16 decimales correctos ", i);
			printf("en el calculo con precisión simple donde hemos llegado al valor\n%.16g\n\n", x);
			seguirx++;
		}
		//8 decimales correctos con precision simple
		if (fabs(diferenciay)<ZERO1 && seguiry==0){
			printf("\nEn la iteración número %d obtenemos 8 decimales 'correctos' ", i);
			printf("en el calculo con precisión simple donde hemos llegado al valor\n%.10g\n\n", y);
			seguiry++;
		}
		//16 decimales correctos con precision simple
		if (fabs(diferenciay)<ZERO2 && seguiry==1){
			printf("\nEn la iteración número %d obtenemos 16 decimales 'correctos' ", i);
			printf("en el calculo con doble precisión donde hemos llegado al valor\n%.16g\n\n", y);
			seguiry++;
		}
	}
	printf("Notemos que la sucesión converge mucho antes de lo que habiamos predicho. Esto no obstante ");
	printf("no contradice nuestros calculos teóricos dado que estos nos daban únicamente una cota ");
	printf("superior del número de iteraciones a realizar.\n");
	printf("Es interesante notar que los resultados obtenidos con precisión simple y precisión doble són muy ");
	printf("diferentes no obstante los dos hayan cumplido con la condición de parada que estipulaba que la ");
	printf("diferencia entre un iterado y el sucesivo tenia que ser menor que (1.e-8)/2 o (1.e-16)/2 y, por lo ");
	printf("tanto, dado que la convergencia és cuadràtica, esto deberia inplicar que se tienen 8 o 16 decimales ");
	printf("correctos. Esto és debido a que, debido a la precisión reducida de la variable tipo float no és posible ");
	printf("que llegue a tener más de 7 cifras significativas. Todo resultado mas preciso lo considerarà identico al ");
	printf("anterior en otras palabras la sucesión obtenida con precisión simple considerarà que tener 7 decimales ");
	printf("corectos és equivalente a tener todos los decimales correctos dado que la variable float no és capaz de ");
	printf("percebir diferencia alguna\n\n");
	printf("\nIntroduce el número de iteraciones que quieres realizar.\n");
	scanf("%d", &n);
	//iniciamos con x_0=2;
	x=2;
	y=2;
	for (i=0; i<2*n; i++){
		//Si i==n entonces ya hemos hecho el nombre de iteracones pedida y imprimimos por pantalla el resultado
		if (i==n){
			imprimirsolucion(x,diferenciax,y,diferenciay,i);
		}
		//aplicamos la iteración
		diferenciax=(x*x*x-x-40)/(3*(x*x)-1);
		x=x-diferenciax;
		diferenciay=(y*y*y-y-40)/(3*(y*y)-1);
		y=y-diferenciay;
	}
	//Volvemos a imprimir la solución tras realizar el doble de iteraciones de las que se han pedido
	imprimirsolucion(x, diferenciax, y, diferenciay,2*n);
	return 0;
}

//hacemos una función que imprime por pantalla los resultados obtenidos
void imprimirsolucion(double x, double errorx, float y, float errory, int n){
	printf("El resultado obtenido tras hacer %d iteraciones és\n\n", n);
	printf("%.16g+_%.16g\n\nCon precisión doble y\n\n%.16g+_%.16g\n\nCon precisión simple\n\n",x, errorx,y, errory);
}