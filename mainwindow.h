#include <QDate>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fetchDataFromApi(const QUrl& apiUrl);
    void on_listWidgetLeagues_currentRowChanged(int currentRow);

    void showAllMatches();
    void showLiveMatches();

    void fetchTodayMatches();
    void fetchLiveMatches();

private:
    Ui::MainWindow *ui;
    QListWidget *listWidgetMatches;
    QLabel *labelSelectedLeague;
    QPushButton *pushButtonAllMatches; // Dodaj deklarację
    QPushButton *pushButtonLiveMatches; // Dodaj deklarację
};

#endif // MAINWINDOW_H
