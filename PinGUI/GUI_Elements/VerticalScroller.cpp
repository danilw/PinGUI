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

#include "VerticalScroller.h"
#include <boost/bind.hpp>

VerticalScroller::VerticalScroller(PinGUI::Vector2<GUIPos> pos, int value, bool* update, std::vector<GUI_Element*>* _ELEMENTS):
    Scroller(pos,update)
{

    PinGUI::Rect tmpRect;
    tmpRect.initPos(pos);

    addSprite(tmpRect,SheetManager::createWindowScroller(value,VERTICAL));

    _collidable = false;

    _ELEMENTS->push_back(this);

    createArrows(_ELEMENTS);
}

VerticalScroller::~VerticalScroller()
{
    //dtor
}

void VerticalScroller::createArrows(std::vector<GUI_Element*>* _ELEMENTS){
    PinGUI::basicPointer f1;
    f1._function = boost::bind(&VerticalScroller::incScroller,this);

    PinGUI::basicPointer f2;
    f2._function = boost::bind(&VerticalScroller::decScroller,this);

    PinGUI::Rect tmpRect;
    tmpRect.w = WINDOW_ARROW_W;
    tmpRect.h = WINDOW_ARROW_H;
    tmpRect.x = getSprite()->getX()+PINGUI_WINDOW_LINE_W;
    tmpRect.y = getSprite()->getY()+PINGUI_WINDOW_LINE_H;

    //Down arrow
    Window_Arrow* tmpArrow = new Window_Arrow(tmpRect,SheetManager::getSurface(BOARD),DOWN);

    tmpArrow->setClickFunction(f1);
    _ARROWS.push_back(tmpArrow);

    //Up arrow
    tmpRect.y = (getSprite()->getY()+getSprite()->getH())-WINDOW_ARROW_H;

    tmpArrow = new Window_Arrow(tmpRect,SheetManager::getSurface(BOARD),UP);
    tmpArrow->setClickFunction(f2);

    _ARROWS.push_back(tmpArrow);

    for (std::size_t i = 0; i < _ARROWS.size(); i++) _ELEMENTS->push_back(_ARROWS[i]);
}

void VerticalScroller::calculateRatio(const int& totalValue){

    int numOfManipulationPixels = getSprite(1)->getY() - (_ARROWS[0]->getSprite()->getY() + _ARROWS[0]->getSprite()->getH());

    _ratio = static_cast<float>(totalValue)/numOfManipulationPixels;

    initNormalizer(totalValue,numOfManipulationPixels);
}

void VerticalScroller::manageScrollerFill(const int& value){

    getSprite(1)->setH(value);
    getSprite(1)->setW(PINGUI_WINDOW_DEFAULT_SCROLLER_W - (PINGUI_WINDOW_LINE_W*2));
    getSprite(1)->setY(_ARROWS[1]->getSprite()->getY() - getSprite(1)->getH());

    getSprite(1)->getGUIRect_P()->realRect = getSprite(1)->getGUIRect_P()->rect;
}

int VerticalScroller::calculateScrollerSize(const int& value, int& totalValue){

    //Percentage of window viewport
    float windowPercentage = static_cast<float>(value)/static_cast<float>(totalValue);

    //Now need the possible length of scroller fill
    int tmpLength = 0;

    tmpLength = _ARROWS[1]->getSprite()->getY()-(_ARROWS[0]->getSprite()->getY()+WINDOW_ARROW_H);

    return tmpLength*windowPercentage;
}

void VerticalScroller::onClick(){

    //Setting the input state
    Input_Manager::setInputState(MANIPULATINGMOD);
    Input_Manager::setState(GUI);
    Input_Manager::createManipulatingModInfo(getSprite(1)->getX(),getSprite(1)->getY(),VERTICAL);
    Input_Manager::initManipulation(_SPRITES[1],_update);

}

void VerticalScroller::checkLimits(){

    if (getSprite(1)->getY()<(_ARROWS[0]->getSprite()->getY()+_ARROWS[0]->getSprite()->getH())){

        getSprite(1)->setY(_ARROWS[0]->getSprite()->getY()+_ARROWS[0]->getSprite()->getH());
    } else if (getSprite(1)->getY() + getSprite(1)->getH() > _ARROWS[1]->getSprite()->getY()){

        getSprite(1)->setY(_ARROWS[1]->getSprite()->getY() - getSprite(1)->getH());
    }

}

void VerticalScroller::decide(){

    if (getSprite(1)->getY()!=_oldPos){

        int diff = 0;

        int  newDiff = getDiff();

        if (newDiff > _oldDiff)
            diff = (newDiff - _oldDiff);
        else
            diff -=  _oldDiff -newDiff;

        diff *= _ratio;

        if (diff>0)
            diff += useNormalizer(PLUS,diff);
        else
            diff += useNormalizer(MINUS,diff);

        PinGUI::Vector2<GUIPos> tmpVec(0,diff);

        _cameraRoll.exec(tmpVec);

        _oldPos = getSprite(1)->getY();
        _oldDiff = newDiff;
    }
}

void VerticalScroller::moveOldPos(const PinGUI::Vector2<GUIPos>& vect){
    _oldPos += vect.y;
}

void VerticalScroller::initOldPos(){
    _oldPos = getSprite(1)->getY();
}

void VerticalScroller::incScroller(){
    getSprite(1)->setY(getSprite(1)->getY() - WINDOW_SCROLLER_ARROW_MOVEMENT);

    manageFunctionality();
}

void VerticalScroller::decScroller(){
    getSprite(1)->setY(getSprite(1)->getY() + WINDOW_SCROLLER_ARROW_MOVEMENT);

    manageFunctionality();
}

int VerticalScroller::getDiff(){

    return (_ARROWS[1]->getSprite()->getY() - (getSprite(1)->getY() + getSprite(1)->getH()));
}

int VerticalScroller::useNormalizer(CHANGER change, int diff){

    int numOfPxs = diff*1;

    switch(change){

        case PLUS : {

            if (_NORMALIZER._PLUS > 0){

                if (_NORMALIZER._PLUS - numOfPxs >=0 ){

                    _NORMALIZER._PLUS -= numOfPxs;
                    _NORMALIZER._MINUS += numOfPxs;

                    return numOfPxs;

                } else {

                    int tmp = _NORMALIZER._PLUS;

                    _NORMALIZER._MINUS += _NORMALIZER._PLUS;
                    _NORMALIZER._PLUS -= _NORMALIZER._PLUS;

                    return tmp;
                }
            }

            break;
        }
        case MINUS : {


            if (_NORMALIZER._MINUS > 0){

                if (_NORMALIZER._MINUS + numOfPxs >=0 ){

                    _NORMALIZER._MINUS += numOfPxs;
                    _NORMALIZER._PLUS -= numOfPxs;

                    return numOfPxs;
                } else {

                    int tmp = _NORMALIZER._MINUS;

                    _NORMALIZER._PLUS += _NORMALIZER._MINUS;
                    _NORMALIZER._MINUS -= _NORMALIZER._MINUS;

                    return -tmp;
                }
            }
            break;
        }
    }
    return 0;
}
