#ifndef AI_LOGIN_GLOBAL_H
#define AI_LOGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AI_LOGIN_LIBRARY)
#  define AI_LOGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define AI_LOGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AI_LOGIN_GLOBAL_H
