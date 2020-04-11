#include <QDebug>
#include <QTimer>
#include <QTime>

#include "cell.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
    Constructor.
    Create the scenes for both the grid and the graph
    Intializes all the cells for the cell grid
    Intializes the bar for the first graph
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qsrand(static_cast<unsigned>(QTime::currentTime().msec()));


    QGraphicsScene * scene = new QGraphicsScene;
    view = ui->graphicsView;
    view->setScene(scene);
    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    ui->turnLabel->setText(QString(std::to_string(turn_).c_str()));


    timer_ = new QTimer(this);
    timer_->stop(); // in miliies

    connect(timer_,&QTimer::timeout,this,&MainWindow::on_step_Button_clicked); // If timer is started do all options


    int width=10;
    int height=10;
    for(int i=0; i<cells_row_; i++){ //Create the cell_grid
        for(int j=0; j<cells_column_; j++){
          cell_grid_[j][i]= new Cell(width,height,j,i);
          cell_grid_[j][i]->set_alive_color(QColor(0,255,0));
          view->scene()->addItem(cell_grid_[j][i]);
          width+=Cell::width_;
        }
        height+=Cell::width_;
        width=10;
    }



    //THE GRAPH
    QGraphicsScene * graph_scene = new QGraphicsScene;
    graph_view_ = ui->graph;
    graph_view_->setScene(graph_scene);
    // make the scene the same size as the view containing it
    graph_view_->setSceneRect(0,0,graph_view_->frameSize().width(),graph_view_->frameSize().height());


    //ADD THE POPULATIONS BAR FOR FIRST TIME
    float h=this->PopulationCount();
    this->DeleteGraph();
    this->AddGraph(graph_pos_, h);


}

MainWindow::~MainWindow()
{
    delete ui;
}




/*
 This helper function will create a new grid with a new outerlayer
 corresponding with the oppisite side of the the current outlayers
 and the corners being the oppisite of that.
 Then does logic to check if cell shoudl stay alive
 */
void MainWindow::UpdateCells(){
    turn_+=1;

    ui->turnLabel->setText(QString(std::to_string(turn_).c_str()));

    int count=0;
    Cell * bigger_grid[cells_column_+2][cells_row_+2]; //i.e 22 columns and 12 rows

    //copy over the inner values for bigger grid
    for(int i=0; i<cells_column_; i++){
        for(int j=0; j<cells_row_; j++){
            bigger_grid[i+1][j+1]=cell_grid_[i][j];
        }
    }
    for(int i=0; i<cells_row_; i++ ){ //left outer layer
        bigger_grid[0][i+1]= cell_grid_[cells_column_-1][i];
    }
    for(int i=0; i<cells_row_; i++ ){ //right outer layer
        bigger_grid[cells_column_+1][i+1]= cell_grid_[0][i];
    }
    for(int i=0; i<cells_column_; i++ ){ //top outer layer
        bigger_grid[i+1][0]= cell_grid_[i][cells_row_-1];
    }
    for(int i=0; i<cells_column_; i++ ){ //bottom outer layer
        bigger_grid[i+1][cells_row_+1]= cell_grid_[i][0];
    }

    bigger_grid[0][0]= cell_grid_[cells_column_-1][cells_row_-1]; //upper left corner
    bigger_grid[cells_column_+1][cells_row_+1]= cell_grid_[0][0]; //lower right corner
    bigger_grid[0][cells_row_+1]= cell_grid_[cells_column_-1][0]; //lower right corner
    bigger_grid[cells_column_+1][0]= cell_grid_[0][cells_row_-1]; //lower right corner

    //Do cell logic
    for(int i=1; i<cells_column_+1; i++){
        for(int j=1; j<cells_row_+1; j++){
            if(bigger_grid[i-1][j-1]->get_is_alive()){//left upper corner
                count+=1;
            }
            if(bigger_grid[i-1][j]->get_is_alive()){//left middle
                count+=1;
            }
            if(bigger_grid[i-1][j+1]->get_is_alive()){//left bottom corner
                count+=1;
            }
            if(bigger_grid[i][j+1]->get_is_alive()){//bottom middle
                count+=1;
            }
            if(bigger_grid[i+1][j+1]->get_is_alive()){//right bottom corner
                count+=1;
            }
            if(bigger_grid[i+1][j]->get_is_alive()){// right middle
                count+=1;
            }
            if(bigger_grid[i+1][j-1]->get_is_alive()){// right upper corner
                count+=1;
            }
            if(bigger_grid[i][j-1]->get_is_alive()){// middle upper corner
                count+=1;
            }

            if(count==3){

                cell_grid_[i-1][j-1]->set_next_turn_status(true);
            }
            else if(count==2){
                cell_grid_[i-1][j-1]->set_next_turn_status(cell_grid_[i-1][j-1]->get_is_alive());
            }
            else{
                cell_grid_[i-1][j-1]->set_next_turn_status(false);
            }

        count=0;
        }
    }


    for(int i=0; i<cells_column_; i++){//update cells
        for(int j=0; j<cells_row_; j++){
            if(cell_grid_[i][j]->get_next_turn_status()){

                cell_grid_[i][j]->set_is_alive(true);
                cell_grid_[i][j]->set_color(cell_grid_[i][j]->get_alive_color());
            }
            else{
               cell_grid_[i][j]->set_is_alive(false);
               cell_grid_[i][j]->set_color(QColor(255,255,255));
            }
        }
    }
}


