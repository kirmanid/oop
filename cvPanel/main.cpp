#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Canvas {
    public:
        Canvas(int _height, int _width, Scalar _color, string name);
        void drawAndWipe();  
        Mat mat;
        string getName();
        int keypress;
    private:
        string name;
        int tick;
        int height;
        int width;
        Scalar color; // 8 bit, BGR
};

static class Click {
    public:
        static void mouseCallback(int event, int  x, int  y, int flag, void *param);
        Point lastClick;
        Point lastPos;
        bool handled;
} click;

class Button {
    public:
        Button(Point _location, int _height, int _width, string _text);
        Mat draw(Mat canvas); /// what's the right way to pass this by reference?
        void checkPressed();
        bool pressed;
        void checkMousedOverAndHighlight();
        int getHeight();
        void assignLocation(Point loc);
    private:
        bool pointInBounds(Point p, Point topLeftCorner, int width, int height);
        Point location; // top left corner
        int height;
        int width;
        int thickness;
        int currentThickness;
        Scalar color;
        Scalar textColor;
        string text;
        double fontSize;
        int margin;
        int font;
};

class Panel {
    public:
        Panel(Point _location, int _width);
        void addButton(Button button);
        Mat draw(Mat canvas);
        vector<bool> checkPressed();
        void updateButtonHighlighting();
        void assignLocation(Point loc);
    private:
        vector<Button> buttons;
        Point location; // top left corner
        Scalar color;
        int width;
        int thickness;
        int spacing;
        int margin;
};

Panel::Panel(Point _location, int _width){
    location = _location;
    width = _width;
    color = Scalar(114,128,250);
    thickness = 1;
    spacing = 5;
    margin = 5;
}

void Panel::addButton(Button button){
    buttons.push_back(button);
}

Mat Panel::draw(Mat canvas){
    Point currentLoc = location;
    currentLoc.x += margin;
    currentLoc.y += margin;
    //draw buttons
    for(unsigned int i = 0; i < buttons.size(); i++){
        buttons[i].assignLocation(currentLoc);
        buttons[i].draw(canvas); /// maybe canvas =
        currentLoc.y += buttons[i].getHeight() + spacing;
    }
    //draw panel
    currentLoc.y -= spacing;
    currentLoc.y += margin;
    currentLoc.x += width + margin; // now 'currentLoc' and 'location' form the two corners of the panel
    rectangle(canvas, location, currentLoc, color, thickness);
    return canvas; /// needed?
}

vector<bool> Panel::checkPressed(){
    vector<bool> pressed(buttons.size(), false);
    unsigned int i = 0; 
    while(i < buttons.size() && !click.handled){
        buttons[i].checkPressed();
        pressed[i] = buttons[i].pressed;
        i++;
    }
    if (i != 0 && click.handled){
        cout << "Button #" << i << " pressed!"<< endl;
    }
    return pressed;
}

void Panel::updateButtonHighlighting(){
    for (unsigned int i = 0; i < buttons.size(); i++){
        buttons[i].checkMousedOverAndHighlight();
    }
}

Button::Button(Point _location, int _height, int _width, string _text){
    location = _location;
    height = _height;
    width = _width;
    text = _text;
    color = Scalar(114,236,250);
    textColor = color;
    fontSize = 1.3;
    thickness = 1;
    currentThickness = thickness;
    margin = 2;
    font = FONT_HERSHEY_PLAIN;
}

Mat Button::draw(Mat canvas){
    Point oppositeCorner = location; //bottom left corner
    oppositeCorner.x += width;
    oppositeCorner.y += height;
    rectangle(canvas, location, oppositeCorner, color, currentThickness);
    Rect textRoi = Rect(location.x + margin, location.y + margin, width - margin, height - margin);
    putText(canvas(textRoi), text, Point(0, height - (margin * 2)), font, fontSize, textColor);
    return canvas;
}

int Button::getHeight(){
    return height;
}

bool Button::pointInBounds(Point p, Point topLeftCorner, int width, int height){
    return
    p.x > topLeftCorner.x
    && p.x < topLeftCorner.x + width
    && p.y > topLeftCorner.y
    && p.y < topLeftCorner.y + height;
}

void Button::checkPressed(){
    if (!click.handled && pointInBounds(click.lastClick, location, width, height)){
        pressed = true;
        click.handled = true;
    } else {
        pressed = false;
    }
}

void Button::checkMousedOverAndHighlight(){
    Scalar highlightTextColor = Scalar(0,0,0);
    int fillThickness = -1;
    if (pointInBounds(click.lastPos, location, width, height)){
        currentThickness = fillThickness;
        textColor = highlightTextColor;
    } else {
        currentThickness = thickness;
        textColor = color;
    }
    // You still need to call draw() after highlighting
}

void Button::assignLocation(Point loc){
    location = loc;
}

void Panel::assignLocation(Point loc){
    location = loc;
}

Canvas::Canvas(int _height, int _width, Scalar _color, string _name){
    height = _height;
    width = _width;
    color = _color;
    name = _name;
    tick = 10; // in ms
    mat = Mat(height, width, CV_8UC3, color);
    namedWindow(name, WINDOW_NORMAL);
    setMouseCallback(name, click.mouseCallback);
}

string Canvas::getName(){
    return name;
}

void Canvas::drawAndWipe(){
    imshow(name, mat);
    keypress = waitKey(tick);
    mat = Mat(height, width, CV_8UC3, color);
}

void Click::mouseCallback(int  event, int  x, int  y, int  flag, void *param){
    if (flag == EVENT_LBUTTONDOWN){
        click.handled = false;
        click.lastClick.x = x;
        click.lastClick.y = y;
    }
    else if ( event == EVENT_MOUSEMOVE){
        click.lastPos.x = x;
        click.lastPos.y = y;
    }
}
/*
# TODO

- widget base class from which panel and button are derived
- epic function on click assignable per button
*/
int main (){
    Canvas canv {768, 1024, Scalar{0,0,0}, "Le Window"};
    Button but {Point{100,100}, 20, 200, "BRUH BUTTON"};
    Panel pan {Point{100,100}, 200};

    pan.addButton(but);
    pan.addButton(but);
    pan.addButton(but);

    do{
        canv.drawAndWipe();
        pan.checkPressed();
        pan.updateButtonHighlighting();
        pan.draw(canv.mat);
    }while(canv.keypress == 255); // aka while key not pressed
    return 0;
}
