#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MEMORY_NUMBER_OF_WORDS 1024 // definido no exercicio
#define CACHE_NUMBER_OF_BLOCKS 64 // 64 blocos que levam 4 palavras
#define WORDS 4 // 4 palavras
#define WORD_SIZE 32 // 32 bits

int decToBinary(int n) 
{ 
	// binary
	int k;

    // array to store binary number 
    int binaryNum[32]; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    }

    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) {
		k = 10 * k + binaryNum[j];
	}
	// printf("%d\n", k);

	return k;
}

// int tagCalculate(N) {

// 	if (N > 111112){
// 		return 0;
// 	}
// 	else {
// 		return 1;
// 	}
// 	return 0;
	
// }

int main(void) {
    
	// memory
	char memory_data[MEMORY_NUMBER_OF_WORDS][WORD_SIZE];
	
	// cache
	char cache_data[CACHE_NUMBER_OF_BLOCKS][WORDS][WORD_SIZE];
	int cache_tag[CACHE_NUMBER_OF_BLOCKS];
	int cache_validity[CACHE_NUMBER_OF_BLOCKS];
	int cache_dirty[CACHE_NUMBER_OF_BLOCKS];

	for (int i = 0; i < CACHE_NUMBER_OF_BLOCKS; i++) {
		cache_tag[i] = 0;
		cache_validity[i] = 0;
		cache_dirty[i] = 0;
		// printf("%d-%d\n", cache_validity[i], cache_dirty[i]);
	}

	int N; // endereco da memoria (0 < N < 4096)
	int operation; // 0: leitura, 1: escrita
	char data[WORD_SIZE]; // dado para escrita

	int N_binary;
	int tag;
	int offset;
	int block_adress;
	int block_number;
	int index_binary;

	float reads; // quantidade de operations == 0
	float writes; // quantidade de operations == 1
	int hits = 1; // acesso ao cache com sucesso
	int misses = 0; // acesso ao cache sem sucesso
	float hit_rate = 1.0; // = reads / hits
	float miss_rate = 1.0; // =  reads / misses

	while(scanf("%d%d", &N, &operation) != EOF) { // entrada endereco de acesso e operacao
			
		if (operation == 1) { // escrever na memoria
			writes++; // aumenta quantidade de escritas
			
			// lendo dado e onde vou escrever na cache
			scanf("%s", data); // entrada data

			// tag = tagCalculate(N)
			offset = N % 2; // encontrar offset
			block_adress = floor(N/16);
			block_number = block_adress % CACHE_NUMBER_OF_BLOCKS; // encontrar bloco da cache
			// printf("%d\n", block_number);
			index_binary = decToBinary(block_number);

			if (cache_validity[block_number] == 1) {
				// temos algm com essa index
				// verifica tag
				if (cache_tag[block_number] != tag)	{
					// se for diferente escrever na memoria esse dado
					strcpy(memory_data[0], cache_data[block_number][offset]);
					// atualiza cache com novo dado
					strcpy(cache_data[block_number][offset], data);
				}
				
			}
			else {
				// nao temos alguem nesse local
				// escrever na cache todos do bloco
				strcpy(cache_data[block_number][offset], data);
				// sujar a cache
				cache_dirty[block_number] = 1;
				// marcar valido como 1
				cache_validity[block_number] = 1;

			}			
			
		} else if (operation == 0) { // ler da memoria
			reads++; // aumenta quantidade de leituras

			// tag = tagCalculate(N)
			offset = N % 2; // encontrar offset
			block_adress = floor(N/16);
			block_number = block_adress % CACHE_NUMBER_OF_BLOCKS; // encontrar bloco da cache
			
			if (cache_validity[block_number] == 1) {
				// temos algm com essa index
				
				// verifica tag
				if (cache_tag[CACHE_NUMBER_OF_BLOCKS] == tag) {
					// se for o mesmo hit++
					hits++;
				} else {
					// se for diferente miss++
					misses++;
					// le da memoria
					
				}
			}
			else {
				misses++;
			}
					
		} else {
			printf("Operacao errada");
		
		}

	};

	printf("READS: %f\n", reads);
	printf("WRITES: %f\n", writes);  
	printf("HITS: %d\n", hits);  
	printf("MISSES: %d\n", misses);  
	printf("HIT RATE: %.2f\n", reads / hits);  
	printf("MISS RATE: %.2f\n", reads / misses);

}