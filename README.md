# Tamagotchi

Proyecto de una mascota virtual inspirada en los Tamagotchi clásicos. El usuario puede alimentar, jugar y cuidar a su mascota para mantenerla feliz y saludable.

## Características técnicas

- Lenguaje: C++

## Desafíos

- No depender de ninguna librería externa.
- Mantener el código limpio y bien documentado.
- Hacer el código modular para facilitar futuras expansiones.
- Mostrar al tamagochi y todo tipo de información en consola usando solo caracteres ASCII.

## Experimentos

Antes de implementar una version definitiva de ciertas funcionalidades, tienes que realizar diferentes pruebas, estas pruebas estarán en la carpeta `experiments`.

## Cómo ejecutar el proyecto
1. Clona el repositorio:
   ```
   git clone https://github.com/TechAtlasDev/tamagotchi.git
    ```
2. Navega al directorio del proyecto:
    ```
    cd tamagotchi
    ```
3. Compila el código fuente:
    ```
    g++ -std=c++11 -o tamagotchi src/main.cpp src/Display.cpp src/Tamagotchi.cpp src/Inventario.cpp
    ```
4. Ejecuta el programa:
    ```
    ./tamagotchi
    ```

## Estructura del Proyecto

```
src/
├── main.cpp              # Programa principal con menú interactivo
├── Display.hpp/.cpp      # Clase para renderizar en pantalla ASCII
├── Tamagotchi.hpp/.cpp   # Clase base de la mascota virtual
└── Inventario.hpp/.cpp   # Subclases Pou y Gato

assets/
└── Gato/
    └── Frame1-6.txt      # Animaciones ASCII del gato
```

## Excalidraw

https://excalidraw.com/#room=45361e09e609fb7e2ea0,aS6-pik6p9JBNu-CQvpeVA