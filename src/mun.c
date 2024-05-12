#include "../include/mun.h"

//define a chave de cada município
int get_key_municipio_cod_ibge(void * mun) {
    return (*((Municipio *) mun)).cod_ibge;
}

char * get_key_municipio_nome(void * mun) {
	return (*((Municipio *) mun)).nome;
}

//a partir da passagem de parâmetros, constrói um "objeto" Município
void * aloca_municipio(int ibge, char * nome, double latitude, double longitude, int capital, int uf, int id, int ddd, char * fuso) {
    Municipio * mun = malloc(sizeof(Municipio));

    mun->cod_ibge = ibge;
    strcpy(mun->nome, nome);
    mun->coord[0]= latitude;
    mun->coord[1]= longitude;
    mun->capital = capital;
    mun->cod_uf = uf;
    mun->siafi_id = id;
    mun->ddd = ddd;
    strcpy(mun->fuso, fuso);

    return mun;
}

//informe um ponteiro de Municipio e todas suas informações serão mostradas
void exibe_municipio(void * cid) {
    Municipio * mun = (Municipio *) cid;

    printf("\n");
    printf("codigo_ibge: %d\n", mun->cod_ibge);
    printf("nome: %s\n", mun->nome);
    printf("latitude: %f\n", mun->coord[0]);
    printf("longitude: %f\n", mun->coord[1]);
    printf("capital: %d\n", mun->capital);
    printf("codigo_uf: %d\n", mun->cod_uf);
    printf("siafi_id: %d\n", mun->siafi_id);
    printf("ddd: %d\n", mun->ddd);
    printf("fuso_horario: %s\n", mun->fuso);
    printf("\n");
}

double distancia_municipios(void * cid1, void * cid2) {
    Municipio * mun1 = (Municipio *) cid1;
    Municipio * mun2 = (Municipio *) cid2;

    double aux;
    double dist = 0;

    for(int i = 0; i < 2; i++) {
	    aux = mun1->coord[i] - mun2->coord[i];
	    aux *= aux;
	    dist += aux;
    }

    return sqrt(dist);
}

double compara_coord(void * cid1, void * cid2, int eixo) {
    return ((Municipio *) cid1)->coord[eixo] - ((Municipio *) cid2)->coord[eixo];
}	
