/*risoluzio e di un labirinto*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 20
#define MOSS_MIN 90
#define PASS_MAX 10

/*prototipi*/
void genera_entrata(char labirinto[][DIM], int *eriga, int *ecolonna, int *posr, int *posc);
void stampa_labirinto(char labirinto[][DIM], int *eriga, int *ecolonna, int *uriga, int *ucolonna, int posriga, int poscolonna, int *direzione);
void genera_percorso(char labirinto[][DIM], int *eriga, int *ecolonna, int *posr, int *posc, int *uriga, int *ucolonna);
void attr_perc(char labirinto[][DIM], int *eriga, int *ecolonna, int *posr, int *posc, int *uriga, int *ucolonna, int *direz);

main()
{
      char lab[DIM][DIM];
      int riga, colonna, entr_riga, entr_colonna, pos_riga, pos_colonna, uscita_riga, uscita_colonna, direzione = 0;
      
      /*randomizza i numeri casuali*/
      srand(time(NULL));
      
      /*genera entrata*/
      genera_entrata(lab, &entr_riga, &entr_colonna, &pos_riga, &pos_colonna);
      
      /*genera il percorso del labirinto*/
      genera_percorso(lab, &entr_riga, &entr_colonna, &pos_riga, &pos_colonna, &uscita_riga, &uscita_colonna);
      
      /*attraversamento del labirinto*/
      attr_perc(lab, &entr_riga, &entr_colonna, &pos_riga, &pos_colonna, &uscita_riga, &uscita_colonna, &direzione);
}
  
  
/*genera la posizione d'entrata nel labirinto*/
void genera_entrata(char labirinto[][DIM], int *eriga, int *ecolonna, int *posr, int *posc)
{
      int riga, colonna;
      
      /*inizializza matrice con tutti asterischi*/
      for(riga = 0; riga < DIM; riga++)
      {
               for(colonna = 0; colonna < DIM; colonna++)
               {
                           labirinto[riga][colonna] = '#';
               }
      }
      
      /*genera entrata*/
      *eriga = rand() % DIM;
      
      /*se la riga e la prima o l'ultima;
      /*posizione colonna da 1 a DIM - 2*/
      if(*eriga == 0 || *eriga == DIM - 1)
      {
                   *ecolonna = 1 + (rand() % (DIM - 2));
      }
      
      /*se la riga e compresa tra la seconda riga e la pen'ultima*/
      /*posiziona colonna tra 0 e DIM - 1*/
      else if(*eriga> 0 && *eriga < DIM - 1)
      {
           /*intera finche non esce o 0 o DIM - 1*/
           do
           {
                    *ecolonna = rand() % DIM;
           
           }while(*ecolonna != 0 && *ecolonna != DIM - 1);
      }
      
      /*assegna l'entrata come posizione*/
      *posr = *eriga;
      *posc = *ecolonna;
      labirinto[*eriga][*ecolonna] = '.';
}    

/*stampa il labirinto*/
void stampa_labirinto(char labirinto[][DIM], int *eriga, int *ecolonna, int *uriga, int *ucolonna, int posriga, int poscolonna, int *direzione)
{
     int riga, colonna;
     
     /*assegna posizione*/
      labirinto[posriga][poscolonna] = 'x';
      
     for(riga = 0; riga < DIM; riga++)
     {
               printf("\t\t\t     ");
               for(colonna = 0; colonna < DIM; colonna++)
               {
                           printf("%c ", labirinto[riga][colonna]);
               }
               printf("\n\n");
      }
      
      printf("Entrata = Riga: %d - Colonna: %d\n", *eriga + 1, *ecolonna + 1);
      printf("Uscita = Riga: %d - Colonna: %d\n", *uriga + 1, *ucolonna + 1);
      printf("Posizione = Riga: %d - Colonna: %d\n", posriga + 1, poscolonna + 1);
      printf("Direzione = ");
      
      /*se direzione 0 nessuna*/
      if(*direzione == 0)
      printf("Nessuna");
      
      else if(*direzione == 1)
      printf("Destra");
      
      else if(*direzione == 2)
      printf("Giu");
      
      else if(*direzione == 3)
      printf("Sinistra");
      
      else
      printf("Su");
      
      /*se il labirinto non ha uscita*/
      if(*eriga == *uriga && *ecolonna == *ucolonna)
      {
                printf("\n\nIl labirinto non ha uscita*/");
      }
}

