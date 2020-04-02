#ifndef DISK_H
#define DISK_H

#include <QJsonObject>
#include <QString>
#include <QUuid>
#include <QVector>

class Disk
{
public:
    const static QVector<QString> typeInformation;

    Disk(QString id, QString diskType, QString name, QString author, QString note, QString price);
    QJsonObject toJsonObject();
    static Disk fromJsonObject(QJsonObject diskObj);

    QString getDiskType() const;
    void setDiskType(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getAuthor() const;
    void setAuthor(const QString &value);

    QString getNote() const;
    void setNote(const QString &value);

    QString getPrice() const;
    void setPrice(const QString &value);

    QString getId() const;

    QString toString();

private:
    QString id;
    QString diskType;
    QString name;
    QString author;
    QString note;
    QString price;
};

#endif // DISK_H
