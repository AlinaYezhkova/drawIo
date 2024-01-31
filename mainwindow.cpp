#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include "CanvasView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    CanvasView *view = new CanvasView(m_doc, this);
    view->setScene(scene);
    setCentralWidget(view);
    m_doc.m_shapes.push_back( new Circle(Position(100, 100), 50, Qt::red, Qt::yellow) );
    m_doc.m_shapes.push_back( new Square(Position(-100, -100), 50, Qt::red, Qt::green) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

