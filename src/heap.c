#include "../include/heap.h"

/* funções para encontrar pai e filhos, recebendo como parâmetro o índice do vetor  */
int pai(int n) {
    return (n-1)/2;
}

int f_esq(int n) {
    return (n*2)+1;
}

int f_dir(int n) {
    return (n*2)+2;
}

/* realiza a troca de valores de duas variáveis  */
void troca(float *a, float *b) {
    float aux = *a;
    *a = *b;
    *b = aux;
}

/* percorre os filhos em busca do valor maior  */
void desce(float v[], int pos, int max_size) {
    int e, d, max_value;

    /* guardando valores dos índices dos filhos e posição do maior valor  */
    e = f_esq(pos);
    d = f_dir(pos);
    max_value = pos;

    /* checagem de tamanho e se os filhos são maiores que o pai  */
    if(e < max_size && v[max_value] < v[e]) max_value = e;
    if(d < max_size && v[max_value] < v[d]) max_value = d;

    /* caso o pai não seja o maior valor, trocar com o filho */
    if(max_value!=pos) {
        troca(&v[pos],&v[max_value]);
	desce(v, max_value, max_size);
    }
}

/* percorre os pais a partir de um nó determinando se seu valor é menor que seu filho  */
void sobe(float v[], int pos) {
    if(v[pai(pos)] < v[pos] && pos > 0) {
        troca(&v[pai(pos)], &v[pos]);
	sobe(v, pai(pos));
    }
}

/* retorna o maior valor, como no caso da max_heap, está no índice 0 */
float acessa_max(float v[]) {
    return v[0];
}

/* percorre a partir do último pai da heap e engloba os demais nós a partir da função desce */
void constroi_heap(float v[], int max_size) {
    for(int i = pai(max_size-1); i>=0; i--) desce(v, i, max_size);
}

/* retorna extraindo o maior valor da heap, reajustando-a após tal */
float extrai_max(float v[], int *size) {
    float ret = acessa_max(v);
    
    *size -= 1;
    v[0] = v[*size];
    desce(v, 0, *size);

    return ret;
}

/* insere elemento na última posição e chama a função sobe para adequação do valor */
int insere_elemento(float v[], float new_element, int max_size, int *size) {
    int ret = EXIT_FAILURE;

    if(*size < max_size) {
	v[*size] = new_element;
	sobe(v, *size);
        *size += 1;
        ret = EXIT_SUCCESS;
    }

    return ret;
}

/* realiza a alteração de um valor do vetor e a partir de seu nó, reajusta a heap */
void altera_prioridade(float v[], int pos, int max_size, float value) {
    if(v[pos] < value) {
        v[pos] = value;
	sobe(v, pos);
    }
    else if(v[pos] > value) {
	v[pos] = value;
	desce(v, pos, max_size);
    }
}

/* troca o primeiro elemento com o último, posiciando o maior ao fim, assim ordenando o vetor */
void heap_sort(float v[], int max_size) {
    for(int i = max_size-1; i >= 0; i--) {
	troca(&v[i], &v[0]);
	desce(v, 0, i);
    }    
}
