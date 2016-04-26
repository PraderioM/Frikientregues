#include <stdio.h>
#include <stdlib.h>

int ordenar(double*, int);
int factorial(int);
int demanardades(double**, double**, double**);
void preparardades(double*, double*, double**, double**, int);
void freememory(double*, double*, double*, double*);
void diferenciesdividides(double*, double*, double*, double*, int);
void MostrarCoeficientsHermite(double*, double*, int);
void CalcularPolinomiHermite(double*, double*, int);
void MostrarPolinomiHermite(double*, int);

/*L'objectiu és construir un polinòmi interpolador d'Hermite.*/
int main(){
	int n;
	double *X, *Y, *P, *aux;
	/*demanem les dades per pantalla*/
	n=demanardades(&X, &Y, &aux);
	/*si n és -1 hi ha hagut un error.*/
	if (n==-1){return 1;}
	/*preparem les dades per poder aplicar l'algorisme de les diferències dividides.*/
	preparardades(X, Y, &P, &aux, n);
	/*Apliquem l'algorisme per trobar el polinomi interpolador de Hermite*/
	diferenciesdividides(X,Y,P,aux,n);
	/*mostrem per pantalla el resultat*/
	MostrarCoeficientsHermite(X,P,n);
	/*calculem ara el polinomi interpolador i mostrem el resultat.*/
	CalcularPolinomiHermite(X,P,n);
	/*allibarem memoria*/
	freememory(aux,X,Y,P);
	return 0;
}

/*La funció freememory allibera la memoria que hem allocat dinamicament.*/
void freememory(double* aux, double* X, double* Y, double* P){
	free(aux);
	free(X);
	free(Y);
	free(P);
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

/*Fem una funció que demani per pantalla les dades, les guardi i torni la quantitat de punts interpoladors
(amb repetició)*/
int demanardades(double** X, double** Y, double** aux){
	int i, j, k, n, m;
	double x;
	/*Demanem per pantalla el nombre de punts diferents on volem interpolar el polinomi
	i guardem el resultat en la variable k*/
	printf("En quants punts diferents vols evaluar el polinomi?");
	scanf("%d", &k);
	/*Demanem per pantalla els punts i guardem-los en la variable aux per la que abans reservarem l'espai.*/
	aux[0]=malloc(k*sizeof(double));
	for (i=0; i<k; i++){
		printf("Quin és el valor del punt número %d?\n", i+1);
		scanf("%lf", &aux[0][i]);
	}
	/*ordenem els punt cosa casi inútil pero que ens permet mirar si hi ha elements repetits en el qual cas tornem 1
	i acabem la funció.*/
	i=ordenar(aux[0], k);
	if (i==1){
		return -1;
	}
	/*la variable n guardarà la cuantitat total de punts amb repetició la inicialitzarem a 0 i després l'anirem 
	fent mes gran a mesura que s'introdueixin dades.*/
	n=0;
	/*Demanem el valor de la funció i de les seves derivades en cada punt i les guardem
	en Y mentres que en X guardem els punts amb repetició. Pero abans alloquem memoria per aquests dos per
	poder utilitzar la funció realloc.*/
	X[0]=malloc(sizeof(double));
	Y[0]=malloc(sizeof(double));
	for (i=0; i<k; i++){
		/*Demanem cuantes derivades se saben de la funció en el punt aux[i]*/
		printf("El valor de cuantes derivades de la funció en el punt %g coneixes?\n", aux[0][i]);
		scanf("%d", &m);
		/*Actualitzem el vector X on es guarden els punts amb repetició i el vector Y on es
		guarden els valors de la funció i de les seves derivades*/
		/*hem de tindre en cinte la derivada 0 m+=1*/
		m+=1;
		X[0]=realloc(*X, (n+m)*sizeof(double));
		Y[0]=realloc(*Y, (n+m)*sizeof(double));
		/*Demanem per pantalla el valor de la funció en els punts donats*/
		printf("Quant val la funció en el punt %g?\n", aux[0][i]);
		scanf("%lf", &x);
		/*la funció en el punt X[n]=aux[i] val Y[n]=x*/
		X[0][n]=aux[0][i];
		Y[0][n]=x;
		/*Demanem per fantalla el valor de les derivades en els punts si n'hi ha.*/
		for (j=1; j<m; j++){
			printf("Quant val la derivada %d de la funció en el punt %g?\n", j, aux[0][i]);
			scanf("%lf", &x);
			/*la derivada j de la funció (si j=0 és senzillament la funció sense derivar) en el punt X[n+j] val Y[n+j]*/
			X[0][n+j]=aux[0][i];
			Y[0][n+j]=x;
		}
		/*actualitzem el nombre de punts totals amb repetició sumant m.*/
		n+=m;
	}
	return n;
}

/*Aquesta funció agafa com a elements les dades dels punts interpoladors i el nombre de punt interpoladors i
comença a preparar dos vectors P i aux que ens serviràn per aplicar l'algorisme de les diferències dividides.*/
void preparardades(double* X, double* Y, double** P, double** aux, int n){
	int i, j;
	/*Ara ja sabem que el polinomi interpolador serà de grau n-1 per tant podem reservar l'espai de memòria
	per guardar-lo*/
	P[0]=malloc(n*sizeof(double));
	/*guardem el valosr de la funció en els punts X dins el vector aux*/
	aux[0]=malloc(n*sizeof(double));
	j=0;
	for (i=0; i<n; i++){
		if (X[j]!=X[i]){
			j=i;
		}
		aux[0][i]=Y[j];
	}
	/*guardem el primer element del polinomi interpolador*/
	P[0][0]=Y[0];
}

/*Aquesta funció aplica el mètode de les diferències dividides amb repetició de Lagrange per trobar els coeficients
del polinomi d'Hermite que guardarà en P.*/
void diferenciesdividides(double* X, double* Y, double* P, double* aux, int n){
	int i, j, k, f;
	double x;
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
				aux[i]=(aux[i]-aux[i+1])/(X[i]-X[i+j]);
				k=i+1;
			}
			/*En cas contrari hem d'atribuir a aux[i] el valor de la j ésima derivada de la funció evaluada
			en el punt X[i] dividit entre j factorial.*/
			else{
				f=factorial(j);
				aux[i]=Y[k+j]/f;
			}
		}
		P[j]=aux[0];
		j++;
		n--;
	}
}

