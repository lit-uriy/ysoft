(*
 *		SystemTools.Free QtGuiTest ~
 *		QtGuiTest.QtGuiTest ~
 *)

MODULE QtGuiTest;

IMPORT	
	Modules, Utilities, QtGui0; 



VAR
	wgt : QtGui0.QWidget;


(** Termination handler.
 *	Removes the window from the display space when the module is unloaded.
 *)
PROCEDURE Cleanup;	
BEGIN
	wgt.Close ();
	wgt := NIL
END Cleanup;


(** 
 *
 *)
BEGIN
	NEW (wgt);
	wgt.setTitle(Utilities.NewString ("QtGuiTest"));
	wgt.show;
	Modules.InstallTermHandler(Cleanup)
END QtGuiTest.



