/*
 * yerith-erp-9-0-system-daemon-logger.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yerith-erp-9-0-system-daemon-logger.hpp"

#include "src/utils/yerith-erp-9-0-system-daemon-utils.hpp"

#include <QtCore/QDebug>
#include <QtCore/QFile>

//#define YERITH_DEBUG_LOG

YERITH_ERP_SYSTEM_DAEMON_LOGGER::YERITH_ERP_SYSTEM_DAEMON_LOGGER(QString cppClassName, YERITH_LOG_LEVEL logLevel):_logLevel(logLevel),
    _cppClassName(cppClassName),
    _qDebug(0), _logFile(0)
{
    _logFile = new QFile(YerothERPAlertUtils::getLogFileName());
    _qDebug = new QDebug(_logFile);
    if (!_logFile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "[YerenLogger][YerenLogger] "
                 << "Could not create file " << YerothERPAlertUtils::getLogFileName();
    }
}

YERITH_ERP_SYSTEM_DAEMON_LOGGER::~YERITH_ERP_SYSTEM_DAEMON_LOGGER()
{
    delete _logFile;
    delete _qDebug;
}

void YERITH_ERP_SYSTEM_DAEMON_LOGGER::debug(const char *cppMethodName,
                                            const char *msg)
{
    *_qDebug << QString("DEBUG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() << QString("DEBUG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg;
#endif
}

void YERITH_ERP_SYSTEM_DAEMON_LOGGER::debug(const char *cppMethodName,
                                            QString msg)
{
    *_qDebug << QString("DEBUG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() << QString("DEBUG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg;
#endif
}

void YERITH_ERP_SYSTEM_DAEMON_LOGGER::log(const char *cppMethodName,
                                          const char *msg)
{
    *_qDebug << QString("LOG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() << QString("LOG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg;
#endif
}

void YERITH_ERP_SYSTEM_DAEMON_LOGGER::log(const char *cppMethodName,
                                          const QString msg)
{
    *_qDebug << QString("LOG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() << QString("LOG | %1 %2 | %3 | %4 |").
             arg(GET_CURRENT_STRING_DATE, CURRENT_TIME, _cppClassName,
                 cppMethodName).toStdString().c_str() << msg;
#endif
}

YERITH_ERP_SYSTEM_DAEMON_LOGGER &YERITH_ERP_SYSTEM_DAEMON_LOGGER::
operator<< (const char *s)
{
    *_qDebug << s;
    return *this;
}

YERITH_ERP_SYSTEM_DAEMON_LOGGER &YERITH_ERP_SYSTEM_DAEMON_LOGGER::
operator<< (QString s)
{
    *_qDebug << s;
    return *this;
}

YERITH_ERP_SYSTEM_DAEMON_LOGGER &YERITH_ERP_SYSTEM_DAEMON_LOGGER::
operator<< (bool s)
{
    *_qDebug << s;
    return *this;
}

YERITH_ERP_SYSTEM_DAEMON_LOGGER &YERITH_ERP_SYSTEM_DAEMON_LOGGER::
operator<< (int s)
{
    *_qDebug << s;
    return *this;
}

YERITH_ERP_SYSTEM_DAEMON_LOGGER &YERITH_ERP_SYSTEM_DAEMON_LOGGER::
operator<< (char s)
{
    *_qDebug << s;
    return *this;
}

YERITH_ERP_SYSTEM_DAEMON_LOGGER &YERITH_ERP_SYSTEM_DAEMON_LOGGER::
operator<< (QByteArray s)
{
    *_qDebug << s;
    return *this;
}
