#include "SlownikAVL.h"

// Konstruktor słownika opartego na tablicy mieszającej z drzewami AVL jako kubełkami
SlownikAVL::SlownikAVL(int r) : rozmiar(r) {
    // Tworzymy tablicę wskaźników do drzew AVL
    tablica.resize(rozmiar);
    for (int i = 0; i < rozmiar; ++i)
        tablica[i] = new AVLTree(); // Każdy kubełek to osobne drzewo AVL
}

// Destruktor – usuwa każde drzewo AVL w tablicy
SlownikAVL::~SlownikAVL() {
    for (int i = 0; i < rozmiar; ++i)
        delete tablica[i];
}

// Prosta funkcja haszująca – reszta z dzielenia
int SlownikAVL::hasz(int klucz) {
    return klucz % rozmiar;
}

// Wstawia parę (klucz, wartość) do odpowiedniego drzewa AVL na podstawie funkcji haszującej
void SlownikAVL::insert(int klucz, int wartosc) {
    int i = hasz(klucz);
    tablica[i]->insert(klucz, wartosc);
}

// Usuwa parę związaną z kluczem z odpowiedniego drzewa AVL
void SlownikAVL::remove(int klucz) {
    int i = hasz(klucz);
    tablica[i]->remove(klucz);
}
