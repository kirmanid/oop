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
        bool clickHandled;
        bool moveHandled;
} click;

class Shape{
    virtual void draw() = 0;
    virtual void onMouseDrag() = 0;
}

class Rectangle: public Shape {
    public:
        Rectangle();
        void draw() override;
        void onMouseDrag() override;
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
        click.clickHandled = false;
        click.lastClick.x = x;
        click.lastClick.y = y;
    }
    else if ( event == EVENT_MOUSEMOVE){
        click.moveHandled = false;
        click.lastPos.x = x;
        click.lastPos.y = y;
    }
}

int main (){
    Canvas canv {768, 1024, Scalar{0,0,0}, "Le Window"};
    vector<uniqe_ptr<Shape>> shapeVect;

    do{
        if (!click.clickHandled){
            shapeVect.push_back(make_unique<Rectangle>);
            click.clickHandled = true;
        }
        if (!click.moveHandled){
            shapeVect[shapeVect.size() -1].mouseDrag();
        }
        canv.drawAndWipe();
    }
    }while(canv.keypress == 255); // aka while key not pressed
    return 0;
}
