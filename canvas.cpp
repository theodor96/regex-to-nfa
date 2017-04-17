#include "Canvas.h"
#include "State.h"

#include <QPainter>

Canvas::Canvas() :
    QDialog()
{
    // setup the canvas
    this->setWindowTitle("NFA Computation Result");
    this->setFixedSize(300, 300);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    auto s = new State(this, 40, 40);
    s->show();

}
