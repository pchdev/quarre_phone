#ifndef ROTATIONSPAT_GLOBAL_H
#define ROTATIONSPAT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ROTATIONSPAT_LIBRARY)
#  define ROTATIONSPATSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ROTATIONSPATSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ROTATIONSPAT_GLOBAL_H