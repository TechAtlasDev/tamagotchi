#include "Display.hpp"
#include <cstdlib>

Display::Display(int x, int y) {
    ancho = x;
    alto = y;
    generar();
}

Display::~Display() {
    if (data != nullptr) {
        for (int i = 0; i < alto; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
}

void Display::generar() {
    data = new int*[alto];

    for (int i = 0; i < alto; i++) {
        data[i] = new int[ancho];
    }

    rellenar_matriz(0);
}

void Display::rellenar_matriz(int valor) {
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            data[i][j] = valor;
        }
    }
}

void Display::limpiar() {
    rellenar_matriz(0);
}

void Display::print() {
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void Display::setValor(int x, int y, int valor) {
    if (x >= 0 && x < ancho && y >= 0 && y < alto) {
        data[y][x] = valor;
    }
}

int Display::getValor(int x, int y) {
    if (x >= 0 && x < ancho && y >= 0 && y < alto) {
        return data[y][x];
    }
    return 0;
}

void Display::draw(int x, int y, int valor) {
    setValor(x, y, valor);
}

char Display::replace_ascii(int valor) {
    switch (valor) {
        case 0: return ' ';
        case 1: return '@';
        case 2: return '#';
        case 3: return '*';
        case 4: return '%';
        case 5: return '+';
        case 6: return '=';
        case 7: return '-';
        case 8: return ':';
        case 9: return '.';
        default: return (char)valor;
    }
}

void Display::clear_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Display::render() {
    clear_terminal();
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            int valor = getValor(j, i);
            cout << replace_ascii(valor);
        }
        cout << endl;
    }
}

AnimacionDisplay::AnimacionDisplay() {
    frames_cargados = 0;
    frame_actual = 0;
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i][0] = '\0';
    }
}

AnimacionDisplay::~AnimacionDisplay() {
}

bool AnimacionDisplay::cargar_frame(const char* ruta, int indice) {
    if (indice < 0 || indice >= MAX_FRAMES) {
        cerr << "Indice de frame fuera de rango: " << indice << endl;
        return false;
    }
    
    ifstream archivo(ruta);
    
    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo: " << ruta << endl;
        return false;
    }
    
    int pos = 0;
    char caracter;
    
    while (archivo.get(caracter) && pos < MAX_FRAME_SIZE - 1) {
        frames[indice][pos++] = caracter;
    }
    frames[indice][pos] = '\0';
    
    archivo.close();
    return true;
}

bool AnimacionDisplay::cargar_animacion(const char* carpeta, int cantidad_frames) {
    if (cantidad_frames > MAX_FRAMES) {
        cerr << "Cantidad de frames excede el máximo permitido: " << MAX_FRAMES << endl;
        return false;
    }
    
    frames_cargados = 0;
    
    for (int i = 1; i <= cantidad_frames; i++) {
        char ruta[256];
        snprintf(ruta, sizeof(ruta), "%s/Frame%d.txt", carpeta, i);
        
        if (!cargar_frame(ruta, i - 1)) {
            cerr << "Error al cargar Frame " << i << endl;
            return false;
        }
        frames_cargados++;
    }
    
    return true;
}

void AnimacionDisplay::mostrar_frame(int numero_frame) {
    if (numero_frame < 0 || numero_frame >= frames_cargados) {
        cerr << "Frame no valido: " << numero_frame << endl;
        return;
    }
    
    system("clear");
    cout << frames[numero_frame];
}

void AnimacionDisplay::mostrar_animacion() {
    if (frames_cargados == 0) {
        cerr << "No hay frames cargados" << endl;
        return;
    }
    
    system("clear");
    cout << frames[frame_actual];
    frame_actual = (frame_actual + 1) % frames_cargados;
}

int AnimacionDisplay::obtener_cantidad_frames() const {
    return frames_cargados;
}

const char* AnimacionDisplay::obtener_frame_str(int numero_frame) const {
    if (numero_frame < 0 || numero_frame >= frames_cargados) {
        return "";
    }
    return frames[numero_frame];
}

DisplayLayout::DisplayLayout(int ancho, int alto_total, int porcentaje_superior) {
    this->ancho = ancho;
    this->alto_total = alto_total;
    this->alto_superior = (alto_total * porcentaje_superior) / 100;
    this->alto_inferior = alto_total - alto_superior - 1;
}

DisplayLayout::~DisplayLayout() {
}

int DisplayLayout::obtener_alto_superior() const {
    return alto_superior;
}

int DisplayLayout::obtener_alto_inferior() const {
    return alto_inferior;
}

void DisplayLayout::mostrar_linea_divisoria() {
    for (int i = 0; i < ancho; i++) {
        cout << "═";
    }
    cout << endl;
}

void DisplayLayout::mostrar_animacion_y_menu(const char* animacion, const char* menu) {
    system("clear");
    
    int lineas_animacion = 0;
    const char* ptr = animacion;
    int col_actual = 0;
    
    while (*ptr != '\0' && lineas_animacion < alto_superior) {
        cout << *ptr;
        if (*ptr == '\n') {
            lineas_animacion++;
            col_actual = 0;
        } else {
            col_actual++;
        }
        ptr++;
    }
    
    while (lineas_animacion < alto_superior) {
        cout << endl;
        lineas_animacion++;
    }
    
    mostrar_linea_divisoria();
    
    int lineas_menu = 0;
    ptr = menu;
    col_actual = 0;
    
    while (*ptr != '\0' && lineas_menu < alto_inferior) {
        cout << *ptr;
        if (*ptr == '\n') {
            lineas_menu++;
            col_actual = 0;
        } else {
            col_actual++;
        }
        ptr++;
    }
}
