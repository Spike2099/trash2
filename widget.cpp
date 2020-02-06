//подключаем заголовочные файлы для виджетов
#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QString>
#include <QDebug>
#include <QDialog>
#include <windows.h>
#include "des.cpp"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    textEdit = new QTextEdit();
    //Кнопки методов шифрования DES/XOR
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::encodeXorDecode);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::encodeDesDecode);
    //Открытие и сохранение в файл.
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::save);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::open);
}

Widget::~Widget()
{
    delete ui;
}
//функция расшифровки и дешифровки
//нужно учитывать что для расшифровки алгоритма xor нужно всего навсего знать ключ.
void Widget::encodeXorDecode()
{

    QMessageBox Warning;
    Warning.setText("Обязательно: на ввод для XOR длинна строки 10 символов");
    //массив char с исходными данными
    //toLatin1() приводит данные к ASCII таблице
    const char* input = (ui->textEdit->toPlainText()).toLatin1().data();
    //массива с исходными данными
    int inputLength = ui->textEdit->toPlainText().toLatin1().length();
    //Ключ в виде массива char
    const char* key = ui->KeyLineEdit->text().toLatin1().data();
    //длинна ключа
    int keyLength = ui->KeyLineEdit->text().toLatin1().length();
    //массивы с исходными данными
    char output[inputLength];
    if(inputLength!=0){
        for (int i = 0; i < inputLength + 1; ++i)
        {
            //берём индекс вводимых данных и степень ключа по модолю + длинна ключа
            output[i] = input[i] ^ key[i % keyLength + 1];
        }
    //выводим всё это дело на славянском если вводили на славянском соотвественно.
        ui->textEdit_1->setText(QString::fromLatin1(output));
    }
     Warning.exec();
}

void Widget::encodeDesDecode()
{
    Des d1,d2;
    setlocale( LC_ALL, "ru_RU.UTF-8" );
    char *str = new char[1000000];
    char *str1;
    str = (ui->textEdit->toPlainText()).toLatin1().data();
    str1 = d1.Encrypt(str);
    str =  d2.Decrypt(str1);
    ui->textEdit_1->setText(QString::fromLatin1(str1));
    delete[] str;
    delete[] str1;
}

void Widget::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
     tr("сохранить файл"), "",
     tr("текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));
    if (fileName != "") {
     QFile file(fileName);
     if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox msgBox;
       msgBox.setText("Ошибка записи файа");
      msgBox.exec();
     }
     else {
      QTextStream stream(&file);
      //toPlainText() Метод возвращает экземпляр QString с текстом, который находится в виджете.
      stream << ui->textEdit->toPlainText();
      //освобождаем поток
      stream.flush();
      //закрываем файл
      file.close();
     }
    }
}

void Widget::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Открыть файл"), "",
               tr("Текстовые файлы (*.txt);; Файлы C++ (*.cpp *.h)"));
   if (fileName != "")
   {
     QFile file(fileName);
   if (!file.open(QIODevice::ReadOnly)){
    //critical вывод об ошибке
       QMessageBox::critical(this, tr("Ошибка"), tr("Не могу открыть файл"));
    return;
   }
   QTextStream in(&file);
   //считываем весь входной поток
   ui->textEdit->setText(in.readAll());
   //закрываем файл
   file.close();
  }
}
