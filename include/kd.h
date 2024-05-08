#ifndef __KD__
#define __KD__
#include <stdio.h>
#include <stdlib.h>
#include "mun.h"
#include "heap.h"
typedef struct _node {
	Municipio * mun;
	struct _node * esq;
	struct _node * dir;
} Node;

typedef struct {
	Node * raiz;
	int dim;
} Arv;

void constroi_kd(Arv * arv, int dim);
void insere_kd(Arv * arv, Municipio * mun);
void insere_node_kd(Arv * arv, Node ** node, Municipio * mun, int eixo);
void * busca_kd(Arv * arv, Municipio * mun);
void * busca_node_kd(Arv * arv, Node * node, Municipio * mun, int eixo);
void libera_kd(Arv * arv);
void libera_node_kd(Node * node);
void exibe_kd(Arv * arv);
void exibe_node_kd(Arv * arv, Node * node);
int conta_kd(Arv * arv);
int conta_node_kd(Node * node);
int * atribui_distancias(Arv * arv, Municipio * mun, Node * node, float * distancias, int tam, int * i);
int * n_proximos_kd(Arv * arv, Municipio * mun, int n);
#endif
