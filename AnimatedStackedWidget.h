#ifndef ANIMATEDSTACKEDWIDGET_H
#define ANIMATEDSTACKEDWIDGET_H

#include "CrossFadePixmapWidget.h"
#include "StackLayout.h"

#include <QFrame>
#include <QList>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QStackedLayout>
#include <QWidget>

class AnimatedStackedWidget : public QFrame {

    Q_OBJECT

  public:
    AnimatedStackedWidget ( bool animationEnabled = true, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags () );
    ~AnimatedStackedWidget ();

    QWidget *addWidget ( QWidget *widget );
    int count ();
    int getCurrentIndex ();
    bool hasPendingResize ( QWidget *widget );
    int indexOf ( QWidget *widget );
    QWidget *insertWidget ( int index, QWidget *widget );
    bool isAnimationEnabled ();
    QWidget *removeWidget ( QWidget *widget );
    void setAnimationEnabled ( bool animationEnabled );
    void setCurrentIndex ( int index );
    void setCurrentWidget ( QWidget *widget );
    QSize sizeHint () const Q_DECL_OVERRIDE;
    void transitionStart ();
    QWidget *widget ( int index );

  public slots:
    void onLayoutCurrentChanged ( int index );
    void onTransitionFinished ();

  signals:
    // Current widget has changed
    void currentChanged ( int index );
    // Transition animation has started
    void transitionStarted ();
    // Transition animation has finished
    void transitionFinished ();

  private:
                     bool  animationEnabled;
                      int  currentIndex;
    CrossFadePixmapWidget *fadeWidget;
                      int  nextCurrentIndex;
              StackLayout *stackLayout;
       QPropertyAnimation *transitionAnimation;
       QList < QWidget *>  widgetList;
};

#endif // ANIMATEDSTACKEDWIDGET_H
