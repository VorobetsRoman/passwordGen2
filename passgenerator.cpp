#include "passgenerator.h"
#include "ui_passgenerator.h"
#include <QCheckBox>
#include <QTime>
#include <QSpinBox>
#include <QSlider>



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
            this,           SLOT(lengthChanged(int)));
    connect(ui->slLength,   &QSlider        ::valueChanged,
            this,           &PassGenerator  ::lengthChanged );
    connect(ui->pbGenerate, &QPushButton    ::pressed,
            this,           &PassGenerator  ::generatePassword);
    connect(ui->pbCopy,     &QPushButton    ::pressed,
            this,           &PassGenerator  ::pbCopy    );

    generatePassword();
}




//======================================= Деструктор
PassGenerator::~PassGenerator() {delete ui;}



//======================================= Функция генерирования нового пароля
void PassGenerator::generatePassword()
{
    QString alphabet {""};

    if (ui->cbDigit->isChecked())   alphabet.append(digitsS);
    if (ui->cbLetters->isChecked()) alphabet.append(lettersS);
    if (ui->cbLETTERS->isChecked()) alphabet.append(LETTERSS);
    if (ui->cbSymbols->isChecked()) alphabet.append(symbolsS);

    if (alphabet == "") return;

    QString password;

    for (int i {ui->sbLength->value()}, alphabetSize {alphabet.size()}; --i >= 0;)
        password.append(alphabet.at(qrand() % alphabetSize));

    ui->lePassword->setText(password);
}




//======================================= Изменение длины пароля
void PassGenerator::lengthChanged(int length)
{
    (ui->slLength->value() == length) ? ui->sbLength->setValue(length) : ui->slLength->setValue(length);
    generatePassword();
}




//======================================= Кнопка копирования в память
void PassGenerator::pbCopy()
{
    ui->lePassword->selectAll();
    ui->lePassword->copy();
}



