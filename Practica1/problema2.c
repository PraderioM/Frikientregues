/*x=(e^t+e^(-t))/2 =>
=> x-e^t=(e^(-t)-e^t)/2 =>
=> (x-e^t)²=(e^(-2t)-2+e^(2t))/4=(e^(-2t)+2+e^(2t))/4-1=x²-1 =>
=> x-e^t=+_sqrt(x²-1) =>
=> e^t=x+_sqrt(x²-1) =>
=> t=log(x+_sqrt(x²-1))
Notem que si x és prou gran i utilitzem el signe - aleshores x-sqrt(x²-1)-> x-x=0 i, per tant, es produeix una cancelació
que dispara l'error relatiu.*/
#include <stdio.h>
#include <math.h>

int main(){
	double x;
	//recordem que cosh és una funció parella i, per tant, cosh(-x)=cosh(x)
	x=cosh(-10);
	x=log(x-sqrt(pow(x,2)-1));
	printf("Intentem calcular arcosh(cosh(-10)) aplicant la formula arccosh(y)=log(x-sqrt(x²-1)) i observem que, tot  que el resultat hauria de ser -10 obtenim com a resultat el nombre\n\n%.*g\n\nAixò és degut al error causat per la cancelació cosh(-10)-sqrt(cosh(-10)²-1) que tendeix a 0 en quant cosh(10)=%g\n",20,x,cosh(-10));
	printf("Podem evitar aquest error si escrivim\n\nlog(x-sqrt(x²-1))=\n=log((x-sqrt(x²-1))(x+sqrt(x²-1))/(x+sqrt(x²-1)))=\n=log((x²-x²+1)/(x+sqrt(x²-1)))=\n=log(1/(x+sqrt(x²-1)))=-log((x+sqrt(x²-1)))\n");
	printf("\nI, per tant, arccosh(y)=+_log(x+sqrt(x²-1))\n");
	x=cosh(-10);
	x=-log(x+sqrt(pow(x,2)-1));
	printf ("\nAplicant aquesta nova fórmula obtenim\n\narcosh(cosh(-10))=%g\n\n",x);
	if (x==-10){
		printf("El resultat exacte,");
	}
	printf (" molt més precis que el resultat anterior.\n\n");
}