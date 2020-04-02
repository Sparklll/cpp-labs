#include "Enrollee.h"

Enrollee::Enrollee(QString id,
                   QString name,
                   QString surname,
                   QString patronymic,
                   QString adress,
                   QVector<QString> score)
{
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->patronymic = patronymic;
    this->adress = adress;
    this->score = score;
}

QJsonObject Enrollee::toJsonObject()
{
    QJsonObject jsonObj;
    jsonObj.insert("Id", getId());
    jsonObj.insert("Name", getName());
    jsonObj.insert("Surname", getSurname());
    jsonObj.insert("Patronymic", getPatronymic());
    jsonObj.insert("Adress", getAdress());
    jsonObj.insert("SC", getScore().at(0));
    jsonObj.insert("CT1", getScore().at(1));
    jsonObj.insert("CT2", getScore().at(2));
    jsonObj.insert("CT3", getScore().at(3));

    return jsonObj;
}

Enrollee Enrollee::fromJsonObject(QJsonObject enrolleeObj)
{
    QString enrolleeObjId = enrolleeObj.value("Id").toString();
    QString enrolleeObjName = enrolleeObj.value("Name").toString();
    QString enrolleeObjSurname = enrolleeObj.value("Surname").toString();
    QString enrolleeObjPatronymic = enrolleeObj.value("Patronymic").toString();
    QString enrolleeObjAdress = enrolleeObj.value("Adress").toString();
    QString enrolleeObjSC = enrolleeObj.value("SC").toString();
    QString enrolleeObjCT1 = enrolleeObj.value("CT1").toString();
    QString enrolleeObjCT2 = enrolleeObj.value("CT2").toString();
    QString enrolleeObjCT3 = enrolleeObj.value("CT3").toString();

    Enrollee enrollee(enrolleeObjId,
                      enrolleeObjName,
                      enrolleeObjSurname,
                      enrolleeObjPatronymic,
                      enrolleeObjAdress,
                      QVector<QString>()
                          << enrolleeObjSC << enrolleeObjCT1 << enrolleeObjCT2 << enrolleeObjCT3);
    return enrollee;
}

QString Enrollee::toString()
{
    QString totalScore;

    return getName() + " " + getSurname() + " " + getPatronymic() + " " + getAdress() + " "
           + getTotalScore() + " " + getScore().at(0) + " " + getScore().at(1) + " "
           + getScore().at(2) + " " + getScore().at(3);
}

QString Enrollee::getId() const
{
    return id;
}

void Enrollee::setId(const QString &value)
{
    id = value;
}

QString Enrollee::getName() const
{
    return name;
}

void Enrollee::setName(const QString &value)
{
    name = value;
}

QString Enrollee::getSurname() const
{
    return surname;
}

void Enrollee::setSurname(const QString &value)
{
    surname = value;
}

QString Enrollee::getPatronymic() const
{
    return patronymic;
}

void Enrollee::setPatronymic(const QString &value)
{
    patronymic = value;
}

QString Enrollee::getAdress() const
{
    return adress;
}

void Enrollee::setAdress(const QString &value)
{
    adress = value;
}

QVector<QString> Enrollee::getScore() const
{
    return score;
}

void Enrollee::setScore(const QVector<QString> &value)
{
    score = value;
}

QString Enrollee::getTotalScore() const
{
    int totalScore = 0;
    foreach (QString singleScore, this->getScore()) {
        totalScore += singleScore.toInt();
    }

    return QString::number(totalScore);
}

QString Enrollee::toString() const
{
    return getName() + " " + getSurname() + " " + getPatronymic() + " " + getAdress() + " "
           + getTotalScore() + " " + getScore().at(0) + " " + getScore().at(1) + " "
           + getScore().at(2) + getScore().at(3);
}
