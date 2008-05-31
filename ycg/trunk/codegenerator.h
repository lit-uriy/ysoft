#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QStringList>
#include <QString>



//=====================================================
//		
//=====================================================
bool GenerateCode(const QString &uifilename, const QString &classname, const QString &parentname)
{
//  int		errorLine;
//  int		errorColumn;
  bool		ok = false;  
  QFile		uifile(uifilename);
  QFileInfo fi(uifilename);
  QString	text;
  QString	clrname;	// ������ ���, ��� ����������
  QString	outname;
  QString	outfullname;
  QString	path;
  QFile		outfile;
  QFile		templatefile;
  QTextStream	stream;


	// ����������� ��� ����� �� *.ui � *
	path = fi.dir().absolutePath();	
	//qDebug() << "File path: " << path << "\n\r";	
	clrname = fi.completeBaseName();
	//qDebug() << "File name: " << clrname << "\n\r";


// ���������� ���� ����������
	outname = clrname + ".cpp";
	//qDebug() << "File outname: " << outname << "\n\r";
	outfullname = path + QDir::separator () + outname;
	
	// ��������� ���� �������
	templatefile.setFileName(":/res/[uiclassname].cpp");
	ok = templatefile.open(QIODevice::ReadOnly);
	if (!ok)
	{
		qDebug() << "Error opening tamplate" << "\n\r";
		return ok;
	}

	stream.setDevice(&templatefile);

	// ������ ���� �������
	text = stream.readAll();
	

	if (stream.status() != QTextStream::Ok)
	{
		ok = false;
		qDebug() << "Error reading tamplate" << "\n\r";
	}
	
	templatefile.close();
	
	// �������� ������ � �������
		// ��� �����
	text.replace("[classname]", clrname);
		// ��� ������
	text.replace("[ClassName]", classname);
		// ��� ������������� ������
	text.replace("[ParentClass]", parentname);
	
	
	// ������� ���� ����������
	outfile.setFileName(outfullname);
	if (outfile.exists())
	{
		qDebug() << "File " << outfullname << " already exist" << "\n\r";
		return false;
	}
	
	ok = outfile.open(QIODevice::WriteOnly);
	if (!ok)
	{
		qDebug() << "Error open file";
		return ok;
	}
	// ��������� ����������������� ������ � �������� ����
	stream.setDevice(&outfile);
	stream << text;
	outfile.close();
	if (stream.status() != QTextStream::Ok)
	{
		ok = false;
		qDebug() << "Error writing output" << "\n\r";
	}	

// ���������� ���� ����������
	outname = clrname + ".h";
	//qDebug() << "File outname: " << outname << "\n\r";
	outfullname = path + QDir::separator () + outname;
	
	// ��������� ���� �������
	templatefile.setFileName(":/res/[uiclassname].h");
	ok = templatefile.open(QIODevice::ReadOnly);
	if (!ok)
	{
		qDebug() << "Error opening tamplate" << "\n\r";
		return ok;
	}

	stream.setDevice(&templatefile);

	// ������ ���� �������
	text = stream.readAll();

	if (stream.status() != QTextStream::Ok)
	{
		ok = false;
		qDebug() << "Error reading tamplate" << "\n\r";
	}
	
	templatefile.close();
	
	// �������� ������ � �������
		// ��� �����
	text.replace("[classname]", clrname);
		// define
	text.replace("[CLASSNAME]", clrname.toUpper());	
		// ��� ������
	text.replace("[ClassName]", classname);
		// ��� ������������� ������
	text.replace("[ParentClass]", parentname);
	//qDebug() << text << "\n\r";
	
	// ������� ���� ����������
	outfile.setFileName(outfullname);
	if (outfile.exists())
	{
		qDebug() << "File " << outfullname << " already exist" << "\n\r";
		return false;
	}
	
	ok = outfile.open(QIODevice::WriteOnly);
	if (!ok)
	{
		qDebug() << "Error open file";
		return ok;
	}
	// ��������� ����������������� ������ � �������� ����
	stream.setDevice(&outfile);
	stream << text;
	outfile.close();

	if (stream.status() != QTextStream::Ok)
	{
		ok = false;
		qDebug() << "Error writing output" << "\n\r";
	}

    return ok;
}
