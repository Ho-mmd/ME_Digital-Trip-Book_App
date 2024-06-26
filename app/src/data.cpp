#include "data.hpp"

Data::Data(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Data::onFinished);
}

Data::~Data() {

}

void Data::fetchData() {
    QUrl url("http://Server_Address/raw_data");
    QNetworkRequest request(url);
    manager->get(request);
}

void Data::onFinished(QNetworkReply *reply) {
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray resultDataArray = jsonObj["result_data"].toArray();
    QJsonArray locationArray = jsonObj["raw_data"].toArray();
    QJsonArray warnArray = jsonObj["overpoint_data"].toArray();

    m_locations.clear();
    m_accel.clear();
    m_decel.clear();

    for (const QJsonValue &value : locationArray) {
        QJsonObject obj = value.toObject();
        m_locationX = obj["LocationX"].toDouble();
        m_locationY = obj["LocationY"].toDouble();
        m_locations.append(QVariantMap{{"x", m_locationX}, {"y", m_locationY}});
    }

    emit locationsChanged();

    for (const QJsonValue &value : warnArray) {
        QJsonObject obj = value.toObject();
        if(obj["type"].toInt() == 0) {
            m_locationX = obj["x_over"].toDouble();
            m_locationY = obj["y_point"].toDouble();
            m_accel.append(QVariantMap{{"x", m_locationX}, {"y", m_locationY}});
        } else if(obj["type"].toInt() == 1) {
            m_locationX = obj["x_over"].toDouble();
            m_locationY = obj["y_point"].toDouble();
            m_decel.append(QVariantMap{{"x", m_locationX}, {"y", m_locationY}});
        } else if(obj["type"].toInt() == 2) {
            m_locationX = obj["x_over"].toDouble();
            m_locationY = obj["y_point"].toDouble();
            m_night.append(QVariantMap{{"x", m_locationX}, {"y", m_locationY}});
        }
    }

    emit warnChanged();

    if (!resultDataArray.isEmpty()) {
        QJsonObject obj = resultDataArray.last().toObject();
        m_distance = QString::number(obj["Distance"].toDouble());
        m_distance_available = QString::number(obj["Distance_available"].toDouble());
        m_battery = QString::number(obj["battery"].toDouble());
        m_score_fuel = obj["score_fuel"].toInt();
        m_score_safety = obj["score_safety"].toInt();
        m_score_time = obj["score_time"].toInt();
        m_acel_score = obj["score_Acc"].toInt();
        m_dcel_score = obj["score_Dec"].toInt();
        m_night_score = obj["score_night"].toInt();
        m_driving_type = obj["driving_type"].toInt();

        if(m_driving_type == 111)
            m_driving_type = 0;
        else if(m_driving_type == 112)
            m_driving_type = 1;
        else if(m_driving_type == 121)
            m_driving_type = 2;
        else if(m_driving_type == 211)
            m_driving_type = 3;
        else if(m_driving_type == 122)
            m_driving_type = 4;
        else if(m_driving_type == 212)
            m_driving_type = 5;
        else if(m_driving_type == 221)
            m_driving_type = 6;
        else if(m_driving_type == 222)
            m_driving_type = 7;

        emit dataChanged();
    }

    if(m_openingSignal == 0) {
        emit dataReady();
        m_openingSignal++;
    }

    reply->deleteLater();
}

QString Data::distance() const {
    return m_distance;
}

QString Data::distance_available() const {
    return m_distance_available;
}

QString Data::battery() const {
    return m_battery;
}

int Data::score_fuel() const {
    return m_score_fuel;
}

int Data::score_safety() const {
    return m_score_safety;
}

int Data::score_time() const {
    return m_score_time;
}

QVariantList Data::locations() const {
    return m_locations;
}

QVariantList Data::acceleration() const {
    return m_accel;
}

QVariantList Data::deceleration() const {
    return m_decel;
}

QVariantList Data::night() const {
    return m_night;
}

int Data::openingSignal() const {
    return m_openingSignal;
}

void Data::setopeningSignal(int openingSignal) {
    m_openingSignal = openingSignal;

    emit openingInitialized();
}

int Data::acel_score() const {
    return m_acel_score;
}

int Data::dcel_score() const {
    return m_dcel_score;
}

int Data::night_score() const {
    return m_night_score;
}

int Data::driving_type() const {
    return m_driving_type;
}
