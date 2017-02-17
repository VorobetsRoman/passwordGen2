#ifndef PASSGENERATOR_H
#define PASSGENERATOR_H

#include <QWidget>


namespace Ui {
class PassGenerator;
}

class PassGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit PassGenerator(QWidget *parent = 0);
    ~PassGenerator();

private:
    Ui::PassGenerator *ui;

private slots:
    void    generatePassword    ();
    void    sbChanged           (int);
    void    slChanged           (int);
    void    pbGenerate          ();
    void    pbCopy              ();
};

#endif // PASSGENERATOR_H
