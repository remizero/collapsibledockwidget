#include "DockWidgetTitleBar.h"

#include <QDebug>

DockWidgetTitleBar::DockWidgetTitleBar ( QWidget *parent ) : QWidget ( parent ) {

  //import dockwidget_icons

  this->openIcon = QIcon ( ":/icons/arrow-down.svg" );
  this->closeIcon = QIcon ( ":/icons/arrow-right.svg" );
  this->pinIcon = QIcon ( ":/icons/pin.svg" );
  DockWidget *q = ( DockWidget * ) parent;
  this->floatButton = new DockWidgetTitleBarButton ( this );
  this->floatButton->setIcon ( q->style ()->standardIcon ( QStyle::SP_TitleBarNormalButton, nullptr, q ) );
  connect ( this->floatButton, SIGNAL ( clicked () ), this, SLOT ( toggleFloating () ) );
  this->floatButton->setVisible ( true );
  this->closeButton = new DockWidgetTitleBarButton ( this );
  this->closeButton->setIcon ( q->style ()->standardIcon ( QStyle::SP_TitleBarCloseButton, nullptr, q ) );
  connect ( this->closeButton, SIGNAL ( clicked () ), q, SLOT ( close () ) );
  this->closeButton->setVisible ( true );
  this->collapseButton = new DockWidgetTitleBarButton ( this );
  this->collapseButton->setIcon ( this->openIcon );
  this->collapseButton->setToolTip ( "Collapse the DockWidget" );
  this->collapseButton->setToolTipDuration ( 3000 );
  connect ( this->collapseButton, SIGNAL ( clicked () ), this, SLOT ( toggleCollapsed () ) );
  this->collapseButton->setVisible ( true );
  this->pinButton = new DockWidgetTitleBarButton ( this );
  this->pinButton->setIcon ( this->pinIcon );
  this->pinButton->setCheckable ( true );
  this->pinButton->setChecked ( true );
  connect ( this->pinButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( togglePinned ( bool ) ) );
  this->pinButton->setVisible ( true );
  //#this->connect(dockWidget, SIGNAL("featuresChanged(QDockWidget.DockWidgetFeatures)"), this->featuresChanged);
  connect ( q, SIGNAL ( featuresChanged ( QDockWidget::DockWidgetFeatures ) ), this, SLOT ( featuresChanged ( QDockWidget::DockWidgetFeatures ) ) );
  //dockWidget.featuresChanged.connect(this->featuresChanged);
  this->featuresChanged ( 0 );
}

void DockWidgetTitleBar::featuresChanged ( QDockWidget::DockWidgetFeatures features ) {

  Q_UNUSED ( features )
  DockWidget *q = ( DockWidget * ) this->parentWidget ();
  this->closeButton->setVisible ( DockWidget::hasFeature ( q, QDockWidget::DockWidgetClosable ) );
  this->floatButton->setVisible ( DockWidget::hasFeature ( q, QDockWidget::DockWidgetFloatable ) );
  //# this->resizeEvent(None);
}

QSize DockWidgetTitleBar::minimumSizeHint () const {

  return this->sizeHint ();
}

