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
	/*Creem un bucle que demani per pantalla si es prefereix introduir les dades mitjançant fitxer o
	per pentalla i que permeti introduir les dades de la forma especificada o torni a demanar el mètode
	de introducció de dades en cas de que la resposta introduïda no sigui una de les anteriors.*/
	s=0;
	while (s==0){
		printf("\nVols introduir el vector per pantalla o mitjançant un fitxer?\n1=Per pantalla\n2=mitjançant fitxer\n");
		scanf("%d", &n);
		if (n==1){
			/*Si n==1 aleshores s'haurà seleccionat l'opció de introduir les dades per pantalla cosa que es farà
			mitjançant la funció demanardadespantalla*/
			w=demanardadespantalla();
			/*La funció demanardadespantalla torna com a resultat un vector de n+1 elements (sent n el nombre de dades)
			guardats amb precisió doble*/
			/*El primer element de w guarda el nombre de dades introduides n mentres que els altre n guarden
			les dades guardem el nombre de dades en la variable n*/
			n=w[0];
			v=malloc(n*sizeof(float));
			for (i=0; i<n; i++){
				/*desplacem totes les dades del vector w en una posició cap a l'esquerra per tal de sobreescriure el
				valor que indicava el nombre total dades i que ja no necessitem en quant està guardat en la
				variable n*/
				w[i]=w[i+1];
				/*guardem les dades que tenim en w en el vector v on estarán guardades amb precisió simple*/
				v[i]=(float)(w[i]);
			}
			s=1;
		}
		else if(n==2){
			/*Si n==2 aleshores s'haurà seleccionat l'opció de introduir les dades mitjançant cosa que es farà
			fent us de la funció demanardadesfitxer*/
			w=demanardadesfitxer();
			/*La funció demanardadesfitxer torna com a resultat un vector de n+1 elements (sent n el nombre de dades)
			guardats amb precisió doble*/
			/*El primer element de w guarda el nombre de dades introduides n mentres que els altre n guarden
			les dades guardem el nombre de dades en la variable n*/
			n=w[0];
			v=malloc(n*sizeof(float));
			for (i=0; i<n; i++){
				/*desplacem totes les dades del vector w en una posició cap a l'esquerra per tal de sobreescriure el
				valor que indicava el nombre total dades i que ja no necessitem en quant està guardat en la
				variable n*/
				w[i]=w[i+1];
				/*guardem les dades que tenim en w en el vector v on estarán guardades amb precisió simple*/
				v[i]=(float)(w[i]);
			}
			s=1;
		}
		else{
			/*Si la resposta introduïda és incorrecta es tornarà a demanar*/
			printf ("No he entès la teva resposta repeteix-la si us plau.\n");
		}
	}
	/*Mostrem per pantalla els resultats dels calculs de la variança fets amb un o dos bucles i amb precisió simple o
	doble (calculs realitzats per les funcions simpledosbucles, simpleunbucle, doubledosbucles i doubleunbucle*/
	printf ("\nLa variança al cuadrat calculada amb un sol bucle i precisió simple és\n%f\nLa variança calculada amb dos bucles i precisió simple és\n%f\nLa variança calculada amb un sol bucle i precisió doble és\n%g\nLa variança calculada amb dos bucles i precisió doble és\n%g\n",simpleunbucle(v,n),simpledosbucles(v,n),doubleunbucle(w,n),doubledosbucles(w,n));
	/*Imprimim per pantalla una explicació de les diferències en el càlcul de les variances fetes amb el 
	mètode de un sol bucle i amb el mètode de dos bucles*/
	printf ("\nLes diferencies entre els calculs amb un sol bucle i amb dos bucles son deguts a errors de cancelació mentres que les diferències entre precisió simple i doble son deguts a la precisió de representació i es fan mes evident cuantes mes operacions es fan.\n\n");
}

/*La funcio demanardadespantalla demana per pantalla el nombre de dades a introduir i seguidament les dades en si
  que guarda amb precisió double i torna com a resultat un vector de n+1 nombre amb precisió doble
  (on n és el nombre de dades) on están guardats en la primera posició el nombre de dades i la resta d'espais del
  vector estan ocupats per les dades en si.*/
