#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QJsonObject>
#include "basicClasses.h"

class UserManager {
public:
    static QString encryptPassword(const QString &password);
    static bool loadUserData(QJsonArray &userArray);
    static void saveUserData(const QJsonArray &userArray);
    static bool isUsernameTaken(const QString &username);
    static void registerUser(const QString &username, const QString &password);
    static bool loginUser(const QString &username, const QString &password, UserInformation * currentUser);
    static void storageUserInformation(UserInformation * currentUser);

};

#endif // USERMANAGER_H
