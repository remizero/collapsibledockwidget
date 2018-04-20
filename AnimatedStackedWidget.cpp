#include "AnimatedStackedWidget.h"

AnimatedStackedWidget::AnimatedStackedWidget ( bool animationEnabled, QWidget *parent, Qt::WindowFlags f ) : QFrame ( parent, f ) {

  this->animationEnabled = animationEnabled;
  this->stackLayout = new StackLayout ();
  this->fadeWidget = new CrossFadePixmapWidget ( QPixmap (), QPixmap (), this );

  this->transitionAnimation = new QPropertyAnimation ( this->fadeWidget, "blendingFactor_", this );
  //this->transitionAnimation = QPropertyAnimation ( this->fadeWidget, this->fadeWidget->getBlendingFactor (), this );
  this->transitionAnimation->setStartValue ( 0.0 );
  this->transitionAnimation->setEndValue ( 1.0 );
  this->transitionAnimation->setDuration ( this->animationEnabled ? 100 : 0 );

  connect ( this->transitionAnimation, SIGNAL ( finished () ), this, SLOT ( onTransitionFinished () ) );

  this->stackLayout->addWidget ( this->fadeWidget );
  connect ( this->stackLayout, SIGNAL ( currentChanged ( int ) ), this, SLOT ( onLayoutCurrentChanged ( int ) ) );

  this->setLayout ( this->stackLayout );

  //this->widgetList = [];
  this->currentIndex = -1;
  this->nextCurrentIndex = -1;
}

AnimatedStackedWidget::~AnimatedStackedWidget () {}

QWidget *AnimatedStackedWidget::addWidget ( QWidget *widget ) {

  /*"""
  Append the widget to the stack and return its index.
  """*/
  return this->insertWidget ( ( ( QStackedLayout * ) this->layout () )->count (), widget );
}

int AnimatedStackedWidget::count () {
  /*"""
  Return the number of widgets in the stack.
  """*/
  return qMax ( this->layout ()->count () - 1, 0 );
}

int AnimatedStackedWidget::getCurrentIndex () {

  /*"""
  Return the current shown widget index.
  """*/
  return this->currentIndex;
}

bool AnimatedStackedWidget::hasPendingResize ( QWidget *widget ) {

  return widget->testAttribute ( Qt::WA_PendingResizeEvent ) || !widget->testAttribute ( Qt::WA_WState_Created );
}

int AnimatedStackedWidget::indexOf ( QWidget *widget ) {
  /*"""
  Return the index of `widget` in the stack.
  """*/
  return this->widgetList.indexOf ( widget );
}

QWidget *AnimatedStackedWidget::insertWidget ( int index, QWidget *widget ) {

  /*"""
  Insert `widget` into the stack at `index`.
  """*/
  index = qMin ( index, this->count () );
  this->widgetList.insert ( index, widget );
  if ( ( index <= this->currentIndex ) || ( this->currentIndex == -1 ) ) {

    this->currentIndex += 1;
  }
  ( ( QStackedLayout * ) this->layout () )->insertWidget ( index, widget );
  return widget;
}

bool AnimatedStackedWidget::isAnimationEnabled () {

  /*"""
  Is the transition animation enabled.
  """*/
  return this->animationEnabled;
}

void AnimatedStackedWidget::onLayoutCurrentChanged ( int index ) {

    //# Suppress transitional fadeWidget current widget
  if ( index != this->count () ) {

    emit currentChanged ( index );
  }
}

void AnimatedStackedWidget::onTransitionFinished () {

  /*"""
  Transition has finished.
  """*/
  //log.debug("Stack transition finished (%s)" % str(this->objectName()))
  this->fadeWidget->setBlendingFactor ( 1.0 );
  this->currentIndex = this->nextCurrentIndex;
  bool oldState = this->updatesEnabled ();
  this->setUpdatesEnabled ( false );
  //with updates_disabled(self):
  ( ( QStackedLayout * ) this->layout () )->setCurrentIndex ( this->currentIndex );
  this->setUpdatesEnabled ( oldState );

  emit transitionFinished ();
}

QWidget *AnimatedStackedWidget::removeWidget ( QWidget *widget ) {
  /*"""
  Remove `widget` from the stack.
  .. note:: The widget is hidden but is not deleted.
  """*/
  int index = this->widgetList.indexOf ( widget );
  this->layout ()->removeWidget ( widget );
  this->widgetList.removeAt ( index );
  return widget;
}

void AnimatedStackedWidget::setAnimationEnabled ( bool animationEnabled ) {

  /*"""
  Enable/disable transition animations.
  """*/
  if ( this->animationEnabled != animationEnabled ) {

    this->animationEnabled = animationEnabled;
  }
  this->transitionAnimation->setDuration ( this->animationEnabled ? 100 : 0 );
}

void AnimatedStackedWidget::setCurrentIndex ( int index ) {
  /*"""
  Set the current shown widget index.
  """*/
  index = qMax ( qMin ( index, this->count () - 1 ), 0 );
  if ( this->currentIndex == -1 ) {

    ( ( QStackedLayout * ) this->layout () )->setCurrentIndex ( index );
    this->currentIndex = index;
    return;
  }

//#        if not this->animationEnabled():
//#            this->layout().setCurrentIndex(index);
//#            this->currentIndex = index;
//#            return;

//  # else start the animation
  QWidget *current = this->widgetList.at ( this->currentIndex );
  QWidget *next_widget = this->widgetList.at ( index );
  QPixmap current_pix;
  QPixmap next_pix;
  if ( !this->hasPendingResize ( current ) ) {

    current_pix = current->grab ();
  }
  if ( !this->hasPendingResize ( next_widget ) ) {

    next_pix = next_widget->grab ();
  }

  //with updates_disabled(self):
  bool oldState = this->updatesEnabled ();
  this->setUpdatesEnabled ( false );
  this->fadeWidget->setPixmap ( current_pix );
  this->fadeWidget->setPixmap2 ( next_pix );
  this->nextCurrentIndex = index;
  this->transitionStart ();
  this->setUpdatesEnabled ( oldState );
}

void AnimatedStackedWidget::setCurrentWidget ( QWidget *widget ) {

  /*"""
  Set the current shown widget.
  """*/
  int index = this->widgetList.indexOf ( widget );
  this->setCurrentIndex ( index );
}

QSize AnimatedStackedWidget::sizeHint () const {

  QSize hint = QFrame::sizeHint ();
  if ( hint.isEmpty () ) {

    hint = QSize ( 0, 0 );
  }
  return hint;
}

void AnimatedStackedWidget::transitionStart () {

  /*"""
  Start the transition.
  """*/
  //log.debug("Stack transition start (%s)", str(this->objectName()))
  //# Set the fade widget as the current widget
  this->fadeWidget->setBlendingFactor ( 0.0 );
  ( ( QStackedLayout * ) this->layout () )->setCurrentWidget ( this->fadeWidget );
  this->transitionAnimation->start ();
  emit this->transitionStarted ();
}

QWidget *AnimatedStackedWidget::widget ( int index ) {
  /*"""
  Return the widget at `index`
  AnimatedStackedWidget.obj:-1: error: LNK2001: unresolved external symbol "public: virtual struct QMetaObject const * __cdecl AnimatedStackedWidget::metaObject(void)const " (?metaObject@AnimatedStackedWidget@@UEBAPEBUQMetaObject@@XZ)
  """*/
  return this->widgetList.at ( index );
}
