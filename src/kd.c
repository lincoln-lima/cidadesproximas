#include "../include/kd.h"

void constroi_kd(Arv * arv, int dim) {
    arv->raiz = NULL;
    arv->dim = dim;
}

void insere_kd(Arv * arv, Municipio * mun) {
    _insere_node_kd(arv, &(arv->raiz), mun, 0);
}

void _insere_node_kd(Arv * arv, Node ** node, Municipio * mun, int eixo) {
    if(!(*node)) {
		*node = malloc(sizeof(Node));
		(*node)->mun = mun;
		(*node)->esq = NULL;
		(*node)->dir = NULL;
    }

    else if(compara_coord((*node)->mun, mun, eixo) > 0) _insere_node_kd(arv, &((*node)->esq), mun, ++eixo % arv->dim);
    //else if(compara_coord((*node)->mun, mun, eixo) < 0) insere_node_kd(arv, &((*node)->dir), mun, ++eixo % arv->dim);
    else _insere_node_kd(arv, &((*node)->dir), mun, ++eixo % arv->dim);
}

void * busca_kd(Arv * arv, Municipio * mun) {
    return _busca_node_kd(arv, arv->raiz, mun, 0);
}
void * _busca_node_kd(Arv * arv, Node * node, Municipio * mun, int eixo) {
    void * ret;

    if(!node) ret = NULL;
    else if(compara_coord(node->mun, mun, eixo) > 0) _busca_node_kd(arv, node->esq, mun, ++eixo % arv->dim);
    else if(compara_coord(node->mun, mun, eixo) < 0) _busca_node_kd(arv, node->dir, mun, ++eixo % arv->dim);
    else ret = node->mun;

    return ret;
}

//int remove_kd(Arv * arv, Municipio * mun);
//int remove_node_kd(Arv * arv, Node * node, Municipio * mun);

void libera_kd(Arv * arv) {
    _libera_node_kd(arv->raiz);
}

void _libera_node_kd(Node * node) {
    if(node) {
		_libera_node_kd(node->esq);
		_libera_node_kd(node->dir);
		free(node->mun);
		free(node);
    }
}

void exibe_kd(Arv * arv) {
    _exibe_node_kd(arv, arv->raiz);
}

void _exibe_node_kd(Arv * arv, Node * node) {
    if(node) {
		_exibe_node_kd(arv, node->esq);
		exibe_municipio(node->mun);
		_exibe_node_kd(arv, node->dir);
    }
}

int conta_kd(Arv * arv) {
    return _conta_node_kd(arv->raiz);
}

int _conta_node_kd(Node * node) {
    if(node) return 1 + _conta_node_kd(node->esq) + _conta_node_kd(node->dir);
}

void _insertion_sort_mun_kd(int * codigos, float * distancias, int tam) {
	float key_d;
	int key_m;
	int j;

	for(int i = 1; i < tam; i++) {
		key_d = distancias[i];
		key_m = codigos[i];
		
		j = i - 1;		
		while(j >= 0 && distancias[j] > key_d) {
			distancias[j+1] = distancias[j];
			codigos[j+1] = codigos[j];

			j--;
		}
		distancias[j+1] = key_d;
		codigos[j+1] = key_m;
	}	
}

void _calcula_dist_cod(Arv * arv, Municipio * mun, Node * node, float * distancias, int * codigos, int tam, int * i) {
    if(*i < tam) {
		if(node) {
			_calcula_dist_cod(arv, mun, node->esq, distancias, codigos, tam, i);

			if(distancia_municipios(mun, node->mun)) {
				distancias[*i] = distancia_municipios(mun, node->mun);
				codigos[*i] = node->mun->cod_ibge;

				(*i)++;

				_insertion_sort_mun_kd(codigos, distancias, *i);
			}

			_calcula_dist_cod(arv, mun, node->dir, distancias, codigos, tam, i);
		}
    }
}

int * n_proximos_kd(Arv * arv, Municipio * mun, int n) {
    int i = 0;
    int qtd_nodes = conta_kd(arv)-1;

    float * distancias = (float *) calloc(qtd_nodes, sizeof(float));
	int * codigos = (int *) calloc(qtd_nodes, sizeof(int));

    _calcula_dist_cod(arv, mun, arv->raiz, distancias, codigos, qtd_nodes, &i);

	int * proximos = (int *) calloc(n, sizeof(int));

    for(i = 0; i < n; i++) proximos[i] = codigos[i];

	free(codigos);
    free(distancias);

    return proximos;
}
