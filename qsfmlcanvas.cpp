#include "qsfmlcanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget* p_parentWindow, const QPoint& Position, const QSize& Size, unsigned int FrameTime) :
    QWidget(p_parentWindow),
    parentWindow(p_parentWindow),
    isInitialized(false),
    settings(),
    engine(this, &settings)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setVerticalSyncEnabled(settings.getVSync());

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    //parentWindow->setWindowState(Qt::WindowFullScreen);

    // Setup the timer
    renderTimer.setInterval(FrameTime);
}

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!isInitialized)
    {
        // Create the SFML window with the widget handle
        sf::Window::create(winId());

        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        renderTimer.setInterval(1000 / settings.getFps());
        connect(&renderTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        renderTimer.start();
        isInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    display();
}

QSFMLCanvas::~QSFMLCanvas()
{

}

void QSFMLCanvas::OnInit()
{

}

void QSFMLCanvas::OnUpdate()
{
    sf::Event event;
    while (pollEvent(event)) {
        switch(event.type)
        {
            case (sf::Event::MouseButtonPressed) :
                qDebug() << "mouse clicked"; // Event never handled
                //mousePressedEventHandling(event);
                break;
            case (sf::Event::MouseMoved) :
                qDebug() << "mouse moved"; // Event handled
                //mouseMovedEventHandling(event);
                break;
            case (sf::Event::KeyPressed) :
                qDebug() << "key pressed"; // Event handled
                break;
            default:
                break;
        }

    }
    // Clear screen
    clear(sf::Color(0, 0, 0));
    engine.render();
}
