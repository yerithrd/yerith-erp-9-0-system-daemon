/*
 * yerith-erp-9-0-system-daemon-entity-Employe.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: yerith-xavier
 */


#include "src/entities/yerith-erp-9-0-system-daemon-entity-Employe.hpp"


#include "src/utils/yerith-erp-9-0-system-daemon-utils.hpp"


double _Employee::get_salary_for_today()
{
    double employee_Salary = 0.0;

    QDEBUG_STRING_OUTPUT_2_N("groupe_dun_employe__TO__payments.size()",
                              groupe_dun_employe__TO__payments.size());

    QMapIterator<QString, double> it(groupe_dun_employe__TO__payments);

    while (it.hasNext())
    {
        it.next();

        employee_Salary += it.value();
    }

    return employee_Salary;
}


void _Employee::set__Employee_GROUP(QString groupes_dun_employe)
{
    _groupe_dun_employe = groupes_dun_employe;


    QString a___groupes_dun_employe = _groupe_dun_employe;

    _groupe_dun_employe__LIST = a___groupes_dun_employe.split("*", Qt::SkipEmptyParts);
}
