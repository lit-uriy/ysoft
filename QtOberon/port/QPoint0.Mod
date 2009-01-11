(** В этом модуле реализован порт класса QPoint библиотеки
	\link{Qt4}{http://trolltech.com/products/} на язык Active Oberon.
	\ver 0.0.0 (нулевая) версия модуля. *)
(**
	\todo Реализовать связанные не-члены объекта QPoint:
bool operator!= ( const QPoint & p1, const QPoint & p2 )
const QPoint operator* ( const QPoint & point, qreal factor )
const QPoint operator* ( qreal factor, const QPoint & point )
const QPoint operator+ ( const QPoint & p1, const QPoint & p2 )
const QPoint operator- ( const QPoint & p1, const QPoint & p2 )
const QPoint operator- ( const QPoint & point )
const QPoint operator/ ( const QPoint & point, qreal divisor )
bool operator== ( const QPoint & p1, const QPoint & p2 )

	\todo Реализовать модуль QGlobal0 и вспомогательные функции в нем qRound(), qAbs.
	
	\todo Рассмотреть возможность вывода объекта в поток:
	Связанные не-члены:
QDataStream & operator<< ( QDataStream & stream, const QPoint & point )
QDataStream & operator>> ( QDataStream & stream, QPoint & point )
	\pre{В заключение, объект QPoint может быть выведен в поток так же просто
	как и сравниваться}
	
*)
MODULE QPoint0 {OVERLOADING};

IMPORT
	KernelLog, QGlobal0;

(** Объект QPoint описывает точку на плоскости с целочисленными координатами.

	Точка на плоскости определяется двумя экспортируемыми координатам \a x и \a y.
	
	\note В оригинале координаты находятся в частной области видимости и 
	не доступны из вне. Для доступа к этим координатам в оригинале используются
	следующие функции:
	\o x() и y() - для чтения координат;
	\o setX() и setY() - для установки/изменения их значения;
	\o rx() и ry() - для установки/изменения их значения, эти функции возвращают
		ссылки на координаты (допуская прямые манипуляции);
	Существование последних привело к отказу от функций-оберток для координат.
	
	Функция isNull() проверяет точку на пустоту, т.е. она возвращает истину
	если обе координаты, \a x и \a y, равны нулю.	
	
	\note \include replaceoperators.doc

	
	Объект QPoint также может быть использован как вектор: Сложение и
	вычитание определены как для векторов (каждый компонент добавляется
	отдельно). Объект QPoint также может быть разделен или умножен на
	\c INTEGER или \c REAL.
	
	Дополнительно, класс QPoint предоставляет функцию manhattanLength(),
	которая дает экономичную аппроксимацию длинны объекта QPoint
	интерпретируемого как вектор.

*)

TYPE
	(** Объект QPoint -  точка на плоскости с целочисленными координатами.
		\sa QPointF, QPolygon
	*)
	QPoint* = OBJECT
		VAR
			(** Координаты точки \a x и \a y.*)		
			x*, y*: INTEGER;
		
		(** Конструктор.
			Конструирует пустую точку, т.е. с координатами (0, 0).
			\sa isNull().
		
		PROCEDURE &New;	
		BEGIN
			x := 0;
			y := 0;
		END New;
		*)
		(** Конструктор.
			Конструирует точку с заданными координатами (\a x, \a  y).
		*)	
		PROCEDURE &New(xpos, ypos :INTEGER);	
		BEGIN
			x := xpos;
			y := ypos;		
		END New;
		
		(** Метод isNull.
			Возвращает истину если обе координаты, \a x и \a y, равны нулю,
			в противном случае возвращает ложь.
		*)		
		PROCEDURE isNull*():BOOLEAN;	
		BEGIN
			RETURN ((x = 0) & (y = 0));		
		END isNull;	
		
		(** "Манхэтэнская длинна".
			Возвращает сумму абсолютных величин \a x и \a y,
			традиционно известную как "Манхэтэнская длинна" вектора от
			начала координат до точки.
			Например:
			\code
				VAR
					p : QPoint;
					i : INTEGER;
				BEGIN
					NEW(p, 3, 7);
					i := p.manhattanLength();    // i станет (10)
				END;
			\endcode			
		*)		
		PROCEDURE manhattanLength*(): INTEGER; 
		VAR
			xt, yt : INTEGER;
		BEGIN
			xt := QGlobal0.qAbs(x);
			yt := QGlobal0.qAbs(y);
			RETURN (xt + yt);
		END manhattanLength;
		
		(** Метод сложения.
			Как эквивалент оператора "+=" в С\С++.
			Прибавляет заданную точку \a point к этой точке.
			Например:
			\code
				VAR
					p, q : QPoint;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -1, 4);
					p.add(q);		// p станет (2, 11)
				END;
			\endcode
		*)		
		PROCEDURE add*(CONST point : QPoint); 
		BEGIN 
			SELF.x := SELF.x + point.x;
			SELF.y := SELF.y + point.y;
		END add;
		
		(** Метод вычитания.
			Как эквивалент оператора "-=" в С\С++.
			Вычитает заданную точку \a point из этой точки.
			Например:
			\code
				VAR
					p, q : QPoint;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -1, 4);
					p.sub(q);		// p станет (4, 3)
				END;
			\endcode
		*)		
		PROCEDURE sub*(CONST point : QPoint); 
		BEGIN 
			SELF.x := SELF.x - point.x;
			SELF.y := SELF.y - point.y;
		END sub;
		
		(** Метод умножения.
			Как эквивалент оператора "*=" в С\С++.
			Умножает координаты этой точки на \a factor.
			Например:
			\code
				VAR
					p, q : QPoint;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -3, 10);
					p.mul(4);    // p станет (12, 28)
					q.mul(2.3);  // q станет (-7, 23) 
				END;
			\endcode
			Заметьте, что результат округляется к ближайшему целому, поскольку
			точка представлена целыми числами. Используйте QPointF если необходимо
			представление с плавающей запятой.
		*)		
		PROCEDURE mul*(factor : REAL); 
		BEGIN 
			SELF.x := QGlobal0.qRound(SELF.x * factor);
			SELF.y := QGlobal0.qRound(SELF.y * factor);
		END mul;
		
		(** Метод деления.
			Как эквивалент оператора "/=" в С\С++.
			Делит координаты этой точки на \a divisor.
			Например:
			\code
				VAR
					p, q : QPoint;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -1, 4);
					p = p * 4;    // p станет (12, 28)
					q = q * 2.3;  // q станет (-2, 9) 
				END;
			\endcode
			Заметьте, что результат округляется к ближайшему целому, поскольку
			точка представлена целыми числами. Используйте QPointF если необходимо
			представление с плавающей запятой.
		*)		
		PROCEDURE div*(divisor : REAL); 
		BEGIN 
			SELF.x := QGlobal0.qRound(SELF.x / divisor);
			KernelLog.String("Object SELF.x= "); KernelLog.Int(SELF.x,     0); KernelLog.Ln;
			SELF.y := QGlobal0.qRound(SELF.y / divisor);
			KernelLog.String("Object SELFyx= "); KernelLog.Int(SELF.y,     0); KernelLog.Ln;
		END div;
		
	END QPoint;



