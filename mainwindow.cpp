#include "mainwindow.h"

MainWindow::MainWindow ( QWidget *parent ) : QMainWindow ( parent ) {

  CollapsibleDockWidget *dock = new CollapsibleDockWidget ( tr ( "Customers" ), this );
  dock->setAllowedAreas ( Qt::TopDockWidgetArea );
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
}

MainWindow::~MainWindow () {}
