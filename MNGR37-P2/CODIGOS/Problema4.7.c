#include <stdio.h>
#include <math.h>

#define ZERO 5.e-248
#define ZERO1 5.e-249

__float128 f(__float128);
__float128 sqrtq(__float128);

//El objetivo de este programa és el de calcular g(g(g(1)))\sqrt{2}/2 y dar una cota superior de este para así poder
//demostrar la desigualdad que se pide en en apartado 4.7
int main(){
	int i;
	__float128 x, y;
	//utilizamos un bucle para calcular g(g(g(1)))
	x=1;
	for (i=0; i<3; i++){
		x=f(x);
	}
	y=sqrtq(2.)/2;
	x*=y;
	if (x<=ZERO){
		printf("\nHemos podido calcular numéricamente el valor de \\sqrt{2}g(g(g(1)))/2 utilizando variables tipo ");
		printf("__float128 y determinar que este és más pequeño que 5.e-248.\n");
	}
	if (x>ZERO1){
		printf("No obstante el mismo valor és mayor a 5.e-249.\n");
	}
	printf("\n");
	return 0;
}


//definimos g(x)=x⁷/(x³+24x²+80x+64)²
__float128 f(__float128 x){
	return x*x*x*x*x*x*x/((x*x*x+24*x*x+80*x+64)*(x*x*x+24*x*x+80*x+64));
}

//esta función calcula la raiz cuadrada de un determinado valor ejorando la aproximación dada por sqrt haciendo dos
//iterados mas del método de newton lo cual deberia almenos duplicar el número de decimales correctos obteniendo así
//la mejor aproximación posible para una variable tipo __float128.
__float128 sqrtq(__float128 x){
	__float128 y;
	y=sqrt(x);
	y=(y+x/y)/2;
	y=(y+x/y)/2;
	return y;
}