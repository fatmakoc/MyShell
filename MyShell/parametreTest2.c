#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//bu program iki sayı alıp topluyor..

int main(int argc, char *argv[], char *envp[]) //buraya char **argv yazmayı dene bir de
{
  int toplam;
   
       toplam=toplam + atoi(argv[1])+atoi(argv[2]);
       
    
  printf("Toplam sonuc= %d",toplam);
}
