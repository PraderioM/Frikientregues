#include <stdio.h>
#include <math.h>

#define ZERO (1.e-16)/2

int potenceof2(int);

//la finalidad de este programa és hacer los calculos asociados al ejercicio 3 de la pràctica 2 y mostrar por pantalla
//los resultados obtenidos.
int main(){
	int i, millor, igual, n;
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
	i=0;
	//experimentando hemos notado que la sucesión oscila por lo tanto guardaremos en la variable millor el iterado
	//en el que se consigue la mejor aproximación de pi i en la variable igual iterados mayores que millor en el que
	//la aproximación de pi sea igual de buena
	millor=0;
	n=-1;
	error=fabs(Aitken[0]-M_PI);
	errormenor=error;
	while (error>ZERO && i<1000){
		i++;
		aux=a;
		a=(a+b)/2;
		b=sqrt(aux*b);
		c=a*a-b*b;
		s-=potenceof2(i)*c;
		Aitken[i]=2*a*a/s;
		errorant=error;
		error=fabs(Aitken[i]-M_PI);
		if (n==-1 && error>errorant){
			printf("En el iterado número %d el error ha empezado a crecer pasando de\n%.16g\na\n%.16g\n\n", i, fabs(Aitken[i-1]-M_PI), fabs(Aitken[i]-M_PI));
			n=1;
		}
		else if(n==1 && error<errorant){
			printf("En el iterado número %d el error ha empezado a decrecer pasando de\n%.16g\na\n%.16g\n\n", i, fabs(Aitken[i-1]-M_PI), fabs(Aitken[i]-M_PI));
			n=-1;
		}
		if (error<errormenor){
			errormenor=error;
			millor=i;
		}
	}
	n=i;
	//si s'arriba al iterat 1000 aleshores significa que la successió no ha pogut convergir i ho mostrem per pantalla.
	if (i==1000){
		printf("No hemos conseguido obtiner 16 decimales correctos de pi y la mejor aproximación a la que ");
		printf("hemos pogdido llegar se ha dado por primera vez en el iterado %d con el valor\n", millor);
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
	printf("obtenemos:\n");
	for (i=millor-4; i<millor; i++){
		a=fabs(Aitken[i+1]-M_PI);
		if (a==0){
			a=5.e-16;
		}
		printf("%g\n", a);
	}
	if (errormenor!=0){
		printf("Como podemos observar a partir de los resultados obtenidos el error varia entre iterado y iterado ");
		printf("de forma lineal (el número de cifras significativas se mantiene igual o diminuye en 1) esto nos ");
		printf("indica que el orden de convergéncia de la serie és lineal y no cuadràtico como sugeria el ");
		printf("enunciado del ejercicio");
	}
	else{

	}
	i=0;
	while (fabs(Aitken[i]-M_PI)>errormenor && i<n-2){
		Aitken[i]=(Aitken[i]*Aitken[i+2]-Aitken[i+1]*Aitken[i+1])/(Aitken[i+2]-2*Aitken[i+1]+Aitken[i]);
		i++;
	}
	if (i==n-2){
		printf("\nEl método de acceleración de Aitken no ha funcionado.\n");
		printf("Esto se debe al hecho que la sucesión se estabiliza (debido a la precisión finita) a partir del ");
		printf("iterado %d ", millor);
		printf("por lo tanto la sucesión tiende al valor que asume a partir de ese iterado y ya hemos ");
		printf("comentado en el apartado anterior que el método de Aitken no funciona para sucesiones ");
		printf("las cuales contienen el número al cual tienden.\n\n");
	}
	else{
		printf("\nAplicando el metodo de aceleración de Aitken obtenemos el resultado\n");
		printf("%.16g\nCon una precisión de %.16g en el iterado %d\n\n", Aitken[i], fabs(Aitken[i]-M_PI), i);
	}

}

//esta función calcula potencias de 2 mediante operaciones bit a bit lo cual provoca menos error que la función pow.
int potenceof2(int n){
	int p=1;
	p=p<<n;
	return p;
}