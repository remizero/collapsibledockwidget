#include "QAutoHideDockWidgets.h"

QAutoHideDockWidgets::QAutoHideDockWidgets ( const QString &title, QWidget *parent ) : QToolBar ( title, parent ) {

  /*QToolBar.__init__(this, parent)
  assert isinstance(parent, QMainWindow)
  assert area in this->DOCK_AREA_TO_TB
  this->_area = area
  this->setObjectName ( name );
  this->setWindowTitle ( name );

  this->setFloatable ( false );
  this->setMovable ( false );
  QWidget *w = new QWidget ();
  w->resize ( 10, 100 );
  this->setSizePolicy ( QSizePolicy ( QSizePolicy.Fixed, QSizePolicy.MinimumExpanding ) );
  this->addWidget ( w );

  this->setAllowedAreas ( this->DOCK_AREA_TO_TB [ this->_area ] );
  this->parent ().addToolBar ( this->DOCK_AREA_TO_TB [ this->_area ], this );
  this->parent ().centralWidget ().installEventFilter ( this );

  this->setVisible ( false );
  this->hideDockWidgets ();*/
}

QAutoHideDockWidgets::QAutoHideDockWidgets ( QWidget *parent ) : QToolBar ( parent ) {

  /*QToolBar.__init__(this, parent)
  assert isinstance(parent, QMainWindow)
  assert area in this->DOCK_AREA_TO_TB
  this->_area = area
  this->setObjectName ( name );
  this->setWindowTitle ( name );

  this->setFloatable ( false );
  this->setMovable ( false );
  QWidget *w = new QWidget ();
  w->resize ( 10, 100 );
  this->setSizePolicy ( QSizePolicy ( QSizePolicy.Fixed, QSizePolicy.MinimumExpanding ) );
  this->addWidget ( w );

  this->setAllowedAreas ( this->DOCK_AREA_TO_TB [ this->_area ] );
  this->parent ().addToolBar ( this->DOCK_AREA_TO_TB [ this->_area ], this );
  this->parent ().centralWidget ().installEventFilter ( this );

  this->setVisible ( false );
  this->hideDockWidgets ();*/
}

void QAutoHideDockWidgets::_dockWidgets () {

  /*QMainWindow *mw = ( QMainWindow * ) this->parent ();
  for ( w in mw->findChildren ( QDockWidget ) ) {

    if ( mw->dockWidgetArea ( w ) == ( this->_area && !w.isFloating () ) ) {

      yield w;
    }
  }*/
}

void QAutoHideDockWidgets::paintEvent ( QPaintEvent *event ) {

  /*p = QPainter ( this );
  p.setPen ( Qt::black );
  p.setBrush ( Qt::black );
  if ( this->_area == Qt::LeftDockWidgetArea ) {

    p.translate ( QPointF ( 0, this->height () / 2 - 5 ) );
    p.drawPolygon ( QPointF ( 2, 0 ), QPointF ( 8, 5 ), QPointF ( 2, 10 ) );

  } else if ( this->_area == Qt::RightDockWidgetArea ) {

    p.translate ( QPointF ( 0, this->height () / 2 - 5 ) );
    p.drawPolygon ( QPointF ( 8, 0 ), QPointF ( 2, 5 ), QPointF ( 8, 10 ) );
  }*/
}

void QAutoHideDockWidgets::_multiSetVisible ( QWidget *widgets, bool state ) {

  /*if ( state ) {

    this->setVisible ( !state );
  }

  for ( w in widgets ) {

    w.setUpdatesEnabled ( false );
  }
  for ( w in widgets ) {

    w.setVisible ( state );
  }
  for ( w in widgets ) {

    w.setUpdatesEnabled ( true );
  }

  if ( !state && widgets ) {

    this->setVisible ( true );
  }*/
}

void QAutoHideDockWidgets::enterEvent ( QEvent *event ) {

  //this->showDockWidgets ();
}

bool QAutoHideDockWidgets::eventFilter ( QObject *obj, QEvent *event ) {

  /*if ( event->type () == QEvent::Enter ) {

    assert obj == this->parent ().centralWidget ();
    this->hideDockWidgets ();
  }*/
  return false;
}

void QAutoHideDockWidgets::setDockWidgetsVisible ( bool state ) {

  //this->_multiSetVisible ( list ( this->_dockWidgets () ), state );
}

void QAutoHideDockWidgets::showDockWidgets () {

  //this->setDockWidgetsVisible ( true );
}

void QAutoHideDockWidgets::hideDockWidgets () {

  //this->setDockWidgetsVisible ( false );
}




