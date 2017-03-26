#ifndef UTIL_H
#define UTIL_H

#define DEBUG_OUTPUT false

#if DEBUG_OUTPUT
    #define DEBUG qDebug() << Q_FUNC_INFO
#else
    #define DEBUG qDebug()
#endif

class Util
{
public:
    Util();
};

#endif // UTIL_H
