#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <Iterative.h>

const int MAX_FUNC_NUMBER = 10; // max number of functios supported
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
	void on_spinBox_valueChanged(int arg1); // spinbox slot

	void on_horizontalSlider_valueChanged(int value); // slider slot, triggers when the a

	void on_FunctionsTable_cellChanged(int row, int column); // FunctionsTable slot, triggers when a function was entered

	void on_InitTable_cellChanged(int row, int column); // InitTable slot, triggers when an initial guess was entered

	void on_SolvePushButton_clicked(); // SolveButton slot, triggers when a button was pressed

private:
	Ui::MainWindow *ui; // ui implementation
	std::vector<std::string> functions;// function is postfix notation
	std::vector<bool> function_is_fine;// flags to check the states of the functions
	std::vector<double> initial_guess;// intial guess
	std::vector<bool> initial_guess_is_fine;// flags to check the states of the intial guess
	std::vector<double> result;// results

	bool isFine();// declaration of a function that checks if all the values in tables are ok

	void writeToFile(Iterative::S_Result _result);// declaration of a function that writes the iterative process to file
};

#endif // MAINWINDOW_H
