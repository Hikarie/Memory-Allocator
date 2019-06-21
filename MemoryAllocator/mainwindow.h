// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "allocator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();

    void on_abort_clicked();

    void on_init_clicked();

private:
    Ui::MainWindow *ui;
    Allocator a;
    int curr;
    vector<QColor> colors;


public:
    void paintEvent(QPaintEvent *event);
    bool allocate();
};

#endif // MAINWINDOW_H
