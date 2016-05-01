#ifndef _Interpolacio_h
#define _Interpolacio_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int ordenar(double*, int);
int factorial(int);
int demanardades(double**, double**, double**);
int demanardadesPantalla(double**, double**, double**);
int demanardadesFitxer(double**, double**, double**);
void preparardades(double*, double*, double**, double**, int);
void diferenciesdividides(double*, double*, double*, double*, int);
void MostrarCoeficientsHermite(double*, double*, int);
void CalcularPolinomiHermite(double*, double**, int, int);
void MostrarPolinomiHermite(double*, int);
double* PolinomiInterpoladorHermite(double*, double*, int, int);
double* PolinomiInterpoladorHermite1(int*, int);
double AvaluarPolinomi(double*, int, double);
double* NodesChebyschev(double, double, int);
double* NodesEquiespaiats(double, double, int);
double* AvaluarFuncio(double (*f)(double) , double*, int);
double* Calculardiferencia(double*, double*, int);
void DibuixarGrafica(double*, double*, int, char*);
double AlgorismeNeville(double*, double*, double, int);

double* PolinomiInterpoladorSplines(double*, double*, int);
double* LongitudIntervals(double*, int);
double* CalculMu(double*, int);
double* CalculLambda(double*, int);
double* CalculD(double*, double*, int);
double* ConstruirMatriu(double*, double*, int);
double* CalculBeta(double*, double*, double*, int);
double* CalculDelta(double*, double*, int);
double AvaluarSplines(double*, double*, double);

double* ResoldreMatriuTridiagonal(double*, double*, double*, double*, int);
double* ResoldreSistemaLineal(double*, double*, int);
void Idn (int*, int*, int);
int LUtot(double*, int*, int*, int*, int*, int);
int pivotatge(double*, int*, int*, int*, int*, int, int);
void canvidecolumnesfiles (int*, int, int, int);
int guardarcanvidefiles (int*, int*, int);
int guardarcanvidecolumnes (int*, int*, int);
double* matriupermatriuintdb(int*, double*, int);
double* matriupermatriudbint(double*, int*, int);
int matriupermatriuintint(int*, int*, int, int);
double* matriupervector(int*, double*, int);
void resoldresistematriangularinferior (double*, double*, int);
void resoldresistematriangularsuperior (double*, double*, int);

/*Aquesta funció agafa com a parametres d'entrada dos vectors de igual longitud on es guarden les coordenades de punts
  interpoladors, el punt en el que es vol interpolar el polinomi i la longitud dels vectors i torna el 
  resultat d'aplicar el mètode de Neville sobre aquest punts interpoladors per a calcular el polinomi en un punt.*/
double AlgorismeNeville(double* X, double* Y, double x, int n){
	double aux[n];
	int i, j;
	/*copiem el vector Y sobre el vector aux*/
	for (i=0; i<n; i++){
		aux[i]=Y[i];
	}
	/*apliquem ara l'algorisme*/
	for (j=1; j<n; j++){
		for (i=0; i<(n-j); i++){
			/*apliquem la fórmula i guardem el resultat sobre el mateix vector.*/
			aux[i]=(aux[i]*(x-X[i+j])-aux[i+1]*(x-X[i]))/(X[i]-X[i+j]);
		}
	}
	return aux[0];
}


/*Aquesta funció pren com a parametres dos llistes de dades igual de llargues i la seva longitud i un títol i crida
 a gnuplot per fer-ne una gràfica*/
void DibuixarGrafica(double* X, double* Y, int n, char* titol){
	/*creem un fitxer anomenat dades on imprimirem les dades a dibuixar*/
	char s[80];
	sprintf(s, "%s.txt", titol);
    FILE * dades=fopen(s, "w");
    /*Obrim una interface que es pugui utilitzar per enviar comandes com com si les estiguessim escrivint en la linea de 
     comandes de gnuplot. el terme "The -persistent" manté obert el gnuplot després de que la funció s'acabi d'executar*/
    FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
    int i;
    //escrivim en el fitxer dades.txt els punts a dibuixar.
    for (i=0; i<n; i++){
	    fprintf(dades, "%.16lf %.16lf\n", X[i], Y[i]);
    }
    //Enviem a gnuplot la comanda per posr titol a la gràfica i dibuixar les dades.
    fprintf(gnuplotPipe, "set title '%s'\n", titol);
    fprintf(gnuplotPipe, "plot '%s.txt' using 1:2 with lines\n", titol);
    return;
}

