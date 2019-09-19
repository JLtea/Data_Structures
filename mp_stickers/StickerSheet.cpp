#include "StickerSheet.h"




StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    base = picture;
    maxStickers=max;
    stickers = new Image*[max];
    coordX = new int[max];
    coordY = new int[max];
}

StickerSheet::~StickerSheet(){

    delete[] stickers;
    delete[] coordX;
    delete[] coordY;
}

StickerSheet::StickerSheet(const StickerSheet & other){
    this->base = other.base;
    this->maxStickers = other.maxStickers;
    this->stickers = other.stickers;
    this->coordX = other.coordX;
    this->coordY = other.coordY;
}
const StickerSheet & StickerSheet::operator= (const StickerSheet & other) {
    this->base = other.base;
    this->maxStickers = other.maxStickers;
    this->stickers = other.stickers;
    this->coordX = other.coordX;
    this->coordY = other.coordY;
    return *this;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    int ind = 0;
    bool added = false;
    if(x > base.width() || y > base.height()){
        base.scale(x + sticker.width(),y + sticker.height());

    }
    if (stickers[0] == NULL) {
        *stickers[0] = sticker;
        coordX[0] = x;
        coordY[0] = y;
        added = true;
    } else {
        while(stickers[ind] != NULL && ind < (maxStickers - 1)&& added == false){
            ind++;
            if (stickers[ind] == NULL){
                *stickers[ind] = sticker;
                coordX[ind] = x;
                coordY[ind] = y;
                added = true;
            }

        }
    }
    if(!added) {
        ind = -1;
    }
    return ind;
    
}

void StickerSheet::changeMaxStickers(unsigned max) {
    Image** changed = new Image*[max];
    int upto;
    if ((int)max > maxStickers){
        for(int i = 0; i < maxStickers; i++){
            *changed[i] = *stickers[i];
        }
    } else {
        for (int i = 0; i < maxStickers; i++) {
            if (i < (int)max) {
                *changed[i] = *stickers[i];
            } else {
                removeSticker(i);
            }
        }
    }
    delete[] stickers;
    stickers = changed;
    maxStickers = max;
}

Image* StickerSheet::getSticker(unsigned index) {
    if (maxStickers < (int)index || (int)index < 0) {
        return NULL;
    } else {
        return stickers[index];
    }
}

void StickerSheet::removeSticker(unsigned index) {
    if (0<index<maxStickers) {
        if (stickers[index] != NULL){
            delete stickers[index];
        }
    }
    
}

Image StickerSheet::render() const {
    Image rendered = base;
    //rendered.resize(base.width(),base.height());
    // for(unsigned x = 0; x < base.width(); x++){
    //     for(unsigned y = 0; y < base.height(); y++){
    //         rendered.getPixel(x,y) = base.getPixel(x,y);
    //     }
    // }
    for(int h = 0; h < maxStickers; h++) {
        if (stickers[h] != NULL){
            Image* current = stickers[h];
            for(unsigned i = 0; i < current->width(); i++){
                for(unsigned j = 0; j < current->height(); j++){
                    rendered.getPixel(coordX[h] + i, coordY[h] + j) = stickers[h]->getPixel(i,j);
                }
            }
        }
    }
    return rendered;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if(0<index<maxStickers){
        coordX[index] = x;
        coordY[index] = y;
        return true;
    } else {
        return false;
    }
}
