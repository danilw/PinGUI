#ifndef CLFUNCTION_HPP
#define CLFUNCTION_HPP

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

#include <iostream>
#include <functional>

#include "PinGUI_Vector.hpp"

namespace PinGUI{

    class basicPointer{
        public :
            std::function<void()> _function;

            void exec(){

                if (_function){

                    _function();
                }

            }
    };

     class scrollFuncPointer{
        public :
            std::function<void(PinGUI::Vector2<GUIPos>)> _function;

            void exec(PinGUI::Vector2<GUIPos> vect){

                if (_function){

                    _function(vect);
                }
            }
    };

     class comboBoxFuncPointer{
        public :
            std::function<void(int option)> _function;

            void exec(int option){

                if (_function){

                    _function(option);
                }
            }
    };

}


#endif // CLFUNCTION_HPP
