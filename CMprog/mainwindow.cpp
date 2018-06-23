#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    build();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build()
{
    subLayout1=0;
    subLayout1 = new QCPLayoutGrid;
    ui->graph_1->plotLayout()->addElement(1, 0, subLayout1);
    subLayout1->setMargins(QMargins(5, 0, 5, 5));
    //subLayout1->clear();
    subLayout1->addElement(0, 0, ui->graph_1->legend);
    //ui->graph_1->legend->setVisible(false);
    ui->graph_1->legend->setVisible(true);
    ui->graph_1->legend->setFillOrder(QCPLegend::foColumnsFirst);
    QColor none; none.setRgb(255,255,255);
    QPen p; p.setColor(none);
    ui->graph_1->legend->setBorderPen(p );
    subLayout2=0;
    subLayout2 = new QCPLayoutGrid;
    ui->graph_2->plotLayout()->addElement(1, 0, subLayout2);
    subLayout2->setMargins(QMargins(5, 0, 5, 5));
    //subLayout1->clear();
    subLayout2->addElement(0, 0, ui->graph_2->legend);
    //ui->graph_1->legend->setVisible(false);
    ui->graph_2->legend->setVisible(true);
    ui->graph_2->legend->setFillOrder(QCPLegend::foColumnsFirst);
    ui->graph_2->legend->setBorderPen(p );
    model=0;
    //weightTarget=0;
    //numVin=-1;
    valueChanged=false;
    headerName<<"i"<<"τ"<<"Χ"<<"Υa"<<"Υ1"<<"Υ2"<<"ΔΥ1"<<"ΔΥ2"<<"δΥ1"<<"δΥ2";
    for(int i=1; i<22; i++)
    {
        rowName.append(QString().setNum(i) );
    }
    //
    lebelSName<<"A"<<"K"<<"Υ0"<<"Δτ";
    lebelAName<<"a0"<<"a1"<<"a2"<<"a3";
    //hLayout = new QHBoxLayout();
    colColumn=headerName.length()-1;
    colRow=rowName.length();
    //
    tableRate=new QTableView();
    tableRate->setFont(QFont("Arial",10,5000));
    tableRate->verticalHeader()->hide();
    tableRate->horizontalHeader()->hide();
    ui->verticalLayout_2->addWidget(tableRate);

    for(int i=0; i<4; i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel(QString("%1=").arg(lebelSName[i] ));

        MyLineEdit *line = new MyLineEdit(i);
        line->setFixedWidth(50);
        //
        linesSValue.append(line);
        //labelForKompetent.append(label);
        connect(line, SIGNAL(MySignal(MyLineEdit*)) ,this,SLOT(lineChanged(MyLineEdit*) ));
        //
        hLayout->addWidget(label);
        hLayout->addWidget(line);
        hLayout->setAlignment(label,Qt::AlignLeft);
        hLayout->setAlignment(line,Qt::AlignLeft);
        ui->verticalLayout_5->addLayout(hLayout);
        //--
        hLayout = new QHBoxLayout();
        label = new QLabel(QString("%1=").arg(lebelAName[i] ));

        line = new MyLineEdit(i+4);
        line->setFixedWidth(50);
        //
        linesAValue.append(line);
        //labelForKompetent.append(label);
        connect(line, SIGNAL(MySignal(MyLineEdit*)) ,this,SLOT(lineChanged(MyLineEdit*) ));
        //
        hLayout->addWidget(label);
        hLayout->addWidget(line);
        hLayout->setAlignment(label,Qt::AlignLeft);
        hLayout->setAlignment(line,Qt::AlignLeft);
        ui->verticalLayout_4->addLayout(hLayout);
    }

    //
    rebuild();
    linesSValue[0]->setText("1.5");
    linesSValue[1]->setText("1");
    linesSValue[2]->setText("0");
    linesSValue[3]->setText("0.5");
    linesAValue[0]->setText("1.2");
    linesAValue[1]->setText("1");
    linesAValue[2]->setText("0.5");
    linesAValue[3]->setText("1");
}

