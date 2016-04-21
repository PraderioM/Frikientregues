#include <stdio.h>
#include <math.h>

#define ZERO (1.e-13)/2
//definimos la raiz como el valor en contrado en el apartado anterior y que sabemos que és correcto o que almenos
//es la mejor aproximación que nuestro ordenador és capaz de dar con precisión doble.
#define RAIZ 7.413302725857898

double f(double);
double f1(double);
__float128 f__float128(__float128);
__float128 f1__float128(__float128);
__float128 absolute(__float128);
void repetimos();

//El objetivo de este programa és el de estudiar la convergencia de la sucesión definida en el problema 2
int main(){
	int i, j, n;
	double x, b, Succession[1000];
	//mostramos por pantalla lo que vamos a hacer
	printf("Aplicando la sucesión presentada en el problema 2 para calcular la raiz real del polinomio p(x)=x³-x-400 ");
	printf("calculada en el apartado anterior con una precisión de 16 decimales obtenemos que ");
	x=6;
	b=1/f1(x);
	Succession[0]=x;
	i=0;
	while(fabs(RAIZ-x)>ZERO && i<1000){
		x=x-b*f(x);
		b=b*(2-f1(x)*b);
		i++;
		Succession[i]=x;
	}
	if (i==1000){
		printf("la sucesión presentada en el problema 2 no converge.\n\n");
		return 0;
	}
	n=i;
	printf("en la iteración número %d llegamos al resultado\n%.13g\nEl cual tiene 13 decimales correctos como ", n, x);
	printf("podemos observar comparandolo con los resultados obtenidos en el ejercicio anterior.\n");
	printf("\nSi ahora denotamos por RAIZ el valor de la raiz encontrado en el apartado anterior y calculamos ");
	printf("(x_k-RAIZ)/(x_{k-1}-RAIZ)^n para n=1,2,3 i k=%d,%d,%d ",(n-2),(n-1),n);
	printf("los tres iterados previos a obtener la aproximación de la raiz con 13 decimales correctos obtenemos.\n\n");
	for (i=0; i<3; i++){
		for (j=n-2; j<n+1; j++){
			x=fabs(Succession[j]-RAIZ);
			b=fabs(Succession[j-1]-RAIZ);
			printf("%g\t", x/pow(b,i+1));
		}
		printf("\nn=%d\n\n", i+1);
	}
	printf("El hecho que los resultados obtenidos para n=1 tienden a 0 nos indica que el orden de convergencia de la ");
	printf("sucesión és almenos lineal. Por otro lado el hecho que, para n>1 los resultados obtenidos crezcan ");
	printf("descontroladamente nos indica que la sucesión no llega a tener orden de convergencia cuadràtico.\n");
	printf("No obstante, dado que los dos primeros quocientes en el caso de n=2 són bastante similares nos");
	printf(" surge la duda de si el hecho de que el tercer quociente aumente és debido a la precisión finita.\n");
	printf("Para comprobrarlo repetimos los calculos utilizando ahora variables del typo __float128 las cuales ");
	printf("tienen el doble de precisión que las variables tipo double obteniendo así los siguientes resultados.\n\n");
	//repetimos los calculos con otros tipos de variables.
	repetimos();
	printf("Como podemos observar el primer y segundo quociente se ha mantenido iguales mientras que el ");
	printf("tercer quociente ha disminuido para los tres valores de n. No obstante, en el caso de n=2, sigue siendo ");
	printf("sensiblemente mayor que los dos primeros quocientes por lo tanto no podemos afirmar que el orden de");
	printf(" convergencia sea cuadràtico.\nPero podemos sin duda alguna afirmar que el orden de convergéncia, ");
	printf("no obstante puede no llegar a ser cuadràtico, es superior al lineal (un orden de convergencia ");
	printf("fraccionario entre 1 y 2 bastante cercano al 2)\n\n");
	return 0;
}

//esta función toma como parametro de entrada la variable x y devuelve el resultado de evaluar la función
//f(x)=x^3-x-400 en el punto x.
double f(double x){
	return x*x*x-x-400;
}

//esta función toma como parametro de entrada la variable x y devuelve el resultado de evaluar la función
//f'(x)=3x²-1 (derivada de f(x)=x³-x-400) en el punto x.
double f1(double x){
	return 3*x*x-1;
}


//repetimos todo el calculo hecho pero ahora con mas precisión y mostrando únicamente la tabla de los quocientes.
void repetimos(){
	int i, j, n, k;
	__float128 error, x, b, Succession[1000];
	x=6;
	b=1/f1__float128(x);
	Succession[0]=x;
	i=0;
	error=RAIZ-x;
	if (error<0){
		error=-error;
	}
	while(error>ZERO && i<1000){
		x=x-b*f__float128(x);
		b=b*(2-f1__float128(x)*b);
		i++;
		Succession[i]=x;
		error=RAIZ-x;
		if (error<0){
			error=-error;
		}
	}
	if (i==1000){
		printf("\nLa sucesión presentada en el problema 2 no converge.\n\n");
		return;
	}
	n=i;
	for (i=0; i<3; i++){
		for (j=n-2; j<n+1; j++){
			x=absolute(Succession[j]-RAIZ);
			b=absolute(Succession[j-1]-RAIZ);
			for (k=0; k<i+1; k++){
				x/=b;
			}
			printf("%g\t", (double)x);
		}
		printf("\nn=%d\n\n", i+1);
	}
}

//esta función toma como parametro de entrada la variable x y devuelve el resultado de evaluar la función
//f(x)=x^3-x-400 en el punto x.
__float128 f__float128(__float128 x){
	return x*x*x-x-400;
}

//esta función toma como parametro de entrada la variable x y devuelve el resultado de evaluar la función
//f'(x)=3x²-1 (derivada de f(x)=x³-x-400) en el punto x.
__float128 f1__float128(__float128 x){
	return 3*x*x-1;
}


//esta función devuelve el valor absoluto de un numero guardado en una variable tipo __float128
__float128 absolute(__float128 x){
	if (x<0){
		x=-x;
	}
	return x;
}