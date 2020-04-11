#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "cell.h"

/**
  Creates a new Cell object with coordinates x and y
  @param x int x coordinate
  @param y int y coordinate
*/
Cell::Cell(const int x, const int y, const int row, const int col){
  x_ = x;
  y_ = y;
  row_=row;
  col_=col;
  if(qrand()%2){ //Radomly generate 50 50 chance of life
      is_alive_=true;
      color_=QColor(0,255,0);
  }
  else{
      is_alive_=false;
      color_=QColor(255,255,255);
  }

}

/**
  Click on cell. When left its alive and change to corresponding correct color
  right click dies
 */
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    // Day 2, Task 4 (pre-lecture 20 work)
    // change to a new color
    QColor white(255, 255, 255);
    if (event->button()==Qt::RightButton){
        color_=white;
        is_alive_=false;
    }
    if(event->button()==Qt::LeftButton){
        color_ = alive_color_;
        is_alive_=true;
    }

    update();

}

// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Cell::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

// define the actual shape of the object
QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

// called by Qt to actually display the Cell
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

/**
  Calculates the distance between this Cell and another Cell.
  @param other Cell object to calculate the distance to
*/
double Cell::Distance(const Cell &other) const {
  double distance = (x_ - other.get_x()) * (x_ - other.get_x());
  distance += (y_ - other.y_) * (y_ - other.y_);
  return sqrt(distance);
}




/**
  Makes it so the == operator will have the behavior that you
  expect when comparing Cells.
  You can overload pretty much any operator in c++
  @param first Cell left hand side of the expression
  @param other Cell right hand side of the expression
*/
bool operator==(const Cell &first, const Cell &other) {
  return first.x_ == other.x_ && first.y_ == other.y_;
}