(* Связанные не-члены *)
(** Оператор равенства "=".
	Возвращает истину если \a p1 and \a p2 равны,
	в противном случае возвращает ложь.
	\sa "#".
	
PROCEDURE "="* (CONST p1, CONST p2 : QPoint): BOOLEAN; 
BEGIN 
	return (p1.x = p2.x && p1.y = p2.y);
END "=";
*)	
(** Оператор неравенства  "#".
	Возвращает истину если \a p1 и \a p2 неравны,
	в противном случае возвращает ложь.
	\sa "=".			
	
PROCEDURE "#"* (CONST p1, CONST p2 : QPoint): BOOLEAN; 
BEGIN 
	return (p1.x # p2.x && p1.y # p2.y);
END "#";
*)	
(** Оператор сложения  "+".
	Возвращает объект QPoint, который является суммой заданных точек
	\a p1 и \a p2.
	Например:
	\code
		VAR
			p, q : QPoint;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -1, 4);
			p = p + q;    // p станет (2, 11)
		END;
	\endcode			
	
PROCEDURE "+"* (CONST p1, CONST p2 : QPoint): QPoint; 
VAR
	p : QPoint;
BEGIN
	NEW(p, p1.x + p2.x, p1.y + p2.y);
	return p;
END "+";
*)	
(** Оператор вычитания  "-".
	Возвращает объект QPoint, который является разностью заданных точек
	\a p1 и \a p2.
	Например:
	\code
		VAR
			p, q : QPoint;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -1, 4);
			p = p - q;    // p станет (4, 3)
		END;
	\endcode			
	
