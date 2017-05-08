#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

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
    void on_spinBox_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_FunctionsTable_cellChanged(int row, int column);

    void on_InitTable_cellChanged(int row, int column);

    void on_SolvePushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> functions;
    std::vector<bool> function_is_fine;
    std::vector<double> initial_guess;
    std::vector<bool> initial_guess_is_fine;
    std::vector<double> result;

    bool isFine();
    void writeToFile(double _time);
};

#endif // MAINWINDOW_H
