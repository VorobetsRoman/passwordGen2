#include "passgenerator.h"
#include "ui_passgenerator.h"
#include <QCheckBox>
#include <QTime>
#include <QSpinBox>
#include <QSlider>
#include <QDebug>



static const QString digitsS = "0123456789";
static const QString lettersS = "abcdefghijklmnopqrstuvwxyz";
static const QString LETTERSS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const QString symbolsS = "!@#$%^&*()-=_+{}[]\\|/?.,';:`";



//======================================= Конструктор
PassGenerator::PassGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassGenerator)
{
    ui->setupUi(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    connect(ui->cbDigit,    &QCheckBox      ::clicked,
            this,           &PassGenerator  ::generatePassword);
    connect(ui->cbLETTERS,  &QCheckBox      ::clicked,
            this,           &PassGenerator  ::generatePassword);
    connect(ui->cbLetters,  &QCheckBox      ::clicked,
            this,           &PassGenerator  ::generatePassword);
    connect(ui->cbSymbols,  &QCheckBox      ::clicked,
            this,           &PassGenerator  ::generatePassword);
    connect(ui->sbLength,   SIGNAL(valueChanged(int)),
            this,           SLOT(sbChanged(int)));
    connect(ui->slLength,   &QSlider        ::valueChanged,
            this,           &PassGenerator  ::slChanged );
    connect(ui->pbGenerate, &QPushButton    ::pressed,
            this,           &PassGenerator  ::pbGenerate);
    connect(ui->pbCopy,     &QPushButton    ::pressed,
            this,           &PassGenerator  ::pbCopy    );

    generatePassword();
}




//======================================= Деструктор
PassGenerator::~PassGenerator()
{
    delete ui;
}




//======================================= Функция генерирования нового пароля
void PassGenerator::generatePassword()
{
    QString source {""};

    if (ui->cbDigit->isChecked())
        source.append(digitsS);
    if (ui->cbLetters->isChecked())
        source.append(lettersS);
    if (ui->cbLETTERS->isChecked())
        source.append(LETTERSS);
    if (ui->cbSymbols->isChecked())
        source.append(symbolsS);

    if (source == "") return;

    QString password;

    for (int i {0}, m {source.size()}; i < ui->sbLength->value(); i++)
        password.append(source.at(qrand() % m));

    ui->lePassword->setText(password);
}




//======================================= Изменение спина длины пароля
void PassGenerator::sbChanged(int value_)
{
    if (ui->slLength->value() != value_) {
        ui->slLength->setValue(value_);
        generatePassword();
    }
}




//======================================= Изменение слайдера длины пароля
void PassGenerator::slChanged(int value_)
{
    if (ui->sbLength->value() != value_) {
        ui->sbLength->setValue(value_);
    }
    generatePassword();
}




//======================================= Кнопка генерации нового пароля
void PassGenerator::pbGenerate()
{
    generatePassword();
}




//======================================= Кнопка копирования в память
void PassGenerator::pbCopy()
{
    ui->lePassword->selectAll();
    ui->lePassword->copy();
}



