#include "neworbobj.h"
#include <QDebug>
#include <math.h>
#include <QFileDialog>
#include <QTextCodec>
#include <QValidator>
#include <QRegExp>
#include <QMessageBox>

CNewOrbObj::CNewOrbObj(QWidget *parent) :
	QDialog(parent)

{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("windows-1251"));
	resize(650, 500);
	//   Dialog_addorbobj->setModal(true);
	QGridLayout *gridLayout_3;
	QGridLayout *gridLayout_4;
	gridLayout_3 = new QGridLayout(this);
	gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
	groupBox_type = new QGroupBox(this);
	groupBox_type->setObjectName(QString::fromUtf8("groupBox_type"));
	gridLayout_2 = new QGridLayout(groupBox_type);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	label_typeSYS = new QLabel(groupBox_type);
	label_typeSYS->setObjectName(QString::fromUtf8("label_typeSYS"));

	gridLayout_2->addWidget(label_typeSYS, 0, 0, 1, 1);

	comboBox_typeSYS = new QComboBox(groupBox_type);
	comboBox_typeSYS->setObjectName(QString::fromUtf8("comboBox_typeSYS"));

	gridLayout_2->addWidget(comboBox_typeSYS, 1, 0, 1, 1);

	label_typedat = new QLabel(groupBox_type);
	label_typedat->setObjectName(QString::fromUtf8("label_typedat"));

	gridLayout_2->addWidget(label_typedat, 2, 0, 1, 1);

	comboBox_typedat = new QComboBox(groupBox_type);
	comboBox_typedat->setObjectName(QString::fromUtf8("comboBox_typedat"));

	gridLayout_2->addWidget(comboBox_typedat, 3, 0, 1, 1);

	label_tle = new QLabel(groupBox_type);
	label_tle->setObjectName(QString::fromUtf8("label_tle"));

	gridLayout_2->addWidget(label_tle, 4, 0, 1, 1);

	listWidget_tle = new QListWidget(groupBox_type);
	listWidget_tle->setObjectName(QString::fromUtf8("listWidget_tle"));

	gridLayout_2->addWidget(listWidget_tle, 5, 0, 1, 1);

	pushButton_tle = new QPushButton(groupBox_type);
	pushButton_tle->setObjectName(QString::fromUtf8("pushButton_tle"));

	gridLayout_2->addWidget(pushButton_tle, 6, 0, 1, 1);

	gridLayout_3->addWidget(groupBox_type, 0, 0, 1, 1);

	groupBox_edit = new QGroupBox(this);
	groupBox_edit->setObjectName(QString::fromUtf8("groupBox_edit"));
	gridLayout_4 = new QGridLayout(groupBox_edit);
	gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
	label_namesys = new QLabel(groupBox_edit);
	label_namesys->setObjectName(QString::fromUtf8("label_namesys"));

	gridLayout_4->addWidget(label_namesys, 0, 0, 1, 1);

	lineEdit_namesys = new QLineEdit(groupBox_edit);
	lineEdit_namesys->setObjectName(QString::fromUtf8("lineEdit_namesys"));

	gridLayout_4->addWidget(lineEdit_namesys, 0, 1, 1, 1);

	label_name = new QLabel(groupBox_edit);
	label_name->setObjectName(QString::fromUtf8("label_name"));

	gridLayout_4->addWidget(label_name, 1, 0, 1, 1);

	lineEdit_nameka = new QLineEdit(groupBox_edit);
	lineEdit_nameka->setObjectName(QString::fromUtf8("lineEdit_nameka"));

	gridLayout_4->addWidget(lineEdit_nameka, 1, 1, 1, 1);

	label_datetim = new QLabel(groupBox_edit);
	label_datetim->setObjectName(QString::fromUtf8("label_datetim"));

	gridLayout_4->addWidget(label_datetim, 2, 0, 1, 1);

	dateTimeEdit = new QDateTimeEdit(groupBox_edit);
	dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));

	gridLayout_4->addWidget(dateTimeEdit, 2, 1, 1, 1);

	label_par1 = new QLabel(groupBox_edit);
	label_par1->setObjectName(QString::fromUtf8("label_par1"));

	gridLayout_4->addWidget(label_par1, 3, 0, 1, 1);

	lineEdit_par1 = new QLineEdit(groupBox_edit);
	lineEdit_par1->setObjectName(QString::fromUtf8("lineEdit_par1"));

	gridLayout_4->addWidget(lineEdit_par1, 3, 1, 1, 1);

	label_par2 = new QLabel(groupBox_edit);
	label_par2->setObjectName(QString::fromUtf8("label_par2"));

	gridLayout_4->addWidget(label_par2, 4, 0, 1, 1);

	lineEdit_par1_2 = new QLineEdit(groupBox_edit);
	lineEdit_par1_2->setObjectName(QString::fromUtf8("lineEdit_par1_2"));

	gridLayout_4->addWidget(lineEdit_par1_2, 4, 1, 1, 1);

	label_par3 = new QLabel(groupBox_edit);
	label_par3->setObjectName(QString::fromUtf8("label_par3"));

	gridLayout_4->addWidget(label_par3, 5, 0, 1, 1);

	lineEdit_par3 = new QLineEdit(groupBox_edit);
	lineEdit_par3->setObjectName(QString::fromUtf8("lineEdit_par3"));

	gridLayout_4->addWidget(lineEdit_par3, 5, 1, 1, 1);

	label_par4 = new QLabel(groupBox_edit);
	label_par4->setObjectName(QString::fromUtf8("label_par4"));

	gridLayout_4->addWidget(label_par4, 6, 0, 1, 1);

	lineEdit_par4 = new QLineEdit(groupBox_edit);
	lineEdit_par4->setObjectName(QString::fromUtf8("lineEdit_par4"));

	gridLayout_4->addWidget(lineEdit_par4, 6, 1, 1, 1);

	label_par5 = new QLabel(groupBox_edit);
	label_par5->setObjectName(QString::fromUtf8("label_par5"));

	gridLayout_4->addWidget(label_par5, 7, 0, 1, 1);

	lineEdit_par5 = new QLineEdit(groupBox_edit);
	lineEdit_par5->setObjectName(QString::fromUtf8("lineEdit_par5"));

	gridLayout_4->addWidget(lineEdit_par5, 7, 1, 1, 1);

	label_par6 = new QLabel(groupBox_edit);
	label_par6->setObjectName(QString::fromUtf8("label_par6"));

	gridLayout_4->addWidget(label_par6, 8, 0, 1, 1);

	lineEdit_par6 = new QLineEdit(groupBox_edit);
	lineEdit_par6->setObjectName(QString::fromUtf8("lineEdit_par6"));

	gridLayout_4->addWidget(lineEdit_par6, 8, 1, 1, 1);

	groupBox_bck = new QGroupBox(groupBox_edit);
	groupBox_bck->setObjectName(QString::fromUtf8("groupBox_bck"));
	groupBox_bck->setCheckable(true);
	gridLayout = new QGridLayout(groupBox_bck);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	label_typebsk = new QLabel(groupBox_bck);
	label_typebsk->setObjectName(QString::fromUtf8("label_typebsk"));

	gridLayout->addWidget(label_typebsk, 0, 0, 1, 1);

	label_namebck = new QLabel(groupBox_bck);
	label_namebck->setObjectName(QString::fromUtf8("label_namebck"));

	gridLayout->addWidget(label_namebck, 1, 0, 1, 1);

	lineEdit_namebck = new QLineEdit(groupBox_bck);
	lineEdit_namebck->setObjectName(QString::fromUtf8("lineEdit_namebck"));

	gridLayout->addWidget(lineEdit_namebck, 1, 1, 1, 3);

	label_gamma = new QLabel(groupBox_bck);
	label_gamma->setObjectName(QString::fromUtf8("label_gamma"));

	gridLayout->addWidget(label_gamma, 2, 0, 1, 2);

	lineEdit_gamma = new QLineEdit(groupBox_bck);
	lineEdit_gamma->setObjectName(QString::fromUtf8("lineEdit_gamma"));

	gridLayout->addWidget(lineEdit_gamma, 2, 3, 1, 1);

	label_alfa = new QLabel(groupBox_bck);
	label_alfa->setObjectName(QString::fromUtf8("label_alfa"));

	gridLayout->addWidget(label_alfa, 3, 0, 1, 3);

	lineEdit_alfa = new QLineEdit(groupBox_bck);
	lineEdit_alfa->setObjectName(QString::fromUtf8("lineEdit_alfa"));

	gridLayout->addWidget(lineEdit_alfa, 3, 3, 1, 1);

	label_tetta = new QLabel(groupBox_bck);
	label_tetta->setObjectName(QString::fromUtf8("label_tetta"));

	gridLayout->addWidget(label_tetta, 4, 0, 1, 3);

	lineEdit_tetta = new QLineEdit(groupBox_bck);
	lineEdit_tetta->setObjectName(QString::fromUtf8("lineEdit_tetta"));

	gridLayout->addWidget(lineEdit_tetta, 4, 3, 1, 1);

	comboBox_typebck = new QComboBox(groupBox_bck);
	comboBox_typebck->setObjectName(QString::fromUtf8("comboBox_typebck"));

	gridLayout->addWidget(comboBox_typebck, 0, 2, 1, 1);

	gridLayout_4->addWidget(groupBox_bck, 9, 0, 1, 2);

	gridLayout_3->addWidget(groupBox_edit, 0, 1, 1, 1);

	buttonBox = new QDialogButtonBox(this);
	buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel
			| QDialogButtonBox::Ok);

	gridLayout_3->addWidget(buttonBox, 1, 1, 1, 1);

	buttonBox = new QDialogButtonBox(this);
	buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel
			| QDialogButtonBox::Ok);

	gridLayout_3->addWidget(buttonBox, 1, 1, 1, 1);

	setWindowTitle(QObject::trUtf8("Добавление орбитального объекта"));

	groupBox_type->setTitle(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\242\320\270\320\277 \320\275\320\260\321\207\320\260\321\207\320\260\320\273\321\214\320\275\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205",
                    0));
	label_typeSYS->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\222\321\213\320\261\320\276\321\200 \321\202\320\270\320\277\320\260 \321\201\320\270\321\201\321\202\320\265\320\274\321\213",
                    0 ));

	comboBox_typeSYS->setWhatsThis(
			QApplication::translate(
					"Dialog_addorbobj",
					"<html><head/><body><p>\320\222\321\213\320\261\320\276\321\200 \321\202\320\270\320\277\320\260 \320\272\320\276\321\201\320\274\320\270\321\207\320\265\321\201\320\272\320\276\320\271 \321\201\320\270\321\201\321\202\320\265\320\274\321\213</p></body></html>",
                    0 ));

	label_typedat->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\222\321\213\320\261\320\276\321\200 \321\202\320\270\320\277\320\260 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205",
                    0 ));
	comboBox_typedat->clear();
	comboBox_typedat->insertItems(
			0,
			QStringList()
					<< QApplication::translate(
							"Dialog_addorbobj",
							"\320\232\320\265\320\277\320\273\320\265\321\200\320\276\320\262\321\201\320\272\320\270\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\321\213",
                            0 )
					<< QApplication::translate(
							"Dialog_addorbobj",
							"\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\262 \320\220\320\223\320\241\320\232",
                            0 )
					<< QApplication::translate(
							"Dialog_addorbobj",
							"NORAD tle \321\204\320\276\321\200\320\274\320\260\321\202",
                            0));

	comboBox_typedat->setWhatsThis(
			QApplication::translate(
					"Dialog_addorbobj",
					"<html><head/><body><p>\320\222\321\213\320\261\320\276\321\200 \321\202\320\270\320\277\320\260 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205 \320\272\320\276\321\201\320\274\320\270\321\207\320\265\321\201\320\272\320\276\320\263\320\276 \320\276\320\261\321\212\320\265\320\272\321\202\320\260</p></body></html>",
                    0));

	label_tle->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 Tle",
                    0));

	listWidget_tle->setWhatsThis(
			QApplication::translate(
					"Dialog_addorbobj",
					"<html><head/><body><p>\320\241\320\277\320\270\321\201\320\276\320\272 \320\232\320\220 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 tle NORAD, \321\201\320\276\320\264\320\265\321\200\320\266\320\260\321\211\320\270\321\205\321\201\321\217 \320\262 \321\204\320\260\320\271\320\273\320\265</p></body></html>",
                    0));

	pushButton_tle->setWhatsThis(
			QApplication::translate(
					"Dialog_addorbobj",
					"<html><head/><body><p>\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \320\264\320\260\320\275\320\275\321\213\321\205 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 tle NORAD</p></body></html>",
                    0));

	pushButton_tle->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265 Tle",
                    0));

	groupBox_edit->setWhatsThis(
			QApplication::translate(
					"Dialog_addorbobj",
					"<html><head/><body><p>\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205</p></body></html>",
                    0));

	groupBox_edit->setTitle(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262",
                    0));
	label_namesys->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\213",
                    0));
	label_name->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265  \320\232\320\220",
                    0));
	label_datetim->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\224\320\260\321\202\320\260 \320\270 \320\262\321\200\320\265\320\274\321\217",
                    0));

	label_par1->setText(QObject::trUtf8("Большая полуось,км"));
	label_par2->setText(QObject::trUtf8("Эксцентриситет"));
	label_par3->setText(QObject::trUtf8("Наклонение,град"));
	label_par4->setText(QObject::trUtf8("Долгота ВУ,град"));
	label_par5->setText(QObject::trUtf8("Аргумент Широты,град"));
	label_par6->setText(QObject::trUtf8("Аргумент Перигея,град"));

	groupBox_bck->setTitle(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\276\321\207\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265 \320\221\320\241\320\232",
                    0));
	label_typebsk->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\242\320\270\320\277 \320\260\320\277\320\277\320\260\321\200\320\260\321\202\321\203\321\200\321\213",
                    0));
	label_namebck->setText(QApplication::translate("Dialog_addorbobj",
			"\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265",
            0));
