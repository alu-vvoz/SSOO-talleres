#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include "constants.h"

enum {READ, WRITE};

int generate_random_number(){
	return (rand() % 50);
}

void hijo(int src[2], int dst[2]) { 
	close(src[WRITE]);
	close(dst[READ]);
	int numero;
	while (1) {
		read(src[READ], &numero, sizeof(numero));
		numero++;
		write(dst[WRITE], &numero, sizeof(numero));
	}
}

void hijo_especial(int src[2], int dst[2], int parent[2]) {
	close(src[WRITE]);
	close(dst[READ]);
	int numero = 0;
	int numero_secreto = generate_random_number();
	read(parent[READ], &numero, sizeof(numero));
	while( numero < numero_secreto) {
		numero++;
		write(dst[WRITE], &numero, sizeof(numero));
		read(src[READ], &numero, sizeof(numero));
	}
	write(parent[WRITE], &numero, sizeof(numero));
	exit(0);
}

int main(int argc, char **argv)
{	
	//Funcion para cargar nueva semilla para el numero aleatorio
	
	srand(time(NULL));

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
	int children[n];
	// pipes[0] está reservado para el pipe entre el padre y el start
	int pipes[n + 1][2];
	
	for (int i=0; i < n + 1; i++) {
		pipe(pipes[i]);
	}
	
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);
    
	for (int i = 0; i < n; i++) {
		children[i] = fork();
		if (children[i] == 0) {
			//Se cierran el resto de pipes
			for (int j = 0; j < n + 1; j++) {
				if(i==0){
					if( j != 1 && j != n ){
						if(i == start-1 && j==0){
							continue;
						}
						close(pipes[j][0]);
						close(pipes[j][1]);
					}
				}else{
					if( j != i && j != i + 1 ){
						if(i == start-1 && j==0){
							continue;
						}
						close(pipes[j][0]);
						close(pipes[j][1]);
					}
				}
			}


			if (i != 0) {
				if (start - 1 == i ) {
					hijo_especial(pipes[i], pipes[i + 1], pipes[0]);
				} else {
					hijo(pipes[i], pipes[i+1]);
				}
			} else {
				if (start - 1  == i) {
					hijo_especial(pipes[n], pipes[1], pipes[0]);
				} else {
					hijo(pipes[n], pipes[1]);
				}
			}
		}
	}

	write(pipes[0][WRITE], &buffer, sizeof(buffer));
	int numero_final;
	waitpid(children[start - 1 ], &status,0);
	read(pipes[0][READ], &numero_final, sizeof(numero_final));

	printf("EL NUMERO FINAL ES %d\n", numero_final);
    
}