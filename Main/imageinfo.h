#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QImage>
#include <QMap>
#include <QPolygonF>
#include <QPixmap>

class ImageInfo
{
public:
    ImageInfo();

    ImageInfo(ImageInfo *temp);

    ~ImageInfo();

public:
    const QMap<int, QPolygonF> getPoly() const;

    const float getStep() const;

    const int getIndex() const;

    QPixmap *getOrigin();

    const QString getPath() const;

    const QMap<QString, QMap<QString, QString>> getFocusInfo() const;

    void setPoly(QMap<int, QPolygonF> poly);

    void setFocusInfo(QMap<QString, QMap<QString, QString>> focusInfo);

    void setOrigin(QPixmap pix);

    void setStep(float step);

    void setIndex(int index);


private:
    QMap<int, QPolygonF> m_poly;
    float m_step;
    QPixmap *m_origin;
    int m_index;
    QMap<QString, QMap<QString, QString>> m_focusInfo;
    QString m_path;
};

#endif // IMAGEINFO_H
