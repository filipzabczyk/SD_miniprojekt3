#pragma once
#include <vector>
#include "AVLTree.h"

class SlownikAVL {
private:
    std::vector<AVLTree*> tablica;
    int rozmiar;

    int hasz(int klucz);

public:
    SlownikAVL(int r = 1031);
    ~SlownikAVL();

    void insert(int klucz, int wartosc);
    void remove(int klucz);
};
