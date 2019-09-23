//* raap means "read args and printf"

#include <stdio.h>

int main(int argc, char *argv[]) {
	int i;
	printf("read_params_and_print:\n");
	for (i = 0; i < argc; i++) {
		printf("%d: %s\n", i, argv[i]);
	}
	return(0);
}
