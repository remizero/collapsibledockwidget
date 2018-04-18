#ifndef CROSSFADEPIXMAPWIDGET_H
#define CROSSFADEPIXMAPWIDGET_H

#include <QtMath>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QPoint>
#include <QSize>
#include <QSizePolicy>
#include <QWidget>

class CrossFadePixmapWidget : public QWidget {

    Q_OBJECT
    Q_PROPERTY ( float blendingFactor_ READ getBlendingFactor WRITE setBlendingFactor )

  public:
    explicit CrossFadePixmapWidget ( QPixmap pixmap1, QPixmap pixmap2, QWidget *parent = 0 );
    ~CrossFadePixmapWidget ();

    float getBlendingFactor ();
    void setBlendingFactor ( float factor );
    void setPixmap ( QPixmap pixmap );
    void setPixmap2 ( QPixmap pixmap );
    void paintEvent ( QPaintEvent *event ) Q_DECL_OVERRIDE;
    QSize sizeHint () const Q_DECL_OVERRIDE;

  signals:

  public slots:

  private:
      float blendingFactor;
      float blendingFactor_;
    QPixmap pixmap1;
    QPixmap pixmap2;
};

#endif // CROSSFADEPIXMAPWIDGET_H
