#include "../include/hash_string.h"

unsigned long loselosehash(unsigned char *str) {
	/*
	 * lose lose
	 * Source: http://www.cse.yorku.ca/~oz/hash.html
	*/
	unsigned int hash = 0;
	int c;

	while (c = *str++)
	    hash += c;

	return hash;
}

unsigned long djb2hash(unsigned char *str) {
	/*
	 * djb2
	 * Source: http://www.cse.yorku.ca/~oz/hash.html
	*/
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

int calcula_pos(HashString * hash, char * key, int i) {
    // hash duplo dos elementos
    return (djb2hash(key) + i * loselosehash(key)) % hash->max_size;
}

int insere_hash_string(HashString * hash, void * bucket) {
    int ret;

    //checagem se o array da tabela está cheio
    if(hash->size == hash->max_size) {
		free(bucket);
		ret = EXIT_FAILURE;
    }
    else {
		int pos;
		char * key = hash->get_key(bucket);
		int i = 0;
		
		do {
			pos = calcula_pos(hash, key, i);
			i++; 
		} while(hash->array[pos] != 0 && hash->array[pos] != hash->deleted);
		//garante que a posição para alocação da estrutura esteja desocupada

		//armazena ponteiro para o bucket específico
		hash->array[pos] = (uintptr_t) bucket;
		hash->size++;
		//acréscimo ao tamanho ocupado pelo vetor;

		ret = EXIT_SUCCESS;
    }

    return ret;
}

void ** busca_hash_string(HashString * hash, char * key) {
    //criação do objeto para retorno
    void ** buckets = (void **) malloc(sizeof(void *) * 8); 

    int i = 0, n = 0;

    for(int pos = calcula_pos(hash, key, i); hash->array[pos] != 0; pos = calcula_pos(hash, key, ++i)) {
		if(strcmp(hash->get_key((void *) hash->array[pos]), key) == 0) buckets[n++] = (void *) hash->array[pos];
    }

    return buckets;
}

int constroi_hash_string(HashString * hash, int n_buckets, char * (* get_key)(void *)) {
    int ret;
    //aloca espaco para array da tabela
    hash->array = calloc(sizeof(void *), n_buckets + 1);

    //em caso de falha na alocação
    if(hash->array == NULL) ret = EXIT_FAILURE;
    else {
		//inicialização dos parâmetros necessários
		hash->size = 0;
		hash->max_size = n_buckets + 1;
		hash->deleted = (uintptr_t) &(hash->size);
		hash->get_key = get_key;

		ret = EXIT_SUCCESS;
    }

    return ret;
}

//remove elemento específico
int remover_hash_string(HashString * hash, char * key) {
    int ret = EXIT_FAILURE;

    int i = 0;
    int pos = calcula_pos(hash, key, i); 

    //caso determinada posição esteja nula, o elemento não deve existir
    for(i; hash->array[pos] != 0; i++) {
	//compara a chave do registro com a chave informada na chamada da função
        if(hash->get_key((void *) hash->array[pos]) == key) {
			//diminui tamanho ocupado, libera a posição e diz que a mesma foi deletada
			hash->size--;
			free((void *) hash->array[pos]);
			hash->array[pos] = hash->deleted;
			ret = EXIT_SUCCESS;
		}
        else pos = calcula_pos(hash, key, i); 
    }

    return ret;
}

//elimina todos os registros da tabela
void libera_hash_string(HashString * hash) {
    //libera posição a posição do array
    for(int pos = 0; pos < hash->max_size; pos++) {
		if(hash->array[pos] != 0 && hash->array[pos] != hash->deleted) free((void *) hash->array[pos]);
    }

    //libera o array
    free(hash->array);
}

void exibe_hash_string(HashString * hash) {
    for(int pos = 0; pos < hash->max_size; pos++) {
        printf("%d: ", pos);
		if(hash->array[pos] != 0) printf("%s\n\n", hash->get_key((void *) hash->array[pos]));
		else printf("%ld\n\n", hash->array[pos]);
    }
}
