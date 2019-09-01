#include "apue.h"

int f1(int val);
void f2(void);
int* f3(int val);

int main(int argc, char **argv) {
	int val = 0;
	
	val = f1(val);
	printf("main f1 val=%d\n", val);
	
	if (1) {
		int a = 0;
		int b = 1;
		int c = 2;
		int d = 3;
	}
	
	f2();
	printf("main f2 val=%d\n", val);

	int *pval = NULL;
	pval = f3(val);
	printf("main() f3() *pval=%d\n", *pval);

	f2();
	printf("main() f2() *pval=%d\n", *pval);
	
	return(0);
}

int f1(int val) {
	int num = 10;
	int *ptr = &num;

	if (val == 0) {
		int val = 5;
		ptr = &val;
	}
	
	printf("f1() val=%d\n", val);
	printf("f1() *ptr=%d\n", *ptr);
	return (*ptr + 1);
}

void f2() {
	int arr[1000];
	for (int i = 0; i < 1000; i++) {
		arr[i] = i;
	}
	printf("f2() end\n");
	return;
}

int* f3(int val) {
	int *p = &val;
	printf("f3() *p=%d\n", *p);
	return p;
}
