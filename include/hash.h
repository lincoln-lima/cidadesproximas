#ifndef __HASH__
#define __HASH__
#include <stdint.h>
typedef struct {
    uintptr_t * array;
    int size;
    int max_size;
    uintptr_t deleted;
    int (* get_key)(void *);
} thash;

uint32_t int32hash(u_int32_t a);
int insere_hash(thash * hash, void * bucket);
void * busca_hash(thash * hash, int key);
int constroi_hash(thash * hash, int n_buckets, int (* get_key)(void *));
int remover_hash(thash * hash, int key);
void apaga_hash(thash * hash);
void printa_hash(thash * hash);
#endif
