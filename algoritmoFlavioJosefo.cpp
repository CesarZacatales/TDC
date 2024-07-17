#include <iostream>
#include <cstdlib>
#include <unistd.h> //para la funcion sleep que nos dejara asombrarlo con un mensaje al inicio del programa XD

using namespace std;
//definicion de codigos de color para el texto 
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"  

void escribirMensaje(const string& message) {
    for (char c : message) {
        cout << c << flush; // flush para que se muestre inmediatamente
        usleep(100000); // Retraso de 100 milisegundos para escribir cada letra del mensaje inicial 
    }
}

// Definición de la estructura de nodo
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Función para crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// Clase para la lista circular doblemente enlazada
class ListaCircularDobleEnlazada {
private:
    Node* head;
    Node* tail;
    int size;

public:
    // Constructor
    ListaCircularDobleEnlazada() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor
    ~ListaCircularDobleEnlazada() {
        while (size > 0)
            removeNode(head);
    }

    // Función para agregar un nodo al final de la lista
    void addNode(int data) {
        Node* newNode = createNode(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            head->next = tail;
            tail->prev = head;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
        size++;
    }
    
    // Función para crear la lista
    void createList(int k) {
        for (int i = 1; i <= k; ++i) {
            addNode(i);
        }
    }
   
    // Función para eliminar un nodo de la lista
    void removeNode(Node* node) {
        if (size == 0)
            return;
        if (size == 1) {
            delete node;
            head = nullptr;
            tail = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if (node == head)
                head = node->next;
            else if (node == tail)
                tail = node->prev;
            delete node;
        }
        size--;
    }

    // Función para mostrar la lista
    void display() {
        if (size == 0){
            cout << MAGENTA << "Carpe diem" << RESET << endl;
            cout << "Lista vacia" << endl;
        }else {
            Node* current = head;
            do {
                cout << current->data << " ";
                current = current->next;
            } while (current != head);
            cout << endl;
        }
    }

    // Algoritmo de eliminacion de Flavio Josefo
    void flavioJosefo(int k) {
        if (size == 0) {
            cout << "No hay nodos en la lista." << endl;
            return;
        }
        if (size == 1) {
        cout<< RED << "Veni, vidi, vici" << RESET << endl;
        cout << "¡El nodo sobreviviente es: " <<  head->data << "!" << endl;
        return;
        }
        Node* current = head;
        display();
        for(int i = 0; i < size ; i++){
            if(i < size - 1){
                cout << "--" ;
            }else{
                cout << "-" << endl;
            }
            
        }
        
        while (size > 1) {
            for (int i = 0; i < k - 1; ++i) {
                current = current->next;
            }
            Node* nextNode = current->next;
            removeNode(current);
            current = nextNode;
            display();
        }
        cout<< RED << "Veni, vidi, vici" << RESET << endl;
        cout << "El nodo sobreviviente es: " << RED << current->data << RESET << endl;
    }
    
    // Función para eliminar la lista y liberar memoria
    void clear() {
        while (size > 0) {
            removeNode(head);
        }
    }

    // Algoritmo de Flavio Josefo parcial
    void flavioJosefoParcial(int k, int j) {
        int initialSize = size;
        if (size == 0) {
            cout << "No hay nodos en la lista." << endl;
            return;
        }
        if(j > initialSize - 1) {
            cout << "No es posible tener mas ejecuciones que el tamano de la lista - 1." << endl;
            return;
        }
        Node* current = head;
        display();
        for(int i = 0; i < size ; i++){
            if(i < size - 1){
                cout << "--" ;
            }else{
                cout << "-" << endl;
            }
            
        }
        while (size > (initialSize - j)) {
            for (int i = 0; i < k - 1; ++i) {
                current = current->next;
            }
            Node* nextNode = current->next;
            removeNode(current);
            current = nextNode;
            display();
        }
    }
};

void printMenu(){
    system("cls");
    cout << "############ MENU ############\n";
    cout << "1- Crear lista nueva\n";
    cout << "2- Consultar lista\n";
    cout << "3- Ejecutar algoritmo completo\n";
    cout << "4- Ejecutar algoritmo parcial\n";
    cout << "5- Eliminar lista\n";
    cout << "6- Salir\n";
    cout << "Elija una opcion: ";
}

int main() {
    string entrada = "Buen dia Heroe\nFlavio Josefo esta en aprietos y necesita tu ayuda para sobrevivir!!\neste creativo y desesperado grupo de estudiantes\nha creado un programa para que puedas ayudarle\nMemento mori";
    string salida = "buena suerte en tu camino \ngracias por ayudar a Flavio Josefo a sobrevivir, la historia seria diferente sin el \nesperamos pasar la materia\ny haber sido de tu ayuda ";
    escribirMensaje(entrada);
    sleep(2);
    ListaCircularDobleEnlazada list;

    int n, k, j, opcion;

    do{
        cout << endl;
        printMenu();
        cin >> opcion;
        switch(opcion){
            case 1:
                system("cls");
                cout << "Ingrese el tamano de la lista: ";
                cin >> n;
                list.createList(n);
                cout << "Lista llenada exitosamente" << endl;
                cout << "Presiona una tecla para volver al menu...";
                cin.ignore(); // Ignora el salto de línea anterior
                cin.get(); // Espera a que el usuario presione una tecla
                break;
            case 2:
                system("cls");
                cout << BLUE << "Ave Caesar, morituri te salutant" << RESET << endl;
                cout << "Lista Actual:" << endl;

                list.display();
                cout << "Presiona una tecla para volver al menu...";
                cin.ignore(); // Ignora el salto de línea anterior
                cin.get(); // Espera a que el usuario presione una tecla
                break;
            case 3:
                system("cls");
                cout << "Ingrese la cantidad de saltos para el algoritmo de Flavio Josefo: \n";
                cout << "(toma en cuenta que Flavio Josefo no sabia programacion,\ny le seria dificil entender el recorrido de una lista) \n";
                cout << "asi que la cantidad de saltos se contara a partir de tu posicion \n";
                cin >> k;
                k++;//aumentamos en uno la variable de entrada de la lista para que se corra el algoritmo en base a la percepcion natural y no como recorrido de lista
                list.flavioJosefo(k);
                cout << "Presiona una tecla para volver al menu...";
                cin.ignore(); // Ignora el salto de línea anterior
                cin.get(); // Espera a que el usuario presione una tecla
                break;
            case 4:
                system("cls");
                cout << "Ingrese la cantidad de saltos para el algoritmo de Flavio Josefo parcial: \n";
                cout << "(toma en cuenta que Flavio Josefo no sabia programacion, \ny le seria dificil entender el recorrido de una lista) \n";
                cout << "asi que la cantidad de saltos se contara a partir de tu posicion \n";
                cin >> k;
                k++;//aumentamos en uno la variable de entrada de la lista para que se corra el algoritmo en base a la percepcion natural y no como recorrido de lista
                cout << "Ingrese cuantos ejecuciones se mostraran: ";
                cin >> j;
                list.flavioJosefoParcial(k, j);
                cout << "Presiona una tecla para volver al menu...";
                cin.ignore(); // Ignora el salto de línea anterior
                cin.get(); // Espera a que el usuario presione una tecla
                break;
            case 5:
                system("cls");
                list.clear();
                cout << "Roma est fortis" << endl;
                cout << "Lista de enemigos eliminada." << endl ;
                cout << "Presiona una tecla para volver al menu...";
                cin.ignore(); // Ignora el salto de línea anterior
                cin.get(); // Espera a que el usuario presione una tecla
                break;
            case 6:
                system("cls");
                escribirMensaje(salida); 
                sleep(2);
                exit(0);
            default:
                cout << "Valor ingresado no valido" << endl ;
                break;
        }
        k = 0, j = 0;
    }while(opcion != 6);

    return 0;
}