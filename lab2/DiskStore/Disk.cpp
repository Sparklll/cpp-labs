#include "Disk.h"

const QVector<QString> Disk::typeInformation = QVector<QString>() << "Game"
                                                                  << "Film"
                                                                  << "Music"
                                                                  << "Photo"
                                                                  << "Soft"
                                                                  << "Utility";

Disk::Disk(QString id, QString diskType, QString name, QString author, QString note, QString price)
{
    this->id = id;
    this->diskType = diskType;
    this->name = name;
    this->author = author;
    this->note = note;
    this->price = price;
}

QJsonObject Disk::toJsonObject()
{
    QJsonObject jsonObj;
    jsonObj.insert("Id", getId());
    jsonObj.insert("Disk Type", getDiskType());
    jsonObj.insert("Name", getName());
    jsonObj.insert("Author", getAuthor());
    jsonObj.insert("Note", getNote());
    jsonObj.insert("Price", getPrice());

    return jsonObj;
}

Disk Disk::fromJsonObject(QJsonObject diskObj)
{
    QString diskObjId = diskObj.value("Id").toString();
    QString diskObjType = diskObj.value("Disk Type").toString();
    QString diskObjName = diskObj.value("Name").toString();
    QString diskObjAuthor = diskObj.value("Author").toString();
    QString diskObjNote = diskObj.value("Note").toString();
    QString diskObjPrice = diskObj.value("Price").toString();
    Disk disk(diskObjId, diskObjType, diskObjName, diskObjAuthor, diskObjNote, diskObjPrice);
    return disk;
}

QString Disk::getDiskType() const
{
    return diskType;
}

void Disk::setDiskType(const QString &value)
{
    diskType = value;
}

QString Disk::getName() const
{
    return name;
}

void Disk::setName(const QString &value)
{
    name = value;
}

QString Disk::getAuthor() const
{
    return author;
}

void Disk::setAuthor(const QString &value)
{
    author = value;
}

QString Disk::getNote() const
{
    return note;
}

void Disk::setNote(const QString &value)
{
    note = value;
}

QString Disk::getPrice() const
{
    return price;
}

void Disk::setPrice(const QString &value)
{
    price = value;
}

QString Disk::getId() const
{
    return id;
}

QString Disk::toString()
{
    return getDiskType() + " " + getName() + " " + getAuthor() + " " + getNote() + " " + getPrice();
}
