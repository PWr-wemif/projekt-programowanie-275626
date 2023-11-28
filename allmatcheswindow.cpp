#include "allmatcheswindow.h"
#include "ui_allmatcheswindow.h"


AllMatchesWindow::AllMatchesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AllMatchesWindow)
{
    ui->setupUi(this);
    // Tutaj możesz dodać dodatkową logikę dla okna wszystkich meczów
}

AllMatchesWindow::~AllMatchesWindow()
{
    delete ui;
}
