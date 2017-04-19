#include <QPushButton>
#include "Canvas.h"

Canvas::Canvas() :
    QDialog(),
    m_closeBtn(new QPushButton(this))
{
    // setup the canvas
    this->setWindowTitle("NFA Computation Result");
    this->setFixedSize(300, 300);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    
    // setup the close button
    m_computeBtn->setText("Close ");
    m_computeBtn->move(100, 270);

    // close the canvas on close button push
    this->connect(m_closeBtn, &QPushButton::clicked, this, &QWidget::close);
}

