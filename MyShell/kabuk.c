#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

/* 
 @author 
 
NOT:*****
->Hocam çalıştırmak için test1,test2,test3 var .
->parametrelilere örnekte parametreTest1, parametreTest2 exelerimiz var.

->Bazen,arada bir  MyShell yazısı çıkmıyor ama siz yazdığınızda algılıyor çalıştırıyor. Sonsuz döngüde.
-> bir de test1 i çalıştırmak için mesela sadece test1 yazın test1.exe yazarsanız hata veriyor.
-> parametreTest1 iki string parametresi alıyor, parametreTes2 de iki sayı alıyor

*/

//Aynı dizinde iseler programı çalıştırıyor.

const int max=4; 
const int min=1;

int fonkNe(char *giris) //fonksiyonunun parametreli mi parametresiz mi olduğunu anlamak icin
{
  int dondur=0;
  char *d;
  int say=0;

  for(d=strtok(giris,""); d!=NULL; d=strtok(NULL,""))
   { 
     say=say+1;
     if(*d=='&')
      break;
   }

  if(say>=2)// & a kadar 2 veya daha fazla boşluk varsa parametrelidir.
    dondur=1;

return dondur;

}


//***** proses calıştırma *****
 void cokluCalistir( char *args)
  {   
    pid_t pid;
    char *parca[100]; //parçaladığı verileri tutmak için 
    char* al;
    int say=0;
    int s=0;
    int progSayisi=0; //kaç tane program çalıştırılacagı
 
     //burada gelen komutları & işaretine göre ayırdık
     for(al=strtok(args,"&"); al!=NULL; al=strtok(NULL,"&"))
     {
      if(*al!='&')
       {
         parca[say++]=al;
         progSayisi=progSayisi+1;
       } 
     }

   
    parca[say++]=NULL;  

    
  
    while(progSayisi>=min && progSayisi<=max) //en az 1 tane girilmiş ve 4ten küçük eşitse 
    {
      
        pid=fork();
       
        if (pid == 0)
        {
          
         if(*parca[s]!='&') 
         { 
           if(execl (parca[s], parca[s], (char *) NULL)<0)
           printf("%s dosyası bulunamıyor..\n",parca[s]);
         }
        }

 
      s=s+1;
      progSayisi=progSayisi-1;
    }

    
    if(progSayisi>max) //4ten fazla ise uyarıyor 
       printf("4ten fazla dosya çalıştıramazsınız tekrar deneyin....\n"); 

}

//parametreli çalıştırmak için ...
void parametreliCalistir(char *gelen) //Bu fonksiyon çalışmadı..
{

   char *al1,*al2;     
   char* parcala2[200];
   int parametreSay=0;

   al1=strtok(gelen,""); //boşluklara göre ayırıyoruz
   while(al1!=NULL)
   {
       if(*al1!='&') 
         parcala2[parametreSay++]=al1;
    
      else //ayırdığımız karakter & da olabilir. & olunca birinci programı toplamış oluyoruz . Burada çalıştırıyoruz. 
       {
       parcala2[parametreSay++]=NULL;
       parametreSay=0;
       
       //parametreyi ve adını proggram şimdi çalıştıralım bitince nullarız.parcala1 de adı, parcala2 de parametreler var
         if(execv(parcala2[1],parcala2)<0)
            printf("Program çalıştırılamıyor.....");
             
       }
     al1=strtok(NULL,"");
   }

}


 int main(int argc, char *argv[])
 {
    char komut[500];
    int gelenDeger; 
    

    while(1)
    {
      printf("myShell>>");
      scanf("%s",komut);
      
      
   
      gelenDeger=fonkNe(komut); // eğer boşluğa göre ayrılabiliyorsa  parametrelidir fonksiyona gitsin kontrol edilsin

      if(gelenDeger==1) //parametreli ise 1 dönücekti o yuzden parametreli fonksiyona gönderdim
      parametreliCalistir(komut);
      else 
      cokluCalistir(komut);
      
    
   }


   return 0;

 }










