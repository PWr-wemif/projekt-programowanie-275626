#ifndef ALLMATCHESWINDOW_H
#define ALLMATCHESWINDOW_H

#include <QMainWindow>

namespace Ui {
class AllMatchesWindow;
}

class AllMatchesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AllMatchesWindow(QWidget *parent = nullptr);
    ~AllMatchesWindow();

private:
    Ui::AllMatchesWindow *ui;
};

#endif // ALLMATCHESWINDOW_H
