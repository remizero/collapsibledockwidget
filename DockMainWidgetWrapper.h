#ifndef DOCKMAINWIDGETWRAPPER_H
#define DOCKMAINWIDGETWRAPPER_H

#include "DockWidget.h"

#include <QDockWidget>
#include <QHBoxLayout>
#include <QSize>
#include <QWidget>

class DockMainWidgetWrapper : public QWidget {

    Q_OBJECT

  public:
    explicit DockMainWidgetWrapper ( QWidget *parent = 0 );

    bool isCollapsed ();
    void setCollapsed ( bool flag );
    void setWidget ( QWidget *widget );

  signals:

  public slots:

  private:
    QWidget *widget;
    int widget_height;
    QHBoxLayout *hlayout;
    QSize old_size;
};

#endif // DOCKMAINWIDGETWRAPPER_H
