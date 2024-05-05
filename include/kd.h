#ifndef __KD__
#define __KD__
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
	void (* printa)(void *);
	int (* get_key)(void *);
} Arv;

void constroi_kd(Arv * arv, int dim, double (* dist)(void *, void *), double (* cmp)(void *, void *, int), void (* printa)(void *), int (* get_key)(void *));
void insere_kd(Arv * arv, void * reg);
void insere_node_kd(Arv * arv, Node ** node, void * reg, int eixo);
void * busca_kd(Arv * arv, void * reg, int cod);
void * busca_node_kd(Arv * arv, Node * node, void * reg, int eixo, int cod);
//int remove_kd(Arv * arv, void * reg);
//int remove_node_kd(Arv * arv, Node * node, void * reg);
void libera_kd(Arv * arv);
void libera_node_kd(Node * node);
void printa_kd(Arv * arv);
void printa_node_kd(Arv * arv, Node * node);
int conta_kd(Arv * arv);
int conta_node_kd(Node * node);
void atribui_distancias(Arv * arv, Node * node, Node * aux, float * distancias, int tam, int * i); 
void n_proximos_kd(Arv * arv, Node * node, int n); 
#endif
