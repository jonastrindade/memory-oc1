#include <stdio.h>

#define MEMORY_NUMBER_OF_WORDS 1024 // definido no exercicio
#define CACHE_NUMBER_OF_WORDS 256 // 64 blocos que levam 4 palavras
#define WORD_SIZE 32 // 32 BITS

int main(void) {
    
	char memory[MEMORY_NUMBER_OF_WORDS][WORD_SIZE];
	char cache[CACHE_NUMBER_OF_WORDS][WORD_SIZE];

	// cache com mapeamento direto
	// write back para operações de escrita
	// enrecos da cpu contem 32 bits

	int N; // endereco da memoria (0 < N < 4096)
	int operation; // 0: leitura, 1: escrita
	char data[WORD_SIZE]; // dado para escrita

	int reads; // quantidade de operations == 0
	int writes; // quantidade de operations == 1
	int hits = 0; // acesso ao cache com sucesso
	int misses = 0; // acesso ao cache sem sucesso
	float hit_rate; // = reads / hits
	float miss_rate; // =  reads / misses

	while(scanf("%d%d", &N, &operation) != EOF) { // entrada endereco de acesso e operacao
			
		if (operation == 1) { // escrever na memoria
			scanf("%s", data); // entrada data
			printf("N: %d, operation: %d, data: %s\n", N, operation, data);
			writes++;
		
		} else if (operation == 0) { // ler da memoria
			printf("N: %d, operation: %d\n", N, operation);
			reads++;
		
		} else {
			printf("Operacao errada");
		
		}

	};   

}