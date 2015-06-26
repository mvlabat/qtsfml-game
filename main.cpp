#include "mycanvas.h"
#include <QApplication>
#include <QFrame>
#include <QBoxLayout>

#include "binarysearchtree.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    // Create the main frame
    QFrame MainFrame;
    MainFrame.setWindowTitle("Qt SFML");
    MainFrame.resize(400, 400);
    MainFrame.show();

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight, &MainFrame);
    QSFMLCanvas *SFMLView = new QSFMLCanvas(&MainFrame);
    layout->addWidget(SFMLView);
    layout->setContentsMargins(0, 0, 0, 0);
    SFMLView->show();

    return App.exec();
}
