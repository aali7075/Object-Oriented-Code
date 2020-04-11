#ifndef Cell_H
#define Cell_H

#include <QColor>
#include <QGraphicsItem>

// any object that inherits from QObject can emit signals
// things that inherit from QGraphicsItem can be added to QGraphicScenes
class Cell: public QObject, public QGraphicsItem {

    // this makes it so that we can emit signals
    Q_OBJECT

public:
    static const int width_=30;
    Cell(const int x, const int y, const int row, const int col);  // constructor

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function

    int get_row() const { return row_; }  // inline member function
    int get_col() const { return col_; }  // inline member function

    int get_is_alive(){ return is_alive_; }  // inline member function
    void set_is_alive(bool alive){ is_alive_=alive; }  // inline member function

    QColor get_color() { return color_; }  // inline member function
    void set_color(QColor new_color) { color_=new_color; update(); }  // inline member function

    void set_alive_color(QColor new_color) { alive_color_ = new_color; }  // inline member function
    QColor get_alive_color(){return alive_color_; }

    void set_next_turn_status(bool alive) { next_turn_status=alive;}  // inline member function
    bool get_next_turn_status(){ return next_turn_status; }  // inline member function







    double Distance(const Cell &other) const;  // member function

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


// in Cell.h
signals:

    // Day 2, Task 3
    void CellSelected(Cell * c);
    void DeleteCell(Cell * c);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;




private:
  int row_;
  int col_;
  int x_;
  int y_;
  bool is_alive_;
  bool next_turn_status;
  QColor color_; // The cell's current color either white for dead or alive
  QColor alive_color_;


  // all our Cells will be 20 wide and tall (they are circles)

  // if you declare the operator as a friend, then it isn't
  // part of the object
  // friend will let this method access the private fields
  friend bool operator==(const Cell &first, const Cell &other);
};  // class Cell



#endif // Cell_H