PROCEDURE "-"* (CONST p1, CONST p2 : QPoint): QPoint; 
VAR
	p : QPoint;
BEGIN
	NEW(p, p1.x - p2.x, p1.y - p2.y);
	return p;
END "-";
*)	
(** Оператор умножения  "*".
	Возвращает объект QPoint, который является произведением точеки и константы
	\a p и \a с.
	Например:
	\code
		VAR
			p, q : QPoint;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -1, 4);
			p = p * 4;    // p станет (12, 28)
			q = q * 2.3;  // q станет (-2, 9) 
		END;
	\endcode			
	
PROCEDURE "*"* (CONST p : QPoint, c : REAL): QPoint; 
VAR
	p : QPoint;
BEGIN
	NEW(p, qRound(p1.x*c), qRound(p1.y*c));
	return p;
END "*";
*)	
(** Оператор деления  "/".
	Возвращает объект QPoint, который является произведением точеки и константы
	\a p и \a с.
	Например:
	\code
		VAR
			p, q : QPoint;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -3, 10);
			p = p / 4;    // p станет (0, 2)
			q = q / 2.3;  // q станет (-1, 4)
		END;
	\endcode			
	
PROCEDURE "/"* (CONST p : QPoint, c : REAL): QPoint; 
VAR
	p : QPoint;
BEGIN
	NEW(p, qRound(p1.x/c), qRound(p1.y/c));
	return p;
END "/";
*)	



(* Тело модуля *)
BEGIN
	KernelLog.String("Modul QPoint0 loded"); KernelLog.Ln;
END QPoint0.


SystemTools.Free QPoint0~

QPoint0.Test ~



(* помойка *)
(*
	Оригинальные перегруженные операторы-члены класса типа: "+=", "-=", "*=" и т.п.
	отсутствуютТоТ.к. в Активном Обероне  
	Пусть задана точка \e p, тогда все следующие выражения эквивалентны:
	\code{cpp}
		QPoint p;
		
		p.setX(p.x() + 1);
		p += QPoint(1, 0);
		p.rx()++;
	\endcode
	тоже Активном обероне:
	\code
		VAR
			p, q : QPoint;
		BEGIN
			NEW(p); 
			p.x = p.x + 1;
			NEW(q, 1, 0); p.add(q);
			INC(p.x);
		END;
	\endcode

	\tbl
	\col1					|	\col2
							|	\code
	\code{cpp}				|		VAR
		QPoint p;			|			p, q : QPoint;
							|		BEGIN
							|			NEW(p); 
		p.setX(p.x() + 1);	|			p.x = p.x + 1;
		p += QPoint(1, 0);	|			NEW(q, 1, 0); p.add(q);
		p.rx()++;			|			INC(p.x);
							|		END;
	\endcode				|	\endcode
	
	

	.
	
	Пусть задана точка \e p, тогда все следующие выражения эквивалентны:
	
	\code{cpp}
		QPoint p;
		
		p.setX(p.x() + 1);
		p += QPoint(1, 0);
		p.rx()++;
	\endcode
*)