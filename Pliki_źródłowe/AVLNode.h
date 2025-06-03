#pragma once

// Węzeł drzewa AVL przechowujący parę klucz-wartość
struct AVLNode {
    int klucz;
    int wartosc;
    int wysokosc;
    AVLNode* lewy;
    AVLNode* prawy;

    AVLNode(int k, int v)
        : klucz(k), wartosc(v), wysokosc(1), lewy(nullptr), prawy(nullptr) {
    }
};