void MainWindow::drawFirstG()
{
    ui->graph_1->clearGraphs();//очищаем все графики
    ui->graph_1->addGraph();
    ui->graph_1->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->graph_1->graph(0)->setData(valuesForTable[0], valuesForTable[2]);
    ui->graph_1->graph(1)->setData(valuesForTable[0], valuesForTable[1]);
    //
    ui->graph_1->graph(0)->setPen(QColor(0, 0, 0, 255));//задаем цвет точки
    //формируем вид точек
    ui->graph_1->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 6));
    //
    ui->graph_1->graph(0)->setName("Υa");
    ui->graph_1->graph(1)->setName("X");
    //Подписываем оси Ox и Oy
    ui->graph_1->xAxis->setLabel("τ");
    ui->graph_1->yAxis->setLabel("X, Ya");
    int N=valuesForTable[0].size();
    //Установим область, которая будет показываться на графике
    ui->graph_1->xAxis->setRange(valuesForTable[0][0], valuesForTable[0][N-1]);//Для оси Ox
    double minY = valuesForTable[2][0], maxY = valuesForTable[2][0];
    for (int i=1; i<N; i++)
    {
        if (valuesForTable[2][i]<minY) minY = valuesForTable[2][i];
        if (valuesForTable[2][i]>maxY) maxY = valuesForTable[2][i];
        //
        if (valuesForTable[1][i]<minY) minY = valuesForTable[1][i];
        if (valuesForTable[1][i]>maxY) maxY = valuesForTable[1][i];
    }
    ui->graph_1->yAxis->setRange(minY, maxY);//Для оси Oy
    ui->graph_1->plotLayout()->setRowStretchFactor(1, 0.001);
    ui->graph_1->replot();

}
void MainWindow::drawSecondG()
{
    ui->graph_2->clearGraphs();//очищаем все графики
    ui->graph_2->addGraph();
    ui->graph_2->addGraph();
    ui->graph_2->addGraph();
    ui->graph_2->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->graph_2->graph(1)->setData(valuesForTable[0], valuesForTable[4]);
    ui->graph_2->graph(3)->setData(valuesForTable[0], valuesForTable[3]);
    ui->graph_2->graph(0)->setData(valuesForTable[0], valuesForTable[1]);
    //
    ui->graph_2->graph(0)->setPen(QColor(0, 0, 0, 255));//задаем цвет точки
    //формируем вид точек
    ui->graph_2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 6));
    ui->graph_2->graph(1)->setPen(QColor(0, 0, 0, 255));//задаем цвет точки
    //формируем вид точек
    ui->graph_2->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, 6));
    //2
    ui->graph_2->graph(3)->setPen(QColor(0, 0, 0, 255));//задаем цвет точки
    //формируем вид точек
    ui->graph_2->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond, 8));
    //2

    ui->graph_2->graph(2)->setData(valuesForTable[0], valuesForTable[2]);
    //
    QColor ya; ya.setRgb(250, 50, 20);
    QPen p; p.setColor(ya);
    p.setWidth(2);
    ui->graph_2->graph(2)->setPen(p);//задаем цвет точки
    //формируем вид точек
    //ui->graph_2->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 5));
    //--
    ui->graph_2->graph(1)->setName("Υ2");
    ui->graph_2->graph(0)->setName("X");
    ui->graph_2->graph(2)->setName("Ya");
    ui->graph_2->graph(3)->setName("Y1");
    //Подписываем оси Ox и Oy
    ui->graph_2->xAxis->setLabel("τ");
    ui->graph_2->yAxis->setLabel("X, Ya");
    int N=valuesForTable[0].size();
    //Установим область, которая будет показываться на графике
    ui->graph_2->xAxis->setRange(valuesForTable[0][0], valuesForTable[0][N-1]);//Для оси Ox
    double minY = valuesForTable[2][0], maxY = valuesForTable[2][0];
    for (int i=1; i<N; i++)
    {
        if (valuesForTable[2][i]<minY) minY = valuesForTable[2][i];
        if (valuesForTable[2][i]>maxY) maxY = valuesForTable[2][i];
        //
        if (valuesForTable[1][i]<minY) minY = valuesForTable[1][i];
        if (valuesForTable[1][i]>maxY) maxY = valuesForTable[1][i];
    }
    ui->graph_2->yAxis->setRange(minY, maxY);//Для оси Oy
    ui->graph_2->plotLayout()->setRowStretchFactor(1, 0.001);
    ui->graph_2->replot();
}

