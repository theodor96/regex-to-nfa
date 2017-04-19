#ifndef CANVAS_H
#define CANVAS_H

#include <QDialog>

class Canvas : public QDialog
{
public:
    Canvas();
    //NO_COPY_NO_MOVE(Canvas)

protected:
    void closeEvent(QCloseEvent* event) override;
};

#endif // CANVAS_H
