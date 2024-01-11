## SCACCHI 1 vs 1 <br/> Tema d'esame per il corso di Tecniche di calcolo per la fisica
Università di Torino <br/> A.A. 2023/2024 <br/> Marchetti Luca, Orione Andrea, Pusterla Paolo

<br/>

## INTRODUZIONE
Questo progetto ha lo scopo di creare un programma che permetta di giocare a scacchi. In particolare, si vuole progettare un programma che, dati due giocatori, dia la possibilità di:

1. visualizzare nel terminale lo stato attuale della scacchiera;
2. effettuare una mossa;
3. valutare lo stato del gioco, per verificare se la partita è finita;
4. cambiare il modo di visualizzazione tra le seguenti possibilità
    - *normale*: utilizzando caratteri ASCII
    - *semplificata*: utilizzando solo lettere e caratteri della tastiera
    - *colorata*: utilizzando stringhe ANSI per cambiare il colore di sfondo dei caratteri
      in modo da avere una scacchiera colorata
    - *invertita*: con lo stesso settaggio della normale ma con i colori invertiti (adatta
      a terminali con sfondo chiaro)

<br/>

L'esecuzione della mossa consiste nei seguenti passi:

1. prendere in input una mossa in notazione UCI (Universal Chess Interface);
2. controllare che la notazione della mossa indicata sia valida;
3. controllare che la mossa indicata sia realizzabile; 
3. eseguire la mossa;
4. valutare il nuovo stato della partita, controllando se è: *scacco matto*, *stallo*, *patta per ripetizione* o *patta per mancanza di pezzi*.

<br/>

La notazione UCI è costruita nel modo seguente:
 - Indicare la casella di partenza con lettera e numero (da a1 a h8) e la casella di arrivo nello stesso modo,
     in una stringa senza spazi. L'arrocco e la cattura seguono la stessa formattazione
 - Per la promozione apporre alla stringa indicata sopra il carattere corrispondente al tipo di pezzo in cui si
     vuole promuovere (i caratteri validi sono /r/, /n/, /b/, /q/ in maiuscolo o minuscolo)

Esempi di notazione valida sono i seguenti:
 - e2e4
 - e1g1 (per l'arrocco di re del bianco)
 - b7b8Q (per la promozione del pedone bianco in regina)

<br/>

## COME COMPILARE ED ESEGUIRE
Innanzitutto è necessario assicurarsi di avere una versione di CMake superiore a 3.26 installata e funzionante sul proprio computer. Si noti che è possibile abbassare la versione minima di CMake richiesta modificando il file *CMakeLists.txt*. 

### MacOS e Linux

Seguire i passaggi elencati.

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
5. Compilare e linkare il progetto:
   ```bash
   make -j N
   ```
   dove N va sostituito con il numero di threads che si vogliono utilizzare (scrivere solamente ```make``` per usare un solo thread).
6. Eseguire l'eseguibile generato da CMake:
   ```bash
   ./scacchi
   ```
<br/>

## Diagrammi UML
Per vedere lo Use Case Diagram, il Class Diagram ed i diagrammi di flusso in versione originale, scaricare UMLet ed aprire i file *.uxf* con tale applicazione.
In alternativa, una versione in formato *.pdf* è disponibile nella cartella **UML**.

