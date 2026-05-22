#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

#define max_domande 100
#define max_punteggi 100
#define max_domande_partita 10

#define punti_corretta 10
#define penalita_tempo 5
#define tempo_risposta 30

struct Domanda
{
    string categoria;
    string testo;
    string A;
    string B;
    string C;
    string D;
    char corretta;
};

struct Punteggio
{
    string nome;
    int punti;
};

char maiuscola(char c)
{
    return (char)toupper((unsigned char)c);
}

bool rispostaValida(char risposta)
{
    risposta = maiuscola(risposta);

    if (risposta == 'A' || risposta == 'B' ||
        risposta == 'C' || risposta == 'D')
        return true;

    return false;
}

string nomeCategoria(string categoria)
{
    if (categoria == "Science")
        return "Scienza";
    else if (categoria == "History")
        return "Storia";
    else if (categoria == "Technology")
        return "Tecnologia";
    else
        return "Tutte";
}

bool inserisciDomanda(Domanda quiz[], int &N, string categoria, string testo,
                      string A, string B, string C, string D, char corretta)
{
    if (N >= max_domande)
        return false;

    if (categoria == "" || testo == "" || A == "" || B == "" ||
        C == "" || D == "")
        return false;

    corretta = maiuscola(corretta);

    if (!rispostaValida(corretta))
        return false;

    quiz[N].categoria = categoria;
    quiz[N].testo = testo;
    quiz[N].A = A;
    quiz[N].B = B;
    quiz[N].C = C;
    quiz[N].D = D;
    quiz[N].corretta = corretta;

    N++;
    return true;
}

int dividiRiga(string riga, string parti[])
{
    int posizione = 0;
    string parola = "";

    for (int i = 0; i < (int)riga.length(); i++)
    {
        if (riga[i] == '|')
        {
            if (posizione < 7)
                parti[posizione] = parola;

            posizione++;
            parola = "";
        }
        else
        {
            parola = parola + riga[i];
        }
    }

    if (posizione < 7)
        parti[posizione] = parola;

    return posizione + 1;
}

bool salvaDomande(Domanda quiz[], int N, string file)
{
    ofstream outFile(file);

    if (outFile.is_open())
    {
        for (int i = 0; i < N; i++)
        {
            outFile << quiz[i].categoria << "|"
                    << quiz[i].testo << "|"
                    << quiz[i].A << "|"
                    << quiz[i].B << "|"
                    << quiz[i].C << "|"
                    << quiz[i].D << "|"
                    << quiz[i].corretta << endl;
        }

        outFile.close();
        return true;
    }
    else
    {
        cout << "Impossibile aprire il file delle domande" << endl;
        return false;
    }
}

int caricaDomande(Domanda quiz[], int &N, string file)
{
    ifstream inFile(file);
    N = 0;

    string riga;
    string parti[7];
    int ret;
    int err = 0;

    if (inFile.is_open())
    {
        while (getline(inFile, riga))
        {
            if (riga == "" || riga[0] == '#')
                continue;

            if (riga[riga.length() - 1] == '\r')
                riga.erase(riga.length() - 1);

            int quanti = dividiRiga(riga, parti);

            if (quanti == 7)
            {
                ret = inserisciDomanda(quiz, N, parti[0], parti[1], parti[2],
                                       parti[3], parti[4], parti[5],
                                       parti[6][0]);

                if (ret != 1)
                    err++;
            }
            else
            {
                err++;
            }
        }

        if (err > 0)
            cout << "Domande caricate con " << err << " errori" << endl;

        inFile.close();
        return N;
    }
    else
    {
        cout << "Impossibile aprire il file delle domande" << endl;
        return -1;
    }
}

void visualizzaDomande(Domanda quiz[], int N)
{
    if (N == 0)
    {
        cout << "Nessuna domanda presente" << endl;
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            cout << i + 1 << ") "
                 << quiz[i].categoria << " - "
                 << quiz[i].testo << " - Corretta: "
                 << quiz[i].corretta << endl;
        }
    }
}

bool trovaCategoria(Domanda quiz[], int N, string categoria)
{
    for (int i = 0; i < N; i++)
    {
        if (quiz[i].categoria == categoria)
            return true;
    }

    return false;
}

