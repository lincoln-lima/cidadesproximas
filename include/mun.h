#ifndef __MUNICIPIO__
#define __MUNICIPIO__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct {
    int cod_ibge;
    char nome[35];
    double coord[2];
    int capital;
    int cod_uf;
    int siafi_id;
    int ddd;
    char fuso[50];
} Municipio;

int get_key_municipio(void * mun);
void * aloca_municipio(int ibge, char * nome, double latitude, double longitude, int capital, int uf, int id, int ddd, char * fuso);
void exibe_municipio(void * cid);
double compara_coord(void * cid1, void * cid2, int eixo); 
double distancia_municipios(void * cid1, void * cid2);
#endif
