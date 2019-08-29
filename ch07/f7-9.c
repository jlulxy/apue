#include "apue.h"

#define TOK_ADD 5

void do_line(char *);
void cmd_add(void);
int get_token(void);

int main(void) {
	char line[MAXLINE];

	while (fgets(line, MAXLINE, stdin) != NULL) {
		do_line(line);
	}

	exit(0);
}

// global pointer for get_token()
char *tok_ptr;
int tok_cnt= 6;

void do_line(char *ptr) {
	int cmd;

	tok_ptr = ptr;
	while ((cmd = get_token()) > 0) {
		switch (cmd) {
		case TOK_ADD:
			cmd_add();
			break;
		}
	}
}

void cmd_add(void) {
	int token;
	token = get_token();
	printf("cmd_add(): token=%d\n", token);
}

int get_token() {
	printf("get_token(): ret=%d.\n", tok_cnt);
	return tok_cnt--;
}

