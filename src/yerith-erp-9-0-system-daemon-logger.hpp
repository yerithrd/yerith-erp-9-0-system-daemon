/*
 * yeren-erp-alert-logger.hpp
 *
 *      Author: PROF. DR.-ENG. DIPL.-INF. Xavier Noundou
 */

#ifndef SRC_YERITH_LOGGER_HPP_
#define SRC_YERITH_LOGGER_HPP_

#include <QtCore/QString>

class QDebug;
class QFile;

class YERITH_ERP_SYSTEM_DAEMON_LOGGER
{
public:

    typedef enum _YERITH_LOG_LEVEL
    {
        YERITH_DEBUG = 0,
        YERITH_LOG,
        YERITH_WARN
    } YERITH_LOG_LEVEL;

    YERITH_ERP_SYSTEM_DAEMON_LOGGER(QString cppClassName,
                                    YERITH_LOG_LEVEL logLevel = YERITH_LOG);

    ~YERITH_ERP_SYSTEM_DAEMON_LOGGER();

    void debug(const char *cppMethodName, const char *msg = "");

    void debug(const char *cppMethodName, QString msg);

    void log(const char *cppMethodName, const char *msg = "");

    void log(const char *cppMethodName, QString msg);

    YERITH_ERP_SYSTEM_DAEMON_LOGGER &operator<< (const char *s);
    YERITH_ERP_SYSTEM_DAEMON_LOGGER &operator<< (QString s);
    YERITH_ERP_SYSTEM_DAEMON_LOGGER &operator<< (bool s);
    YERITH_ERP_SYSTEM_DAEMON_LOGGER &operator<< (int s);
    YERITH_ERP_SYSTEM_DAEMON_LOGGER &operator<< (char s);
    YERITH_ERP_SYSTEM_DAEMON_LOGGER &operator<< (QByteArray s);

    inline void *operator  new[](size_t size)
    {
        return malloc(size);
    }

    inline void *operator  new (size_t size)
    {
        return malloc(size);
    }

    inline void operator  delete[](void *ptr)
    {
        free(ptr);
    }

    inline void operator  delete[](void *ptr, size_t)
    {
        free(ptr);
    }

    inline void operator  delete (void *ptr)
    {
        free(ptr);
    }

    inline void operator  delete (void *ptr, size_t)
    {
        free(ptr);
    }

private:

    YERITH_LOG_LEVEL _logLevel;

    QString _cppClassName;

    QDebug *_qDebug;
    QFile *_logFile;
};


#endif //SRC_YERITH_LOGGER_HPP_
