#include "mainwindow.h"

MainWindow::MainWindow ( QWidget *parent ) : QMainWindow ( parent ) {


  /**
   * Version 1
   * AnimatedStackedWidget.h
   * AnimatedStackedWidget.cpp
   * CollapsibleDockWidget.h
   * CollapsibleDockWidget.cpp
   * CrossFadePixmapWidget.h
   * CrossFadePixmapWidget.cpp
   * StackLayout.h
   * StackLayout.cpp
   */

   /*
  CollapsibleDockWidget *dock = new CollapsibleDockWidget ( tr ( "Customers" ), this );
  dock->setAllowedAreas ( Qt::TopDockWidgetArea );
  dock->resize ( 100, 100 );
  QListWidget *customerList = new QListWidget ( dock );
  customerList->addItems ( QStringList ()
          << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
          << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
          << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
          << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
          << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
          << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula" );
  dock->setWidget ( customerList );
  this->addDockWidget ( Qt::TopDockWidgetArea, dock );
  this->setCentralWidget ( new QTextEdit ( this ) );
   */

  /**
   * Version 2
   * QAutoHideDockWidget.h
   * QAutoHideDockWidget.cpp
   */



  /**
   * Version 3
   * DockWidgetTitleBarButton.h
   * DockWidgetTitleBarButton.cpp
   * DockMainWidgetWrapper.h
   * DockMainWidgetWrapper.cpp
   * DockWidget.h
   * DockWidget.cpp
   * DockWidgetTitleBar.h
   * DockWidgetTitleBar.cpp
   */

  DockWidget *dock1 = new DockWidget ( "1st dockwidget", this );
  QComboBox *combo = new QComboBox ( dock1 );
  dock1->setWidget ( combo );
  this->addDockWidget ( Qt::TopDockWidgetArea, dock1 );
  DockWidget *dock2 = new DockWidget ( "2nd dockwidget", this );
  dock2->setFeatures ( dock1->features () | QDockWidget::DockWidgetVerticalTitleBar );
  QPushButton *button = new QPushButton ( "Hello, world!", dock2 );
  dock2->setWidget ( button );
  this->addDockWidget ( Qt::RightDockWidgetArea, dock2 );
  QTextEdit *edit = new QTextEdit ( this );
  this->setCentralWidget ( edit );



}

MainWindow::~MainWindow () {}
