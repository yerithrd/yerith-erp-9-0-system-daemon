/*
 * yerith-erp-9-0-system-daemon.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */


#include "yerith-erp-9-0-system-daemon-runtime-pay.hpp"

#include "yerith-erp-9-0-system-daemon-db-backup-export-gz.hpp"

#include "yerith-erp-9-0-system-daemon-periode.hpp"

#include "yerith-erp-9-0-system-daemon-quantite.hpp"

#include "yerith-erp-9-0-system-daemon-config.hpp"

#include "yerith-erp-9-0-system-daemon-database.hpp"

#include "yerith-erp-9-0-system-daemon-logger.hpp"

#include "src/utils/yerith-erp-9-0-system-daemon-utils.hpp"


#include <QtCore/QList>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QCryptographicHash>

#include <QtNetwork/QNetworkInterface>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

#include <unistd.h>



const QString SQLITE("SQLite");
const QString MYSQL("MySQL");
const QString MSSQL("MSSQL");
const QString ORACLE("Oracle");


class YERITH_ERP_SYSTEM_DAEMON_ALERT_PERIOD_TIME;

QString text_init_cfg("");

class YerothERPAlertMain
{
public:

    inline YerothERPAlertMain(YERITH_ERP_SYSTEM_DAEMON_LOGGER *logger)
    {
        _logger = logger;
    }

    inline ~ YerothERPAlertMain()
    {
    }

private:

    YERITH_ERP_SYSTEM_DAEMON_LOGGER *_logger;
};


