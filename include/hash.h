#ifndef __HASH__
#define __HASH__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct {
    uintptr_t * array;
    int size;
    int max_size;
    int (* get_key)(void *);
} Hash;

uint32_t int32hash(u_int32_t a);
unsigned int fiftyhash(unsigned int x);
int _calcula_pos_hash(Hash * hash, int key, int i); 
int insere_hash(Hash * hash, void * bucket);
void * busca_hash(Hash * hash, int key);
int constroi_hash(Hash * hash, int n_buckets, int (* get_key)(void *));
void libera_hash(Hash * hash);
void exibe_hash(Hash * hash);
#endif
