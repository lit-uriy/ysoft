(** Порт класса QWidget
 *)

MODULE QtGui0;

IMPORT	
	WM := WMWindowManager, WMComponents, Utilities; 

CONST
	(* Window position relative to the upper left display corner. *)
	Toleft = 100;
	Fromtop = 50;
	(* Window size. *)
	Width = 80;
	Height = 120;


TYPE
	String = Utilities.String;
	QWidget* = OBJECT(WMComponents.FormWindow);
		VAR
			title : String;
			visible : BOOLEAN;
		
		(* Конструктор *)
		PROCEDURE &New;	
		BEGIN
			Init(Width, Height , TRUE);		
		END New;
		
		(* Отображение *)
		PROCEDURE show*;	
		BEGIN
			(* Open the window *)
			 WM.ExtAddWindow(SELF, Toleft, Fromtop, {WM.FlagFrame});
		END show;	
		
		(* Заголовок *)
		PROCEDURE setTitle*(t : String);	
		BEGIN
			title:=t;
			SetTitle(title);	
		END setTitle;
		
	END QWidget;


(* Тело модуля *)
BEGIN
END QtGui0.



