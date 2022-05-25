#include <stdio.h>

int main(){
	// Prints fizzbuzz from 1 to N
	int N = 0;
	printf("Enter N: ");
	scanf("%d", &N);
	for(int i = 1; i < N+1; i++){
		printf("%d: ", i);
		if(((i%3)==0) && ((i%5)==0)){
			printf("FizzBuzz!\n");
		}
		else if((i % 3) == 0){
			printf("Fizz!\n");
		}
		else if((i % 5) == 0){
			printf("Buzz!\n");
		}
		else{
			printf("\n");
		}
	}
}
