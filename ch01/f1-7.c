#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);

int main(void) {
    char buf[MAXLINE];
    pid_t pid;
    int status;
    if (signal(SIGINT, sig_int) == SIG_ERR)
      err_sys("signal error");
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
        }
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
			/*
			 * If execlp() succeed, the current process will
			 * NOT do the follow code, that is, in this program,
			 * "prinf pid2" and so on.
			 * 
			 * But if ececlp() faild, it will set errno and do
			 * the next code to "printf pid2" ans so on.
			 *
			 * So great exercise, 2019-06-30.
			 */
            execlp(buf, buf, (char *)0);
            err_ret("couldn't, execute: %s", buf);
			/* exit(127) or not matters! */
			//exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error with pid=%d, status=%d\n", pid, status);
        } else {
		}

        printf("%% ");
    }
    exit(0);
}

void sig_int(int signo)
{
  printf("interrupt\n%% ");
  exit(1);
}

