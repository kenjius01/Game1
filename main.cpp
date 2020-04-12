
#include <iostream>
#include <SDL.h>
#include<time.h>
#include "window.h"
#include <vector>
#include <cmath>
#include<SDL_image.h>
#include<SDL_mixer.h>
using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;
Mix_Chunk* sound=nullptr;
const char WINDOW_TITLE[] = "GAME_PONG";
bool va_cham(int gach_x, int gach_y, int gach_w, int gach_h,int  bong_x,int  bong_y,int bong_w,int bong_h, int& bong_step_x, int& bong_step_y){
        if (bong_x+bong_w>= gach_x && bong_x<=gach_x+gach_w &&
            (  (bong_y+bong_h>=gach_y && bong_y+bong_h<=gach_y+5) || (bong_y<=gach_y+gach_h && bong_y>=gach_y+15)  )) {
            bong_step_y=-bong_step_y;

            return true;
        }
         if(bong_y+bong_h>=gach_y && bong_y<=gach_y+gach_h &&
             (  (bong_x+bong_w>= gach_x && bong_x+bong_w<=gach_x+5 ) || (bong_x<=gach_x+gach_w && bong_x>=gach_x+70)  )){
                bong_step_x=-bong_step_x;

                return true;
            }
            return false;

}
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool bong_run=true;
    int so_hang=5,so_cot=10,h=20,w=50,i,j,x,y;
    int vi_tri_y[so_hang][so_cot], vi_tri_x[so_hang][so_cot], so_box=3, danhdau[so_hang][so_cot], mang_gach[so_hang][so_cot];
    int van1_x=200, van1_y=670, bong_step_x=3, bong_step_y=3, bong_x, bong_y, time_gach=0, so_gach_pha=0;
    srand((int) time(NULL));
    bong_x=rand()%700+50;  bong_y=rand()%50+500;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_Texture* gach[so_hang][so_cot];
    SDL_Texture* nen=nullptr;
   SDL_Texture* van1=nullptr;
   SDL_Texture* bong=nullptr;
   for(i=0;i<so_hang;i++)
    for(j=0;j<so_cot;j++)
     danhdau[i][j]=0;
    nen=loadTexture("bgr_bien1.bmp",renderer);
    van1=loadTexturepng("van.png",renderer);
    bong=loadTexturepng("bong1.png",renderer);

      if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1){
            cout<<"LOI MO AM THANH"<<endl;
        return false;
      }
      sound=Mix_LoadWAV("1.wav");
   for(i=0;i<1;i++){
      for(j=0;j<so_cot;j++){
          gach[i][j]=loadTexturepng("gach_2.png",renderer);
          mang_gach[i][j]=5;
      }
   }
   for(i=1;i<3;i++){
      for(j=0;j<so_cot;j++){
          gach[i][j]=loadTexturepng("gach_1.png",renderer);
          mang_gach[i][j]=3;
      }
   }
   for(i=3;i<so_hang;i++){
      for(j=0;j<so_cot;j++){
          gach[i][j]=loadTexturepng("gach.png",renderer);
          mang_gach[i][j]=2;
      }
   }
   vi_tri_x[0][0]=3; vi_tri_y[0][0]=2;
   for(j=1;j<so_cot;j++){
        vi_tri_x[0][j]= vi_tri_x[0][j-1]+80;
        vi_tri_y[0][j]= 2;
        cout<<vi_tri_x[0][j]<<" ";
   }
    for(i=1;i<so_hang;i++){
      for(j=0;j<so_cot;j++){
           vi_tri_x[i][j]= vi_tri_x[i-1][j];
           vi_tri_y[i][j]=vi_tri_y[i-1][j]+35;
      }
   }

    SDL_Event e;
    bool running = true;
    while (running) {
        SDL_Delay(1);
        SDL_RenderClear(renderer);
        renderTexture(nen, renderer,0,0,800,700);
        renderTexture(van1, renderer,van1_x,van1_y,140,30);
        renderTexture(bong, renderer,bong_x,bong_y,20,20);

        for(i=0;i<so_hang;i++){
         for(j=0;j<so_cot;j++){
           renderTexture(gach[i][j],renderer,vi_tri_x[i][j],vi_tri_y[i][j],75,30);
      }
   }

       SDL_UpdateWindowSurface(window);

     // CHUYEN DONG CUA BONG
    if (bong_run) { bong_x-=bong_step_x; bong_y-=bong_step_y;   }

          // VA CHAM BIEN
     if (bong_x<=0|| bong_x+20>=800) bong_step_x=-bong_step_x;
     if (bong_y<=0||(bong_x+20>=van1_x && bong_x<=van1_x+120 && bong_y+20 >=van1_y && bong_y+20<=van1_y+3)) {
            bong_step_y=-bong_step_y;
     }
     // GAME PAUSE
     if(bong_y>=680) {
        bong_run=false;
     }

     // GACH DI CHUYEN
     time_gach++;
    // cout<<time_gach<<endl;
     if(bong_run){

            for(i=0;i<so_hang;i++){
             for(j=0;j<so_cot;j++){
                 if(time_gach==2000)     vi_tri_y[i][j]+=40;
              if( danhdau[i][j]==0 && va_cham(vi_tri_x[i][j],vi_tri_y[i][j],75,30,bong_x,bong_y,20,20,bong_step_x, bong_step_y)) {
                    mang_gach[i][j]--;
              if (mang_gach[i][j]==0){
                Mix_PlayChannel(-1, sound, 0);
                 so_gach_pha++;
                  SDL_DestroyTexture(gach[i][j]);
                  danhdau[i][j]=1;
              }

              }
                     if (vi_tri_y[i][j]+30>= van1_y) running=false;
               }
           }
        if(time_gach>=3000) time_gach=0;

     }
     if(so_gach_pha==50){
         cout<<"WIN:))"<<endl;
         running=false;

     }

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) running = false;
                break;
            }
            if (e.type== SDL_MOUSEMOTION){
                 if(bong_run)   van1_x=e.motion.x-60;
            }
        }

    }
    SDL_DestroyTexture(nen);
    SDL_DestroyTexture(van1);
    SDL_DestroyTexture(bong);
     for(i=0;i<so_hang;i++){
      for(j=0;j<so_cot;j++){
          SDL_DestroyTexture(gach[i][j]);
      }
   }
    quitSDL(window, renderer);
    return 0;
}
