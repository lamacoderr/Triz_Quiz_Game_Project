# Triz_Quiz_Game_Project
Questo e il mio applicazione personale in c++
# TriQuiz - Quiz a risposta multipla in C++

TriQuiz e' un'applicazione console scritta in C++ per gestire e giocare un quiz a risposta multipla. Il progetto usa domande divise per categoria, una classifica dei giocatori e un menu interattivo per rendere il programma piu' chiaro da usare.

---

## Descrizione

Il programma permette all'utente di giocare a un quiz scegliendo una categoria tra:

- Scienza
- Storia
- Tecnologia
- Tutte le categorie

Le domande vengono caricate da un file esterno chiamato `questions.txt`. Alla fine della partita il programma aggiorna la classifica del giocatore.

---

## Funzionalita' principali

- Menu interattivo in console
- Caricamento delle domande da file esterno
- Categorie per le domande: Scienza, Storia e Tecnologia
- Risposte multiple con opzioni A, B, C e D
- Timer di 30 secondi per ogni domanda
- Risposta corretta: **+10 punti**
- Tempo scaduto: risposta considerata sbagliata e **-5 punti**
- Il punteggio non puo' andare sotto zero
- Classifica dei giocatori salvata su file
- CRUD completo sui punteggi:
  - aggiunta punteggio
  - ricerca giocatore
  - modifica punteggio
  - eliminazione punteggio
- Ordinamento della classifica con Bubble Sort
- Ricerca di un giocatore con Binary Search
- Possibilita' di aggiungere nuove domande dal menu

---

## Argomenti di programmazione usati

Nel progetto sono stati usati diversi argomenti studiati nel primo anno di programmazione:

- `struct`
- array
- funzioni con parametri
- passaggio per riferimento
- cicli `for` e `while`
- istruzioni `if` ed `else`
- gestione dell'input utente
- file di testo con `ifstream` e `ofstream`
- Bubble Sort
- Binary Search
- numeri casuali con `rand()`
- timer con `time()`

---

## File del progetto

| File | Descrizione |
|------|-------------|
| `triquiz.cpp` | File principale con tutto il codice C++ del programma |
| `questions.txt` | File esterno che contiene le domande del quiz |
| `scores.txt` | File della classifica, creato automaticamente dal programma |

---

## Formato di questions.txt

Ogni riga e' una domanda. I campi sono separati dal carattere `|`:

```
categoria|testo domanda|opzione A|opzione B|opzione C|opzione D|risposta corretta
```

Esempio:

```
# FORMAT: category|question|A|B|C|D|correct
Science|Cosa e' H2O?|Acqua|Oro|Sale|Olio|A
History|Chi fu il primo presidente degli USA?|Lincoln|Washington|Jefferson|Adams|B
Technology|Cosa significa CPU?|Central Processing Unit|Computer Power Unit|Central Power Unit|Core Processing Unit|A
```

Le righe che iniziano con `#` vengono ignorate.

---

## Come avviare il programma

1. Scarica i file `triquiz.cpp` e `questions.txt`
2. Metti i due file nella stessa cartella
3. Compila il programma con un compilatore C++:

```
g++ triquiz.cpp -o TriQuiz
```

4. Esegui il file generato:

```
.\TriQuiz.exe
```

5. Inserisci il nome del giocatore, scegli una categoria e divertiti con il quiz!
