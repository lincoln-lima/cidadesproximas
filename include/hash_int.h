#ifndef __HASHINT__
#define __HASHINT__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct {
    uintptr_t * array;
    int size;
    int max_size;
    uintptr_t deleted;
    int (* get_key)(void *);
} HashInt;

uint32_t int32hash(u_int32_t a);
unsigned int fiftyhash(unsigned int x);
int _calcula_pos_hash_int(int key, int i, HashInt * hash); 
int insere_hash_int(HashInt * hash, void * bucket);
void * busca_hash_int(HashInt * hash, int key);
int constroi_hash_int(HashInt * hash, int n_buckets, int (* get_key)(void *));
int remover_hash_int(HashInt * hash, int key);
void libera_hash_int(HashInt * hash);
void exibe_hash_int(HashInt * hash);
#endif
