#ifndef __KDMUN__
#define __KDMUN__
#include <stdio.h>
#include <stdlib.h>
#include "mun.h"
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
void _insere_node_kd(Arv * arv, Node ** node, Municipio * mun, int eixo);
void * busca_kd(Arv * arv, Municipio * mun);
void * _busca_node_kd(Arv * arv, Node * node, Municipio * mun, int eixo);
void libera_kd(Arv * arv);
void _libera_node_kd(Node * node);
void exibe_kd(Arv * arv);
void _exibe_node_kd(Arv * arv, Node * node);
int conta_kd(Arv * arv);
int _conta_node_kd(Node * node);
void _insertion_sort_mun_kd(int * codigos, float * distancias, int tam);
void _calcula_dist_cod(Municipio * mun, Node * node, float * distancias, int * codigos, int tam, int * i);
int * n_proximos_kd(Arv * arv, Municipio * mun, int n);
#endif
