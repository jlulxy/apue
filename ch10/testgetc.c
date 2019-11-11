#include <stdio.h>

int main(int argc, char **argv) {
	FILE *fp = NULL;
	char c = 'a';
	long pos = 0;
	
	if (argc >= 2) {
		c = argv[1][0];
	}
	printf("char = %c\n", c);
	if ((fp = fopen("testgetc.txt", "rw+")) == NULL) {
		printf("fopen error\n");
	}
	if ((pos = ftell(fp)) == -1) {
		printf("ftell error");	
	}
	printf("after fopen(), file current position= %ld\n", pos);
	// setbuf(fp ,NULL);
	if (putc(c + 1, fp) == EOF) {
		printf("putc error\n");
	}
	if ((pos = ftell(fp)) == -1) {
		printf("ftell error");	
	}
	printf("after putc(), file current position = %ld\n", pos);

	rewind(fp);
	fflush(fp);
	fclose(fp);
	
	// if ((fp = fopen("testgetc.txt", "r+")) == NULL) {
	// if ((fp = fopen("testgetc.txt", "rw+")) == NULL) {
	
	// if ((fp = fopen("testgetc.txt", "wr+")) == NULL) {
	if ((fp = fopen("testgetc.txt", "rw+")) == NULL) {
		printf("fopen error\n");
	}
	if ((pos = ftell(fp)) == -1) {
		printf("ftell error");	
	}
	printf("after re-fopen(), file current position= %ld\n", pos);
	
	if ((c = getc(fp)) == EOF) {
		printf("getc error\n");
	}

	if ((pos = ftell(fp)) == -1) {
		printf("ftell error");	
	}
	printf("after getc(), file current position= %ld\n", pos);
	printf("getc() return as int=%d\n", c);
	return 0;
}
