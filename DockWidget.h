#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include "DockWidgetTitleBar.h"
#include "DockMainWidgetWrapper.h"

#include <QDockWidget>
#include <QEvent>
#include <QTimer>

class DockMainWidgetWrapper;
class DockWidgetTitleBar;

class DockWidget : public QDockWidget {

    Q_OBJECT

  public:
    explicit DockWidget ( const QString &title, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags () );
    explicit DockWidget ( QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags () );

    void enterEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    bool isCollapsed ();
    bool isPinned ();
    void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    void setCollapsed ( bool flag );
    void setPinned ( bool flag );
    void setWidget ( QWidget *widget );
    void toggleCollapsed ();

    static bool hasFeature ( QDockWidget *dockwidget, QDockWidget::DockWidgetFeature feature );

  public slots:
    void autohide ();
    void autoshow ();

  private:
                     bool  entered;
    DockMainWidgetWrapper *mainWidget;
                     bool  pinned;
                     bool  shot;
       DockWidgetTitleBar *titleBar;
};

#endif // DOCKWIDGET_H
