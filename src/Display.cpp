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
    system("clear");
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

// ============ AnimacionDisplay ============

AnimacionDisplay::AnimacionDisplay() {
}

AnimacionDisplay::~AnimacionDisplay() {
    frames.clear();
}

bool AnimacionDisplay::cargar_frame(const char* ruta) {
    ifstream archivo(ruta);
    
    if (!archivo.is_open()) {
        cerr << "Error al abrir archivo: " << ruta << endl;
        return false;
    }
    
    string contenido = "";
    string linea;
    
    while (getline(archivo, linea)) {
        contenido += linea + "\n";
    }
    
    archivo.close();
    frames.push_back(contenido);
    return true;
}

bool AnimacionDisplay::cargar_animacion(const char* carpeta, int cantidad_frames) {
    frames.clear();
    
    for (int i = 1; i <= cantidad_frames; i++) {
        char ruta[256];
        snprintf(ruta, sizeof(ruta), "%s/Frame%d.txt", carpeta, i);
        
        if (!cargar_frame(ruta)) {
            cerr << "Error al cargar Frame " << i << endl;
            return false;
        }
    }
    
    return true;
}

void AnimacionDisplay::mostrar_frame(int numero_frame) {
    if (numero_frame < 0 || numero_frame >= (int)frames.size()) {
        cerr << "Frame no valido: " << numero_frame << endl;
        return;
    }
    
    system("clear");
    cout << frames[numero_frame];
}

void AnimacionDisplay::mostrar_animacion() {
    if (frames.empty()) {
        cerr << "No hay frames cargados" << endl;
        return;
    }
    
    system("clear");
    cout << frames[frame_actual];
    frame_actual = (frame_actual + 1) % frames.size();
}

int AnimacionDisplay::obtener_cantidad_frames() const {
    return frames.size();
}

string AnimacionDisplay::obtener_frame_str(int numero_frame) const {
    if (numero_frame < 0 || numero_frame >= (int)frames.size()) {
        return "";
    }
    return frames[numero_frame];
}

// ============ DisplayLayout ============

DisplayLayout::DisplayLayout(int ancho, int alto_total, int porcentaje_superior) {
    this->ancho = ancho;
    this->alto_total = alto_total;
    this->alto_superior = (alto_total * porcentaje_superior) / 100;
    this->alto_inferior = alto_total - alto_superior - 1; // -1 para la línea divisoria
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

void DisplayLayout::mostrar_animacion_y_menu(const string& animacion, const string& menu) {
    system("clear");
    
    // Dividir animación en líneas
    vector<string> lineas_animacion;
    string linea_actual = "";
    for (size_t i = 0; i < animacion.length(); i++) {
        if (animacion[i] == '\n') {
            // Limitar líneas al ancho máximo
            if (linea_actual.length() > (size_t)ancho) {
                linea_actual = linea_actual.substr(0, ancho);
            }
            lineas_animacion.push_back(linea_actual);
            linea_actual = "";
        } else {
            linea_actual += animacion[i];
        }
    }
    if (!linea_actual.empty()) {
        if (linea_actual.length() > (size_t)ancho) {
            linea_actual = linea_actual.substr(0, ancho);
        }
        lineas_animacion.push_back(linea_actual);
    }
    
    // Mostrar sección superior (animación)
    int lineas_mostradas = 0;
    for (const string& l : lineas_animacion) {
        if (lineas_mostradas >= alto_superior) break;
        cout << l << endl;
        lineas_mostradas++;
    }
    
    // Rellenar con espacios si la animación tiene menos líneas
    while (lineas_mostradas < alto_superior) {
        cout << endl;
        lineas_mostradas++;
    }
    
    // Línea divisoria
    mostrar_linea_divisoria();
    
    // Mostrar sección inferior (menú)
    vector<string> lineas_menu;
    linea_actual = "";
    for (size_t i = 0; i < menu.length(); i++) {
        if (menu[i] == '\n') {
            if (linea_actual.length() > (size_t)ancho) {
                linea_actual = linea_actual.substr(0, ancho);
            }
            lineas_menu.push_back(linea_actual);
            linea_actual = "";
        } else {
            linea_actual += menu[i];
        }
    }
    if (!linea_actual.empty()) {
        if (linea_actual.length() > (size_t)ancho) {
            linea_actual = linea_actual.substr(0, ancho);
        }
        lineas_menu.push_back(linea_actual);
    }
    
    lineas_mostradas = 0;
    for (const string& l : lineas_menu) {
        if (lineas_mostradas >= alto_inferior) break;
        cout << l << endl;
        lineas_mostradas++;
    }
}
