#ifndef TRANSITIONWIDGET_H
#define TRANSITIONWIDGET_H

#include <QWidget>
#include <QSize>
#include "Utils.h"

class AutomatonWidget;
class QPaintEvent;

class TransitionWidget : public QWidget
{
public:
    using Self   = TransitionWidget;
    using Ptr    = Utils::Ptr<Self>;
    using Shared = Utils::SharedPtr<Self>;

    TransitionWidget(AutomatonWidget* parent);
    NO_COPY_NO_MOVE(TransitionWidget);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:

};

#endif // TRANSITIONWIDGET_H
