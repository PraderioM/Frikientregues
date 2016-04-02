#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

double f(double);

int main(){
	int i, n;
	double a, b, Aitken[1000], s, error;
	//definimos los dos valores que dan inicio al método de la bisección sabiendo que f(a)*f(b)<0
	a=2;
	b=8;
	//nos aseguramos de que se cumpla f(a)<0 y f(b)>0
	if (f(a)>f(b)){
		Aitken[0]=b;
		b=a;
		a=Aitken[0];
	}
	//El error és inicialmente |b-a| dado que lo único que sabemos és que el zero se encuentra en el intervalo [a,b];
	error=fabs(b-a);
	//ponemos el contador de iteraciones a 0;
	i=0;
	//hacemos iteraciones hasta que el error sea lo suficientemente pequeño como para dar 16 decimales exactos
	//o hasta que súperamos el límite de iteraciones (cosa que no pasarà dado que el mètodo de la bisección siempre
	//converge si las condiciones iniciales són correctas)
	while (error>ZERO && i<1000){
		//guardamos cada iterado de la sucesión en el vector Aitken que luego utilizaremos.
		Aitken[i]=(a+b)/2;
		//guardamos el valor de la función evaluada en Aitken[i] en la variable s (signo) que nos servirà para comprobar
		//si la función en ese punto és positiva nula o negativa sin tener que volver a evaluar la función.
		s=f(Aitken[i]);
		//Aplicamos una iteración del método de bisección.
		if (s>0){
			b=Aitken[i];
		}
		//si la función vale exactamente 0 hemos encontrado el 0 de la función, contamos el iterado
		//hecho y salimos del bucle while
		else if (s==0){
			//denotamos que la raiz és un elemento de la sucesión igualando el error a -1.
			error=-1;
			i++;
			break;
		}
		else{
			a=Aitken[i];
		}
		//tras aplicar un iteración el método se reduce a la mitad y contamos la iteración hecha.
		error/=2;
		i++;
	}
	//guardamos el número de iteraciones hechas para llegar a la convergencia en la variable n
	//y mostramos el resultado obtenido por pantalla.
	n=i;
	printf("\n\nAplicando el mètodo de la bisección en el intervalo [2,8] y con %d iteraciones hemos llegado al ", i);
	printf("resultado\n%.16g\n", Aitken[n-1]);
	//si el error és -1 significa que hemos llegado al resultado exacto y lo decimos por pantalla.
	if (error==-1){
		printf("Con únicamente error de representación dado que, \n");
		printf("afortunadamente, hemos caido en el valor exacto de la raiz en uno de los iterados.\n");
	}
	//en caso contrario mostramos el error.
	else{
		printf("Con un error de %.16g\n", error);
	}
	//si la sucesión obtenida és demasiado corta como para aplicar el método de aceleración de Aitken lo decimos por
	//pantalla y finalizamos la función.
	if(n<=2){
		printf("\nNo és posible aplicar el método de Aitken a esta sucesión perqué no tiene suficientes iterados.\n");
		return 0;
	}
	//guardamos el resultado obtenido en la sucesión sin acelerar en la variable b. la utilizaremos para determinar
	//la convergencia de la sucesión acelerada.
	b=Aitken[n-1];
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

double f(double x){
	return pow(x,3)-x-400;
}