#ifndef PAINTLABEL_H
#define PAINTLABEL_H
#include <QLabel>
#include <QMap>
#include <QPainter>
#include <QPolygonF>
#include <QMouseEvent>

class PaintLabel : public QLabel
{
    Q_OBJECT

public:
    PaintLabel(QWidget * parent = 0);
   
    ~PaintLabel();

	void cleanPainter();

	void Resize(QSize size);

    QMap<int, QPolygonF> labelInfo();

    void isNullImage(bool null);

    void setStep(float step);

    void setIndex(int index);

    float getStep();

    void cleanPolyPool();

    void changeSize(float step);

    void paint(QPolygonF poly, int index);

    const int getIndex() const;
    
protected:
    void paintEvent(QPaintEvent *e) ;

    void mousePressEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void wheelEvent(QWheelEvent *e);

    void mouseDoubleClickEvent(QMouseEvent *e);

private:
    void _leftButtomRelaese();

    void _rightButtomRelaese();

    void _cleanPen(QPolygonF pointPool);

    void _paintPen(QPolygonF pointPool);

    void _myIntersect(int flag);

signals:
    void changeImageSize(float size);

    void addLabel(int index);

    void currentLabel(int index);

    void removeLabel(int index);

    void paintNow();

private:
    QImage *m_pix;//画板
    QPointF m_PosStart;//起始点
    QPointF m_Poscurrent;//当前点
    QVector<QPointF> m_PointPool;//存放坐标
    QPolygonF *m_Poly;
    QMap<int, QPolygonF> m_polyPool;
    float m_step;
    int m_index;
    bool m_isNullImage;
    
};

#endif // PAINTLABEL_H
