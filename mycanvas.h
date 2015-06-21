#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <SFML/Graphics.hpp>
#include "qsfmlcanvas.h"

class MyCanvas : public QSFMLCanvas
{
public:
    MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
    {

    }

private:
    //virtual void OnInit();
    //virtual void OnUpdate();
};


#endif // MYCANVAS_H
