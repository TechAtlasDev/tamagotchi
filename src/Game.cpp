#include "Game.hpp"
#include <iostream>
#include <cstdio>

using namespace std;

Game::Game(int ancho_total, int alto_total) {
    ancho = ancho_total;
    alto = alto_total;
    pantalla = new Display(ancho, alto);
    mascota = nullptr;
    corriendo = true;
    frame_actual = 0;
    seccion_animacion = (alto * 3) / 5;
    if (seccion_animacion >= alto) {
        seccion_animacion = alto - 5;
    }
    animacion.cargar_animacion("assets/Gato", 6);
}

Game::~Game() {
    if (mascota != nullptr) {
        delete mascota;
    }
    if (pantalla != nullptr) {
        delete pantalla;
    }
}

void Game::dibujarTexto(int x, int y, const char* texto) {
    if (pantalla == nullptr) {
        return;
    }
    int cursor_x = x;
    int cursor_y = y;
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (c == '\n') {
            cursor_y++;
            cursor_x = x;
            continue;
        }
        if (cursor_x >= ancho || cursor_y >= alto) {
            break;
        }
        pantalla->draw(cursor_x, cursor_y, (int)c);
        cursor_x++;
    }
}

void Game::dibujarLineaDivisoria() {
    int linea = seccion_animacion;
    for (int x = 0; x < ancho; x++) {
        pantalla->draw(x, linea, (int)'-');
    }
}

void Game::dibujarAnimacion() {
    if (animacion.obtener_cantidad_frames() == 0) {
        dibujarTexto(2, 1, "Carga una animacion en assets/Gato para ver la mascota en pantalla.");
        return;
    }
    const char* frame = animacion.obtener_frame_str(frame_actual);
    int fila = 1;
    int columna = 2;
    int limite = seccion_animacion - 1;
    for (int i = 0; frame[i] != '\0' && fila < limite; i++) {
        char c = frame[i];
        if (c == '\n') {
            fila++;
            columna = 2;
            continue;
        }
        if (columna >= ancho - 2) {
            columna = 2;
            fila++;
            continue;
        }
        pantalla->draw(columna, fila, (int)c);
        columna++;
    }
    if (animacion.obtener_cantidad_frames() > 0) {
        frame_actual = (frame_actual + 1) % animacion.obtener_cantidad_frames();
    }
}

void Game::dibujarEstado() {
    if (mascota == nullptr) {
        return;
    }
    char buffer[128];
    int inicio = seccion_animacion + 1;
    dibujarLineaDivisoria();
    dibujarTexto(2, inicio, "Estado actual");
    snprintf(buffer, sizeof(buffer), "Nombre: %s", mascota->getNombre());
    dibujarTexto(2, inicio + 1, buffer);
    snprintf(buffer, sizeof(buffer), "Hambre: %d/100", mascota->getHambre());
    dibujarTexto(2, inicio + 2, buffer);
    snprintf(buffer, sizeof(buffer), "Felicidad: %d/100", mascota->getFelicidad());
    dibujarTexto(2, inicio + 3, buffer);
    snprintf(buffer, sizeof(buffer), "Energia: %d/100", mascota->getEnergia());
    dibujarTexto(2, inicio + 4, buffer);
    snprintf(buffer, sizeof(buffer), "Salud: %d/100", mascota->getSalud());
    dibujarTexto(2, inicio + 5, buffer);
    snprintf(buffer, sizeof(buffer), "Dinero: $%d", mascota->getDinero());
    dibujarTexto(2, inicio + 6, buffer);
}

void Game::dibujarMenu() {
    int inicio = seccion_animacion + 8;
    dibujarTexto(2, inicio, "Opciones disponibles:");
    dibujarTexto(2, inicio + 1, "1. Comer");
    dibujarTexto(2, inicio + 2, "2. Jugar");
    dibujarTexto(2, inicio + 3, "3. Dormir");
    dibujarTexto(2, inicio + 4, "4. Trabajar");
    dibujarTexto(2, inicio + 5, "5. Ver estado detallado");
    dibujarTexto(2, inicio + 6, "6. Volver al menu principal");
    dibujarTexto(2, inicio + 7, "7. Salir del juego");
}

