#!/bin/sh
cd html
qhelpgenerator assistant_ru.qhp -o ../assistant_ru.qch
qhelpgenerator designer_ru.qhp -o ../designer_ru.qch
qhelpgenerator linguist_ru.qhp -o ../linguist_ru.qch
qhelpgenerator qmake_ru.qhp -o ../qmake_ru.qch
qhelpgenerator qt_ru.qhp -o ../qt_ru.qch

# using read instead of pause
read