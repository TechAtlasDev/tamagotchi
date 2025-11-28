#ifndef GAME_HPP
#define GAME_HPP

#include "Display.hpp"
#include "Tamagotchi.hpp"
#include "Inventario.hpp"

class Game {
    private:
        Display* pantalla;
        AnimacionDisplay animacion;
        Tamagotchi* mascota;
        bool corriendo;
        int ancho;
        int alto;
        int seccion_animacion;
        int frame_actual;

        void dibujarTexto(int x, int y, const char* texto);
        void dibujarLineaDivisoria();
        void dibujarAnimacion();
        void dibujarEstado();
        void dibujarMenu();
        void renderizar();
        int pedirOpcion();
        void procesarAccion(int opcion);
        bool seleccionarMascota();
        void manejarMuerte();

    public:
        Game(int ancho, int alto);
        ~Game();
        void play();
};

#endif
