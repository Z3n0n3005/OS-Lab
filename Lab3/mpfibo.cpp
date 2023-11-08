#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

static void usage(){
	fprintf(stderr, "Usage: fibo a_1 a_2 ...\n");
}

static void inputChar(){
	fprintf(stderr, "Only integers are allowed\n");
}

bool isPerfectSquare(int num){
	int squareRoot = sqrt(num);
	return (squareRoot * squareRoot == num);
}

bool isFibonacci(int num){
	return isPerfectSquare(5*num*num + 4) || isPerfectSquare(5*num*num - 4);
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

			//char c = argv[i];
			if(isalpha(argv[i][0])){
				inputChar();
			} else if(isFibonacci(atoi(argv[i]))){
				printf("%d : %s is a Fibonacci number \n", getpid(), argv[i]);
			} else {
				printf("%d : %s is not a Fibonacci number \n", getpid(), argv[i]);
			}


		}
	} else {
		waitpid(pid, &status, 0);
		printf("%d is a parent process\n", getppid());
	}

	return 1;
}
