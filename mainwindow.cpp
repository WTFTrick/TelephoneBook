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

        QJsonObject object = QJsonObject::fromVariantMap(map);
        QJsonDocument document;
        document.setObject(object);

        QFile jsonFile("/home/kopylov/tb.json");
        jsonFile.open(QFile::Append);
        jsonFile.write(document.toJson());
        jsonFile.close();

        ui->listWidget->addItem(document.toJson());

        connect_status->setText("Information successfull convert to JSON!");
        ui->statusBar->addWidget(connect_status);

    }
    else
    {
        ui->listWidget->clear();
        ui->listWidget->addItem("Fill all the fields before convert information to JSON!");
        connect_status->setText("Failed when convert information to JSON!");
        ui->statusBar->addWidget(connect_status);
    }
}

void MainWindow::ClearAll()
{
    ui->listWidget->clear();

    connect_status->setText("JSON file cleared!");
    ui->statusBar->addWidget(connect_status);

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
    connect_status->setText("Connection successfull");
    ui->statusBar->addWidget(connect_status);
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
}

void MainWindow::InterfaceSettings()
{
    setCentralWidget(ui->gridWidget);
    setWindowTitle("Telephone Book");

    connect_status = new QLabel(this);
    connect_status->setText("Application run");
    ui->statusBar->addWidget(connect_status);

    ui->tel_lineEdit->setFocus();
    ui->tel_lineEdit->setInputMask("0-000-000-00-00");
    ui->tel_lineEdit->setText("0-000-000-00-00");

    QRegExp rx("[A-z]+");
    QRegExpValidator  *valid = new QRegExpValidator(rx,this);
    ui->name_lineEdit->setValidator(valid);
    ui->name_lineEdit->setText("Name");

    ui->listWidget->viewport()->setAttribute( Qt::WA_TransparentForMouseEvents);

    //Don't work!
    /*QVariantList people;

    QVariantMap bob;
    bob.insert("Name", "Bob");
    bob.insert("Phonenumber", 123);

    QVariantMap alice;
    alice.insert("Name", "Alice");
    alice.insert("Phonenumber", 321);

    people << bob << alice;

    QJson::Serializer serializer;
    qDebug() << "Before crash";
    QString l = "1";

    QByteArray json = serializer.serialize(people);

    qDebug() << json;*/

}
