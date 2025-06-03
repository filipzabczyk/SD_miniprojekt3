#include "SlownikOtwarteAdresowanie.h"
#include <iostream>

// Konstruktor – tworzy tablicę o podanym rozmiarze i ustawia licznik elementów na 0
SlownikOtwarteAdresowanie::SlownikOtwarteAdresowanie(int r)
    : rozmiar(r), liczbaElementow(0) {
    tablica = new Para[rozmiar]; // Dynamiczna alokacja tablicy struktur Para
}

// Destruktor – zwalnia zaalokowaną pamięć
SlownikOtwarteAdresowanie::~SlownikOtwarteAdresowanie() {
    delete[] tablica;
}

// Funkcja haszująca z liniowym sondowaniem: (h(k) + i) mod rozmiar
int SlownikOtwarteAdresowanie::hasz(int klucz, int i) {
    return (klucz % rozmiar + i) % rozmiar;
}

// Wstawianie pary (klucz, wartość) do tablicy
void SlownikOtwarteAdresowanie::insert(int klucz, int wartosc) {
    for (int i = 0; i < rozmiar; ++i) {
        int indeks = hasz(klucz, i);

        // Wstaw jeśli pole jest wolne, usunięte lub nadpisujemy istniejący klucz
        if (!tablica[indeks].aktywna || tablica[indeks].usunieta || tablica[indeks].klucz == klucz) {
            tablica[indeks].klucz = klucz;
            tablica[indeks].wartosc = wartosc;
            tablica[indeks].aktywna = true;
            tablica[indeks].usunieta = false;
            ++liczbaElementow;
            return;
        }
    }
    // Komunikat błędu, jeśli nie udało się znaleźć wolnego miejsca
    std::cerr << "Błąd: tablica pełna przy wstawianiu klucza " << klucz << std::endl;
}

// Usuwanie pary na podstawie klucza
void SlownikOtwarteAdresowanie::remove(int klucz) {
    for (int i = 0; i < rozmiar; ++i) {
        int indeks = hasz(klucz, i);

        // Znaleziono aktywny wpis z pasującym kluczem – oznacz jako usunięty
        if (tablica[indeks].aktywna && tablica[indeks].klucz == klucz) {
            tablica[indeks].aktywna = false;
            tablica[indeks].usunieta = true;
            --liczbaElementow;
            return;
        }
        // Przerywamy przeszukiwanie, jeśli trafimy na wolne, nigdy nieużywane pole
        else if (!tablica[indeks].aktywna && !tablica[indeks].usunieta) {
            return;
        }
    }
}
