#include <stdio.h>
#include <math.h>

int main(){
	float ax, bx, cx, px, Ax;
	double ay, by, cy, py, Ay;
	printf("Com que a, b, c són els costats de un triangle i a>=b>=c aleshores sempre es compleix que a<b+c ");
	printf("Si a>approx b+c aleshores podem concloure que a approx b+c per tant, si definim p=(a+b+c)/2 obtindrem que");
	printf(" p-a=(b+c-a)/2approx 0 i, per tant, es produiria un error de cancelació.\nEls costats de cualsevol");
	printf(" triangle amb un angle prou proper a pi radiants donarà un resultat molt dolent de la mesura de A.\n");
	Ax=0;
	while (Ax==0){
		printf ("\nIntrodueix els valors de a,b,c separats per comes.\n");
		scanf("%lf,%lf,%lf",&ay,&by,&cy);
		if (ay>(by+cy) || by>(ay+cy) || cy>(ay+by)){
			printf ("\n\nERROR\nLes dades introduides no corresponen a les mesures dels costats de un triangle. ");
			printf("Torna a introduir-les.\n");
		}
		else{
			Ax=1;
		}
	}
	py=(ay+by+cy)/2;
	ax=(float)(ay);
	bx=(float)(by);
	cx=(float)(cy);
	px=(ax+bx+cx)/2;
	Ax=sqrt(px*(px-ax)*(px-bx)*(px-cx));
	Ay=sqrt(py*(py-ay)*(py-by)*(py-cy));
	printf ("El resultat de la mesura del area mitjançant la fórmula de Heron és");
	printf("\n%.10f\nEn el cas de precisió simple i\n%.10f\nEn el cas de precisió doble.\n\n",Ax,Ay);
	Ax=sqrt(pow((pow(ax,2)+pow(bx,2)+pow(cx,2)),2)-2*(pow(ax,4)+pow(bx,4)+pow(cx,4)))/4;
	Ay=sqrt(pow((pow(ay,2)+pow(by,2)+pow(cy,2)),2)-2*(pow(ay,4)+pow(by,4)+pow(cy,4)))/4;
	printf("Si modifiquem la formula de la següent manera\n");
	printf("A=sqrt(p(p-a)(p-b)(p-c))=sqrt(((b+c)+a)((b+c)-a)(a+(c-b))(a-(c-b))/16)=\n");
	printf("=sqrt((b+c)²-a²)(a²-(c-b)²))/4=sqrt((2cb)²-(b²+c²-a²)²)/4=\n=sqrt(2(a²b²+b²c²+c²a²)-(a⁴+b⁴+c⁴))/4=\n");
	printf("=sqrt((a²+b²+c²)²-2(a⁴+b⁴+c⁴))/4\n");
	printf("Podem reduir l'error en quant eliminarem cancelacions obtenint\n");
	printf("%.10f\nEn el cas de precisió simple i \n%.10f\nEn el cas de precisió doble.\n\n", Ax, Ay);
	return 0;
}