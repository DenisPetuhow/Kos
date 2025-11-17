#ifndef NEWORBOBJ_H
#define NEWORBOBJ_H

#include <QtCore/QVariant>
#include <QtGui>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

#include "ASD/asdtype.h"
#include "ASD/objfileparser.h"

class CNewOrbObj: public QDialog

{
Q_OBJECT

public:
        CNewOrbObj(QWidget* parent = 0);
	QWidget *Form;
	QTextCodec *c;
	QVector<ASDOrbitalObjectPar> obj_rez;
public slots:
	void accept();
protected slots:

	void setdattab();
	void setdatsys();
	void opentle();
	void settabtle();
	void chekparam1();
	void chekparam2();
	void chekparam3();
	void chekparam4();
	void chekparam5();
	void chekparam6();
private:
	// для Norad tle
	bool CheckSum(const QString ligne);
	void VerifieLignes(const QString &li1, const QString &li2);
	void parseTle(QString ligne1, QString ligne2, QString& _norad, double* a,
			double* nakl, double* w, double* M, double* E, double* l);
	QList<ASDOrbitalObjectPar> tleList;// Список для хранения Norad tle

	QGroupBox *groupBox_type;
	QGridLayout *gridLayout_2;
	QLabel *label_typeSYS;
	QComboBox *comboBox_typeSYS;
	QLabel *label_typedat;
	QComboBox *comboBox_typedat;
	QLabel *label_tle;
	QListWidget *listWidget_tle;
	QPushButton *pushButton_tle;
	QGroupBox *groupBox_edit;
	QLineEdit *lineEdit_namesys;
	QLineEdit *lineEdit_nameka;
	QLineEdit *lineEdit_par1_2;
	QLineEdit *lineEdit_par1;
	QDateTimeEdit *dateTimeEdit;
	QLabel *label_namesys;
	QLabel *label_name;
	QLabel *label_datetim;
	QLabel *label_par1;
	QLabel *label_par2;
	QLineEdit *lineEdit_par3;
	QLineEdit *lineEdit_par4;
	QLineEdit *lineEdit_par5;
	QLineEdit *lineEdit_par6;
	QLabel *label_par3;
	QLabel *label_par4;
	QLabel *label_par5;
	QLabel *label_par6;
	QGroupBox *groupBox_bck;
	QGridLayout *gridLayout;
	QLabel *label_typebsk;
	QLabel *label_namebck;
	QLineEdit *lineEdit_namebck;
	QLabel *label_gamma;
	QLineEdit *lineEdit_gamma;
	QLabel *label_alfa;
	QLineEdit *lineEdit_alfa;
	QLabel *label_tetta;
	QLineEdit *lineEdit_tetta;
	QComboBox *comboBox_typebck;
	QDialogButtonBox *buttonBox;

};

#endif // WIDGETADDORBOBJ_H
