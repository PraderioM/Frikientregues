#include <stio.h>
#include <math.h>

#define ZERO (1.e-16)/2

void biseccion();
void secante();
void newton();
double f(double);
double g(double);

//El objetivo de este programa és realizar todos los calculos pedidos en el ejercicio 1c de la pràctica 2 y mostrar
//por pantalla los resultados obtenidos.
int main(){
	double x;
	//Mostramos por pantalla una descripción de la primera operación que vamos a realizar
	printf("Para calcular la raiz real del polinomio P(x)=x³-x-400 aplicaremos la fórmula de Cardano Vieta dada por\n");
	printf("INTRODUCIOR FORMULA DE CARDANO VIETA\n");
	//calculamos la fórmula con doble precisión.
	x=3
	printf("Haciendo el calculo con doble precisión obtenemos como resultado el valor %g ", a);
	//Si la raiz obtenida està comprendida entre 2 y 8 tal y como se especifica en la pràctica mostramos
	//este dato por pantalla.
	if (x>=2 && x<=8){
		printf("el cual està coprendido entre 2 i 8");
	}
	//Ahora nos disponemos a calcular la raiz del polinomio mediante los mètodos de Bisección, de la secante y de Newton
	//Y a acelerar las succesiones mediante el mètodo de aceleración de Aitken. Método que, teoricamente, se les 
	//puede aplicar a las tres sucesiones si convergen.
	printf("\n\nCalculemos ahora la raiz del polinomio con hasta 16 decimales correctos mediante los métodos ");
	printf("de Bisección, de la secante y el método de Newton. Sucesivamente intentaremos aplicar el Método ");
	printf("de aceleración de Aitken para acelerar las tres sucesiones obtenidas. És fàcil comprobar que, ");
	printf("teoricamente, el método de Aitken se puede aplicar a las tres sucesiones");
	biseccion();
	secante();
	newton();
	return 0;
}

//El objetivo de esta función és aplicar el mètodo de la bisección para calcular la raiz real del polinomio
//f(x)=x³-x-400 y, sucesivamente, aplicar el mètodo de Aitken para acelerar la sucesión obtenida.
void biseccion(){
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
			printf("La raiz és %.16g con únicamente error de representación\n", aux);
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
	printf("resultado\n%.16g\nCon una precisió de %.16g\n\n", Aitken[n-1], error);
	//si la sucesión obtenida és demasiado corta como para aplicar el método de aceleración de Aitken lo decimos por
	//pantalla y finalizamos la función.
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta sucesión perqué no tiene suficientes iterados.\n");
		return;
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
		printf("El mètode d'acceleració de Aitken no ha logrado acelerar la sucesión.\n");
		return;
	}
	//si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
}

//El objetivo de esta función és aplicar el mètodo de la secante para calcular la raiz real del polinomio
//f(x)=x³-x-400 y, sucesivamente, aplicar el mètodo de Aitken para acelerar la sucesión obtenida.
void secante(){
	int i, n;
	double a, b, Aitken[1000] s;
	a=2;
	b=8;
	Aitken[0]=a;
	//ponemos el contador de iteraciones a 0;
	i=0;
	//hacemos iteraciones hasta que el error sea lo suficientemente pequeño como para dar 16 decimales exactos
	//o hasta que súperamos el límite de iteraciones.
	while (fabs(b-a)>ZERO && i<1000){
		//guardamos los elementos de la sucesión el el vector Aitken que usaremos más adelante.
		Aitken[i+1]=b;
		b=a-f(a)*(b-a)/(f(b)-f(a));
		a=Aitken[i+1];
		i++;
	}
	//si superamos el límite de iteraciones significa que la sucesión no converge. mostramos un mensaje por pantalla
	//y finalizamos la función.
	if (i==1000){
		printf("Aplicando el método de la secante para encontrar raices del polinomio P(x)=x³-x-400 partiendo de ");
		printf("los valores iniciales x_0=2 y x_1=8 no llegamos a una sucesión convergente.\n\n");
		return;
	}
	//Si la sucesión converge guardamos el número de iteraciones hechas para llegar a la convergencia en la variable n
	//y mostramos el resultado obtenido por pantalla.
	n=i;
	printf("\nAplicando el método de la secante y en el intervalo [2,8] y con %d iteraciones hemos ", i);
	printf("llegado al resultado\n%.16g\nCon una precisión de %.16g\n", b, fabs(b-a));
	//si la sucesión obtenida és demasiado corta como para aplicar el método de aceleración de Aitken lo decimos por
	//pantalla y finalizamos la función.
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta successión perqué no tiene suficientes iterados.\n");
		return;
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
	if (i==n-2 && n>2){
		printf("El método d'aceleración de Aitken no ha logrado acelerar la sucesión.\n");
		return;
	}
	//si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	return;
}

//El objetivo de esta función és aplicar el mètodo de la secante para calcular la raiz real del polinomio
//f(x)=x³-x-400 y, sucesivamente, aplicar el mètodo de Aitken para acelerar la sucesión obtenida.
void newton(){
	int i, n;
	double x, error;
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
		//guardamos los iterados en el vector aitken que utilizaremos más adelante.
		Aitken[i]=x;
		i++;
	}
	//si superamos el límite de iteraciones significa que la sucesión no converge. mostramos un mensaje por pantalla
	//y finalizamos la función.
	if (i==1000){
		printf("Aplicando el método de Newton para encontrar raices del polinomio P(x)=x³-x-400 partiendo de ");
		printf("x_0=2 no llegamos a una sucesión convergente.");
		return;
	}
	//Si la sucesión converge guardamos el número de iteraciones hechas para llegar a la convergencia en la variable n
	//y mostramos el resultado obtenido por pantalla.
	n=i-1;
	printf("\nAplicando el mètodo de Newton y con %d iteraciones hemos llegado al resultat\n%.16g\ncon ", n, x);
	printf("una precisión de %.16g\n\n", error);
	//si la sucesión obtenida és demasiado corta como para aplicar el método de aceleración de Aitken lo decimos por
	//pantalla y finalizamos la función.
	if(n<=2){
		printf("No és posible aplicar el método de Aitken a esta successión perqué no tiene suficientes iterados.\n");
		return;
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
		return
	}
	//si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	return;
}

//esta función evalua el polinomio x³-x-400 en un punto que toma como parametro de entrada y devuelve
//el resultado obtenido.
double f(double x){
	return pow(x,3)-x-400;
}

//dado el polinomio p(x)=x³-x-400 esta función evalua la fracción p(x)/p'(x) en un punto que toma como parametro de
//entrada y devuelve el resultado obtenido.
double g(double x){
	return (pow(x,3)-x-400)/(3*pow(x,2)-1);
}