void MainWindow::rebuild()
{
    model = new QStandardItemModel;
    QStandardItem *item;

    for (int i=0; i<colRow; i++)//номера строк
    {
        QString s = rowName[i];
        item = new QStandardItem(s);
        item->setFont(QFont("Arial",10,6500));
        item->setEditable(false);
        item->setSelectable(false);
        item->setBackground(QBrush(QColor(250,230,170)) );
        //
        model->setItem(i+1, 0, item);
    }
    for(int i=0; i<colColumn+1; i++)//названия столбцов
    {
        QString s = headerName[i];
        item = new QStandardItem(s);
        item->setFont(QFont("Arial",10,6500));
        item->setEditable(false);
        item->setSelectable(false);
        item->setBackground(QBrush(QColor(250,230,170)) );
        //
        model->setItem(0, i, item);
    }
    if(!valuesForTable.isEmpty())
    {
        for (int i=0; i<colRow; i++)
        {
            for(int j=0;j<colColumn-2; j++)
            {
                if(valuesForTable[j][i]-int(valuesForTable[j][i]) >= 0.01)
                    item = new QStandardItem(QString().setNum(valuesForTable[j][i],'f',2));
                else
                    item = new QStandardItem(QString().setNum(valuesForTable[j][i],'f',0));
                item->setEditable(false);
                item->setFont(QFont("Arial",10,6500));
                model->setItem(i+1, j+1, item);
            }
            for(int j=colColumn-2;j<colColumn; j++)
            {
                if(valuesForTable[j][i]-int(valuesForTable[j][i]) >= 0.01)
                    item = new QStandardItem(QString("%1%").arg(QString().setNum(valuesForTable[j][i]*100,'f',2) ) );
                else
                    item = new QStandardItem(QString("%1%").arg(QString().setNum(valuesForTable[j][i]*100,'f',0) ) );
                item->setEditable(false);
                item->setFont(QFont("Arial",10,6500));
                model->setItem(i+1, j+1, item);
            }
        }

        drawFirstG();
        drawSecondG();
    }

    tableRate->setModel(model);
    for(int i=0; i < colColumn+1; i++)//
    {
        tableRate->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }
    tableRate->setFixedSize(getSize());
}

QSize MainWindow::getSize()
{
    QSize tableSize;
    int i=0;
    int height=0;
    int currentHeight=tableRate->rowHeight(i);
    while(currentHeight > 0)
    {
        height+=currentHeight;
        ++i;
        currentHeight=tableRate->rowHeight(i);
    }
    height+=i/2+1;
    i=0;
    int width=0;
    int currentWidth=tableRate->columnWidth(i);
    while(currentWidth > 0)
    {
        width+=currentWidth;
        ++i;
        currentWidth=tableRate->columnWidth(i);
    }
    width+=i/2+1;
    //width = tableCreterion->columnWidth(0)+20;
    tableSize.setHeight(height);
    tableSize.setWidth(width);
    return tableSize;
}

