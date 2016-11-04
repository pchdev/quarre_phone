#include "userdatamanager.h"

using namespace quarre;

UserDataManager::UserDataManager() :
    m_id(0),
    m_server_address("NULL") {}

UserDataManager::~UserDataManager() {}

void UserDataManager::setUserId(int id) {
    m_id = id;
}

void UserDataManager::setServerAddress(QUrl address) {
    m_server_address = address;
}

int UserDataManager::getUserId() const {
    return m_id;
}

QUrl UserDataManager::getServerAddress() const {
    return m_server_address;
}
