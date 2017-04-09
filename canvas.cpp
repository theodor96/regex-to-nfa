#include "Canvas.h"

Canvas::Canvas() :
    QDialog()
{
    // setup the canvas
    this->setWindowTitle("NFA Computation Result");
    this->setFixedSize(300, 300);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}
