#ifndef CANVASSERIALIZER_H
#define CANVASSERIALIZER_H

#include <QByteArray>
#include <QString>

class CanvasSerializer
{
public:
    CanvasSerializer();
    ~CanvasSerializer() = default;

    static QString toQString(QByteArray &barr);
    static QByteArray toQByteArray(QString &qstring);
};

#endif // CANVASSERIALIZER_H
