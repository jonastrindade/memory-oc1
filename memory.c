#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MEMORY_SIZE 4096 // definido no exercicio
#define CACHE_NUMBER_OF_BLOCKS 64 // 64 blocos que levam 4 palavras
#define WORDS 4 // 4 palavras
#define WORD_SIZE 32 // 32 bits

unsigned long int decToBinary(int n) 
{ 
	// binary
	unsigned long int k = 0;

    // array to store binary number 
    unsigned long int  binaryNum[32]; 
  
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

	// printf("kzin: %lu\n", k);
	return k;
}

unsigned long int tagCalculate(unsigned long int binary) {
	
	unsigned long int rest;
	unsigned long int tag_with_zeros;
	unsigned long int tag_without_zeros;

	if (binary < 111112){
		return 0;
	}
	else {
		// printf("binary: %lu\n", binary);
		
		rest = binary % 1000000;
		// printf("rest: %lu\n", rest);
		
		tag_with_zeros = binary - rest;
		// printf("tag_with_zeros: %lu\n", tag_with_zeros);
		
		tag_without_zeros = tag_with_zeros / 1000000;
		// printf("tag_without_zeros: %lu\n", tag_without_zeros);
		
		return tag_without_zeros;
	}

	return 1;

}

int main(void) {
    
	// memory
	char memory_data[MEMORY_SIZE][WORD_SIZE];
	
	// cache
	char cache_data[CACHE_NUMBER_OF_BLOCKS][WORDS][WORD_SIZE];
	int cache_tag[CACHE_NUMBER_OF_BLOCKS];
	int cache_index[CACHE_NUMBER_OF_BLOCKS];
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

	unsigned long int N_binary;
	unsigned long int tag;
	int offset;
	int block_adress;
	int block_number;
	int index_binary;

	float reads; // quantidade de operations == 0
	float writes; // quantidade de operations == 1
	int hits = 0; // acesso ao cache com sucesso
	int misses = 0; // acesso ao cache sem sucesso
	float hit_rate = 0.0; // = reads / hits
	float miss_rate = 0.0; // =  reads / misses

	while(scanf("%d%d", &N, &operation) != EOF) { // entrada endereco de acesso e operacao
		
		// printf("%d\n", N);

		N_binary = decToBinary(N);
		// printf("N_binary: %lu\n", N_binary);

		tag = tagCalculate(N_binary);
		// printf("tag: %lu\n", tag);

		offset = N % 4; // encontrar offset
		// printf("offset: %d\n", offset);

		block_adress = floor(N/16);
		// printf("block_adress: %d\n", block_adress);

		block_number = block_adress % CACHE_NUMBER_OF_BLOCKS; // encontrar bloco da cache
		// printf("block_number: %d\n", block_number);

		if (operation == 1) { // escrever na memoria
			writes++; // aumenta quantidade de escritas

			// lendo dado e onde vou escrever na cache
			scanf("%s", data); // entrada data
			
			if (cache_validity[block_number] == 1) {
				// temos algm com essa index
				// verifica tag
				if (cache_tag[block_number] != tag)	{

					if (cache_dirty[block_number] == 1) {
						// se for diferente escrever na memoria esse dado
						strcpy(memory_data[N], cache_data[block_number][offset]);
						// atualiza cache com novo dado
						strcpy(cache_data[block_number][offset], data);

						printf("%d %d %s W\n", N, operation, data);

					} else {
						// atualiza cache com novo dado
						strcpy(cache_data[block_number][offset], data);

						printf("%d %d %s W\n", N, operation, data);

					}
				}
				else {
					if (cache_dirty[block_number] == 1) {
						// se for diferente escrever na memoria esse dado
						strcpy(memory_data[N], cache_data[block_number][offset]);
						// atualiza cache com novo dado
						strcpy(cache_data[block_number][offset], data);

						printf("%d %d %s W\n", N, operation, data);

					} else {
						// atualiza cache com novo dado
						strcpy(cache_data[block_number][offset], data);

						printf("%d %d %s W\n", N, operation, data);

					}
				}
				
			}
			else {
				// nao temos alguem nesse local
				// escrever na cache todos do bloco
				strcpy(cache_data[block_number][offset], data);
				// marcar tag
				cache_tag[block_number] = tag;
				// sujar a cache
				cache_dirty[block_number] = 1;
				// marcar valido como 1
				cache_validity[block_number] = 1;

				printf("%d %d %s W\n", N, operation, data);
			}			
			
		} else if (operation == 0) { // ler da memoria
			reads++; // aumenta quantidade de leituras
			
			if (cache_validity[block_number] == 1) {
				// temos algm com essa index
				
				// verifica tag
				if (cache_tag[block_number] == tag) {
					// se for o mesmo hit++
					hits++;

					printf("%d %d H\n", N, operation);
				} else {
					// se for diferente miss++
					misses++;
					// le da memoria

					printf("%d %d M\n", N, operation);				
				}
			}
			else {
				printf("%d %d M\n", N, operation);
				misses++;
			}
					
		} else {
			printf("Operacao errada\n\n");
		
		}

	};

	printf("\nREADS: %f\n", reads);
	printf("WRITES: %f\n", writes);  
	printf("HITS: %d\n", hits);  
	printf("MISSES: %d\n", misses);  
	printf("HIT RATE: %.2f\n", hits / reads);  
	printf("MISS RATE: %.2f\n", misses / reads);

}