#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

int potenceof2(unsigned short);
double potenceof2bo(double, unsigned short);

//la finalidad de este programa és hacer los calculos asociados al ejercicio 3 de la pràctica 2 y mostrar por pantalla
//los resultados obtenidos.
int main(){
	int i, millor, igual, n;
	unsigned short j;
	double a, b, c, s, aux, error, errorant, errormenor, Aitken[1000];
	//presentamos por pantalla el ejercicio.
	printf("Calculando numèricamente con precisión doble la sucesión descrita en el problema 3 obtenemos los ");
	printf("siguientes resultados notables.\n");
	//ponemos las condiciones iniciales
	a=1.;
	b=1./sqrt(2);
	s=1./2;
	Aitken[0]=2*a*a/s;
	//iniciamos la cuenta
	j=0;
	//experimentando hemos notado que la sucesión oscila por lo tanto guardaremos en la variable millor el iterado
	//en el que se consigue la mejor aproximación de pi i en la variable igual iterados mayores que millor en el que
	//la aproximación de pi sea igual de buena
	millor=0;
	n=-1;
	error=fabs(Aitken[0]-M_PI);
	errormenor=error;
	while (error>ZERO && j<1000){
		j++;
		aux=a;
		a=(a+b)/2;
		b=sqrt(aux*b);
		c=a*a-b*b;
		/*probando dos maneras diferentes de multiplicar por una potencia de 2 hemos determinado que la que
		da un resultado mas exacto és la que que se puede ver comentada en la siguiente linea
		s-=potenceof2(j)*c;
		no obstante el hecho de que el resultado obtenido sea más preciso és completamente casual dado que la funcion
		potenceof2 produce overflow en el iterado 31 debido a la longitud finita de la variable tipo int por lo tanto
		hemos optado por el siguiente mètodo que, aunque no llega a un resultado tan exacto, sabemos que és correcto*/
		s-=potenceof2bo(c,j);
		Aitken[j]=2*a*a/s;
		errorant=error;
		error=fabs(Aitken[j]-M_PI);
		if (n==-1 && error>errorant){
			printf("En el iterado número %d el error ha empezado a crecer pasando de\n%.16g\na\n%.16g\n\n", j, fabs(Aitken[j-1]-M_PI), fabs(Aitken[j]-M_PI));
			n=1;
		}
		else if(n==1 && error<errorant){
			printf("En el iterado número %d el error ha empezado a decrecer pasando de\n%.16g\na\n%.16g\n\n", j, fabs(Aitken[j-1]-M_PI), fabs(Aitken[j]-M_PI));
			n=-1;
		}
		if (error<errormenor){
			errormenor=error;
			millor=j;
		}
	}
	//si el error no para de crecer imprimimos por pantalla una explicación.
	if (n==1){
		printf("El hecho de que a partir del iterado %d el error haya seguido creciendo nos indica que, ", millor);
		printf("a partir de este iterado la convergencia degenera a causa de la precisión finita\n\n");
	}
	//hacemos lo mismo si decrece pero no lo suficiente como para igualar valores anteriores.
	if (n==-1 && errormenor<error){
		printf("El hecho de que hasta el iterado %d no se haya podido mejorar el resultado obtenido en el iterado ",j);
		printf("%d nos indica que, a partir de este iterado, la convergencia degenera a causa de ", millor);
		printf("la precisión finita\n\n");
	}
	n=j;
	//si s'arriba al iterat 1000 aleshores significa que la successió no ha pogut convergir i ho mostrem per pantalla.
	if (j==1000){
		printf("No hemos conseguido obtener 16 decimales correctos de pi y la mejor aproximación a la que ");
		printf("hemos podido llegar se ha dado por primera vez en el iterado %d con el valor\n", millor);
		printf("%.16g\ny un error de %g\n\n", Aitken[millor], fabs(errormenor));
	}
	else{
		printf("En el iterado número %d obtenemos el valor \n%.16g\nEl cual aproxima pi ", millor, Aitken[millor]);
		if (errormenor!=0){
			printf("con un error de %.g\n", errormenor);
		}
		else{
			printf("únicamente con error de representación que para precisión doble és de 5e-16 (si guardamos en una ");
			printf("variable de precisión doble la diferencia entre una aproximación de pi con 15 decimales correctos ");
			printf("y la constante M_PI guardada en la libreria math.h y que representa pi con 20 decimales correctos ");
			printf("obtenemos como resultado 0).\n");
		}
	}
	printf("Además calculando el error asociado a las últimas 4 iteraciones previas a la mejor aproximación (incluida)");
	printf("de pi obtenida (tengamos en cuenta de que el error debido a representación és como mínimo de 5e-16) ");
	printf("obtenemos:\n\n");
	for (i=millor-4; i<millor; i++){
		a=fabs(Aitken[i+1]-M_PI);
		if (a==0){
			a=5.e-16;
		}
		printf("%g\n", a);
	}
	if (errormenor!=0){
		printf("\nEl error debido a la finitud de la representación de tipo double no nos permite hacer un analisis ");
		printf("preciso del orden de convergencia dado que, a partir de los resultados obtenidos, podria resultar ser ");
		printf("tanto lineal (con una constante assimptotica del orden de 10⁻⁴) como cuadràtico (és razonable pensar ");
		printf("que el número de cifras signitivas no se duplica en la última iteración debido a que la precisión ");
		printf("limitada de la variable tipo double no se lo permite al generar errores de magnitud superior a 10⁻²⁰) ");
		printf("serà necesario repetir los calculos con una precisión mayor para poder dar una respuesta concluyente.\n");
	}
	else{

	}
	i=0;
	while (fabs(Aitken[i]-M_PI)>errormenor && i<millor-2){
		Aitken[i]=(Aitken[i]*Aitken[i+2]-Aitken[i+1]*Aitken[i+1])/(Aitken[i+2]-2*Aitken[i+1]+Aitken[i]);
		i++;
	}
	if (i==millor-2){
		printf("\nEl método de acceleración de Aitken no ha funcionado");
		if (millor<=4){
			printf(" probablemente debido a la escasa longitud de la sucesión a acelerar");
		}
		printf(".\n\n");
	}
	else{
		printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
		printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-M_PI), i);
	}

}

//esta función calcula potencias de 2 mediante operaciones bit a bit lo cual provoca menos error que la función pow.
int potenceof2(unsigned short n){
	int p=1;
	p=p<<n;
	printf("%d\n",p);
	return p;
}

//esta función toma como parametros un double positivo x i un entero corto n (16 bits) i hace operaciones bit a bit para
//devolver el resultado x*2^n;
double potenceof2bo(double x, unsigned short n){
	n=n<<4;
	((unsigned short*)&x)[3]+=n;
	if (x<0){
		printf("\n\nSe ha producido un overflow en el iterado %d\n\n",n);
	}
	return x;
}