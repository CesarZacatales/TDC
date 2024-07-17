#include <iostream>
#include "nodo.hpp"

using namespace std;

// Clase para la lista doblemente enlazada circular
class ListaCircularDoble {
private:
    Nodo* cabeza; // Puntero al primer nodo de la lista

public:

    
    //Constructor, inicializa la lista con un puntero nulo
    ListaCircularDoble() : cabeza(nullptr) {}

    // Destructor, libera la memoria de todos los nodos de la lista
    ~ListaCircularDoble() {
        if (cabeza == nullptr) return; //verfica que la cabeza no sea nula

        Nodo* actual = cabeza;
        do {
            Nodo* temp = actual; //nodo que esta siendo apuntado sera nuestro actual 
            actual = actual->siguiente; //actual se mueve al siguiente nodo
            delete temp; //liberamos memoria 
        } while (actual != cabeza);

        cabeza = nullptr; // Reiniciar el puntero cabeza después de destruir la lista
    }

    // Método para insertar un nodo al final de la lista
    void insertar(int valor) {
        // Crear un nuevo nodo con el valor dado
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo->dato = valor;

        // Si la lista esta vacia, el nuevo nodo sera el único y se apuntara a si mismo
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            // Si la lista no esta vacia, se agregara el nuevo nodo al final
            Nodo* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevoNodo;
            nuevoNodo->anterior = ultimo;
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
        }
    }

    
     // Método para imprimir la lista, muestra los valores de los nodos en orden, separados por guiones
    void imprimir() {
        if (cabeza == nullptr) { //verifica que la cabeza sea nula, esto indica que la lista esta vacia
            cout << "La lista esta vacia." << endl;
            return;
        }
        Nodo* actual = cabeza; //nodo actual se inicializa con la cabeza de la lista
        do {
            cout << actual->dato; 
            if (actual->siguiente != cabeza) {
                cout << "-";
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
        cout << endl;
    }

   //Método para eliminar un nodo especifico de la lista
    void eliminar(Nodo* nodo) {
        if (cabeza == nullptr) return;

        // Si el nodo a eliminar es la cabeza
        if (cabeza == nodo) {
            // Si solo hay un nodo en la lista
            if (cabeza->siguiente == cabeza) {
                delete cabeza;
                cabeza = nullptr;
            } else {
                Nodo* ultimo = cabeza->anterior;
                cabeza = cabeza->siguiente;
                ultimo->siguiente = cabeza;
                cabeza->anterior = ultimo;
                delete nodo;
            }
        } else {
            // Si el nodo a eliminar esta en medio de la lista
            nodo->anterior->siguiente = nodo->siguiente;
            nodo->siguiente->anterior = nodo->anterior;
            delete nodo;
        }
    }
     //Método para obtener el primer nodo de la lista
    Nodo* obtenerCabeza() const {
        return cabeza;
    }
};