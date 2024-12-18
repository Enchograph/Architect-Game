#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QUuid>
#include "basicClasses.h"
#include "userManager.h"




QString UserManager::encryptPassword(const QString &password) {
    // 使用SHA-256加密密码
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

bool UserManager::loadUserData(QJsonArray &userArray) {
    QFile file("userinfo.json");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Error", "无法读取用户数据文件");
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::warning(nullptr, "Error", "账户信息文件格式不正确");
        return false;
    }

    userArray = doc.array();
    file.close();
    return true;
}

void UserManager::saveUserData(const QJsonArray &userArray) {
    QFile file("userinfo.json");
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "Error", "无法写入用户数据文件");
        return;
    }

    QJsonDocument doc(userArray);
    file.write(doc.toJson());
    file.close();
}

bool UserManager::isUsernameTaken(const QString &username) {
    QJsonArray userArray;
    if (!loadUserData(userArray)) {
        return false;
    }

    for (const QJsonValue &value : userArray) {
        QJsonObject userObject = value.toObject();
        if (userObject["username"].toString() == username) {
            return true;
        }
    }

    return false;
}

void UserManager::registerUser(const QString &username, const QString &password) {
    QJsonArray userArray;
    loadUserData(userArray);

    QString uid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString encryptedPassword = encryptPassword(password);

    QJsonObject userObject;
    userObject["username"] = username;
    userObject["password"] = encryptedPassword;
    userObject["uid"] = uid;
    userObject["winNum"] = 0;
    userObject["loseNum"] = 0;
    userObject["drawNum"] = 0;

    userArray.append(userObject);
    saveUserData(userArray);
}

bool UserManager::loginUser(const QString &username, const QString &password, UserInformation * currentUser) {

    QJsonArray userArray;
    if (!loadUserData(userArray)) {
        qDebug("loginUser() load error");
        return false;
    }

    for (const QJsonValue &value : userArray) {
        QJsonObject userObject = value.toObject();
        QString storedPassword = userObject["password"].toString();
        QString encryptedPassword = encryptPassword(password);

        if (userObject["username"].toString() == username && encryptedPassword == storedPassword) {


            currentUser->currentUserName = username;
            currentUser->currentUid = userObject["uid"].toString();
            currentUser->currentWinNum = userObject["winNum"].toInt();
            currentUser->currentLoseNum = userObject["loseNum"].toInt();
            currentUser->currentDrawNum = userObject["drawNum"].toInt();
            return true;
        }
    }

    qDebug("loginUser() pswd or name not correct.");
    return false;
}
