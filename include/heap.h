#ifndef __HEAP__
#define __HEAP__
#include <stdio.h>
#include <stdlib.h>
int pai(int n);
int f_esq(int n);
int f_dir(int n);
void troca(float *a, float *b);
void desce(float v[], int pos, int max_size);
void sobe(float v[], int pos);
float acessa_max(float v[]);
void constroi_heap(float v[], int max_size);
float extrai_max(float v[], int *size);
int insere_elemento(float v[], float new_element, int max_size, int *size);
void altera_prioridade(float v[], int pos, int max_size, float value);
void heap_sort(float v[], int max_size);
#endif
