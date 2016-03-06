#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>
#include <QtNetwork>
#include <QTcpSocket>
#include <QLabel>

#include <stdio.h>

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
    void ToJson();
    void ClearAll();
    void slotReadyRead();
    void slotConnected();
    void connectToHost();
    void JSONtoServer();

private:
    Ui::MainWindow *ui;
    bool connected_state;
    void CreatorConnections();
    void InterfaceSettings();
    QJsonObject object;
    QJsonObject object2;
    quint8 id;
    QJsonDocument document;

    int nPort;
    QTcpSocket* m_pTcpSocket;
    quint32     m_nNextBlockSize;

};

#endif // MAINWINDOW_H
