#ifndef CANVAS_H
#define CANVAS_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QString>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas() = default;

    bool isModified() const;

//    void takeSnapshot(QByteArray& barr);
//    void loadFromSnapshot(const QByteArray& arr);
    QString takeSnapshot();
    void loadFromSnapshot(QString &qstring);

    int penWidth() const;
    void setPenWidth(int width);
    void setPenColor(QColor color);


public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:

    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool _modified = false;
    bool _drawing = false;
    int _myPenWidth = 5;
    const int _maxPenWidth = 10;
    const int _minPenWidth = 1;

    QColor _myPenColor = Qt::black;
    QImage _image;
    QPoint _lastPoint;


};

#endif // CANVAS_H
