#include <stdio.h>
#include <stdlib.h>

int ordenar(double*, int);
int factorial(int);

/*L'objectiu és construir un polinòmi interpolador d'Hermite.*/
int main(){
	int i, j, k, n, m;
	double *X, *Y, *P, *aux, x;
	n=0;
	/*Demanem per pantalla el nombre de punts diferents on volem interpolar el polinomi*/
	printf("En quants punts diferents vols evaluar el polinomi?");
	scanf("%d", &k);
	aux=malloc(k*sizeof(double));
	/*Demanem per pantalla els punts.*/
	for (i=0; i<k; i++){
		printf("Quin és el valor del punt número %d?\n", i+1);
		scanf("%lf", &aux[i]);
	}
	/*ordenem els punt cosa casi inútil per que ens permet mirar si hi ha elements repetits en el caul cas tornem 1*/
	i=ordenar(aux, k);
	if (i==1){
		return 1;
	}
	/*Demanem el valor de la funció i de les seves derivades en cada punt*/
	n=0;
	for (i=0; i<k; i++){
		/*Demanem cuantes derivades se saben de la funció en el punt X[i]*/
		printf("El valor de cuantes derivades de la funció en el punt %g coneixes?\n", aux[i]);
		scanf("%d", &m);
		/*Actualitzem el vector X on es guarden els punts amb repetició i el vector Y on es
		guarden els valors de la funció i de les seves derivades*/
		X=realloc(X, (n+m)*sizeof(double));
		Y=realloc(Y, (n+m)*sizeof(double));
		/*Demanem per fantalla el valor de les derivades*/
		for (j=0; j<m; j++){
			printf("Quant val la derivada %d de la funció en el punt %g?\n", j, aux[i]);
			scanf("%lf", &x);
			/*la derivada j de la funció (si j=0 és senzillament la funció sense derivar) en el punt X[n+j] val Y[n+j]*/
			X[n+j]=aux[i];
			Y[n+j]=x;
		}
		/*actualitzem la dimensió del vector X*/
		n+=m;
	}
	/*Ara ja sabem que el polinomi interpolador serà de grau n-1 per tant podem reservar l'espai de memòria
	per guardar-lo*/
	P=malloc(n*sizeof(double));
	/*guardem el valor de la funció en els punts X dins el vector aux*/
	aux=realloc(aux, n);
	j=0;
	for (i=0; i<n; i++){
		if (X[j]!=X[i]){
			j=i;
		}
		aux[i]=Y[j];
	}
	/*guardem el primer element del polinomi interpolador*/
	P[0]=Y[0];
	/*Apliquem l'algorisme per trobar el polinomi interpolador de Lagrange*/
	/*Aquest terme ens servirà per identificar quins seràn els punts en el denomidador
	 de la fórmula de les diferències dividides de Lagrange*/
	j=1;
	while (n>1){
		/*Aquest terme ens servirà per a poder trobar la posició on està guardada la j-èsima derivada de la funció
		evaluada en un punt múltiple (la j-èsima derivada de la funció en el punt que es pot trobar per primera
		vegada en X[i] es troba guardada en Y[i+j])*/
		k=0;
		for (i=0; i<(n-1); i++){
			/*Si X[i] és diferent de X[i+j] apliquem les diferències dividides de Lagrange normals*/
			if(X[i]!=X[i+j]){
				aux[i]=(aux[i]-aux[i+1])/(X[i]-X[j]);
				k=i+1;
			}
			/*En cas contrari hem d'atribuir a aux[i] el valor de la j ésima derivada de la funció evaluada
			en el punt X[i] dividit entre j factorial.*/
			else{
				m=factorial(j);
				aux[i]=Y[k+j]/m;
			}
		}
		P[j]=aux[0];
		j++;
		n--;
	}
	/*mostrem per pantalla el resultat*/
	printf("Els coefinients del polinòmi interpolador de Hermite són:\n\n");
	for (i=0; i<n; i++){
		printf("f[");
		for(j=0; j<i; j++){
			printf("%.1g,", X[j]);
		}
		printf("%.1g]=%g\n",X[i], P[i]);
	}
}

/*La funció ordenar agafa com a parametres un vector (V) i un la seva dimensió (n)
n'ordena els elements mitjançant el mètode de la bombolla.*/
int ordenar(double* V, int n){
	int i, j;
	double aux;
	for (j=0; j<(n-1); j++){
		for (i=0; i<(n-j-1); i++){
			if (V[i]>V[i+1]){
				aux=V[i+1];
				V[i+1]=V[i];
				V[i]=aux;
			}
			else if (V[i]==V[i+1]){
				printf("Error has introduits dos valors iguals.\n");
				return 1;
			}
		}
	}
	return 0;
}

/*La funció factorial agafa com a paràmetre un enter i torna el seu factorial*/
int factorial(n){
	int i, prod;
	if (n==0){
		return 1;
	}
	prod=1;
	for (i=n; i>0; i--){
		prod=prod*i;
	}
	return prod;
}