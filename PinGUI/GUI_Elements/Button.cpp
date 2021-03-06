/**

    PinGUI

    Copyright (c) 2017 Lubomir Barantal <l.pinsius@gmail.com>

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

**/

#include "Button.h"


Button::Button(int x, int y, std::string name, PinGUI::basicPointer f, clipboardData data)
{
    _position.x = x;
    _position.y = y;

    _func = f;

    _maxSize = name.size();

    initSprites(name,data);
}

Button::Button(int x, int y, std::string name, PinGUI::basicPointer f, clipboardData data, int maxSize)
{
    _maxSize = maxSize;

    _position.x = x;
    _position.y = y;

    _func = f;

    initSprites(name,data);
}

Button::Button(int x, int y, std::string name, clipboardData data)
{
    _maxSize = name.size();

    _position.x = x;
    _position.y = y;

    initSprites(name,data);
}

Button::~Button()
{
    //dtor
}

void Button::initSprites(std::string name, clipboardData& data){

    SDL_Surface* tmpSurface;
    int tmp_width, tmp_height;

    fakeInputText(tmp_width,tmp_height,data);

    addCollider(_position.x,_position.y,tmp_width,tmp_height);

    _textStorage = new TextStorage(data.texter);
    initText();

    tmpSurface = SheetManager::createClipBoard(tmp_width,tmp_height);

    addSprite(_position.x,_position.y,tmpSurface);

    setClipboardText(name);

    getSprite()->setColor(0,255,0);
    getSprite()->setAlpha(75);
}

void Button::onClick(){

    _func.exec();
}

void Button::onAim(){

    //Define with your behavior..

}

void Button::onEndAim(){

    //Define with your behavior..
}

void Button::setWritingAvailability(bool state){

    if (state){
        getSprite()->setColor(0,255,0);
        getSprite()->setAlpha(150);
    } else {
        getSprite()->setAlpha(75);
    }
}

bool Button::listenForClick(GUI_Element** manipulatingElement){

    GUI_Element::listenForClick(manipulatingElement);
}
