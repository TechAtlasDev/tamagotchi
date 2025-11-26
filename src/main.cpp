#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Display.hpp"
#include "Tamagotchi.hpp"
#include "Inventario.hpp"

using namespace std;

void mostrar_menu_principal() {
    cout << "\n";
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║       TAMAGOTCHI - MENU PRINCIPAL      ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "\n1. Crear nuevo Tamagotchi (Gato)" << endl;
    cout << "2. Crear nuevo Tamagotchi (Pou)" << endl;
    cout << "3. Salir" << endl;
    cout << "\nElige una opcion (1-3): ";
}

string generar_menu_acciones() {
    stringstream ss;
    ss << "\n";
    ss << "╔════════════════════════════════════════╗" << endl;
    ss << "║         MENU DE ACCIONES               ║" << endl;
    ss << "╚════════════════════════════════════════╝" << endl;
    ss << "\n1. Comer" << endl;
    ss << "2. Jugar" << endl;
    ss << "3. Dormir" << endl;
    ss << "4. Trabajar" << endl;
    ss << "5. Ver estado" << endl;
    ss << "6. Volver al menu principal" << endl;
    ss << "\nElige una accion (1-6): ";
    return ss.str();
}

string generar_pantalla_juego(Tamagotchi* mascota) {
    stringstream ss;
    ss << "\n Nombre: " << mascota->getNombre() << endl;
    ss << " Felicidad: " << mascota->getFelicidad() << "/100";
    for (int i = 0; i < mascota->getFelicidad() / 10; i++) ss << "█";
    ss << endl;
    ss << " Energia:   " << mascota->getEnergia() << "/100";
    for (int i = 0; i < mascota->getEnergia() / 10; i++) ss << "█";
    ss << endl;
    ss << " Salud:     " << mascota->getSalud() << "/100";
    for (int i = 0; i < mascota->getSalud() / 10; i++) ss << "█";
    ss << endl;
    ss << " Dinero:    $" << mascota->getDinero() << endl;
    return ss.str();
}

int main() {
    srand(time(nullptr));
    Tamagotchi* mascota = nullptr;
    AnimacionDisplay* animacion = nullptr;
    DisplayLayout* layout = new DisplayLayout(80, 30, 60); // 80 de ancho, 30 de alto, 60% superior
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
            // Mostrar animación arriba y menú abajo
            string menu_str = generar_menu_acciones();
            string estado_str = generar_pantalla_juego(mascota);
            string contenido_completo = estado_str + "\n" + menu_str;
            
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

            // Actualizar estado cada acción
            if (mascota != nullptr) {
                mascota->actualizar();
            }

            if (mascota != nullptr && !mascota->estaVivo()) {
                system("clear");
                cout << "\n╔════════════════════════════════════════╗" << endl;
                cout << "║  ¡Tu Tamagotchi ha muerto!            ║" << endl;
                cout << "║  No cuidaste bien a tu mascota :(      ║" << endl;
                cout << "╚════════════════════════════════════════╝" << endl;
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