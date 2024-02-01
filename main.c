#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* STRUTTURE */

struct Intervallo {
       int sinistra;
       int destra;
};

typedef struct Intervallo INTER;

struct Nodo {
    INTER intervallo;
    struct Nodo* next;
};

typedef struct Nodo* NODO;

/* STAMPE */

/* per stampare un intervallo */
void stampaIntervallo(INTER intervallo) {
       for(int i=0;i<intervallo.sinistra;i++)
              printf(" ");
       for(int i=intervallo.sinistra;i<=intervallo.destra;i++)
              printf("-");
       printf("\n");
}

/* per stampare una lista di intervalli */
void stampa(NODO lista) {
     /* vai avanti fino a che ci sono intervalli */
     lista = lista->next;         // supera il nodo fittizio
     if(lista==NULL)
               printf("La lista e' vuota!\n\n");
     else {
               printf("************\n");
               printf("Ecco gli intervalli in lista\n");
               printf("************\n");
               while(lista!=NULL) {
                     stampaIntervallo(lista->intervallo);
                     lista = lista->next;
               }
               printf("\n");
               printf("*************\n\n");
     }
}

/* INSERIMENTO IN TESTA */

/* leggi i campi di un intervallo */
INTER leggiIntervallo() {
      INTER in;            // da leggere
      do {
             printf("Introduci l'estremo sinistro dell'intevallo: ");
             scanf("%d", &in.sinistra);
             if(in.sinistra<0)
                     printf("L'estremo sinistro deve essere maggiore o uguale a zero!\n\n");
      }
      while(in.sinistra<0);
      do {
             printf("Introduci l'estremo destro dell'intervallo: ");
             scanf("%d", &in.destra);
             if(in.destra<=in.sinistra)
                     printf("L'estremo destro deve essere maggiore di quello sinistro!\n");
      }
      while(in.destra<=in.sinistra);
      return in;
}

/* inserimento di un intervallo in testa alla lista */
void inserimento(NODO head) {
     /* alloca memoria per il nodo */
     NODO testa = malloc(sizeof(struct Nodo));
     /* riempi il campo dati */
     testa->intervallo = leggiIntervallo();
     /* collega il nuovo nodo al successivo */
     testa->next = head->next;
     /* collega il nuovo nodo al nodo fittizio */
     head->next = testa;
     printf("Inserimento effettuato!\n\n");
}

/* CANCELLAZIONE */

/* funzione che cancella l'ultimo intervallo della lista */
void cancellazione(NODO lista) {
     /* c'e' un intervallo da cancellare? */
     if(lista->next==NULL)
               printf("Niente da cancellare!\n\n");
     else {
           /* arriva in fondo alla lista */
           while(lista->next->next!=NULL) {
                   lista = lista->next;
           }
           /* OK sei in fondo: dealloca l'ultimo nodo ed il penultimo diventa ultimo */
           free(lista->next);
           lista->next = NULL;
           /* stampa messaggio e termina */
           printf("Intervallo cancellato!\n\n");
     }
}

/******** ORDINAMENTO ********/

/* funzione che determina se un intervallo precede un altro */
int precede(INTER in1, INTER in2) {
      int prima;          // valore da restituire
      if(in1.sinistra<in2.sinistra  || (in1.sinistra=in2.sinistra && in1.destra<in2.destra))
          prima = 1;
      else
          prima = 0;
      return prima;
}

/* funzione che ordina gli elementi di una lista; implementa il selection sort*/
void ordina(NODO lista) {
       NODO primo;       // il primo nodo non ordinato della lista
       NODO minimo;          // minimo corrente
       NODO nodo;             // nodo corrente
       INTER inter;            // variabile ausiliaria
       /* se la lista e' vuota non fare niente */
       if(lista->next!=NULL) {
           /* il primo nodo non ordinato e' il primo nodo della lista (non fittizio)*/
           primo = lista->next;
           /* prosegui fino a che la parte ordinata ha almeno due nodi */
           while(primo->next!=NULL) {
                  /* inizializza il minimo a primo */
                  minimo = primo;
                  /* guarda tutti i nodi a partire dal successivo a primo e prosegui
                     fino a che non li hai visti tutti */
                     for(nodo=primo->next;nodo!=NULL;nodo=nodo->next)
                     /* minore del minimo? */
                     if(precede(nodo->intervallo, minimo->intervallo))
                     minimo = nodo;
                     /* adesso scambia i campi dati del minimo e del primo elemento non ordinato */
                     inter = primo->intervallo;
                     primo->intervallo = minimo->intervallo;
                     minimo->intervallo = inter;
                     /* fai scorrere il primo elemento non ordinato */
                     primo = primo->next;
           }
           printf("Lista ordinata!\n\n");
       }
       else
           printf("Non ci sono abbastanza intervalli da ordinare!\n");
}

/***** INTERSEZIONE *****/

