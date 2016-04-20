#include <stdio.h>
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
	printf("\nx=\\sqrt[3]{200+\\sqrt{200²-1/3³}}+\\sqrt[3]{200-\\sqrt{200²-1/3³}}\n\nLa cual producirà error de ");
	printf("cancelación en la resta de la segunda raíz cúbica en cuanto 200 és aproximadamente igual a ");
	printf("\\sqrt{200²-1/3³}\n");
	//calculamos la fórmula con doble precisión sumamos las fracciones manualmente para reducir ligeramente los errores.
	x=pow(200+sqrt(1079999./3)/3,1./3)+pow(200-sqrt(1079999./3)/3,1./3);
	printf("Haciendo el calculo con doble precisión obtenemos como resultado el valor %g ", x);
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
	printf("teoricamente, el método de Aitken se puede aplicar a las tres sucesiones siempre y cuando ");
	printf("las sucesiones tengan un mínimo de iterados y la raiz exacta no forme parte de las sucesiones.");
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
		printf("\nEl mètode d'acceleració de Aitken no ha logrado acelerar la sucesión.\n");
		//una de las condiciones necesarias para poder aplicar el método de aceleración de Aitken és que la raiz no
		//sea un elemento de la sucesión. Si el étodo de Aitken no funciona y esto pasa mostramos por pantalla la
		//causa del fallo.
		if (error==-1){
			printf("Esto és debido al hecho que la sucesión dada por el método de la bisección tiene como ");
			printf("elemento la raiz exacta del polinomio.");
			printf("Esto causa que no se pueda utilizar el método de aceleración de Aitken dedo que una de las ");
			printf("condiciones para poder aplicar el método és que la raiz exacta no pertenezca a la sucesión ");
			printf("que se desea acelerar.\n\n");
		}
		return;
	}
	//Si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	return;
}

//El objetivo de esta función és aplicar el mètodo de la secante para calcular la raiz real del polinomio
//f(x)=x³-x-400 y, sucesivamente, aplicar el mètodo de Aitken para acelerar la sucesión obtenida.
void secante(){
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
		return;
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
	if (i==n-2){
		printf("\nEl mètode d'acceleració de Aitken no ha logrado acelerar la sucesión.\n");
		//una de las condiciones necesarias para poder aplicar el método de aceleración de Aitken és que la raiz no
		//sea un elemento de la sucesión. Si el étodo de Aitken no funciona y esto pasa mostramos por pantalla la
		//causa del fallo.
		if (error==-1){
			printf("Esto és debido al hecho que la sucesión dada por el método de la secante tiene como ");
			printf("elemento la raiz exacta del polinomio.");
			printf("Esto causa que no se pueda utilizar el método de aceleración de Aitken dedo que una de las ");
			printf("condiciones para poder aplicar el método és que la raiz exacta no pertenezca a la sucesión ");
			printf("que se desea acelerar.\n\n");
		}
		return;
	}
	//Si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-b), i);
	return;
}

//El objetivo de esta función és aplicar el mètodo de la secante para calcular la raiz real del polinomio
//f(x)=x³-x-400 y, sucesivamente, aplicar el mètodo de Aitken para acelerar la sucesión obtenida.
void newton(){
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
		return;
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
		return;
	}
	//si la aceleración ha funcionado mostramos los resultados por pantalla.
	printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
	printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-x), i);
	return;
}

//esta función evalua el polinomio x³-x-400 en un punto que toma como parametro de entrada y devuelve
//el resultado obtenido.
double f(double x){
	return x*x*x-x-400;
}

//dado el polinomio p(x)=x³-x-400 esta función evalua la fracción p(x)/p'(x) en un punto que toma como parametro de
//entrada y devuelve el resultado obtenido.
double g(double x){
	return (x*x*x-x-400)/(3*x*x-1);
}