/*Genera il percorso del labirinto*/
void genera_percorso(char labirinto[][DIM], int *eriga, int *ecolonna, int *posr, int *posc, int *uriga, int *ucolonna)
{
     int passi, cont, mossa = 1, direzione;
     
     /*itera finche non si crea un uscita*/
     do
     {
         /*direzioni da prendere in base alla posizione attuale*/
         /*se la posizione iniziale e alla prima colonna vai a destra*/
         if(*posc == 0)
         {
             /*stabilisci direzione*/
             /*destra*/
             direzione = 1;
         }
     
         /*se la posizione in iniziale e a l'ultima colonna vai a sinistra*/
         else if(*posc == DIM - 1)
         {
              /*sinistra*/
              direzione = 3;
          }
     
          /*se la posizione in iniziale e alla prima riga vai a giu*/
          else if(*posr == 0)
          {
               /*giu*/
               direzione = 2;
          }
     
          /*se la posizione in iniziale e alla prima riga vai a giu*/
          else if(*posr == DIM - 1)
          {
               /*giu*/
               direzione = 4;
          }
     
          /*altrimenti scegli casualmene la direzione*/
          else
          {
              /*casuale*/
              direzione = 1 + (rand() % 4);
          }
     
          /*genera i passi da fare in una direzione*/
          passi = 1 + (rand() % PASS_MAX);
          
          /*itera fino al numero di passi per segnare ogni casela*/
          for(cont = 1; cont <= passi; cont++)
          {
              /*prima di generare un uscita fare almeno MOSS_MIN mosse
                per espandere il labirinto*/
              
              /*se non sono state fatte MIN_MOSS non creare uscita*/
              if(mossa <= MOSS_MIN)
              {
                       /*se la direzione e destra*/
                       if(direzione == 1)
                       {
                                    /*se la colonna piu 1 uguale a 11 assegna mossa precedente e esci*/
                                    if(*posc + 1 == DIM - 1)
                                    {
                                             break;
                                    }
                                    
                                    /*altrimenti assegna mossa*/
                                    else
                                    {
                                        labirinto[*posr][*posc + 1] = '.';
                                        *posc += 1;
                                    }
                       }
              
                       /*se la direzione e sinistra*/
                       else if(direzione == 3)
                       {
                            /*se la colonna meno 1 uguale a 0 assegna mossa precedente e esci*/
                            if(*posc - 1 == 0)
                            {
                                     break;
                            }
                            
                            /*altrimenti assegna mossa*/
                            else
                            {
                                labirinto[*posr][*posc - 1] = '.';
                                *posc -= 1;
                            }
                       }
              
                       /*se la direzione e giu*/
                       else if(direzione == 2)
                       {
                            /*se la riga piu 1 uguale a 11 assegna mossa precedente e esci*/
                            if(*posr + 1 == DIM - 1)
                            {
                                     break;
                            }
                            
                            /*altrimenti assegna mossa*/
                            else
                            {
                                labirinto[*posr + 1][*posc] = '.';
                                *posr += 1;
                            }
                       } 
              
                       /*se la direzione e su*/
                       else if(direzione == 4)
                       {
                            /*se la riga meno 1 uguale a 0 assegna mossa precedente e esci*/
                            if(*posr - 1 == 0)
                            {
                                     break;
                            }
                            
                            /*altrimenti assegna mossa*/
                            else
                            {
                                     labirinto[*posr - 1][*posc] = '.';
                                     *posr -= 1;
                            }
                       } 
              }
              
              /*se ha superato il numero minimo di mosse itera finche non si crea un uscita*/
              else
              {
                       /*se la direzione e destra*/
                       if(direzione == 1)
                       {
                                    /*se la colonna piu 1 uguale a 11 assegna assegna e termina*/
                                    if(*posc + 1 == DIM - 1)
                                    {
                                             *posc += 1;
                                             labirinto[*posr][*posc] = '.';
                                             break;
                                    }
                                    
                                    /*altrimenti assegna mossa*/
                                    else
                                    {
                                        labirinto[*posr][*posc + 1] = '.';
                                        *posc += 1;
                                    }
                       }
                       
                       /*se la direzione e sinistra*/
                       else if(direzione == 3)
                       {
                            /*se la colonna meno 1 uguale a 0 assegna mossa precedente e esci*/
                            if(*posc - 1 == 0)
                            {
                                     *posc -= 1;
                                     labirinto[*posr][*posc] = '.';
                                     break;
                            }
                            
                            /*altrimenti assegna mossa*/
                            else
                            {
                                labirinto[*posr][*posc - 1] = '.';
                                *posc -= 1;
                            }
                       }
                       
                       /*se la direzione e giu*/
                       else if(direzione == 2)
                       {
                            /*se la riga piu 1 uguale a 11 assegna mossa precedente e esci*/
                            if(*posr + 1 == DIM - 1)
                            {
                                     *posr += 1;
                                     labirinto[*posr][*posc] = '.';
                                     break;
                            }
                            
                            /*altrimenti assegna mossa*/
                            else
                            {
                                labirinto[*posr + 1][*posc] = '.';
                                *posr += 1;
                            }
                       } 
                       
                       /*se la direzione e su*/
                       else if(direzione == 4)
                       {
                            /*se la riga meno 1 uguale a 0 assegna mossa precedente e esci*/
                            if(*posr - 1 == 0)
                            {
                                     *posr -= 1;
                                     labirinto[*posr][*posc] = '.';
                                     break;
                            }
                            
                            /*altrimenti assegna mossa*/
                            else
                            {
                                     labirinto[*posr - 1][*posc] = '.';
                                     *posr -= 1;
                            }
                       } 
              }
          }
          
      ++mossa;
      }while(*posr != 0 && *posr != DIM - 1 && *posc != 0 && *posc != DIM - 1);
      
      /*assegna uscita*/
      *uriga = *posr;
      *ucolonna = *posc;
      
      /*imposta posizione all'entrata*/
      *posr = *eriga;
      *posc = *ecolonna;
}