#ifndef QT_NO_TOOLTIP
	lineEdit_namebck->setToolTip(
			QApplication::translate(
					"Dialog_addorbobj",
					"<html><head/><body><p>\320\222\320\262\320\276\320\264 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\321\217 \320\260\320\277\320\277\320\260\321\200\320\260\321\202\321\203\321\200\321\213</p></body></html>",
                    0));
#endif // QT_NO_TOOLTIP
	label_gamma->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\243\320\263\320\276\320\273 \320\277\320\276\320\273\321\203\321\200\320\260\321\201\321\202\320\262\320\276\321\200\320\260, \320\263\321\200\320\260\320\264",
                    0));
	label_alfa->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\243\321\201\321\202. \321\203\320\263\320\276\320\273 \320\262 \320\263\320\276\321\200\320\270\320\267. \320\277\320\273\320\276\321\201\320\272\320\276\321\201\321\202\320\270, \320\263\321\200\320\260\320\264",
                    0));
	label_tetta->setText(
			QApplication::translate(
					"Dialog_addorbobj",
					"\320\243\321\201\321\202. \321\203\320\263\320\276\320\273 \320\262 \320\262\320\265\321\200\321\202. \320\277\320\273\320\276\321\201\320\272\320\276\321\201\321\202\320\270, \320\263\321\200\320\260\320\264",
                    0));
