#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "graph.h"

/**
  Creates a new Graph object with coordinates x and y
  @param x int x coordinate
  @param y int y sets the height of the frame
  @param height is a percentage based on how many cells are alive
*/
Graph::Graph(const int x, const int y, const float height_precent){
  x_ = x;
  qDebug()<<"y is "<<y;
  height_=int(y*height_precent);//Length of the scene
  qDebug()<<"height "<<height_;
  y_=y-height_;

}



// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Graph::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

// define the actual shape of the object
QPainterPath Graph::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

// called by Qt to actually display the Graph
void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(QColor(255,255,255)));

    painter->drawRect(QRect(this->x_,this->y_, this->width_,this->height_));
    painter->setBrush(b);
}

/**
  Calculates the distance between this Graph and another Graph.
  @param other Graph object to calculate the distance to
*/
double Graph::Distance(const Graph &other) const {
  double distance = (x_ - other.get_x()) * (x_ - other.get_x());
  distance += (y_ - other.y_) * (y_ - other.y_);
  return sqrt(distance);
}




/**
  Makes it so the == operator will have the behavior that you
  expect when comparing Graphs.
  You can overload pretty much any operator in c++
  @param first Graph left hand side of the expression
  @param other Graph right hand side of the expression
*/
bool operator==(const Graph &first, const Graph &other) {
  return first.x_ == other.x_ && first.y_ == other.y_;
}