int main(int argc, char *argv[])
{
    qDebug() <<
             "yerith-erp-9-0-system-daemon | yerith-erp-9-0-system-daemon.cpp | main. started"
             << "\n";

    //sleep(30);

    QApplication app(argc, argv);

    YerenConfig::YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER =
                    QString(std::getenv("YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER")).
                    trimmed();

    YerenConfig::YERITH_ERP_3_0_SYSTEM_DAEMON_HOME_FOLDER =
                    QString(std::getenv("YERITH_ERP_3_0_SYSTEM_DAEMON_HOME_FOLDER")).
                    trimmed();

    YerenConfig::YERITH_ERP_3_0_HOME_FOLDER =
                    QString(std::getenv("YERITH_ERP_3_0_HOME_FOLDER")).trimmed();


    qDebug() <<
             "yerith-erp-9-0-system-daemon.cpp | main | YERITH-PGI-9.0 HOME FOLDER: "
             << YerenConfig::YERITH_ERP_3_0_HOME_FOLDER;


    if (YerenConfig::YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER.isEmpty())
    {
        QString errMsg
			("La variable d'environement YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER n'a pas de valeur ! \n\n");

        errMsg.append("Contacter Pr. Prof. Dr.-Ing. Xavier Noundou\n"
        			  "\t(YERITH.xavier@gmail.com)\n\n"
        			  "Cliquer sur 'Cancel' pour terminer yerith-erp-9-0-system-daemon-3.0");

        QDEBUG_STRING_OUTPUT_2("yerith-erp-9-0-system-daemon", errMsg);

        exit(1);
    }


    if (YerenConfig::YERITH_ERP_3_0_SYSTEM_DAEMON_HOME_FOLDER.isEmpty())
    {
        QString errMsg
        	("La variable d'environement YERITH_ERP_3_0_SYSTEM_DAEMON_HOME_FOLDER n'a pas de valeur ! \n\n");

        errMsg.append("Contacter Pr. Prof. Dr.-Ing. Xavier Noundou\n"
        			  "\t(YERITH.xavier@gmail.com)\n\n"
        			  "Cliquer sur 'Cancel' pour terminer yerith-erp-9-0-system-daemon-3.0");

        QDEBUG_STRING_OUTPUT_2("yerith-erp-9-0-system-daemon", errMsg);

        exit(1);
    }


    QString logFileName(YerenConfig::YERITH_ERP_3_0_SYSTEM_DAEMON_HOME_FOLDER);

    logFileName.append("/yerith-erp-9-0-system-daemon.log");


    QDEBUG_STRING_OUTPUT_2("yerith-erp-9-0-system-daemon.cpp | main | yerith-erp-9-0-system-daemon home folder",
    					   YerenConfig::YERITH_ERP_3_0_SYSTEM_DAEMON_HOME_FOLDER);


    YerothERPAlertUtils::setLogFileName(logFileName);


    QDEBUG_STRING_OUTPUT_2("yerith-erp-9-0-system-daemon.cpp | main | log file name",
    					   logFileName);


    YERITH_ERP_SYSTEM_DAEMON_LOGGER logger(YerothERPAlertUtils::getLogFileName());

    YerothERPAlertMain yerithERPAlertMain(&logger);

    QString initCfg(QString("%1/%2").
                    arg(YerenConfig::
                        YERITH_ERP_3_0_PROPERTIES_CONFIGURATION_FOLDER,
                        "yerith-erp-9-0.properties"));


    QDEBUG_STRING_OUTPUT_2("yerith-erp-9-0-system-daemon.cpp | main | yerith-erp-9-0.properties absolute file path",
    					   initCfg);


    YerenConfig::initYerenConfig(initCfg);

    YerothERPDatabase database(YerenConfig::_db_type);

    //qDebug() << "++ database.toString(): " << database.toString();

    text_init_cfg.append(database.db_type());

    /*
     * Only the 'client' version of yeren can be configured
     * to use a remote database.
     */
#ifndef YERITH_CLIENT
    //YERITH_SERVER, YERITH_STANDALONE, YERITH_ACADEMIC_EVALUATION_VERSION
    if (!YerothERPAlertUtils::
    			isEqualCaseInsensitive(database.db_ip_address(),
                                       YerothERPAlertUtils::LOCALHOST_IP_ADDRESS) &&
        !YerothERPAlertUtils::
			isEqualCaseInsensitive(database.db_ip_address(),
                                   YerothERPAlertUtils::LOCALHOST))
    {
        //qDebug() << "++ database.toString(): " << database.toString();

        QString errMsg("Cette version de yerith-erp-9-0-system-daemon "
                       "ne peut pas se connecter");

        errMsg.append(QString(" à un serveur MYSQL externe (%1) !\n\n"
                              "Contacter Pr. Prof. Dr.-Ing. Xavier Noundou\n"
                              "\t(YERITH.xavier@gmail.com)\n\n"
                              "Cliquer sur 'Cancel' pour terminer YERITH-PGI-9.0").
                      arg(database.db_ip_address()));

        QDEBUG_STRING_OUTPUT_2("yerith-erp-9-0-system-daemon",
        					  FROM_UTF8_STRING(errMsg));

        exit(3);
    }
#endif

    if (!database.open())
    {
        QString errMsg(QObject::
                       trUtf8("La connection de yerith-erp-9-0-system-daemon "
                              "à la base de données ne peut être établiée!\n\n"));

        errMsg.append(QObject::trUtf8("Serveur de base de données: %1.\n\n"
        							  "Dernière erreur (%2).\n\n"
                         	 	 	  "Contacter Pr. Prof. Dr.-Ing. Xavier Noundou\n"
                         	 	 	  "\t(YERITH.xavier@gmail.com)\n\n"
                         	 	 	  "Cliquer sur 'Cancel' pour terminer YERITH-PGI-9.0")
                      	  	  .arg(database.db_ip_address(),
                      	  		   database.lastError().text()));

        logger.log("main",
                   QString("last database (host: %1) error: %2")
                   	   .arg(database.db_ip_address(),
                   			database.lastError().text()));

        QDEBUG_STRING_OUTPUT_2("yerith-erp-9-0-system-daemon",
        					  FROM_UTF8_STRING(errMsg));

        exit(4);
    }

    //qDebug() << "yerith-erp-9-0-system-daemon.cpp | main | Database connection could be opened successfully";
    //logger << "[yerith-erp-9-0-system-daemon.cpp][main] Database connection could be opened successfully"
    //         << "\n";


    YERITH_ERP_3_0_SYSTEM_DAEMON_RUNTIME_PAY_HPP RUNTIME_PAY_YERITH_ERP_3_SYSTEM_DAEMON;


    YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ BACKUP_YERITH_ERP_3_SYSTEM_DAEMON;

    YERITH_ERP_SYSTEM_DAEMON_ALERT_PERIOD_TIME alertPeriode(&logger);

    YERITH_ERP_SYSTEM_DAEMON_ALERT_OVER_STOCK_QUANTITY alertDaemonQuantite(&logger);

    app.exec();

    return 0;
}
