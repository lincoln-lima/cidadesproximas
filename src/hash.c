#include <stdlib.h>
#include "../include/hash.h"

//funcao especifica de has
u_int32_t int32hash(u_int32_t a)
{
	/*
	 * Robert Jenkins' 32 bit integer hash function
	 * Source: https://github.com/JeffBezanson/libsupport/blob/master/hashing.c
	*/
	a = (a+0x7ed55d16) + (a<<12);
	a = (a^0xc761c23c) ^ (a>>19);
	a = (a+0x165667b1) + (a<<5);
	a = (a+0xd3a2646c) ^ (a<<9);
	a = (a+0xfd7046c5) + (a<<3);
	a = (a^0xb55a4f09) ^ (a>>16);
	return a;
}

int insere(thash * hash, void * bucket) {
    int pos = int32hash(hash->get_key(bucket)) % hash->max_size;
    int ret;

    //checagem se o array da tabela está cheio
    if(hash->size == hash->max_size) {
	free(bucket);
	ret = EXIT_FAILURE;
    }
    else {
	//garante que a posição para alocação da estrutura esteja desocupada
        while(hash->array[pos] != 0 && hash->array[pos] != hash->deleted)
	    pos = (pos+1) % hash->max_size;
	    // sondagem linear dos elementos
        
	//armazena ponteiro para o bucket específico
        hash->array[pos] = (uintptr_t) bucket;
        hash->size++;
	//acréscimo ao tamanho ocupado pelo vetor;

	ret = EXIT_SUCCESS;
    }

    return ret;
}

void * busca(thash * hash, int key) {
    int pos = int32hash(key) % hash->max_size;

    //criação do objeto para retorno
    void * ret = NULL; 

    while(hash->array[pos] != 0 && ret == NULL) {
	if(hash->get_key((void *) hash->array[pos]) == key) 
	    ret = (void *) hash->array[pos];
	else
	    pos = (pos+1) % hash->max_size;
    }

    return ret;
}

int constroi(thash * hash, int n_buckets, int (* get_key)(void *)) {
    int ret;
    //aloca espaco para array da tabela
    hash->array = calloc(sizeof(void *), n_buckets + 1);

    //em caso de falha na alocação
    if(hash->array == NULL)
        ret = EXIT_FAILURE;
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
int remover(thash * hash, int key) {
    int ret = EXIT_FAILURE;
    int pos = int32hash(key) % hash->max_size;

    //caso determinada posição esteja nula, o elemento não deve existir
    while(hash->array[pos] != 0) {
	//compara a chave do registro com a chave informada na chamada da função
        if(hash->get_key((void *) hash->array[pos]) == key) {
	    //diminui tamanho ocupado, libera a posição e diz que a mesma foi deletada
	    hash->size--;
	    free((void *) hash->array[pos]);
	    hash->array[pos] = hash->deleted;
	    ret = EXIT_SUCCESS;
	}
        else
            pos = (pos+1) % hash->max_size;
    }

    return ret;
}

//elimina todos os registros da tabela
void apaga(thash * hash) {
   //libera posição a posição do array
    for(int pos = 0; pos < hash->max_size; pos++) {
	if(hash->array[pos] != 0 && hash->array[pos] != hash->deleted) free((void *) hash->array[pos]);
    }

   //libera o array
   free(hash->array);
}