/*Aquesta funció mostra per pantalla els coeficients del polinomi interpolador d'Hermite resultant.*/
void MostrarCoeficientsHermite(double* X, double* P, int n){
	int i, j;
	printf("\nEls coefinients del polinòmi interpolador de Hermite són:\n\n");
	for (i=0; i<n; i++){
		printf("f[");
		for(j=0; j<i; j++){
			printf("%.1g,", X[j]);
		}
		printf("%.1g]=%g\n",X[i], P[i]);
	}
}

/*Aquesta funció calcula explicitament el polinomi interpolador a partir dels coeficients del polinomi interpolador
 d'Hermite i mostra el resultat per pantalla.*/
void CalcularPolinomiHermite(double* X, double* P, int n){
	int i, j, k;
	double C[n], aux[n];
	/*posem el vector C[n] on es guardaràn els coeficients que multipliquin el terme de grau i del polinomi
	interpolador en un estat inicial igual a 0*/
	for (i=1; i<n; i++){
		C[i]=0;
	}
	/*desenvolupem el producte P[i](x-X[0])(x-X[1])...(x-X[i-1]).
	Si i=0 aleshores interpretarem el desenvolupament com P[0].*/
	C[0]=P[0];
	for (i=1; i<n; i++){
		aux[0]=-X[0];
		aux[1]=1;
		for (j=1; j<i; j++){
			/*multipliquem per (x-X[j]) obtenint un polinòmi de grau j+1*/
			aux[j+1]=aux[j];
			for (k=(j-1); k>-1 ;k--){
				aux[k+1]=aux[k]-X[j]*aux[k+1];
			}
			aux[0]=-X[j]*aux[0];
		}
		/*sumem el resultat al polinomi guardat en C*/
		for(j=0; j<i+1; j++){
			C[j]+=P[i]*aux[j];
		}
	}
	MostrarPolinomiHermite(C,n);
}

/*Aquesta funció agafa com a variables els coeficients de un polinomi i el seu grau mes 1
 i mostra el polinòmi per pantalla*/
void MostrarPolinomiHermite(double* C, int n){
	printf("\nEl polinomi desenvolupat és:\n\nP(x)=");
	//farem servir aquesta varieable per finalitats purament estètique i no posar el signe + devant del primer terme
	//si aquest és positiu (se sobreenten que és + si és positiu).
	int noprimer;
	noprimer=0;
	n-=1;
	//imprimim tots els coeficients no nuls que multipliquen potencies de x superiors o iguals a la segona.
	while(n>-1){
		if (C[n]!=0){
			if(C[n]>0 && noprimer){
				//imprimim el signe mes si el coeficient és positiu, el signe menys s'imprimeix per defecte si és el
				// primer terme no fa falta posar el signe + ja s'enten
				printf(" +");
			}
			//si és -1 posarem - per elegancia
			if (C[n]==-1 && n!=0){
				printf(" -");
			}
			//si el coeficient és 1 no el posarem per elegancia
			else if (C[n]!=1){
				printf(" %g",C[n]);
			}
			//imprimim la potencia de x que es multiplica.
			if (n>1){
				printf("x^%d",n);
			}
			//si la potencia de x que és multimplica escriurem x en comptes de x^1 per elegancia.
			else if(n==1){
				printf("x");
			}
			//si la potència de x és la 0 no escriurem res en comptes de escriure x^0.
			//Ja hem passat per aquí una vegada almenys.
			noprimer=1;
		}
		n--;
	}
	//posem dos espais per fer que quedi mono.
	printf("\n\n");
}