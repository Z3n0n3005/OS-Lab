#include <stdio.h>
#include <vector>
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
};

bool isPerfectSquare(int num){
	int squareRoot = sqrt(num);
	return (squareRoot * squareRoot == num);
}

bool isFibonacci(int num){
	return isPerfectSquare(5*num*num + 4) || isPerfectSquare(5*num*num - 4);
}

void* checkFibonnaciThread(void* arg){
    int number = *((int*)arg);
		//char c = argv[i];
    if(isalpha(number)){
        inputChar();
    } else if(isFibonacci(number)){
        printf("%d is a Fibonacci number \n", number);
    } else {
        printf("%d is not a Fibonacci number \n", number);
    }
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	int status;
	int errno;
	struct thread_info *tinfo;
	if(argc < 2){
		usage();
		return 0;
	} 

    std::vector<int> numbers;

    for(int i = 1; i < argc; i++){
        int number = atoi(argv[i]);
        numbers.push_back(number);
    }

	pthread_t threads[numbers.size()];
	for(int tnum = 0; tnum < numbers.size(); tnum++){
       int* arg = new int(numbers[tnum]);
       int status = pthread_create(&threads[tnum], NULL, checkFibonnaciThread, (void*)arg);
        if(status){
            printf("Error creating thread %d", tnum);
            return 1;
        }
    }	

    for(int tnum = 0; tnum < numbers.size(); tnum++){
        pthread_join(threads[tnum], NULL);
    }
	return 1;
}
