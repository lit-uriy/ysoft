#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QString>
#include <QDebug>


//=====================================================
//		Создаем тикеты
//=====================================================
bool CreateTickets(QStringList list, QString component, QString milestone, QString filename)
{
  bool	ok;
 
  QSqlQuery query;
  QString	qstr;
  // ticket param
  int		t_time,
			t_changetime;   
  QString	t_type,
			t_component,
			t_severity,
			t_priority,
			t_owner,
			t_reporter,
			t_cc,
			t_version,
			t_milestone,
			t_status,
			t_resolution,
			t_summary,
			t_description,
			t_keywords;
  

	// Сначала узнаем время последнего тикета
	qstr = "SELECT MAX(time) FROM ticket"
	ok = query(qstr);
    if (!ok)
	{
		qDebug() << "Select Time status: " << query.lastError().text() << "\n\r";
		return ok;
    }
	query.first();
	ok = !query.isNull();
    if (!ok)
	{
		qDebug() << "Time is NULL "  << "\n\r";
		return ok;
    } 
	t_time = query.value(0).toInt();
	t_changetime = t_time;
	
	// Заполним одинаковые атрибуты тикетов для БД
	t_type = tr("задача");
	t_component = component;
	t_severity = tr("обычный");
	t_priority = tr("обычный");
	t_owner = tr("lit-uriy");
	t_reporter = tr("lit-uriy");
	t_cc = tr("");
	t_version = tr("");	//NULL
	t_milestone = milestone;
	t_status = tr("new");
	t_resolution = tr(""); //NULL
	t_keywords = tr("");

	// Создадим тикеты в БД
	qstr = "INSERT INTO ticket \
			( \
			type, \
			time, \
			changetime, \
			component, \
			severity, \
			priority, \
			owner, \
			reporter, \
			cc, \
			version, \
			milestone, \
			status, \
			resolution, \
			summary, \
			description, \
			keywords \
			) \
		VALUES \
			( \
			:type, \
			:time, \
			:changetime, \
			:component, \
			:severity, \
			:priority, \
			:owner, \
			:reporter, \
			:cc, \
			:version, \
			:milestone, \
			:status, \
			:resolution, \
			:summary, \
			:description, \
			:keywords \
			)";
	appdbquery.prepare(qstr);
	// Индивидуально для каждого тикета
	foreach(QString section, list)
	{
		t_summary = tr("секция ") + section;
		t_description = tr("перевод секции ") + section + tr(" в файле ") + filename;
		query.bindValue(":type", t_type);
		query.bindValue(":time", t_time);
		query.bindValue(":changetime", t_changetime);
		query.bindValue(":component", t_component);
		query.bindValue(":severity", t_severity);
		query.bindValue(":priority", t_priority);
		query.bindValue(":owner", t_owner);
		query.bindValue(":reporter", t_reporter);
		query.bindValue(":cc", t_cc);
		query.bindValue(":version", t_version);
		query.bindValue(":milestone", t_milestone);
		query.bindValue(":status", t_status);
		query.bindValue(":resolution", t_resolution);
		query.bindValue(":summary", t_summary);
		query.bindValue(":description", t_description);
		query.bindValue(":keywords", t_keywords);
	}
}
INSERT INTO ticket VALUES(11,'задача',1210408131,1210408131,'Qt Designer','обычный','обычный','lit-uriy','lit-uriy','',NULL,'Перевод TS-файлов','new',NULL,'секция PluginDialog','перевод секции PluginDialog в файле designer_ru.ts','');


t_type
t_time
t_changetime
t_component
t_severity
t_priority
t_owner
t_reporter
t_cc
t_version
t_milestone
t_status
t_resolution
t_summary
t_description
t_keywords


id
type
time
changetime
component
severity
priority
owner
reporter
cc
version
milestone
status
resolution
summary
description
keywords

