/*
 * yerith-erp-9-0-system-daemon-alert-abstract-entity.hpp
 *
 *      Author: PROF. DR.-ENG. DIPL.-INF. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY_HPP_
#define YERITH_ERP_3_0_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY_HPP_


#include "src/include/yerith-erp-9-0-system-daemon-abstract-entity.hpp"


#include "src/utils/yerith-erp-9-0-system-daemon-utils.hpp"


class _StockRecord__FOR_ALERT_QUANTITY;


class YERITH_ERP_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY :
		public YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY
{
	Q_OBJECT

public:

    YERITH_CLASS_OPERATORS

    inline YERITH_ERP_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY
			(YERITH_ERP_SYSTEM_DAEMON_LOGGER *aLogger)
    :YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY(aLogger)
    {
    }

    inline virtual ~YERITH_ERP_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY()
    {
    }

protected:

    virtual void checkAlertes(const _StockRecord__FOR_ALERT_QUANTITY &
                              aStockQuantiteAlerteData)
    {
        QDEBUG_STRING_OUTPUT_2("checkAlertes",
                               "PLEASE IMPLEMENT THIS VIRTUAL ABSTRACT METHOD !!!");
    }

    virtual void process_courrier_alertes(const QString &TRIGGER_CONDITION,
                                          const
                                          _StockRecord__FOR_ALERT_QUANTITY &
                                          aStockQuantiteAlerteData);
};


#endif /* YERITH_ERP_3_0_SYSTEM_DAEMON_ALERT_ABSTRACT_ENTITY_HPP_ */