#ifndef QT_NO_TOOLTIP
	comboBox_typebck->setToolTip(
			QApplication::translate(
					"Dialog_addorbobj",
					"<html><head/><body><p>\320\222\321\213\320\261\320\276\321\200 \321\202\320\270\320\277\320\260 \320\260\320\277\320\277\320\260\321\200\320\260\321\202\321\203\321\200\321\213</p></body></html>",
                    0));
#endif // QT_NO_TOOLTIP
	//end ui;
	// slot
	QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	// Загрузка tle данных
	QObject::connect(pushButton_tle, SIGNAL(clicked()), this, SLOT(opentle()));
	// выбор типа исходных данных
	QObject::connect(comboBox_typeSYS, SIGNAL(activated(QString)), this,
			SLOT(setdatsys()));
	QObject::connect(comboBox_typedat, SIGNAL(activated(QString)), this,
			SLOT(setdattab()));
	// Выбор ВСК
	// QObject::connect(pushButton_tle, SIGNAL(toggled(bool)), this, SLOT(setdatBSK()));

	//  QObject::connect(radioButton_tle, SIGNAL(toggled(bool)), groupBox_tle, SLOT(setEnabled(bool)));
	//

	QObject::connect(listWidget_tle, SIGNAL(itemClicked(QListWidgetItem*)),
			this, SLOT(settabtle()));
	// end slot
	pushButton_tle->setEnabled(false);
	listWidget_tle->setEnabled(false);
	// проверка
	QObject::connect(lineEdit_par1, SIGNAL( textChanged (const QString &)),
			this, SLOT(chekparam1()));
	QObject::connect(lineEdit_par1_2, SIGNAL( textChanged (const QString &)),
			this, SLOT(chekparam2()));
	QObject::connect(lineEdit_par3, SIGNAL( textChanged (const QString &)),
			this, SLOT(chekparam3()));
	QObject::connect(lineEdit_par4, SIGNAL( textChanged (const QString &)),
			this, SLOT(chekparam4()));
	QObject::connect(lineEdit_par5, SIGNAL( textChanged (const QString &)),
			this, SLOT(chekparam5()));
	QObject::connect(lineEdit_par6, SIGNAL( textChanged (const QString &)),
			this, SLOT(chekparam6()));
}

