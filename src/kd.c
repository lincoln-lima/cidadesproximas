#include "../include/kd.h"

void constroi_kd(Arv * arv, int dim, double (* dist)(void *, void *), double (* cmp)(void *, void *, int eixo), void (* printa)(void *), int (* get_key)(void *)) {
    arv->raiz = NULL;
    arv->dim = dim;
    arv->dist = dist;
    arv->cmp = cmp;
    arv->printa = printa;
    arv->get_key = get_key;
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

void * busca_kd(Arv * arv, void * reg, int cod) {
    return busca_node_kd(arv, arv->raiz, reg, 0);
}
void * busca_node_kd(Arv * arv, Node * node, void * reg, int eixo, int cod) {
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

int conta_kd(Arv * arv) {
    return conta_node_kd(arv->raiz);
}

int conta_node_kd(Node * node) {
    if(node) return 1 + conta_node_kd(node->esq) + conta_node_kd(node->dir);
}

void atribui_distancias(Arv * arv, Node * node, Node * aux, float * distancias, int tam, int * i) {
    if(*i < tam) {
	if(aux) {
	    atribui_distancias(arv, node, aux->esq, distancias, tam, i);
	    //distancias[i] = arv->dist(node, aux);
	    //printf("%d\n", i);
	    distancias[*i] = 5;
	    printf("i: %d e dist: %f\n", *i, distancias[*i]);
	    //printf("i: %d e dist: %f\n", i, arv->dist(node, aux));
	    (*i)++;
	    atribui_distancias(arv, node, aux->dir, distancias, tam, i);
	}
    }
}

void n_proximos_kd(Arv * arv, Node * node, int n) {
    //int qtd_nodes = 1000;
    int qtd_nodes = conta_kd(arv);

    float * distancias = (float *) calloc(qtd_nodes, sizeof(float));
    //float distancias[qtd_nodes];

    int i = 0;
    atribui_distancias(arv, node, arv->raiz, distancias, qtd_nodes, &i);

    printf("dist: %f\n", arv->dist(node, arv->raiz));

    /*
    for(float * p = distancias; p < distancias + qtd_nodes; p++) {
		printf("%f\n", *p);		
    }
    */

    free(distancias);
}
