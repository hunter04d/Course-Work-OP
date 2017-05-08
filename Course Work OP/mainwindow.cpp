#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ShuntingYard.h"
#include "Iterative.h"
#include "Maths.h"
#include <fstream>
#include <ctime>
#include <iomanip>
#include<string>
#include <chrono>
#include <QDebug>


const int MAX_FUNC_NUMBER = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), functions(MAX_FUNC_NUMBER), function_is_fine(MAX_FUNC_NUMBER, false),  initial_guess(MAX_FUNC_NUMBER), initial_guess_is_fine(MAX_FUNC_NUMBER,false), result(MAX_FUNC_NUMBER)
{
    ui->setupUi(this);
    ui->FunctionsTable->setColumnWidth(0,256);
    QStringList name_initer;
    for(int i = 1; i <= MAX_FUNC_NUMBER; ++i )
        name_initer << "x" + QString::number(i);
    ui->InitTable->setVerticalHeaderLabels(name_initer);
    ui->ResultsTable->setVerticalHeaderLabels(name_initer);
    ui->FunctionsTable->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    ui->FunctionsTable->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    ui->InitTable->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    ui->InitTable->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    ui->ResultsTable->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    ui->ResultsTable->verticalHeader()->setSectionResizeMode (QHeaderView::Fixed);

    for(int i = 0; i<MAX_FUNC_NUMBER;++i)
    {
        QTableWidgetItem* init_tables[3];
        for(int j = 0; j< 3;++j)
        {
            init_tables[j] = new QTableWidgetItem;
        }
        ui->FunctionsTable->setItem(i,0,init_tables[0]);
        ui->InitTable->setItem(i,0,init_tables[1]);
        ui->ResultsTable->setItem(i,0,init_tables[2]);
    }
    ui->horizontalSlider->setRange(2,MAX_FUNC_NUMBER);
    ui->SolvePushButton->setEnabled(false);
    ui->SIMButton->setChecked(true);
    ui->StatisticsBox->hide();
    ui->statusBar->clearMessage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int new_val)
{
    ui->SolvePushButton->setEnabled(false);
    auto curr_val = new_val;
    if(curr_val<2)
    {
        ui->spinBox->setValue(2);
        curr_val = 2;
    }
    if(curr_val>MAX_FUNC_NUMBER)
    {
        ui->spinBox->setValue(MAX_FUNC_NUMBER);
         curr_val = MAX_FUNC_NUMBER;
    }
    ui->horizontalSlider->setValue(curr_val);
    for(int i = 0; i < curr_val; ++i)
    {
        ui->FunctionsTable->showRow(i);
        ui->InitTable->showRow(i);
        ui->ResultsTable->showRow(i);
    }
    for(int i = curr_val; i < MAX_FUNC_NUMBER; ++i)
    {
        ui->FunctionsTable->hideRow(i);
        ui->InitTable->hideRow(i);
        ui->ResultsTable->hideRow(i);
    }
    for(int row = 0; row < curr_val;++row)
    {
       on_FunctionsTable_cellChanged(row,0);
       on_InitTable_cellChanged(row, 0);
    }
    ui->statusBar->clearMessage();
    if(isFine())
    {
        ui->statusBar->showMessage("Ready to solve!!!");
        ui->SolvePushButton->setEnabled(true);
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int _new_value)
{
    ui->spinBox->setValue(_new_value);
}

void MainWindow::on_FunctionsTable_cellChanged(int row, int column)
{
   ui->SolvePushButton->setEnabled(false);
   try
   {
     auto Qfunc = ui->FunctionsTable->item(row,column)->text().toLower().remove(' ');
     ui->FunctionsTable->item(row,column)->setText(Qfunc);
     std::string func = Qfunc.toStdString();
     if(func.empty())
     {
         ui->FunctionsTable->item(row,column)->setBackgroundColor({255,255,255});
         return;
     }
     preAnalize(func);
     functions.at(row) = shuntingYard(func, ui->spinBox->value());
      ui->statusBar->showMessage("Function " + QString::number(row+1) + " is ok",2000);
      ui->FunctionsTable->item(row,column)->setBackgroundColor({255,255,255});
      function_is_fine.at(row) = true;
      if(isFine())
      {
           ui->statusBar->showMessage("Ready to solve!!!");
           ui->SolvePushButton->setEnabled(true);
      }
   }
   catch(std::exception _exception)
   {
       ui->statusBar->showMessage("Function " + QString::number(row+1) + ": " + _exception.what());
       function_is_fine.at(row) = false;
       ui->FunctionsTable->item(row,column)->setBackgroundColor({255,0,0});
   }
}

bool MainWindow::isFine()
{
    for(int i = 0; i < ui->spinBox->value(); ++i)
    {
        if(function_is_fine[i] == false)
        {
            return false;
        }
        if(initial_guess_is_fine[i] == false)
        {
            return false;
        }
    }
    return true;
}

void MainWindow::on_InitTable_cellChanged(int row, int column)
{
    ui->SolvePushButton->setEnabled(false);
    bool state = false;
    double res = ui->InitTable->item(row,column)->text().toDouble(&state);
    res = round(res*1000.0)/1000.0;
    if(state)
    {
        ui->InitTable->item(row,column)->setText(QString::number(res));
        initial_guess.at(row) = res;
        initial_guess_is_fine.at(row) = true;
        if(isFine())
        {
             ui->statusBar->showMessage("Ready to solve!!!");
             ui->SolvePushButton->setEnabled(true);
        }
    }
    else
    {
         ui->InitTable->item(row,column)->setText("");
         initial_guess_is_fine.at(row) = false;
         ui->statusBar->showMessage("Intial guess for x" + QString::number(row+1) + ": " + "Only a number can be entered");
    }
}
size_t number_of_iterations = 0;
Maths::T_matrix iterations;

void MainWindow::on_SolvePushButton_clicked()
{
    std::vector<std::string> useful_funcs(functions.cbegin(),functions.cbegin()+ ui->spinBox->value());
    auto copy = useful_funcs;
    std::sort(copy.begin(),copy.end());
    if(std::unique(copy.begin(),copy.end()) != copy.end())
    {
         ui->statusBar->showMessage("Error: Some functions are duplicates. A single isolated solution does not exist");
        return;
    }
    std::vector<double> useful_guess(initial_guess.cbegin(),initial_guess.cbegin()+ ui->spinBox->value());
    try
    {
        auto begun_time = std::chrono::high_resolution_clock::now();
        auto result = ui->SIMButton->isChecked()? Iterative::getResult(useful_funcs, useful_guess): GaussZeidel::getResult(useful_funcs, useful_guess);
        for(int i = 0; i < result.size();++i)
        {
            ui->ResultsTable->item(i,0)->setText(QString::number(result[i],'f', 5));
        }
        auto ended_time = std::chrono::high_resolution_clock::now();
        auto taken_time = round(std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(ended_time - begun_time).count()*1000.0)/1000.0;
        ui->TimeLabel->setText("Time taken: <b>" + QString::number(taken_time)+"ms</b>");
        ui->IterationLabel->setText("Number of iterations: <b>" + QString::number(number_of_iterations) + "</b>");
        ui->StatisticsBox->show();
        if(ui->WriteToFilecheckBox->isChecked())
        {
            writeToFile(taken_time);
        }
        iterations.clear();
        ui->statusBar->showMessage("Solved!!! See statistics above");
    }
    catch(std::exception _exception)
    {
         ui->statusBar->showMessage(_exception.what());
         ui->StatisticsBox->hide();
         for(int i = 0; i < MAX_FUNC_NUMBER; ++i)
         {
             ui->ResultsTable->item(i,0)->setText("");
         }
    }
}

void MainWindow::writeToFile(double _time)
{
    std::ofstream file("stats.txt", std::ios::app);
    auto curr_time = std::time(nullptr);
    auto tm = std::localtime(&curr_time);
    file << std::put_time(tm,"%T %d-%m-%Y");
    file << "\nSolution was foud using " << (ui->SIMButton->isChecked()?"Simple interation method":"Gauss-Siedel method")<<"!!!\nFunctions: \n";
    for(int i = 0 ; i < ui->spinBox->value();++i)
    {
        auto func = ui->FunctionsTable->item(i,0)->text().toStdString();
        preAnalize(func);
        file << i+1 << ": " << func << '\n';
    }
    file << std::fixed <<std::left <<std::setprecision(5);
    file <<std::setw(15)<<"Variables: ";
    file <<std::setw(11);
    for(int i = 0 ; i < ui->spinBox->value();++i)
    {
        ((file.put('x')) << i+1);
    }
    file<< std::endl <<std::setw(15)<<"Init Guess:";
    file <<std::setw(12);
    for(int i = 0 ; i < ui->spinBox->value();++i)
    {
        file << initial_guess[i];
    }
    for(size_t i = 0; i < iterations.size();++i)
    {
         std::string out = "iteration " + std::to_string(i+1) + ": ";
         file << std::endl <<std::setw(15) << out <<std::setw(12) ;
         for(int j = 0 ; j < ui->spinBox->value();++j)
         {
            (file << iterations[i][j]);
         }
    }
    (file.put('\n')) << std::setw(1);
    file << "Number of iterations:" << number_of_iterations << '\n';
    file << "Time:" << _time << "ms\n\n";
}
