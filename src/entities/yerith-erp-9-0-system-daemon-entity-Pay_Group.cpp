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

    double montly_amount_real = monthly_amount - (monthly_amount * montly_taxes / 100.0);


    if (! anEmployee->groupe_dun_employe__TO__payments.contains(_designation))
    {
        anEmployee->groupe_dun_employe__TO__payments
                        .insert(_designation,
                                montly_amount_real);
    }
    else
    {
        double previous_value = anEmployee->groupe_dun_employe__TO__payments.value(_designation);
        double new_value = previous_value + montly_amount_real;

        anEmployee->groupe_dun_employe__TO__payments
                        .insert(_designation,
                                new_value);
    }


    return montly_amount_real;
}


