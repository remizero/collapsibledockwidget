#ifndef DOCKWIDGETTITLEBARBUTTON_H
#define DOCKWIDGETTITLEBARBUTTON_H

#include <QAbstractButton>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QRect>
#include <QSize>
#include <QStyleOptionToolButton>

class DockWidgetTitleBarButton : public QAbstractButton {

    Q_OBJECT

  public:
    DockWidgetTitleBarButton ( QWidget *parent = Q_NULLPTR );

    void enterEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    void paintEvent ( QPaintEvent *event ) Q_DECL_OVERRIDE;
    QSize sizeHint () const Q_DECL_OVERRIDE;
};

#endif // DOCKWIDGETTITLEBARBUTTON_H