/**
ColorUpdateHelper is an helper function to update the color
If the cell is alive then update the color to the appropriate color
*/

void MainWindow::ColorUpdateHelper(QColor new_color){


    for(int i=0; i<cells_column_; i++){
        for(int j=0; j<cells_row_; j++){
            if(cell_grid_[i][j]->get_is_alive()){
               cell_grid_[i][j]->set_color(new_color);
            }
            cell_grid_[i][j]->set_alive_color(new_color);
        }
    }

}

void MainWindow::on_green_Button_clicked()
{
    ColorUpdateHelper(QColor(0,255,0));
}

void MainWindow::on_red_Button_clicked()
{
    ColorUpdateHelper(QColor(255,0,0));
}

void MainWindow::on_blue_Button_clicked()
{
    ColorUpdateHelper(QColor(0,0,255));
}

void MainWindow::on_pink_Button_clicked()
{
   ColorUpdateHelper(QColor(255,0,255));
}



/**
This slot does the main corse of actions.
 1. calls UpdateCells to check if they stay alive
 2. calls ZombieHelper if zombiemode is on
 3. determines height based on population porportion
 4. Deletes all the previous bar graphs from scene
 5. Show the new graph
 */
void MainWindow::on_step_Button_clicked()
{

    this->UpdateCells();
    this ->ZombieHelper();
    float height=this->PopulationCount();
    this->DeleteGraph();
    this->AddGraph(graph_pos_, height);




}




/**
    stop the timer which stops the connection from being called
 */
void MainWindow::on_pause_Button_clicked()
{
        timer_->stop(); // in miliies
}


/**
Everytime the horizontal slider is called we must update the time_step
to whatever the horizontal slider value is.

 */
void MainWindow::on_horizontalSlider_valueChanged(int value)
{

    int slide_value= value;
    qDebug() <<"Slide_value is "<<slide_value;
    time_step_= 1000-int(750*(float(slide_value/100.0)));
    std::string value_string = std::to_string(time_step_) + " miliseconds";
    ui->sliderLabel->setText(QString(value_string.c_str())); //change the label;
    timer_->start(time_step_);

}

/**
Emit signalfor the timer
 */
void MainWindow::on_play_Button_clicked()
{
    timer_->start(time_step_);
}

/**
Functions counts how many cells are alive and then gives the population
percentage.
 */
float MainWindow::PopulationCount(){
    float count=0;
    float pop_percent;
    for(int i=0; i<cells_column_; i++){
        for(int j=0; j<cells_row_; j++){
            if(cell_grid_[i][j]->get_is_alive()){
               count+=1;
            }
        }
    }

    pop_percent=count/(cells_column_*cells_row_);

    std::string pop= "Population "+ std::to_string(int(count)) + " (" + std::to_string(int(pop_percent*100)) +"%)";
    ui->populationLabel->setText(QString(pop.c_str()));

    return pop_percent;

}

/**
Deletes the bars from the scene. Needed to make sure bars aren't stack on each other
 */
void MainWindow::DeleteGraph(){
    for (unsigned int i = 0; i < graph_vector_.size(); i ++){
        graph_view_->scene()->removeItem(graph_vector_[i]);
        update();
    }
}


/**
Add a new bar each time corresponding to correct population height.
Once the graph reaches the end we will then start shifting previous values
so it looks like the bars move contiously
 */
void MainWindow::AddGraph(int x, float height){
    Graph * bar=new Graph(x,graph_view_->frameSize().height(),height);
    graph_vector_.push_back(bar);
    graph_pos_+=30;
    for(int i=0; i<graph_vector_.size(); i++){
        graph_view_->scene()->addItem(graph_vector_[i]);
    }

    if(graph_vector_.size() == 21){
            int x_shift;
            Graph * first = graph_vector_[0];
            graph_view_->scene()->removeItem(first);
            graph_vector_.erase(graph_vector_.begin());
            for(int i=0; i<graph_vector_.size(); i++){
               x_shift=graph_vector_[i]->get_x()-30;
               graph_vector_[i]->set_x(x_shift);
            }
            graph_pos_-=30;
        }
    qDebug()<<"graph_vector_size is "<<graph_vector_.size();
    qDebug()<<"grpha_pos_ is "<<graph_pos_;

    update();


}

/**
One of the extra features. Helper function that does the logic
to revive old dead cells.
 */
void MainWindow::ZombieHelper(){
    if(zombie_mode_){
        for(int i=0; i<cells_column_; i++){
            for(int j=0; j<cells_row_; j++){
                if(qrand()%100<5){ //5% chance for random revival
                    if(!cell_grid_[i][j]->get_is_alive()){
                      cell_grid_[i][j]->set_is_alive(true);
                    }
                }
            }
        }
    }
}



/**
For the zombieButton label turns private variable zombie_mode_ on and off
 */
void MainWindow::on_zombieButton_clicked()
{
    zombie_mode_= (!zombie_mode_);
    if(zombie_mode_){
        ui->zombieButton->setText(QString("Zombie Mode ON"));
    }
    else{
        ui->zombieButton->setText(QString("Zombie Mode"));
    }
}
