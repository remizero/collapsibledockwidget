#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CollapsibleDockWidget.h"
#include "DockWidget.h"

#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QMainWindow>
#include <QStringList>
#include <QTextEdit>

class MainWindow : public QMainWindow {

    Q_OBJECT

  public:
    MainWindow ( QWidget *parent = 0 );
    ~MainWindow ();
    // TODO: Un ejemplo interesante
    // http://www.scottenglert.com/2016/02/24/code-snippet-qt-dockwidget-tab-click-simulation/
    // https://bitbucket.org/henning/
    // https://svn.labri.fr/repos/tulip_plugins/public/branches/testing_3_6_maint/controllers/TulipLite/include/CollapsableDockWidget.h
    // https://www.linux-apps.com/p/1131417/
    // https://github.com/juangburgos/WtDesigner
};

#endif // MAINWINDOW_H
