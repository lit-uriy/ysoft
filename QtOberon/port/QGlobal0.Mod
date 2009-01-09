(** В этом модуле реализованы вспомогательные функции на языке Active Oberon,
	подобно qglobal.{h|cpp}	библиотеки \link{Qt4}{http://trolltech.com/products/}.
	\ver 0.0.0 (нулевая) версия модуля. *)
(**
	\todo Реализовать вспомогательные функции:
	\o qAbs.
	
	\todo проверить работу:
	\o qRound().
	
*)
MODULE QGlobal0;

(*
inline int qRound(qreal d)
{ return d >= 0.0 ? int(d + 0.5) : int(d - int(d-1) + 0.5) + int(d-1); }
*)
PROCEDURE qRound(d: REAL): INTEGER;  
BEGIN  
    IF d >= 0.0 THEN
		RETURN ENTIER(x + 0.5);
	ELSE
		RETURN ENTIER(d - ENTIER(d-1) + 0.5)  + ENTIER(d-1);
END round;


(*
inline qint64 qRound64(qreal d)
{ return d >= 0.0 ? qint64(d + 0.5) : qint64(d - qint64(d-1) + 0.5) + qint64(d-1); }
*)


(* Тело модуля *)
BEGIN
END QtCore0.

(* Свалка *)
(*
PROCEDURE round(x: REAL): LONGINT;  
BEGIN  
    RETURN ENTIER(x + 0.5)  
END round;  


PROCEDURE ceil(x: REAL): LONGINT;  
BEGIN  
    RETURN -ENTIER(-x)  
END ceil; 

PROCEDURE round(x: REAL): INTEGER;  
BEGIN  
    RETURN SHORT(ENTIER(x + 0.5))  
END round;
*)

(*
template <typename T>
inline T qAbs(const T &t) { return t >= 0 ? t : -t; }
*)
(*
template <typename T>
inline const T &qMin(const T &a, const T &b) { if (a < b) return a; return b; }
template <typename T>
inline const T &qMax(const T &a, const T &b) { if (a < b) return b; return a; }
template <typename T>
inline const T &qBound(const T &min, const T &val, const T &max)
{ return qMax(min, qMin(max, val)); }
*)