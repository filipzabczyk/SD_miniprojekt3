#pragma once

struct Wezel {
    int klucz;
    int wartosc;
    Wezel* nastepny;

    Wezel(int k, int v) : klucz(k), wartosc(v), nastepny(nullptr) {}
};

class Lista {
private:
    Wezel* glowa;

public:
    Lista();
    ~Lista();

    void insert(int klucz, int wartosc);
    void remove(int klucz);
};
