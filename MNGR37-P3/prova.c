#include <stdio.h>

typedef int(*f1)(int);

f1 g(int);
int h(f1);

int main(){
	f1 f;
	int n;
	f=g(2);
	n=h(f);
	printf("%d\n",n);
}

f1 g(int n){
	int f (int m){
		return n*m;
	}
	return f;
}

int h(f1 f){
	return f(2);
}