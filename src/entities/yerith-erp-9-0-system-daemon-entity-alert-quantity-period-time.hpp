/*
 * yerith-erp-9-0-system-daemon-entity-alert-quantity.hpp
 *
 *  Created on: Dec 28, 2020
 *      Author: yerith-xavier
 */

#ifndef SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_ALERT_QUANTITY_HPP_
#define SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_ALERT_QUANTITY_HPP_


#include "src/include/yerith-erp-9-0-definition-oo-class-operators.hpp"


#include <QtCore/QString>


class _StockRecord__FOR_ALERT_QUANTITY
{
public:

    YERITH_CLASS_OPERATORS int _notifications;

    double _quantite;

    bool _alerte_resolue;

    QDate _date_debut;

    QDate _date_fin;

    QString _designation;

    QString _destinataire;

    QString _nom_complet_destinataire;

    QString _designation_alerte;

    QString _message_alerte;

    QString _condition_alerte;

    QString _id_alerte;

    QString _stockDesignation;
};

#endif /* SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_ALERT_QUANTITY_HPP_ */
