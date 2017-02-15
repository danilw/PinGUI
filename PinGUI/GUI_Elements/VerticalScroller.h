#ifndef VERTICALSCROLLER_H
#define VERTICALSCROLLER_H

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


#include "../GUI_Elements/Scroller.h"

class VerticalScroller: public Scroller
{
    private:

        /** Private methods **/
        int useNormalizer(CHANGER change, int diff) override;

        void checkLimits() override;

        int calculateScrollerSize(const int& value, int& totalValue) override;

        void manageScrollerFill(const int& value) override;

        void calculateRatio(const int& totalValue) override;

        void decide() override;

        void initOldPos() override;

        void incScroller() override;

        void decScroller() override;

        void moveOldPos(const PinGUI::Vector2<GUIPos>& vect) override;

        int getDiff() override;


        //From GUI_Element
        void onClick() override;


    public:
        VerticalScroller(PinGUI::Vector2<GUIPos> pos, int value, bool* update, std::vector<GUI_Element*>* _ELEMENTS);
        ~VerticalScroller();

        void createArrows(std::vector<GUI_Element*>* _ELEMENTS) override;
};

#endif // VERTICALSCROLLER_H
