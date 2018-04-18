#ifndef QAUTOHIDEDOCKWIDGETS_H
#define QAUTOHIDEDOCKWIDGETS_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QToolBar>

class QAutoHideDockWidgets : QToolBar {

    Q_OBJECT

  public:
    QAutoHideDockWidgets ( const QString &title, QWidget *parent = Q_NULLPTR );
    QAutoHideDockWidgets ( QWidget *parent = Q_NULLPTR );

    void _dockWidgets ();
    void paintEvent ( QPaintEvent *event ) Q_DECL_OVERRIDE;
    void _multiSetVisible ( QWidget *widgets, bool state );
    void enterEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    bool eventFilter ( QObject *obj, QEvent *event ) Q_DECL_OVERRIDE;
    void setDockWidgetsVisible ( bool state );
    void showDockWidgets ();
    void hideDockWidgets ();
};

#endif // QAUTOHIDEDOCKWIDGETS_H

/**
 *
 * class QAutoHideDockWidgets(QToolBar):
    """
    QMainWindow "mixin" which provides auto-hiding support for dock widgets
    (not toolbars).
    """
    DOCK_AREA_TO_TB = {
        Qt.LeftDockWidgetArea: Qt.LeftToolBarArea,
        Qt.RightDockWidgetArea: Qt.RightToolBarArea,
        Qt.TopDockWidgetArea: Qt.TopToolBarArea,
        Qt.BottomDockWidgetArea: Qt.BottomToolBarArea,
    }

    def __init__(self, area, parent, name="AUTO_HIDE"):
        QToolBar.__init__(self, parent)
        assert isinstance(parent, QMainWindow)
        assert area in self.DOCK_AREA_TO_TB
        self._area = area
        self.setObjectName(name)
        self.setWindowTitle(name)

        self.setFloatable(False)
        self.setMovable(False)
        w = QWidget(None)
        w.resize(10, 100)
        self.setSizePolicy(QSizePolicy(QSizePolicy.Fixed, QSizePolicy.MinimumExpanding))
        self.addWidget(w)

        self.setAllowedAreas(self.DOCK_AREA_TO_TB[self._area])
        self.parent().addToolBar(self.DOCK_AREA_TO_TB[self._area], self)
        self.parent().centralWidget().installEventFilter(self)

        self.setVisible(False)
        self.hideDockWidgets()

    def _dockWidgets(self):
        mw = self.parent()
        for w in mw.findChildren(QDockWidget):
            if mw.dockWidgetArea(w) == self._area and not w.isFloating():
                yield w

    def paintEvent(self, event):
        p = QPainter(self)
        p.setPen(Qt.black)
        p.setBrush(Qt.black)
        if self._area == Qt.LeftDockWidgetArea:
            p.translate(QPointF(0, self.height() / 2 - 5))
            p.drawPolygon(QPointF(2,0), QPointF(8,5), QPointF(2,10))
        elif self._area == Qt.RightDockWidgetArea:
            p.translate(QPointF(0, self.height() / 2 - 5))
            p.drawPolygon(QPointF(8,0), QPointF(2,5), QPointF(8,10))

    def _multiSetVisible(self, widgets, state):
        if state:
            self.setVisible(False)

        for w in widgets:
            w.setUpdatesEnabled(False)
        for w in widgets:
            w.setVisible(state)
        for w in widgets:
            w.setUpdatesEnabled(True)

        if not state and widgets:
            self.setVisible(True)

    def enterEvent(self, event):
        self.showDockWidgets()

    def eventFilter(self, obj, event):
        if event.type() == QEvent.Enter:
            assert obj == self.parent().centralWidget()
            self.hideDockWidgets()
        return False

    def setDockWidgetsVisible(self, state):
        self._multiSetVisible(list(self._dockWidgets()), state)

    def showDockWidgets(self): self.setDockWidgetsVisible(True)
    def hideDockWidgets(self): self.setDockWidgetsVisible(False)
 *
 */
