/*
 * yerith-erp-9-0-system-daemon-daemon-quantite.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_SYSTEM_DAEMON_QUANTITE_HPP_
#define YERITH_ERP_3_0_SYSTEM_DAEMON_QUANTITE_HPP_

#include "src/include/yerith-erp-9-0-system-daemon-alert-abstract-entity.hpp"

#include "src/include/yerith-erp-9-0-software-text-configuration.hpp"


class _StockRecord__FOR_ALERT_QUANTITY;

class YERITH_ERP_SYSTEM_DAEMON_LOGGER;


class YERITH_ERP_SYSTEM_DAEMON_ALERT_OVER_STOCK_QUANTITY :
		public YERITH_ERP_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

	YERITH_ERP_SYSTEM_DAEMON_ALERT_OVER_STOCK_QUANTITY(YERITH_ERP_SYSTEM_DAEMON_LOGGER *logger);

    inline ~YERITH_ERP_SYSTEM_DAEMON_ALERT_OVER_STOCK_QUANTITY()
    {
        delete _alertesTimer;
    }

public slots:

    void doChecks();

protected:

    virtual void checkAlertes(const _StockRecord__FOR_ALERT_QUANTITY &
                              aStockQuantiteAlerteData);

    virtual void process_courrier_alertes
					(const QString &TRIGGER_CONDITION,
					 const _StockRecord__FOR_ALERT_QUANTITY &aStockQuantiteAlerteData);
};


#endif /* YERITH_ERP_3_0_SYSTEM_DAEMON_QUANTITE_HPP_ */
