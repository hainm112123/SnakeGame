#ifndef GALLERY_H_INCLUDED
#define GALLERY_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Painter.h"

using namespace std;

enum PictureID {
    PIC_CHERRY = 0,
    PIC_BODY_HORIZONTAL,
    PIC_BODY_VERTICAL,
    PIC_HEAD_UP,
    PIC_HEAD_DOWN,
    PIC_HEAD_LEFT,
    PIC_HEAD_RIGHT,
    PIC_TAIL_UP,
    PIC_TAIL_DOWN,
    PIC_TAIL_LEFT,
    PIC_TAIL_RIGHT,
    PIC_BODY_BOTTOM_LEFT,
    PIC_BODY_BOTTOM_RIGHT,
    PIC_BODY_TOP_LEFT,
    PIC_BODY_TOP_RIGHT,
};

class Gallery {
    vector<SDL_Texture*> pictures;
    Painter &painter;
public:
    Gallery(Painter &_painter);
    ~Gallery();

    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const {
        return pictures[id];
    }
};

#endif // GALLERY_H_INCLUDED
