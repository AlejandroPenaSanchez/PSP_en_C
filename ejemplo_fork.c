#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	pid_t pid_hijo;

	fprintf(stdout, "Antes del Fork\n");
	fprintf(stdout, "\tPid proceso actual: %d\n", getpid());
	fprintf(stdout, "\tPid proceso padre: %d\n", getppid());

	pid = fork();

	if(pid == -1){
		fprintf(stderr, "Error en el fork \n");
		exit(-1);
	}
	if (pid == 0){ //nos encontramos en el proceso hijo
		fprintf(stdout, "En el hijo. PID: %d\n", getpid());
		fprintf(stdout, "En el hijo. PPID: %d\n", getppid());
		sleep(5);
	} else{ //Este se ejecutara en el proceso padre
		fprintf(stdout, "En el padre. PID: %d\n", getpid());
		fprintf(stdout, "En el padre. PPID: %d\n", getppid());
		pid_hijo = wait(NULL);
		fprintf(stdout, "En el padre. mi hijo con pid %d,ha finalizado\n", pid_hijo);
	}

	return 0;
}