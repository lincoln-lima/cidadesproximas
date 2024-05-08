#include "../include/kd.h"

void constroi_kd(Arv * arv, int dim) {
    arv->raiz = NULL;
    arv->dim = dim;
}

void insere_kd(Arv * arv, Municipio * mun) {
    insere_node_kd(arv, &(arv->raiz), mun, 0);
}

void insere_node_kd(Arv * arv, Node ** node, Municipio * mun, int eixo) {
    if(!(*node)) {
	*node = malloc(sizeof(Node));
	(*node)->mun = mun;
	(*node)->esq = NULL;
	(*node)->dir = NULL;
    }

    else if(compara_coord((*node)->mun, mun, eixo) > 0) insere_node_kd(arv, &((*node)->esq), mun, ++eixo % arv->dim);
    //else if(compara_coord((*node)->mun, mun, eixo) < 0) insere_node_kd(arv, &((*node)->dir), mun, ++eixo % arv->dim);
    else insere_node_kd(arv, &((*node)->dir), mun, ++eixo % arv->dim);
}

void * busca_kd(Arv * arv, Municipio * mun) {
    return busca_node_kd(arv, arv->raiz, mun, 0);
}
void * busca_node_kd(Arv * arv, Node * node, Municipio * mun, int eixo) {
    void * ret;

    if(!node) ret = NULL;
    else if(compara_coord(node->mun, mun, eixo) > 0) busca_node_kd(arv, node->esq, mun, ++eixo % arv->dim);
    else if(compara_coord(node->mun, mun, eixo) < 0) busca_node_kd(arv, node->dir, mun, ++eixo % arv->dim);
    else ret = node->mun;

    return ret;
}

//int remove_kd(Arv * arv, Municipio * mun);
//int remove_node_kd(Arv * arv, Node * node, Municipio * mun);

void libera_kd(Arv * arv) {
    libera_node_kd(arv->raiz);
}

void libera_node_kd(Node * node) {
    if(node) {
	libera_node_kd(node->esq);
	libera_node_kd(node->dir);
	free(node->mun);
	free(node);
    }
}

void exibe_kd(Arv * arv) {
    exibe_node_kd(arv, arv->raiz);
}

void exibe_node_kd(Arv * arv, Node * node) {
    if(node) {
	exibe_node_kd(arv, node->esq);
	exibe_municipio(node->mun);
	exibe_node_kd(arv, node->dir);
    }
}

int conta_kd(Arv * arv) {
    return conta_node_kd(arv->raiz);
}

int conta_node_kd(Node * node) {
    if(node) return 1 + conta_node_kd(node->esq) + conta_node_kd(node->dir);
}

int * atribui_distancias(Arv * arv, Municipio * mun, Node * node, float * distancias, int tam, int * i) {
	int codigos[tam];

    if(*i < tam) {
		if(node) {
			atribui_distancias(arv, mun, node->esq, distancias, tam, i);

			if(distancia_municipios(mun, node->mun)) {
				distancias[*i] = distancia_municipios(mun, node->mun);
				//printf("%d: %d\n", *i, node->mun->cod_ibge);
				codigos[*i] = node->mun->cod_ibge;
				(*i)++;
			}

			atribui_distancias(arv, mun, node->dir, distancias, tam, i);
		}
    }
}

int * n_proximos_kd(Arv * arv, Municipio * mun, int n) {
    int i = 0;
    int qtd_nodes = conta_kd(arv)-1;

    float * distancias = (float *) calloc(qtd_nodes, sizeof(float));
    //float * proximos = (float *) calloc(n, sizeof(float));

    int * codigos = atribui_distancias(arv, mun, arv->raiz, distancias, qtd_nodes, &i);
	int * proximos = (int *) calloc(n, sizeof(int));

    constroi_heap(distancias, qtd_nodes);
    heap_sort(distancias, qtd_nodes);

    for(i = 0; i < n; i++) proximos[i] = codigos[i];

    free(distancias);

    return proximos;
}
