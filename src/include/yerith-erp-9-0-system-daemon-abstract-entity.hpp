/*
 * yerith-erp-9-0-system-daemon-abstract-entity.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_SYSTEM_DAEMON_ABSTRACT_ENTITY_HPP_
#define YERITH_ERP_3_0_SYSTEM_DAEMON_ABSTRACT_ENTITY_HPP_


#include "src/include/yerith-erp-9-0-definition-oo-class-operators.hpp"

#include "src/utils/yerith-erp-9-0-system-daemon-utils.hpp"


#include <QtCore/QTimer>

#include <QtSql/QSqlRecord>

#include <QtSql/QSqlQuery>

#include <QtSql/QSqlError>

#include <QtCore/QObject>

#include <QtCore/QString>


class QTimer;

class YERITH_ERP_SYSTEM_DAEMON_LOGGER;


class YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY:public QObject
{
Q_OBJECT public:

    YERITH_CLASS_OPERATORS
    inline YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY()
	:_dbusServer(0),
	 _alertesTimeIntervall(0),
     _alertesTimer(0),
	 _logger(0)
    {
    	_dbusServer = new YERITH_RUNTIME_VERIFIER;
    }

    inline YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY(YERITH_ERP_SYSTEM_DAEMON_LOGGER *aLogger)
    :_dbusServer(0),
	 _alertesTimeIntervall(0),
	 _alertesTimer(0),
	 _logger(aLogger)
    {
    	_dbusServer = new YERITH_RUNTIME_VERIFIER;
    }

    inline virtual ~YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY()
    {
    	delete _dbusServer;
    }


    inline YERITH_RUNTIME_VERIFIER *dbusServer()
    {
        return _dbusServer;
    }


protected:

    YERITH_RUNTIME_VERIFIER *_dbusServer;

    int _alertesTimeIntervall;

    QTimer *_alertesTimer;

    YERITH_ERP_SYSTEM_DAEMON_LOGGER *_logger;
};


#endif /* YERITH_ERP_3_0_SYSTEM_DAEMON_ABSTRACT_ENTITY_HPP_ */
