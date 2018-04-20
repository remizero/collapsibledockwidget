#include "CollapsibleDockWidget.h"

#include <QDebug>

CollapsibleDockWidget::CollapsibleDockWidget ( const QString &title, QWidget *parent, Qt::WindowFlags flags ) : QDockWidget ( title, parent, flags ) {

  //QDockWidget.__init__(self, *args, **kwargs)

  this->expandedWidget = nullptr;
  this->collapsedWidget = nullptr;
  this->expanded = true;
  this->trueMinimumWidth = -1;

  this->setFeatures ( QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable );
  this->setAllowedAreas ( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );

  //connect ( this, SIGNAL ( featuresChanged ( QDockWidget::DockWidgetFeatures ) ), this, SLOT ( onDockLocationChanged ( Qt::DockWidgetArea ) ) );
  //connect ( this, SIGNAL ( dockLocationChanged ( Qt::DockWidgetArea ) ), this, SLOT ( onFeaturesChanged ( QDockWidget::DockWidgetFeatures ) ) );
  //this->featuresChanged.connect ( this->__onFeaturesChanged );
  //this->dockLocationChanged.connect ( this->__onDockLocationChanged );
  connect ( this, SIGNAL ( dockLocationChanged ( Qt::DockWidgetArea ) ), this, SLOT ( onDockLocationChanged ( Qt::DockWidgetArea ) ) );
  connect ( this, SIGNAL ( featuresChanged ( QDockWidget::DockWidgetFeatures ) ), this, SLOT ( onFeaturesChanged ( QDockWidget::DockWidgetFeatures ) ) );

  // Use the toolbar horizontal extension button icon as the default
  // for the expand/collapse button
  QPixmap pm = this->style ()->standardPixmap ( QStyle::SP_ToolBarHorizontalExtensionButton );

  // Rotate the icon
  //QTransform *transform = new QTransform ();
  QTransform transform;
  transform.rotate ( 180 );

  QPixmap pm_rev = pm.transformed ( transform );

  this->iconRight = new QIcon ( pm );
  this->iconLeft = new QIcon ( pm_rev );

  //QAbstractButton *closeAbsBtn = this->findChild ( QAbstractButton, "qt_dockwidget_closebutton" );
  QAbstractButton *closeAbsBtn = this->findChild < QAbstractButton * > ( "qt_dockwidget_closebutton" );
  closeAbsBtn->installEventFilter ( this );
  this->closeButton = closeAbsBtn;

  this->stack = new AnimatedStackedWidget ();
  this->stack->setSizePolicy ( QSizePolicy::Fixed, QSizePolicy::Expanding );
  connect ( this->stack, SIGNAL ( transitionStarted () ), this, SLOT ( onTransitionStarted () ) );
  connect ( this->stack, SIGNAL ( transitionFinished () ), this, SLOT ( onTransitionFinished () ) );

  QDockWidget::setWidget ( this->stack );
  this->closeButton->setIcon ( *this->iconLeft );
  this->resize ( 300, 300 );
}

CollapsibleDockWidget::~CollapsibleDockWidget () {}

bool CollapsibleDockWidget::isAnimationEnabled () {

  return this->stack->isAnimationEnabled ();
}

void CollapsibleDockWidget::collapse () {

  this->setExpanded ( false );
}

QWidget *CollapsibleDockWidget::getCollapsedWidget () {

  return this->collapsedWidget;
}

QWidget *CollapsibleDockWidget::currentWidget () {

  if ( this->expanded ) {

    return this->expandedWidget;

  } else {

    return this->collapsedWidget;
  }
}

bool CollapsibleDockWidget::event ( QEvent *event ) {

  qDebug () << event->type ();
  if ( event->type () == QEvent::LayoutRequest ) {

    this->fixMinimumWidth ();
  }
  return QDockWidget::event ( event );
}

bool CollapsibleDockWidget::eventFilter ( QObject *watched, QEvent *event ) {

  if ( watched == this->closeButton ) {

    QEvent::Type etype = event->type ();
    if ( etype == QEvent::MouseButtonPress ) {

      this->setExpanded ( !this->expanded );
      return true;

    } else if ( etype == QEvent::MouseButtonDblClick || etype == QEvent::MouseButtonRelease ) {

      return true;
    }
    //# TODO: which other events can trigger the button (is the button
    //# focusable).
  }
  return QDockWidget::eventFilter ( watched, event );
}

void CollapsibleDockWidget::expand () {

  /*"""
  Expand the dock (same as ``setExpanded(True)``)
  """*/
  this->setExpanded ( true );
}

bool CollapsibleDockWidget::isExpanded () {

  /*"""
  Is the dock widget in expanded state. If `True` the
  ``isExpandedWidget`` will be shown, and ``collapsedWidget`` otherwise.

  """*/
  return this->expanded;
}

void CollapsibleDockWidget::fixIcon () {

  Qt::LayoutDirection direction = this->layoutDirection ();
  QIcon *icon;
  if ( direction == Qt::LeftToRight ) {

    if ( this->expanded ) {

      icon = this->iconLeft;

    } else {

      icon = this->iconRight;
    }
  } else {

    if ( this->expanded ) {

      icon = this->iconRight;

    } else {

      icon = this->iconLeft;
    }
  }
  this->closeButton->setIcon ( *icon );
}

