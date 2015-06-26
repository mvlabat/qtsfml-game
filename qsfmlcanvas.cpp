#include "qsfmlcanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget *p_parentWindow, unsigned int FrameTime) :
    QWidget(),
    parentWindow(p_parentWindow),
    isInitialized(false),
    engine(this, &settings)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setVerticalSyncEnabled(settings.getVSync());

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    //parentWindow->setWindowState(Qt::WindowFullScreen);

    // Setup the timer
    renderTimer.setInterval(FrameTime);

    this->setMouseTracking(true);
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
    QPoint p = this->mapFromGlobal(QCursor::pos());
    if (p.rx() > size().width())
    {
        system.mousePosition.x = (uint)size().width();
    }
    else
    {
        system.mousePosition.x = (uint)p.rx();
    }
    if (p.ry() > size().height())
    {
        system.mousePosition.y = (uint)size().height();
    }
    else
    {
        system.mousePosition.y = (uint)p.ry();
    }
    qDebug() << system.mousePosition.x << system.mousePosition.y;
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    system.windowSize = sf::Vector2u((uint)size().width(), (uint)size().height());
    sf::Window::setSize(system.windowSize);
    setView(sf::View(sf::FloatRect(0, 0, (uint)size().width(), (uint)size().height())));
}

void QSFMLCanvas::paintEvent(QPaintEvent *)
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
    // Clear screen
    clear(sf::Color(0, 0, 0));
    engine.render();
}

void QSFMLCanvas::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    QPointF p = mouseEvent->localPos();
    system.mousePosition.x = p.rx();
    system.mousePosition.y = p.ry();
}

void QSFMLCanvas::keyPressEvent(QKeyEvent *keyEvent)
{
    engine.processPressedKeyEvent(keyEvent);
}

void QSFMLCanvas::keyReleaseEvent(QKeyEvent *keyEvent)
{
    engine.processReleasedKeyEvent(keyEvent);
}
