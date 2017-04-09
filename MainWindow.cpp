#include "MainWindow.h"

MainWindow::MainWindow() :
    QDialog()
{
    // set the title, size, and window buttons
    this->setWindowTitle("RegexToNFA");
    this->setFixedSize(200, 200);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}
