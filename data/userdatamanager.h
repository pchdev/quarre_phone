#ifndef USERDATAMANAGER_H
#define USERDATAMANAGER_H

#include "../control/control.h"

namespace quarre {

class UserDataManager {

public:
    UserDataManager();
    ~UserDataManager();
    void setUserId(int id);
    void setServerAddress(QUrl address);
    int getUserId() const;
    QUrl getServerAddress() const;

private:
    int m_id;
    QUrl m_server_address;
};

}

#endif // USERDATAMANAGER_H