/*Aquesta funció pren com a parametres d'entrada dos vectors amb la mateixa longitud i la seva dimensió i torna com a
  resultat el modul de les diferencies entre els elements d'aquest vector*/
double* Calculardiferencia(double* X, double* Y, int n){
	int i;
	double* D;
	/*reservem memòria per al vector D*/
	D=malloc(n*sizeof(double));
	/*guardem en D el valor dels mòduls de les diferències entre els valors de X i Y*/
	for (i=0; i<n; i++){
		D[i]=fabs(X[i]-Y[i]);
	}
	return D;
}

/*aquesta funció pren com a parametres un apuntador a una funció, un vector on estan guardats una sèrie de punts i
  un enter que indica la longitud del vector y retorna un vector de la mateixa longitud amb guardats els valors de
  la funció avaluada en els punts donats.*/
double* AvaluarFuncio(double (*f)(double), double* X, int n){
	int i;
	double* Y;
	/*reservem memoria per al vector Y*/
	Y=malloc(n*sizeof(double));
	/*avaluem f en els punts donats i guardem el resultat en Y*/
	for (i=0; i<n; i++){
		Y[i]=(*f)(X[i]);
	}
	/*tornem com a resultat el vector Y*/
	return Y;
}


/*Aquesta funció pren com a parametres els extrems de un interval [a,b] i el nombre de nodes que es desitgen (n) i
 torna com a resultat un vector amb guardats els n nodes equiespaiats per a aquest interval*/
double* NodesEquiespaiats(double a, double b, int n){
	int i;
	double* nodes;
	/*reservem memoria per al vector nodes*/
	nodes=malloc(n*sizeof(double));
	/*ordenem a i b de manera que b>a*/
	if (b<a){
		nodes[0]=b;
		b=a;
		a=nodes[0];
	}
	/*apliquem la formula per a nodes equiespaiats*/
	b=(b-a)/(n-1);
	for (i=0; i<n; i++){
		nodes[i]=a;
		a+=b;
	}
	return nodes;
}


/*Aquesta funció pren com a parametres els extrems de un interval [a,b] i el nombre de nodes que es desitgen (n) i
 torna com a resultat un vector amb guardats els n nodes de Chebyschev per a aquest interval*/
double* NodesChebyschev(double a, double b, int n){
	int i;
	double* nodes;
	/*reservem memoria per al vector nodes*/
	nodes=malloc(n*sizeof(double));
	nodes[0]=a;
	/*apliquem la formula per a trobar nodes de chebyschev*/
	a=(a+b)/2;
	b=(b-nodes[0])/2;
	for (i=1; i<=n; i++){
		nodes[i-1]=cos(M_PI_2*(2*i-1)/n);
	}
	/*tornem el vector nodes*/
	return nodes;
}

/*Aquesta funció pren com a parametres un vector on estan guardats els coeficients de un polinomi en ordre creixent,
  un enter que indica el grau d'aquest polinomi i el punt en el que es vol avaluar la funció i torna com a resultat
  la funció avaluada en aquest punt.*/
double AvaluarPolinomi(double* P, int n, double x){
	int i;
	double prod=1, sum=0;
	/*sumem els coeficients del polinomi multiplicats per la potencia de x corresponent guardada en la variable prod
	 y guardem la suma en la variable sum*/
	for (i=0; i<n; i++){
		sum+=P[i]*prod;
		prod*=x;
	}
	/*retornem el valor de la suma (que no és altra cosa que el polinomi P avaluat en x*/
	return sum;
}

