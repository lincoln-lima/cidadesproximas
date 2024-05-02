#include "../include/kd.h"

void constroi_kd(Arv * arv, int dim, double (* dist)(void *, void *), double (* cmp)(void *, void *, int eixo), void (* printa)(void *)) {
	arv->raiz = NULL;
	arv->dim = dim;
	arv->dist = dist;
	arv->cmp = cmp;
	arv->printa = printa;
}

void insere_kd(Arv * arv, void * reg) {
	insere_node_kd(arv, &(arv->raiz), reg, 0);
}

void insere_node_kd(Arv * arv, Node ** node, void * reg, int eixo) {
	if(!(*node)) {
		*node = malloc(sizeof(Node));
		(*node)->reg = reg;
		(*node)->esq = NULL;
		(*node)->dir = NULL;
	}

	else if(arv->cmp((*node)->reg, reg, eixo) > 0) insere_node_kd(arv, &((*node)->esq), reg, ++eixo % arv->dim);
	else if(arv->cmp((*node)->reg, reg, eixo) < 0) insere_node_kd(arv, &((*node)->dir), reg, ++eixo % arv->dim);
}

void * busca_kd(Arv * arv, void * reg) {
	return busca_node_kd(arv, arv->raiz, reg, 0);
}
void * busca_node_kd(Arv * arv, Node * node, void * reg, int eixo) {
	Node * ret;

	if(!node) ret = NULL;
	else if(arv->cmp(node->reg, reg, eixo) > 0) busca_node_kd(arv, node->esq, reg, ++eixo % arv->dim);
	else if(arv->cmp(node->reg, reg, eixo) < 0) busca_node_kd(arv, node->dir, reg, ++eixo % arv->dim);
	else ret = node->reg;

	return ret;
}
//int remove_kd(Arv * arv, void * reg);
//int remove_node_kd(Arv * arv, Node * node, void * reg);

void libera_kd(Arv * arv) {
	libera_node_kd(arv->raiz);
}

void libera_node_kd(Node * node) {
	if(node) {
		libera_node_kd(node->esq);
		libera_node_kd(node->dir);
		free(node->reg);
		free(node);
	}
}

void printa_kd(Arv * arv) {
	printa_node_kd(arv, arv->raiz);
}

void printa_node_kd(Arv * arv, Node * node) {
	if(node) {
		printa_node_kd(arv, node->esq);
		arv->printa(node->reg);
		printa_node_kd(arv, node->dir);
	}
}
