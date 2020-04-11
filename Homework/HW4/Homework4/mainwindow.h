#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cell.h"
#include "graph.h"
#include <QMainWindow>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_green_Button_clicked();

    void on_red_Button_clicked();

    void on_blue_Button_clicked();

    void on_pink_Button_clicked();

    void ColorUpdateHelper(QColor new_color);

    void UpdateCells();


    void on_step_Button_clicked();

    void on_pause_Button_clicked();

    void on_play_Button_clicked();

    float PopulationCount();

    void AddGraph(int x, float height);

    void DeleteGraph();


    void ZombieHelper();

    void on_zombieButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsView * view;

    QGraphicsView * graph_view_;

    QTimer * timer_;

    int time_step_=1000;

    int turn_=0;

    int graph_pos_=0;

    static const int cells_row_ = 10;
    static const int cells_column_ = 20;
    Cell * cell_grid_ [cells_column_][cells_row_];

    std::vector< Graph *> graph_vector_;
    bool zombie_mode_=false;

};
#endif // MAINWINDOW_H
