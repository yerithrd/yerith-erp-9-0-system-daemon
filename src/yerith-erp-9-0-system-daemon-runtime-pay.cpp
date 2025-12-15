/*
 * yerith-erp-9-0-system-daemon-runtime-pay.hpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-9-0-system-daemon-runtime-pay.hpp"

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

    strQuery.append(" WHERE nom_configuration = 'PAY_SUPPLIER_HUMAN_RESOURCE_YERITH_ERP_3_TIME_INTERVAL'");

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

                              QDEBUG_STRING_OUTPUT_2("_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT *",
                                                      _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT);
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


//void Enregistrer___TOUS__LES___Membres_Du_Groupe_Paye(QString groupe_de_paye)
//{
//    QString groupe_de_paye_TRIMMED = groupe_de_paye.trimmed();
//
//    if (groupe_de_paye_TRIMMED.isEmpty())
//    {
//        return ;
//    }
//
//    QString query = QString("SELECT %1 FROM %2 WHERE %3 = %4")
//                        .arg(YerithDatabaseTableColumn::MEMBRES_DU_GROUPE_db_ID,
//                             YerithDatabase::GROUPES_DEMPLOYES_hr
//                             YerithDatabaseTableColumn::DESIGNATION,
//                             groupe_de_paye_TRIMMED,
//                             );
//
//
//    QSqlQuery a_sql_query;
//
//    querySize = YerothERPAlertUtils::execQuery(a_sql_query,
//                                               query);
//
//    if (querySize)
//    {
//
//    }
//}


 void YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::naviguer___SUR__TOUS___DES___groupes_demployes()
{
    QList<QString> Current_groupe__dun_employe__LIST;


    QString groupe_de_paie_hr;

    QSqlRecord a_qsql_record;

    QSqlQuery a_sql_query;

    int querySize = 0;


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
//                        QDEBUG_STRING_OUTPUT_2("a group of pay", groupe_de_paie_hr);
                        groupe_de_payes.insert(groupe_de_paie_hr);
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

            set_of_employee.insert(an_employee_RECORD);
        }
    }
}


void YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::do_payments_to_employee()
{
//      QDEBUG_STRING_OUTPUT_2("YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ ****",
//                      _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY);

    naviguer___SUR__TOUS___DES___employes();

    naviguer___SUR__TOUS___DES___groupes_demployes();


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