bool inserisciPunteggio(Punteggio classifica[], int &N, string nome, int punti)
{
    if (N >= max_punteggi)
        return false;

    classifica[N].nome = nome;
    classifica[N].punti = punti;

    N++;
    return true;
}

bool salvaPunteggi(Punteggio classifica[], int N, string file)
{
    ofstream outFile(file);

    if (outFile.is_open())
    {
        for (int i = 0; i < N; i++)
        {
            outFile << classifica[i].nome << " "
                    << classifica[i].punti << endl;
        }

        outFile.close();
        return true;
    }
    else
    {
        cout << "Impossibile aprire il file dei punteggi" << endl;
        return false;
    }
}

int caricaPunteggi(Punteggio classifica[], int &N, string file)
{
    ifstream inFile(file);
    N = 0;

    string nome;
    int punti;

    int ret;
    int err = 0;

    if (inFile.is_open())
    {
        while (inFile >> nome >> punti)
        {
            ret = inserisciPunteggio(classifica, N, nome, punti);

            if (ret != 1)
                err++;
        }

        if (err > 0)
            cout << "Classifica caricata con " << err << " errori" << endl;

        inFile.close();
        return N;
    }
    else
    {
        return 0;
    }
}

void scambiaPunteggi(Punteggio &a, Punteggio &b)
{
    Punteggio temp = a;
    a = b;
    b = temp;
}

void ordinaPerPunti(Punteggio classifica[], int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (classifica[j].punti < classifica[j + 1].punti)
                scambiaPunteggi(classifica[j], classifica[j + 1]);
        }
    }
}

void ordinaPerNome(Punteggio classifica[], int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (classifica[j].nome > classifica[j + 1].nome)
                scambiaPunteggi(classifica[j], classifica[j + 1]);
        }
    }
}

int cercaGiocatoreBinaria(Punteggio classifica[], int N, string nome)
{
    int sinistra = 0;
    int destra = N - 1;

    while (sinistra <= destra)
    {
        int centro = (sinistra + destra) / 2;

        if (classifica[centro].nome == nome)
            return centro;
        else if (classifica[centro].nome < nome)
            sinistra = centro + 1;
        else
            destra = centro - 1;
    }

    return -1;
}

void visualizzaClassifica(Punteggio classifica[], int N)
{
    if (N == 0)
    {
        cout << "Classifica vuota" << endl;
    }
    else
    {
        ordinaPerPunti(classifica, N);

        for (int i = 0; i < N; i++)
        {
            cout << i + 1 << ") "
                 << classifica[i].nome << " "
                 << classifica[i].punti << endl;
        }
    }
}

bool modificaPunteggio(Punteggio classifica[], int N, string nome, int nuoviPunti)
{
    ordinaPerNome(classifica, N);

    int pos = cercaGiocatoreBinaria(classifica, N, nome);

    if (pos == -1)
        return false;

    classifica[pos].punti = nuoviPunti;
    return true;
}

bool cancellaPunteggio(Punteggio classifica[], int &N, string nome)
{
    ordinaPerNome(classifica, N);

    int pos = cercaGiocatoreBinaria(classifica, N, nome);

    if (pos == -1)
        return false;

    for (int i = pos; i < N - 1; i++)
        classifica[i] = classifica[i + 1];

    N--;
    return true;
}

void salvaRisultato(Punteggio classifica[], int &N, string nome, int punti)
{
    ordinaPerNome(classifica, N);

    int pos = cercaGiocatoreBinaria(classifica, N, nome);

    if (pos == -1)
    {
        if (inserisciPunteggio(classifica, N, nome, punti))
            cout << "Punteggio salvato" << endl;
        else
            cout << "Classifica piena" << endl;
    }
    else
    {
        if (punti > classifica[pos].punti)
        {
            classifica[pos].punti = punti;
            cout << "Nuovo record salvato" << endl;
        }
        else
        {
            cout << "Il vecchio record resta: "
                 << classifica[pos].punti << endl;
        }
    }

    ordinaPerPunti(classifica, N);
    salvaPunteggi(classifica, N, "scores.txt");
}