/*funzione ricorsiva per attraversare il labirinto*/
void attr_perc(char labirinto[][DIM], int *eriga, int *ecolonna, int *posr, int *posc, int *uriga, int *ucolonna, int *direz)
{
     int posx = *posr, posy = *posc;
     
     /*pulisci schermo*/
     system("cls");
     
     /*stampa labirinto*/
     stampa_labirinto(labirinto, eriga, ecolonna, uriga, ucolonna, *posr, *posc, direz);
     getch();
     
     /*caso base*/
     /*se e stata trovata l'uscita termina*/
     /*controlla se e stato raggiunta un uscita, ma verifica che non sia l'entarta*/
     if(*posr == *uriga && *posc == *ucolonna)
     {
              printf("\n\n\nUscita trovata");
              getch();
     }
     
     /*ricorsione*/
     /*altrimenti muovi fino a trovare l'uscita*/
     else
     {
         /*se la posizione e sulla colonna 0 fai un passo a destra*/
         if(*posc == 0)
         {
                  labirinto[*posr][*posc] = '.';
                  *posc += 1;
                  *direz = 1;
                  return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
         }
          
         /*se la posizione e sulla colonna DIM - 1 fai un passo a sinistra*/
         else if(*posc == DIM - 1)
         {
                  labirinto[*posr][*posc] = '.';
                  *posc -= 1;
                  *direz = 3;
                  return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
         }
         
         /*se la posizione e sulla riga 0 fai un passo giu*/
         else if(*posr == 0)
         {
                  labirinto[*posr][*posc] = '.';
                  *posr += 1;
                  *direz = 2;
                  return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
         }
         
         /*se la posizione e sulla riga DIM - 1 fai un passo su*/
         else if(*posr == DIM - 1)
         {
                  labirinto[*posr][*posc] = '.';
                  *posr -= 1;
                  *direz = 4;
                  return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
         }    
         
         /*altrimenti*/
         else
         {
             /*se e stato fatto un passo a destra*/
             if(*direz == 1)
             {
                      /*se la casella giu e un . vai giu*/
                      if(labirinto[*posr + 1][*posc] == '.')
                      {
                                         labirinto[*posr][*posc] = '.';
                                         *posr += 1;
                                         *direz = 2;
                                         return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se giu e un # vai a destra*/
                      else if(labirinto[*posr][*posc + 1] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posc += 1;
                           *direz = 1;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se a destra e un # vai su*/
                      else if(labirinto[*posr - 1][*posc] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posr -= 1;
                           *direz = 4;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti torna a sinistra*/
                      else
                      {
                           labirinto[*posr][*posc] = '.';
                           *posc -= 1;
                           *direz = 3;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
             }
             
             /*se e stato fatto un passo giu*/
             else if(*direz == 2)
             {
                       /*se la casella a sinistra e un . vai a sinistra*/
                      if(labirinto[*posr][*posc - 1] == '.')
                      {
                                         labirinto[*posr][*posc] = '.';
                                         *posc -= 1;
                                         *direz = 3;
                                         return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se sinistra e un # vai giu*/
                      else if(labirinto[*posr + 1][*posc] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posr += 1;
                           *direz = 2;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se giu e un # vai destra*/
                      else if(labirinto[*posr][*posc + 1] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posc += 1;
                           *direz = 1;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti torna su*/
                      else
                      {
                           labirinto[*posr][*posc] = '.';
                           *posr -= 1;
                           *direz = 4;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
             }
             
             /*se e stato fatto un passo a sinistra*/
             else if(*direz == 3)
             {
                      /*se la casella su e un . vai su*/
                      if(labirinto[*posr - 1][*posc] == '.')
                      {
                                         labirinto[*posr][*posc] = '.';
                                         *posr -= 1;
                                         *direz = 4;
                                         return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se su e un # vai a sinistra*/
                      else if(labirinto[*posr][*posc - 1] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posc -= 1;
                           *direz = 3;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se a sinistra e un # vai giu*/
                      else if(labirinto[*posr + 1][*posc] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posr += 1;
                           *direz = 2;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti torna a destra*/
                      else
                      {
                           labirinto[*posr][*posc] = '.';
                           *posc += 1;
                           *direz = 1;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
             }
             
             /*se e stato fatto un passo su*/
             else if(*direz == 4)
             {
                       /*se la casella a destra e un . vai a destra*/
                      if(labirinto[*posr][*posc + 1] == '.')
                      {
                                         labirinto[*posr][*posc] = '.';
                                         *posc += 1;
                                         *direz = 1;
                                         return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se destra e un # vai su*/
                      else if(labirinto[*posr - 1][*posc] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posr -= 1;
                           *direz = 4;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti se su e un # vai a sinistra*/
                      else if(labirinto[*posr][*posc - 1] == '.')
                      {
                           labirinto[*posr][*posc] = '.';
                           *posc -= 1;
                           *direz = 3;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
                      
                      /*altrimenti torna giu*/
                      else
                      {
                           labirinto[*posr][*posc] = '.';
                           *posr += 1;
                           *direz = 2;
                           return attr_perc(labirinto, eriga, ecolonna, posr, posc, uriga, ucolonna, direz);
                      }
             }
         } 
     }
}
