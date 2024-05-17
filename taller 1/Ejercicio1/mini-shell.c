#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"

enum {READ, WRITE};

void ejecutar_cmd(char* cmd, char** p) {
	execvp(cmd, p);
}

void hijo(char **cmd, int src[2], int dst[2]) {
	// No soy el primer proceso
	if (src != NULL) {
		close(src[WRITE]);
		dup2(src[READ], STD_INPUT);
	}
	// No soy el ultimo proceso
	if (dst != NULL) {
		close(dst[READ]);
		dup2(dst[WRITE], STD_OUTPUT);
	}
	ejecutar_cmd(cmd[0], cmd);
}

/*
[
 [comando1, arg1, arg2],
 [comando2, arg1, arg2],
 [comando3, arg1, arg2]
]
*/
static int run(char ***progs, size_t count) {
	int r, status;

	//Reservo memoria para el arreglo de pids
	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children = malloc(sizeof(*children) * count);

	//TODO: Pensar cuantos procesos necesito
	//RESP: count

	//TODO: Pensar cuantos pipes necesito.
	//RESP: count-1
	int cant_pipes = count - 1;
	int pipes[cant_pipes][2];

	for (int i = 0; i < cant_pipes; i++) {
		pipe(pipes[i]);
	}
	

	//TODO: Para cada proceso hijo:
			//1. Redireccionar los file descriptors adecuados al proceso
			//2. Ejecutar el programa correspondiente
	
	for (int i = 0; i < count; i++) {
		children[i] = fork();
		if (children[i] == 0) {
			//Se cierran el resto de pipes
			for (int j = 0; j < cant_pipes; j++) {
				if (j != i && j != i - 1) {
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
			}

			if (i != 0 && i != count - 1) {
				hijo(progs[i], pipes[i - 1], pipes[i]);
			} else if (i == 0) {
				hijo(progs[i], NULL, pipes[i]);
			} else {
				hijo(progs[i], pipes[i - 1], NULL);
			}
		}
	}

	for (int i = 0; i < cant_pipes; i++) {
		close(pipes[i][0]);
		close(pipes[i][1]);
	}

	//Espero a los hijos y verifico el estado que terminaron
	for (int i = 0; i < count; i++) {
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ",
			    (int)children[i], WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}

	
	r = 0;
	free(children);

	return r;
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n"); 
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
		return 0;
	}
	int programs_count;
	char*** programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	fflush(stdout);
	fflush(stderr);

	return 0;
}