void Game::renderizar() {
    if (pantalla == nullptr) {
        return;
    }
    dibujarAnimacion();
    dibujarEstado();
    dibujarMenu();
    pantalla->render();
}

int Game::pedirOpcion() {
    int opcion = 0;
    cout << "Ingresa opcion: ";
    cin >> opcion;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    
    cin.ignore(10000, '\n');
    return opcion;
}

void Game::procesarAccion(int opcion) {
    if (mascota == nullptr) {
        return;
    }
    if (opcion == 1) {
        mascota->comer();
    } else if (opcion == 2) {
        mascota->jugar();
    } else if (opcion == 3) {
        mascota->dormir();
    } else if (opcion == 4) {
        mascota->trabajar();
    } else if (opcion == 5) {
        mascota->mostrar_estado();
        cout << "Presiona Enter para continuar...";
        cin.ignore();
        cin.get();
    } else if (opcion == 6) {
        if (mascota != nullptr) {
            delete mascota;
            mascota = nullptr;
        }
    } else if (opcion == 7) {
        corriendo = false;
    }
}

bool Game::seleccionarMascota() {
    while (true) {
        cout << "\n";
        cout << "╔════════════════════════════════════════╗" << endl;
        cout << "║       TAMAGOTCHI - MENU PRINCIPAL      ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        cout << "\n1. Crear nuevo Tamagotchi (Gato)" << endl;
        cout << "2. Crear nuevo Tamagotchi (Pou)" << endl;
        cout << "3. Salir" << endl;
        cout << "\nElige una opcion (1-3): ";
        int opcion = 0;
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nOpcion invalida. Intenta de nuevo." << endl;
            continue;
        }
        
        cin.ignore(10000, '\n');
        if (opcion == 1 || opcion == 2) {
            char nombre[100];
            cout << "Nombre de tu mascota: ";
            cin.getline(nombre, 100);
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nNombre invalido. Intenta de nuevo." << endl;
                continue;
            }
            
            int len = 0;
            while (nombre[len] != '\0') len++;
            
            if (len == 0 || len >= 99) {
                cout << "\nNombre invalido. Debe tener entre 1 y 98 caracteres." << endl;
                continue;
            }
            if (mascota != nullptr) {
                delete mascota;
            }
            if (opcion == 1) {
                mascota = new Gato(nombre);
            } else {
                mascota = new Pou(nombre);
            }
            return true;
        } else if (opcion == 3) {
            return false;
        } else {
            cout << "\nOpcion invalida. Intenta de nuevo." << endl;
        }
    }
}

void Game::manejarMuerte() {
    if (mascota == nullptr) {
        return;
    }
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  ¡Tu Tamagotchi ha muerto!            ║" << endl;
    cout << "║  No cuidaste bien a tu mascota :(      ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    delete mascota;
    mascota = nullptr;
}

void Game::play() {
    time_t ultima_actualizacion = time(nullptr);
    
    while (corriendo) {
        if (mascota == nullptr) {
            if (!seleccionarMascota()) {
                corriendo = false;
                break;
            }
            ultima_actualizacion = time(nullptr);
            continue;
        }
        
        time_t ahora = time(nullptr);
        if (difftime(ahora, ultima_actualizacion) >= 5) {
            int modulo = (int)difftime(ahora, ultima_actualizacion) % 5;
            for (int i = 0; i < modulo; i++) {
                mascota->trabajar();
            }
            ultima_actualizacion = ahora;
            
            if (!mascota->estaVivo()) {
                manejarMuerte();
                continue;
            }
        }
        
        pantalla->limpiar();
        renderizar();
        
        if (!mascota->estaVivo()) {
            manejarMuerte();
            continue;
        }
        
        int opcion = pedirOpcion();
        procesarAccion(opcion);
        
        if (!corriendo) {
            break;
        }
        
        if (mascota != nullptr && !mascota->estaVivo()) {
            manejarMuerte();
        }
    }
}
