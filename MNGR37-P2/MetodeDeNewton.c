#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

double g(double);

int main(){
	int i, n;
	double x, error, Aitken[1000];
	x=2;
	Aitken[0]=x;
	//ponemos el contador de iteraciones a 0 i iniciamos con un error lo bastante grande como para que se cumpla la
	//condición del while;
	i=0;
	error=1;
	//hacemos iteraciones hasta que el error sea lo suficientemente pequeño como para dar 16 decimales exactos
	//o hasta que súperamos el límite de iteraciones.
	while (error>ZERO && i<1000){
		error=g(x);
		x-=error;
		error=fabs(error);
		//guardamos los iterados en el vector aitken que utilizaremos más adelante.
		Aitken[i]=x;
		i++;
	}
	//si superamos el límite de iteraciones significa que la sucesión no converge. mostramos un mensaje por pantalla
	//y finalizamos la función.
	if (i==1000){
		printf("\n\nAplicando el método de Newton para encontrar raices del polinomio P(x)=x³-x-400 partiendo de ");
		printf("x_0=2 no llegamos a una sucesión convergente.");
		return 0;
	}
	//Si la sucesión converge guardamos el número de iteraciones hechas para llegar a la convergencia en la variable n
	//y mostramos el resultado obtenido por pantalla.
	n=i-1;
	printf("\n\nAplicando el mètodo de Newton y con %d iteraciones hemos llegado al resultado\n%.16g\n", n, x);
	//Si es compleix que f(x)==0 significa que el resultat obtingut està tan a prop de la arrel real que la màquina
	//no pot representar la diferència. Si això passa ho diem per pantalla.
	if (g(x)==0){
		printf("Con un error tan pequeño que la màquina no és capaz de representarlo y, por lo tanto, és ");
		printf("equivalente a tener únicamente error de representación.\n\n");
	}
	//Si l'error comés és diferent de 0 aleshores el mostrem per pantalla.
	else{
		printf("Con un error de %.16g\n\n", error);
	}
	//si la sucesión obtenida és demasiado corta como para aplicar el método de aceleración de Aitken lo decimos por
	//pantalla y finalizamos la función.
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta successión perqué no tiene suficientes iterados.\n");
		return 0;
	}
	//Recordemos que hemos guardado el resultado de la sucesión sin acelerar en la variable x. la utilizaremos
	//para determinar la convergencia de la sucesión acelerada.
	i=0;
	//Aplicamos el método de Aitken.
	while (fabs(Aitken[i]-x)>ZERO && i<n-2){
		Aitken[i]=(Aitken[i]*Aitken[i+2]-Aitken[i+1]*Aitken[i+1])/(Aitken[i+2]-2*Aitken[i+1]+Aitken[i]);
		i++;
	}
	//si el método de aceleración no ha conseguido acelerar la sucesión lo decimos por pantalla y finalizamos la
	//función.
	if (i==n-2){
		printf("El mètode d'acceleració de Aitken no ha logrado acelerar la sucesión.\n");
		//una de las condiciones necesarias para poder aplicar el método de aceleración de Aitken és que la raiz no
		//sea un elemento de la sucesión. Si el error és f(x)==0 significa que, para la màquina, el resultado obtenido.
		//mediante el método de Newton y la raiz exacta del polinomio són el mismo número y esto causa que no se pueda
		//aplicar el método de Aitken. Si esto pasa mostramos por pantalla esta explicación.
		if (g(x)==0){
			printf("Esto és debido al hecho que la sucesión dada por el método de newton lleva a un resultado tan ");
			printf("similar a la raiz exacta del polinomio que la màquina no és capaz de distinguir los dos valores ");
			printf("esto causa que no se pueda utilizar el método de aceleración de Aitken dado que una de las ");
			printf("condiciones para poder aplicar el método és que la raiz exacta no pertenezca a la sucesión ");
			printf("que se desea acelerar.\n\n");
		}
		return 0;
	}
	//si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-x), i);
	return 0;
}

double g(double x){
	return (pow(x,3)-x-400)/(3*pow(x,2)-1);
}