#ifndef CANVAS_H
#define CANVAS_H

#include <QDialog>
#include "AutomatonWidget.h"
#include "Utils.h"

class QPushButton;

class Canvas : public QDialog
{
public:
    using Self   = Canvas;
    using Ptr    = Utils::Ptr<Self>;
    using Shared = Utils::SharedPtr<Self>;
    
    Canvas();
    NO_COPY_NO_MOVE(Canvas);
    
private:
    QPushButton*         m_closeBtn;
    AutomatonWidget::Ptr m_automaton;
};

#endif // CANVAS_H

