(**  ( global.{h|cpp} 
	\link{Qt4}{http://trolltech.com/products/}  Active Oberon.
	\ver 0.0.0 ()  *)

(**
	\todo  
	\o qRound().
	
*)
MODULE QTest0;

IMPORT
	KernelLog, QPoint0;



PROCEDURE Test*; 
VAR
	p, q : QPoint0.QPoint;
BEGIN
KernelLog.String("========== Create Points =================="); KernelLog.Ln;
	NEW(p, 3, 7);
KernelLog.String("Point p.x= "); KernelLog.Int(p.x,     0); KernelLog.Ln;
KernelLog.String("Point p.y= "); KernelLog.Int(p.y,    0); KernelLog.Ln;
	NEW(q, -3, 10);
KernelLog.String("Point q.x= "); KernelLog.Int(q.x,     0); KernelLog.Ln;
KernelLog.String("Point q.y= "); KernelLog.Int(q.y,     0); KernelLog.Ln;	

KernelLog.String("========== Multiplication Points =================="); KernelLog.Ln;
	p.mul(4);
KernelLog.String("Point p.x= "); KernelLog.Int(p.x,     0); KernelLog.Ln;
KernelLog.String("Point p.y= "); KernelLog.Int(p.y,    0); KernelLog.Ln;
	q.mul(2.3);
KernelLog.String("Point q.x= "); KernelLog.Int(q.x,     0); KernelLog.Ln;
KernelLog.String("Point q.y= "); KernelLog.Int(q.y,     0); KernelLog.Ln;	

KernelLog.String("========== Division Points =================="); KernelLog.Ln;
	p.div(4);
KernelLog.String("Point p.x= "); KernelLog.Int(p.x,     0); KernelLog.Ln;
KernelLog.String("Point p.y= "); KernelLog.Int(p.y,    0); KernelLog.Ln;
	q.div(2.3);
KernelLog.String("Point q.x= "); KernelLog.Int(q.x,     0); KernelLog.Ln;
KernelLog.String("Point q.y= "); KernelLog.Int(q.y,     0); KernelLog.Ln;	

KernelLog.String("========== Division member of Points =================="); KernelLog.Ln;
	p.x := p.x + 4;
	p.y := p.y + 4;	
KernelLog.String("Point p.x= "); KernelLog.Int(p.x,     0); KernelLog.Ln;
KernelLog.String("Point p.y= "); KernelLog.Int(p.y,    0); KernelLog.Ln;
	q.x := q.x * 2;
	q.y := q.y * 2;	
KernelLog.String("Point q.x= "); KernelLog.Int(q.x,     0); KernelLog.Ln;
KernelLog.String("Point q.y= "); KernelLog.Int(q.y,     0); KernelLog.Ln;	



(*
	p = p / 4;    
KernelLog.String("Point p.x= "); KernelLog.Int(p.x, o); KernelLog.Ln;
KernelLog.String("Point p.y= "); KernelLog.Int(p.y, o); KernelLog.Ln;
	q = q / 2.3; 
KernelLog.String("Point q.x= "); KernelLog.Int(q.x, o); KernelLog.Ln;
KernelLog.String("Point q.y= "); KernelLog.Int(q.y, o); KernelLog.Ln;
*)
END Test;




(*  Body *)
BEGIN
	KernelLog.String("Modul QTest0 loded"); KernelLog.Ln;
END QTest0.


SystemTools.Free QTest0 QPoint0 QGlobal0 ~

QTest0.Test ~



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