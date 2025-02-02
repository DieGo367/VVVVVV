#ifndef GRAPHICSRESOURCES_H
#define GRAPHICSRESOURCES_H

#include <SDL.h>

enum TextureLoadType
{
    TEX_COLOR,
    TEX_WHITE,
    TEX_GRAYSCALE
};

#ifdef __NDS__
typedef struct {
    void *gfx;
    size_t gfxSize;
    u16 *palette;
    size_t paletteSize;
    u16 *map;
} Tileset;
typedef struct {
	u16 w, h;
	u8 bpp;
	u8 alphaMod;
	u16 colorMod;
	u16 *palette;
	u8 *gfx;
} Bitmap;
#endif

class GraphicsResources
{
public:
    void init(void);
    void destroy(void);

    void init_translations(void);

    #ifdef __NDS__
    Tileset *im_tiles;
    Tileset *im_tiles2;
    Tileset *im_tiles3;
    Bitmap* im_entcolours;
    Bitmap* im_entcolours_tint;
    u16 *im_sprites;
    u16 *im_flipsprites;
    u16 *im_teleporter;
    Bitmap* im_image0;
    Bitmap* im_image1;
    Bitmap* im_image2;
    Bitmap* im_image3;
    Bitmap* im_image4;
    Bitmap* im_image5;
    Bitmap* im_image6;
    Bitmap* im_image7;
    Bitmap* im_image8;
    Bitmap* im_image9;
    Bitmap* im_image10;
    Bitmap* im_image11;
    Bitmap* im_image12;

    Bitmap* im_sprites_translated;
    Bitmap* im_flipsprites_translated;
    #else
    SDL_Surface* im_sprites_surf;
    SDL_Surface* im_flipsprites_surf;

    SDL_Texture* im_tiles;
    SDL_Texture* im_tiles_white;
    SDL_Texture* im_tiles_tint;
    SDL_Texture* im_tiles2;
    SDL_Texture* im_tiles2_tint;
    SDL_Texture* im_tiles3;
    SDL_Texture* im_entcolours;
    SDL_Texture* im_entcolours_tint;
    SDL_Texture* im_sprites;
    SDL_Texture* im_flipsprites;
    SDL_Texture* im_teleporter;
    SDL_Texture* im_image0;
    SDL_Texture* im_image1;
    SDL_Texture* im_image2;
    SDL_Texture* im_image3;
    SDL_Texture* im_image4;
    SDL_Texture* im_image5;
    SDL_Texture* im_image6;
    SDL_Texture* im_image7;
    SDL_Texture* im_image8;
    SDL_Texture* im_image9;
    SDL_Texture* im_image10;
    SDL_Texture* im_image11;
    SDL_Texture* im_image12;

    SDL_Texture* im_sprites_translated;
    SDL_Texture* im_flipsprites_translated;
    #endif
};

#ifdef __NDS__
Bitmap* LoadImage(const char *filename, TextureLoadType loadtype);
void DestroyImage(Bitmap *image);
#else
SDL_Surface* LoadImageSurface(const char* filename);
SDL_Texture* LoadImage(const char *filename, TextureLoadType loadtype);

bool SaveImage(const SDL_Surface* surface, const char* filename);
#endif
bool SaveScreenshot(void);

#endif /* GRAPHICSRESOURCES_H */
