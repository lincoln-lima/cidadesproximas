#ifndef __KD__
#define __KD__
#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
	void * reg;
	struct _node * esq;
	struct _node * dir;
} Node;

typedef struct {
	Node * raiz;
	int dim;
	double (* dist)(void *, void *);
	double (* cmp)(void *, void *, int);
	void (* exibe)(void *);
} Arv;

void constroi_kd(Arv * arv, int dim, double (* dist)(void *, void *), double (* cmp)(void *, void *, int), void (* exibe)(void *));
void insere_kd(Arv * arv, void * reg);
void insere_node_kd(Arv * arv, Node ** node, void * reg, int eixo);
void * busca_kd(Arv * arv, void * reg);
void * busca_node_kd(Arv * arv, Node * node, void * reg, int eixo);
//int remove_kd(Arv * arv, void * reg);
//int remove_node_kd(Arv * arv, Node * node, void * reg);
void libera_kd(Arv * arv);
void libera_node_kd(Node * node);
void exibe_kd(Arv * arv);
void exibe_node_kd(Arv * arv, Node * node);
int conta_kd(Arv * arv);
int conta_node_kd(Node * node);
void atribui_distancias(Arv * arv, void * reg, Node * node, float * distancias, int tam, int * i);
float * n_proximos_kd(Arv * arv, void * reg, int n);
#endif
