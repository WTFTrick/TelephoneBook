#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>

#include <stdio.h>
#include <qjson/parser.h>
#include <qjson-qt5/qjson_export.h>
#include <qjson/serializer.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void QVariantToJson();
    void ClearAll();

private:
    Ui::MainWindow *ui;
    void CreatorConnections();
    void InterfaceSettings();
};

#endif // MAINWINDOW_H
