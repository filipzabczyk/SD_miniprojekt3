#include "SlownikZamknieteAdresowanie.h"

// Konstruktor – tworzy tablicę list o zadanym rozmiarze (domyślnie łańcuchowa metoda obsługi kolizji)
SlownikZamknieteAdresowanie::SlownikZamknieteAdresowanie(int r) : rozmiar(r) {
    // Inicjalizacja tablicy wskaźników do list
    tablica.resize(rozmiar);
    for (int i = 0; i < rozmiar; ++i)
        tablica[i] = new Lista();  // Każdy kubełek to osobna lista jednokierunkowa
}

// Destruktor – zwalnia pamięć zajmowaną przez listy
SlownikZamknieteAdresowanie::~SlownikZamknieteAdresowanie() {
    for (int i = 0; i < rozmiar; ++i)
        delete tablica[i];
}

// Funkcja mieszająca – oblicza indeks na podstawie klucza (modulo rozmiar)
int SlownikZamknieteAdresowanie::hasz(int klucz) {
    return klucz % rozmiar;
}

// Wstawienie pary (klucz, wartość) do odpowiedniego kubełka (listy)
void SlownikZamknieteAdresowanie::insert(int klucz, int wartosc) {
    int i = hasz(klucz);                 // Wyznacz indeks kubełka
    tablica[i]->insert(klucz, wartosc); // Wstaw do listy
}

// Usunięcie elementu o podanym kluczu z odpowiedniego kubełka (listy)
void SlownikZamknieteAdresowanie::remove(int klucz) {
    int i = hasz(klucz);               // Wyznacz indeks kubełka
    tablica[i]->remove(klucz);        // Usuń z listy
}
