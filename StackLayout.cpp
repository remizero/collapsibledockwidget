#include "StackLayout.h"

StackLayout::StackLayout() : QStackedLayout () {

  this->rect = new QRect ();
  connect ( this, SIGNAL ( currentChanged ( int ) ), this, SLOT ( onCurrentChanged ( int ) ) );
}

StackLayout::StackLayout ( QWidget *parent ) : QStackedLayout ( parent ) {

  this->rect = new QRect ();
  connect ( this, SIGNAL ( currentChanged ( int ) ), this, SLOT ( onCurrentChanged ( int ) ) );
}

StackLayout::StackLayout ( QLayout *parentLayout ) : QStackedLayout ( parentLayout ) {

  this->rect = new QRect ();
  connect ( this, SIGNAL ( currentChanged ( int ) ), this, SLOT ( onCurrentChanged ( int ) ) );
}

StackLayout::~StackLayout () {}

QSize StackLayout::clipMinMax ( QSize size, QSize minSize, QSize maxSize ) const {

  return size.expandedTo ( minSize ).boundedTo ( maxSize );
}

QSize StackLayout::fixSizePolicy ( QSize size, QSize hint, QSizePolicy policy ) {

  /*"""
      Fix size so it conforms to the size policy and the given size hint.
      """*/
  int height = hint.height ();
  int width = hint.width ();
  const Qt::Orientations expanding = policy.expandingDirections ();
  const QSizePolicy::Policy hpolicy = policy.horizontalPolicy ();
  const QSizePolicy::Policy vpolicy = policy.verticalPolicy ();

  if ( expanding & Qt::Horizontal ) {

    if ( width > size.width () ) {

      width = width;

    } else {

      width = size.width ();
    }
    //width = max ( width, size.width () );
  }
  if ( hpolicy == QSizePolicy::Maximum ) {

    if ( width < size.width () ) {

      width = width;

    } else {

      width = size.width ();
    }
    //width = min ( width, size.width () );
  }
  if ( expanding & Qt::Vertical ) {

    if ( height > size.height () ) {

      height = height;

    } else {

      height = size.height ();
    }
    //height = max ( height, size.height () );
  }
  if ( vpolicy == QSizePolicy::Maximum ) {

    if ( height < size.height () ) {

      height = height;

    } else {

      height = size.height ();
    }
    //height = min ( height, hint.height () );
  }

  return QSize ( width, height ).boundedTo ( size );
}

QRect StackLayout::geometry () const {

//# Reimplemented due to QTBUG-47107.
  return QRect ( this->rect->topLeft (), this->rect->size () );
}

QSize StackLayout::maximumSize () const {

  QWidget *current =  this->currentWidget ();
  if ( current ) {

    return current->maximumSize ();

  } else {

    return QStackedLayout::maximumSize ();
  }
}

QSize StackLayout::minimumSize () const {

  QWidget *current =  this->currentWidget ();
  if ( current ) {

    return current->minimumSize ();

  } else {

    return QStackedLayout::minimumSize ();
  }
}

void StackLayout::onCurrentChanged ( int index ) {

  /*"""
  Current widget changed, invalidate the layout.
  """*/
   this->invalidate ();
}

void StackLayout::setGeometry ( const QRect &rect ) {

  if ( rect != this->rect->normalized () ) {

    this->rect = new QRect ( rect.topLeft (), rect.size () );
    QStackedLayout::setGeometry ( rect );

    for ( int i = 0; i < this->count (); i++ ) {

      QWidget *w =  this->widget ( i );
      const QSize hint = w->sizeHint ();
      QRect geom = QRect ( rect );
      QSize size = this->clipMinMax ( rect.size (), w->minimumSize (), w->maximumSize () );
      size = this->fixSizePolicy ( size, hint, w->sizePolicy () );
      geom.setSize ( size );
      if ( geom != w->geometry () ) {

        w->setGeometry ( geom );
      }
    }
  }
}

QSize StackLayout::sizeHint () const {

  QWidget *current = this->currentWidget ();
  if ( current ) {

    QSize hint = current->sizeHint ();
    // Clip the hint with min/max sizes.
    hint = this->clipMinMax ( hint, current->minimumSize (), current->maximumSize () );
    return hint;

  } else {

    return QStackedLayout::sizeHint ();
  }
}
