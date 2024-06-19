/*
 * yerith-erp-9-0-system-daemon-db-backup-export-gz.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef YERITH_ERP_3_0_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ_HPP_
#define YERITH_ERP_3_0_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ_HPP_


#include "src/include/yerith-erp-9-0-system-daemon-abstract-entity.hpp"


class YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ:public
    YERITH_ERP_SYSTEM_DAEMON_ABSTRACT_ENTITY
{
Q_OBJECT public:
    YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ();

    inline ~ YERITH_ERP_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ()
    {
    }

public slots:
    void do_backups();

protected:

    QString _YERITH_ERP_3_0_BINARY_FULL_PATH_FOR_BACKUP_RESTORE;

    QString _YERITH_ERP_3_0_SQL_BACKUP_DIRECTORY;
};


#endif /* YERITH_ERP_3_0_SYSTEM_DAEMON_DB_BACKUP_EXPORT_GZ_HPP_ */
