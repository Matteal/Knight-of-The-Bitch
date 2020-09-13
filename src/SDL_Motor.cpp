#include "SDL_Motor.h"

SDL_Motor::SDL_Motor() : m_window("SDL2", 800, 500, SDL_WINDOW_SHOWN), m_input(), m_renderer(), /* TODO : Move this */ m_play(NULL,250,100,300,50), m_quit(NULL,250,300,300,50)
{
    // ctor
}

SDL_Motor::~SDL_Motor()
{
    //dtor
}

bool SDL_Motor::init()
{
    if(!m_window.initWindow())
    {
        return false;
    }

    m_play = Button(m_window.getRenderer(),250,100,300,50);
    m_quit = Button(m_window.getRenderer(),250,300,300,50);

    // Loading Textures
    m_textureArray[0] = chargerTexture("data/jouer.png",m_window.getRenderer());
    m_textureArray[1] = chargerTexture("data/quitter.png",m_window.getRenderer());

    // Keep this after any renderer modification
    m_renderer = m_window.getRenderer();

    return true;
}

void SDL_Motor::mainloop()
{

    // Framerate variables
    unsigned int frameRate (1000 / 50);
    float debutBoucle(0), finBoucle(0), tempsEcoule(0);

    // Core Loop
    while(!m_input.terminer())
    {
        std::cout<<"Debug"<<std::endl;


        // Defining timestamp
        debutBoucle = SDL_GetTicks();


        // *** Managing Events ***
        m_input.updateEvenements();

        // Close the window when asked
        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
        {
            m_input.SetTerminer(true);
        }


        // *** GRAPHICS ***

        // Clear the SDL_Renderer
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer,0,255,255,255);

        // Render
        SDL_RenderCopy(m_renderer,m_textureArray[0],NULL,m_play.getSDL_Rect());
        SDL_RenderCopy(m_renderer,m_textureArray[1],NULL,m_quit.getSDL_Rect());
        SDL_RenderPresent(m_renderer);


        // Affichage du renderer
        //SDL_SetRenderDrawColor(m_renderer, 0,0,0,0);





        // *** FRAMERATE ***

        // Calcul du temps �coul�
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;
        //std::cout<< tempsEcoule <<std::endl;

        // Si n�cessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}



SDL_Texture* chargerTexture(const std::string &chemin, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(chemin.c_str());
    if (surface == NULL)
    {
        std::cout << "Erreur de chargement de surface " <<std::endl;
        return NULL;
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
        return texture;
    }
}