// Проверка ввода текста
void CNewOrbObj::chekparam1()
{
	if (comboBox_typedat->currentIndex() == 0)
	{

		lineEdit_par1->setValidator(
				new QDoubleValidator(0.0, 190000.0, 4, this));
		if (lineEdit_par1->text().toDouble() > 190000)
			lineEdit_par1->setText(" ");

	}

	if (comboBox_typedat->currentIndex() == 1)
	{

		lineEdit_par1->setValidator(new QDoubleValidator(-100000.0, 100000.0,
				4, this));
		if (fabs(lineEdit_par1->text().toDouble()) > 100000.0)
			lineEdit_par1->setText(" ");
	}

}

void CNewOrbObj::chekparam2()
{
	if (comboBox_typedat->currentIndex() == 0)
	{
		lineEdit_par1_2->setValidator(new QDoubleValidator(0.0, 1.0, 4, this));
		if (lineEdit_par1_2->text().toDouble() > 1)
			lineEdit_par1_2->setText(" ");

	}
	if (comboBox_typedat->currentIndex() == 1)
	{

		lineEdit_par1_2->setValidator(new QDoubleValidator(-100000.0, 100000.0,
				4, this));
		if (fabs(lineEdit_par1_2->text().toDouble()) > 100000.0)
			lineEdit_par1_2->setText(" ");
	}
}

