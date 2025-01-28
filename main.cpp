#include "Studentas.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Rūšiuoti pagal pavardę
bool lygintiPavarde(const Studentas &a, const Studentas &b) {
    return a.gautiPavarde() < b.gautiPavarde();
}

// Generuoti atsitiktinius studentus
void generuotiStudentus(vector<Studentas> &studentai, int kiekis) {
    for (int i = 0; i < kiekis; ++i) {
        Studentas studentas;
        studentas.generuotiAtsitiktiniusDuomenis();
        studentas.skaiciuotiGalutiniusBalus();
        studentai.push_back(studentas);
    }
}

// Nuskaityti studentus iš failo
void nuskaitytiIsFailo(vector<Studentas> &studentai, const string &failoPavadinimas) {
    ifstream in(failoPavadinimas);
    if (!in) throw runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);

    while (true) {
        Studentas studentas;
        try {
            studentas.nuskaitytiIsFailo(in);
        } catch (const exception &e) {
            if (in.eof()) break; // Pasiekta failo pabaiga
            throw runtime_error("Klaida skaitant failą: " + string(e.what()));
        }
        studentai.push_back(studentas);
    }

    in.close();
}

// Spausdinti studentų rezultatus
void spausdintiStudentus(const vector<Studentas> &studentai) {
    cout << left << setw(15) << "Pavardė" 
         << setw(15) << "Vardas" 
         << setw(20) << "Galutinis (Vid.)" 
         << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(70, '-') << endl;

    for (const auto &studentas : studentai) {
        studentas.spausdintiRezultata();
    }
}

int main() {
    vector<Studentas> studentai;
    char pasirinkimas;

    cout << "Norite generuoti atsitiktinius duomenis (g) ar nuskaityti iš failo (f)? (g/f): ";
    cin >> pasirinkimas;

    try {
        if (pasirinkimas == 'g') {
            int studentuSkaicius;
            cout << "Įveskite studentų skaičių: ";
            cin >> studentuSkaicius;
            generuotiStudentus(studentai, studentuSkaicius);
        } else if (pasirinkimas == 'f') {
            string failoPavadinimas = "kursiokai.txt";
            cout << "Įveskite failo pavadinimą (default: kursiokai.txt): ";
            cin.ignore();
            getline(cin, failoPavadinimas);
            nuskaitytiIsFailo(studentai, failoPavadinimas);
        } else {
            throw runtime_error("Neteisingas pasirinkimas. Naudokite 'g' arba 'f'.");
        }

        // Surūšiuoti pagal pavardę
        sort(studentai.begin(), studentai.end(), lygintiPavarde);

        // Spausdinti rezultatus
        spausdintiStudentus(studentai);

    } catch (const exception &e) {
        cerr << "Klaida: " << e.what() << endl;
    }

    return 0;
}
