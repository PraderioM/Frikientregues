#include <stdio.h>
#include <math.h>
#include "Interpolacio.h"


double f(double);
/*f1 está definido en Interpolacio.h mediante
typedef double (*f1)(double);*/
f1 g(int);
double* CalcularDiferencia(f1, double*, double*, double*, int, int);
double* CalcularPolinomio(f1, double*, double*, int, int);


/*El objetivo de este programa és realizar los calculos relacionados con el problema 1 de la pràctica 3
  Para ello haremos uso de la libreria Interpolacio.h la cual debe estar en la misma carpeta que este programa
  para que se pueda compilar*/
int main(){
	/*els vectors fx i px guardaran respectivamente los resultados de evaluar la función f i los polinomios
	interpoladores en los puntos guardados en X i descritos en el ejercicio.*/
	double *fx, *px, X[181];
	/*en el vector N guardaremos los nodos en los que se interpola.*/
	double *N, *M;
	/*en el apuntador h guardarem una funció*/
	f1 h;
	/*s guardarà los títulos de las gràficas*/
	char s[80];
	int i, n;
	/*construimos el vector de puntos donde evaluaremos f y los polinomios interpoladores*/
	for (i=0; i<181; i++){
		X[i]=-0.989+i*0.011;
	}
	/*Avaluamos f en los puntos de X*/
	fx=AvaluarFuncio(f, X, 181);
	n=2;
	while (n<17){
		/*Calculamos los nodos equiespaiados*/
		N=NodesEquiespaiats(-1,1,n);
		/*calculamos la diferencia entre el polinomio interpolador y la función y hacemos su
		logaritmo en base 10. Ademàs imprimimos por pantalla donde se asume el màximo.*/
		px=CalcularDiferencia(f, N, X, fx, n, 181);
		/*dibujamos la gràfica*/
		sprintf(s, "Logaritmo diferencia polinomio Interpolador con %d nodos equiespaiados",n); // escribimos el título
		DibuixarGrafica(X, px, 181, s);
		/*Calculamos los nodos de Chebyschev*/
		N=NodesChebyschev(-1,1,n);
		/*calculamos la diferencia entre el polinomio interpolador y la función y hacemos su logaritmo en base 10.*/
		px=CalcularDiferencia(f, N, X, fx, n, 181);
		/*dibujamos la gràfica*/
		sprintf(s, "Logaritmo diferencia polinomio interpolador con %d nodos Chebyschev",n); // escribimos el título
		DibuixarGrafica(X,px,181, s);
		n*=2;
	}
	/*pedimos por pantalla cuantos nodos se quieren utilizar para estudiar el comportamiento del poinomio interpolador
	 bajo perturbaciones de f en los nodos de interpolación*/
	printf("Cuantos nodos interpoladores de Chebyschev quieres para evaluar la función f perturbada por la sinusoidal?\n");
	scanf("%d", &n);
	/*Calculamos los nodos de Chebyschev*/
	N=NodesChebyschev(-1,1,n);
	/*calculamos la función ftilde para n nodos interpoladores*/
	h=g(n);
	/*calculamos el polinomio interpolador en los puntos X*/
	px=CalcularDiferencia(h, N, X, fx, n, 181);
	/*dibujamos la gràfica*/
	sprintf(s, "Logaritmo diferencia polinomio interpolador perturbado con %d nodos Chebyschev",n); // escribimos el título
	DibuixarGrafica(X,px,181, s);
	return 0;
}

/*hacemos una función que actue como la función de R a R presentada en el ejercicio f(x)=1/(1+3x)*/
double f(double x){
	return 1/(3+x);
}

/*hacemos una función que dado un entero n devuelva como resultado la función f(x)=1/(1+3x)+0.05*sin(2*pi*x*n).*/
f1 g(int n){
	double h(double x){
		return (1/(3+x)+0.05*sin(2*M_PI*x*n));
	}
	return h;
}

/*esta función se encarga de calular el polinomio interpolador para unos puntos dados, calcular el valor del
polinomio en otro conjunto de puntos y calcular el logaritmo de el valor absoluto de la diferencia entre el valor
del polinomio y el de la función en esos puntos. Ademàs imprime por pantalla el màximo de esta diferencia.
Toma como parametros los puntos donde interpolar, los puntos donde mirar la diferencia, el valor de la función en estos
puntos y dos enteros que indican la cantidad de puntos*/
double* CalcularDiferencia(f1 f, double* N, double* X, double* fx, int n, int m){
	double *px, *P, Y[n], error=0;
	int i, max=0;
	/*calculem la imatge de f en els nodes de N*/
	for (i=0; i<n; i++){
		Y[i]=f(N[i]);
	}
	px=malloc(m*sizeof(double));
	/*Calculamos el polinomio interpolador de Hermite utilizando los puntos de N para interpolar*/
	P=CoeficientsHermite(N, Y,n, 0);
	/*calculamos |f(x)-p(x)| para los puntos guardados en X*/
	for (i=0; i<m; i++){
		px[i]=AvaluarCoeficientsPolinomi(N, P, n, X[i]);
		px[i]=fabs(px[i]-fx[i]);
		/*actualizamos el error y el máximo (lo podemos hacer porque el logaritmo és creciente).*/
		if (px[i]>error){
			max=i;
			error=px[i];
		}
		/*evaluamos el logaritmo*/
		px[i]=log10(px[i]);
	}
	/*Imprimimos el máximo de la diferéncia por pantalla.*/
	printf("Evaluando el logaritmo de la diferencia entre la función 1/(3+x) y el polinomio ");
	printf("interpolador obtenido utilizando %d nodos ", n);
	/*Si el primer nodo és un extremo entonces los nodos són equiespaiados si no són de Chebyschev.*/
	if (N[0]==-1){
		printf("equiespaiados ");
	}
	else{
		printf("de Chebyschev ");
	}
	printf("hemos detectado que");
	if (px[max]==0){
		printf(":\nel polinomio y la función no presentan diferencia alguna en los puntos analizados.\n\n");
	}
	else{
		printf(" se presenta un màximo en la diferencia en el punto\n%g\ndonde ", X[max]);
		printf("el logaritmo de la diferencia vale\n%g\nCorrespondiente a un error de\n%g\n\n", px[max], error);
	}
	return px;
}