void CollapsibleDockWidget::fixMinimumWidth () {

//# A workaround for forcing the QDockWidget layout to disregard the
//# default minimumSize which can be to wide for us (overriding the
//# minimumSizeHint or setting the minimum size directly does not
//# seem to have an effect (Qt 4.8.3).
  QSize size = this->stack->sizeHint ();
  qDebug () << "size.width () " << size.width ();
  qDebug () << "size.height () " << size.height ();
  if ( size.isValid () && !size.isEmpty () ) {

    int left, top, right, botton;
    this->getContentsMargins ( &left, &top, &right, &botton );
    int width = size.width () + left + right;

    qDebug () << "width " << width;

    if ( width < this->minimumSizeHint ().width () ) {

      if ( !this->hasFixedWidth () ) {
        /*log.debug("Overriding default minimum size "
                      "(setFixedWidth(%i))", width)*/
        this->trueMinimumWidth = this->minimumSizeHint ().width ();
      }
      this->setFixedWidth ( width );

    } else {

      if ( this->hasFixedWidth () ) {

        if ( width >= this->trueMinimumWidth ) {
          /*# Unset the fixed size.
                log.debug("Restoring default minimum size "
                          "(setFixedWidth(%i))", QWIDGETSIZE_MAX)*/
          this->trueMinimumWidth = -1;
          this->setFixedWidth ( QWIDGETSIZE_MAX_1 );
          this->updateGeometry ();

        } else {

          this->setFixedWidth ( width );
        }
      }
    }
  }
}

bool CollapsibleDockWidget::isExpandedWidget () {
  /*"""
  Return the widget previously set with ``setExpandedWidget``,
  or ``None`` if no widget has been set.

  """*/
  return this->expandedWidget;
}

int CollapsibleDockWidget::hasFixedWidth () {

  return this->trueMinimumWidth >= 0;
}

void CollapsibleDockWidget::onDockLocationChanged ( Qt::DockWidgetArea area ) {

  if ( area == Qt::LeftDockWidgetArea ) {

    this->setLayoutDirection ( Qt::LeftToRight );

  } else {

    this->setLayoutDirection ( Qt::RightToLeft );
  }

  this->stack->setLayoutDirection ( this->parentWidget ()->layoutDirection () );
  this->fixIcon ();
}

void CollapsibleDockWidget::onFeaturesChanged ( QDockWidget::DockWidgetFeatures features ) {

  Q_UNUSED ( features )
}

void CollapsibleDockWidget::onTransitionFinished () {

  //log.debug ( "Dock transition finished (new width %i)", this->size ().width () );
}

void CollapsibleDockWidget::onTransitionStarted () {

  //log.debug ( "Dock transition started." );
}

void CollapsibleDockWidget::setCollapsedWidget ( QWidget *widget ) {

  /*"""
  Set the widget with contents to show while collapsed.
  """*/
  if ( widget == this->collapsedWidget ) {

    return;
  }

  if ( this->collapsedWidget != nullptr ) {

    this->stack->removeWidget ( this->collapsedWidget );
  }

  this->stack->insertWidget ( 1, widget );
  this->collapsedWidget = widget;

  if ( !this->expanded ) {

    this->stack->setCurrentWidget ( widget );
  }
  this->updateGeometry ();
}

void CollapsibleDockWidget::setExpanded ( bool expanded ) {

  /*"""
  Set the widgets `expanded` state.
  """*/
  if ( this->expanded != expanded ) {

    this->expanded = expanded;
    if ( expanded && ( this->expandedWidget != nullptr ) ) {

      //log.debug("Dock expanding.");
      this->stack->setCurrentWidget ( this->expandedWidget );

    } else if ( !expanded && ( this->collapsedWidget != nullptr ) ) {

      //log.debug("Dock collapsing.");
      this->stack->setCurrentWidget ( this->collapsedWidget );
    }
    this->fixIcon ();
    //this->expandedChanged.emit ( expanded );
    emit this->expandedChanged ( expanded );
  }
}

void CollapsibleDockWidget::setExpandedWidget ( QWidget *widget ) {

    /*"""
    Set the widget with contents to show while expanded.
    """*/
    if ( widget == this->expandedWidget ) {

      return;
    }

    if ( this->expandedWidget != nullptr ) {

      this->stack->removeWidget ( this->expandedWidget );
    }

    this->stack->insertWidget ( 0, widget );
    this->expandedWidget = widget;

    if ( this->expanded ) {

      this->stack->setCurrentWidget ( widget );
      this->updateGeometry ();
    }
}

void CollapsibleDockWidget::setWidget ( QWidget *widget ) {

  Q_UNUSED ( widget )
  /*raise NotImplementedError(
            "Please use the 'setExpandedWidget'/'setCollapsedWidget' "
            "methods to set the contents of the dock widget."
            );*/
}
