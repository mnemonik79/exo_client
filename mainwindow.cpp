#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QHostAddress>
#include <QFileDialog>
#include <QTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
    QByteArray datas = _socket.readAll();
   QString otvet=datas;
   ui->textEdit->setText(otvet);
 //    qDebug() << datas;
 //   _socket.write(QByteArray("я отправляю тебе данные пожалйста поймай их"));
}

void MainWindow::on_pushButton_clicked()
{  QString Str_url=ui->lineEdit->text();
    QString Port_url=ui->lineEdit_2->text();
  _socket.connectToHost(QHostAddress(Str_url), 23);
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void MainWindow::on_pushButton_2_clicked()
{   QString Pos_sobsh=ui->textEdit_2->toPlainText();
    QByteArray pos;
    pos+="\xD1";
    pos+="\x81";
     pos.append(Pos_sobsh);
    //    pos=test.readAll();
     _socket.write(pos);
qDebug()<< "Отправляем" << pos;

}





void MainWindow::on_pushButton_3_clicked()
{
     m_fileName = QFileDialog::getOpenFileName(this, "Файл для Товароучетки");
}

void MainWindow::on_pushButton_4_clicked()
{
    QString filePathName = m_fileName;
        QStringList filePath = filePathName.split("/");

        QFile file(m_fileName);
        QByteArray q;
        int i = 0;
        QByteArray block;
        QByteArray arrBlock;
        QByteArray junk("!@#Rtasd#$%sdfs!!!)()334rrer");
        QList<QByteArray> Blocks;

        if (file.open(QIODevice::ReadOnly)) {
                QFileInfo fileInfo(file);
                QString fileName(filePath.last());

                QDataStream out(&arrBlock, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_8);
  QString Me("Ops");
               out << quint16(0) << QTime::currentTime() << Me + "_" + "Сервер" + "_" + fileName << fileInfo.size();

                out.device()->seek(0);
                out << quint16(arrBlock.size() - sizeof(quint16));
                _socket.write(arrBlock);
                _socket.waitForBytesWritten();

                while (!file.atEnd())
                       {
                           q = file.readAll();
                           file.close();
                       }
               //        Blocks = q.split('\n');
                       int pos = 0, arrsize = q.size(), sizeInArray = 512;
                       while(pos<arrsize){
                           QByteArray arr = q.mid(pos, sizeInArray);
                           Blocks << arr;
                           pos+=arr.size();
                       }

                       foreach (block, Blocks) {

                                 _socket.write(block);
                                 _socket.waitForBytesWritten();
                                 if (block == Blocks.last()) {
                                     qDebug() << "sended!";
                                     _socket.write(junk);
                                     _socket.waitForBytesWritten();
                                     block.clear();
                                 }
                                 q.clear();
                                 i++;
                               //  ui->prBr_fileSending->setValue(i/Blocks.size()*100);
                             }

        }
        }

void MainWindow::on_pushButton_5_clicked()
{    QByteArray pos;
    QString Pos_sobsh;
    if (ui->radioButton->isEnabled()==true)
      {
      Pos_sobsh="Проверить версию";
      }

    else if (ui->radioButton_2->isEnabled()==true)
      {
      Pos_sobsh="Ренейм ТУ";
      }
    else if (ui->radioButton_3->isEnabled()==true)
      {
      Pos_sobsh="Ренейм КК";
      }
    else if (ui->radioButton_4->isEnabled()==true)
      {
      Pos_sobsh="Обновить";
      }
    else {
        Pos_sobsh="";
          }



        pos+="\xD0";
        pos+="\xBA";
         pos.append(Pos_sobsh);
        //    pos=test.readAll();
         _socket.write(pos);
    qDebug()<< "комманда" << pos;
}
