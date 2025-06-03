#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include "SlownikOtwarteAdresowanie.h"
#include "SlownikZamknieteAdresowanie.h"
#include "SlownikAVL.h"

using namespace std;
using namespace chrono;

// Funkcja generująca wektor unikalnych par (klucz, wartość) o zadanym rozmiarze
vector<pair<int, int>> generuj_dane(int rozmiar) {
    unordered_set<int> unikalne;
    vector<pair<int, int>> dane;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10 * rozmiar); // Szerszy zakres niż liczba danych

    // Losowanie unikalnych kluczy z wartościami
    while ((int)dane.size() < rozmiar) {
        int klucz = dis(gen);
        if (unikalne.insert(klucz).second) {
            int wartosc = dis(gen);
            dane.emplace_back(klucz, wartosc);
        }
    }
    return dane;
}

// Funkcja zapisująca wynik pomiaru czasu do pliku CSV
void zapisz_csv(ofstream& plik, int rozmiar, const string& operacja, long long czas_ns) {
    plik << rozmiar << ";" << operacja << ";" << czas_ns << "\n";
}

int main() {
    ofstream plik("wyniki.csv");
    plik << "Rozmiar;Struktura;Operacja;Czas[ns]\n";

    const int powtorzenia = 100; // Liczba powtórzeń dla uśrednienia pomiarów

    // Główna pętla testowa dla różnych rozmiarów danych
    for (int rozmiar = 10000; rozmiar <= 100000; rozmiar += 10000) {
        vector<pair<int, int>> dane = generuj_dane(rozmiar); // Generacja danych

        // Pomiar insert
        for (const string& nazwa : { "AVL", "Zamkniete", "Otwarte" }) {
            long long czas_suma = 0;

            for (int p = 0; p < powtorzenia; ++p) {
                if (nazwa == "AVL") {
                    SlownikAVL slownik;
                    auto start = high_resolution_clock::now();
                    for (const auto& par : dane)
                        slownik.insert(par.first, par.second);
                    auto end = high_resolution_clock::now();
                    czas_suma += duration_cast<nanoseconds>(end - start).count();
                }
                else if (nazwa == "Zamkniete") {
                    SlownikZamknieteAdresowanie slownik;
                    auto start = high_resolution_clock::now();
                    for (const auto& par : dane)
                        slownik.insert(par.first, par.second);
                    auto end = high_resolution_clock::now();
                    czas_suma += duration_cast<nanoseconds>(end - start).count();
                }
                else { // Otwarte adresowanie
                    SlownikOtwarteAdresowanie slownik(2 * rozmiar); // Zapobieganie pełnej tablicy
                    auto start = high_resolution_clock::now();
                    for (const auto& par : dane)
                        slownik.insert(par.first, par.second);
                    auto end = high_resolution_clock::now();
                    czas_suma += duration_cast<nanoseconds>(end - start).count();
                }
            }
            zapisz_csv(plik, rozmiar, nazwa + ";insert", czas_suma / powtorzenia);
        }

        // Pomiar remove
        for (const string& nazwa : { "AVL", "Zamkniete", "Otwarte" }) {
            long long czas_suma = 0;

            if (nazwa == "AVL") {
                SlownikAVL slownik;
                for (const auto& par : dane)
                    slownik.insert(par.first, par.second); // Wypełnienie przed usuwaniem

                for (int p = 0; p < powtorzenia; ++p) {
                    auto start = high_resolution_clock::now();
                    for (const auto& par : dane)
                        slownik.remove(par.first);
                    auto end = high_resolution_clock::now();
                    czas_suma += duration_cast<nanoseconds>(end - start).count();

                    // Odtwarzanie danych po każdym usunięciu
                    for (const auto& par : dane)
                        slownik.insert(par.first, par.second);
                }
                zapisz_csv(plik, rozmiar, nazwa + ";remove", czas_suma / powtorzenia);
            }
            else if (nazwa == "Zamkniete") {
                SlownikZamknieteAdresowanie slownik;
                for (const auto& par : dane)
                    slownik.insert(par.first, par.second);

                for (int p = 0; p < powtorzenia; ++p) {
                    auto start = high_resolution_clock::now();
                    for (const auto& par : dane)
                        slownik.remove(par.first);
                    auto end = high_resolution_clock::now();
                    czas_suma += duration_cast<nanoseconds>(end - start).count();

                    for (const auto& par : dane)
                        slownik.insert(par.first, par.second);
                }
                zapisz_csv(plik, rozmiar, nazwa + ";remove", czas_suma / powtorzenia);
            }
            else { // Otwarte adresowanie
                SlownikOtwarteAdresowanie slownik(2 * rozmiar);
                for (const auto& par : dane)
                    slownik.insert(par.first, par.second);

                for (int p = 0; p < powtorzenia; ++p) {
                    auto start = high_resolution_clock::now();
                    for (const auto& par : dane)
                        slownik.remove(par.first);
                    auto end = high_resolution_clock::now();
                    czas_suma += duration_cast<nanoseconds>(end - start).count();

                    for (const auto& par : dane)
                        slownik.insert(par.first, par.second);
                }
                zapisz_csv(plik, rozmiar, nazwa + ";remove", czas_suma / powtorzenia);
            }
        }
    }

    plik.close();
    cout << "Pomiar zakonczony. Wyniki zapisane do pliku 'wyniki.csv'\n";
    return 0;
}
