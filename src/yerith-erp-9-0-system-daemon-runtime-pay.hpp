/*
 * yerith-erp-9-0-system-daemon-runtime-pay.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP_
#define YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP_


#include "entities/yerith-erp-9-0-system-daemon-entity-Employe.hpp"

#include "src/include/yerith-erp-9-0-system-daemon-abstract-entity.hpp"


class YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP : public YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY
{
    Q_OBJECT

public:

        YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP();

        inline ~YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP()
        {
        }

public slots:

    void do_payments_to_employee();


protected:

    void naviguer___SUR__TOUS___DES___groupes_demployes();

    void naviguer___SUR__TOUS___DES___employes();


    QString _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT;


public:

    QSet<QString> groupe_de_payes;

    QSet<_Employee *> set_of_employee;

    QMap<QString, QString> _groupe_demploye__TO__groupe_de_paye;

    QMap<QString, QString> _nom_emtreprise__TO__groupe_demploye;

};

#endif /* YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP_ */