void DockWidgetTitleBar::paintEvent ( QPaintEvent *event ) {

  Q_UNUSED ( event )
  QStylePainter *p = new QStylePainter ( this );
  DockWidget *q = ( DockWidget * ) this->parentWidget ();
  if ( DockWidget::hasFeature ( q, QDockWidget::DockWidgetVerticalTitleBar ) ) {

    int fw = ( ( 1 || q->isFloating () ) && ( q->style ()->pixelMetric ( QStyle::PM_DockWidgetFrameWidth, nullptr, q ) || 0 ) );
    int mw = q->style ()->pixelMetric ( QStyle::PM_DockWidgetTitleMargin, nullptr, q );
    QStyleOptionDockWidget *titleOpt = new QStyleOptionDockWidget ();
    titleOpt->initFrom ( q );
    titleOpt->verticalTitleBar = true;
    titleOpt->rect = QRect ( QPoint ( fw, fw + mw + this->collapseButton->size ().height () + this->pinButton->size ().height () ), QSize ( this->geometry ().width () - ( fw * 2 ), this->geometry ().height () - ( fw * 2 ) - mw - this->collapseButton->size ().height () - this->pinButton->size ().height () ) );
    titleOpt->title = q->windowTitle ();
    titleOpt->closable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetClosable );
    titleOpt->floatable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetFloatable );
    p->drawControl ( QStyle::CE_DockWidgetTitle, *titleOpt );

  } else {

    int fw = ( q->isFloating () && ( q->style ()->pixelMetric ( QStyle::PM_DockWidgetFrameWidth, nullptr, q ) || 0 ) );
    int mw = q->style ()->pixelMetric ( QStyle::PM_DockWidgetTitleMargin, nullptr, q );
    QStyleOptionDockWidget *titleOpt = new QStyleOptionDockWidget ();
    titleOpt->initFrom ( q );
    titleOpt->rect = QRect ( QPoint ( fw + mw + this->collapseButton->size ().width () + this->pinButton->size ().width (), fw ), QSize ( this->geometry ().width () - ( fw * 2 ) - mw - this->collapseButton->size ().width () - this->pinButton->size ().width (), this->geometry ().height () - ( fw * 2 ) ) );
    titleOpt->title = q->windowTitle ();
    titleOpt->closable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetClosable );
    titleOpt->floatable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetFloatable );
    p->drawControl ( QStyle::CE_DockWidgetTitle, *titleOpt );
  }
}

void DockWidgetTitleBar::resizeEvent ( QResizeEvent *event ) {

  Q_UNUSED ( event )
  DockWidget *q = ( DockWidget * ) this->parentWidget ();
  if ( DockWidget::hasFeature ( q, QDockWidget::DockWidgetVerticalTitleBar ) ) {

    int fh = ( q->isFloating () && ( q->style ()->pixelMetric ( QStyle::PM_DockWidgetFrameWidth, nullptr, q ) || 0 ) );
    QStyleOptionDockWidget *opt = new QStyleOptionDockWidget ();
    opt->initFrom ( q );
    opt->verticalTitleBar = true;
    opt->rect = QRect ( QPoint ( fh, 40 ), /*# this->geometry().height() - (fh * 3)),*/ QSize ( this->geometry ().width () - ( fh * 2 ), fh * 2 ) );
    opt->title = q->windowTitle ();
    opt->closable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetClosable );
    opt->floatable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetFloatable );
    QRect floatRect = q->style ()->subElementRect ( QStyle::SE_DockWidgetFloatButton, opt, q );
    if ( !floatRect.isNull () ) {

      this->floatButton->setGeometry ( floatRect );
    }
    QRect closeRect = q->style ()->subElementRect ( QStyle::SE_DockWidgetCloseButton, opt, q );
    if ( !closeRect.isNull () ) {

      this->closeButton->setGeometry ( closeRect );
    }
    int top = fh;
    if ( !floatRect.isNull () ) {

      top = floatRect.x ();

    } else if ( !closeRect.isNull () ) {

      top = closeRect.x ();
    }
    QSize size = this->collapseButton->size ();
    if ( !closeRect.isNull () ) {

      size = this->closeButton->size ();

    } else if ( !floatRect.isNull () ) {

      size = this->floatButton->size ();
    }
    QRect collapseRect = QRect ( QPoint ( top, fh ), size );
    this->collapseButton->setGeometry ( collapseRect );
    QRect pinRect = QRect ( QPoint ( top, fh + collapseRect.height () + 1 ), size );
    this->pinButton->setGeometry ( pinRect );

  } else {

    int fw = ( q->isFloating () && ( q->style ()->pixelMetric ( QStyle::PM_DockWidgetFrameWidth, nullptr, q ) || 0 ) );
    QStyleOptionDockWidget *opt = new QStyleOptionDockWidget ();
    opt->initFrom ( q );
    opt->rect = QRect ( QPoint ( fw, fw ), QSize ( this->geometry ().width () - ( fw * 2 ), this->geometry ().height () - ( fw * 2 ) ) );
    opt->title = q->windowTitle ();
    opt->closable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetClosable );
    opt->floatable = DockWidget::hasFeature ( q, QDockWidget::DockWidgetFloatable );
    QRect floatRect = q->style ()->subElementRect ( QStyle::SE_DockWidgetFloatButton, opt, q );
    if ( !floatRect.isNull () ) {

      this->floatButton->setGeometry ( floatRect );
    }
    QRect closeRect = q->style ()->subElementRect ( QStyle::SE_DockWidgetCloseButton, opt, q );
    if ( !closeRect.isNull () ) {

      this->closeButton->setGeometry ( closeRect );
    }
    int top = fw;
    if ( !floatRect.isNull () ) {

      top = floatRect.y ();

    }  else if ( !closeRect.isNull () ) {

      top = closeRect.y ();
    }
    QSize size = this->collapseButton->size ();
    if ( !closeRect.isNull () ) {

      size = this->closeButton->size ();

    } else if ( !floatRect.isNull () ) {

      size = this->floatButton->size ();
    }
    QRect collapseRect = QRect ( QPoint ( fw, top ), size );
    this->collapseButton->setGeometry ( collapseRect );
    QRect pinRect = QRect ( QPoint ( fw + collapseRect.width () + 1, top ), size );
    this->pinButton->setGeometry ( pinRect );
  }
}

