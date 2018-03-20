#include "CrossFadePixmapWidget.h"

CrossFadePixmapWidget::CrossFadePixmapWidget ( QPixmap pixmap1, QPixmap pixmap2 , QWidget *parent ) : QWidget ( parent ) {

  this->setPixmap ( pixmap1 );
  this->setPixmap2 ( pixmap2 );
  this->blendingFactor_ = 0.0;
  this->setSizePolicy ( QSizePolicy::Fixed, QSizePolicy::Fixed );

  /*
   * self.setPixmap(pixmap1)
   * self.setPixmap2(pixmap2)
   * self.blendingFactor_ = 0.0
   * self.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
   */
}

CrossFadePixmapWidget::~CrossFadePixmapWidget () {}

float CrossFadePixmapWidget::getBlendingFactor () {

  /*"""
  Pixmap blending factor between 0.0 and 1.0
  """*/
  return this->blendingFactor;
}

void CrossFadePixmapWidget::setBlendingFactor ( float factor ) {

  /*"""
  Set the blending factor between the two pixmaps.
  """*/
  this->blendingFactor = factor;
  this->updateGeometry ();
}

void CrossFadePixmapWidget::setPixmap ( QPixmap pixmap ) {

  /*"""
  Set pixmap 1
  """*/
  this->pixmap1 = pixmap;
  this->updateGeometry ();
}

void CrossFadePixmapWidget::setPixmap2 ( QPixmap pixmap ) {

  /*"""
  Set pixmap 2
  """*/
  this->pixmap2 = pixmap;
  this->updateGeometry ();
}

void CrossFadePixmapWidget::paintEvent ( QPaintEvent *event ) {

  /*"""
  Paint the interpolated pixmap image.
  """*/
  QPainter *p = new QPainter ();
  p->setClipRect ( event->rect () );
  //float factor = this->blendingFactor_ ** 2;
  float factor = qPow ( this->blendingFactor_, 2 );
  if ( !this->pixmap1.isNull () && ( 1.0 - factor ) ) {

    p->setOpacity ( 1.0 - factor );
    p->drawPixmap ( QPoint ( 0, 0 ), this->pixmap1 );
  }
  if ( !this->pixmap2.isNull () && factor ) {

    p->setOpacity ( factor );
    p->drawPixmap ( QPoint ( 0, 0 ), this->pixmap2 );
  }
}

QSize CrossFadePixmapWidget::sizeHint () const {

  /*"""
  Return an interpolated size between pixmap1.size()
  and pixmap2.size()

  """*/
  if ( !this->pixmap1.isNull () && !this->pixmap2.isNull () ) {

    QSize size1 = this->pixmap1.size ();
    QSize size2 = this->pixmap2.size ();
    return size1 + this->blendingFactor * ( size2 - size1 );
  }
  return QWidget::sizeHint ();
}
