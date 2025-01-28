#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Studentas {
private:
    std::string vardas;             // Studentų vardas
    std::string pavarde;            // Studentų pavardė
    std::vector<int> namu_darbai;   // Namų darbų balai
    int egzaminas;                  // Egzamino balas
    double galutinis_vidurkis;      // Galutinio balo vidurkis
    double galutinis_mediana;       // Galutinio balo mediana

public:
    // Konstruktorius ir destruktorius
    Studentas();
    ~Studentas();

    // Atsitiktinių duomenų generavimas
    void generuotiAtsitiktiniusDuomenis();

    // Galutinio balo skaičiavimo metodai
    void skaiciuotiGalutiniusBalus();
    double skaiciuotiVidurki() const; // "const" reiškia, kad metodas nekeičia objekto
    double skaiciuotiMediana() const;

    // Rezultatų išvedimas
    void spausdintiRezultata() const;

    // Nuskaitymas iš failo
    void nuskaitytiIsFailo(std::ifstream &in);

    // Pavardės gavimas (naudinga rūšiavimui)
    std::string gautiPavarde() const;
};

#endif
