#ifndef DOCKWIDGETTITLEBAR_H
#define DOCKWIDGETTITLEBAR_H

#include "DockWidget.h"
#include "DockWidgetTitleBarButton.h"

#include <QDockWidget>
#include <QFontMetrics>
#include <QIcon>
#include <QPaintEvent>
#include <QPoint>
#include <QRect>
#include <QResizeEvent>
#include <QSize>
#include <QStyle>
#include <QStylePainter>
#include <QWidget>

class DockWidgetTitleBar : public QWidget {

    Q_OBJECT

  public:
    explicit DockWidgetTitleBar ( QWidget *parent = 0 );

    QSize minimumSizeHint () const Q_DECL_OVERRIDE;
    void paintEvent ( QPaintEvent *event ) Q_DECL_OVERRIDE;
    void resizeEvent ( QResizeEvent *event ) Q_DECL_OVERRIDE;
    void setCollapsed ( bool collapsed );
    void setCollapsedIcon ( bool flag );
    QSize sizeHint () const Q_DECL_OVERRIDE;

  signals:

  public slots:
    void featuresChanged ( QDockWidget::DockWidgetFeatures features );
    void toggleCollapsed ();
    void toggleFloating ();
    void togglePinned ( bool checked );

  private:
    QIcon closeIcon;
    QIcon openIcon;
    QIcon pinIcon;
    DockWidgetTitleBarButton *closeButton;
    DockWidgetTitleBarButton *collapseButton;
    DockWidgetTitleBarButton *floatButton;
    DockWidgetTitleBarButton *pinButton;
};

#endif // DOCKWIDGETTITLEBAR_H
