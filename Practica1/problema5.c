#include <stdio.h>
#include <math.h>

int main(){
	float ax, bx, cx, px, Ax;
	double ay, by, cy, py, Ay;
	printf("Com que a, b, c són els costats de un triangle i a>=b>=c aleshores sempre es compleix que a<b+c ");
	printf("Si a>approx b+c aleshores podem concloure que a approx b+c per tant, si definim p=(a+b+c)/2 obtindrem que ");
	printf("p-a=(b+c-a)/2approx 0 i, per tant, es produiria un error de cancelació.\nEls costats de cualsevol triangle");
	printf(" amb un angle prou proper a pi radiants donarà un resultat molt dolent de la mesura de A.\n");
	printf ("\nIntrodueix els valors de a,b,c separats per comes.\n");
	scanf("%lf,%lf,%lf",&ay,&by,&cy);
	py=(ay+by+cy)/2;
	ax=(float)(ay);
	bx=(float)(by);
	cx=(float)(cy);
	px=(ax+bx+cx)/2;
	Ax=sqrt(px*(px-ax)*(px-bx)*(px-cx));
	Ay=sqrt(py*(py-ay)*(py-by)*(py-cy));
	printf ("El resultat de la mesura del area mitjançant la fórmula de Heron és\n%f\nEn el cas de precisió simple i\n%f\nEn el cas de precisió doble.\n\n",Ax,Ay);
	Ax=sqrt(px*(pow(px,3)+(ax+bx+cx)*pow(px,2)+(ax*bx+ax*cx+bx*cx)*px+ax*bx*cx));
	Ay=sqrt(py*(pow(py,3)+(ay+by+cy)*pow(py,2)+(ay*by+ay*cy+by*cy)*py+ay*by*cy));
	printf("Si modifiquem la formula convertint-la en\nA=sqrt(p(p³+(a+b+c)p²+(ab+bc+ac)p-abc))\nPodem reduir considerablement l'error en quant eliminarem cancelacions obtenint \n%f\nEn el cas de precisió simple i \n%f\nEn el cas de precisió doble.\n\n", Ax, Ay);
	return 0;
}