#pragma once

// Struktura przechowująca wpis w tablicy mieszającej z adresowaniem otwartym.
struct Para {
    int klucz;
    int wartosc;
    bool aktywna; // Określa czy para jest aktualnie używana
    bool usunieta; // Pozwala rozróżnić czy dane pole było kiedyś zajęte i zostało usunięte

    Para() : klucz(0), wartosc(0), aktywna(false), usunieta(false) {}
};
