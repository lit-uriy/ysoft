UTF-8 w/o BOM 
********************** RU ***********************

Класс-партнёр для табличного представления (Qt4).

Автор:
Литкевич Юрий (lit-uriy@yandex.ru).

Описание:
Этот класс задуман для расширения возможностей табличного представления
наиболее распространёнными функциями. Такими как копирование, форматирование таблицы и др.

Использование:
в pro-файл вашего проекта добавmте строчку:
include(peth/to/tableviewbuddy.pri)

в подключите заголовчный файл в исходном коде:
#include "tableviewbuddy.h"

И свяжите пртнёра с представлением:
TableViewBuddy *buddy = new TableViewBuddy(myTableView);



********************** EN ***********************
Class-buddy for table view (Qt4).

Author:
Yuriy Litkevich (lit-uriy@yandex.ru).

Description:
This class is conceived for the extension of possibilities of table view
by the most used functions. Such as copying, formatting of the table view, etc.

Usage:
in a pro-file of your project add a line:
include(peth/to/tableviewbuddy.pri)

include a header file into source code:
#include "tableviewbuddy.h"

also link the buddy to table view:
TableViewBuddy *buddy = new TableViewBuddy(myTableView);
