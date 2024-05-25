/*
 * yerith-erp-9-0-system-daemon-periode.hpp
 *
 *      Author: PROF. DR.-ENG. DIPL.-INF. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_SYSTEM_DAEMON_PERIOD_TIME_HPP_
#define YERITH_ERP_3_0_SYSTEM_DAEMON_PERIOD_TIME_HPP_

#include "src/include/yerith-erp-9-0-system-daemon-alert-abstract-entity.hpp"


class YERITH_ERP_SYSTEM_DAEMON_LOGGER;


class YERITH_ERP_SYSTEM_DAEMON_ALERT_PERIOD_TIME:public
    YERITH_ERP_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY
{
Q_OBJECT public:
    YERITH_ERP_SYSTEM_DAEMON_ALERT_PERIOD_TIME(YERITH_ERP_SYSTEM_DAEMON_LOGGER
                                               * logger);

    ~YERITH_ERP_SYSTEM_DAEMON_ALERT_PERIOD_TIME();

public slots:
    void doChecks();

protected:

    virtual void process_courrier_alertes
    (const QString &TRIGGER_CONDITION,
     const _StockRecord__FOR_ALERT_QUANTITY &aStockQuantiteAlerteData);

};


#endif /* YERITH_ERP_3_0_SYSTEM_DAEMON_PERIOD_TIME_HPP_ */
