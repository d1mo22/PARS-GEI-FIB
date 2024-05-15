#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
struct linea {
	int v;
	int TAG;
};

struct linea cache[128];
int hit = 0, fallo = 0;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 128; i++) cache[i].v = 0;


}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reempla�a una linia valida
	unsigned int tag_out;	   // TAG de la linia reempla�ada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */
	byte = address%32;
	bloque_m = address/32;
	linea_mc = bloque_m%128;
	tag = bloque_m/128;
	if (cache[linea_mc].v == 0) {
		miss = 1;
		replacement = 0;
		tag_out = -1;
		cache[linea_mc].TAG = tag;
		cache[linea_mc].v = 1;
	}
	else if (cache[linea_mc].v == 1 && cache[linea_mc].TAG != tag) {
		miss = 1;
		replacement = 1;
		tag_out = cache[linea_mc].TAG;
		cache[linea_mc].TAG = tag;
	}
	else {
		miss = 0;
		replacement = 0;
		tag_out = -1;
	}
	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. Tamb� mesurem el temps d'execuci�
	 * */
	if (miss) ++fallo;
	else ++hit;
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
  	printf("Aciertos %d y fallos %d\n", hit, fallo);
  
}
