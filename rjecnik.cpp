#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <random>
#include <queue>
#include <chrono>
#include "rjecnik.h"

using namespace std;



vector<string> UcitajRijeciIzFajla(const string& imeFajla) {
    vector<string> rijeci;
    ifstream fajl(imeFajla);

    if (!fajl) {
        throw runtime_error("Ne mogu da otvorim fajl: " + imeFajla);
    }

    string rijec;
    while (fajl >> rijec) {
        rijeci.push_back(rijec);
    }

    return rijeci;
}

bool JesuPovezane(const string& rijec1, const string& rijec2, int& trosak,
                  int trosakDodavanja, int trosakBrisanja, int trosakZamjene) {
    if (rijec1.size() == rijec2.size()) {
        int razlika = 0;
        for (size_t i = 0; i < rijec1.size(); ++i) {
            if (rijec1[i] != rijec2[i]) {
                ++razlika;
            }
        }
        if (razlika == 1) {
            trosak = trosakZamjene; // Use substitution cost
            return true;
        }
    } else if (rijec1.size() + 1 == rijec2.size()) {
        trosak = trosakDodavanja; // Use insertion cost
        return true;
    } else if (rijec1.size() == rijec2.size() + 1) {
        trosak = trosakBrisanja; // Use deletion cost
        return true;
    }
    return false;
}


vector<pair<string, string>> GenerisiRandomParove(
    const vector<string>& rijeci,
    int k,
    int broj_parova,
    int trosak_dodavanja,
    int trosak_brisanja,
    int trosak_zamjene) {

    vector<pair<string, string>> parovi;

    srand(time(0));

    while (parovi.size() < broj_parova) {
        int indeks1 = rand() % rijeci.size();
        int indeks2 = rand() % rijeci.size();

        if (indeks1 == indeks2) continue;

        int udaljenost = IzracunajUdaljenost(rijeci[indeks1], rijeci[indeks2], trosak_dodavanja, trosak_brisanja, trosak_zamjene);

        if (udaljenost <= k) {
            parovi.emplace_back(rijeci[indeks1], rijeci[indeks2]);
        }
    }

    return parovi;
}

int IzracunajUdaljenost(const string& prva, const string& druga, int dodavanje, int brisanje, int zamjena) {
    int duzina1 = prva.length();
    int duzina2 = druga.length();

    int tabela[duzina1 + 1][duzina2 + 1];  // Matrica dimenzija (duzina1+1) x (duzina2+1)

    for (int i = 0; i <= duzina1; i++) {
        tabela[i][0] = i * brisanje;
    }

    for (int j = 0; j <= duzina2; j++) {
        tabela[0][j] = j * dodavanje;
    }

    for (int i = 1; i <= duzina1; i++) {
        for (int j = 1; j <= duzina2; j++) {
            if (prva[i - 1] == druga[j - 1]) {
                tabela[i][j] = tabela[i - 1][j - 1];
            } else {
                tabela[i][j] = min({
                    tabela[i - 1][j] + brisanje,
                    tabela[i][j - 1] + dodavanje,
                    tabela[i - 1][j - 1] + zamjena
                });
            }
        }
    }

    return tabela[duzina1][duzina2];  // Vraća minimalni trošak
}

vector<string> PromjenaSaNajmanjimTroskom(
    vector<string>& rijeci,
    int pocetnaRijec,
    int krajnjaRijec,
    int trosakDodavanja,
    int trosakBrisanja,
    int trosakZamjene) {

    string prvaRijec = rijeci[pocetnaRijec];
    string drugaRijec = rijeci[krajnjaRijec];
    int duzina1 = prvaRijec.length();
    int duzina2 = drugaRijec.length();

    int tabela[duzina1 + 1][duzina2 + 1];

    // Popunjava matricu pomoću funkcije IzracunajUdaljenost
    for (int i = 0; i <= duzina1; i++) {
        for (int j = 0; j <= duzina2; j++) {
            if (i == 0) tabela[i][j] = j * trosakDodavanja;
            else if (j == 0) tabela[i][j] = i * trosakBrisanja;
            else {
                if (prvaRijec[i - 1] == drugaRijec[j - 1]) {
                    tabela[i][j] = tabela[i - 1][j - 1];
                } else {
                    tabela[i][j] = min({
                        tabela[i - 1][j] + trosakBrisanja,
                        tabela[i][j - 1] + trosakDodavanja,
                        tabela[i - 1][j - 1] + trosakZamjene
                    });
                }
            }
        }
    }

    vector<string> koraciTransformacije;
    koraciTransformacije.push_back(prvaRijec);

    int i = duzina1, j = duzina2;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && prvaRijec[i - 1] == drugaRijec[j - 1]) {
            i--;
            j--;
        } else if (i > 0 && tabela[i][j] == tabela[i - 1][j] + trosakBrisanja) {
            prvaRijec.erase(i - 1, 1);
            koraciTransformacije.push_back(prvaRijec);
            i--;
        } else if (j > 0 && tabela[i][j] == tabela[i][j - 1] + trosakDodavanja) {
            prvaRijec.insert(i, 1, drugaRijec[j - 1]);
            koraciTransformacije.push_back(prvaRijec);
            j--;
        } else {
            prvaRijec[i - 1] = drugaRijec[j - 1];
            koraciTransformacije.push_back(prvaRijec);
            i--;
            j--;
        }
    }

    reverse(koraciTransformacije.begin(), koraciTransformacije.end());
    return koraciTransformacije;
}
