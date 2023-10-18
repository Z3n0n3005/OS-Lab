#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

static void usage(){
	fprintf(stderr, "Usage: mpprime a_1 a_2 ...\n");
}

static void inputChar(){
	fprintf(stderr, "Only integers are allowed\n");
}

static bool isPrime(int n){
	if (n <= 1) { return false; }
	for (int i = 2; i * i <= n; i++){
		if(n%i == 0){
			return false;
		}
	}
	return true;
}

static bool isString(char c[]){
	for(int i = 0; i < strlen(c); i++){
		if(isalpha(c[i])){
			return true;
		} else {
			return false;
		}
	}
}

int main(int argc, char* argv[]){
	int status;
	if(argc < 2){
		usage();
		return 0;
	} 
	int pid = fork();
	if(pid < 0){
		perror("fork: cannot create a new process");
		exit(0);
	}
	else if (pid == 0){
		for(int i = 1; i < argc; i++){
			if(isString(argv[i]){
				inputChar();
			} else if (isPrime(atoi(argv[i])){
				printf("%d: %s is a prime number.", getpid(), argv[i]);
			} else {
				printf("%d: %s is not a prime number.", getpid(), argv[i]);
			}
		}
	} else {
		waitpid(pid, &status, 0);
		printf("%d is a parent process\n", getppid());
	}

	return 1;
}
