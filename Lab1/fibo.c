#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

static const char *progname = "fibo";
static const int TRUE = 1;
static const int FALSE = 0;

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
	if(argc < 2){
		usage();
		return 0;
	} else {
		for(int i = 1; i < argc; i++){
			//char c = argv[i];
			if(isalpha(argv[i][0])){
				inputChar();
			} else if(isFibonacci(atoi(argv[i]))){
				printf("%s is a Fibonacci number \n", argv[i]);
			} else {
				printf("%s is not a Fibonacci number \n", argv[i]);
			}
		}
	}
	return 1;
}
