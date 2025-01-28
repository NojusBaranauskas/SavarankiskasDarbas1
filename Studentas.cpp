#include "Studentas.h"
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <stdexcept>
#include <iostream>

using namespace std;

// Konstruktorius
Studentas::Studentas() 
    : vardas(""), pavarde(""), egzaminas(0), galutinis_vidurkis(0.0), galutinis_mediana(0.0) {}

// Destruktorius
Studentas::~Studentas() {}

// Generuoti atsitiktinius studento duomenis
void Studentas::generuotiAtsitiktiniusDuomenis() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    cout << "Įveskite studento vardą: ";
    cin >> vardas;
    cout << "Įveskite studento pavardę: ";
    cin >> pavarde;

    namu_darbai.clear();
    for (int i = 0; i < 5; ++i) {
        namu_darbai.push_back(dist(gen)); // Atsitiktiniai namų darbų balai
    }
    egzaminas = dist(gen); // Atsitiktinis egzamino balas
}

// Skaičiuoti galutinius balus (vidurkį ir medianą)
void Studentas::skaiciuotiGalutiniusBalus() {
    galutinis_vidurkis = skaiciuotiVidurki();
    galutinis_mediana = skaiciuotiMediana();
}

// Skaičiuoti galutinį balą pagal vidurkį
double Studentas::skaiciuotiVidurki() {
    if (namu_darbai.empty()) throw runtime_error("Nėra namų darbų balų");
    double vidurkis = accumulate(namu_darbai.begin(), namu_darbai.end(), 0.0) / namu_darbai.size();
    return 0.4 * vidurkis + 0.6 * egzaminas;
}

// Skaičiuoti galutinį balą pagal medianą
double Studentas::skaiciuotiMediana() {
    if (namu_darbai.empty()) throw runtime_error("Nėra namų darbų balų");

    vector<int> kopija = namu_darbai; // Kopijuoti, kad nepakeistume originalių duomenų
    size_t size = kopija.size();

    nth_element(kopija.begin(), kopija.begin() + size / 2, kopija.end());
    double mediana = kopija[size / 2];
    if (size % 2 == 0) {
        nth_element(kopija.begin(), kopija.begin() + size / 2 - 1, kopija.end());
        mediana = (mediana + kopija[size / 2 - 1]) / 2.0;
    }
    return 0.4 * mediana + 0.6 * egzaminas;
}

// Spausdinti studento rezultatus
void Studentas::spausdintiRezultata() const {
    cout << left << setw(15) << pavarde 
         << setw(15) << vardas
         << setw(20) << fixed << setprecision(2) << galutinis_vidurkis
         << setw(20) << fixed << setprecision(2) << galutinis_mediana << endl;
}

// Skaityti studentą iš failo
void Studentas::nuskaitytiIsFailo(ifstream &in) {
    in >> pavarde >> vardas;
    namu_darbai.resize(5);
    for (int &nd : namu_darbai) {
        if (!(in >> nd)) throw runtime_error("Neteisingi namų darbų duomenys faile.");
    }
    if (!(in >> egzaminas)) throw runtime_error("Neteisingi egzamino duomenys faile.");
    skaiciuotiGalutiniusBalus();
}

// Gauti pavardę
std::string Studentas::gautiPavarde() const {
    return pavarde;
}
