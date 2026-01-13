/*
 * yerith-erp-9-0-system-daemon-database.cpp
 *
 *      Author: Pr. Prof. Dr.-Ing. Xavier Noundou
 */

#include "yerith-erp-9-0-system-daemon-database.hpp"

#include "src/utils/yerith-erp-9-0-system-daemon-utils.hpp"

const QString YerothERPDatabase::MYSQL("MySQL");

QString YerothERPDatabase::_db_type("");

QString YerothERPDatabase::_db_name("");

QString YerothERPDatabase::_db_ip_address("");

QString YerothERPDatabase::_db_user_name("");

QString YerothERPDatabase::_db_user_pwd("");

QString YerothERPDatabase::_db_connection_options("");


const QString YerothERPDatabase::PERIODES_DAPPARTENANCE_GROUPES_DE_PAIE_HR("periodes_dappartenance_groupes_de_paie_hr");

const QString YerothERPDatabase::IMPRIMANTERESEAU_RECUS_PETITS("imprimantereseau_recus_petits");

const QString YerothERPDatabase::COMPTES_BANCAIRES("comptes_bancaires");

const QString YerothERPDatabase::OPERATIONS_COMPTABLES("operations_comptables");

const QString YerothERPDatabase::ENTREPRISE_INFO("entreprise_info");

const QString YerothERPDatabase::PAIEMENTS("paiements");

const QString YerothERPDatabase::USERS("users");

const QString YerothERPDatabase::UNITES_DE_MESURES("unites_DE_MESURES");

const QString YerothERPDatabase::TITRES("titres");

const QString YerothERPDatabase::LOCALISATIONS("localisations");

const QString YerothERPDatabase::DEPARTEMENTS_PRODUITS("departements_produits");

const QString YerothERPDatabase::CATEGORIES("categories");

const QString YerothERPDatabase::LIGNES_BUDGETAIRES("LIGNES_BUDGETAIRES");

const QString YerothERPDatabase::PROGRAMMES_DE_FIDELITE_CLIENTS("programmes_de_fidelite_clients");

const QString YerothERPDatabase::GROUPES_DEMPLOYES_hr("groupes_demployes_hr");

const QString YerothERPDatabase::GROUPES_DE_PAIE_hr("groupes_de_paie_hr");

const QString YerothERPDatabase::CLIENTS("clients");

const QString YerothERPDatabase::GROUPES_DE_CLIENTS("groupes_de_clients");

const QString YerothERPDatabase::SALAIRES("SALAIRES");

const QString YerothERPDatabase::FOURNISSEURS("fournisseurs");

const QString YerothERPDatabase::ALERTES("alertes");

const QString YerothERPDatabase::REMISES("remises");

const QString YerothERPDatabase::CREDIT_CARD_ISSUING_COMPANY("credit_card_issuing_company");

const QString YerothERPDatabase::CONDITIONS_ALERTES("conditions_alertes");

const QString YerothERPDatabase::COURRIERS_ALERTES("courriers_alertes");

const QString YerothERPDatabase::CHARGES_FINANCIERES("charges_financieres");

const QString YerothERPDatabase::ACHATS("achats");

const QString YerothERPDatabase::STOCKS("stocks");

const QString YerothERPDatabase::SERVICES_COMPLETES("services_completes");

const QString YerothERPDatabase::STOCKS_VENDU("stocks_vendu");

const QString YerothERPDatabase::STOCKS_SORTIES("stocks_sorties");

const QString YerothERPDatabase::MARCHANDISES("marchandises");

const QString YerothERPDatabase::CONFIGURATIONS("configurations");

const QString YerothERPDatabase::INIT_CONFIGURATIONS("init_configurations");

const QString YerothERPDatabase::YRI_DB_RUNTIME_VERIF("yri_db_runtime_verif");

const QString YerothERPDatabase::TYPE_DOPERATIONS_FINANCIERES("type_doperations_financieres");

const QString YerothERPDatabase::TYPE_DE_VENTE("type_de_vente");

const QString YerothERPDatabase::TYPE_DE_PAIEMENT("type_de_paiement");

const QString YerothERPDatabase::ROLES("roles");

const QString YerothERPDatabase::DBMS("dbms");


YerothERPDatabase::YerothERPDatabase(QString dbType)
{
    if (YerothERPAlertUtils::
            isEqualCaseInsensitive(dbType, YerothERPDatabase::MYSQL))
    {
        qDebug() <<
                 "yerith-erp-9-0-system-daemon-3.0 | YerenDatabase::YerenDatabase | database type: QMYSQL \n";
        _database = QSqlDatabase::addDatabase("QMYSQL");
    }

    this->set_db_type(dbType);
    this->set_db_name(YerenConfig::_db_name);
    this->set_db_ip_address(YerenConfig::_db_ip_address);
    this->set_db_user_name(YerenConfig::_db_user_name);
    this->set_db_user_pwd(YerenConfig::_db_user_pwd);
    this->set_db_connection_options(YerenConfig::_db_connection_options);
}

void YerothERPDatabase::set_db_name(QString db_name)
{
    _db_name = db_name;
    _database.setDatabaseName(_db_name);
}

void YerothERPDatabase::set_db_ip_address(QString db_ip_address)
{
    _db_ip_address = db_ip_address;
    _database.setHostName(_db_ip_address);
}

void YerothERPDatabase::set_db_user_name(QString db_user_name)
{
    _db_user_name = db_user_name;
    _database.setUserName(_db_user_name);
}

void YerothERPDatabase::set_db_user_pwd(QString db_user_pwd)
{
    _db_user_pwd = db_user_pwd;
    _database.setPassword(_db_user_pwd);
}

void YerothERPDatabase::set_db_connection_options(QString db_connection_options)
{
    _db_connection_options = db_connection_options;
    _database.setConnectOptions(_db_connection_options);

}

QString YerothERPDatabase::toString() const
{
    QString ret;

    if (_database.isValid())
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            _database.
                                                            databaseName(),
                                                            _database.
                                                            hostName(),
                                                            _database.
                                                            connectOptions
                                                            ()));
    }
    else
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            YerothERPDatabase::
                                                            _db_name,
                                                            YerothERPDatabase::
                                                            _db_ip_address,
                                                            YerothERPDatabase::
                                                            _db_connection_options));
    }

    return ret;
}
