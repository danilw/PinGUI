# PinGUI

15 feb 2017

fork of https://github.com/Pinsius/PinGUI

I make it work for linux and fix evrythink for build it and launch demo

Extensions you need: SDL2,SDL2_image,SDL2_TTF,GLEW,glm

To build demo- open terminal in demo folder, write to terminal:

>g++  ../PinGUI/TextManager/Text.cpp ../PinGUI/TextManager/TextStorage.cpp ../PinGUI/TextManager/TextManager.cpp ../PinGUI/GUI_Elements/ArrowBoard.cpp ../PinGUI/GUI_Elements/Button.cpp ../PinGUI/GUI_Elements/ClipBoard.cpp ../PinGUI/GUI_Elements/ComboBox.cpp ../PinGUI/GUI_Elements/ComboBoxItem.cpp ../PinGUI/GUI_Elements/CrossBox.cpp ../PinGUI/GUI_Elements/HorizontalScroller.cpp ../PinGUI/GUI_Elements/Image.cpp ../PinGUI/GUI_Elements/Scroller.cpp ../PinGUI/GUI_Elements/VerticalScroller.cpp ../PinGUI/GUI_Elements/VolumeBoard.cpp ../PinGUI/GUI_Elements/Window.cpp ../PinGUI/GUI_Elements/Window_Arrow.cpp ../PinGUI/GUI_Elements/WindowButton.cpp ../PinGUI/GUI_Elements/WindowExit.cpp ../PinGUI/GUI_Elements/WindowMover.cpp ../PinGUI/GUI_Elements/WindowTab.cpp ../PinGUI/CameraManager.cpp ../PinGUI/CropManager.cpp ../PinGUI/ErrorManager.cpp ../PinGUI/GL_Vertex.cpp ../PinGUI/GUI_CollisionManager.cpp ../PinGUI/GUI_ColorManager.cpp ../PinGUI/GUI_Cursor.cpp ../PinGUI/GUI_Element.cpp ../PinGUI/GUIManager.cpp ../PinGUI/GUI_Sprite.cpp ../PinGUI/Input_Manager.cpp ../PinGUI/PINGUI.cpp ../PinGUI/Shader_Program.cpp ../PinGUI/SheetManager.cpp ../PinGUI/VBO_Manager.cpp  FPS_Timer.cpp main.cpp -o demo -std=gnu++14 -lstdc++ -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLEW

>cp -ar ../PinGUI/Shaders/ Shaders

>cp -ar ../PinGUI/TextManager/ TextManager

>cd TextManager

>rm -f *{.h,.cpp}

>cd ..

>./demo

Tested and its work!

( I did not fix memory leaks and other bugs, fixes only to make it work )

![Alt text](/itsok.png?raw=true "Work")