#include "Canvas.h"
#include "Automaton.h"

Canvas::Canvas(MainWindow* parent) :
    QDialog(),
    m_closeBtn(new)
{
    // setup the canvas
    this->setWindowTitle("NFA Computation Result");
    this->setFixedSize(300, 300);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    auto nfa


    this->connect(m_closeBtn)
    auto s = new Automaton(this);
    s->show();
}

void Canvas::closeEvent(QCloseEvent* event)
{
    parent->onCanvasClosed();
    event->accept();
}
