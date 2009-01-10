(** В этом модуле реализован порт файла(ов) global.{h|cpp} библиотеки
	\link{Qt4}{http://trolltech.com/products/} на язык Active Oberon.
	\ver 0.0.0 (нулевая) версия модуля. *)

(**
	\todo проверить работу:
	\o qRound().
	
*)
MODULE QGlobal0;

IMPORT
	KernelLog;

(*
template <typename T>
inline T qAbs(const T &t) { return t >= 0 ? t : -t; }
*)
PROCEDURE qAbs*(x: INTEGER): INTEGER;  
BEGIN  
		RETURN ABS(x);
END qAbs;


(*
inline int qRound*(qreal d)
{ return d >= 0.0 ? int(d + 0.5) : int(d - int(d-1) + 0.5) + int(d-1); }
*)
PROCEDURE qRound*(d: REAL): INTEGER;  
BEGIN  
    IF (d >= 0.0) THEN
		RETURN SHORT(ENTIER(d + 0.5));
	ELSE
		RETURN SHORT(ENTIER(d - ENTIER(d-1) + 0.5)  + ENTIER(d-1));
	END
END qRound;


(*
inline qint64 qRound64(qreal d)
{ return d >= 0.0 ? qint64(d + 0.5) : qint64(d - qint64(d-1) + 0.5) + qint64(d-1); }
*)


(* *)
BEGIN
	KernelLog.String("Loding is ok "); KernelLog.Ln;
END QGlobal0.


SystemTools.Free QGlobal0~

QGlobal0.Open x.txt ~



(*
PROCEDURE ceil(x: REAL): LONGINT;  
BEGIN  
    RETURN -ENTIER(-x)  
END ceil; 
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