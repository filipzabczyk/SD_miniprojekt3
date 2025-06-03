#include "AVLTree.h"
#include <algorithm>

// Konstruktor – inicjalizuje pusty korzeń drzewa AVL
AVLTree::AVLTree() : korzen(nullptr) {}

// Destruktor – usuwa całe drzewo, aby nie było wycieku pamięci
AVLTree::~AVLTree() {
    usunDrzewo(korzen);
}

// Zwraca wysokość danego węzła, 0 jeśli wskaźnik pusty
int AVLTree::wysokosc(AVLNode* n) {
    return n ? n->wysokosc : 0;
}

// Oblicza współczynnik balansu węzła różnica wysokości lewego i prawego poddrzewa
int AVLTree::balans(AVLNode* n) {
    return n ? wysokosc(n->lewy) - wysokosc(n->prawy) : 0;
}

// Aktualizuje wysokość węzła na podstawie wysokości jego dzieci
void AVLTree::aktualizujWysokosc(AVLNode* n) {
    n->wysokosc = 1 + std::max(wysokosc(n->lewy), wysokosc(n->prawy));
}

// Wykonuje rotację w prawo wokół węzła y naprawa naruszenia lewo-lewo
AVLNode* AVLTree::rotacjaWPrawo(AVLNode* y) {
    AVLNode* x = y->lewy;
    AVLNode* T2 = x->prawy;
    x->prawy = y;
    y->lewy = T2;
    aktualizujWysokosc(y);
    aktualizujWysokosc(x);
    return x;
}

// Wykonuje rotację w lewo wokół węzła x naprawa naruszenia prawo-prawo
AVLNode* AVLTree::rotacjaWLewo(AVLNode* x) {
    AVLNode* y = x->prawy;
    AVLNode* T2 = y->lewy;
    y->lewy = x;
    x->prawy = T2;
    aktualizujWysokosc(x);
    aktualizujWysokosc(y);
    return y;
}

// Wstawia rekurencyjnie parę klucz, wartość do drzewa, przywraca balans
AVLNode* AVLTree::wstaw(AVLNode* node, int klucz, int wartosc) {
    if (!node) return new AVLNode(klucz, wartosc);

    if (klucz < node->klucz)
        node->lewy = wstaw(node->lewy, klucz, wartosc);
    else if (klucz > node->klucz)
        node->prawy = wstaw(node->prawy, klucz, wartosc);
    else {
        // Jeśli klucz już istnieje to nadpisz wartość
        node->wartosc = wartosc;
        return node;
    }

    // Aktualizuj wysokość i balansuj drzewo
    aktualizujWysokosc(node);
    int b = balans(node);

    // Naprawa naruszenia AVL przez odpowiednią rotację
    if (b > 1 && klucz < node->lewy->klucz)
        return rotacjaWPrawo(node);
    if (b < -1 && klucz > node->prawy->klucz)
        return rotacjaWLewo(node);
    if (b > 1 && klucz > node->lewy->klucz) {
        node->lewy = rotacjaWLewo(node->lewy);
        return rotacjaWPrawo(node);
    }
    if (b < -1 && klucz < node->prawy->klucz) {
        node->prawy = rotacjaWPrawo(node->prawy);
        return rotacjaWLewo(node);
    }

    return node;
}

// Zwraca wskaźnik do węzła o najmniejszym kluczu w danym poddrzewie
AVLNode* AVLTree::minWartosc(AVLNode* node) {
    while (node->lewy)
        node = node->lewy;
    return node;
}

// Usuwa węzeł o podanym kluczu, utrzymując balans drzewa AVL
AVLNode* AVLTree::usun(AVLNode* node, int klucz) {
    if (!node) return node;

    if (klucz < node->klucz)
        node->lewy = usun(node->lewy, klucz);
    else if (klucz > node->klucz)
        node->prawy = usun(node->prawy, klucz);
    else {
        // Jeśli jeden lub żadne dziecko to usuń węzeł bezpośrednio
        if (!node->lewy || !node->prawy) {
            AVLNode* temp = node->lewy ? node->lewy : node->prawy;
            delete node;
            return temp;
        } else {
            // Znajdź następnika i przesuń jego dane do bieżącego węzła
            AVLNode* temp = minWartosc(node->prawy);
            node->klucz = temp->klucz;
            node->wartosc = temp->wartosc;
            node->prawy = usun(node->prawy, temp->klucz);
        }
    }

    // Aktualizuj wysokość i balansuj drzewo
    aktualizujWysokosc(node);
    int b = balans(node);

    if (b > 1 && balans(node->lewy) >= 0)
        return rotacjaWPrawo(node);
    if (b > 1 && balans(node->lewy) < 0) {
        node->lewy = rotacjaWLewo(node->lewy);
        return rotacjaWPrawo(node);
    }
    if (b < -1 && balans(node->prawy) <= 0)
        return rotacjaWLewo(node);
    if (b < -1 && balans(node->prawy) > 0) {
        node->prawy = rotacjaWPrawo(node->prawy);
        return rotacjaWLewo(node);
    }

    return node;
}

// Usuwa rekurencyjnie całe drzewo – postorder traversal
void AVLTree::usunDrzewo(AVLNode* node) {
    if (!node) return;
    usunDrzewo(node->lewy);
    usunDrzewo(node->prawy);
    delete node;
}

// Publiczna metoda do wstawiania pary klucz, wartość
void AVLTree::insert(int klucz, int wartosc) {
    korzen = wstaw(korzen, klucz, wartosc);
}

// Publiczna metoda do usuwania klucza
void AVLTree::remove(int klucz) {
    korzen = usun(korzen, klucz);
}
