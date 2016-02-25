#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float simpledosbucles(float*,int);
float simpleunbucle(float*,int);
double doubledosbucles(double*,int);
double doubleunbucle(double*,int);
double* demanardadespantalla();
double* demanardadesfitxer();

int main(){
	int n, s, i;
	float *v;
	double *w;
	s=0;
	while (s==0){
		printf("\nVols introduir el vector per pantalla o mitjançant un fitxer?\n1=Per pantalla\n2=mitjançant fitxer\n");
		scanf("%d", &n);
		if (n==1){
			w=demanardadespantalla();
			n=w[0];
			v=malloc(n*sizeof(float));
			for (i=0; i<n; i++){
				w[i]=w[i+1];
				v[i]=(float)(w[i]);
			}
			s=1;
		}
		else if(n==2){
			w=demanardadesfitxer();
			n=w[0];
			v=malloc(n*sizeof(float));
			for (i=0; i<n; i++){
				w[i]=w[i+1];
				v[i]=(float)(w[i]);
			}
			s=1;
		}
		else{
			printf ("No he entès la teva resposta repeteix-la si us plau.\n");
		}
	}
	printf ("\nLa variança al cuadrat calculada amb un sol bucle i precisió simple és\n%f\nLa variança calculada amb dos bucles i precisió simple és\n%f\nLa variança calculada amb un sol bucle i precisió doble és\n%g\nLa variança calculada amb dos bucles i precisió doble és\n%g\n",simpleunbucle(v,n),simpledosbucles(v,n),doubleunbucle(w,n),doubledosbucles(w,n));
	printf ("\nLes dferencies entre els calculs amb un sol bucle i amb dos bucles son deguts a errors de cancelació mentres que les diferències entre precisió simple i doble son deguts a la precisió de representació i es fan mes evident cuantes mes operacions es fan.\n\n");
}

double* demanardadespantalla(){
	int n, i;
	double x, *w;
	n=0;
	while (n<2){
		printf("Introdueix el nombre de mesures disponibles\n");
		scanf("%d",&n);
		if (n<2){
			printf ("El nombre de mesures ha de ser com a mínim 2 si us plau torna a introduir-lo.\n");
		}
		else if (n>=2){}
		else{
			printf ("Si us plau introdueix un número\n");
		}
	}
	w=malloc((n+1)*sizeof(double));
	w[0]=n;
	for (i=1; i<=n; i++){
		printf("Introdueix la mesura número %d\n", i);
		scanf("%lf", &x);
		w[i]=x;
	}
	return w;
}

double* demanardadesfitxer(){
	int i, n;
	char fitxer[50];
	double x, *w;
	FILE* dades;
	dades=NULL;
	while (dades==NULL){
		printf("introdueix el nom del fitxer on es troben les dades recorda que cada dada ha de estar separada de la anterior amb una coma i un espai i la primera dada el nombre total de mesures\n");
		scanf("%s", fitxer);
		dades=fopen(fitxer, "r");
		if (dades==NULL){
			printf("Error el fitxer %s no existeix.\nControla si has introduit correctament el nom del fitxer.\n", fitxer);
		}
	}
	fscanf(dades, "%d", &n);
	fseek(dades, 2, SEEK_CUR);
	w=malloc((n+1)*sizeof(double));
	w[0]=n;
	for (i=0; i<n; i++){
		fscanf(dades, "%lf", &x);
		fseek(dades, 2, SEEK_CUR);
		w[i]=x;
	}
	return w;
}

float simpledosbucles(float* v, int n){
	float var=0, mig=0;
	int i;
	for (i=0; i<n; i++){
		mig+=v[i];
	}
	mig=mig/n;
	for (i=0; i<n; i++){
		var+=pow((v[i]-mig), 2);
	}
	var=var/(n-1);
	return var;
}

float simpleunbucle(float* v, int n){
	float var=0, mig=0;
	int i;
	for (i=0; i<n; i++){
		mig+=v[i];
		var+=pow(v[i],2);
	}
	mig=pow(mig, 2);
	mig=mig/n;
	var-=mig;
	var=var/(n-1);
	return var;
}

double doubledosbucles(double* w, int n){
	double var=0, mig=0;
	int i;
	for (i=0; i<n; i++){
		mig+=w[i];
	}
	mig=mig/n;
	for (i=0; i<n; i++){
		var+=pow(w[i]-mig, 2);
	}
	var=var/(n-1);
	return var;
}

double doubleunbucle(double* w, int n){
	float var=0, mig=0;
	int i;
	for (i=0; i<n; i++){
		mig+=w[i];
		var+=pow(w[i],2);
	}
	mig=pow(mig, 2);
	mig=mig/n;
	var-=mig;
	var=var/(n-1);
	return var;
}