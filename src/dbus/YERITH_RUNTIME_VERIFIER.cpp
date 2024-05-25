/*
 * YERITH_RUNTIME_VERIFIER.hpp
 *
 *      Author: PROF. DR.-ENG. DIPL.-INF. XAVIER NOUNDOU
 */


#include "YERITH_RUNTIME_VERIFIER.hpp"


#include "src/utils/yerith-erp-9-0-system-daemon-utils.hpp"





uint YERITH_RUNTIME_VERIFIER::_MAX_LAST_SIGNALS_SOURCE_TARGET_COUNT(0);

uint YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index(0);

QStringList YERITH_RUNTIME_VERIFIER::_LAST_SIGNALS_source_target_strings;

const QString YERITH_RUNTIME_VERIFIER::DBUS_TIME_FORMAT_WITH_MILLISECONDS(DBUS_FORMAT_TIME_WITH_MS);

const QString YERITH_RUNTIME_VERIFIER::YERITH_ERP_PGI_SYSTEM_DAEMOM_dbus_verifier_tester_ID("yerith-erp-pgi-sys-daemon-3.0");


YERITH_RUNTIME_VERIFIER::YERITH_RUNTIME_VERIFIER()
:a_YRI_DB_RUNTIME_VERIF_instance(0)
{
	QString systemYerothService = "yri.db-runtime.verif";

	a_YRI_DB_RUNTIME_VERIF_instance =
			new com::yerith::rd::IYRIruntimeverification(systemYerothService,
														"/yri_sd_runtime_verif_language_EXAMPLE_realcase",
														QDBusConnection::systemBus(),
														this);

	startTimer(3000);
}


void YERITH_RUNTIME_VERIFIER::YRI_slot_refresh_DELETE_DB_MYSQL__CALLED(QString in0 /* = "" */,
   											 	 	 	 	 	 	  uint in1 /* = 1 */)
{
    QString yri_in0 = QString("%1;%2")
                        .arg(in0,
                             YERITH_RUNTIME_VERIFIER::YERITH_ERP_PGI_SYSTEM_DAEMOM_dbus_verifier_tester_ID);

	a_YRI_DB_RUNTIME_VERIF_instance->YRI_slot_refresh_DELETE_DB_MYSQL(yri_in0,
																	in1);

	QStringList db_op_INFORMATIONS = in0.split(";", Qt::KeepEmptyParts);

	QString sql_table_name = db_op_INFORMATIONS.at(0);

	QString signal_source_target =
				QString("%1;%2.%3;%4;%5;%6")
				.arg(DBUS_CURRENT_TIME_WITH_MILLISECONDS,
						"DELETE",
						sql_table_name,
						"ERP_PGI",
						"runtime_verif",
						QString::number(in1));

		if (YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index >
			YERITH_RUNTIME_VERIFIER::_MAX_LAST_SIGNALS_SOURCE_TARGET_COUNT)
		{
			YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index = 0;
		}
		else
		{
			++YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index;
		}

		YERITH_RUNTIME_VERIFIER::_LAST_SIGNALS_source_target_strings
							.insert(YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index,
									signal_source_target);
}


void YERITH_RUNTIME_VERIFIER::YRI_slot_refresh_INSERT_DB_MYSQL__CALLED(QString in0 /* = "" */,
 											 	 	 	 	 	 	  uint in1 /* = 1 */)
{
    QString yri_in0 = QString("%1;%2")
                        .arg(in0,
                             YERITH_RUNTIME_VERIFIER::YERITH_ERP_PGI_SYSTEM_DAEMOM_dbus_verifier_tester_ID);

	a_YRI_DB_RUNTIME_VERIF_instance->YRI_slot_refresh_INSERT_DB_MYSQL(yri_in0,
																	in1);

	QStringList db_op_INFORMATIONS = in0.split(";", Qt::KeepEmptyParts);

	QString sql_table_name = db_op_INFORMATIONS.at(0);

	QString signal_source_target =
				QString("%1;%2.%3;%4;%5;%6")
				.arg(DBUS_CURRENT_TIME_WITH_MILLISECONDS,
						"INSERT",
						sql_table_name,
						"ERP_PGI",
						"runtime_verif",
						QString::number(in1));

		if (YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index >
			YERITH_RUNTIME_VERIFIER::_MAX_LAST_SIGNALS_SOURCE_TARGET_COUNT)
		{
			YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index = 0;
		}
		else
		{
			++YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index;
		}

		YERITH_RUNTIME_VERIFIER::_LAST_SIGNALS_source_target_strings
							.insert(YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index,
									signal_source_target);
}


void YERITH_RUNTIME_VERIFIER::YRI_slot_refresh_SELECT_DB_MYSQL__CALLED(QString in0 /* = "" */,
   											 	 	 	 	 	 	  uint in1 /* = 1 */)
{
    QString yri_in0 = QString("%1;%2")
                        .arg(in0,
                             YERITH_RUNTIME_VERIFIER::YERITH_ERP_PGI_SYSTEM_DAEMOM_dbus_verifier_tester_ID);

	a_YRI_DB_RUNTIME_VERIF_instance->YRI_slot_refresh_SELECT_DB_MYSQL(yri_in0,
																	in1);

	QStringList db_op_INFORMATIONS = in0.split(";", Qt::KeepEmptyParts);

	QString sql_table_name = db_op_INFORMATIONS.at(0);

	QString signal_source_target =
				QString("%1;%2.%3;%4;%5;%6")
				.arg(DBUS_CURRENT_TIME_WITH_MILLISECONDS,
						"SELECT",
						sql_table_name,
						"ERP_PGI",
						"runtime_verif",
						QString::number(in1));

		if (YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index >
			YERITH_RUNTIME_VERIFIER::_MAX_LAST_SIGNALS_SOURCE_TARGET_COUNT)
		{
			YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index = 0;
		}
		else
		{
			++YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index;
		}

		YERITH_RUNTIME_VERIFIER::_LAST_SIGNALS_source_target_strings
							.insert(YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index,
									signal_source_target);
}


void YERITH_RUNTIME_VERIFIER::YRI_slot_refresh_UPDATE_DB_MYSQL__CALLED(QString in0 /* = "" */,
   											 	 	 	 	 	 	  uint in1 /* = 1 */)
{
    QString yri_in0 = QString("%1;%2")
                        .arg(in0,
                             YERITH_RUNTIME_VERIFIER::YERITH_ERP_PGI_SYSTEM_DAEMOM_dbus_verifier_tester_ID);

	a_YRI_DB_RUNTIME_VERIF_instance->YRI_slot_refresh_UPDATE_DB_MYSQL(yri_in0,
																	in1);

	QStringList db_op_INFORMATIONS = in0.split(";", Qt::KeepEmptyParts);

	QString sql_table_name = db_op_INFORMATIONS.at(0);

	QString signal_source_target =
				QString("%1;%2.%3;%4;%5;%6")
				.arg(DBUS_CURRENT_TIME_WITH_MILLISECONDS,
						"UPDATE",
						sql_table_name,
						"ERP_PGI",
						"runtime_verif",
						QString::number(in1));

		if (YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index >
			YERITH_RUNTIME_VERIFIER::_MAX_LAST_SIGNALS_SOURCE_TARGET_COUNT)
		{
			YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index = 0;
		}
		else
		{
			++YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index;
		}

		YERITH_RUNTIME_VERIFIER::_LAST_SIGNALS_source_target_strings
							.insert(YERITH_RUNTIME_VERIFIER::_current_MAX_LAST_SIGNALS_SOURCE_TARGET_index,
									signal_source_target);
}



