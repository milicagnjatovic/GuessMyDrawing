#include "canvasserializer.h"

CanvasSerializer::CanvasSerializer()
{

}

QString CanvasSerializer::toQString(QByteArray &barr)
{
    return QString(barr.toBase64());
}

QByteArray CanvasSerializer::toQByteArray(QString &qstring)
{
    return QByteArray::fromBase64(qstring.toUtf8());
}
