#include <stdio.h>

int main(){
	int i, LB;
	double z;
	z=(double)1;
	//aquesta part comentada del codi ensenya, en ordre, els 4 bytes que ocupa el nombre z. en la memoria de l'ordinador. 
	/*for (i=0; i<8; i++){
		printf("%d\n", (int)(((unsigned char*)&z)[i]));	
	}*/
	//Si el primer byte és diferent de 0 significarà que l'ordinador guarda les dades en format Big-endian perquè el bit
	//reservat al signe formarà part del primer byte. En cas contrari serà Little-endian.
	if ((int)(((unsigned char*)&z)[0])==0){
		printf("\nEl teu ordinador utilitza el format Little-endian.\n");
		LB=1;
	}
	else{
		printf("\nEl teu ordinador utilitza el format Big-endian.\n");
		LB=-1;
	}
	printf("\nA més a més agafant un nombre enter com ara %d i guardant-lo en un double obtenim un resultat ", (int)(z));
	i=3.5+LB*3.5;
	//Una representació subnormal ha de complir les condicions especificades per aquest if o sigui que l'exponent sigui.
	//0 (el signe pot ser 0 o 1 o sigui que el primer byte pot ser 0 o 128) i que la mantissa sigui diferent de 0.
	if ((int)(((unsigned char*)&z)[i])==0 || (int)(((unsigned char*)&z)[i])==128){
		if ((((unsigned char*)&z)[i-LB]>>4)==0){
			int j, k;
			k=0;
			for (j=1; j<8; j++){
				k+=(int)(((unsigned char*)&z)[i-j*LB]);
			}
			if (k!=0){
				printf("sub");
			}
		}
	}
	printf("normal.\n");

	double x,y;
	int n, aux;
	printf("\nintrodueix un nombre.\n");
	scanf("%lf",&x);
	//imposem que el signe sigui positiu per tal de que es guardi com a 0 en els 8 bytes reservats al double x.
	if (x<0){
		y=-x;
	}
	else{
		y=x;
	}
	//Tenint en copte la endianitat de l'ordinador agafem el byte on es guarda la segona part de l'exponent l'exponent.
	//Aquest serà el que ocupi la posiciò 6 en el Little-endian i el que ocupi la posició 1 en el Big-endian.
	i=3.5+LB*2.5;
	n=(int)(((unsigned char*)&y)[i]);
	//Aquestes linees serveixen per mostrar per pantalla els 8 bytes que ocupa el double x en la memoria de l'ordinador.
	/*for (i=0; i<8; i++){
		printf("%d\t%d\n",(int)(((unsigned char*)&y)[i]), i);
	}*/

	//utilitzant l'operador >> eliminem els últims cuatre bits del byte que estem examinant i ens quedem únicament amb
	//els bits que guarden la informació del exponent.
	n=n>>4;
	//Tenint en compte la endianitat de l'ordinador agafem el byte on es guarda la primera part del exponent l'exponent.
	//Aquest serà el que ocupi la posiciò 7 en el Little-endian i el que ocupi la posició 0 en el Big-endian.
	i=3.5+LB*3.5;
	aux=((int)(((unsigned char*)&y)[i]));
	//aplicant l'operador <<4 sobre el nombre guardat en el byte que guarda la primera part del exponent obtenim
	//floor(e)*16 on e és l'exponent y sumant el nombre trobat anteriorment trobem l'exponent normalitzat.
	n+=aux<<4;
	printf("\nL'exponent normalitzat de %g és %d.\n", x, n);
	n-=1023;
	printf("\nLa part entera del logaritme en base 2 de %g és %d.\n", y, n);
	y=x;
	//Per tal de multiplicar per 2 només hem de sumar 1 al exponent en base 2 de x i això s'obté sumant 16 al byte que 
	//guarda la segona part del exponent estant atents al fet que l'exponent està guardat en dos bytes diferents.
	i=3.5+LB*2.5;
	if (((unsigned char*)&y)[i]>(255-16)){
		((unsigned char*)&y)[i]+=16-256;
		((unsigned char*)&y)[i+LB]+=1;
	}
	else{
		((unsigned char*)&y)[i]+=16;
	}
	//Per tal de canviar el signe només hem de canviar el primer bit del byte que guarda la primera part del exponent
	//sumant 128 i restant 256 en cas de que el resultat sigui mes gran o igual a 256 (cosa que es fa automàticament).
	i=3.5+LB*3.5;
	((unsigned char*)&y)[i]+=128;
	printf("\n%g multiplicat per -2 dona %g.\n", x, y);
	//Dividim ara y entre 4 per obtindre x dividit entre -2. Per tal de fer-ho només hem de restar 2 al exponent en
	//base 2 de y i això s'obté restant 32 al byte que guarda la segona part del exponent tenint en compte que 
	//l'exponent es guarda en dos bytes diferents.
	i=3.5+LB*2.5;
	if (((unsigned char*)&y)[i]<32){
		((unsigned char*)&y)[i]+=256-32;
		((unsigned char*)&y)[i+LB]-=1;
	}
	else{
		((unsigned char*)&y)[i]-=32;
	}
	printf("\nMentres que %g dividit per -2 dona %g.\n\n", x, y);
	return 0;
}