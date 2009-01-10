(** В этом модуле реализован порт класса QSize библиотеки
	\link{Qt4}{http://trolltech.com/products/} на язык Active Oberon.
	\ver 0.0.0 (нулевая) версия модуля. *)
(**
	\todo Реализовать связанные не-члены объекта QSize:
bool operator!= ( const QSize & p1, const QSize & p2 )
const QSize operator* ( const QSize & point, qreal factor )
const QSize operator* ( qreal factor, const QSize & point )
const QSize operator+ ( const QSize & p1, const QSize & p2 )
const QSize operator- ( const QSize & p1, const QSize & p2 )
const QSize operator- ( const QSize & point )
const QSize operator/ ( const QSize & point, qreal divisor )
bool operator== ( const QSize & p1, const QSize & p2 )

	\todo Реализовать модуль QGlobal0 и вспомогательные функции в нем qRound(), qAbs.
	
	\todo Рассмотреть возможность вывода объекта в поток:
	Связанные не-члены:
QDataStream & operator<< ( QDataStream & stream, const QSize & point )
QDataStream & operator>> ( QDataStream & stream, QSize & point )
	\pre{В заключение, объект QSize может быть выведен в поток так же просто
	как и сравниваться}
	
*)
MODULE QSize0;

IMPORT
	QGlobal0 (* - qRound(),  *);

(** Объект QSize описывает точку на плоскости с целочисленными координатами.

	Точка на плоскости определяется двумя экспортируемыми координатам \a x и \a y.
	
	\note В оригинале координаты находятся в частной области видимости и 
	не доступны из вне. Для доступа к этим координатам в оригинале используются
	следующие функции:
	\o width() и height() - для чтения координат;
	\o setWidth() и setHeight() - для установки/изменения их значения;
	\o rwidth() и rheight() - для установки/изменения их значения, эти функции возвращают
		ссылки на координаты (допуская прямые манипуляции);
	Существование последних привело к отказу от функций-оберток для координат.
	
	Функция isNull() проверяет точку на пустоту, т.е. она возвращает истину
	если обе координаты, \a x и \a y, равны нулю.	
	
	\note \include replaceoperators.doc

	
	Объект QSize также может быть использован как вектор: Сложение и
	вычитание определены как для векторов (каждый компонент добавляется
	отдельно). Объект QSize также может быть разделен или умножен на
	\c INTEGER или \c REAL.
	
	Дополнительно, класс QSize предоставляет функцию manhattanLength(),
	которая дает экономичную аппроксимацию длинны объекта QSize
	интерпретируемого как вектор.

*)

TYPE
	(** Объект QSize -  точка на плоскости с целочисленными координатами.
		\sa QSizeF, QSize, QRect
	*)
	QSize* = OBJECT;
		VAR
			(** Ширина \a w и высота \a h.*)		
			w*, h*: INTEGER;
		
		(** Конструктор.
			Конструирует размер с недействительной шириной и высотой.
			\sa isValid().
		*)
		PROCEDURE &New*;	
		BEGIN
			w = -1;
			y = -1;
		END New;
		
		(** Конструктор.
			Конструирует точку с заданной шириной \a width и высотой \a  height).
		*)	
		PROCEDURE &New*(width, height :INTEGER);	
		BEGIN
			w = width;
			h = height;		
		END New;
		
		(** Метод isNull.
			Возвращает истину если и \a ширина и \a высота, равны нулю,
			в противном случае возвращает ложь.
			
			\sa isValid(), isEmpty()
		*)		
		PROCEDURE isNull*():BOOLEAN;	
		BEGIN
			return ((w = 0) & (h = 0));		
		END isNull;	
		
		(** Метод isEmpty.
			Возвращает истину если или \a ширина или \a высота, меньше либо равны нулю,
			в противном случае возвращает ложь.
			
			\sa isNull(), isValid()
		*)		
		PROCEDURE isEmpty*():BOOLEAN;	
		BEGIN
			return ((w < 1) OR (h < 1));		
		END isEmpty;	
		
		(** Метод isValid.
			Возвращает истину если и \a ширина и \a высота, больше либо равны нулю,
			в противном случае возвращает ложь.
			
			\sa isNull(), isEmpty()
		*)		
		PROCEDURE isValid*():BOOLEAN;	
		BEGIN
			return ((w >= 0) & (h >= 0));		
		END isValid;	
		
		(** Метод transpose.
			Меняет местами ширину и высоту этого объекта.			
		*)		
		PROCEDURE transpose*(); 
		VAR
			tmp : INTEGER;
		BEGIN
			tmp := w;
			w := h;
			h := tmp;
		END transpose;
		
		(** Метод сложения.
			Как эквивалент оператора "+=" в С\С++.
			Прибавляет заданную точку \a point к этой точке.
			Например:
			\code
				VAR
					p, q : QSize;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -1, 4);
					p.add(q);		// p станет (2, 11)
				END;
			\endcode
		*)		
		PROCEDURE add*(CONST point : QSize); 
		BEGIN 
			SELF.x = SELF.x + point.x;
			SELF.y = SELF.y + point.y;
		END add;
		
		(** Метод вычитания.
			Как эквивалент оператора "-=" в С\С++.
			Вычитает заданную точку \a point из этой точки.
			Например:
			\code
				VAR
					p, q : QSize;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -1, 4);
					p.sub(q);		// p станет (4, 3)
				END;
			\endcode
		*)		
		PROCEDURE sub*(CONST point : QSize); 
		BEGIN 
			SELF.x = SELF.x - point.x;
			SELF.y = SELF.y - point.y;
		END sub;
		
		(** Метод умножения.
			Как эквивалент оператора "*=" в С\С++.
			Умножает координаты этой точки на \a factor.
			Например:
			\code
				VAR
					p, q : QSize;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -1, 4);
					p = p * 4;    // p станет (12, 28)
					q = q * 2.3;  // q станет (-2, 9) 
				END;
			\endcode
			Заметьте, что результат округляется к ближайшему целому, поскольку
			точка представлена целыми числами. Используйте QSizeF если необходимо
			представление с плавающей запятой.
		*)		
		PROCEDURE mul*(factor : REAL); 
		BEGIN 
			SELF.x = qRound(SELF.x * factor);
			SELF.y = qRound(SELF.y * factor);
		END mul;
		
		(** Метод деления.
			Как эквивалент оператора "/=" в С\С++.
			Делит координаты этой точки на \a divisor.
			Например:
			\code
				VAR
					p, q : QSize;
				BEGIN
					NEW(p, 3, 7);
					NEW(q, -1, 4);
					p = p * 4;    // p станет (12, 28)
					q = q * 2.3;  // q станет (-2, 9) 
				END;
			\endcode
			Заметьте, что результат округляется к ближайшему целому, поскольку
			точка представлена целыми числами. Используйте QSizeF если необходимо
			представление с плавающей запятой.
		*)		
		PROCEDURE div*(divisor : REAL); 
		BEGIN 
			SELF.x = qRound(SELF.x / divisor);
			SELF.y = qRound(SELF.y / divisor);
		END div;
		
	END QSize;



