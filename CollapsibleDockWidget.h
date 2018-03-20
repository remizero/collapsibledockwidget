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

    bool isAnimationEnabled ();
    void collapse ();
    QWidget *getCollapsedWidget ();
    QWidget *currentWidget ();
    bool event ( QEvent *event ) Q_DECL_OVERRIDE;
    bool eventFilter ( QObject *watched, QEvent *event ) Q_DECL_OVERRIDE;
    void expand ();
    bool isExpanded ();
    void fixIcon ();
    void fixMinimumWidth ();
    bool isExpandedWidget ();
    int hasFixedWidth ();
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

       bool animationEnabled;
    QWidget *collapsedWidget;
       bool expanded;
    QWidget *expandedWidget;
      QIcon *iconLeft;
      QIcon *iconRight;
        int trueMinimumWidth;

    AnimatedStackedWidget *stack;

    QAbstractButton *closeButton;
};

#endif // COLLAPSIBLEDOCKWIDGET_H
