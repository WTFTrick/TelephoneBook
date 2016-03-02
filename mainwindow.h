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


private:
    Ui::MainWindow *ui;
    void CreatorConnections();
    void InterfaceSettings();
    QLabel* connect_status;

    int nPort;
    QTcpSocket* m_pTcpSocket;
    quint32     m_nNextBlockSize;

};

#endif // MAINWINDOW_H
