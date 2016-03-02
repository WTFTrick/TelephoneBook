#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : nPort(2323), m_nNextBlockSize(0), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InterfaceSettings();
    CreatorConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    close();
}

void MainWindow::ToJson()
{
    if ((ui->tel_lineEdit->text()!= "----")&(ui->name_lineEdit->text()!=""))
    {
        qDebug() << connected_state;
        QVariantMap map;
        map.insert("thelephone", ui->tel_lineEdit->text());
        map.insert("name", ui->name_lineEdit->text());

        object = QJsonObject::fromVariantMap(map);
        document.setObject(object);

        /*QFile jsonFile("/home/kopylov/tb.json");
        jsonFile.open(QFile::Append);
        jsonFile.write(document.toJson());
        jsonFile.close();*/

        ui->listWidget->addItem(document.toJson());
        ui->statusBar->showMessage("Information successfull convert to JSON!");
        ui->pb_toServer->setEnabled(true);
    }
    else
    {
        ui->listWidget->clear();
        ui->listWidget->addItem("Fill all the fields before convert information to JSON!");
        ui->statusBar->showMessage("Failed when convert information to JSON!");
    }
}

void MainWindow::ClearAll()
{

    ui->listWidget->clear();
    ui->pb_toServer->setEnabled(false);
    ui->statusBar->showMessage("JSON cleared!");

    /*QFile file("/home/kopylov/tb.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        file.write("");
    }
    file.close();*/
}

void MainWindow::connectToHost()
{
    m_pTcpSocket->connectToHost(ui->le_connect->text(), nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
}

void MainWindow::slotConnected()
{
    ui->statusBar->showMessage("Connection successfull");
    qDebug() << "Received the connected() signal";
    qDebug() << "Connection successfull";
    if(m_pTcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        ui->pb_connect->setDisabled(true);
    }
}

void MainWindow::slotReadyRead()
{

}

void MainWindow::CreatorConnections()
{
    connect(ui->pb_toJSON, SIGNAL(clicked(bool)), this, SLOT(ToJson()));
    connect(ui->pb_clear, SIGNAL(clicked(bool)), this, SLOT(ClearAll()));
    connect(ui->pb_toServer, SIGNAL(clicked(bool)), this, SLOT(JSONtoServer()));
    connect(ui->pb_connect, SIGNAL(clicked(bool)), this, SLOT(connectToHost()));
}

void MainWindow::InterfaceSettings()
{
    setCentralWidget(ui->gridWidget);
    setWindowTitle("Telephone Book");

    ui->statusBar->showMessage("Application run");
    ui->tel_lineEdit->setFocus();
    ui->tel_lineEdit->setInputMask("0-000-000-00-00");
    ui->tel_lineEdit->setText("0-000-000-00-00");

    m_pTcpSocket = new QTcpSocket(this);

    ui->le_connect->setValidator( new QIntValidator(0, 255, this) );
    ui->le_connect->setInputMask("000.000.000.000");
    ui->le_connect->setText("127.0.0.1");

    ui->pb_toServer->setEnabled(false);

    QRegExp rx("[A-z]+");
    QRegExpValidator  *valid = new QRegExpValidator(rx,this);
    ui->name_lineEdit->setValidator(valid);
    ui->name_lineEdit->setText("Name");

    ui->listWidget->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents);

}

void MainWindow::JSONtoServer()
{
    if(m_pTcpSocket->state() == QAbstractSocket::ConnectedState)
    {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out << (quint16)0;
    QString output = document.toJson();
    out << output;
    qDebug() << document.toJson();

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_pTcpSocket->write(block);
    ui->statusBar->showMessage("JSON was sended to server!");
    }
    else
    {
        ui->statusBar->showMessage("Client don't connect to server!");
    }
}
