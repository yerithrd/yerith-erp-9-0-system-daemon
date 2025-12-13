/*
 * yerith-erp-9-0-system-daemon-entity-Employe.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: yerith-xavier
 */


#include "src/entities/yerith-erp-9-0-system-daemon-entity-Employe.hpp"



void _Employee::set__Employee_GROUP(QString groupes_dun_employe)
{
    _groupe_dun_employe = groupes_dun_employe;


    QString a___groupes_dun_employe = _groupe_dun_employe;

    _groupe_dun_employe__LIST = a___groupes_dun_employe.split("*", Qt::SkipEmptyParts);
}
