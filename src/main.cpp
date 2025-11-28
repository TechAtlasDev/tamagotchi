#include <ctime>
#include <cstdlib>
#include "Game.hpp"

int main() {
    srand(time(nullptr));
    Game juego(80, 30);
    juego.play();
    return 0;
}