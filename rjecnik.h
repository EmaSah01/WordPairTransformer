#ifndef RJECNIK_H
#define RJECNIK_H

#include <string>
#include <vector>
#include <utility>

std::vector<std::string> UcitajRijeciIzFajla(const std::string& imeFajla);

bool JesuPovezane(const std::string& rijec1, const std::string& rijec2, int& trosak,
                  int trosakDodavanja, int trosakBrisanja, int trosakZamjene);

std::vector<std::pair<std::string, std::string>> GenerisiRandomParove(
    const std::vector<std::string>& rijeci,
    int k,
    int broj_parova,
    int trosak_dodavanja,
    int trosak_brisanja,
    int trosak_zamjene);

std::vector<std::string> PromjenaSaNajmanjimTroskom(
    std::vector<std::string>& rijeci,
    int indeks_pocetne,
    int indeks_krajnje,
    int trosak_dodavanja,
    int trosak_brisanja,
    int trosak_zamjene);

int IzracunajUdaljenost(
    const std::string& word1,
    const std::string& word2,
    int trosak_dodavanja,
    int trosak_brisanja,
    int trosak_zamjene);

#endif // RJECNIK_H

