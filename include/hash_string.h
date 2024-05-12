#ifndef __HASHSTRING__
#define __HASHSTRING__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
typedef struct {
    uintptr_t * array;
    int size;
    int max_size;
    char * (* get_key)(void *);
} HashString;

unsigned long loselosehash(unsigned char * str);
unsigned long djb2hash(unsigned char * str);
int _calcula_pos_hash_string(HashString * hash, char * key, int i); 
int insere_hash_string(HashString * hash, void * bucket);
void ** busca_hash_string(HashString * hash, char * key);
int constroi_hash_string(HashString * hash, int n_buckets, char * (* get_key)(void *));
void libera_hash_string(HashString * hash);
void exibe_hash_string(HashString * hash);
#endif
