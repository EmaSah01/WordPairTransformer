#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "rjecnik.h"

using namespace std;

int main() {
    try {
        auto rijeci = UcitajRijeciIzFajla("words.txt");

        // Ispis broja učitanih riječi
        cout << "Ucitano je " << rijeci.size() << " rijeci iz fajla";
        cout << endl;

        int trosakDodavanja = 1;
        int trosakBrisanja = 1;
        int trosakZamjene = 1;

        int k = 6;
        int brojParova = 100;

        vector<pair<string, string>> parovi = GenerisiRandomParove(
            rijeci, k, brojParova, trosakDodavanja, trosakBrisanja, trosakZamjene);

        cout << "Generisani parovi rijeci sa putanjama transformacija za k <= " << k << ":" << endl;
        for (const auto& par : parovi) {
            int indeks_pocetne = find(rijeci.begin(), rijeci.end(), par.first) - rijeci.begin();
            int indeks_krajnje = find(rijeci.begin(), rijeci.end(), par.second) - rijeci.begin();

            auto transformacije = PromjenaSaNajmanjimTroskom(
                rijeci, indeks_pocetne, indeks_krajnje,
                trosakDodavanja, trosakBrisanja, trosakZamjene);

            for (size_t i = 0; i < transformacije.size(); ++i) {
                cout << transformacije[i];
                if (i != transformacije.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << "\n";
        }

    } catch (const exception& e) {
        cerr << "Greška: " << e.what();
    }

    return 0;
}

