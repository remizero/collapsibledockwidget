#include "DockWidget.h"

DockWidget::DockWidget ( const QString &title, QWidget *parent, Qt::WindowFlags flags ) : QDockWidget ( title, parent, flags ) {

  this->titleBar = new DockWidgetTitleBar ( this );
  this->setTitleBarWidget ( this->titleBar );
  this->mainWidget = nullptr;
  this->entered = false;
  this->pinned = true;
  this->shot = false;
}

DockWidget::DockWidget ( QWidget *parent, Qt::WindowFlags flags ) : QDockWidget ( parent, flags ) {

  this->titleBar = new DockWidgetTitleBar ( this );
  this->setTitleBarWidget ( this->titleBar );
  this->mainWidget = nullptr;
  this->entered = false;
  this->pinned = true;
  this->shot = false;
}

void DockWidget::autohide () {

  this->shot = false;
  if ( !this->entered ) {

    this->setCollapsed ( false );
  }
}

void DockWidget::autoshow () {

  this->shot = false;
  if ( this->entered ) {

    this->setCollapsed ( true );
  }
}

void DockWidget::enterEvent ( QEvent *event ) {

  this->entered = true;
  if ( !this->shot && !this->isPinned () && !this->isFloating () ) {

    this->shot = true;
    QTimer::singleShot ( 500, this, SLOT ( autoshow () ) );
    return QDockWidget::enterEvent ( event );
  }
}

bool DockWidget::isCollapsed () {

  return this->mainWidget->isCollapsed ();
}

bool DockWidget::isPinned () {

  return this->pinned;
}

void DockWidget::leaveEvent ( QEvent *event ) {

  this->entered = false;
  if ( !this->shot && !this->isPinned () && !this->isFloating () ) {

    this->shot = true;
    QTimer::singleShot ( 1000, this, SLOT ( autohide () ) );
    return QDockWidget::leaveEvent ( event );
  }
}

void DockWidget::setCollapsed ( bool flag ) {

  this->mainWidget->setCollapsed ( flag );
  this->titleBar->setCollapsedIcon ( flag );
}

void DockWidget::setPinned ( bool flag ) {

  this->pinned = flag;
}

void DockWidget::setWidget ( QWidget *widget ) {

  this->mainWidget = new DockMainWidgetWrapper ( this );
  this->mainWidget->setWidget ( widget );
  QDockWidget::setWidget ( this->mainWidget );
}

void DockWidget::toggleCollapsed () {

  this->setCollapsed ( !this->isCollapsed () );
}

bool DockWidget::hasFeature ( QDockWidget *dockwidget, QDockWidget::DockWidgetFeature feature ) {

  return ( ( dockwidget->features () && feature ) == feature );
}
