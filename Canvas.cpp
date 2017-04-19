#include <QPushButton>
#include "Canvas.h"

Canvas::Canvas(const NFA& nfa) :
    QDialog(),
    m_closeBtn(new QPushButton(this)),
    m_automaton(AutomatonWidget::Ptr(new AutomatonWidget(this)))
{
    // setup the canvas
    this->setWindowTitle("NFA Computation Result");
    this->setFixedSize(500, 570);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    
    // setup the close button
    m_computeBtn->setText("Close ");
    m_computeBtn->move(220, 540);

    // close the canvas on close button push
    this->connect(m_closeBtn, &QPushButton::clicked, this, &QWidget::close);
    
    // now feed the automaton widget with data from the NFA
  	 // for every vertex in nfa, m_automaton->addState
  	 // for every transition in nfa, m_automaton->
}