string scegliCategoria()
{
    char scelta;

    cout << "\nScegli categoria" << endl;
    cout << "A Scienza" << endl;
    cout << "B Storia" << endl;
    cout << "C Tecnologia" << endl;
    cout << "D Tutte" << endl;
    cin >> scelta;

    scelta = maiuscola(scelta);

    if (scelta == 'A')
        return "Science";
    else if (scelta == 'B')
        return "History";
    else if (scelta == 'C')
        return "Technology";
    else
        return "ALL";
}

void stampaDomanda(Domanda d, int numero, int totale)
{
    cout << "\nDomanda " << numero << " di " << totale << endl;
    cout << d.testo << endl;
    cout << "A) " << d.A << endl;
    cout << "B) " << d.B << endl;
    cout << "C) " << d.C << endl;
    cout << "D) " << d.D << endl;
}

void mescolaIndici(int v[], int N)
{
    for (int i = N - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

bool leggiRispostaConTempo(char &risposta)
{
    time_t inizio = time(NULL);

    cout << "Risposta: ";
    cin >> risposta;

    risposta = maiuscola(risposta);

    int secondi = (int)(time(NULL) - inizio);

    if (secondi > tempo_risposta)
        return false;

    return true;
}

void giocaQuiz(Domanda quiz[], int N, Punteggio classifica[], int &NP)
{
    string nome;
    string categoria;
    int indici[max_domande];
    int trovate = 0;
    int punti = 0;

    cout << "\nNome giocatore: ";
    cin >> nome;

    categoria = scegliCategoria();

    for (int i = 0; i < N; i++)
    {
        if (categoria == "ALL" || quiz[i].categoria == categoria)
        {
            indici[trovate] = i;
            trovate++;
        }
    }

    if (trovate == 0)
    {
        cout << "Nessuna domanda trovata" << endl;
        return;
    }

    mescolaIndici(indici, trovate);

    int daFare = trovate;

    if (daFare > max_domande_partita)
        daFare = max_domande_partita;

    cout << "\nInizio quiz" << endl;
    cout << "Categoria: " << nomeCategoria(categoria) << endl;
    cout << "Domande: " << daFare << endl;
    cout << "Tempo per domanda: " << tempo_risposta << " secondi" << endl;

    for (int i = 0; i < daFare; i++)
    {
        int pos = indici[i];
        char risposta;

        stampaDomanda(quiz[pos], i + 1, daFare);

        bool inTempo = leggiRispostaConTempo(risposta);

        if (inTempo == false)
        {
            punti = punti - penalita_tempo;

            if (punti < 0)
                punti = 0;

            cout << "Tempo scaduto" << endl;
            cout << "Risposta corretta: " << quiz[pos].corretta << endl;
        }
        else if (risposta == quiz[pos].corretta)
        {
            punti = punti + punti_corretta;
            cout << "Corretta" << endl;
        }
        else
        {
            cout << "Sbagliata" << endl;
            cout << "Risposta corretta: " << quiz[pos].corretta << endl;
        }

        cout << "Punti attuali: " << punti << endl;
    }

    cout << "\nPunteggio finale di " << nome << ": "
         << punti << endl;

    salvaRisultato(classifica, NP, nome, punti);
}

void aggiungiDomandaDaTastiera(Domanda quiz[], int &N)
{
    string categoria;
    string testo;
    string A;
    string B;
    string C;
    string D;
    char corretta;
    char scelta;

    cout << "\nCategoria:" << endl;
    cout << "A Scienza" << endl;
    cout << "B Storia" << endl;
    cout << "C Tecnologia" << endl;
    cin >> scelta;

    scelta = maiuscola(scelta);

    if (scelta == 'A')
        categoria = "Science";
    else if (scelta == 'B')
        categoria = "History";
    else
        categoria = "Technology";

    cin.ignore(10000, '\n');

    cout << "Testo domanda: ";
    getline(cin, testo);

    cout << "Opzione A: ";
    getline(cin, A);

    cout << "Opzione B: ";
    getline(cin, B);

    cout << "Opzione C: ";
    getline(cin, C);

    cout << "Opzione D: ";
    getline(cin, D);

    cout << "Risposta corretta: ";
    cin >> corretta;

    if (inserisciDomanda(quiz, N, categoria, testo, A, B, C, D, corretta))
    {
        salvaDomande(quiz, N, "questions.txt");
        cout << "Domanda inserita" << endl;
    }
    else
    {
        cout << "Domanda non inserita" << endl;
    }
}

int main()
{
    Domanda quiz[max_domande];
    Punteggio classifica[max_punteggi];

    int N = 0;
    int NP = 0;
    int scelta;

    srand((unsigned int)time(NULL));

    cout << "===== TRIQUIZ =====" << endl;

    int resDomande = caricaDomande(quiz, N, "questions.txt");

    if (resDomande == -1)
    {
        cout << "Errore file domande" << endl;
        return 0;
    }

    caricaPunteggi(classifica, NP, "scores.txt");

    cout << "Domande caricate: " << N << endl;
    cout << "Punteggi caricati: " << NP << endl;

    do
    {
        cout << "\n===== MENU =====" << endl;
        cout << "1 Gioca" << endl;
        cout << "2 Visualizza classifica" << endl;
        cout << "3 Cerca giocatore" << endl;
        cout << "4 Inserisci punteggio" << endl;
        cout << "5 Modifica punteggio" << endl;
        cout << "6 Cancella punteggio" << endl;
        cout << "7 Aggiungi domanda" << endl;
        cout << "8 Visualizza domande" << endl;
        cout << "9 Salva tutto" << endl;
        cout << "10 Esci" << endl;
        cin >> scelta;

        if (scelta == 1)
        {
            giocaQuiz(quiz, N, classifica, NP);
        }

        else if (scelta == 2)
        {
            visualizzaClassifica(classifica, NP);
        }

        else if (scelta == 3)
        {
            string nome;

            cout << "Nome: ";
            cin >> nome;

            ordinaPerNome(classifica, NP);

            int pos = cercaGiocatoreBinaria(classifica, NP, nome);

            if (pos == -1)
                cout << "Non trovato" << endl;
            else
                cout << classifica[pos].nome << " "
                     << classifica[pos].punti << endl;
        }

        else if (scelta == 4)
        {
            string nome;
            int punti;

            cout << "Nome: ";
            cin >> nome;
            cout << "Punti: ";
            cin >> punti;

            if (inserisciPunteggio(classifica, NP, nome, punti))
            {
                salvaPunteggi(classifica, NP, "scores.txt");
                cout << "Inserito" << endl;
            }
            else
            {
                cout << "Classifica piena" << endl;
            }
        }

        else if (scelta == 5)
        {
            string nome;
            int punti;

            cout << "Nome: ";
            cin >> nome;
            cout << "Nuovi punti: ";
            cin >> punti;

            if (modificaPunteggio(classifica, NP, nome, punti))
            {
                salvaPunteggi(classifica, NP, "scores.txt");
                cout << "Modificato" << endl;
            }
            else
            {
                cout << "Non trovato" << endl;
            }
        }

        else if (scelta == 6)
        {
            string nome;

            cout << "Nome: ";
            cin >> nome;

            if (cancellaPunteggio(classifica, NP, nome))
            {
                salvaPunteggi(classifica, NP, "scores.txt");
                cout << "Cancellato" << endl;
            }
            else
            {
                cout << "Non trovato" << endl;
            }
        }

        else if (scelta == 7)
        {
            aggiungiDomandaDaTastiera(quiz, N);
        }

        else if (scelta == 8)
        {
            visualizzaDomande(quiz, N);
        }

        else if (scelta == 9)
        {
            bool ok1 = salvaDomande(quiz, N, "questions.txt");
            bool ok2 = salvaPunteggi(classifica, NP, "scores.txt");

            if (ok1 && ok2)
                cout << "Salvato tutto" << endl;
            else
                cout << "Errore salvataggio" << endl;
        }

        else if (scelta == 10)
        {
            cout << "Ciao" << endl;
        }

        else
        {
            cout << "Scelta non valida" << endl;
        }

    } while (scelta != 10);

    return 0;
}