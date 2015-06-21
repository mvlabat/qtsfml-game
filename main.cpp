#include "mycanvas.h"
#include <QApplication>
#include <QFrame>

#include "binarysearchtree.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    // Create the main frame
    QFrame MainFrame;
    MainFrame.setWindowTitle("Qt SFML");
    MainFrame.resize(400, 400);
    MainFrame.show();

    // Create a SFML view inside the main frame
    QSFMLCanvas SFMLView(&MainFrame, QPoint(0, 0), QSize(400, 400));
    SFMLView.show();

    return App.exec();
}
