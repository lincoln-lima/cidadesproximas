#include <stdio.h>
#include <json-c/json.h>

typedef struct {
	int cod_ibge;
	char[] nome;
	int latitude;
	int capital;
	int cod_uf;
	int siafi_id;
	int ddd;
	char[] fuso;

} Municipios;

int main() {
	FILE * arq = fopen("../file/municipios.json", r);

	if(!arq) printf("erro para abrir arquivo\n");

	char buffer[2048];
	
	return EXIT_SUCCESS;
}
