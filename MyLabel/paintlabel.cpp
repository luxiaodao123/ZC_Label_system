#include "paintlabel.h"
#include <QDebug>

PaintLabel::PaintLabel(QWidget* parent):
    QLabel(parent)
{
    this->resize(631, 451);
    m_pix = new QImage(this->width(), this->height(), QImage::Format_RGB32);
    m_pix->fill(Qt::white);
    m_isNullImage = true;
    m_index = 1;
}

PaintLabel::~PaintLabel()
{
    delete m_pix;
}

void PaintLabel::paintEvent(QPaintEvent *e)
{
     QPainter wp(this);
     wp.setOpacity(0.2);
     wp.drawImage(0, 0, *m_pix);
}

void PaintLabel::mousePressEvent(QMouseEvent *e)
{
    if(m_isNullImage == true)
        return;
    m_PosStart = QPointF(e->pos().x(), e->pos().y());
    m_Poscurrent = m_PosStart;
    m_PointPool.append(m_Poscurrent);
}

void PaintLabel::mouseMoveEvent(QMouseEvent *e)
{
    if(m_isNullImage == true)
        return;
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::black);

    painter->begin(m_pix);
    painter->setPen(pen);
    painter->drawLine(m_Poscurrent, QPoint(e->pos().x(), e->pos().y()));
    m_Poscurrent = QPointF(e->pos().x(), e->pos().y());
    painter->end();

    m_PointPool.append(m_Poscurrent);

    update();
    delete painter;

}

void PaintLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_isNullImage == true)
        return;

    if(e->button() == Qt::LeftButton)
    {
        _leftButtomRelaese();
    }

    if(e->button() == Qt::RightButton)
    {
        _rightButtomRelaese();
    }

    m_PointPool.clear();

    if(NULL != m_Poly)
    {
        delete  m_Poly;
        m_Poly = NULL;
    }


}

void PaintLabel::wheelEvent(QWheelEvent *e)
{
    if(m_isNullImage == true)
        return;
    float step;
    if(e->delta() > 0)
        step = 1.1;
    else
        step = 0.9;

    changeSize(step);

}

void PaintLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
     QMap<int,QPolygonF>::Iterator i = m_polyPool.begin();
     while(i != m_polyPool.end())
     {
           if(i.value().containsPoint(e->pos(), Qt::OddEvenFill))
           {
               emit currentLabel(i.key());
           }
           ++i;
     }

}

void PaintLabel::_leftButtomRelaese()
{

//    _myIntersect(0);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::black);

    QPainter *painter = new QPainter;
    painter->begin(m_pix);
    painter->setPen(pen);
    painter->drawLine(m_Poscurrent, m_PosStart); //补全区域


    m_Poly = new QPolygonF(m_PointPool);

    if(m_Poly->boundingRect().width() < 5 )
    {
        qDebug() << "Poly width less than 5";
        delete painter;
        return;
    }

    QPainterPath path;
    path.addPolygon(*m_Poly);
    painter->setOpacity(0);
    painter->fillPath(path, QBrush(Qt::white));
    painter->end();


    QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
    QMap<int, QPolygonF>::Iterator itTemp;
    QPolygonF temp;
    int tempIndex = 0;
	int i = 0;
    while(it != m_polyPool.end())
    {
		itTemp = it++;
		if (!itTemp.value().intersected(*m_Poly).isEmpty())
		{
			_cleanPen(*m_Poly);
			temp = itTemp.value();
			QPolygonF both = temp.united(*m_Poly);
			for (i = 0; i < m_Poly->count(); i++)
			{
				if (!temp.containsPoint(m_Poly->at(i), Qt::OddEvenFill))
					break;
			}
			if (i == m_Poly->count())
			{
				tempIndex = itTemp.key();
				m_polyPool.erase(itTemp);
			}
			else
			{
				*m_Poly = both;
				tempIndex = itTemp.key();
				m_polyPool.erase(itTemp);
			}
			_cleanPen(temp);
		}
    }

    if(!temp.isEmpty())
    {
        m_polyPool[tempIndex] = *m_Poly;
        _paintPen(*m_Poly);
    }
    else
    {
		m_polyPool[m_index] = *m_Poly;
		emit addLabel(m_index++);
    }

    update();
    delete painter;

}

void PaintLabel::_rightButtomRelaese()
{
    QPainter *painter = new QPainter;
    m_Poly = new QPolygonF(m_PointPool);
    painter->begin(m_pix);
    QPainterPath path;
    path.addPolygon(*m_Poly);
    painter->setOpacity(0);
    painter->fillPath(path,QBrush(Qt::white));
    painter->end();
	_cleanPen(*m_Poly);

    QMap<int,QPolygonF>::Iterator it = m_polyPool.begin();
    QMap<int,QPolygonF>::Iterator itTemp;
    QPolygonF temp;
    int tempIndex = 0;
	int i = 0;
    while(it != m_polyPool.end())
    {
          itTemp = it++;
          if(!itTemp.value().intersected(*m_Poly).isEmpty())
          {
              
			  for (i = 0; i < m_Poly->count(); i++)
			  {
				  if (!itTemp.value().containsPoint(m_Poly->at(i), Qt::OddEvenFill))
					  break;
			  }
			  if (i != m_Poly->count())
			  {
                  _cleanPen(itTemp.value());
                  temp = *m_Poly;
                  QPolygonF both = m_Poly->united(itTemp.value());
                  *m_Poly = both.subtracted(*m_Poly);
                  tempIndex = itTemp.key();
                  m_polyPool.erase(itTemp);
              }

          }
    }
    if(!temp.isEmpty())
    {
        if(m_Poly->boundingRect().width() != 0)
        {
            m_polyPool[tempIndex] = *m_Poly;
            _paintPen(*m_Poly);
        }
        else
        {
            emit removeLabel(tempIndex);
        }
    }
    update();
    delete painter;
}

