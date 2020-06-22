#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
typedef struct Score{
	int s1;
	int s2;
	int choix;
}score;

void concat(char* s1, char* s2, char* ns) {
    ns[0] = '\0';
    strcpy(ns, s1);
    strcat(ns, s2);
}

int main(){
	score scoreBefore;
	score scoreAfter;
	scoreBefore.s1=0;
	scoreBefore.s2=0;
	scoreBefore.choix=0;
	char *m;
	m=malloc(50*sizeof(char));
	m="nombre de points : ";
	char s[50];
	char *nbr;
        nbr=malloc(5*sizeof(char));

	int i;
        int socketClient=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in addrClient;
        addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
        addrClient.sin_family = AF_INET;
        addrClient.sin_port = htons(30000);
        connect(socketClient, (const struct sockaddr *)&addrClient,sizeof(addrClient));
	/***********************/
	SDL_Window *window =NULL;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Renderer *renderer=NULL;
	SDL_Texture *texture=NULL;
	SDL_Texture *texture1=NULL;
	SDL_Texture *texture2=NULL;
	SDL_Rect dest_rect0={50,50,150,150};
	SDL_Rect dest_rect_0={58,58,128,128};

	SDL_Rect dest_rect1={250,50,150,150};
	SDL_Rect dest_rect2={450,50,150,150};

	SDL_Rect dest_rect_1={258,58,128,128};
        SDL_Rect dest_rect_2={458,58,128,128};

	SDL_Rect dest_rect00={50,250,150,150};
        SDL_Rect dest_rect11={250,250,150,150};
        SDL_Rect dest_rect22={450,250,150,150};

	SDL_Rect dest_rect_00={58,258,128,128};
        SDL_Rect dest_rect_11={258,258,128,128};
        SDL_Rect dest_rect_22={458,258,128,128};

	 if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }
	window=SDL_CreateWindow("Bienvenue dans le jeu de chifoumi ",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,650,420,SDL_WINDOW_SHOWN);
	renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);
	if(renderer==NULL)
		printf("renderer");

	texture=IMG_LoadTexture(renderer,"images1/leaf3.png");
	texture1=IMG_LoadTexture(renderer,"images1/stone2.png");
	texture2=IMG_LoadTexture(renderer,"images1/scissors2.png");
	//SDL_SetTextureColorMod(texture, 64, 64, 64 );
		TTF_Font *Sans=NULL;
		if ( TTF_Init() == -1 )
			printf("TTF_Init: %s\n", TTF_GetError());
	Sans = TTF_OpenFont("arial.ttf",10);
	if(Sans==NULL)
		printf("TTF_Initiii: %s\n", TTF_GetError());

	SDL_Color White = {0, 0, 0};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, m, White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_Rect Message_rect={200,0,150,15};
	SDL_Rect Message_rect1={200,210,150,15};

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect1);

	int t=128;
	SDL_QueryTexture(texture, NULL, NULL, &t, &t);	
	SDL_QueryTexture(texture1, NULL, NULL, &dest_rect_1.w, &dest_rect_1.h);
	SDL_QueryTexture(texture2, NULL, NULL, &dest_rect_2.w, &dest_rect_2.h);
	SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_RenderDrawRect(renderer,&dest_rect0);
	SDL_RenderDrawRect(renderer,&dest_rect2);
	SDL_RenderDrawRect(renderer,&dest_rect1);
	SDL_RenderDrawRect(renderer,&dest_rect00);
        SDL_RenderDrawRect(renderer,&dest_rect22);
        SDL_RenderDrawRect(renderer,&dest_rect11);
	SDL_RenderCopy(renderer,texture,NULL,&dest_rect_0);
	SDL_RenderCopy(renderer,texture1,NULL,&dest_rect_1);
	SDL_RenderCopy(renderer,texture2,NULL,&dest_rect_2);
	SDL_RenderCopy(renderer,texture,NULL,&dest_rect_00);
        SDL_RenderCopy(renderer,texture1,NULL,&dest_rect_11);
        SDL_RenderCopy(renderer,texture2,NULL,&dest_rect_22);
	SDL_RenderPresent(renderer);
	bool isRunning=true;
	SDL_Event ev;
	int c;
	SDL_Delay(5000);
	int x,y;
	while(isRunning)
	{
		i=-1;
		while(SDL_PollEvent(&ev)!=0)
		{
			if(ev.type==SDL_QUIT)
				isRunning = false;
			if(ev.type==SDL_MOUSEBUTTONDOWN)
			{
				x=ev.button.x;
				y=ev.button.y;
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
				if(y>50 && y<200 && x>50 && x<200)
				{
					i=1;
					//send(socketClient,&i,sizeof(int),0);
					SDL_RenderDrawRect(renderer,&dest_rect0);
				}
				else if(y>50 && y<200 && x>250 && x<400)
				{
					i=2;
                                       //send(socketClient,&i,sizeof(int),0);
				       SDL_RenderDrawRect(renderer,&dest_rect1);
				}
				else if(y>50 && y<200 && x>450 && x<600)
				{ 
					i=3;
                                       //send(socketClient,&i,sizeof(int),0);
				       SDL_RenderDrawRect(renderer,&dest_rect2);
				}
				SDL_RenderPresent(renderer);
				if(i!=-1)
					send(socketClient,&i,sizeof(int),0);
				SDL_UpdateWindowSurface(window);
			}

		}
		if(i!=-1)
		{
			while(recv(socketClient,&scoreAfter,sizeof(score),0)==0);
			printf("s1.s1  %d\n",scoreAfter.s1);
			printf("s1.s2  %d\n",scoreAfter.s2);
			printf("s1.choix %d\n",scoreAfter.choix);
			if(scoreAfter.s1>scoreBefore.s1)
			{
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
				if(i==1)
					SDL_RenderDrawRect(renderer,&dest_rect0);
				else if(i==2)
					SDL_RenderDrawRect(renderer,&dest_rect1);
				else
					SDL_RenderDrawRect(renderer,&dest_rect2);
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
				if(scoreAfter.choix==1)
					SDL_RenderDrawRect(renderer,&dest_rect00);
				else if(scoreAfter.choix==2)
					SDL_RenderDrawRect(renderer,&dest_rect11);
                                else
					SDL_RenderDrawRect(renderer,&dest_rect22);
					SDL_RenderPresent(renderer);
			}else if(scoreAfter.s2>scoreBefore.s2)
                               {
                                        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
                                        if(i==1)
                                                SDL_RenderDrawRect(renderer,&dest_rect0);
                                        else if(i==2)
                                                SDL_RenderDrawRect(renderer,&dest_rect1);
                                        else
                                                SDL_RenderDrawRect(renderer,&dest_rect2);
                                        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
					printf("%d",scoreAfter.choix);
                                        if(scoreAfter.choix==1)
                                                SDL_RenderDrawRect(renderer,&dest_rect00);
                                        else if(scoreAfter.choix==2)
                                                SDL_RenderDrawRect(renderer,&dest_rect11);
                                        else
                                                SDL_RenderDrawRect(renderer,&dest_rect22);

                                        SDL_RenderPresent(renderer);
                                }
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0x00);
                                        if(i==1)
                                                SDL_RenderDrawRect(renderer,&dest_rect0);
                                        else if(i==2)
                                                SDL_RenderDrawRect(renderer,&dest_rect1);
                                        else
                                                SDL_RenderDrawRect(renderer,&dest_rect2);
                                        if(scoreAfter.choix==1)
                                                SDL_RenderDrawRect(renderer,&dest_rect00);
                                        else if(scoreAfter.choix==2)
                                                SDL_RenderDrawRect(renderer,&dest_rect11);
                                        else
                                                SDL_RenderDrawRect(renderer,&dest_rect22);

                                        SDL_RenderPresent(renderer);
					SDL_UpdateWindowSurface(window);

			}
			scoreBefore.s1=scoreAfter.s1;
			scoreBefore.s2=scoreAfter.s2;
			scoreBefore.choix=scoreAfter.choix;
			SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
                        SDL_FillRect(screenSurface, &Message_rect, SDL_MapRGB(screenSurface->format, 200, 200, 200));
                        SDL_FillRect(screenSurface, &Message_rect1, SDL_MapRGB(screenSurface->format, 200, 200, 200));
                        SDL_RenderPresent(renderer);
			if(scoreAfter.s2==2)
			{
				concat("malheuresement, vous avez perdu","",s);
			}
			else if(scoreAfter.s1!=2)
			{
				sprintf(nbr, "%d", scoreAfter.s1);
                        	printf("%s",nbr);
                        	concat(m,nbr,s);
			}
			else 
				concat("bravo, vous avez gagne","",s);
                        surfaceMessage = TTF_RenderText_Solid(Sans, s, White);
                        Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
			sprintf(nbr, "%d", scoreAfter.s2);
                        printf("%s",nbr);
                        concat(m,nbr,s);
                        surfaceMessage = TTF_RenderText_Solid(Sans, s, White);
                        Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                        SDL_RenderCopy(renderer, Message, NULL, &Message_rect1);

			SDL_Delay(2000);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		        //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
		        SDL_RenderDrawRect(renderer,&dest_rect0);
      	 		SDL_RenderDrawRect(renderer,&dest_rect2);
     			SDL_RenderDrawRect(renderer,&dest_rect1);
		        SDL_RenderDrawRect(renderer,&dest_rect00);
     			SDL_RenderDrawRect(renderer,&dest_rect22);
      			SDL_RenderDrawRect(renderer,&dest_rect11);
			SDL_RenderPresent(renderer);
		}

		//SDL_Delay(10000);
		SDL_UpdateWindowSurface(window);
	}
	close(socketClient);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