void CNewOrbObj::chekparam3()
{
	if (comboBox_typedat->currentIndex() == 0)
	{
		lineEdit_par3->setValidator(new QDoubleValidator(0.0, 180.0, 4, this));
		if (lineEdit_par3->text().toDouble() > 180)
			lineEdit_par3->setText(" ");
	}
	if (comboBox_typedat->currentIndex() == 1)
	{

		lineEdit_par3->setValidator(new QDoubleValidator(-100000.0, 100000.0,
				4, this));
		if (fabs(lineEdit_par3->text().toDouble()) > 100000.0)
			lineEdit_par3->setText(" ");
	}

}

void CNewOrbObj::chekparam4()
{
	if (comboBox_typedat->currentIndex() == 0)
	{

		lineEdit_par4->setValidator(new QDoubleValidator(0.0, 360.0, 4, this));
		if (lineEdit_par4->text().toDouble() > 360)
			lineEdit_par4->setText(" ");
	}
	if (comboBox_typedat->currentIndex() == 1)
	{

		lineEdit_par4->setValidator(new QDoubleValidator(-1000.0, 1000.0, 4,
				this));
		if (fabs(lineEdit_par4->text().toDouble()) > 100000.0)
			lineEdit_par4->setText(" ");

	}

}
void CNewOrbObj::chekparam5()
{
	if (comboBox_typedat->currentIndex() == 0)
	{

		lineEdit_par5->setValidator(new QDoubleValidator(0.0, 360.0, 4, this));
	}
	if (comboBox_typedat->currentIndex() == 1)
	{

		lineEdit_par5->setValidator(new QDoubleValidator(-1000.0, 1000.0, 4,
				this));
		if (fabs(lineEdit_par5->text().toDouble()) > 100000.0)
			lineEdit_par5->setText(" ");
	}

}

void CNewOrbObj::chekparam6()
{
	if (comboBox_typedat->currentIndex() == 0)
	{

		lineEdit_par6->setValidator(new QDoubleValidator(0.0, 360.0, 4, this));
		if (fabs(lineEdit_par6->text().toDouble()) > 360.0)
			lineEdit_par6->setText(" ");

	}
	if (comboBox_typedat->currentIndex() == 1)
	{

		lineEdit_par6->setValidator(new QDoubleValidator(-1000.0, 1000.0, 4,
				this));
		if (fabs(lineEdit_par6->text().toDouble()) > 1000.0)
			lineEdit_par6->setText(" ");
	}
}

