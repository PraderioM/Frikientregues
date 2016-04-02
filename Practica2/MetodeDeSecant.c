#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

double f(double);

int main(){
	int i, n;
	double a, b, error, Aitken[1000];
	a=2;
	b=8;
	Aitken[0]=a;
	//ponemos el contador de iteraciones a 0 y damos un valor inicial del error lo bastante grande como para que
	//se entre en el bucle del while.
	i=0;
	error=1;
	//hacemos iteraciones hasta que el error sea lo suficientemente pequeño como para dar 16 decimales exactos
	//o hasta que súperamos el límite de iteraciones.
	while (error>ZERO && i<1000){
		//guardamos los elementos de la sucesión el el vector Aitken que usaremos más adelante.
		Aitken[i+1]=b;
		//Si caiem en el alor exacte del polinomi ho notifiquem amb error=-1 i sortim del bucle després de haver
		//comptat la iteració.
		if (f(b)==0){
			error=-1;
			i++;
			break;
		}
		b=a-f(a)*(b-a)/(f(b)-f(a));
		a=Aitken[i+1];
		error=fabs(b-a);
		i++;
	}
	//Si superamos el límite de iteraciones significa que la sucesión no converge. mostramos un mensaje por pantalla
	//y finalizamos la función.
	if (i==1000){
		printf("\n\nAplicando el método de la secante para encontrar raices del polinomio P(x)=x³-x-400 partiendo de ");
		printf("los valores iniciales x_0=2 y x_1=8 no obtenemos una sucesión convergente.\n\n");
		return 0;
	}
	//Si la sucesión converge guardamos el número de iteraciones hechas para llegar a la convergencia en la variable n
	//y mostramos el resultado obtenido por pantalla.
	n=i;
	printf("\n\nAplicando el mètodo de la secante en el intervalo [2,8] y con %d iteraciones hemos llegado al ", i);
	printf("resultado\n%.16g\n", Aitken[n]);
	//si el error és -1 significa que hemos llegado al resultado exacto y lo decimos por pantalla.
	if (error==-1){
		printf("Con únicamente error de representación dado que, ");
		printf("afortunadamente, hemos caido en el valor exacto de la raiz en uno de los iterados.\n");
	}
	//en caso contrario mostramos el error.
	else{
		printf("Con un error de %.16g\n", error);
	}
	//si la sucesión obtenida és demasiado corta como para aplicar el método de aceleración de Aitken lo decimos por
	//pantalla y finalizamos la función.
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta successión perqué no tiene suficientes iterados.\n");
		return 0;
	}
	//Recordemos que hemos guardado el resultado de la sucesión sin acelerar en la variable b. la utilizaremos
	//para determinar la convergencia de la sucesión acelerada.
	i=0;
	//Aplicamos el método de Aitken.
	while (fabs(Aitken[i]-b)>ZERO && i<n-2){
		Aitken[i]=(Aitken[i]*Aitken[i+2]-Aitken[i+1]*Aitken[i+1])/(Aitken[i+2]-2*Aitken[i+1]+Aitken[i]);
		i++;
	}
	//si el método de aceleración no ha conseguido acelerar la sucesión lo decimos por pantalla y finalizamos la
	//función.
	if (i==n-2){
		printf("\nEl mètode d'acceleració de Aitken no ha logrado acelerar la sucesión.\n");
		//una de las condiciones necesarias para poder aplicar el método de aceleración de Aitken és que la raiz no
		//sea un elemento de la sucesión. Si el étodo de Aitken no funciona y esto pasa mostramos por pantalla la
		//causa del fallo.
		if (error==-1){
			printf("Esto és debido al hecho que la sucesión dada por el método de la bisección tiene como ");
			printf("elemento la raiz exacta del polinomio.");
			printf("Esto causa que no se pueda utilizar el método de aceleración de Aitken dedo que una de las ");
			printf("condiciones para poder aplicar el método és que la raiz exacta no pertenezac a la sucesión ");
			printf("que se desea acelerar.\n\n");
		}
		return 0;
	}
	//Si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	return 0;
}


//fem una funció que avalui la funció que volem en un punt i retorni el seu valor
double f(double x){
	return pow(x,3)-x-400;
}