void MainWindow::calculate()
{
    //заполнить пока чем нибудь список для перестройки
//здесь --------------------------------------------------
    QVector<double> analyticC(3);//аналитический C1 C2 C3
    QVector<double> analyticNetsD(3);//аналитико-сеточный D1 D2 D3
    QVector<double> explicitD(2);//явный метод D4 D5
    analyticC[0] = SValue[1]*AValue[0];
    analyticC[1] = SValue[1]*AValue[1]*(qCos(AValue[3])+SValue[0]*AValue[2]*qSin(AValue[3]) )/
            ( qPow(SValue[0]*AValue[2],2)+1 );
    analyticC[2] = SValue[1]*AValue[1]*(qSin(AValue[3])-SValue[0]*AValue[2]*qCos(AValue[3]) )/
            ( qPow(SValue[0]*AValue[2],2)+1 );
    //
    analyticNetsD[0] = qExp((-1*SValue[3])/SValue[0] );
    analyticNetsD[1] = SValue[0]*SValue[1]/SValue[3] * (1-analyticNetsD[0])-SValue[1]*analyticNetsD[0];
    analyticNetsD[2] = SValue[1]-SValue[0]*SValue[1]/SValue[3] * (1-analyticNetsD[0]);
    //
    explicitD[0] = 1-SValue[3]/SValue[0];
    explicitD[1] = SValue[1]*SValue[3]/SValue[0];
    QVector<double> tColumn;
    tColumn.append(0);
    for(int i=1; i < colRow; i++)
    {
        tColumn.append(tColumn[i-1]+SValue[3] );
    }
    valuesForTable.append(tColumn);
    //второй столбец X
    QVector<double> xColumn;
    for(int i=0; i < colRow; i++)
    {
        xColumn.append(AValue[0]+AValue[1]*qSin(AValue[2]*tColumn[i]+AValue[3] ) );
    }
    valuesForTable.append(xColumn);
    //третий столбец Ya
    QVector<double> yaColumn;
    for(int i=0; i < colRow; i++)
    {
        yaColumn.append( (SValue[2]-analyticC[0]-analyticC[2]) * qExp((-1*tColumn[i])/SValue[0]) +
                analyticC[0]+analyticC[1]*qSin(AValue[2] * tColumn[i]) +
                analyticC[2]*qCos(AValue[2] * tColumn[i] ) );//
    }
    valuesForTable.append(yaColumn);
    double minYa = yaColumn[0];
    double maxYa = yaColumn[0];
    for(int i=1; i<colRow; i++)
    {
        if(yaColumn[i]>maxYa)
            maxYa=yaColumn[i];
        else
            if(yaColumn[i]<minYa)
                minYa=yaColumn[i];
    }
    //четвертый столбец Y1
    QVector<double> y1Column;
    y1Column.append(SValue[2] );
    for(int i=1; i < colRow; i++)
    {
        y1Column.append(analyticNetsD[0]*y1Column[i-1]+analyticNetsD[1]*xColumn[i-1]+
                analyticNetsD[2]*xColumn[i] );
    }
    valuesForTable.append(y1Column);
    //пятый столбец Y2
    QVector<double> y2Column;
    y2Column.append(SValue[2] );
    for(int i=1; i < colRow; i++)
    {
        y2Column.append(explicitD[0]*y2Column[i-1] + explicitD[1]*xColumn[i-1] );
    }
    valuesForTable.append(y2Column);
    //шестой столбец dY1
    QVector<double> dy1Column;
    for(int i=0; i < colRow; i++)
    {
        dy1Column.append(y1Column[i]-yaColumn[i] );
    }
    valuesForTable.append(dy1Column);
    //седьмой столбец dY2
    QVector<double> dy2Column;
    for(int i=0; i < colRow; i++)
    {
        dy2Column.append(y2Column[i]-yaColumn[i] );
    }
    valuesForTable.append(dy2Column);
    //восьмой столбец bY1
    QVector<double> by1Column;
    for(int i=0; i < colRow; i++)
    {
        by1Column.append(dy1Column[i]/(maxYa-minYa ) );
    }
    valuesForTable.append(by1Column);
    //восьмой столбец bY1
    QVector<double> by2Column;
    for(int i=0; i < colRow; i++)
    {
        by2Column.append(dy2Column[i]/(maxYa-minYa ) );
    }
    valuesForTable.append(by2Column);
}

void MainWindow::start()
{
    foreach (QVector<double> collon, valuesForTable)
    {
        collon.clear();
    }
    valuesForTable.clear();
    //
    if(isFull())//проверку сделать//ок
    {
        qDebug() << "УБРАТЬ 1";        
        calculate();//заполнение ответов для построения
        qDebug() << "УБРАТЬ 2";
    }
    rebuild();

}
void MainWindow::lineChanged(MyLineEdit * lE)
{


    if(valueChanged)
        return;
    int id = lE->getID();
    bool ok;
    float f=lE->text().toFloat(&ok);
    if(lE->text().length() > 0 && ok)
    {
        if(id<4)
            SValue[id]=f;
        else
            AValue[id-4]=f;
    }
    else
    {
        if(id<4)
            SValue.remove(id);
        else
            AValue.remove(id-4);
        valueChanged=true;
        lE->setText("");
        valueChanged=false;
    }
    //findVin();
    start();

}
bool MainWindow::isFull()//ok
{
    if(SValue.size() != 4)
        return false;
    if(AValue.size() != 4)
        return false;
    return true;

}

