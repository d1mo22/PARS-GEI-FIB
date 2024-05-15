#include <stdio.h>

#define N 200000
#define tam 16*1024*1024

#define CACHE_SIZE 1310464

int i, j, limite;
unsigned char v[tam];

void InitCache(int cod);
void Referencia(unsigned char *dir);
int Referencias();
int Fallos();
 
int refs, misses;

int main() 
{  int i, j;

  for (limite = 1; limite <= 65536; limite++) {
    InitCache(879883513); 
    for (i=0, j=0; j<N; j++) {
      if ((j % limite)==0) i=0;
      Referencia(&v[i]);     // acceso a v[i] 
      i=i+CACHE_SIZE;
    }

    refs = Referencias();
    misses = Fallos(); 

    printf("Associativity? limite=%5d ; fallos=%6d ; referencias=%6d\n", limite, misses, refs);

  }

  return 0;
}

