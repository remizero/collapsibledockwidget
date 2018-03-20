#ifndef STACKLAYOUT_H
#define STACKLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QSize>
#include <QSizePolicy>
#include <QStackedLayout>
#include <QWidget>

class StackLayout : public QStackedLayout
{
  public:
    StackLayout ();
    StackLayout ( QWidget *parent );
    StackLayout ( QLayout *parentLayout );
    ~StackLayout ();

    QSize clipMinMax ( QSize size, QSize minSize, QSize maxSize ) const;
    QSize fixSizePolicy ( QSize size, QSize hint, QSizePolicy policy );
    QRect geometry () const Q_DECL_OVERRIDE;
    QSize maximumSize () const Q_DECL_OVERRIDE;
    QSize minimumSize () const Q_DECL_OVERRIDE;
    void setGeometry ( const QRect &rect ) Q_DECL_OVERRIDE;
    QSize sizeHint () const Q_DECL_OVERRIDE;

  public slots:
    void onCurrentChanged ( int index );

  private:
    QRect *rect;
};

#endif // STACKLAYOUT_H

/**
 *
 */
