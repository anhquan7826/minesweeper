#ifndef CLASS_TEXTURE
#define CLASS_TEXTURE

#include <SDL.h>
#include <string>

using namespace std;

class Texture {
    private:
        SDL_Texture* texture;
        int x;
        int y;
        int w; 
        int h;
        int a;
    public:
        Texture();
        void free();
        int getWidth();
        int getHeight();
        void setDimension(int _x, int _y, int _w, int _h);
        void setAlpha(Uint8 alpha);
        bool loadFromFile(SDL_Renderer* gRenderer, string path);
        void render(SDL_Renderer* gRenderer);
        bool isTextureNULL();
};

#endif