// закрытие формы
void CNewOrbObj::accept()
{
	update();
	//	qDebug() << "qwe=====";
	ASDOrbitalObjectPar obj;
	obj.type_dat = static_cast<InitDataType>(comboBox_typedat->currentIndex());
	obj.nameSys = lineEdit_namesys->text();
	obj.type = static_cast<BseType>(comboBox_typeSYS->currentIndex());
	ASDBsePar bsa;
	// ПРОВЕРКА ВВОДА??????
	//if()
	bsa.alfaMounting = lineEdit_alfa->text().toDouble();
	bsa.gamma = lineEdit_gamma->text().toDouble();
	bsa.etaMounting = lineEdit_tetta->text().toDouble();
	obj.bsa.push_back(bsa);

	if (obj.type_dat == 0)
	{
		//		qDebug() << "lineEdit_par1->text()=" << lineEdit_par1->text()
		//				<< lineEdit_par1->text().toDouble();
		if ((lineEdit_par1->text().toDouble() < 0)
				|| (lineEdit_par1->text().toDouble() > 190000))
		{
			QString s1 =
					QString::fromUtf8("Неправильно задана большая полуось");
			QMessageBox::warning(this, QObject::trUtf8("Ошибка ввода"), s1);
			lineEdit_par1->setText("");
			return;
		}

		obj.kep.name = lineEdit_nameka->text();
		obj.kep.t_epoch = dateTimeEdit->dateTime();
		obj.kep.a = lineEdit_par1->text().toDouble();
		obj.kep.e = lineEdit_par1_2->text().toDouble();
		obj.kep.i = lineEdit_par3->text().toDouble();
		obj.kep.l = lineEdit_par4->text().toDouble();
		obj.kep.u = lineEdit_par5->text().toDouble();
		obj.kep.omega = lineEdit_par6->text().toDouble();
	}
	if (obj.type_dat == 1)
	{

		obj.ags.name = lineEdit_nameka->text();
		obj.ags.t_epoch = dateTimeEdit->dateTime();
		obj.ags.x = lineEdit_par1->text().toDouble();
		obj.ags.y = lineEdit_par1_2->text().toDouble();
		obj.ags.z = lineEdit_par3->text().toDouble();
		obj.ags.vx = lineEdit_par4->text().toDouble();
		obj.ags.vy = lineEdit_par5->text().toDouble();
		obj.ags.vz = lineEdit_par6->text().toDouble();
	}
	if (obj.type_dat == 2)
	{
		QListWidgetItem *___qlistwidgetitem = listWidget_tle->currentItem();
		QString line = ___qlistwidgetitem->text();
		QString lin0;
		QString lin1;
		QString lin2;
		for (int i = 0; i < tleList.size(); i++)
		{
			lin0 = tleList.at(i).stle.satName;
			lin1 = tleList.at(i).stle.firstString;
			lin2 = tleList.at(i).stle.secondString;

			if (line == lin0)
			{

				obj.stle.satName = lin0;
				obj.stle.firstString = lin1;
				obj.stle.secondString = lin2;
				//				qDebug() << "obj tle==" << lin0;
			}
		}

	}
	obj_rez.push_back(obj);

	QDialog::accept();

}
// Открытие tle файла
void CNewOrbObj::opentle()
{

	listWidget_tle->setEnabled(true);

	ASDOrbitalObjectPar obj;

	obj.type_dat = TLE;
	QFileDialog::Options options;
	// QCheckBox *native;
	//   if (!native->isChecked())
	options |= QFileDialog::DontUseNativeDialog;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
			QObject::trUtf8("Файл с данными в формате tle "),
			// openFileNameLabel->text(),
			// filename_navatel_gps,
			"", QObject::trUtf8("tle Files (*.txt);;All Files (*)"),
			&selectedFilter, options);
	if (!fileName.isEmpty())
	{
		//    _fileNovatelObsLineEdit->setText(fileName);
		//qDebug()<<"file====";
		QFile fSatellites(fileName.toStdString().c_str());

		fSatellites.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream flux(&fSatellites);
		int j;
		QString nomsat;

		j = 0;
		nomsat = "---";
		while (!flux.atEnd())
		{

			const QString ligne = flux.readLine();

			if (ligne.mid(0, 2) == "1 ")
			{

				QString li1, li2;
				li1 = ligne;
				do
				{
					li2 = flux.readLine();
				} while (li2.trimmed().length() == 0);

				obj.stle.satName = nomsat;
				obj.stle.firstString = li1;
				obj.stle.secondString = li2;
				obj.nameSys = "tle";
				obj.type = UN;
				obj.type_dat = TLE;
				tleList.append(obj);

			}
			else
			{
				nomsat = ligne.trimmed();
				//  qDebug()<<"ddddd  nomsat="<<nomsat;
				listWidget_tle->addItem(nomsat);
			}
		}
		fSatellites.close();

		//} catch (PreviSatException &e) {
		//  }

		// }

	}

}
// Выбор типа системы
void CNewOrbObj::setdatsys()
{

}
void CNewOrbObj::settabtle()
{
	QListWidgetItem *___qlistwidgetitem = listWidget_tle->currentItem();
	QString line;
	QString lin0;
	QString lin1;
	QString lin2;
	/*
	 QTableWidgetItem *___qtablewidgetitem =  new QTableWidgetItem();//tabView_tle->horizontalHeaderItem(0);
	 ___qtablewidgetitem->setText(QObject::trUtf8("Параметр"));
	 QTableWidgetItem *___qtablewidgetitem1 =new QTableWidgetItem();// tabView_tle->horizontalHeaderItem(1);

	 ___qtablewidgetitem1->setText( QObject::trUtf8("Значение"));
	 tabView_tle->setHorizontalHeaderItem(0, ___qtablewidgetitem);

	 tabView_tle->setHorizontalHeaderItem(1, ___qtablewidgetitem1);
	 if (tabView_tle->rowCount() < 5)
	 tabView_tle->setRowCount(5);
	 */

	line = ___qlistwidgetitem->text();

	for (int i = 0; i < tleList.size(); i++)
	{
		lin0 = tleList.at(i).stle.satName;
		lin1 = tleList.at(i).stle.firstString;
		lin2 = tleList.at(i).stle.secondString;

		if (line == lin0)
		{

			double a, nakl, W, M, E, l;
			QString norad;

			//tabView_tle->update();

			parseTle(lin1, lin2, norad, &a, &nakl, &W, &M, &E, &l);
			dateTimeEdit->setEnabled(false);
			lineEdit_par1->setText(norad.toUtf8());
			lineEdit_par1_2->setText(QString("%1").arg(a));
			lineEdit_par3->setText(QString("%1").arg(nakl));
			lineEdit_par4->setText(QString("%1").arg(l));
			lineEdit_par5->setText(QString("%1").arg(E));
			lineEdit_par6->setText(QString("%1").arg(W));
			label_par1->setText(QObject::trUtf8("Номер NORAD"));
			label_par2->setText(QObject::trUtf8("Большая полуось,км"));
			label_par3->setText(QObject::trUtf8("Наклонение, град"));
			label_par4->setText(QObject::trUtf8("Долгота В.У., град"));
			label_par5->setText(QObject::trUtf8("Эксцентриситет"));
			label_par6->setText(QObject::trUtf8("Аргумент перигея, град"));
			//lineEdit_par1->setAttribute(Qt::);
			lineEdit_par1->setReadOnly(true);
			lineEdit_par1_2->setReadOnly(true);
			lineEdit_par3->setReadOnly(true);
			lineEdit_par4->setReadOnly(true);
			lineEdit_par5->setReadOnly(true);
			lineEdit_par6->setReadOnly(true);
			//addMass(model,0,QObject::trUtf8("Номер NORAD"),norad);
			//addMass(model,1,QObject::trUtf8("Большая полуось"),QString("%1").arg(a));
			//addMass(model,2,QObject::trUtf8("Наклонение"),QString("%1").arg(nakl));
			//addMass(model,3,QObject::trUtf8("Долгота В.У."),QString("%1").arg(l));
			//addMass(model,4,QObject::trUtf8("Эксцентриситет"),QString("%1").arg(E));
			//addMass(model,5,QObject::trUtf8("Аргумент перигея"),QString("%1").arg(W));
			//addMass(model,6,QObject::trUtf8("Средняя аномалия"),QString("%1").arg(M));
			//  tableView->setModel(model);
			//  tableView->setItemDelegate(delegate);
			//  tableView->setEnabled(true);
			//  tableView->update();

		}
	}
}

