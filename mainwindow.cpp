#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
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

        /*QtJson::JsonObject contributor;
    contributor["thelephone"] = ui->tel_lineEdit->text();
    contributor["name"] = ui->name_lineEdit->text();
    QByteArray data = QtJson::serialize(contributor);
    ui->listWidget->clear();
    ui->listWidget->addItem(data);
    qDebug() << data;

    QFile file("/home/kopylov/tb.json");

    //QTextStream out(&file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
       file.write(data);
    }
    file.close();*/

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

    }
    else
    {
        ui->listWidget->addItem("Fill all the fields before translate information to JSON!");
    }
}

void MainWindow::ClearAll()
{
    ui->listWidget->clear();
    QFile file("/home/kopylov/tb.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
       file.write("");
    }
    file.close();
}

void MainWindow::CreatorConnections()
{
    connect(ui->pb_toJSON, SIGNAL(clicked(bool)), this, SLOT(QVariantToJson()));
    connect(ui->pb_clear, SIGNAL(clicked(bool)), this, SLOT(ClearAll()));
}

void MainWindow::InterfaceSettings()
{
    setCentralWidget(ui->gridWidget);
    setWindowTitle("Telephone Book");

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
