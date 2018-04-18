#ifndef COLLAPSIBLEDOCKWIDGET_H
#define COLLAPSIBLEDOCKWIDGET_H

#include "AnimatedStackedWidget.h"

#include <QAbstractButton>
#include <QDockWidget>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QStyle>
#include <QTransform>
#include <QWidget>

class CollapsibleDockWidget : public QDockWidget {

    Q_OBJECT

  public:
    CollapsibleDockWidget ( const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags () );
    ~CollapsibleDockWidget ();

    static const int QWIDGETSIZE_MAX_AUX = ( 1 << 24 );
    static const int QWIDGETSIZE_MAX_1 = ( ( 1 << 24 ) - 1 );
//C:\Users\fzaa\Documents\proyectos\Desarrollo\qt\collapsibledockwidget\CollapsibleDockWidget.h:24: error: C2059: syntax error: 'constant'
    void collapse ();
    QWidget *currentWidget ();
    bool event ( QEvent *event ) Q_DECL_OVERRIDE;
    bool eventFilter ( QObject *watched, QEvent *event ) Q_DECL_OVERRIDE;
    void expand ();
    void fixIcon ();
    void fixMinimumWidth ();
    QWidget *getCollapsedWidget ();
    int hasFixedWidth ();
    bool isAnimationEnabled ();
    bool isExpanded ();
    bool isExpandedWidget ();
    void setAnimationEnabled ( bool animationEnabled );
    void setCollapsedWidget ( QWidget *widget);
    void setExpanded ( bool expanded );
    void setExpandedWidget ( QWidget *widget );
    void setWidget ( QWidget *widget );

  public slots:
    void onDockLocationChanged ( Qt::DockWidgetArea area );
    void onFeaturesChanged ( QDockWidget::DockWidgetFeatures features );
    void onTransitionFinished ();
    void onTransitionStarted ();

  signals:
    void expandedChanged ( bool );

  private:
    //bool expandedWidget;
                     bool  animationEnabled;
                  QWidget *collapsedWidget;
                     bool  expanded;
                  QWidget *expandedWidget;
                    QIcon *iconLeft;
                    QIcon *iconRight;
                      int  trueMinimumWidth;
    AnimatedStackedWidget *stack;
          QAbstractButton *closeButton;
};

#endif // COLLAPSIBLEDOCKWIDGET_H