/*Aquesta funció demana punts interpoladors i construeix el polinomi d'hermite a partir d'ells.
 pren com a parametre l'opció de mostrar el polinomi resultant (1) o no fer-ho (0) i un apuntador a un enter.
 La funció torna com a resultat un vector amb els coeficients del polinomi desenvolupat i guarda la dimensió
 d'aquest vector en el espai de memoria al que apunta el parametre dimensio.
 */
double* PolinomiInterpoladorHermite1(int* dimensio, int mostrar){
	int n;
	double *X, *Y, *P, *aux;
	/*demanem les dades per pantalla*/
	n=demanardades(&X, &Y, &aux);
	/*si n és -1 hi ha hagut un error.*/
	if (n==-1){return;}
	/*preparem les dades per poder aplicar l'algorisme de les diferències dividides.*/
	preparardades(X, Y, &P, &aux, n);
	/*Apliquem l'algorisme per trobar el polinomi interpolador de Hermite*/
	diferenciesdividides(X,Y,P,aux,n);
	/*mostrem per pantalla el resultat si així ho especifica el parametre mostrar.*/
	if (mostrar){
		MostrarCoeficientsHermite(X,P,n);
	}
	/*calculem ara el polinomi interpolador desenvolupat i el mostrem si aixi especifica la variable mostrar.*/
	CalcularPolinomiHermite(X,&P,n, mostrar);
	dimensio[0]=n;
	return P;
}

/*Aquesta funció fa exactament lo mateix que la funció anterior pero amb la diferència que pren com a parametres els
  vectors X i Y on estan guardats els punts interpoladors, el enter n on es guarda la dimensió d'aquests vectors i el
  enter mostrar que abilita o inhabilita la opció de mostrar explicitament el polinomi calculat.*/
