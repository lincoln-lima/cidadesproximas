#ifndef __HASH__
#define __HASH__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct {
    uintptr_t * array;
    int size;
    int max_size;
    uintptr_t deleted;
    int (* get_key)(void *);
} thash;

uint32_t int32hash(u_int32_t a);
unsigned int fiftyhash(unsigned int x);
int calcula_pos(int key, int i, thash * hash); 
int insere_hash(thash * hash, void * bucket);
void * busca_hash(thash * hash, int key);
int constroi_hash(thash * hash, int n_buckets, int (* get_key)(void *));
int remover_hash(thash * hash, int key);
void libera_hash(thash * hash);
void exibe_hash(thash * hash);
#endif
