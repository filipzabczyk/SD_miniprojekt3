#pragma once
#include <vector>
#include "Lista.h"

class SlownikZamknieteAdresowanie {
private:
    std::vector<Lista*> tablica;
    int rozmiar;

    int hasz(int klucz);

public:
    SlownikZamknieteAdresowanie(int r = 1031);
    ~SlownikZamknieteAdresowanie();

    void insert(int klucz, int wartosc);
    void remove(int klucz);
};
