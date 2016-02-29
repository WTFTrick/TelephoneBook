#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Telephone Book");
    CreatorConnections();
    ui->tel_lineEdit->setFocus();
    ui->tel_lineEdit->setText("0-000-000-00-00");
    ui->name_lineEdit->setText("Name");

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::QVariantToJson()
{
    //Don't Work!
    /*QVariantList people;

    QVariantMap bob;
    bob.insert("Name", "Bob");
    bob.insert("Phonenumber", 123);

    QVariantMap alice;
    alice.insert("Name", "Alice");
    alice.insert("Phonenumber", 321);

    people << bob << alice;

    QJson::Serializer serializer;
    bool ok;
    QByteArray json = serializer.serialize(people, &ok);

    //ui->listWidget->addItem(json);
    qDebug() << json;*/


    if ((ui->tel_lineEdit->text()!= "")&(ui->name_lineEdit->text()!=""))
    {
    QtJson::JsonObject contributor;
    contributor["thelephone"] = ui->tel_lineEdit->text();
    contributor["name"] = ui->name_lineEdit->text();
    QByteArray data = QtJson::serialize(contributor);
    ui->listWidget->addItem(data);
    qDebug() << data;

    QFile file("/home/kopylov/json.js");
    QTextStream out(&file);
    if (file.open(QIODevice::Append))
    {
       file.write(data);
    }
    file.close();
    }
}


void MainWindow::CreatorConnections()
{
    connect(ui->pb_toJSON, SIGNAL(clicked(bool)), this, SLOT(QVariantToJson()));
}
