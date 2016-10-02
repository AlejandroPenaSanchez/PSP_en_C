#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid_abuelo;
	pid_t pid_padre;
	pid_t pid_nieto;

	pid_abuelo = fork();

	if(pid_abuelo == -1){
		fprintf(stderr, "Error en el fork \n");
		exit(-1);
	}
	
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);

	if (pid_abuelo == 0){
		pid_padre = fork();
		
		if(pid_padre == -1){
			fprintf(stderr, "Error en el fork hijo \n");
			exit(-1);
		}
		if(pid_padre == 0){
			fprintf(stdout, "\t#%d: mi padre tiene el pid %d\n",getpid() ,getppid());
			fprintf(stdout, "-NIETO-La Suma: %d\n", (num1+num2));
			sleep(3);
		}else{
			pid_nieto = wait(NULL);
			fprintf(stdout, "\t#%d: mi hijo con pid %d,ha finalizado\n",getpid() ,pid_nieto);
			fprintf(stdout, "-PADRE-La Resta: %d\n", (num1-num2));
			sleep(3);
		}

	} else{
		pid_padre = wait(NULL);
		fprintf(stdout, "\t#%d: mi hijo con pid %d,ha finalizado\n",getpid() ,pid_padre);
		fprintf(stdout, "-ABUELO-La Multiplicacion: %d\n", (num1*num2));
	}

	return 0;
}