#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    auto window = MainWindow::Ptr(new MainWindow());
    window->show();

    return app.exec();
}
