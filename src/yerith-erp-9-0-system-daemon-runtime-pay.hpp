/*
 * yerith-erp-9-0-system-daemon-runtime-pay.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP_
#define YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP_


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

    void naviguer___SUR__TOUS___DES___employes();


    QString _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT;


public:

    QMap<QString, QString> _nom_emtreprise__TO__groupe_demploye;


};

#endif /* YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP_ */
