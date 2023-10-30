#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Wywołaj funkcję do pobierania danych
    fetchDataFromApi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetchDataFromApi()
{
    QNetworkAccessManager manager;
    QUrl apiUrl("https://api.football-data.org/v4/competitions"); // Endpoint API do pobierania lig

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

                    // Możesz teraz wyświetlić nazwę ligi w interfejsie użytkownika, np. w QLabel
                    // Przykład: ui->label->setText(leagueName);
                }
            } else {
                qDebug() << "Błąd zapytania HTTP: " << reply->errorString();
            }
            reply->deleteLater(); // Zwolnienie zasobów
        } // <--- Poprawiony nawias zamykający
    }); // <--- Poprawiony nawias zamykający
}