double* demanardadespantalla(){
	int n, i;
	double x, *w;
	n=0;
	/*Demanem per pantalla el nombre de dades i tornem-lo a demanar en el cas de que el nombre introduït sigui
	  menor a dos (no te sentit calcular la variança de un sol element o de un nombre negatiu d'elements) o en
	  el cas de que el valor introduït no sigui un número.*/
	while (n<2){
		printf("Introdueix el nombre de mesures disponibles\n");
		/*guardem el nombre de dades en la variable n.*/
		scanf("%d",&n);
		if (n<2){
			printf ("El nombre de mesures ha de ser com a mínim 2 si us plau torna a introduir-lo.\n");
		}
		else if (n>=2){}
		else{
			printf ("Si us plau introdueix un número\n");
		}
	}
	/*establim la dimensió del vector de doubles w en n+1 elements on n és el nombre total de dades.*/
	w=malloc((n+1)*sizeof(double));
	/*guardem la variable n en el primer espai del vector w*/
	w[0]=n;
	/*demanem per pantalla una a una totes les dades i les guardem en el vector w amb precisió double*/
	for (i=1; i<=n; i++){
		printf("Introdueix la mesura número %d\n", i);
		scanf("%lf", &x);
		w[i]=x;
	}
	return w;
}

/*La funcio demanardadesfitxer demana per pantalla el nom del fitxer on es guarden les dades i llegeix a partir del
  fitxer primer el nombre de dades (que ha d'estar guardat el primer) i després la resta de dades (que han d'estar
  guardats seguidament separats per una coma i un espai). La funció guarda les dades llegides amb una precisió
  doble i torna com a resultat un vector de n+1 nombre amb precisió doble (on n és el nombre de dades) on están
  guardats en la primera posició el nombre de dades i la resta d'espais del vector estan ocupats per les dades en si.*/
double* demanardadesfitxer(){
	int i, n;
	char fitxer[50];
	double x, *w;
	FILE* dades;
	dades=NULL;
	/*Demanem per pantalla el nom del fitxer on estan guardades les dades i, en cas de no trobar-lo, donem un missatge
	  de error i tornem a demanar el nom del fitxer.*/
	while (dades==NULL){
		printf("introdueix el nom del fitxer on es troben les dades recorda que cada dada ha de estar separada de la anterior amb una coma i un espai i la primera dada el nombre total de mesures\n");
		scanf("%s", fitxer);
		dades=fopen(fitxer, "r");
		if (dades==NULL){
			printf("Error el fitxer %s no existeix.\nControla si has introduit correctament el nom del fitxer.\n", fitxer);
		}
	}
	/*llegim la primera dada del fitxer corresponent al nombre total de dades*/
	fscanf(dades, "%d", &n);
	/*movem el cursor dos posicions saltant aixis la coma i el espai*/
	fseek(dades, 2, SEEK_CUR);
	/*establim la dimensió del vector de doubles w en n+1 elements on n és el nombre total de dades.*/
	w=malloc((n+1)*sizeof(double));
	/*guardem la variable n en el primer espai del vector w*/
	w[0]=n;
	/*llegim una a una totes les dades del fitxer i les guardem en el vector w amb precisió double*/
	for (i=1; i<=n; i++){
		fscanf(dades, "%lf", &x);
		fseek(dades, 2, SEEK_CUR);
		w[i]=x;
	}
	return w;
}

/*La funció simpledosbucles agafa com a variable un vector de nombres amb precisió simple v i un enter n que
  indica la quantitat de dades present en v i torna com a resultat la variamça dels elements de v calculada fent
  servir l'algoritme de dos bucles.*/
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

/*La funció simpledosbucles agafa com a variable un vector de nombres amb precisió simple v i un enter n que
  indica la quantitat de dades present en v i torna com a resultat la variamça dels elements de v calculada fent
  servir l'algoritme de un sol bucle.*/
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

/*La funció simpledosbucles agafa com a variable un vector de nombres amb precisió doble w i un enter n que
  indica la quantitat de dades present en v i torna com a resultat la variamça dels elements de w calculada fent
  servir l'algoritme de dos bucles.*/
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

/*La funció simpledosbucles agafa com a variable un vector de nombres amb precisió doble w i un enter n que
  indica la quantitat de dades present en v i torna com a resultat la variamça dels elements de w calculada fent
  servir l'algoritme de un sol bucle.*/
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