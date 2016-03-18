#include <stdio.h>
#include <math.h>

int main(){
	float ax, bx, cx, px, Ax, aux1x, aux2x;
	double ay, by, cy, py, Ay, aux1y, aux2y;
	/*Mostrem per pantalla una breu demostració del fet que la formula de heron per a calcular arees de triangle
	A=sqrt(p(p-a)(p-b)(p-c)) provoca errors de cancelació en el cas en que un dels costats és aproximadament igual
	a la suma dels altres dos costats. A més a més mostrem per pantalla un perfil del tipus de triangle que
	provocarà errors de cancelació*/
	printf("Tenim que a approx b+c per tant, si definim p=(a+b+c)/2 obtindrem que");
	printf(" p-a=(b+c-a)/2approx 0 i, per tant, es produiria un error de cancelació.\nEls costats de cualsevol");
	printf(" triangle amb un angle prou proper a 0 radiants donarà un resultat molt dolent de la mesura de A ");
	printf("en quant significarà o bé que un dels costats és prou petit com perquè els altres dos siguin prou ");
	printf("similars o bé que hi ha dos angles prou petits com per aconseguir que el tercer sigui lo ");
	printf("suficientment gran com per ser aproximadament igual a la suma dels altres dos.\n");
	/*Demanem per pantalla els costats del triangle del cual volem calcular l'area i els guardem amb precisió doble
	(variables amb sub-index y) i simple (variables amb sub-index x).*/
	Ax=0;
	while (Ax==0){
		printf ("\nIntrodueix els valors de a,b,c separats per comes.\n");
		scanf("%lf,%lf,%lf",&ay,&by,&cy);
		/*Si no es compleix alguna de les condicions del següent if significarà que un dels costats és mes gran
		que la suma dels altres dos i, per tant, no es tractarà de un triangle per tant demanarem que es tornin
		a introduir les dades*/
		if (ay>(by+cy) || by>(ay+cy) || cy>(ay+by)){
			printf ("\n\nERROR\nLes dades introduides no corresponen a les mesures dels costats de un triangle. ");
			printf("Torna a introduir-les.\n");
		}
		/*Si les dades corresponen als costats de un triangle no les tornem a demanar i sortim del bucle
		(Ax=1 s'encarrega de que es deixi de complir la condició per estar en el bucle).*/
		else{
			Ax=1;
		}
	}
	/*calculem el semiperimetre amb precisió doble i guardem el resultat en la variable py*/
	py=(ay+by+cy)/2;
	/*guardem els costats del triangle amb precisió simple en les variables ax, bx i cx*/
	ax=(float)(ay);
	bx=(float)(by);
	cx=(float)(cy);
	/*calculem el semiperímetre amb precisió simple*/
	px=(ax+bx+cx)/2;
	/*Avaluem la fórmula de Heron amb precisió simple*/
	Ax=sqrt(px*(px-ax)*(px-bx)*(px-cx));
	/*Avaluem la fórmula de Heron amb precisió doble*/
	Ay=sqrt(py*(py-ay)*(py-by)*(py-cy));
	/*Mostrem per pantalla els resultats de les dos mesures amb 10 decimals de precisió*/
	printf ("El resultat de la mesura del area mitjançant la fórmula de Heron és");
	printf("\n%.10f\nEn el cas de precisió simple i\n%.10f\nEn el cas de precisió doble.\n\n",Ax,Ay);
	/*Proposem una modificació de la fórmula de Heron A=sqrt((a²+b²+c²)²-2(a⁴+b⁴+c⁴))/4 la cual ha resultat
	la millor entre les fórmules que hem probat i que redueix bastant els errors per cancelació*/
	printf("Si modifiquem la formula de la següent manera\n");
	printf("A=sqrt(p(p-a)(p-b)(p-c))=sqrt((a+b+c)(c-(a-b))(c+(a-b))(a+(b-c)))/4\n");
	printf("Podem reduir l'error molt en alguns casos com per exemple el que");
	printf(" ve donat per un triangle amb dos costats sensiblement més grans ");
	printf("que el tercer el cual és sensiblement més gran que la diferència entre els dos anteriors");
	printf(" situació que es dona sovint en atronomia i que estaria subjecte a errors de cancelació ");
	printf("si fessim servir la primera fórmula.\n");
	/*Avaluem l'area del triangle aplicant la nova fórmula de Heron amb precisió simple i doble*/
	aux1y=ay-by;
	aux2y=by-cy;
	Ay=sqrt((ay+by+cy)*(cy-aux1y)*(cy+aux1y)*(ay+aux2y))/4;
	aux1x=ax-bx;
	aux2x=bx-cx;
	Ax=sqrt((ax+bx+cx)*(cx-aux1x)*(cx+aux1x)*(ax+aux2x))/4;
	/*Mostrem els nous resultats per pantalla.*/
	printf("%.10f\nEn el cas de precisió simple i \n%.10f\nEn el cas de precisió doble.\n\n", Ax, Ay);
	return 0;
}