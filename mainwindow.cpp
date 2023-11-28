#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>
#include <QUrlQuery>
#include "allmatcheswindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Połącz przyciski z odpowiednimi funkcjami
    connect(ui->pushButtonAllMatches, &QPushButton::clicked, this, &MainWindow::fetchTodayMatches);
    connect(ui->pushButtonAllMatches, &QPushButton::clicked, this, &MainWindow::showAllMatches);

    connect(ui->pushButtonLiveMatches, &QPushButton::clicked, this, &MainWindow::fetchLiveMatches);


    // Połącz sygnał z listWidgetLeagues z odpowiednią funkcją slot
    connect(ui->listWidgetMatches, &QListWidget::currentRowChanged, this, &MainWindow::on_listWidgetLeagues_currentRowChanged);

    // Reszta kodu konstruktora...
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetchDataFromApi(const QUrl& apiUrl)
{
    QNetworkAccessManager manager;
    QNetworkRequest request(apiUrl);
    request.setRawHeader("X-Auth-Token", "1086f2b5f3864c6293a660f88b8ff6f2");

    QNetworkReply *reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

            if (!jsonDoc.isEmpty()) {
                QJsonArray jsonArray = jsonDoc.array();

                // Przetwarzaj dostępne ligi
                for (const QJsonValue& leagueValue : jsonArray) {
                    QJsonObject leagueObj = leagueValue.toObject();
                    QString leagueName = leagueObj["name"].toString();

                    // Dodaj nazwę ligi do QListWidget
                    ui->listWidgetMatches->addItem(leagueName);
                }
            } else {
                qDebug() << "Błąd zapytania HTTP: " << reply->errorString();
            }
            reply->deleteLater(); // Zwolnienie zasobów
        }
    });
}

void MainWindow::on_listWidgetLeagues_currentRowChanged(int currentRow)
{
    // Sprawdź, czy indeks jest prawidłowy
    if (currentRow >= 0 && currentRow < ui->listWidgetMatches->count()) {
        // Pobierz nazwę ligi dla danego indeksu
        QString selectedLeagueName = ui->listWidgetMatches->item(currentRow)->text();

        // Wyświetl nazwę ligi w QLabel
        ui->labelSelectedLeagues->setText("Wybrana liga: " + selectedLeagueName);

        // Tutaj możesz dodać dodatkową logikę związaną z wybraną ligą
        // np. pobieranie meczów, statystyk drużyn itp.
    }
}

void MainWindow::fetchTodayMatches()
{
    // Wyczyszczenie listy meczów przed dodaniem nowych
    ui->listWidgetMatches->clear();

    // Tutaj dodaj kod do pobierania wszystkich dzisiejszych meczów
    // Użyj funkcji fetchDataFromApi z odpowiednimi parametrami dla dzisiejszych meczów
    QUrl apiUrl("https://api.football-data.org/v4/matches");
    QUrlQuery query;
    query.addQueryItem("dateFrom", QDate::currentDate().toString("yyyy-MM-dd"));
    query.addQueryItem("dateTo", QDate::currentDate().toString("yyyy-MM-dd"));
    apiUrl.setQuery(query);

    fetchDataFromApi(apiUrl);
}

void MainWindow::fetchLiveMatches()
{
    // Wyczyszczenie listy meczów przed dodaniem nowych
    ui->listWidgetMatches->clear();

    // Tutaj dodaj kod do pobierania meczów trwających na żywo
    // Użyj funkcji fetchDataFromApi z odpowiednimi parametrami dla meczów trwających
    QUrl apiUrl("https://api.football-data.org/v4/matches");
    QUrlQuery query;
    query.addQueryItem("status", "LIVE");
    apiUrl.setQuery(query);

    fetchDataFromApi(apiUrl);
}
void MainWindow::showAllMatches() {
    AllMatchesWindow *allMatchesWindow = new AllMatchesWindow(this);
    allMatchesWindow->show();
    // Pobierz listę wszystkich meczów z API (możesz użyć odpowiedniej funkcji fetchDataFromApi)
    QUrl apiUrl("https://api.football-data.org/v4/matches");
    fetchDataFromApi(apiUrl);
}

void MainWindow::showLiveMatches() {
    // Pobierz listę meczów trwających na żywo z API (możesz użyć odpowiedniej funkcji fetchDataFromApi)
    QUrl apiUrl("https://api.football-data.org/v4/matches");
    QUrlQuery query;
    query.addQueryItem("status", "LIVE");
    apiUrl.setQuery(query);

    fetchDataFromApi(apiUrl);
}

