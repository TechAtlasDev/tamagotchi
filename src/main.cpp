#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "Display.hpp"
#include "Tamagotchi.hpp"
#include "Inventario.hpp"

using namespace std;

void mostrar_menu_principal() {
    cout << "\n";
    cout << "" << endl;
    cout << "║       TAMAGOTCHI - MENU PRINCIPAL  " << endl;
    cout << "" << endl;
    cout << "\n1. Crear nuevo Tamagotchi (Gato)" << endl;
    cout << "2. Crear nuevo Tamagotchi (Pou)" << endl;
    cout << "3. Salir" << endl;
    cout << "\nElige una opcion (1-3): ";
}

void generar_menu_acciones(char* buffer, int max_size) {
    snprintf(buffer, max_size,
        "\\n"
        "║         MENU DE ACCIONES           \n"
        "\n"
        "\n1. Comer\n"
        "2. Jugar\n"
        "3. Dormir\n"
        "4. Trabajar\n"
        "5. Ver estado\n"
        "6. Volver al menu principal\n"
        "\nElige una accion (1-6): "
    );
}

void generar_pantalla_juego(Tamagotchi* mascota, char* buffer, int max_size) {
    int felicidad = mascota->getFelicidad();
    int energia = mascota->getEnergia();
    int salud = mascota->getSalud();
    int dinero = mascota->getDinero();
    
    snprintf(buffer, max_size,
        "\n Nombre: %s\n"
        " Felicidad: %d/100\n"
        " Energia:   %d/100\n"
        " Salud:     %d/100\n"
        " Dinero:    $%d\n",
        mascota->getNombre(), felicidad, energia, salud, dinero
    );
}

int main() {
    srand(time(nullptr));
    Tamagotchi* mascota = nullptr;
    AnimacionDisplay* animacion = nullptr;
    DisplayLayout* layout = new DisplayLayout(120, 70, 60);
    int opcion = 0;

    while (true) {
        if (mascota == nullptr) {
            mostrar_menu_principal();
            cin >> opcion;

            char nombre[100];

            if (opcion == 1) {
                cout << "Nombre de tu Gato: ";
                cin >> nombre;
                mascota = new Gato(nombre);
                animacion = new AnimacionDisplay();
                animacion->cargar_animacion("assets/Gato", 6);
                cout << "\n¡Gato creado exitosamente!" << endl;
            } else if (opcion == 2) {
                cout << "Nombre de tu Pou: ";
                cin >> nombre;
                mascota = new Pou(nombre);
                animacion = new AnimacionDisplay();
                animacion->cargar_animacion("assets/Gato", 6);
                cout << "\n¡Pou creado exitosamente!" << endl;
            } else if (opcion == 3) {
                cout << "\n¡Hasta luego!" << endl;
                delete layout;
                break;
            } else {
                cout << "\nOpcion invalida. Intenta de nuevo." << endl;
            }
        } else {
            char menu_str[1024];
            char estado_str[1024];
            char contenido_completo[2048];
            
            generar_menu_acciones(menu_str, sizeof(menu_str));
            generar_pantalla_juego(mascota, estado_str, sizeof(estado_str));
            
            snprintf(contenido_completo, sizeof(contenido_completo), "%s\n%s", estado_str, menu_str);
            
            if (animacion != nullptr && animacion->obtener_cantidad_frames() > 0) {
                layout->mostrar_animacion_y_menu(animacion->obtener_frame_str(0), contenido_completo);
            }
            
            cin >> opcion;

            if (opcion == 1) {
                mascota->comer();
                cout << "\n¡Tu Tamagotchi comio!" << endl;
            } else if (opcion == 2) {
                mascota->jugar();
                cout << "\n¡Tu Tamagotchi esta jugando!" << endl;
            } else if (opcion == 3) {
                mascota->dormir();
                cout << "\n¡Tu Tamagotchi esta durmiendo!" << endl;
            } else if (opcion == 4) {
                mascota->trabajar();
                cout << "\n¡Tu Tamagotchi esta trabajando!" << endl;
            } else if (opcion == 5) {
                system("clear");
                mascota->mostrar_estado();
                cout << "Presiona Enter para continuar...";
                cin.ignore();
                cin.get();
            } else if (opcion == 6) {
                if (mascota != nullptr) {
                    delete mascota;
                    mascota = nullptr;
                }
                if (animacion != nullptr) {
                    delete animacion;
                    animacion = nullptr;
                }
                cout << "\nVolviendo al menu principal..." << endl;
            } else {
                cout << "\nOpcion invalida. Intenta de nuevo." << endl;
            }
            if (mascota != nullptr) {
                mascota->actualizar();
            }

            if (mascota != nullptr && !mascota->estaVivo()) {
                system("clear");
                cout << "\n" << endl;
                cout << "Tu Tamagotchi ha muerto!        " << endl;
                cout << "No cuidaste bien a tu mascota :(" << endl;
                cout << "" << endl;
                delete mascota;
                mascota = nullptr;
                if (animacion != nullptr) {
                    delete animacion;
                    animacion = nullptr;
                }
                cout << "\nVolviendo al menu principal...\n" << endl;
            }
        }
    }

    return 0;
}