/*! Редактор.
 *	\file	editor.h
 */

void Load*(CONST filename,  format : ARRAY OF CHAR){
/*VAR*/
	text : Texts.Text;
	msg : ARRAY 512 OF CHAR; res : LONGINT;
	fullname : Files.FileName;
	decoder : Codecs.TextDecoder;
	in : Streams.Reader;
	file : Files.File;
/*BEGIN*/
	res := -1;
	COPY(filename, fullname);
	
	/* Check whether file exists and get its canonical name */
	file := Files.Old(filename);
	if (file # NIL)
		file.GetName(fullname);
	else{
		file := Files.New(filename); /* to get path */
		if (file # NIL){
			file.GetName(fullname);
			file := NIL;
		}
	}
	if (filenameEdit # NIL){
		filenameEdit.SetAsString(fullname);
		lastFilename := fullname;
	}
	text := editor.text;
	text.AcquireWrite;
	modified := TRUE; /* avoid the ! on the store button while loading */
	text.Delete(0, text.GetLength());
	editor.tv.firstLine.Set(0);
	text.ReleaseWrite;
	
	if (file # NIL) {
		if (format = "AUTO")
			decoder := TextUtilities.DecodeAuto(fullname, autoCodecFormat);
		else
			decoder := Codecs.GetTextDecoder(format);
		};
		
		if decoder # NIL {
			COPY(format, codecFormat);
			in := Codecs.OpenInputStream(fullname);
			if in # NIL {
				decoder.Open(in, res);
				if res = 0 {
					editor.text.onTextChanged.Remove(TextChanged);
					SetText(decoder.GetText());
					editor.text.onTextChanged.Add(TextChanged);
				};
			}else{
				msg := "Can't open input stream on file "; Utilities.Append(msg, fullname);
				WMDialogs.Error("Error", msg);
			};
		}else{
			msg := "No decoder for file "; Utilities.Append(msg, fullname);
			Utilities.Append(msg, " (Format: "); Utilities.Append(msg, format); Utilities.Append(msg, ")");
			WMDialogs.Error("Error", msg);
		};
		
	};
	
	SetFormatCaption(format);
	editor.tv.firstLine.Set(0);
	editor.tv.cursor.SetPosition(0);
	editor.tv.SetFocus;
	modified := FALSE;
	if (buttons * StoreButton # {}) { storeBtn.caption.SetAOC("Store") };
}
 
 