#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>
#include <QMainWindow>
#include <QDebug>
#include <QLineEdit>
#include "mylineedit.h"
#include <QStandardItem>
#include <QTableView>
#include <QHBoxLayout>
#include <QLabel>
#include <QtMath>
#include <qcustomplot.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void tabChanged(QStandardItem* item);
    //void tablePresed(QModelIndex vodelIndex);
    //void on_comboBox_currentIndexChanged(const QString &arg1);
    //void on_comboBox_2_currentIndexChanged(const QString &arg1);
    void lineChanged(MyLineEdit *lE);//изменение эначения компетентности эксперта



private:
    QPoint mousPos;
    Ui::MainWindow *ui;
    void build();
    void rebuild();
    void drawFirstG();
    void drawSecondG();
    //bool isCorrect();//корректность заполнения всех данных-запускает старт
    bool isFull();
    QSize getSize();
    void calculate();//
    //QMap<int, double> kompetent;//оценки компетентности эксмертов
    //int kolTables;//число критериев
    //int kolVariants;//число вариантов
    QTableView* tableRate;//таблица
    QStandardItemModel  *model;
    //
    QVector< QVector<double> >valuesForTable;//список столбцов таблицы

    //QHBoxLayout *hLayout;
    int colColumn;
    int colRow;
    QCPLayoutGrid *subLayout1;
    QCPLayoutGrid *subLayout2;
    //int oldColRow;
    //int winZ;//номер столбца победителя, если winZ = -1 такого нет
    bool valueChanged;
    QVector< QString >headerName;
    QVector< QString >rowName;
    //ответ
    QVector< QString >lebelSName;
    QVector< QString >lebelAName;
    //int numVin;
    //double *weightTarget;//массив результирующих весов целей
    //void viewerTheWin();
    //
    //void findVin();
    void start();


    QVector< MyLineEdit* > linesSValue;
    QVector< MyLineEdit* > linesAValue;
    //
    QMap<int, double> SValue;//значения первого столбика для формул
    QMap<int, double> AValue;//значения второго столбика для формул
    //QVector< QLabel* > labelForKompetent;
    QVector< QVector<double> > tableContent;//содержимое таблици
};

#endif // MAINWINDOW_H
