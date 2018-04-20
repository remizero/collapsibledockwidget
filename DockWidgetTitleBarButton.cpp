#include "DockWidgetTitleBarButton.h"

DockWidgetTitleBarButton::DockWidgetTitleBarButton ( QWidget *parent ) : QAbstractButton ( parent ) {

  this->setFocusPolicy ( Qt::NoFocus );
}

void DockWidgetTitleBarButton::enterEvent ( QEvent *event ) {

  if ( this->isEnabled () ) {

    this->update ();
  }
  QAbstractButton::enterEvent ( event );
}

void DockWidgetTitleBarButton::leaveEvent ( QEvent *event ) {

  if ( this->isEnabled () ) {

    this->update ();
  }
  QAbstractButton::leaveEvent ( event );
}

void DockWidgetTitleBarButton::paintEvent ( QPaintEvent *event ) {

  Q_UNUSED ( event )
  QPainter *p = new QPainter ( this );
  QRect r = this->rect ();
  Q_UNUSED ( r )
  //QStyleOptionToolButton opt = QStyleOptionToolButton ();
  QStyleOptionToolButton *opt = new QStyleOptionToolButton ();
  opt->init ( this );
  opt->state |= QStyle::State_AutoRaise;
  if ( this->isEnabled () && this->underMouse () && !this->isChecked () && !this->isDown () ) {

    opt->state |= QStyle::State_Raised;
  }
  if ( this->isChecked () ) {

    opt->state |= QStyle::State_On;
  }
  if ( this->isDown () ) {

    opt->state |= QStyle::State_Sunken;
  }
  this->style ()->drawPrimitive ( QStyle::PE_PanelButtonTool, opt, p, this );
  opt->icon = this->icon ();
  opt->subControls = QStyle::SubControls ();
  opt->activeSubControls = QStyle::SubControls ();
  opt->features = QStyleOptionToolButton::None;
  opt->arrowType = Qt::NoArrow;
  int size = this->style ()->pixelMetric ( QStyle::PM_SmallIconSize, nullptr, this );
  opt->iconSize = QSize ( size, size );
  this->style ()->drawComplexControl ( QStyle::CC_ToolButton, opt, p, this );
}

QSize DockWidgetTitleBarButton::sizeHint () const {

  this->ensurePolished ();
  int margin = this->style ()->pixelMetric ( QStyle::PM_DockWidgetTitleBarButtonMargin, nullptr, this );
  if ( this->icon ().isNull () ) {

    return QSize ( margin, margin );
  }
  int iconSize = this->style ()->pixelMetric ( QStyle::PM_SmallIconSize, nullptr, this );
  QPixmap pm = this->icon ().pixmap ( iconSize );
  return QSize ( pm.width () + margin, pm.height () + margin );
}
