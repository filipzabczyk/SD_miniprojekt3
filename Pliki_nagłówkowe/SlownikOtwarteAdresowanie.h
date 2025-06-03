#pragma once
#include "Para.h"

class SlownikOtwarteAdresowanie {
private:
    Para* tablica;
    int rozmiar;
    int liczbaElementow;

    int hasz(int klucz, int i);

public:
    SlownikOtwarteAdresowanie(int r = 1031);
    ~SlownikOtwarteAdresowanie();

    void insert(int klucz, int wartosc);
    void remove(int klucz);
};
