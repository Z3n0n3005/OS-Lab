#include <stdio.h>
#include <pthread.h>
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

struct thread_info{
	pthread_t thread_id;
	int thread_num;
	char *argv;
}

bool isPerfectSquare(int num){
	int squareRoot = sqrt(num);
	return (squareRoot * squareRoot == num);
}

bool isFibonacci(int num){
	return isPerfectSquare(5*num*num + 4) || isPerfectSquare(5*num*num - 4);
}

void* thread_f_1(void* arg){

	for(int i = 1; i < argc; i++){
		//char c = argv[i];
		if(isalpha(argv[i][0])){
			inputChar();
		} else if(isFibonacci(atoi(argv[i]))){
			printf("%d : %s is a Fibonacci number \n", i, argv[i]);
		} else {
			printf("%d : %s is not a Fibonacci number \n", i, argv[i]);
		}
	}
	pthread_exit(n);
}

int main(int argc, char* argv[]){
	int status;
	int errno;
	struct thread_info *tinfo;
	if(argc < 2){
		usage();
		return 0;
	} 

	pthread_t thread1;
	for(int tnum = 0; tnum < argc; tnum++){
		
	pthread_join(thread_1, NULL);
	return 1;
}
