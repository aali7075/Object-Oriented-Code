#ifndef GRAPH_H
#define GRAPH_H

#include <QColor>
#include <QGraphicsItem>

// any object that inherits from QObject can emit signals
// things that inherit from QGraphicsItem can be added to QGraphicScenes
class Graph: public QObject, public QGraphicsItem {

    // this makes it so that we can emit signals
    Q_OBJECT

public:
    static const int width_=30;
    Graph(const int x, const int y, const float height_percent );  // constructor

    int get_x() const { return x_; }  // inline member function
    void set_x(int x) { x_=x; }  // inline member function
    int get_y() const { return y_; }  // inline member function

    int get_height() { return height_; }  // inline member function








    double Distance(const Graph &other) const;  // member function

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


// in GRAPH.h
signals:

    // Day 2, Task 3
    void GraphSelected(Graph * c);
    void DeleteGraph(Graph * c);

protected:




private:
  int x_;
  int y_; //height of window
  int height_;



  // all our GRAPHs will be 20 wide and tall (they are circles)

  // if you declare the operator as a friend, then it isn't
  // part of the object
  // friend will let this method access the private fields
  friend bool operator==(const Graph &first, const Graph &other);
};  // class GRAPH



#endif // GRAPH_H
