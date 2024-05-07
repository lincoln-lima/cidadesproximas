#include "../include/kd.h"

void constroi_kd(Arv * arv, int dim, double (* dist)(void *, void *), double (* cmp)(void *, void *, int eixo), void (* exibe)(void *)) {
    arv->raiz = NULL;
    arv->dim = dim;
    arv->dist = dist;
    arv->cmp = cmp;
    arv->exibe = exibe;
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
    //else if(arv->cmp((*node)->reg, reg, eixo) < 0) insere_node_kd(arv, &((*node)->dir), reg, ++eixo % arv->dim);
    else insere_node_kd(arv, &((*node)->dir), reg, ++eixo % arv->dim);
}

void * busca_kd(Arv * arv, void * reg) {
    return busca_node_kd(arv, arv->raiz, reg, 0);
}
void * busca_node_kd(Arv * arv, Node * node, void * reg, int eixo) {
    void * ret;

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

void exibe_kd(Arv * arv) {
    exibe_node_kd(arv, arv->raiz);
}

void exibe_node_kd(Arv * arv, Node * node) {
    if(node) {
		exibe_node_kd(arv, node->esq);
		arv->exibe(node->reg);
		exibe_node_kd(arv, node->dir);
    }
}

int conta_kd(Arv * arv) {
    return conta_node_kd(arv->raiz);
}

int conta_node_kd(Node * node) {
    if(node) return 1 + conta_node_kd(node->esq) + conta_node_kd(node->dir);
}

void atribui_distancias(Arv * arv, void * reg, Node * node, float * distancias, int tam, int * i) {
    if(*i < tam) {
	if(node) {
	    atribui_distancias(arv, reg, node->esq, distancias, tam, i);

	    if(arv->dist(reg, node->reg)) {
		arv->exibe(node->reg);
		distancias[*i] = arv->dist(reg, node->reg);
		printf("i: %d e dist: %f\n", *i, distancias[*i]);

		(*i)++;
	    }

	    atribui_distancias(arv, reg, node->dir, distancias, tam, i);
	}
    }
}

void n_proximos_kd(Arv * arv, void * reg, int n) {
    int qtd_nodes = conta_kd(arv)-1;

    float * distancias = (float *) calloc(qtd_nodes, sizeof(float));
    void * proximos[n];

    int i = 0;
    atribui_distancias(arv, reg, arv->raiz, distancias, qtd_nodes, &i);
	
    //printf("dist: %f\n", arv->dist(reg, arv->raiz->reg));

    free(distancias);
}
