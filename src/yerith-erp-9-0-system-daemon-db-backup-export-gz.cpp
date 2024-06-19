/*
 * yerith-erp-9-0-system-daemon-db-backup-export-gz.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yerith-erp-9-0-system-daemon-db-backup-export-gz.hpp"


#include "yerith-erp-9-0-system-daemon-config.hpp"


YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ::YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ()
:YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY()
{
    _alertesTimer = new QTimer(this);

    connect(_alertesTimer, SIGNAL(timeout()), this, SLOT(do_backups()));

    //ALERT_QUANTITY_TIME_INTERVAL
    QString strQuery("SELECT valeur_configuration FROM configurations");

    strQuery.append(" WHERE nom_configuration = 'BACKUP_DATABASE_YERITH_ERP_3_TIME_INTERVAL'");

    QSqlQuery query;

    QSqlRecord aConfigurationRecord;

    int querySize = YerothERPAlertUtils::execQuery(query, strQuery);


	_dbusServer->YRI_slot_refresh_SELECT_DB_MYSQL__CALLED
					(QString("%1;%2;%3")
						.arg("configurations.BACKUP_DATABASE_YERITH_ERP_3_TIME_INTERVAL",
							 "yerith-erp-9-0-system-daemon-db-backup-export-gz.cpp",
							 QString::number(29)));


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
                 "database yerith_erp_3 backup into a *.gz file: "
                 << query.lastError();
    }


    {
        QString strQuery_YERITH_ERP_3_0_BACKUP_RESTORE_FOLDER
						("SELECT valeur_configuration FROM configurations");

        strQuery_YERITH_ERP_3_0_BACKUP_RESTORE_FOLDER
			.append(" WHERE nom_configuration = 'DIRECTORY_FULL_PATH_FOR_BACKUP_DATABASE_YERITH_ERP_3'");

        query.clear();

        querySize =
        		YerothERPAlertUtils::execQuery(query,
                                               strQuery_YERITH_ERP_3_0_BACKUP_RESTORE_FOLDER);


    	_dbusServer->YRI_slot_refresh_SELECT_DB_MYSQL__CALLED
    					(QString("%1;%2;%3")
    						.arg("configurations.DIRECTORY_FULL_PATH_FOR_BACKUP_DATABASE_YERITH_ERP_3",
    							 "yerith-erp-9-0-system-daemon-db-backup-export-gz.cpp",
    							 QString::number(72)));


        success = (querySize > 0);

        if (success)
        {
            if (query.next())
            {
                aConfigurationRecord.clear();

                aConfigurationRecord = query.record();

                _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY =
                                GET_SQL_RECORD_DATA(aConfigurationRecord,
                                                    "valeur_configuration");

//                              QDEBUG_STRING_OUTPUT_2("_YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY *",
//                                              _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY);
            }
        }
        else
        {
            qDebug() << "\t\t[reason for failing] couldn't read "
                     "yerith_erp_3 database backup directory: " << query.lastError();
        }
    }


    {
        QString strQuery_YERITH_ERP_3_0_BINARY("SELECT valeur_configuration FROM configurations");

        strQuery_YERITH_ERP_3_0_BINARY
			.append(" WHERE nom_configuration = 'YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE'");

        query.clear();

        querySize = YerothERPAlertUtils::execQuery(query, strQuery_YERITH_ERP_3_0_BINARY);


    	_dbusServer->YRI_slot_refresh_SELECT_DB_MYSQL__CALLED
    					(QString("%1;%2;%3")
    						.arg("configurations.YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE",
    							 "yerith-erp-9-0-system-daemon-db-backup-export-gz.cpp",
    							 QString::number(117)));


        success = (querySize > 0);

        if (success)
        {
            if (query.next())
            {
                aConfigurationRecord.clear();

                aConfigurationRecord = query.record();

                _YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE =
                                GET_SQL_RECORD_DATA(aConfigurationRecord,
                                                    "valeur_configuration");

//                              QDEBUG_STRING_OUTPUT_2("_YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE *",
//                                              _YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE);
            }
        }
        else
        {
            qDebug() << "\t\t[reason for failing] couldn't read "
                     "yerith_erp_3 binary for database backup restore: "
                     << query.lastError();
        }
    }


    do_backups();

    //do_backups() is called every _alertesTimeIntervall ms
    _alertesTimer->start(_alertesTimeIntervall);
}


void YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ::do_backups()
{
//      QDEBUG_STRING_OUTPUT_2("YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ ****",
//                      _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY);

    if (_YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY.isEmpty())
    {
        _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY =
                        QString("%1/%2").
                        arg(YerenConfig::YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER,
                            "YERITH_sql_backup");
    }

    YerothERPAlertUtils::
    YERITH_CREATE_FOLDER(_YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY);


//      QDEBUG_STRING_OUTPUT_2("_YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY ***",
//                      _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY );

    QStringList progArguments;

    progArguments << "--version";

    QString YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID;


//              QDEBUG_STRING_OUTPUT_2("_YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE",
//                                                          _YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE);

    int yerith_erp_3_0_standalone_LAST_BUILD_ID_STRING_SIZE =
                    YerothERPAlertUtils::start_PROCESS_AND_GET_PROCESS_output_AS_QSTRING
                    (_YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE,
                     progArguments,
                     YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID);


//      QDEBUG_STRING_OUTPUT_2("YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID",
//                                                      YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID);


    QString mysqlProcessProgram("/usr/bin/mysqldump");

    progArguments.clear();

    progArguments << "--databases"
                  << YerenConfig::_db_name
                  << "-u"
                  << YerenConfig::_db_user_name
                  << QString("-p%1").arg(YerenConfig::_db_user_pwd);


    QString yerith_erp_3_0_restore_backup_sql_file(QString("%1.sql").
                                                   arg
                                                   (FILE_NAME_WITH_CURRENT_DATE_AND_TIME
                                                    ("yerith_erp_3_0_SYSTEM_DAEMON_BACKUP")));


//      QDEBUG_STRING_OUTPUT_2_N("yerith_erp_3_0_standalone_LAST_BUILD_ID_STRING_SIZE",
//                                                        yerith_erp_3_0_standalone_LAST_BUILD_ID_STRING_SIZE);


    if (YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID.size() > 0)
    {
        yerith_erp_3_0_restore_backup_sql_file.prepend(QString("%1-").
                                                       arg
                                                       (YERITH_ERP_3_0_STANDALONE_VERSION_LAST_BUILD_ID));
    }


//      QDEBUG_STRING_OUTPUT_QSTRINGLIST("progArguments", progArguments);

    int output_file_size =
                    YerothERPAlertUtils::start_PROCESS_AND_READ_PROCESS_output_INTO_FILE
                    (mysqlProcessProgram,
                     _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY,
                     yerith_erp_3_0_restore_backup_sql_file,
                     progArguments);

//      QDEBUG_STRING_OUTPUT_2_N("output_file_size", output_file_size);

    if (output_file_size >= 0)
    {
        YerothERPAlertUtils::
        GZIP_YERITH_FILE(_YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY,
                         QString("%1/%2").
                         arg(_YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY,
                             yerith_erp_3_0_restore_backup_sql_file));
    }

}