// Выбор типа исходных данных
void CNewOrbObj::setdattab()
{
	if (comboBox_typedat->currentIndex() == 0)
	{
		lineEdit_par1->setReadOnly(false);
		lineEdit_par1_2->setReadOnly(false);
		lineEdit_par3->setReadOnly(false);
		lineEdit_par4->setReadOnly(false);
		lineEdit_par5->setReadOnly(false);
		lineEdit_par6->setReadOnly(false);

		label_par1->setText(QObject::trUtf8("Большая полуось,км"));
		label_par2->setText(QObject::trUtf8("Эксцентриситет"));
		label_par3->setText(QObject::trUtf8("Наклонение,град"));
		label_par4->setText(QObject::trUtf8("Долгота ВУ,град"));
		label_par5->setText(QObject::trUtf8("Аргумент Широты,град"));
		label_par6->setText(QObject::trUtf8("Аргумент Перигея,град"));
		lineEdit_par1->setText("");
		lineEdit_par1_2->setText("");
		lineEdit_par3->setText("");
		lineEdit_par4->setText("");
		lineEdit_par5->setText("");
		lineEdit_par6->setText("");
		dateTimeEdit->setDateTime(QDateTime::currentDateTime());
		lineEdit_nameka->setText("");

		listWidget_tle->setEnabled(false);
		pushButton_tle->setEnabled(false);
		dateTimeEdit->setEnabled(true);
		lineEdit_nameka->setEnabled(true);

	}
	if (comboBox_typedat->currentIndex() == 1)
	{
		lineEdit_par1->setReadOnly(false);
		lineEdit_par1_2->setReadOnly(false);
		lineEdit_par3->setReadOnly(false);
		lineEdit_par4->setReadOnly(false);
		lineEdit_par5->setReadOnly(false);
		lineEdit_par6->setReadOnly(false);
		label_par1->setText(QObject::trUtf8("Х, км"));
		label_par2->setText(QObject::trUtf8("Y, км"));
		label_par3->setText(QObject::trUtf8("Z, км"));
		label_par4->setText(QObject::trUtf8("Vx, км/c"));
		label_par5->setText(QObject::trUtf8("Vy, км/c"));
		label_par6->setText(QObject::trUtf8("Vz, км/c"));

		lineEdit_par1->setText("");
		lineEdit_par1_2->setText("");
		lineEdit_par3->setText("");
		lineEdit_par4->setText("");
		lineEdit_par5->setText("");
		lineEdit_par6->setText("");
		dateTimeEdit->setDateTime(QDateTime::currentDateTime());
		lineEdit_nameka->setText("");
		pushButton_tle->setEnabled(false);
		listWidget_tle->setEnabled(false);
		dateTimeEdit->setEnabled(true);
		lineEdit_nameka->setEnabled(true);
	}
	if (comboBox_typedat->currentIndex() == 2)
	{
		label_par1->setText(QObject::trUtf8(""));
		label_par2->setText(QObject::trUtf8(""));
		label_par3->setText(QObject::trUtf8(""));
		label_par4->setText(QObject::trUtf8(""));
		label_par5->setText(QObject::trUtf8(""));
		label_par6->setText(QObject::trUtf8(""));

		lineEdit_par1->setText("");
		lineEdit_par1_2->setText("");
		lineEdit_par3->setText("");
		lineEdit_par4->setText("");
		lineEdit_par5->setText("");
		lineEdit_par6->setText("");
		dateTimeEdit->setDateTime(QDateTime::currentDateTime());
		lineEdit_nameka->setText("");
		pushButton_tle->setEnabled(true);
		listWidget_tle->setEnabled(true);
		dateTimeEdit->setEnabled(false);
		lineEdit_nameka->setEnabled(false);
	}

}
void CNewOrbObj::parseTle(QString ligne1, QString ligne2, QString& _norad,
		double* a, double* nakl, double* w, double* M, double* E, double* l)
{
	/* Declarations des variables locales */
	// int an, ibe;
	// double jrs;

	/* Initialisations */

	/* Corps du constructeur */
	QString _ligne1 = ligne1;
	QString _ligne2 = ligne2;

	// Numero NORAD
	_norad = _ligne1.mid(2, 5);
	//	qDebug() << "norad==" << _norad;
	// Epoque

	// Coefficient pseudo-balistique
	double _bstar = _ligne1.mid(53, 6).toDouble();
	int ibe = _ligne1.mid(59, 2).toInt();
	_bstar *= 1.e-5 * pow(10., ibe);

	// Elements orbitaux moyens
	// Inclinaison
	double _inclo = _ligne2.mid(8, 8).toDouble();

	// Ascension droite du noeud ascendant
	double _omegao = _ligne2.mid(17, 8).toDouble();

	// Excentricite
	double _ecco = 1.e-7 * _ligne2.mid(26, 7).toDouble();

	// Argument du perigee
	double _argpo = _ligne2.mid(34, 8).toDouble();

	// Anomalie moyenne
	double _mo = _ligne2.mid(43, 8).toDouble();

	// Moyen mouvement
	double _no = _ligne2.mid(52, 11).toDouble();

	//	qDebug() << "_no==" << _no;
	*nakl = _inclo;
	*w = _argpo;
	*M = _mo;
	*E = _ecco;
	*l = _omegao;
	;
	double a2 = pow((sqrt(398600.8) / (M_PI * 2 / (86400. / _no))), 2. / 3.);

	*a = a2;

	//
	return;
}
void CNewOrbObj::VerifieLignes(const QString &li1, const QString &li2)
{
	/* Declarations des variables locales */
	int exc, ierr;

	/* Initialisations */
	exc = 0;
	ierr = 0;

	/* Corps de la methode */
	// Verification de la longueur des lignes
	if (li1.size() != 69 || li2.size() != 69)
	{
		exc = 1;
		ierr++;
	}

	// Verification du numero des lignes
	if (li1.mid(0, 2) != "1 " || li2.mid(0, 2) != "2 ")
	{
		exc = 2;
		ierr++;
	}

	//  if (ierr == 1)
	//      throw PreviSatException(exc);
	//   else if (ierr > 1)
	//       throw PreviSatException(8);
	//   else
	//   {}

	// Verification des espaces dans les lignes
	if (li1.at(1) != ' ' || li1.at(8) != ' ' || li1.at(17) != ' ' || li1.at(32)
			!= ' ' || li1.at(43) != ' ' || li1.at(52) != ' ' || li1.at(61)
			!= ' ' || li1.at(63) != ' ' || li2.at(1) != ' ' || li2.at(7) != ' '
			|| li2.at(16) != ' ' || li2.at(25) != ' ' || li2.at(33) != ' '
			|| li2.at(42) != ' ' || li2.at(51) != ' ')
		return;

	// Verification de la ponctuation des lignes
	if (li1.at(23) != '.' || li1.at(34) != '.' || li2.at(11) != '.' || li2.at(
			20) != '.' || li2.at(37) != '.' || li2.at(46) != '.' || li2.at(54)
			!= '.')
		return;

	// Verification du numero NORAD
	if (li1.mid(2, 5) != li2.mid(2, 5))
		return;

	// Verification des checksums
	if (!CheckSum(li1))
		return;

	if (!CheckSum(li2))
		return;

	/* Retour */
	return;
}
bool CNewOrbObj::CheckSum(const QString ligne)
{
	/* Declarations des variables locales */
	int check, chr;

	/* Initialisations */
	check = 0;

	/* Corps de la methode */
	for (int i = 0; i < 68; i++)
	{

		chr = ligne.at(i).digitValue();
		if (chr >= 0 && chr <= 9)
		{
			check += chr;
		}
		else
		{
			if (ligne.at(i) == '-')
				check++;
		}
	}
	chr = ligne.at(68).digitValue();

	/* Retour */
	return ((check % 10 == chr) ? true : false);
}

