#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    auto window = MainWindow::NewPtr{}();
    window->show();

    return app.exec();
}
