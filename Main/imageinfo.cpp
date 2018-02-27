#include "imageinfo.h"

ImageInfo::ImageInfo()
{
    m_step = 1.0;
    m_index = 1;
}

ImageInfo::ImageInfo(ImageInfo *temp)
{
    m_poly = temp->getPoly();
    m_step = temp->getStep();
    m_index = temp->getIndex();
    m_origin = temp->getOrigin();
    m_path = temp->getPath();
    m_focusInfo = temp->getFocusInfo();
}


ImageInfo::~ImageInfo()
{

}

const QMap<int, QPolygonF> ImageInfo::getPoly() const
{
    return m_poly;
}

const float ImageInfo::getStep() const
{
    return m_step;
}

const int ImageInfo::getIndex() const
{
    return m_index;
}

QPixmap *ImageInfo::getOrigin()
{
    return m_origin;
}

const QString ImageInfo::getPath() const
{
    return m_path;
}

const QMap<QString, QMap<QString, QString>> ImageInfo::getFocusInfo() const
{
    return m_focusInfo;
}

void ImageInfo::setPoly(QMap<int, QPolygonF> poly)
{
    m_poly = poly;
}

void ImageInfo::setFocusInfo(QMap<QString, QMap<QString, QString>> focusInfo)
{
    m_focusInfo = focusInfo;
}

void ImageInfo::setOrigin(QPixmap pix)
{
    m_origin = new QPixmap(pix);
}

void ImageInfo::setStep(float step)
{
    m_step = step;
}

void ImageInfo::setIndex(int index)
{
   m_index = index;
}