(* Связанные не-члены *)
(** Оператор равенства "=".
	Возвращает истину если \a p1 and \a p2 равны,
	в противном случае возвращает ложь.
	\sa "#".
*)		
PROCEDURE "="* (CONST p1, CONST p2 : QSize): BOOLEAN; 
BEGIN 
	return (p1.x = p2.x && p1.y = p2.y);
END "=";

(** Оператор неравенства  "#".
	Возвращает истину если \a p1 и \a p2 неравны,
	в противном случае возвращает ложь.
	\sa "=".			
*)		
PROCEDURE "#"* (CONST p1, CONST p2 : QSize): BOOLEAN; 
BEGIN 
	return (p1.x # p2.x && p1.y # p2.y);
END "#";

(** Оператор сложения  "+".
	Возвращает объект QSize, который является суммой заданных точек
	\a p1 и \a p2.
	Например:
	\code
		VAR
			p, q : QSize;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -1, 4);
			p = p + q;    // p станет (2, 11)
		END;
	\endcode			
*)		
PROCEDURE "+"* (CONST p1, CONST p2 : QSize): QSize; 
VAR
	p : QSize;
BEGIN
	NEW(p, p1.x + p2.x, p1.y + p2.y);
	return p;
END "+";

(** Оператор вычитания  "-".
	Возвращает объект QSize, который является разностью заданных точек
	\a p1 и \a p2.
	Например:
	\code
		VAR
			p, q : QSize;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -1, 4);
			p = p - q;    // p станет (4, 3)
		END;
	\endcode			
*)		
PROCEDURE "-"* (CONST p1, CONST p2 : QSize): QSize; 
VAR
	p : QSize;
BEGIN
	NEW(p, p1.x - p2.x, p1.y - p2.y);
	return p;
END "-";

(** Оператор умножения  "*".
	Возвращает объект QSize, который является произведением точеки и константы
	\a p и \a с.
	Например:
	\code
		VAR
			p, q : QSize;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -1, 4);
			p = p * 4;    // p станет (12, 28)
			q = q * 2.3;  // q станет (-2, 9) 
		END;
	\endcode			
*)		
PROCEDURE "*"* (CONST p : QSize, c : REAL): QSize; 
VAR
	p : QSize;
BEGIN
	NEW(p, qRound(p1.x*c), qRound(p1.y*c));
	return p;
END "*";

(** Оператор деления  "/".
	Возвращает объект QSize, который является произведением точеки и константы
	\a p и \a с.
	Например:
	\code
		VAR
			p, q : QSize;
		BEGIN
			NEW(p, 3, 7);
			NEW(q, -3, 10);
			p = p / 4;    // p станет (0, 2)
			q = q / 2.3;  // q станет (-1, 4)
		END;
	\endcode			
*)		
PROCEDURE "/"* (CONST p : QSize, c : REAL): QSize; 
VAR
	p : QSize;
BEGIN
	NEW(p, qRound(p1.x/c), qRound(p1.y/c));
	return p;
END "/";




(* Тело модуля *)
BEGIN
END QtCore0.


(* помойка *)
(*
	Оригинальные перегруженные операторы-члены класса типа: "+=", "-=", "*=" и т.п.
	отсутствуютТоТ.к. в Активном Обероне  
	Пусть задана точка \e p, тогда все следующие выражения эквивалентны:
	\code{cpp}
		QSize p;
		
		p.setX(p.x() + 1);
		p += QSize(1, 0);
		p.rx()++;
	\endcode
	тоже Активном обероне:
	\code
		VAR
			p, q : QSize;
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
		QSize p;			|			p, q : QSize;
							|		BEGIN
							|			NEW(p); 
		p.setX(p.x() + 1);	|			p.x = p.x + 1;
		p += QSize(1, 0);	|			NEW(q, 1, 0); p.add(q);
		p.rx()++;			|			INC(p.x);
							|		END;
	\endcode				|	\endcode
	
	

	.
	
	Пусть задана точка \e p, тогда все следующие выражения эквивалентны:
	
	\code{cpp}
		QSize p;
		
		p.setX(p.x() + 1);
		p += QSize(1, 0);
		p.rx()++;
	\endcode
*)