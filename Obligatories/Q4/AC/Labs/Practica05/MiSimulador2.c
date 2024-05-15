#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
struct linea {
	int v;
	int TAG;
};

struct linea cache0[64];
struct linea cache1[64];
int lru[64];
int hit = 0, fallo = 0;

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 64; i++)  {
		cache0[i].v = 0;
		cache1[i].v = 0;
		lru[i] = -1;
	}
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reempla�a una linia valida
	unsigned int tag_out;	   // TAG de la linia reempla�ada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */
	byte = address%32;
	bloque_m = address/32;
	conj_mc = bloque_m%64;
	tag = bloque_m/64;
	if (cache0[conj_mc].v == 0) {
		if (cache1[conj_mc].v == 0) {
			miss = 1;
			replacement = 0;
			cache0[conj_mc].TAG = tag;
			cache0[conj_mc].v = 1;
			lru[conj_mc] = 0;
			via_mc = 0;
		}
		else {
			if (cache1[conj_mc].TAG != tag) {
				miss = 1;
				replacement = 0;
				cache0[conj_mc].TAG = tag;
				cache0[conj_mc].v = 1;
				lru[conj_mc] = 0;
				via_mc = 0;
			}
			else {
				miss = 0;
				replacement = 0;
				lru[conj_mc] = 1;
				via_mc = 1;
			}
		}
	}
	else {
		if (cache0[conj_mc].TAG != tag) {
			if (cache1[conj_mc].v == 0) {
				miss = 1;
				replacement = 0;
				cache1[conj_mc].TAG = tag;
				cache1[conj_mc].v = 1;
				lru[conj_mc] = 1;
				via_mc = 1;
			}
			else {
				if (cache1[conj_mc].TAG != tag)  {
					if (lru[conj_mc] == 0) {
						miss = 1;
						replacement = 1;
						tag_out = cache1[conj_mc].TAG;
						cache1[conj_mc].TAG = tag;
						cache1[conj_mc].v = 1;
						lru[conj_mc] = 1;
						via_mc = 1;
					}
					else {
						miss = 1;
						replacement = 1;
						tag_out = cache0[conj_mc].TAG;
						cache0[conj_mc].TAG = tag;
						cache0[conj_mc].v = 1;
						lru[conj_mc] = 0;
						via_mc = 0;
					}
				}
				else {
					miss = 0;
					replacement = 0;
					lru[conj_mc] = 1;
					via_mc = 1;
				}
			}
		}
		else {
			miss = 0;
			replacement = 0;
			lru[conj_mc] = 0;
			via_mc = 0;
		}
	}
	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. Tamb� mesurem el temps d'execuci�
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	if (miss) ++fallo;
	else ++hit;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
	printf("Aciertos %d y fallos %d\n", hit, fallo);
  
}
