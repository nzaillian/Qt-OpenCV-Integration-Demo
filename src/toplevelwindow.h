#ifndef TOPLEVELWINDOW_H
#define TOPLEVELWINDOW_H

#include <QWidget>
#include "cvwidget.h"

namespace Ui {
    class ToplevelWindow;
}

class ToplevelWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ToplevelWindow(QWidget *parent = 0);
    ~ToplevelWindow();
    CVWidget* w;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ToplevelWindow *ui;
};

#endif // TOPLEVELWINDOW_H
