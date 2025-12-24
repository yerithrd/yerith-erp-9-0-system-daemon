/*
 * yerith-erp-9-0-system-daemon-entity-Pay_Group.hpp
 *
 *  Created on: Dec 28, 2020
 *      Author: yerith-xavier
 */

#ifndef SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_PAY_Group_HPP_
#define SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_PAY_Group_HPP_


#include "src/include/yerith-erp-9-0-definition-oo-class-operators.hpp"


#include <QtCore/QString>


class _PayGroup
{
public:

    YERITH_CLASS_OPERATORS

    double monthly_amount;

    double montly_taxes;

    QString authorized_site;

    QString _designation;

    uint montly_pay_date;
};


#endif //SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_PAY_Group_HPP_
