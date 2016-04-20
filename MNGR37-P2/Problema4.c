#include <stdio.h>
#include <math.h>

#define ZERO 1.e-16

double f(double);
double g(double);

/*La finalidad de este programa és hacer los calculos asociados al ejercicio 4 de la pràctica 2 y mostrar por pantalla
los resultados*/
int main(){
	double x,prod ,a,b, error;
	int i, k;
	//mostramos el resultado del apartado a.
	printf("Buscando el aproximante de Paé de la función \\sqrt{1+x} obtenemos como resultado la función\n");
	printf("f(x)=(3x+4)/(x+4)\n\n\n");
	//mostramos el resultado del apartado b.
	printf("Demostremos ahora por inducción que si \\sqrt{1+x}=f(x)\\sqrt{1+g(x)} entonces\n");
	printf("\\sqrt{1+x}=(\\prod_{j=0}^{n}b_j)\\sqrt{1+a_{n+1}}\n");
	printf("Donde a_0=x, a_{i+1}=g(a_i)  b_i=f(a_i)\n\n");
	printf("Para n=0 tenemos la identidad \\sqrt{1+x}=f(x)\\sqrt{1+g(x)} la cual és cierta cor hipótesis");
	printf("Suponiendo que la identidad és cierta para n-1 podemos escribir el iterado número n como\n");
	printf("(\\prod_{j=0}^{n}b_j)\\sqrt{1+a_{n+1}}=(\\prod_{j=0}^{n}f(a_j))\\sqrt{1+g(a_n)}=\n");
	printf("=(\\prod_{j=0}^{n-1}f(a_j))f(a_n)\\sqrt{1+g(a_n)}\\sqrt{1+a_n}/\\sqrt{1+a_n}=\n");
	printf("=(\\prod_{j=0}^{n-1}f(a_j))\\sqrt{1+g(a_{n-1})}f(a_n)\\sqrt{1+g(a_n)}/\\sqrt{1+a_n}\n\n");
	printf("por hipótesis tenemos que\n(\\prod_{j=0}^{n-1}f(a_j))\\sqrt{1+g(a_{n-1})}=\\sqrt{1+x}\ny que\n");
	printf("f(a_n)\\sqrt{1+g(a_n)}=\\sqrt{1+a_n}\nPor lo tanto podemos reescribir la identidad anterior como\n");
	printf("(\\prod_{j=0}^{n}b_j)\\sqrt{1+a_{n+1}}=\\sqrt{1+x}\\sqrt{1+a_n}/\\sqrt{1+a_n}=\\sqrt{1+x}\n\n");
	printf("Queda por lo tanto demostrado que\n\\sqrt{1+x}=(\\prod_{j=0}^{n}b_j)\\sqrt{1+a_{n+1}}\nPara todo n\n\n\n");
	//Mostramos el programa pedido en el apartado c.
	printf("Calculando la aproximada de Padé como quociente de dos cúbicas obtenemos como resultado las funciones\n");
	printf("f(x)=(7x³+56x²+112x+64)/(x³+24x²+80x+64)\n");
	printf("y\ng(x)=x⁷/(x³+24x²+80x+64)²\n\n");
	//Motivamos porquè queremos ver que g(x) és contractiva para x>0 y lo demostramos.
	printf("Si ahora demostramos que g(x) és contractiva para x>0 y tiene como punto fijo el origen obtendremos que la serie ");
	printf("{a_n} definida por recurrencia como a_{n+1}=g(a_n) tendirà a 0 cuando n tienda a infinito y, por lo tanto, ");
	printf("cuando n tienda a infinito, se cumplirà que \\sqrt{1+a_n} tendirà a 1 y dado que se cumple la identidad\n");
	printf("\\sqrt{1+x}=(\\prod_{j=0}^{n}b_j)\\sqrt{1+a_{n+1}}\n obtendremos que, cuando n tienda a infinito, el ");
	printf("productorio (\\prod_{j=0}^{n}b_j) tendirà a \\sqrt{1+x}.\nPodremos por lo tanto ");
	printf("calcular una aproximación de \\sqrt{1+x} (con x>0) como el producto (\\prod_{j=0}^{n}b_j)\n\n");
	printf("Ver que 0 és punto fijo para g és trivial dado que, por definición de g(x) tenemos que g(0)=0/64=0\n");
	printf("Veamos ahora que la función g és contractiva para todo x>0.\nCalculando g'(x) y g''(x) obtenemos que, ");
	printf("para x>0, ambas són estrictamente positivas. Explicitamente tenemos que\n");
	printf("g'(x)=x⁶(x³+72x²+400x+448)/(x³+24x²+80x+64)³\n");
	printf("Por lo tanto podemos afirmar que \\lim_{x\\to \\infty}g'(x)=1 y, dado que la derivada segunda de x és ");
	printf("Estrictamente positiva para x>0 entonces podemos afirmar que la función g'(x) és estrictamente creciente ");
	printf("para x>0. Podemos por lo tanto concluir que g'(x)<\\lim_{x\\to \\infty}g'(x)=1 para todo x>0 y, además, ");
	printf("g'(x)>g'(0)=0 para todo x>0. En resumen tenemos que, para todo x>0 se cumple 0<g'(x)<1.\nCojamos ahora ");
	printf("x_1>x_2>0 culesquiera. Aplicando el teorema del valor medio tendremos que\ng(x_1)-g(x_2)=g'(c)(x1-x_2)\n");
	printf("donde c és un valor desconocido entre x_2 i x_1. Pasando a módulos y aplicando que |g'(c)|<1 tal y como ");
	printf("ya hemos visto obtenemos\n|g(x_1)-g(x_2)|=|g'(c)(x1-x_2)|=|g'(c)||x1-x_2|<|x1-x_2|\nQueda así demostrado ");
	printf("que g(x) és contractiva para todo x>0 con el origen como punto fijo y, por lo tanto, por lo que ya hemos ");
	printf("visto, el productorio (\\prod_{j=0}^{n}b_j) tiende a \\sqrt{1+x} cuando n tiende a infinito.\n");
	//Demostremos que g(x)=O(x⁷)
	printf("\nAntes de proseguir és interesante estudiar con que velocidad el producto (\\prod_{j=0}^{n}b_j) tiende ");
	printf("a la raiz \\sqrt{1+x} con x>0. Como hemos visto anteriormente la convergencia del producto està estrictamente ");
	printf("relacionada con la velocidad de la convergencia {a_n} definida como a_0=x a_{n+1}=g(a_n).\n");
	printf("Resulta por lo tanto interesante estudiar como de ràpido g(x) tiende a 0. És bastante trivial ver que g(x)");
	printf("tiende a 0 con la misma velocidad con que x⁷ tiende a 0 (lo cual equivale a decir que g(x)=O(x⁷)). Para ");
	printf("verlo solo hace falta ver que existe el límite \\lim_{x\\to 0}x⁷/g(x) i que és finito. Efectivamente se ");
	printf("cumple que\n");
	printf("\\lim_{x\\to 0}x⁷/g(x)=\\lim_{x\\to 0}x⁷(x³+24x²+80x+64)²/x⁷=\\lim_{x\\to 0}(x³+24x²+80x+64)²=64\n");
	printf("Por lo tanto la serie {a_n} converge a 0 con orden de convergencia 7 lo cual nos indica (no demuestra) ");
	printf("que el producto (\\prod_{j=0}^{n}b_j) tiende a \\sqrt{1+x} con el mismo orden de convergencia.\n");
	//Demostremos ahora que se cumple la inequación del apartado f.
	printf("Demostremos ahora que se cumple\n|\\sqrt{1+x}-(\\prod_{j=0}^{n}b_j)|<_a_{n+1}/2\\sqrt{1+x}\n");
	printf("Lo cual, combinado con lo que hemos demostrado anteriormente, nos lleva a deducir que el producto ");
	printf("(\\prod_{j=0}^{n}b_j) converge hacia \\sqrt{1+x} almenos igual de ràpido que una sucesión con orden ");
	printf("de convergencia 7\nPara demostrar esta desigualdad tendremos que expandir por Taylor de orden 2 la siguiente ");
	printf("identidad demostrada perviamente\n");
	printf("\\sqrt{1+x}=(\\prod_{j=0}^{n}b_j)\\sqrt{1+a_{n+1}}=(\\prod_{j=0}^{n}b_j)(1+a_{n+1}/2-c²/8)\n");
	printf("Donde c és un valor desconocido entre 0 i a_{n+1}.\nDado que c>0 y el producto és positivo y menor que ");
	printf("a_{n+1} podemos convertir la identidad anterior en la inequación\n");
	printf("\\sqrt{1+x}<_(\\prod_{j=0}^{n}b_j)(1+a_{n+1}/2)\nReescribiendo obtenemos\n");
	printf("\\sqrt{1+x}-(\\prod_{j=0}^{n}b_j)<_a_{n+1}/2(\\prod_{j=0}^{n}b_j)\nAdemás el producto és creciente porque ");
	printf("\n(\\prod_{j=0}^{n+1}b_j)=f(a_n)(\\prod_{j=0}^{n}b_j)\ny tenemos que\n");
	printf("f(x)=(7x³+56x²+112x+64)/(x³+24x²+80x+64)=1+6x³/(x³+24x²+80x+64)>1 para todo x>0.\n");
	printf("Por lo tanto, dado que el producto és creciente y tiende a \\sqrt{1+x} podemos deducir que, para todo n ");
	printf("se cumple que (\\prod_{j=0}^{n}b_j)<\\sqrt{1+x} podemos así reescribir la inequación anterior como\n");
	printf("\\sqrt{1+x}-(\\prod_{j=0}^{n}b_j)<_a_{n+1}/2(\\prod_{j=0}^{n}b_j)<a_{n+1}/2\\sqrt{1+x}\n");
	printf("Dado ademàs que, tal y como hemos dicho \\sqrt{1+x}>(\\prod_{j=0}^{n}b_j) entonces tendremos que\n");
	printf("|\\sqrt{1+x}-(\\prod_{j=0}^{n}b_j)|=\\sqrt{1+x}-(\\prod_{j=0}^{n}b_j)\ny combinando esto con los ");
	printf("resultados anteriores obtenemos finalmente que\n|\\sqrt{1+x}-(\\prod_{j=0}^{n}b_j)|<_a_{n+1}/2\\sqrt{1+x}");
	printf("Utilizando esta cota del error podemos calcular con precisión la raiz de \\sqrt{1+x} para x>0. Vamos a ");
	printf("comprobarlo.\n\n");
	//realizamos los calculos.
	printf("Introduce el número del que quieres aproximar la raíz (más grande que 1)\n");
	scanf("%lf", &x);
	while (x<1){
		printf("Ha habido un error en la introducción del número, por favor vuelve a introducirlo.\n\n");
		printf("Introduce el número del que quieres aproximar la raíz (más grande que 1)\n");
		scanf("%lf", &x);
	}
	//escribimos la raiz pedida como \sqrt{1+x}
	x--;
	//ponemos las condiciones iniciales.
	prod=1;
	error=1;
	//definimos k como una cota superior de \sqrt{1+x} que nos servirà para calcular una cota superior de la i-ésima
	//iteración de nuestro programa que, como ya hemos visto, viene dada por a_{n+1}\sqrt{1+x}/2
	k=ceil(sqrt(x+1));
	i=0;
	while (error>ZERO && i<100){
		a=g(x);
		b=f(x);
		x=a;
		prod*=b;
		error=fabs(a*k/2);
		i++;
	}
	if (i==0){
		printf("Tras 100 iterados no hemos conseguido obtener un error menor de 1.e-16.\n");
		printf("El mejor resultado obtenido ha sido %.16g con un error de %.16g\n", prod, error);
	}
	else{
		printf("Tras %d iteraciones hemos obtenido el resultado\n%.16g\n", i, prod);
		if (error==0){
			printf("Con un error tan pequeño que la màquina no lo diferencia del 0. Si no hubiese errores de ");
			printf("representación el error seria igual o menor a 5x10⁻³²⁴.\n");
		}
		else{
			printf("Con un error menor a 1.e-16 de\n%.16g\n", error);
		}
		if (i<5){
			printf("Como podemos comprobar la sucesión converge extremadamente ràpido tal y como cabia esperar de una ");
			printf("sucesión con orden de convergencia almenos 7.\n");
		}
	}
	printf("\n");
	return 0;
}

/*esta función toma como valor de entrada un número x i devuelve el resultado de la operación
(7x³+56x²+112x+64)/(x³+24x²+80x+64)*/
double f(double x){
	x=(7*x*x*x+56*x*x+112*x+64)/(x*x*x+24*x*x+80*x+64);
	return x;
}

/*esta función toma como valor de entrada un número x i devuelve el resultado de la operación
(1+x)/(f(x))²-1
donde la función f és la que està definida previamente en este mismo programa.*/
double g(double x){
	double y;
	y=f(x);
	x=(1+x)/(y*y)-1;
    return x;
}