/*
 * yerith-erp-9-0-system-daemon-entity-Employe.hpp
 *
 *  Created on: Dec 28, 2020
 *      Author: yerith-xavier
 */

#ifndef SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_EMPLOYEE_HPP_
#define SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_EMPLOYEE_HPP_


#include "src/include/yerith-erp-9-0-definition-oo-class-operators.hpp"


#include <QtCore/QString>


class _Employee
{
public:

    YERITH_CLASS_OPERATORS


    double get_salary_for_today();

    void set__Employee_GROUP(QString groupe_dun_employe);



    QString _nom_entreprise;

    QMap<QString, double> groupe_dun_employe__TO__payments;

    QList<QString> _groupe_dun_employe__LIST;


private:

    /* Original encoded string before spliting onto
     * a list of groups of employees.
     */
    QString _groupe_dun_employe;
};


#endif //SRC_YERITH_ERP_3_0_SYSTEM_DAEMON_ENTITY_EMPLOYEE_HPP_
