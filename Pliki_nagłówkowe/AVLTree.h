#pragma once
#include "AVLNode.h"

class AVLTree {
private:
    AVLNode* korzen;

    int wysokosc(AVLNode* n);
    int balans(AVLNode* n);
    void aktualizujWysokosc(AVLNode* n);
    AVLNode* rotacjaWPrawo(AVLNode* y);
    AVLNode* rotacjaWLewo(AVLNode* x);
    AVLNode* wstaw(AVLNode* node, int klucz, int wartosc);
    AVLNode* usun(AVLNode* node, int klucz);
    AVLNode* minWartosc(AVLNode* node);
    void usunDrzewo(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();
    void insert(int klucz, int wartosc);
    void remove(int klucz);
};
