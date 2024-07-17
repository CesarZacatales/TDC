#include <iostream>
#include "listaDoble.hpp"
using namespace std;

// Función para ejecutar el algoritmo de Josefo
void AlgoritmoJosefo(ListaCircularDoble& soldados) {
    Nodo* actual = soldados.obtenerCabeza();

    // Imprimir la lista inicial antes de comenzar el algoritmo
    cout << "Lista inicial: ";
    soldados.imprimir();

    while (actual->siguiente != actual) {
        Nodo* siguienteSoldado = actual->siguiente;
        cout << "Lista despues de eliminar " << siguienteSoldado->dato << ": ";
        // Eliminar al soldado actual
        soldados.eliminar(siguienteSoldado);
        actual = actual->siguiente;
        // Imprimir la lista después de la eliminación
        soldados.imprimir();
    }

    // Imprimir el último sobreviviente
    cout << "Ultimo sobreviviente: " << soldados.obtenerCabeza()->dato << endl;
}

// Función para imprimir un número específico de pasos del algoritmo de Josefo
void imprimirPasos(ListaCircularDoble& soldados, int pasos, bool mostrarSobrevivientes = false) {
    Nodo* actual = soldados.obtenerCabeza(); // Obtener el primer soldado de la lista
    int contador = 0; 
    // Iterar hasta que se alcance el número de pasos o se elimine a todos los soldados
    while (contador < pasos && actual->siguiente != actual) {
        Nodo* siguienteSoldado = actual->siguiente; // Obtener el siguiente soldado a eliminar
        cout << "Soldado eliminado: " << siguienteSoldado->dato << endl; 

        // Eliminar al soldado actual
        soldados.eliminar(siguienteSoldado);
        // Imprimir la lista después de la eliminación
        soldados.imprimir();

        actual = actual->siguiente; // Mover al siguiente soldado
        contador++; // Incrementar el contador de pasos
    }

    // Mostrar la lista de sobrevivientes si se indica
    if (mostrarSobrevivientes) {
        cout << "Soldados sobrevivientes: ";
        actual = soldados.obtenerCabeza(); // Obtener el primer soldado de la lista nuevamente
        do {
            cout << actual->dato; // Imprimir el dato del soldado actual
            if (actual->siguiente != soldados.obtenerCabeza()) {
                cout << "-"; // Agregar guión si no es el último soldado
            }
            actual = actual->siguiente; // Mover al siguiente soldado
        } while (actual != soldados.obtenerCabeza()); // Iterar hasta regresar al primer soldado
        cout << endl; 
    }
}