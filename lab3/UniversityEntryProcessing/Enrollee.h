#ifndef ENROLLEE_H
#define ENROLLEE_H

#include <QJsonObject>
#include <QString>
#include <QUuid>
#include <QVector>

class Enrollee
{
public:
    Enrollee(QString id,
             QString name,
             QString surname,
             QString patronymic,
             QString adress,
             QVector<QString> score);
    static Enrollee fromJsonObject(QJsonObject enrolleeObj);

    QJsonObject toJsonObject();
    QString toString();

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getSurname() const;
    void setSurname(const QString &value);

    QString getPatronymic() const;
    void setPatronymic(const QString &value);

    QString getAdress() const;
    void setAdress(const QString &value);

    QVector<QString> getScore() const;
    void setScore(const QVector<QString> &value);

    QString getTotalScore() const;
    QString toString() const;

private:
    QString id;
    QString name;
    QString surname;
    QString patronymic;
    QString adress;
    QVector<QString> score;
};

#endif
