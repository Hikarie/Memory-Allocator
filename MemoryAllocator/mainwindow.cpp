// mainwindow.cppp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("Memory Allocator");

    curr = 1;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_init_clicked()
{
    a = Allocator(ui->memo_size->text().toInt());
    qDebug()<<"system has been init"<<a.getSize();
    QMessageBox::warning(NULL, "提示", "内存已被初始化");
}

void MainWindow::on_start_clicked()
{
    if(a.getMemory().getHead()==NULL){
        QMessageBox::warning(NULL, "警告", "还没有初始化内存大小！");

    }
    else{
        bool success = allocate();
        qDebug()<<success<<curr;
        if(success == false){
            a.shrink();
            success = allocate();
            if(!success){
                QMessageBox::warning(NULL, "警告", "没有可以分配的内存！");
                update();
            }
        }
        if(success == true) {
            qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
            QColor c = QColor(rand()%256,rand()%256,rand()%256);
            colors.push_back(c);
            curr++;
            update();
        }
    }
}

bool MainWindow::allocate()
{
    int size = ui->size->text().toInt();
    bool success = false;
    switch(ui->comboBox->currentIndex()){
    case 0:
        success = a.BestFit(curr, size);
        break;
    case 1:
        success = a.FirstFit(curr, size);
        break;
    case 2:
        success = a.NextFit(curr, size);
        break;
    case 3:
        success = a.WorstFit(curr, size);
        break;
    return success;
    }
}

void MainWindow::on_abort_clicked()
{
    int id = ui->id->text().toInt();
    if(!a.release(id)){
        QMessageBox::warning(NULL, "警告", "内存中没有这个进程！");
    }
    update();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setBrush(QBrush(Qt::white));
    p.drawRect(650,50,300,700);
    Node *temp = a.getMemory().getHead();
    while(temp!=NULL&&temp->ID>-2){
        if(temp->ID!=H){
            int begin = temp->begin,end=temp->end;
            p.setBrush(QBrush(colors[temp->ID-1]));
            p.drawRect(650,50+((double)begin/a.getSize())*700,300,((double)(end-begin)/a.getSize())*700);
            qDebug()<<((double)begin/a.getSize())*700<<((double)(end-begin)/a.getSize())*700;
            p.drawText(800,50+((double)begin/a.getSize())*700+(double)(end-begin)/a.getSize()*350,QString::number(temp->ID));
            qDebug()<<temp->ID<<begin<<end;
        }
        qDebug()<<temp->ID<<temp->begin<<temp->end;
        if(temp->end == a.getSize())break;
        temp = temp->next;
    }
}



