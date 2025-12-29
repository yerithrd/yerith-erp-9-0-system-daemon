/*
 * yerith-erp-9-0-system-daemon-entity-Pay_Group.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: yerith-xavier
 */

#include "src/entities/yerith-erp-9-0-system-daemon-entity-Pay_Group.hpp"


#include "src/entities/yerith-erp-9-0-system-daemon-entity-Employe.hpp"



double _PayGroup::apply_an_Employee_PAYMENT(_Employee *anEmployee)
{
    if (0 == anEmployee)
    {
        return 0.0;
    }


    double montly_amount_real = monthly_amount * montly_taxes;


    anEmployee->groupe_dun_employe__TO__payments
        .insert(_designation,
                 montly_amount_real);


    return montly_amount_real;
}


