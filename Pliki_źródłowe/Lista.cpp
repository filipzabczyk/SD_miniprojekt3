#include "Lista.h"

// Konstruktor – inicjalizuje pustą listę (brak elementów)
Lista::Lista() : glowa(nullptr) {}

// Destruktor – usuwa wszystkie węzły listy, zwalniając pamięć
Lista::~Lista() {
    while (glowa) {
        Wezel* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }
}

// Wstawia nowy element do listy lub nadpisuje wartość, jeśli klucz już istnieje
void Lista::insert(int klucz, int wartosc) {
    // Przeszukaj listę, aby sprawdzić, czy klucz już istnieje
    for (Wezel* p = glowa; p; p = p->nastepny) {
        if (p->klucz == klucz) {
            // Jeśli klucz istnieje – zaktualizuj wartość
            p->wartosc = wartosc;
            return;
        }
    }

    // Jeśli klucz nie istnieje – dodaj nowy węzeł na początek listy
    Wezel* nowy = new Wezel(klucz, wartosc);
    nowy->nastepny = glowa;
    glowa = nowy;
}

// Usuwa element o podanym kluczu z listy jednokierunkowej
void Lista::remove(int klucz) {
    Wezel* p = glowa;
    Wezel* prev = nullptr;

    // Przeszukaj listę w poszukiwaniu węzła o danym kluczu
    while (p) {
        if (p->klucz == klucz) {
            // Jeśli znaleziono: zaktualizuj wskaźnik poprzedniego węzła
            if (prev)
                prev->nastepny = p->nastepny;
            else
                glowa = p->nastepny;  // Usuwa pierwszy element
            delete p;
            return;
        }
        prev = p;
        p = p->nastepny;
    }
}
