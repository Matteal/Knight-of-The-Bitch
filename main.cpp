#include <SDL2/SDL.h>
#include <iostream>

#include "Window.h"



int main(int argc, char **argv)
{
    // Cr�ation de la sc�ne

    Window window("SDL2", 800, 500, SDL_WINDOW_SHOWN);

    // Initialisation de la sc�ne
    window.initWindow();

    // Boucle Principale
    window.mainloop();


    return 0;
}
