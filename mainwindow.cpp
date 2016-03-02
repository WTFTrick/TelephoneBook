#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : nPort(2323), m_nNextBlockSize(0), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InterfaceSettings();
    CreatorConnections();
    connectToHost();
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
        QVariantMap map;
        map.insert("thelephone", ui->tel_lineEdit->text());
        map.insert("name", ui->name_lineEdit->text());

        object = QJsonObject::fromVariantMap(map);
        document.setObject(object);

        QFile jsonFile("/home/kopylov/tb.json");
        jsonFile.open(QFile::Append);
        jsonFile.write(document.toJson());
        jsonFile.close();

        ui->listWidget->addItem(document.toJson());

        status_bar_label->setText("Information successfull convert to JSON!");
        ui->statusBar->addWidget(status_bar_label);

    }
    else
    {
        ui->listWidget->clear();
        ui->listWidget->addItem("Fill all the fields before convert information to JSON!");
        status_bar_label->setText("Failed when convert information to JSON!");
        ui->statusBar->addWidget(status_bar_label);
    }
}

void MainWindow::ClearAll()
{
    ui->listWidget->clear();

    status_bar_label->setText("JSON file cleared!");
    ui->statusBar->addWidget(status_bar_label);

    QFile file("/home/kopylov/tb.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        file.write("");
    }
    file.close();
}

void MainWindow::connectToHost()
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost("localhost", nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
}

void MainWindow::slotConnected()
{
    status_bar_label->setText("Connection successfull");
    ui->statusBar->addWidget(status_bar_label);
    qDebug() << "Received the connected() signal";
    qDebug() << "Connection successfull";
}

void MainWindow::slotReadyRead()
{

}

void MainWindow::CreatorConnections()
{
    connect(ui->pb_toJSON, SIGNAL(clicked(bool)), this, SLOT(ToJson()));
    connect(ui->pb_clear, SIGNAL(clicked(bool)), this, SLOT(ClearAll()));
    connect(ui->pb_toServer, SIGNAL(clicked(bool)), this, SLOT(JSONtoServer()));
}

void MainWindow::InterfaceSettings()
{
    setCentralWidget(ui->gridWidget);
    setWindowTitle("Telephone Book");

    status_bar_label = new QLabel(this);
    status_bar_label->setText("Application run");
    ui->statusBar->addWidget(status_bar_label);

    ui->tel_lineEdit->setFocus();
    ui->tel_lineEdit->setInputMask("0-000-000-00-00");
    ui->tel_lineEdit->setText("0-000-000-00-00");

    QRegExp rx("[A-z]+");
    QRegExpValidator  *valid = new QRegExpValidator(rx,this);
    ui->name_lineEdit->setValidator(valid);
    ui->name_lineEdit->setText("Name");

    ui->listWidget->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents);

}

void MainWindow::JSONtoServer()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out << (quint16)0;
    //out << document.toJson();
    QString output = document.toJson();
    out << output;
    qDebug() << document.toJson();

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_pTcpSocket->write(block);
    status_bar_label->setText("JSON was sended to server!");
    ui->statusBar->addWidget(status_bar_label);
}
