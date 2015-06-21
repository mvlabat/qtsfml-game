#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <SFML/Graphics.hpp>
#include "gamesettings.h"
#include "engine.h"

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT

public:
    QSFMLCanvas(QWidget* p_parentWindow, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
    ~QSFMLCanvas();
protected:
    virtual void OnInit();
    virtual void OnUpdate();
private:
    virtual QPaintEngine* paintEngine() const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);
    QWidget *parentWindow;
    QTimer renderTimer;
    bool   isInitialized;
    GameSettings settings;
    Engine engine;
};

#endif // QSFMLCANVAS_H
