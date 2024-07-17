#include <iostream>
#include "josefo.hpp"

using namespace std;

int main() {
    ListaCircularDoble soldados;
    int opcion;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Crear nueva lista" << endl;
        cout << "2. Ver lista existente" << endl;
        cout << "3. Ejecutar algoritmo completo de Josefo" << endl;
        cout << "4. Ejecutar un numero especifico de pasos del algoritmo" << endl;
        cout << "5. Eliminar lista" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << "\n";

        switch (opcion) {
            case 1: {
                // Crear una nueva lista
                int n;
                cout << "Ingrese el numero de soldados: ";
                cin >> n;
                for (int i = 1; i <= n; ++i) {
                    soldados.insertar(i);
                }
                break;
            }
            case 2:
                // Ver la lista existente
                cout << "Lista de soldados: ";
                soldados.imprimir();
                break;
            case 3:
                // Ejecutar el algoritmo completo de Josefo
                if (soldados.obtenerCabeza() == nullptr) {
                    cout << "---La lista esta vacia---" << endl; // Mensaje en caso de lista vacia
                } else {
                        AlgoritmoJosefo(soldados);
                }
                break;
            case 4: {
                // Ejecutar un numero especifico de pasos del algoritmo
                if (soldados.obtenerCabeza() == nullptr) {
                    cout << "---La lista esta vacia---" << endl; // Mensaje en caso de lista vacia
                } else if (soldados.obtenerCabeza()->siguiente == soldados.obtenerCabeza()) {
                    cout << "---No hay suficientes datos en la lista---" << endl;
                } else {
                    int pasos;
                    cout << "Ingrese el numero de pasos: ";
                    cin >> pasos;
                    imprimirPasos(soldados, pasos, true);
                }
                break;
            }
            case 5:
                // Eliminar la lista
                if (soldados.obtenerCabeza() == nullptr) {
                    cout << "---La lista esta vacia---" << endl; // Mensaje en caso de lista vacia
                } else {
                    soldados.~ListaCircularDoble();
                    cout << "Lista eliminada." << endl;
                }
                break;
            case 6:
                // Salir del programa
                cout << "Saliendo del programa.\n" << endl; //SALIENDO DEL PROGRAM                   
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n" << endl;
        }
    } while (opcion != 6);
    
    return 0;
}
