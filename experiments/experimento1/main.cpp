#include <iostream>

using namespace std;

class Matriz {
    private:
        int** data=nullptr;

        void rellenar_matriz(int valor);
        void clear_terminal();

    public:
        int x=0;
        int y=0;

        Matriz(int columnas, int filas);
        Matriz();

        void print();
        void setValor(int columna, int fila, int valor);
        int getValor(int columna, int fila);
        void generar();
};

Matriz::Matriz(int columnas, int filas) {            
        x = columnas;
        y = filas;
    }

Matriz::Matriz() {
    x=0;
    y=0;
}

void Matriz::generar() {
    data = new int*[y];

    for (int i=0; i<x; i++) {
        data[i] = new int[y];
    }

    rellenar_matriz(0);
}

void Matriz::rellenar_matriz(int valor) {
    clear_terminal();
    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {
            data[i][j] = valor;
        }
    };
}

void Matriz::print() {
    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    };
}

void Matriz::setValor(int columna, int fila, int valor) {
    data[columna][fila] = valor;
}

int Matriz::getValor(int columna, int fila) {
    return data[columna][fila];
}

void Matriz::clear_terminal() {
    system("clear");
}

class Display {
    private:
        int ancho=0;
        int alto=0;
        Matriz pepe;
        
        char replace_ascii(int valor);

    public:
        Display(int x, int y);

        void render();
        void draw(int x, int y, int valor);
};

void Display::draw(int x, int y, int valor) {
    pepe.setValor(x, y, valor);
}

Display::Display(int x, int y) {
    pepe.x=x;
    pepe.y=y;

    pepe.generar();
}

char Display::replace_ascii(int valor) {
    return valor;
}

void Display::render() {
    for (int i=0; i<pepe.x; i++) {
            for (int j=0; j<pepe.y; j++) {
                int valor = pepe.getValor(i, j);
                cout << replace_ascii(valor) << " ";
            }  
            cout << endl;
    }
}

int main() {
    Display d(101, 53);
    d.draw(5, 10, 53);
    d.render();

    return 0;
}