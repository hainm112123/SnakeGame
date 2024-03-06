#include <bits/stdc++.h>
#include "gallery.h"

using namespace std;

Gallery::Gallery(Painter &_painter): painter(_painter) {
    loadGamePictures();
}

Gallery::~Gallery() {
    for (SDL_Texture* texture: pictures) SDL_DestroyTexture(texture);
}

void Gallery::loadGamePictures() {
    pictures = {
        painter.loadTexture("./Graphics/apple.png"),
        painter.loadTexture("./Graphics/body_horizontal.png"),
        painter.loadTexture("./Graphics/body_vertical.png"),
        painter.loadTexture("./Graphics/head_up.png"),
        painter.loadTexture("./Graphics/head_down.png"),
        painter.loadTexture("./Graphics/head_left.png"),
        painter.loadTexture("./Graphics/head_right.png"),
        painter.loadTexture("./Graphics/tail_up.png"),
        painter.loadTexture("./Graphics/tail_down.png"),
        painter.loadTexture("./Graphics/tail_left.png"),
        painter.loadTexture("./Graphics/tail_right.png"),
        painter.loadTexture("./Graphics/body_bottomleft.png"),
        painter.loadTexture("./Graphics/body_bottomright.png"),
        painter.loadTexture("./Graphics/body_topleft.png"),
        painter.loadTexture("./Graphics/body_topright.png"),
    };
}
