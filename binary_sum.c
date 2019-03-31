#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int *resultado;

int * sumar_acarreo(int *res, int *acarreo){
  resultado = (int *)malloc((5)*sizeof(int));
  int aux = 0;
  for(int i = 0; i < 5; i++){
    if(acarreo[i] == 1)
      aux = 1;
  }

  //int nuevoRes[5];
  int nuevoAca[5];

  for(int i = 0; i < 5; i++){
    resultado[i] = 0;
    nuevoAca[i] = 0;
  }

  if (aux == 1){
    for(int i = 0; i < 5; i++){
      if ((res[i] == 1) && (acarreo[i] == 1)){
	resultado[i] = 0;
	nuevoAca[i-1] = 1;
      }
      else{
	resultado[i] = res[i] + acarreo[i];
      }
      
    }
    printf("Arreglo resultante: \n");
    for(int i = 0; i < 5; i++){
      printf("%d", resultado[i]);
    }
    printf("\n");
    sumar_acarreo(resultado, nuevoAca);
  }
  else{
    
    //return nuevoRes
    printf("ya llegaste\n");
  
    return resultado;}
  
}

int pot( int base, int exp)
{
  if(exp == 0)
    {
      return 1;
    } else
    {
      return base*pot(base, exp-1);
    }
}

int main(int argc, char **argv){
  int potencia;
  if (argc < 2)
    {
      printf("por favor especifique el numero\n");
      exit(1);
    }

  sscanf(argv[1], "%i", &potencia);
  int poten = pot(2,potencia);

  printf("El valor de poten: %i\n", poten);

  int An[] = {1,1,1,1};
  int Bn[] = {0,1,0,0};
  //Resultados
  int Cn[poten + 1];
  //Auxiliar
  int Dn[poten +1];

  for (int i=0 ;i <=poten; i++)
  {
    Cn[i] = 0;
  }

  for (int i=0 ;i <=poten; i++)
  {
    Dn[i] = 0;
  }

  printf("El arreglo A: \n");
  for (int i=0 ;i < poten; i++)
  {
    printf("%i",An[i]);
  }
  printf("\n");

  printf("El arreglo B: \n");
  for (int i=0 ;i <poten; i++)
  {
    printf("%i",Bn[i]);
  }
  printf("\n");

  int idHilo;
  omp_set_num_threads(poten);
#pragma omp parallel shared(idHilo)
  {
    idHilo = omp_get_thread_num();
    //printf("Hilo: %d\n", idHilo);
    if((An[idHilo] == 1)&&(Bn[idHilo]==1)){
      Cn[idHilo+1]=0;
      //if(idHilo != 0)
	Dn[idHilo]=1;
      //printf("Entro en: %i\n", idHilo);
    }else{
      Cn[idHilo+1] = An[idHilo] + Bn[idHilo];
    }
  }

  printf("Resultados: \n");
  for (int i=0 ;i <=poten; i++)
  {
    printf("%i",Cn[i]);
  }
  printf("\n");

  printf("Auxiliar: \n");
  for (int i=0 ;i <= poten; i++)
  {
    printf("%i",Dn[i]);
  }
  printf("\n");

  sumar_acarreo(Cn, Dn);


  printf("Arreglo resultante: \n");
  for(int i = 0; i <= poten; i++){
    printf("%d", resultado[i]);
  }
  printf("\n");

  
  return 0;
}
