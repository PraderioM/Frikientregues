/* per el apartat a primer és necessari notar que la funció és sempre positiva en o 0 en fora del origen en cuant x²>0 i
1-cos³(x)>=0. A més a més
lim x->0 (1-cos³(x))/x²=
=lim x->0 (1-cos(x))(1+cos(x)+cos²(x))/x²=
=lim x->0 (1-cos²(x))(1+cos(x)+cos²(x))/(x²(1+cos(x)))=
=lim x->0 (sin²(x)/x²)(1+cos(x)+cos²(x))/(1+cos(x)))=3/2
per tant si demostrem que la derivada de f(x)=(1-cos³(x))/x² és negativa en un entorn dret de 0 i negativa en un entorn
esquerra aleshores f(x)<3/2 en aquest en la unió d'aquests dos entorns.
Ara bé calculant la derivada de f(x) obtenim que aquesta te el mateix signe que la funció
g(x)=-3sin(x)cos²(x)x²-2x+2xcos³(x)=2x(cos³(x)-1)-3sin(x)x²
ara be en el interval (0;PI/2] es copleix que 3sin(x)x²>0 i x>0, a més a més sempre es compleix que (cos³(x)-1)<0 i,
per tant
g(x)=-3sin(x)x²+2x(cos³(x)-1)<2x(cos³(x)-1)<0
mentres que en el interval [-PI/2;0) es compleix que 3sin(x)x²<0 i x<0 i podem deduir que
g(x)=-3sin(x)x²+2x(cos³(x)-1)>2x(cos³(x)-1)>0
per tant f(x)<3/2 en el interval [-PI/2;PI/2]\{0}.
per altra banda notem que sqrt(2)<PI/2 i que, per |x|>sqrt(2) es compleix que
(1-cos³(x))/x²<3/2 	<=>	 2*(1-cos³(x))<3x²
en quant (1-cos³(x))<2<x² i, per tant,
2*(1-cos³(x))<=4<6<3x²
per tant podem concloure que es compleix f(x)<3/2 per x pertanyent a R\[-sqrt(2);sqrt(2)].
Unint els dos intervals en els que es compleix la inequació obtenim que f(x)<3/2 per tot x diferent de 0 pertanyent a R.
*/
#include <stdio.h>
#include <math.h>
/*definim el punt x0*/
#define x0 0.000011

int main(){
	double x;
	float y;
	x=0;
	/*Fem un bucle que demani per pantalla la introducció de un npmbre diferent de 0 i que ho segueixi fent fins
	que no s'introdueixi un un valor valid (diferent de 0) tal i com indica la condició del if*/
	while (x==0){
		printf ("\nIntrodueix el punt (diferent de 0) en el que vols evaluar f(x)=(1-cos³(x))/x²\n");
		/*guardem el nombre introduit per pantalla en la variable x com a double*/
		scanf ("%lf", &x);
		/*guardem el nombre guardat en x en la variable y com a float*/
		y=(float)(x);
		if (x==0){
			/*Si el nombre introduit és 0 tornem a demanar*/
			printf ("Si us plau introdueix un nombre diferent de 0\n");
		}
	}
	/*Evaluem la funció f(x)=(1-cos³(x))/x² en el punt guardat en la variable y el qual te precisió simple i guardem 
	el resultat en la mateixa variable amb precisió simple (estem evaluant f amb precisió simple)*/
	y=(1-pow(cos(y),3))/pow(y,2);
	/*Evaluem la funció f(x)=(1-cos³(x))/x² en el punt guardat en la variable x el qual te precisió doble i guardem
	el resultat en la mateixa variable amb precisió doble (estem evaluant f amb precisió doble)*/
	x=(1-pow(cos(x),3))/pow(x,2);
	/*Mostrem per pantalla els resultats obtinguts mostrant 10 decimals*/
	printf ("\nEvaluant f en el punt demanat amb una precisió simple obtenim com a resultat %.10f mentres que si la evaluem amb una precisio doble obtenim %.10g\n", y, x);
	/*guardem el punt x0 amb precisió simple en la variable y i amb precisió doble en la variable x*/
	y=(float)(x0);
	x=(double)(x0);
	/*Evaluem la funció en el punt x0 guardat amb precisió simple i en el punt x0 guardat amb precisió doble.
	Guardem els resultat amb precisió simple i precisió doble respectivament*/
	y=(1-pow(cos((y)),3))/pow(y,2);
	x=(1-pow(cos(x),3))/pow(x,2);
	/*Mostrem per pantalla els resultats obtinguts juntament amb el resultat obtingut fent el calcul amb una calculadora
	de butxaca i raonem perquè els resultats són diferents*/
	printf ("\n\nEvaluant f en el punt x0=%.*g amb una calculadora de butxaca obtenim\n0\nMentres que si ho calculem amb precisió simple obtenim\n%.*f\nI si ho calculem amb precisió doble obtenim\n%.*g\n\n",6,x0, 10,y, 10,x);
	printf ("La causa principal d'aquest error ve donada per la resta 1-cos³(x), per x prou petit 1-cos³(x)->0 en altres paraules es produeix una cancelació i això provoca que l'error relatiu es dispari arribant a assumir valors del ordre de Er*10^10 on Er indica l'epsilon màquina.\n");
	/*Proposem una nova forma de evaluar f que suposem hauria de eliminar els errors de cancelació en quant només 
	presenta productes, divisions i sumes entre nombres positius (no hi ha restes que puguin causar cancelacions).*/
	printf ("Podem evitar aquesta font d'error si fem el següent canvi\nf(x)=(1-cos³(x))/x²=\n=(1+cos(x))/(1+cos(x))*((1-cos(x))(1+cos(x)+cos²(x))/x²)=\n=((1-cos²(x))/x²)((1+cos(x)+cos²(x))/(1+cos(x)))=\n=(sin²(x)/x²)((1+cos(x)+cos²(x))/(1+cos(x)))\nQue ens estalvia cancelacions al voltant del 0.\n");	
	/*Tornem a guardar el punt x0 amb precisió simple en la variable y i amb precisió doble en la variable x*/
	y=(float)(x0);
	x=(double)(x0);
	/*Evaluem la funció f escrita de la nova forma f(x)=(sin²(x)/x²)((1+cos(x)+cos²(x))/(1+cos(x))) en el punt x0
	guardat amb precisió simple i en el punt x0 guardat amb precisió doble. Guardem els resultat amb precisió simple
	i precisió doble respectivament*/
	y=(pow(sin(y),2)/pow(y,2))*((1+cos(y)+pow(cos(y),2))/(1+cos(y)));
	x=(pow(sin(x),2)/pow(x,2))*((1+cos(x)+pow(cos(x),2))/(1+cos(x)));
	/*Mostrem per pantalla els resultats amb 15 decimals i els discutim*/
	printf ("\nEfectivament si tornem a evaluar f amb les modificacions en el punt x0 obtenim\n0.02618\nAmb la calculadora de butxaca\n%.*f\nAmb precisió simple i\n%.*g\nAmb precisió doble\n", 15,y, 15,x);
	printf ("\nCom podem observar la propagació del error inicial s'ha reduït de forma considerable ja que elr resultats amb precisió simple i amb precisió doble són molt mes propers (la calculadora de butxaca segueix donant valors disparatats però millors que abans).\n\n");
}