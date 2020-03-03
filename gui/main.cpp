#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>

// For Windows using the gcc compiler (most of you)
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"

//For Mac, if the above doesn't work, you can try this:
//#pragma clang diagnostic ignored "-Wsign-conversion"
//#pragma clang diagnostic ignored "-Wsign-compare"

using namespace std;
using namespace mssm;   // <------ this is important

// Notes:
// 1. Your program will go in the function graphicsMain instead of main (but you
// must have a main function like the one at the bottom of this file)
//
// 2. All of the drawing functions (line, ellipse, text, point, etc) are
// methods on the Graphics object
//
// 3. There is a new type "Vec2d" that represents a pair of x,y coordinates.  Many
// drawing functions are overloaded to take either Vec2d's or individual x and y
// components.
//
// 4. The type "Graphics" must always be passed by reference...
// Pass in the graphics object g to any function that needs to do drawing
//
// 5. The type "Color" is used to represent the rgb components of a color.
//  Some colors are predefined:
//       WHITE,GREY,BLACK,RED,GREEN,BLUE,YELLOW,PURPLE and CYAN
//  You can also mix your own colors:
//       Color c{201,100,10}   (each rgb component goes from 0-255)

class Button{
    private:
        string text;
        double textSize;
        double width;
        double height;
        Vec2d bottomLeft;
    public:
        Button(string _text, Vec2d _bottomLeft, double _width, double _height, double _textSize);
        void drawButton(Graphics& g);
};

class Panel{
    private:
        vector<Button> buttons;
        Vec2d topLeft;
        double buttonHeight;
        double buttonSpacing;
    public:
        Panel(Vec2d _topLeft, double _buttonHeight, double _buttonSpacing);
        void addButton(Button b);
        void drawPanel(Graphics& g);
};

Panel::Panel(Vec2d _topLeft, double _buttonHeight, double _buttonSpacing){
    topLeft = _topLeft;
    buttonHeight = _buttonHeight;
    buttonSpacing = _buttonSpacing;
}

void Panel::addButton(Button b){
    buttons.push_back(b);
}

void Panel::drawPanel(Graphics &g){
    double yPos = topLeft.y;
    for (int i = 0; i < buttons.size(); i++){
        Button b = buttons[i];
        // finish this pls
    }
}

Button::Button(string _text, Vec2d _bottomLeft, double _width, double _height, double _textSize){
    text = _text;
    width = _width;
    height = _height;
    bottomLeft = _bottomLeft;
    textSize = _textSize;
}

void Button::drawButton(Graphics& g){
    g.rect(bottomLeft, width, height);
    g.text(bottomLeft, textSize, text, WHITE);
}

// Example 1:  Hello World
// no animation, no events... just display some stuff
void graphicsMain(Graphics& g)
{
    Button b = {"le test", {100,100}, 80, 25, 20};

    b.drawButton(g);

//    Image im;
//    g.snapShot(im);
//    im.save("snap.png");
}


//// Example 2:  Simple animation without events
//
//void graphicsMain(Graphics& g)
//{
//    double x = 100;
//    double y = 500;

//    while (g.draw()) {  // g.draw() causes the drawing to be sent to the screen

//        g.clear();  // get ready to draw (clear the screen)

//        g.line(0, 0, x, y, GREEN);

//        x = x + 1;

//        if (x > 700) {
//            x = 100;
//        }
//    }
//}

//// Example 3:  Events
//void graphicsMain(Graphics& g)
//{
//    double x = g.width()/2;
//    double y = g.height()/2;
//    string message = "Hello";

//    while (g.draw()) {
//        g.clear();

//        g.text(x, y, 20, message, YELLOW);

//        for (const Event& e : g.events())
//        {
//            switch (e.evtType)
//            {
//            case EvtType::MousePress:
//                x = e.x;
//                y = e.y;
//                message = "MousePress";
//                break;
//            case EvtType::MouseRelease:
//                x = e.x;
//                y = e.y;
//                message = "MouseRelease";
//                break;
//            case EvtType::MouseWheel:
//                break;
//            case EvtType::MouseMove:
//                x = e.x;
//                y = e.y;
//                message = "MouseMove";
//                break;
//            case EvtType::KeyPress:
//                x = g.width()/2;
//                y = g.height()/2;
//                message = "KeyPress: ";
//                message.append(1, char(e.arg));
//                break;
//            case EvtType::KeyRelease:
//                x = g.width()/2;
//                y = g.height()/2;
//                message = "KeyPress: ";
//                message.append(1, char(e.arg));
//                break;
//            default:
//                break;
//            }
//        }
//    }
//}

int main()
{
    // main should be empty except for the following line:
    Graphics g("Drawing", 800, 600, graphicsMain);
}
