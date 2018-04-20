#include "DockMainWidgetWrapper.h"

DockMainWidgetWrapper::DockMainWidgetWrapper ( QWidget *parent ) : QWidget ( parent ) {

  this->widget = nullptr;
  this->hlayout = new QHBoxLayout ( this );
  this->hlayout->setSpacing ( 0 );
  this->hlayout->setContentsMargins ( 0, 0, 0, 0 );
  this->setLayout ( this->hlayout );
}

bool DockMainWidgetWrapper::isCollapsed () {

  return this->widget->isVisible ();
}

void DockMainWidgetWrapper::setCollapsed ( bool flag ) {

  if ( flag ) {

    this->old_size = this->size ();
    this->layout ()->removeWidget ( this->widget );
    this->widget->hide ();
    if ( DockWidget::hasFeature ( ( DockWidget * ) this->parent (), QDockWidget::DockWidgetVerticalTitleBar ) ) {

      ( ( QWidget * ) this->parent () )->setMaximumWidth ( ( ( QWidget * ) this->parent () )->width () - this->width () );

    } else {

      ( ( QWidget * ) this->parent () )->setMaximumHeight ( ( ( QWidget * ) this->parent () )->height () - this->height () );
    }
  } else {

    this->setFixedSize ( this->old_size );
    ( ( QWidget * ) this->parent () )->setMinimumSize ( QSize ( 1, 1 ) );
    ( ( QWidget * ) this->parent () )->setMaximumSize ( QSize ( 32768, 32768 ) );
    this->widget->show ();
    this->layout ()->addWidget ( this->widget );
    this->setMinimumSize ( QSize ( 1, 1 ) );
    this->setMaximumSize ( QSize ( 32768, 32768 ) );
  }
}

void DockMainWidgetWrapper::setWidget ( QWidget *widget ) {

  this->widget = widget;
  this->widget_height = widget->height ();
  this->layout ()->addWidget ( widget );
}