/* funzione che verifica se due intervalli hanno intersezione non nulla */
int esisteIntersezione(INTER in1, INTER in2) {
      /* due intervalli hanno intersezione vuota se il lato destro di uno dei due
         e' a sinistra del lato sinistro dell'altro */
         return !(in1.destra<in2.sinistra) && !(in2.destra<in1.sinistra);
}

/* funzione che dati due intervalli ne calcola l'intersezione, assumendo che ci sia */
INTER intersezioneADue(INTER in1, INTER in2) {
                  // pre: intersezione non vuota
      INTER in;            // da restituire
      if(in1.sinistra>=in2.sinistra)
               in.sinistra = in1.sinistra;
      else
               in.sinistra = in2.sinistra;
      if(in1.destra<=in2.destra)
               in.destra = in1.destra;
      else
               in.destra = in2.destra;
      return in;
}

/* funzione che calcola e stampa l'intersezione di una lista di intervalli */
void intersezione(NODO lista) {
             INTER inter;                    // l'intersezione corrente                  // per scorrere la lista
             if(lista->next==NULL)    //lista vuota
                      printf("Non ci sono abbastanza elementi.\n\n");
             else {          // almeno un intervallo
                               inter = lista->next->intervallo;           // supera il nodo fittizio
                               lista = lista->next;
                          while(lista!=NULL) {
                      // confronta il prossimo intervallo della lista con l'intersezione attuale
                          if(esisteIntersezione(lista->intervallo, inter))
                               inter = intersezioneADue(lista->intervallo, inter);
                                lista = lista->next;
                           }
                           /* stampa l'intersezione solo se e' presente */
                           if(inter.sinistra<=inter.destra) {
                                   stampa(lista);
                                   printf("Ecco l'intersezione!\n");
                                   stampaIntervallo(inter);
                                   printf("\n");
                           }
                           else
                           printf("Non esistono intersezioni nella lista di intervalli.\n\n");
             }
        }


/***** GESTIONE FILE *****/
/* funzione per l'acquisizione di una lista su file, soluzione con nodo fittizio */
void acquisizione(NODO head) {
       FILE* fp = fopen("intervalli.dat", "rb");
       // per la lettura di un file binario

       /* se non hai aperto il file non devi fare niente */
       if(fp!=NULL) {
              int letto;           // lettura OK o no
              NODO nodo;      // nodo corrente
              INTER inter;        // un intervallo
       /* collega la lista al nodo fittizio */
       nodo = head;
       /* adesso leggi gli intervalli */
       do {
          /* leggi un intervallo */
          letto = fread(&inter, sizeof(INTER), 1, fp);
          if(letto) {       // lo hai letto effettivamente?
            // memorizza nell'heap il nodo corrispondente
            nodo->next = malloc(sizeof(struct Nodo));
            nodo->next->intervallo = inter;
            // aggiorna l'ultimo nodo
            nodo = nodo->next;
          }
          else // il file e' terminato, setta il campo next dell'ultimo nodo
             nodo->next = NULL;
       }
       while(letto);
       }
       fclose(fp);
}

/* funzione per il salvataggio di una lista su file */
void salvataggio(NODO lista){
      FILE* fp = fopen("intervalli.dat", "wb"); //per la scrittura di un file binario
      while(lista!=NULL) { // procedi fino a che hai nodi
        fwrite(&(lista->intervallo), sizeof(INTER), 1, fp); // cio' che scrivi e' un intervallo
        lista = lista->next;   // passa al prossimo nodo
      }
      fclose(fp);
}

/****** MAIN *******/

/* funzione principale  */
int main() {
  /* crea la lista con nodo fittizio */
  NODO lista = malloc(sizeof(struct Nodo));
  lista->next = NULL;
  /* acquisisci dati da file */
  acquisizione(lista);
  int risposta = -1;    // per interazione con l'utente
  while(risposta=!0){
     /* richiedi operazione all'utente */
     printf("Che operazione vuoi svolgere?\n");
     printf("1)-> Inserisci un intervallo in testa alla lista.\n");
     printf("2)-> Cancella l'ultimo intervallo della lista.\n");
     printf("3)-> Visualizza la lista di intervalli.\n");
     printf("4)-> Ordina la lista di intervalli.\n");
     printf("5)-> Calcola l'intersezione fra gli intervalli.\n");
     printf("0)-> Termina il programma.\n");
     scanf("%d", &risposta);
     /* gestisci le operazioni con l'utente */
     if(risposta==1) {
        inserimento(lista);
     }
     else if(risposta==2) {
        cancellazione(lista);
     }
     else if(risposta==3) {
         stampa(lista);
     }
     else if(risposta==4) {
         ordina(lista);
     }
     else if(risposta==5) {
         intersezione(lista);
     }
     else if(risposta==0) {
         printf("Adios!\n");
     }
     else printf("Selezione non valida.\n\n");
  }
  /* salva la lista sul file, ignorando il nodo fittizio */
  salvataggio(lista->next);
}