double* PolinomiInterpoladorHermite(double* X, double* Y, int n, int mostrar){
	double *P, *aux;
	/*preparem les dades per poder aplicar l'algorisme de les diferències dividides.*/
	preparardades(X, Y, &P, &aux, n);
	/*Apliquem l'algorisme per trobar el polinomi interpolador de Hermite*/
	diferenciesdividides(X,Y,P,aux,n);
	/*mostrem per pantalla el resultat si així ho especifica el parametre mostrar.*/
	if (mostrar){
		MostrarCoeficientsHermite(X,P,n);
	}
	/*calculem ara el polinomi interpolador desenvolupat i el mostrem si aixi especifica la variable mostrar.*/
	CalcularPolinomiHermite(X,&P,n, mostrar);
	return P;
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

/*Aquesta función demanan per pantalla si es prefereixen introduir les dades manualment o per pantalla i executa una 
 funció o l'altra depenent del resultat*/
int demanardades(double** X, double** Y, double** aux){
	int i;
	printf("Com vol introduir les dades?\n\n1=Manualment\n2=Mitjançant un fitxer\n\n");
	scanf("%d", &i);
	while (i!=1 && i!=2){
		printf("No l'he entès, si us plau torna a introduir la teva resposta\n");
		printf("Com vol introduir les dades?\n\n1=Manualment\n2=Mitjançant un fitxer\n");
		scanf("%d", &i);
	}
	if (i==1){
		i=demanardadesPantalla(X,Y,aux);
		return i;
	}
	else if (i==2){
		i=demanardadesFitxer(X,Y,aux);
		return i;
	}
}

/*Fem una funció que demani per pantalla les dades, les guardi i torni la quantitat de punts interpoladors
(amb repetició)*/
int demanardadesPantalla(double** X, double** Y, double** aux){
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

/*Fem una funció que demani el fitxer on estan guardades les dades, les guardi i torni la quantitat de punts
interpoladors (amb repetició)*/
int demanardadesFitxer(double** X, double** Y, double** aux){
	int i, j, k, n, m;
	char fitxer[50];
	FILE* dades;
	double x;
	dades=NULL;
	while (dades==NULL){
		printf("\nRecorda que les dades del fitxer han d'estar estructurades de la següent manera\n\n");
		printf("1) En la primera linea ha d'apareixer únicament un enter que indiqui el nombre de punts diferents.\n");
		printf("2) Les dades referents a cada punt s'han d'organitzar en dues files.\n");
		printf("3) La primera fila ha de contindre únicament un enter que indiqui el nombre de derivades que ");
		printf("se saben de un determinat punt.\n");
		printf("4) La següent fila ha de contindre com a primera dada el valor del punt, després, separada per un ");
		printf("espai el valor de la funció en aquell punt. Hauran de seguir en ordre i separades per un espai els ");
		printf("valors de totes les derivades que es coneguin de la funció en el punt.\n\n");
		printf("Introdueix el nom del fitxer on es troben les dades.\n");
		scanf("%s", fitxer);
		dades=fopen(fitxer, "r");
		if (dades==NULL){
			printf("Error el fitxer %s no existeix.\nControla si has introduït correctament el nom del fitxer.\n", fitxer);
		}
	}
	/*Llegim la primera dada del fitxer corresponent al nombre de punts diferents on volem interpolar el polinomi
	i guardem el resultat en la variable k*/
	fscanf(dades, "%d", &k);
	/*Llegim ara la resta de dades i les guardem en els vectors aux X i Y per les que abans reservarem espai*/
	aux[0]=malloc(k*sizeof(double));
	/*la variable n guardarà la cuantitat total de punts amb repetició la inicialitzarem a 0 i després l'anirem 
	fent mes gran a mesura que s'introdueixin dades.*/
	n=0;
	/*Llegim el valor de la funció i de les seves derivades en cada punt i les guardem
	en Y mentres que en X guardem els punts amb repetició. Pero abans alloquem memoria per aquests dos per
	poder utilitzar la funció realloc.*/
	X[0]=malloc(sizeof(double));
	Y[0]=malloc(sizeof(double));
	/*començem a llegir les dades*/
	for (i=0; i<k; i++){
		/*cambiem de linea movent el cursor una posició (abans es trobava en la última posició de la linea anterior)*/
		fseek(dades, 1, SEEK_CUR);
		/*Llegim cuantes derivades se saben de la funció en el punt aux[i]*/
		fscanf(dades, "%d", &m);
		/*Actualitzem el vector X on es guarden els punts amb repetició i el vector Y on es
		guarden els valors de la funció i de les seves derivades*/
		/*hem de tindre en compte la derivada 0 m+=1*/
		m+=1;
		X[0]=realloc(*X, (n+m)*sizeof(double));
		Y[0]=realloc(*Y, (n+m)*sizeof(double));
		/*llegim el valor de la funció en el punt (és la primera dada de la nova linea)*/
		fscanf(dades, "%lf", &x);
		/*guardem el valor del punt en la posició i del vector aux*/
		aux[0][i]=x;
		/*Llegim ara el valor de la funció en el punt i el de les derivades en els punts si n'hi ha.*/
		for (j=0; j<m; j++){
			/*movem el cursor de una posició per saltar-nos l'espai entre dada i dada.*/
			fseek(dades, 1, SEEK_CUR);
			fscanf(dades, "%lf", &x);
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
void CalcularPolinomiHermite(double* X, double** P, int n, int mostrar){
	int i, j, k;
	double C[n], aux[n];
	/*posem el vector C[n] on es guardaràn els coeficients que multipliquin el terme de grau i del polinomi
	interpolador en un estat inicial igual a 0*/
	for (i=1; i<n; i++){
		C[i]=0;
	}
	/*desenvolupem el producte P[i](x-X[0])(x-X[1])...(x-X[i-1]).
	Si i=0 aleshores interpretarem el desenvolupament com P[0].*/
	C[0]=P[0][0];
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
			C[j]+=P[0][i]*aux[j];
		}
	}
	if (mostrar){
		MostrarPolinomiHermite(C,n);
	}
	P[0]=C;
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

/*Aquesta fució pren com a parametres les cordenades de punts interpolador guardades en els vectors X i Y i la
  dimensió d'aquests vectors (n) i torna un vector de longitud 4*(n-1) on estan guardats els n-1 polinomis cubics
  de Splines natural de manera que en les posicions congruents a 0 modul cuatre es troba el terme independent en les congruents
  a 1 el terme que multiplica (x-x_i) etc...*/
double* PolinomiInterpoladorSplines(double* X, double* Y, int n){
	double *h,*mu, *matriu, *moments, *lambda, *d, *beta, *delta, *Polin; 
	int i;
	h=LongitudIntervals(X,n);
	mu=CalculMu(h,n);
	lambda=CalculLambda(h,n);
	d=CalculD(h,Y,n);
	matriu=ConstruirMatriu(lambda, mu, n);
	/*Calculem els moments resolent el sistema que hem creat*/
	moments=ResoldreSistemaLineal(matriu, d, n-2);	
	beta=CalculBeta(Y,h,moments,n);
	delta=CalculDelta(h,moments,n);
	/*guardem el resultat obtingut en el vector Polin*/
	Polin=malloc(4*(n-1)*sizeof(double));
	Polin[0]=Y[0];
	Polin[1]=beta[0];
	Polin[2]=0;
	Polin[3]=delta[0];
	for (i=1; i<(n-2); i++){
		Polin[4*i]=Y[i];
		Polin[4*i+1]=beta[i];
		Polin[4*i+2]=moments[i-1]/2;
		Polin[4*i+3]=delta[i];
	}
	Polin[4*(n-2)]=Y[n-2];
	Polin[4*(n-2)+1]=beta[n-2];
	Polin[4*(n-2)+2]=0;
	Polin[4*(n-2)+3]=delta[n-2];
	return Polin;
}

/*Aquesta variable agafa com a parametres un vector de doubles (X) i la seva dimensió (n) i torna com a resultat
  un vector on es guarden les distancies entre els valors de X*/
double* LongitudIntervals(double* X, int n){
	double* h;
	int i;
	h=malloc((n-1)*sizeof(double));
	for (i=0; i<n-1; i++){
		h[i]=X[i+1]-X[i];
	}
	return h;
}

/*Aquesta funció calcula la mu de la formula del polinoi interpolador de Splines presentada a classe de mètodes
ńumèrics. Agafa com a parametres el vector de longituds de intervals h i torna com  a resultat un vector on es
guarden les mu*/
double* CalculMu(double* h, int n){
	double* mu;
	int i;
	mu=malloc((n-2)*sizeof(double));
	for (i=0; i<n-2; i++){
		mu[i]=h[i]/(h[i+1]+h[i]);
	}
	return mu;
}

/*Aquesta funció calcula la lambda de la formula del polinoi interpolador de Splines presentada a classe de mètodes
ńumèrics. Agafa com a parametres el vector de longituds de intervals h i torna com  a resultat un vector on es
guarden les lambda*/
double* CalculLambda(double* h,int n){
	double* lambda;
	int i;
	lambda=malloc((n-2)*sizeof(double));
	for (i=0; i<n-2; i++){
		lambda[i]=h[i+1]/(h[i+1]+h[i]);
	}
	return lambda;
}

/*Aquesta funció calcula la d de la formula del polinoi interpolador de Splines presentada a classe de mètodes
ńumèrics. Agafa com a parametres el vector de longituds de intervals h i el valor de la funció en els punts interpoladors
(Y) i torna com  a resultat un vector on es guarden les D*/
double* CalculD(double* h,double* Y,int n){
	double* d;
	int i;
	d=malloc((n-2)*sizeof(double));
	for (i=0; i<n-2; i++){
		d[i]=6*((Y[i+2]-Y[i+1])/h[i+1]-(Y[i+1]-Y[i])/h[i])/(h[i]+h[i+1]);
	}
	return d;
}

/*aquesta funció agafa com a parametres els vectors on es guarden les lambda i les mu de la formula del polinomi
interpolador natural de splines i torna la matriu que dona el sistema que s'ha de resoldre per obtindre els moments.*/
double* ConstruirMatriu(double* lambda, double* mu, int n){
	int i;
	double *matriu;
	matriu=malloc((n-2)*(n-2)*sizeof(double));
	for (i=0; i<(n-2)*(n-2); i++){
		matriu[i]=0;
	}
	for (i=0; i<(n-3); i++){
		matriu[(n-2)*i+i]=2;
		matriu[(n-2)*i+i+1]=lambda[i];
		matriu[(n-2)*(i+1)+i]=mu[i+1];
	}
	matriu[(n-2)*(n-2)-1]=2;
	return matriu;
}

/*Aquesta funció calcula la beta de la formula del polinoi interpolador de Splines presentada a classe de mètodes
ńumèrics. Agafa com a parametres el valor de la funció en els punts interpoladors el vector de longituds de intervals h
i els moments i torna com  a resultat un vector on es guarden les beta*/
double* CalculBeta(double* y,double* h,double* m,int n){
	double* beta;
	int i;
	beta=malloc((n-1)*sizeof(double));
	for (i=1; i<n-2; i++){
		beta[i]=(y[i+1]-y[i])/h[i]-h[i]*(2*m[i-1]+m[i])/6;
	}
	beta[0]=(y[1]-y[0])/h[0]-h[0]*m[0]/6;
	beta[n-2]=(y[n-1]-y[n-2])/h[n-2]-h[n-2]*m[n-3]/3;
	return beta;
}

/*Aquesta funció calcula la delta de la formula del polinoi interpolador de Splines presentada a classe de mètodes
ńumèrics. Agafa com a parametres el valor de la funció en els punts interpoladors el vector de longituds de intervals h
i els moments i torna com  a resultat un vector on es guarden les delta*/
double* CalculDelta(double* h,double* m,int n){
	double* delta;
	int i;
	delta=malloc((n-1)*sizeof(double));
	for (i=1; i<n-2; i++){
		delta[i]=(m[i]-m[i-1])/(6*h[i]);
	}
	delta[0]=m[0]/(6*h[0]);
	delta[n-2]=-m[n-3]/(6*h[n-2]);
	return delta;
}

/*Aquesta funció agafa com a parametres els nodes interpoladors i el vector on es guarda el resultat de la
  interpolació cúbica natural de Splines i torna com a resultat el seu valor.
  és necessari que el polinomi de Splines estigui definit en el punt on esx vol avaluar la funció.*/
double AvaluarSplines(double* X, double* Polin, double x){
	int i=0;
	double res, gamma;
	/*determinem en quin interval es troba la x per saber quin polinomi aplicar.*/
	while (X[i]<x){
		i++;
	}
	i--;
	/*apliquem el polinomi i tornem el resultat.*/
	res=x-X[i];
	res=Polin[4*i]+res*(Polin[4*i+1]+res*(Polin[4*i+2]+res*Polin[4*i+3]));
	return res;
}


/*L'objectiu d'aquesta funció és el de resoldre sistemes lineals tridiagonals d'una manera més ràpida i eficient que la
  funció ResoldreSistemaLineal aplicand l'algoritme de matriu tridiagonal, aquest algoritme desgraciadament pot propagar
  més l'errror que el mètode LU amb pivotatge fet servir en la funció ResoldreSistemaLineal().
  La funció pren com a parametres els elements de la diagonal (D) els de la diagonal superior (Ds), els de la diagonal
  inferior (Di), els termes independents (B) i la dimensió de la matriu n y torna el vector de solucions.*/
double* ResoldreMatriuTridiagonal(double* D, double* Ds, double* Di, double* B, int n){
	double *X, *aux, *aux1;
	int i;
	/*apliquem l'algorisme*/
	aux=malloc((n-1)*sizeof(double));
	aux1=malloc((n-1)*sizeof(double));
	aux[0]=Ds[0]/D[0];
	aux1[0]=B[0]/D[0];
	for (i=1; i<(n-1); i++){
		aux[i]=Ds[i]/(D[i]-Di[i-1]*aux[i-1]);
		aux1[i]=(B[i]-Di[i-1]*aux1[i-1])/(D[i]-Di[i-1]*aux[i-1]);
	}
	/*guardem el resultat en X*/
	X=malloc(n*sizeof(double));
	X[n-1]=(B[n-1]-Di[n-2]*aux1[n-2])/(D[n-1]-Di[n-2]*aux[n-2]);
	for (i=(n-2); i>-1; i--){
		X[i]=aux1[i]-aux[i]*X[i+1];
	}
	return X;
}

/*fem una funció per resoldre sistemes lineal (la necessitarem per fer interpolació per Splines).
 Aquesta funció prendrà com a parametres un vector de dimensió n*n que representarà la matriu M del sistema lineal
 de n equacions b=M*x, el vector b i la dimensió del sistema n i tornarà com a resultat un vector amb guardada la
 dimensió del sistema també modificarà b per guardar allí la solució. Si hi ha algun problema en la resolució del
 sistema la funció tornarà NULL*/
double* ResoldreSistemaLineal(double* M, double* b, int n){
	int i, Idf[n*n], Idc[n*n], permf[n], permc[n];
	/*inicialitzem les matrius Idf i Idc com la matriu identitat.*/
	Idn(Idf, Idc, n);
	/*apliquem el mètode LU amb pivotatge total.*/
	i=LUtot(M, Idf, Idc, permf, permc, n);
	/*si i==1 significa que hi ha hagut algun problema.*/
	if (i==1){
		return NULL;
	}
	/*permutem els resultats per poder fer els calculs pertinents.*/
	b=matriupervector(Idf,b,n);
	if (b==NULL){
		return NULL;
	}
	resoldresistematriangularinferior(M,b,n);
	resoldresistematriangularsuperior(M,b,n);
	/*els resultats han sigut permutats tornem-los a ordenar.*/
	b=matriupervector(Idc,b,n);
	return b;
}


/*les funcions que segueixen són necessaries per poder aplicar ResoldreSistemaLineal*/

/*Aquesta funció pren com a parametre dues matrius i les converteix en la matriu 
  identitat on després guardarem les permutacions fetes*/
void Idn (int* Idf, int* Idc, int n){
	int i,j;
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			Idf[n*i+j]=0;
			Idc[n*i+j]=0;
		}
		Idf[n*i+i]=1;
		Idc[n*i+i]=1;
	}
}

/*Aquesta funció resol el sistema LU fent pivotatge total per minimitzar l'error.*/
int LUtot(double* M,int* Idf,int* Idc,int* permf, int* permc, int n){
	int i,j,k,l;
	for (i=0; i<n; i++){
		l=pivotatge(M,Idf,Idc,permf,permc,n-i,n);
		if (l==1){
			return 1;
		}
		if (fabs(M[n*i+i])==0){
			fprintf(stderr, "ERROR EL SISTEMA D'EQUACIONS NO ÉS COMPATIBLE DETERMINAT\n");
			return 1;
		}
		for (j=i+1; j<n; j++){
			M[n*j+i]=M[n*j+i]/M[n*i+i];
			for (k=i+1; k<n; k++){
				M[n*j+k]=M[n*j+k]-M[n*j+i]*M[n*i+k];
			}
		}
	}
	return 0;
}


/*Aquesta funció s'encarrega del pivotatge per minimitzar l'error.*/
int pivotatge(double* M,int* Idf,int* Idc,int* permf, int* permc, int m, int n){
	int Idt[n*n], i, j, l=n-1, k=n-1, h;
	for (i=n-1; i>=(n-m); i+=-1){
		for (j=n-1; j>=(n-m); j+=-1){
			if (fabs(M[n*i+j])>fabs(M[n*l+k])){
				l=i;
				k=j;
			}
		}
	}
	permf[n-m]=l;
	canvidecolumnesfiles(Idt, n-m, l, n);
	h=guardarcanvidefiles(Idf,Idt, n);
	if (h==1){
		return 1;
	}
	M=matriupermatriuintdb(Idt,M,n);
	if (M==NULL){
		return 1;
	}
	permc[n-m]=k;
	canvidecolumnesfiles(Idt, n-m, k, n);
	h=guardarcanvidecolumnes(Idc,Idt, n);
	if (h==1){
		return 1;
	}
	M=matriupermatriudbint(M, Idt, n); 
	if (M==NULL){
		return 1;
	}
	return 0;
}

/*Aquesta funció crea una matriu de permutació de columnes o files.*/
void canvidecolumnesfiles (int* Idt, int i, int j, int n){
	int l,k;
	for (l=0; l<n; l++){
		for(k=0; k<n; k++){
			Idt[n*l+k]=0;
		}
		Idt[n*l+l]=1;
	}
	Idt[n*i+i]=0;
	Idt[n*j+j]=0;
	Idt[n*i+j]=1;
	Idt[n*j+i]=1;
}

/*aquesta funció guarda en un vector la permutació de files feta en una matriu de permutacio*/
int guardarcanvidefiles (int* Idf,int* F, int n){
	int i;
	i=matriupermatriuintint(F, Idf, n,1);
	if (i==1){
		return 1;
	}
	return 0;
}

/*aquesta funció guarda en un vector la permutació de columnes feta en una matriu de permutacio*/
int guardarcanvidecolumnes (int* Idc, int* C, int n){
	int i;
	i=matriupermatriuintint(Idc,C, n,2);
	if (i==1){
		return 1;
	}
	return 0;
}

/*Aquesta funció multiplica dues matrius una de doubles i l'altra d'enters i guarda el resultat en M2.*/
double* matriupermatriuintdb(int* M1, double* M2, int n){
	double M[n*n],sum=0.;
	int i,j,k;
	for (i=0; i<n; i++){
		for(j=0; j<n; j++){
			for(k=0; k<n; k++){
				sum+=M1[n*i+k]*M2[n*k+j];
			}
			M[n*i+j]=sum;
			sum=0.;
		}
	}
	for (i=0; i<n*n; i++){
		M2[i]=M[i];
	}
	return M2;
}

/*Aquesta funció multiplica dues matrius una d'enters i l'altra de doubles i guarda el resultat en M1*/
double* matriupermatriudbint(double* M1, int* M2, int n){
	double M[n*n],sum=0.;
	int i,j,k;
	for (i=0; i<n; i++){
		for(j=0; j<n; j++){
			for(k=0; k<n; k++){
				sum+=M1[n*i+k]*M2[n*k+j];
			}
			M[n*i+j]=sum;
			sum=0.;
		}
	}
	for (i=0; i<n*n; i++){
		M1[i]=M[i];
	}
	return M1;
}

/*Aquesta funció multiplica dues matrius d'enters i guarda el resultat en M1.*/
int matriupermatriuintint(int* M1, int* M2, int n, int l){
	int M[n*n],sum=0, i,j,k;
	for (i=0; i<n; i++){
		for(j=0; j<n; j++){
			for(k=0; k<n; k++){
				sum+=M1[n*i+k]*M2[n*k+j];
			}
			M[n*i+j]=sum;
			sum=0;
		}
	}
	if (l==1){
		for (i=0; i<n*n; i++){
			M2[i]=M[i];
		}
	}
	if (l==2){
		for (i=0; i<n*n; i++){
			M1[i]=M[i];
		}
	}
	return 0;
}

/*aquesta funció multiplica una matriu per un vector i guarda els resultats en el vector inicial*/
double* matriupervector(int* M, double* b, int n){
	double m[n],sum=0.;
	int i,j;
	for (i=0; i<n; i++){
		for(j=0; j<n; j++){
			sum+=M[n*i+j]*b[j];
		}
		m[i]=sum;
		sum=0.;
	}
	for (i=0; i<n; i++){
		b[i]=m[i];
	}
	return b;
}

/*aquesta funció resol el sistema triangular inferior de la descomposició LU*/
void resoldresistematriangularinferior (double* L, double* b, int n){
	int i, j;
	double sum=0.;
	for (i=0; i<n; i++){
		for (j=0; j<i; j++){
			sum+=L[n*i+j]*b[j];
		}
		b[i]+=-sum;
		sum=0.;
	}
}

/*aquesta funció resol el sistema triangular superior de la descomposició LU*/
void resoldresistematriangularsuperior (double* U, double* b, int n){
	int i, j;
	double sum=0.;
	for (i=n-1; i>=0; i+=-1){
		for (j=n-1; j>i; j+=-1){
			sum+=U[n*i+j]*b[j];
		}
		b[i]=(b[i]-sum)/U[n*i+i];
		sum=0.;
	}
}

#endif