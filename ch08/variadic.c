#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void print_ints(int num, ...) {
	va_list args;
	
	va_start(args, num);

	for (int i = 0; i < num; i++) {
		int value = va_arg(args, int);
		printf("%d: %d\n", i, value);
	}

	va_end(args);
}

void my_printf(const char *format, ...) {
	va_list args;
	int done = 0;
	
	char *substring = strstr(format, "Xfmeng");
	if (substring != format) {
		printf("done=%d\n", -1);
		return;
	}

	va_start(args, format);
	done = vfprintf(stdout, format, args);
	va_end(args);

	printf("done=%d\n", done);
}

int main(int argc, char *argv[]) {
	print_ints(7, 0, 1, 2, 3, 4, 5);
	my_printf("Something we don't want to print.\n");
	my_printf("Xfmeng says, so cool 1.\n");
	my_printf("Xfmeng says, so cool 2.\n");
}

