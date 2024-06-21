    #include <SDL2/SDL.h>
    #include <stdio.h>
    #include "xwindow.h"
      #include "sdl.h"

     /************************************/
     /*Intialisation des fenetres        */
     /************************************/

#define I 10
#define N 10



     /************************************/
     /*  La fonction Main */
     /************************************/

     int mainxwindow(int argc, char **argv) {
       (void)argc;
       (void)argv;
      // SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
      int i=0;
      char title[12];
      SDL_Window * window[I];
      
      
      

     
      for ( i = 0; i < I/2; i++)
      {
         if (i<(I/2))
         {
            window[i]= creationwindow(title, i*400, 0, 300, 300);
         }
         else if (i>=(I/2))
         {
            
            window[i]= creationwindow(title, i*400, 800, 300, 300);
         }
         sprintf(title, "Window %d", i);
         
      }
      

     /************************************/
      // Deplacemment des fenetres
     /************************************/

      SDL_DisplayMode screen ;
      SDL_GetCurrentDisplayMode(0,&screen); 
      printf("Screen resolution: %dx%d\n",screen.w,screen.h);


    int step = screen.h / N;


    for (i = 0; i < I ; i++) {
        
            int xpos, ypos;

            if (i< I/2)
            {
               for (int j = 0; j <= i; j++) {
                // Déplacement de la fenêtre inf a 5
            SDL_GetWindowPosition(window[i], &xpos, &ypos);
            printf("Fenêtre %d: position avant déplacement: (%d, %d)\n", i, xpos, ypos);
            SDL_SetWindowPosition(window[i], xpos, ypos + step);
            SDL_GetWindowPosition(window[i], &xpos, &ypos);
            printf("Fenêtre %d: position après déplacement: (%d, %d)\n", i, xpos, ypos);

               }
            }
            else if (i>= I/2)    
            {
               for (int j = 0; j <= i; j++) {
                // Déplacement de la fenêtre sup ou egale a 5
            SDL_GetWindowPosition(window[i ], &xpos, &ypos);
            printf("Fenêtre %d: position avant déplacement: (%d, %d)\n", i , xpos, ypos);
            SDL_SetWindowPosition(window[i ], xpos, ypos - step);
            SDL_GetWindowPosition(window[i ], &xpos, &ypos);
            printf("Fenêtre %d: position après déplacement: (%d, %d)\n", i , xpos, ypos);
               }
         
            }
    }


      SDL_Delay(5000);                           // Pause exprimée  en ms

     /************************************/
      // Fermetures des fenetres
     /************************************/
      for (int i = 0; i < I; i++)
      {
         SDL_DestroyWindow(window[i]);
      }
      
      SDL_Quit();                                // la SDL
 
       return 0;
     }

      

      