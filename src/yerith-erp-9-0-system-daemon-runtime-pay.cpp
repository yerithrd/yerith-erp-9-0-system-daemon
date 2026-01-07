/*
 * yerith-erp-9-0-system-daemon-runtime-pay.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-9-0-system-daemon-runtime-pay.hpp"

#include "entities/yerith-erp-9-0-system-daemon-entity-Pay_Group.hpp"

#include "entities/yerith-erp-9-0-system-daemon-entity-Employe.hpp"

#include "yerith-erp-9-0-system-daemon-config.hpp"

#include "yerith-erp-9-0-system-daemon-database.hpp"

#include "utils/yerith-erp-database-table-column.hpp"



YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP()
:YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY()
{
    _alertesTimer = new QTimer(this);

    connect(_alertesTimer, SIGNAL(timeout()), this, SLOT(do_payments_to_employee()));

    //ALERT_QUANTITY_TIME_INTERVAL
    QString strQuery("SELECT valeur_configuration FROM configurations");

    strQuery.append(" WHERE nom_configuration = 'HUMAN_RESOURCE_PAY_YERITH_ERP_3_TIME_INTERVAL'");

    QSqlQuery query;

    QSqlRecord aConfigurationRecord;

    int querySize = YerothERPAlertUtils::execQuery(query, strQuery);


	_dbusServer->YRI_slot_refresh_SELECT_DB_MYSQL__CALLED
					(QString("%1;%2;%3")
						.arg("configurations.PAY_SUPPLIER_HUMAN_RESOURCE_YERITH_ERP_3_TIME_INTERVAL",
							 "yerith-erp-9-0-system-daemon-runtime-pay.cpp",
							 QString::number(32)));

    bool success = (querySize > 0);

    if (success)
    {
        if (query.next())
        {
            aConfigurationRecord = query.record();

            _alertesTimeIntervall = 1000 *
                                    GET_SQL_RECORD_DATA(aConfigurationRecord,
                                                        "valeur_configuration").toInt();
            //qDebug() << "_alertesTimeIntervall: " << _alertesTimeIntervall;
        }
    }
    else
    {
        qDebug() << "\t\t[reason for failing] couldn't read "
                 "yerith_erp_3 time interval for performing "
                 "database yerith_erp_3 query for HR payments: "
                 << query.lastError();
    }


    {
        QString strQuery_YERITH_ERP_3_0_FOLDER_FOR_SUPPLIER_PAYMENT
						("SELECT valeur_configuration FROM configurations");

        strQuery_YERITH_ERP_3_0_FOLDER_FOR_SUPPLIER_PAYMENT
			.append(" WHERE nom_configuration = 'DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT_YERITH_ERP_3'");

        query.clear();

        querySize =
        		YerothERPAlertUtils::execQuery(query,
                                               strQuery_YERITH_ERP_3_0_FOLDER_FOR_SUPPLIER_PAYMENT);


    	_dbusServer->YRI_slot_refresh_SELECT_DB_MYSQL__CALLED
    					(QString("%1;%2;%3")
    						.arg("configurations.DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT_YERITH_ERP_3",
    							 "yerith-erp-9-0-system-daemon-RUNTIME-pay.cpp",
    							 QString::number(75)));


        success = (querySize > 0);

        if (success)
        {
            if (query.next())
            {
                aConfigurationRecord.clear();

                aConfigurationRecord = query.record();

                _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT =
                                GET_SQL_RECORD_DATA(aConfigurationRecord,
                                                    "valeur_configuration");

//                QDEBUG_STRING_OUTPUT_2("_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT *",
//                                        _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT);
            }
        }
        else
        {
            qDebug() << "\t\t[reason for failing] couldn't read "
                        "yerith_erp_3 HR payment folder " << query.lastError();
        }
    }


    do_payments_to_employee();

    //do_backups() is called every _alertesTimeIntervall ms
    _alertesTimer->start(_alertesTimeIntervall);
}


_PayGroup * YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::create_a_pay_group(QString a_pay_group_name)
{
    QSqlRecord a_pay_group_qsql_record;

    QSqlQuery a_pay_group_sql_query;

    int querySize = 0;

    _PayGroup *new_pay_group = 0;

    QString pay_group_sql_stmt = QString("SELECT * FROM %1 WHERE %2 = '%3' AND %4 = '%5';")
                                    .arg(YerothERPDatabase::GROUPES_DE_PAIE_hr,
                                         YerothDatabaseTableColumn::JOUR_DE_PAIE_DU_MOIS,
                                         QString::number(GET_CURRENT_DATE.day()),
                                         YerothDatabaseTableColumn::DESIGNATION,
                                         a_pay_group_name);

    a_pay_group_sql_query.clear();

    querySize = YerothERPAlertUtils::execQuery(a_pay_group_sql_query,
                                               pay_group_sql_stmt);

    if (querySize > 0)
    {
        if (a_pay_group_sql_query.next())
        {
            a_pay_group_qsql_record.clear();

            a_pay_group_qsql_record = a_pay_group_sql_query.record();

            new_pay_group = new _PayGroup;


            new_pay_group->montly_pay_date =
                    GET_SQL_RECORD_DATA(a_pay_group_qsql_record,
                                        YerothDatabaseTableColumn::JOUR_DE_PAIE_DU_MOIS).toUInt();

            new_pay_group->authorized_site =
                    GET_SQL_RECORD_DATA(a_pay_group_qsql_record,
                                        YerothDatabaseTableColumn::LOCALISATION);

            new_pay_group->montly_taxes =
                    GET_SQL_RECORD_DATA(a_pay_group_qsql_record,
                                        YerothDatabaseTableColumn::POURCENTAGE_TAXES_IMPOSABLES).toDouble();

            new_pay_group->monthly_amount =
                    GET_SQL_RECORD_DATA(a_pay_group_qsql_record,
                                        YerothDatabaseTableColumn::MONTANT_A_PAYER_MENSUEL).toDouble();

//            QDEBUG_STRING_OUTPUT_2_N("new_pay_group->montly_taxes",
//                                      new_pay_group->montly_taxes);
//
//            QDEBUG_STRING_OUTPUT_2_N("new_pay_group->monthly_amount",
//                                      new_pay_group->monthly_amount);
        }
    }

    return new_pay_group;
}


double YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::calculer___salaire__DES___Employes()
{
    bool retValue = false;


    _Employee *an_Employee = 0;

    QSetIterator<_Employee *> an_Employee_iterator(set_of_employee);

    QDEBUG_STRING_OUTPUT_2_N("NUMBER OF EMPLOYEES",
                              set_of_employee.size());


    _PayGroup *a_pay_group = 0;

    QString a_salary_group;

    QString a_group_of_employee;


    double payment_amount = 0.0;


    int k_Max = 0;


    while (an_Employee_iterator.hasNext())
    {
        an_Employee = an_Employee_iterator.next();

        if (0 != an_Employee)
        {
            k_Max = an_Employee->_groupe_dun_employe__LIST.size();

            for (int k = 0; k < k_Max; ++k)
            {
                a_group_of_employee = an_Employee->_groupe_dun_employe__LIST.at(k);

                a_salary_group = _groupe_demploye__TO__groupe_de_paye.value(a_group_of_employee);

                if (! paygroupname__TO__paygroupInstance.contains(a_salary_group))
                {
                    a_pay_group = create_a_pay_group(a_salary_group);

                    paygroupname__TO__paygroupInstance.insert(a_salary_group, a_pay_group);
                }
                else
                {
                    a_pay_group = paygroupname__TO__paygroupInstance.value(a_salary_group);
                }

                if (0 != a_pay_group)
                {
                    //Now calculate salary of an employee with taxes included
                    payment_amount = a_pay_group->apply_an_Employee_PAYMENT(an_Employee);

                    retValue = true;
                }
            }
        }
    }

    return retValue;
}


 void YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::naviguer___SUR__TOUS___DES___groupes_demployes()
{
    QList<QString> Current_groupe__dun_employe__LIST;


    QString groupe_de_paie_hr;

    QSqlRecord a_qsql_record;

    QSqlQuery a_sql_query;

    int querySize = 0;


    QString a_group_of_employee;

    _Employee *an_employee = 0;

    QSetIterator<_Employee *> an_employee_iterator(set_of_employee);

    while (an_employee_iterator.hasNext())
    {
       an_employee = an_employee_iterator.next();

        if (0 == an_employee)
        {
            continue;
        }

//        QDEBUG_STRING_OUTPUT_2("an_employee", an_employee->_nom_entreprise);

        Current_groupe__dun_employe__LIST = an_employee->_groupe_dun_employe__LIST;

        for (uint k = 0; k < Current_groupe__dun_employe__LIST.size(); ++k)
        {
            a_sql_query.clear();

            QString queryStr = QString("SELECT %1 FROM %2 WHERE %3 = '%4'")
                                .arg(YerothDatabaseTableColumn::GROUPE_DE_PAIE_HR,
                                     YerothERPDatabase::GROUPES_DEMPLOYES_hr,
                                     YerothDatabaseTableColumn::DESIGNATION,
                                     Current_groupe__dun_employe__LIST.at(k).trimmed());


            querySize = YerothERPAlertUtils::execQuery(a_sql_query,
                                                       queryStr);

            if (querySize > 0)
            {
                while (a_sql_query.next())
                {
                    a_qsql_record.clear();

                    a_qsql_record = a_sql_query.record();

                    groupe_de_paie_hr =
                    GET_SQL_RECORD_DATA(a_qsql_record,
                                        YerothDatabaseTableColumn::GROUPE_DE_PAIE_HR);

                    if (! groupe_de_paie_hr.isEmpty())
                    {
                        _groupe_demploye__TO__groupe_de_paye
                            .insert(Current_groupe__dun_employe__LIST.at(k).trimmed(),
                                    groupe_de_paie_hr);
//
                        a_group_of_employee = Current_groupe__dun_employe__LIST.at(k).trimmed();

//                        QDEBUG_STRING_OUTPUT_2("a group of pay", groupe_de_paie_hr);
//                        groupe_de_payes.insert(groupe_de_paie_hr);
                    }
                }
            }
        }
    }

 }


void YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::naviguer___SUR__TOUS___DES___employes()
{
    QString query = QString("SELECT %1, %2 FROM %3 WHERE %4 = '1'")
                        .arg(YerothDatabaseTableColumn::NOM_ENTREPRISE,
                             YerothDatabaseTableColumn::GROUPES_DUN_EMPLOYE,
                             YerothERPDatabase::FOURNISSEURS,
                             YerothDatabaseTableColumn::EMPLOYE);

    _Employee *an_employee_RECORD = 0;

    QSqlRecord a_qsql_record;

    QSqlQuery a_sql_query;


    int querySize = YerothERPAlertUtils::execQuery(a_sql_query,
                                                   query);

//    QDEBUG_STRING_OUTPUT_2_N("querySize", querySize);

    if (querySize > 0)
    {
        while (a_sql_query.next())
        {
            a_qsql_record.clear();

            a_qsql_record = a_sql_query.record();

            an_employee_RECORD = new _Employee;


            an_employee_RECORD->_nom_entreprise =
                            GET_SQL_RECORD_DATA(a_qsql_record,
                                                YerothDatabaseTableColumn::NOM_ENTREPRISE);

            QString Employe_Group =
                            GET_SQL_RECORD_DATA(a_qsql_record,
                                                YerothDatabaseTableColumn::GROUPES_DUN_EMPLOYE);

            an_employee_RECORD->set__Employee_GROUP(Employe_Group);

            _nom_emtreprise__TO__groupe_demploye
                .insert(an_employee_RECORD->_nom_entreprise,
                        Employe_Group);

            if (check___validity__OF_EMPLOYEE_Group_Appartenance(an_employee_RECORD))
            {
                set_of_employee.insert(an_employee_RECORD);
            }
        }
    }
}


bool YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::
        check___validity__OF_EMPLOYEE_Group_Appartenance(_Employee *an_employee_RECORD)
{
    bool authorized_payment = false;

    if (0 == an_employee_RECORD)
    {
        return authorized_payment;
    }

//    QDEBUG_STRING_OUTPUT_2("GET_CURRENT_STRING_DATE",
//                            GET_CURRENT_STRING_DATE);

    QString query = QString("SELECT id FROM %1 WHERE %2 = '%3' AND %4 <= '%5' AND '%6' <= %7")
                        .arg(YerothERPDatabase::PERIODES_DAPPARTENANCE_GROUPES_DE_PAIE_HR,
                             YerothDatabaseTableColumn::NOM_ENTREPRISE,
                             an_employee_RECORD->_nom_entreprise,
                             YerothDatabaseTableColumn::DATE_DE_DEBUT_DAPPARTENANCE,
                             DATE_TO_DB_FORMAT_STRING(GET_CURRENT_DATE),
                             DATE_TO_DB_FORMAT_STRING(GET_CURRENT_DATE),
                             YerothDatabaseTableColumn::DATE_DE_FIN_DAPPARTENANCE);

//    QDEBUG_STRING_OUTPUT_2("query",
//                            query);

    QSqlQuery a_sql_query;

    int querySize = YerothERPAlertUtils::execQuery(a_sql_query,
                                                   query);

    QDEBUG_STRING_OUTPUT_2_N("querySize",
                              querySize);

    if (querySize > 0)
    {
        authorized_payment = true;
    }

    return authorized_payment;
}


void YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::do_payments_to_employee()
{
//      QDEBUG_STRING_OUTPUT_2("YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ ****",
//                      _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY);

    naviguer___SUR__TOUS___DES___employes();

    naviguer___SUR__TOUS___DES___groupes_demployes();

    calculer___salaire__DES___Employes();



    double anEmployeeSalary = 0.0;


    _Employee *an_Employee = 0;

    QSetIterator<_Employee *> an_Employee_iterator(set_of_employee);

    while (an_Employee_iterator.hasNext())
    {
        anEmployeeSalary = 0.0;

        an_Employee = an_Employee_iterator.next();

        if (0 != an_Employee)
        {
            anEmployeeSalary += an_Employee->get_salary_for_today();
        }
    }




    if (_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT.isEmpty())
    {
        _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT =
                        QString("%1/%2").
                        arg(YerenConfig::YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER,
                            "YERITH_pdf_payment_folder");
    }

    YerothERPAlertUtils::YERITH_CREATE_FOLDER(_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT);


//      QDEBUG_STRING_OUTPUT_2("_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT ***",
//                      _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT );

//    QStringList progArguments;
//
//    progArguments << "--version";
//
//    QString YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID;


}