void DockWidgetTitleBar::setCollapsed ( bool collapsed ) {

  DockWidget *q = ( DockWidget * ) this->parentWidget ();
  if ( ( q && q->widget () && q->widget ()->isHidden () ) != collapsed ) {

    this->toggleCollapsed ();
  }
}

void DockWidgetTitleBar::setCollapsedIcon ( bool flag ) {

  this->collapseButton->setIcon ( flag ? this->openIcon : this->closeIcon );
}

QSize DockWidgetTitleBar::sizeHint () const {

  DockWidget *q = ( DockWidget * ) this->parentWidget ();
  int mw = q->style ()->pixelMetric ( QStyle::PM_DockWidgetTitleMargin, nullptr, q );
  int fw = q->style ()->pixelMetric ( QStyle::PM_DockWidgetFrameWidth, nullptr, q );
  QSize closeSize = QSize ( 0, 0 );
  if ( this->closeButton ) {

    closeSize = this->closeButton->sizeHint ();
  }
  QSize floatSize = QSize ( 0, 0 );
  if ( this->floatButton ) {

    floatSize = this->floatButton->sizeHint ();
  }
  QSize hideSize = QSize ( 0, 0 );
  if ( this->collapseButton ) {

    hideSize = this->collapseButton->sizeHint ();
  }
  QSize pinSize = QSize ( 0, 0 );
  if ( this->pinButton ) {

    pinSize = this->pinButton->sizeHint ();
  }
  //int buttonHeight = qMax ( qMax ( closeSize.height (), floatSize.height () ), hideSize.height (), pinSize.height () ) + 2;
  int buttonHeight = qMax ( qMax ( qMax ( closeSize.height (), floatSize.height () ), hideSize.height () ), pinSize.height () ) + 2;
  int buttonWidth = closeSize.width () + floatSize.width () + hideSize.width () + pinSize.width ();
  QFontMetrics titleFontMetrics = q->fontMetrics ();
  int fontHeight = titleFontMetrics.lineSpacing () + 2 * mw;
  int height = qMax ( buttonHeight, fontHeight );
  int width = buttonWidth + height + 4 * mw + 2 * fw;
  if ( DockWidget::hasFeature ( q, QDockWidget::DockWidgetVerticalTitleBar ) ) {

    //width, height = height, width;
    width = height;
    height = width;
  }
  return QSize ( width, height );
}

void DockWidgetTitleBar::toggleFloating () {

  DockWidget *q = ( DockWidget * ) this->parentWidget ();
  q->setFloating ( !q->isFloating () );
}

void DockWidgetTitleBar::togglePinned ( bool checked ) {

  ( ( DockWidget * ) this->parent () )->setPinned ( checked );
}

void DockWidgetTitleBar::toggleCollapsed () {

  qDebug () << "Está entrando por el toggleCollapsed de la clase DockWidgetTitleBar";
  DockWidget *q = ( DockWidget * ) this->parentWidget ();
  if ( !q ) {

    qDebug () << "Y como que está entrando por el if ( q ) {";
    return;
  }
  q->toggleCollapsed ();
  this->setCollapsedIcon ( q->isCollapsed () );
}
