#include "Window.h"
//#include "Menu.h"
#include "Button.h"

#include <stdlib.h>

Window::Window(const char* titleWindow, const int widhtWindow, const int heightWindow, const Uint32 flags) : m_title(titleWindow), m_width(widhtWindow),
                                                                                             m_height(heightWindow), m_flags(flags), m_window(0), m_renderer(0), m_input(), m_play(m_renderer,250,100,300,50), m_quit(m_renderer,250,300,300,50)
{

}

Window::~Window()
{
    //dtor
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

// initialise SDL2
void Window::initWindow()
{
    // Init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        exit(EXIT_FAILURE);
    }


    // Cr�ation de la fen�tre
    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, m_flags);

    if(m_window == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        exit(EXIT_FAILURE);
    }


    // Cr�ation du renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(m_renderer == NULL)
    {
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);

        if(m_renderer == NULL)
        {
            std::cout << "Erreur lors de la cr�ation du renderer : " << SDL_GetError() << std::endl;
            SDL_Quit();

            exit(EXIT_FAILURE);
        }

        std::cout << "Warning! RENDERER SOFTWARE ENABLED" << std::endl;
    }
    int IMGflags = IMG_INIT_PNG;
    if (! ( IMG_Init(IMGflags) & IMGflags ))
        {
            std::cout << "Erreur : " << IMG_GetError();
            std::cout << std::endl;
            IMG_Quit();
        }
        else
        {
            m_jouer = Texture::Charger("data/jouer.png",m_renderer);
            m_quitter = Texture::Charger("data/quitter.png",m_renderer);
        }


}

SDL_Window* Window::getWindow()
{
    return m_window;
}

void Window::AffJeu()
{
    SDL_SetRenderDrawColor(m_renderer,0,255,255,255);
    SDL_RenderClear(m_renderer);

    SDL_RenderCopy(m_renderer,m_jouer,NULL,m_play.getSDL_Rect());
    SDL_RenderCopy(m_renderer,m_quitter,NULL,m_quit.getSDL_Rect());
    SDL_RenderPresent(m_renderer);
}

void Window::mainloop()
{
    // Variables framerate
    unsigned int frameRate (1000 / 50);
    float debutBoucle(0), finBoucle(0), tempsEcoule(0);

    //Menu mainMenu(m_renderer, m_height, m_width);

    // Boucle principale
    while(!m_input.terminer())
    {
        // On d�finit le temps de d�but de boucle
        debutBoucle = SDL_GetTicks();


        // *** Gestion des �v�nements ***
        m_input.updateEvenements();

        // Fermer la fen�tre
        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
        {
            bool b = true;
            m_input.SetTerminer(b);
        }
        // *** Affichage ***
        //SDL_RenderClear(m_renderer);


        if(m_play.estTouche(m_input.getX(),m_input.getY()))
        {
           if (m_input.getBoutonSouris(SDL_MOUSEBUTTONDOWN))
           {

           }
        }
        else if (m_quit.estTouche(m_input.getX(),m_input.getY()))
        {
           if (m_input.getBoutonSouris(SDL_MOUSEBUTTONDOWN))
           {
               SDL_HideWindow(m_window);
           }
        }


        // Affichage du renderer
        //SDL_SetRenderDrawColor(m_renderer, 0,0,0,0);



        // *** Framerate ***

        // Calcul du temps �coul�
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;
        //std::cout<< tempsEcoule <<std::endl;

        // Si n�cessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }

}



void Window::Update()
{
    initWindow();
    while(!m_input.terminer())
    {
        AffJeu();
        mainloop();
    }
}
