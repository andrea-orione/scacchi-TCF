## SCACCHI 1 vs 1 <br/> Tema d'esame per il corso di Tecniche di calcolo per la fisica
Università di Torino <br/> A.A. 2023/2024 <br/> Marchetti Luca, Orione Andrea, Pusterla Paolo

<br/>

## INTRODUZIONE
Questo progetto ha lo scopo di generare un programma che permetta di giocare a scacchi. In particolare, si vuole progettare un programma che, dati due giocatori, dia la possibilità di:

1. scegliere il colore tra: *casuale*, *bianco* o *nero*;
2. visualizzare nel terminale lo stato attuale della scacchiera;
3. effettuare una mossa;
4. valutare lo stato del gioco, per verificare se la partita è finita.

<br/>

L'esecuzione della mossa consiste nei seguenti passi:

1. prendere in input una mossa in notazione standard FIDE;
2. controllare che notazione della mossa indicata sia valida;
3. controllare che la mossa indicata sia realizzabile; 
3. eseguire la mossa;
4. valutare il nuovo stato della partita, controllando se è: *stallo*, *scacco matto*, *patta per ripetizione* o *patta per mancanza di pezzi*.

<br/>

## COME COMPILARLO ED UTILIZZARLO (MacOs o Linux)
Una volta scaricata ed installata una versione di CMake superiore a 3.26, seguire i seguenti passaggi:

1. Clonare la repository sul proprio computer.
2. Navigare da terminale fino alla directory dove è stato clonato il progetto.
3. Creare una nuova directory *build*, scrivendo:
   ```bash
   mkdir build
   ```
4. Navigare dentro la directory appena creata e generare i *build files*:
   ```bash
   cmake ..
   ```
5. Compilare il progetto:
   ```bash
   make -j N
   ```
   dove N va sostituito con il numero di threads che si vogliono utilizzare (scrivere solo ```make``` per usare un solo thread).
6. Eseguire l'eseguibile ottenuto:
   ```bash
   ./scacchi
   ```



