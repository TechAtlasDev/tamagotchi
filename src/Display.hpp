#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include <fstream>

using namespace std;

const int MAX_FRAMES = 10;
const int MAX_FRAME_SIZE = 5000;

class Display {
    private:
        int** data = nullptr;
        int ancho = 0;
        int alto = 0;

        void rellenar_matriz(int valor);
        void clear_terminal();
        char replace_ascii(int valor);

    public:
        Display(int x, int y);
        ~Display();

        void print();
        void setValor(int x, int y, int valor);
        int getValor(int x, int y);
        void generar();
        void render();
        void draw(int x, int y, int valor);
        void limpiar();
};

class AnimacionDisplay {
    private:
        char frames[MAX_FRAMES][MAX_FRAME_SIZE];
        int frames_cargados = 0;
        int frame_actual = 0;
        bool cargar_frame(const char* ruta, int indice);

    public:
        AnimacionDisplay();
        ~AnimacionDisplay();

        bool cargar_animacion(const char* carpeta, int cantidad_frames);
        void mostrar_frame(int numero_frame);
        void mostrar_animacion();
        int obtener_cantidad_frames() const;
        const char* obtener_frame_str(int numero_frame) const;
};

class DisplayLayout {
    private:
        int ancho = 0;
        int alto_total = 0;
        int alto_superior = 0;
        int alto_inferior = 0;

    public:
        DisplayLayout(int ancho, int alto_total, int porcentaje_superior = 60);
        ~DisplayLayout();

        void mostrar_animacion_y_menu(const char* animacion, const char* menu);
        void mostrar_linea_divisoria();
        int obtener_alto_superior() const;
        int obtener_alto_inferior() const;
};

#endif
