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


    naviguer___SUR__TOUS___DES___employes();

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


void YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::naviguer___SUR__TOUS___DES___employes()
{
    QString query = QString("SELECT %1, %2 FROM %3 WHERE %4 = '1'")
                        .arg(YerothDatabaseTableColumn::NOM_ENTREPRISE,
                             YerothDatabaseTableColumn::GROUPES_DUN_EMPLOYE,
                             YerothERPDatabase::FOURNISSEURS,
                             YerothDatabaseTableColumn::DESIGNATION,
                             YerothDatabaseTableColumn::EMPLOYE);

    _Employee *an_employee_RECORD = 0;

    QSqlRecord a_qsql_record;

    QSqlQuery a_sql_query;


    int querySize = YerothERPAlertUtils::execQuery(a_sql_query,
                                                   query);

    if (querySize > 0)
    {
        while (a_sql_query.next())
        {
            a_qsql_record.clear();

            a_qsql_record = a_sql_query.record();

            an_employee_RECORD = new _Employee;

            an_employee_RECORD->_groupe_dun_employe_paye =
                            GET_SQL_RECORD_DATA(a_qsql_record,
                                                YerothDatabaseTableColumn::GROUPES_DUN_EMPLOYE);

            QDEBUG_STRING_OUTPUT_2("an_employee_RECORD->_groupe_dun_employe_paye ",
                                    an_employee_RECORD->_groupe_dun_employe_paye);
        }
    }
}


void YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP::do_payments_to_employee()
{
//      QDEBUG_STRING_OUTPUT_2("YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ ****",
//                      _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY);

    if (_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT.isEmpty())
    {
        _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT =
                        QString("%1/%2").
                        arg(YerenConfig::YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER,
                            "YERITH_pdf_payment_folder");
    }

    YerothERPAlertUtils::YERITH_CREATE_FOLDER(_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT);


      QDEBUG_STRING_OUTPUT_2("_DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT ***",
                      _DIRECTORY_FULL_PATH_FOLDER_FOR_SUPPLIER_PAYMENT );

//    QStringList progArguments;
//
//    progArguments << "--version";
//
//    QString YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID;


}