void PaintLabel::_cleanPen(QPolygonF pointPool)
{
    QPainter *painter = new QPainter;
    for(int i = 0 ; i < pointPool.count(); i++)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        pen.setColor(Qt::white);
        painter->begin(m_pix);
        painter->setPen(pen);
        if(i == pointPool.count() - 1 )
        {
           painter->drawLine(pointPool.at(i), pointPool.at(0));
        }
        else
        {
           painter->drawLine(pointPool.at(i), pointPool.at(i + 1));
        }
        painter->end();
    }

    update();
    delete painter;
}

void PaintLabel::_paintPen(QPolygonF pointPool)
{
    QPainter *painter = new QPainter;
    for(int i = 0 ; i< pointPool.count(); i++)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        pen.setColor(Qt::black);

        painter->begin(m_pix);
        painter->setPen(pen);
        if(i == 0 )
        {
            painter->drawLine(pointPool.at(pointPool.count() - 1), pointPool.at(0));
        }
        else
        {
            painter->drawLine(pointPool.at(i-1), pointPool.at(i));
        }
        painter->end();
    }
    update();
    delete painter;
}

void PaintLabel::_myIntersect(int flag)
{
    QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
    QMap<int, QPolygonF>::Iterator itTemp;
    QPolygonF temp;
    int tempIndex = 0;
    while(it != m_polyPool.end())
    {
          itTemp = it++;
          if(itTemp.value().containsPoint(m_PosStart, Qt::OddEvenFill))
          {
              temp = itTemp.value();
              for(int i = 0; i < m_PointPool.count() - 1; i++)
              {
                  if(temp.containsPoint(temp[i], Qt::OddEvenFill) && !temp.containsPoint(temp[i + 1], Qt::OddEvenFill))
                  {

                  }
              }





//              *m_Poly = temp.united(*m_Poly);
//              tempIndex = itTemp.key();
//              m_polyPool.erase(itTemp);
          }
    }
}

void PaintLabel::changeSize(float step)
{
    float origin = m_step;
    m_step = m_step * step;

    if(m_step < 1)
    {
        m_step = 1.0;
        origin = m_step / origin;
    }

    if(m_step > 5)
    {
        //qDebug() << m_step << "now";
        m_step = origin;
        return;
    }

    cleanPainter();
    emit  changeImageSize(m_step);
    QMap<int, QPolygonF>::Iterator it = m_polyPool.begin();
    while(it != m_polyPool.end())
    {

        QPolygonF temp = it.value();
        _cleanPen(temp);
        int count = temp.count();
        for(int i = 0; i < count; i++)
        {
            qDebug() << temp[i];
            if(m_step > 1)
            temp[i] = QPointF(temp[i].x() * step  , temp[i].y() * step );
            else
            temp[i] = QPointF(temp[i].x() * origin , temp[i].y() * origin );
            qDebug() << temp[i] << "one";
        }

        QPainter *painter = new QPainter;
        m_polyPool[it.key()] = temp;
        _paintPen(temp);
        painter->begin(m_pix);

        QPainterPath path;
        path.addPolygon(temp);
        painter->setOpacity(0);
        painter->fillPath(path, QBrush(Qt::white));
        painter->end();
        update();
        it++;
        delete painter;
    }

}

void PaintLabel::cleanPainter()
{
	delete m_pix;
	m_pix = new QImage(this->width(), this->height(), QImage::Format_RGB32);
	m_pix->fill(Qt::white);
}

void PaintLabel::Resize(QSize size)
{
	this->resize(size.width(), size.height());
	*m_pix = m_pix->scaled(size.width(), size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	update();
}

QMap<int, QPolygonF> PaintLabel::labelInfo()
{
    return m_polyPool;
}

void PaintLabel::isNullImage(bool null)
{
    m_isNullImage = null;
}

void PaintLabel::setStep(float step)
{
    m_step = step;
}

void PaintLabel::cleanPolyPool()
{
    m_polyPool.clear();
}

float PaintLabel::getStep()
{
    return m_step;
}

void PaintLabel::paint(QPolygonF poly, int index)
{
//    QPainter *painter = new QPainter;

//    painter->begin(m_pix);
//    QPainterPath path;
//    path.addPolygon(poly);
//    painter->fillPath(path, QBrush(Qt::black));
//    painter->end();
//    update();
//    delete painter;

    _paintPen(poly);
    m_polyPool.insert(index, poly);
}

void PaintLabel::setIndex(int index)
{
    m_index = index;
}

const int PaintLabel::getIndex() const
{
    return m_index;
}
