#include "neworbsys.h"
#include <QDebug>
#include <QDateTimeEdit>
#include <QTextCodec>
#include <math.h>
//#include "delegate.h"
//#include <interlocation/SunPosition.h>
QStringList SParamBSKOpticTn(QStringList()<< QString::fromUtf8("площадь элементов, 10<sup>-10</sup>*м<sup>2</sup>")<< QString::fromUtf8("спектр. диапазон, мкм") << QString::fromUtf8("фокус, м")   << QString::fromUtf8("относ. отверстие объектива")  << QString::fromUtf8("время экспозиции,10<sup>-6</sup>*с")<< QString::fromUtf8("квантовая эффективность 10<sup>-5</sup>")<< QString::fromUtf8("световая экспозиция 10<sup>-5</sup>")<< QString::fromUtf8(" к-т пропускаяния OC"));
QStringList SParamBSKOpticFn(QStringList() << QString::fromUtf8("спектр. диапазон, мкм") << QString::fromUtf8("фокус, м") << QString::fromUtf8("разреш. способность,лин/мм")<< QString::fromUtf8(" к-т пропускания OC"));
QStringList SParamBSKPLSFn(QStringList() << QString::fromUtf8("диапазон PB, ГГц")<< QString::fromUtf8("мощность излучения, кВт")<< QString::fromUtf8("угол выноса ближней границы, град")<< QString::fromUtf8("угол выноса дальней границы, град")<< QString::fromUtf8("разрешение, м")<< QString::fromUtf8("порог. чувствительность,дБ")<< QString::fromUtf8("канал передачи РЛИ, Мбит/с"));

CNewOrbSys::CNewOrbSys(QWidget* parent) :
	QDialog(parent)
{

	setMinimumSize(550, 650);

	//setWindowIcon(QIcon(":/Images/icon.png"));


	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	QGroupBox* grSostKA = new QGroupBox(this);
	grSostKA->setTitle(QObject::trUtf8("Состав"));
	QGridLayout* editLayout1 = new QGridLayout(grSostKA);
	QGroupBox* grBazKA = new QGroupBox(this);
	grBazKA->setTitle(QObject::trUtf8("Базовый КА"));
	QGridLayout* editLayout = new QGridLayout(grBazKA);
	_namesys = new QLineEdit(grSostKA);
	_kolplosk = new QSpinBox(grSostKA);
	_kolKA_v_plosk = new QSpinBox(grSostKA);
	//_dattim== new QDateTimeEdit(QDateTime::currentDateTimeUtc());
	_dattim = new QDateTimeEdit(QDate::currentDate());
	_dattim->setMinimumDate(QDate::currentDate().addDays(-365));
	_dattim->setMaximumDate(QDate::currentDate().addDays(365));
	_dattim->setDisplayFormat("yyyy.MM.dd hh:mm:ss");
	//qDebug()<<"2";
	//_dattim->setDateTime(QDateTime::currentDateTimeUtc());
	_naklon = new QDoubleSpinBox(grBazKA);
	_LVU = new QDoubleSpinBox(grBazKA);
	_H = new QDoubleSpinBox(grBazKA);
	_E = new QDoubleSpinBox(grBazKA);
	_Per = new QDoubleSpinBox(grBazKA);
	//QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

	this->setWindowTitle(QObject::trUtf8("Формирование системы КА"));

	editLayout1->addWidget(new QLabel(QObject::trUtf8("Название ситемы")), 0,
			0, Qt::AlignRight);
	editLayout1->addWidget(_namesys, 0, 1);
	editLayout1->addWidget(
			new QLabel(QObject::trUtf8("Количество плоскостей")), 1, 0,
			Qt::AlignRight);
	editLayout1->addWidget(_kolplosk, 1, 1);
	editLayout1->addWidget(new QLabel(QObject::trUtf8(
			"Количество КА в плоскости")), 2, 0, Qt::AlignRight);
	editLayout1->addWidget(_kolKA_v_plosk, 2, 1);
	editLayout1->addWidget(new QLabel(QObject::trUtf8("Дата и время")), 3, 0,
			Qt::AlignRight);
	editLayout1->addWidget(_dattim, 3, 1);
	radioButton_pavn = new QCheckBox(grSostKA);
	radioButton_pavn->setChecked(true);
	radioButton_pavn->setText(QObject::trUtf8(
			"Равномерное расположение плоскостей"));
	editLayout1->addWidget(radioButton_pavn, 4, 0, Qt::AlignLeft);
	radioButton_pavn1 = new QCheckBox(grSostKA);
	radioButton_pavn1->setChecked(true);
	radioButton_pavn1->setText(QObject::trUtf8(
			"Равномерное расположение КА в плоскости"));
        radioButton_sun = new QCheckBox(grSostKA);
        radioButton_sun->setChecked(false);
        radioButton_sun->setText(QObject::trUtf8(
                        "Солнечно-синхронная орбита"));
        Lvit=new QLabel(QObject::trUtf8("Межвитковое расстояние"));
	editLayout1->addWidget(radioButton_pavn1, 5, 0, Qt::AlignLeft);
        editLayout1->addWidget(radioButton_sun, 6, 0, Qt::AlignLeft);
        editLayout1->addWidget(Lvit, 7, 0, Qt::AlignLeft);
	//editLayout1->addWidget(_dattim,     3, 1);
	//qDebug()<<"4";
	//mainLayout->addWidget(grSostKA);
	//qDebug()<<"40";
	editLayout->addWidget(new QLabel(QObject::trUtf8("Долгота ВУ")), 3, 0,
			Qt::AlignRight);
	editLayout->addWidget(_LVU, 3, 1);
	_LVU->setMaximum(360.);
	_LVU->setSingleStep(0.5);
	_LVU->setMinimum(0.);
	editLayout->addWidget(new QLabel(QObject::trUtf8("Наклонение орбит")), 4,
			0, Qt::AlignRight);
	editLayout->addWidget(_naklon, 4, 1);
	_naklon->setMaximum(180.);
	_naklon->setSingleStep(0.1);
	_naklon->setMinimum(0.);
	_H->setMaximum(6471 + 36000.);
	_H->setSingleStep(10.);
	_H->setMinimum(6471.);
	editLayout->addWidget(new QLabel(QObject::trUtf8("Большая полуось орбит")),
			5, 0, Qt::AlignRight);
	editLayout->addWidget(_H, 5, 1);
	editLayout->addWidget(new QLabel(QObject::trUtf8("Эксцентриситет орбит")),
			6, 0, Qt::AlignRight);
	editLayout->addWidget(_E, 6, 1);
	_E->setMaximum(1.);
	_E->setSingleStep(0.001);
	_E->setMinimum(0.);
	_Per->setMaximum(360.);
	_Per->setMinimum(0.);
	editLayout->addWidget(
			new QLabel(QObject::trUtf8("Аргумент широты перигея")), 7, 0,
			Qt::AlignRight);
	editLayout->addWidget(_Per, 7, 1);
	// mainLayout->addLayout(editLayout);
	QHBoxLayout* sLayout = new QHBoxLayout;
	// sLayout->addLayout(editLayout1);
	//  sLayout->addLayout(editLayout);

	sLayout->addWidget(grSostKA);
	sLayout->addWidget(grBazKA);
	mainLayout->addLayout(sLayout);
	//  mainLayout->addWidget(grBazKA);
	//
	grsvdPL = new QGroupBox(this);
	grsvdPL->setTitle(QObject::trUtf8("Смещение плоскостей"));
	grsvdPL->setEnabled(false);
	QGridLayout* editLayout2 = new QGridLayout(grsvdPL);
	grsvdKA = new QGroupBox(this);
	grsvdKA->setTitle(QObject::trUtf8("Смещение КА в плоскости"));
	grsvdKA->setEnabled(false);
	QGridLayout* editLayout3 = new QGridLayout(grsvdKA);
	_svdpl = new QDoubleSpinBox(grsvdPL);
	_npl = new QSpinBox(grsvdPL);
	_npl->setValue(1);
	_svdKA = new QDoubleSpinBox(grsvdKA);
	_svdperKA = new QDoubleSpinBox(grsvdKA);
	_nKApl = new QSpinBox(grsvdKA);
	_nKApl->setValue(0);
	editLayout2->addWidget(new QLabel(QObject::trUtf8("Номер плоскости")), 0,
			0, Qt::AlignRight);
	editLayout2->addWidget(_npl, 0, 1);
	editLayout2->addWidget(new QLabel(QObject::trUtf8(
			"Угол смещения  плоскостей")), 1, 0, Qt::AlignRight);
	editLayout2->addWidget(_svdpl, 1, 1);
	editLayout3->addWidget(new QLabel(QObject::trUtf8("Номер КА в плоскости")),
			0, 0, Qt::AlignLeft);
	editLayout3->addWidget(_nKApl, 0, 1);
	editLayout3->addWidget(
			new QLabel(QObject::trUtf8("Аргумент широты, град")), 1, 0,
			Qt::AlignLeft);
	editLayout3->addWidget(_svdKA, 1, 1);
	editLayout3->addWidget(new QLabel(QObject::trUtf8(
			"Аргумент широты перигея КА, град")), 2, 0, Qt::AlignLeft);
	editLayout3->addWidget(_svdperKA, 2, 1);
	//editLayout3->addWidget(new QLabel(QObject::trUtf8("Угол смешения аргумента перигея КА")),  1, 0, Qt::AlignLeft);
	//editLayout3->addWidget(_svdperKA,     1, 1);
//    QGroupBox* BSA;
//    QComboBox* typeBSA;
//    QDoubleSpinBox* Gamma;
//    QDoubleSpinBox* Gamma1;
//    QDoubleSpinBox* Lz;
//    QDoubleSpinBox* Pz;

    BSA=new QGroupBox(this);
        BSA->setTitle(QObject::trUtf8("БСА"));
        BSA->setEnabled(true);
        QGridLayout* editLayout2b = new QGridLayout(BSA);
        typeBSA = new QComboBox(BSA);
        typeBSA->addItem(QObject::trUtf8("ОЭН"));
        typeBSA->addItem(QObject::trUtf8("РЛН"));
     Gamma = new QDoubleSpinBox(BSA);
     Gamma->setMaximum(70.);
     Gamma->setSingleStep(0.1);
     Gamma->setMinimum(0.);
     Gamma->setValue(65);
     Gamma1 = new QDoubleSpinBox(BSA);

     Gamma1->setMaximum(40.);
     Gamma1->setSingleStep(0.1);
     Gamma1->setMinimum(5.);
     Gamma1->setValue(15);

     Lz = new QDoubleSpinBox(BSA);
     Lz->setMaximum(240.);
     Lz->setSingleStep(1.0);
     Lz->setMinimum(5.);
     Lz->setValue(15);


     Pz = new QDoubleSpinBox(BSA);

     Pz->setMaximum(240.);
     Pz->setSingleStep(0.5);
     Pz->setMinimum(0.5);
     Pz->setValue(1.5);
     editLayout2b->addWidget(new QLabel(QObject::trUtf8("Тип БСА")), 0,
             0, Qt::AlignRight);
     editLayout2b->addWidget(typeBSA, 0, 1);
     labg1=new QLabel(QObject::trUtf8("Мах. угол полураствора,град"));
     labg2=new QLabel(QObject::trUtf8("Мин. угол полураствора,град"));
     editLayout2b->addWidget(labg1, 1,
             0, Qt::AlignRight);
     editLayout2b->addWidget(Gamma, 1, 1);
     editLayout2b->addWidget(labg2, 2,
             0, Qt::AlignRight);

     editLayout2b->addWidget(Gamma1, 2, 1);
      labg2->setEnabled(false);
      Gamma1->setEnabled(false);
     editLayout2b->addWidget(new QLabel(QObject::trUtf8("Ширина полосы захвата, км")), 3,
             0, Qt::AlignRight);
     editLayout2b->addWidget(Lz, 3, 1);
     editLayout2b->addWidget(new QLabel(QObject::trUtf8("Разрешение, м")), 4,
             0, Qt::AlignRight);
     editLayout2b->addWidget(Pz, 4, 1);

	QHBoxLayout* svdLayout = new QHBoxLayout;
	svdLayout->addWidget(grsvdPL);
	svdLayout->addWidget(grsvdKA);
    svdLayout->addWidget(BSA);
  QObject::connect(typeBSA, SIGNAL(activated(int)), this, SLOT(editTs()));
	//slots
	radioButton_pavn->setEnabled(false);
	QObject::connect(radioButton_pavn, SIGNAL(toggled(bool)), this,
			SLOT(setdatpl()));
	QObject::connect(radioButton_pavn1, SIGNAL(toggled(bool)), this,
			SLOT(setdatKApl()));
        QObject::connect(radioButton_sun, SIGNAL(toggled(bool)), this,
                        SLOT(setdatKASUN()));
	// QObject::connect(_npl, SIGNAL(valueChanged(int)), this, SLOT(setdatpl()));
	//  QObject::connect(_nKApl, SIGNAL(valueChanged(int)), this, SLOT(setdatKAplz()));
	radioButton_pavn->setEnabled(false);
	radioButton_pavn1->setEnabled(false);
        radioButton_sun->setEnabled(true);
	grsvdPL->setEnabled(false);
	// _svdKA
	//end slots
	mainLayout->addLayout(svdLayout);

	QGroupBox* grtab = new QGroupBox(this);
	grtab->setTitle(QObject::trUtf8("Состав группировки"));
	tableView = new QTableView(grtab);
	QHBoxLayout* TabLayout = new QHBoxLayout(grtab);
	//TabLayout->
	TabLayout->addWidget(tableView);
	mainLayout->addWidget(grtab);
	_buttonCancel = new QPushButton(QObject::trUtf8("Выход"), this);
	connect(_buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

	_buttonOK = new QPushButton(QObject::trUtf8("OK"), this);
	connect(_buttonOK, SIGNAL(clicked()), this, SLOT(accept()));

	_buttonOK->setDefault(true);
	_buttonformThis = new QPushButton(QObject::trUtf8("Сформировать"), this);
	connect(_buttonformThis, SIGNAL(clicked()), this, SLOT(formsys()));
//	_buttonViewThis = new QPushButton(QObject::trUtf8("Просмотр"), this);
//	_buttonViewThis->setEnabled(false);
//	connect(_buttonViewThis, SIGNAL(clicked()), this, SLOT(formviewplot()));
	QHBoxLayout* buttonLayout = new QHBoxLayout;

	buttonLayout->addWidget(_buttonformThis);
    //buttonLayout->addWidget(_buttonViewThis);
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(_buttonCancel);
	buttonLayout->addWidget(_buttonOK);

	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
}
 void    CNewOrbSys::editTs()
 {

   int curint=typeBSA->currentIndex();
   if(curint==0)
   {
       labg2->setEnabled(false);
       Gamma1->setEnabled(false);
   }
   if(curint==1) {
       labg2->setEnabled(true);
       Gamma1->setEnabled(true);

   }

 }

CNewOrbSys::~CNewOrbSys()
{
	delete _buttonCancel;
	delete _buttonOK;
	delete _buttonformThis;

}
void CNewOrbSys::formsys()
{
	tableView->setEnabled(false);
	tableView->setSortingEnabled(false);
	tableView->horizontalHeader()->setStretchLastSection(true);
//	SpinBoxDelegate* delegate = new SpinBoxDelegate(this);
	//SpinBoxDelegate delegate;
	int n = _kolplosk->value() * _kolKA_v_plosk->value();
    if(n<=0) return;
	QStandardItemModel *model = new QStandardItemModel(n, 8, this);
	model->setHeaderData(0, Qt::Horizontal, QObject::trUtf8("Номер плоскости"));
	model->setHeaderData(1, Qt::Horizontal, QObject::trUtf8(
			"Номер КА в плоскости"));
	model->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Долгота В.У,град"));
	model->setHeaderData(3, Qt::Horizontal, QObject::trUtf8(
			"Большая полуось,км"));
	model->setHeaderData(4, Qt::Horizontal, QObject::trUtf8("Эксцентриситет"));
	model->setHeaderData(5, Qt::Horizontal, QObject::trUtf8(
			"Аргумент широты,град"));
	model->setHeaderData(6, Qt::Horizontal, QObject::trUtf8("Наклонение,град"));
	model->setHeaderData(7, Qt::Horizontal, QObject::trUtf8(
			"Аргумент широты перигея,град"));
	int k = 0;
	QStringList subject;
	formstruct();

	for (int j = 0; j < _kolplosk->value(); j++)
	{
		for (int i = 0; i < _kolKA_v_plosk->value(); i++)
		{
			for (int ij = 0; ij < 8; ij++)
			{
				double ks = ij * i;
				int kk = k * 8 + ij;
				QModelIndex index = model->index(k, ij, QModelIndex());
				model->setData(model->index(k, ij), QVariant(sender.at(kk)));

			}
			k += 1;
		}

	}
	tableView->setModel(model);
//	tableView->setItemDelegate(delegate);
	tableView->setEnabled(true);
	tableView->update();
    //_buttonViewThis->setEnabled(true);
}

// Accept slot
////////////////////////////////////////////////////////////////////////////
void CNewOrbSys::accept()
{

	ASDOrbitalObjectPar obj;

 ASDBsePar bsad;
	if (_namesys->text().length() == 0)
		_namesys->setText("test");
	obj.nameSys = _namesys->text();


	obj.type = UN;
    if(typeBSA->currentIndex()==0)
    {

        obj.type = OERT;
        obj.nameSys ="OEN";
        bsad.name = "bsaO";
        bsad.gamma =Gamma->value();
        bsad.deltaL =Lz->value();

      bsad.deltaVr  = 150.;
      bsad.skor = Pz->value();
        bsad.Pr =10;
        bsad.fmem    = 300.;
        double ttr=0;
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
         bsad.param_value.append(ttr);
        bsad.name_param.append(SParamBSKOpticTn.at(0));
        bsad.name_param.append(SParamBSKOpticTn.at(1));
        bsad.name_param.append(SParamBSKOpticTn.at(2));
        bsad.name_param.append(SParamBSKOpticTn.at(3));
        bsad.name_param.append(SParamBSKOpticTn.at(4));
        bsad.name_param.append(SParamBSKOpticTn.at(5));
        bsad.name_param.append(SParamBSKOpticTn.at(6));
        bsad.name_param.append(SParamBSKOpticTn.at(7));
    }
    if(typeBSA->currentIndex()==1)
    {
        obj.type = RLRF;
        obj.nameSys ="RLN";

        bsad.name = "bsaR";
        bsad.gamma =Gamma->value();
        bsad.deltaL =Lz->value();

      bsad.deltaVr  = 150.;
      bsad.skor =Pz->value();
        bsad.Pr = 1;
        bsad.fmem    = 300.;

        double ttr=0;
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
        bsad.param_value.append(Gamma->value());
        bsad.param_value.append(Gamma1->value());
        bsad.param_value.append(Pz->value());
        bsad.param_value.append(ttr);
        bsad.param_value.append(ttr);
        bsad.name_param.append(SParamBSKPLSFn.at(0));
        bsad.name_param.append(SParamBSKPLSFn.at(1));
        bsad.name_param.append(SParamBSKPLSFn.at(2));
        bsad.name_param.append(SParamBSKPLSFn.at(3));
        bsad.name_param.append(SParamBSKPLSFn.at(4));
        bsad.name_param.append(SParamBSKPLSFn.at(5));
        bsad.name_param.append(SParamBSKPLSFn.at(6));

    }
	obj.type_dat = KEPLER;
	//for

	obj.kep.a = 0.;
	obj.kep.e = 0.;
	obj.kep.i = 0.;
	obj.kep.l = 0.;
	obj.kep.name = "";
	// obj.kep.t_epoch=0.;
	// obj.Xkep.

	//
     obj.bsa.push_back(bsad);
	QAbstractItemModel *model = tableView->model();

	int n = _kolplosk->value() * _kolKA_v_plosk->value();
	for (int k = 0; k < n; k++)
	{

		QModelIndex index = model->index(k, 3, QModelIndex());
		obj.kep.a = index.model()->data(index, Qt::EditRole).toDouble();
		index = model->index(k, 2, QModelIndex());
		obj.kep.l = index.model()->data(index, Qt::EditRole).toDouble();
		index = model->index(k, 6, QModelIndex());
		obj.kep.i = index.model()->data(index, Qt::EditRole).toDouble();
		index = model->index(k, 4, QModelIndex());
		obj.kep.e = index.model()->data(index, Qt::EditRole).toDouble();
		index = model->index(k, 5, QModelIndex());
		obj.kep.u = index.model()->data(index, Qt::EditRole).toDouble();
		index = model->index(k, 0, QModelIndex());
		int i = index.model()->data(index, Qt::EditRole).toInt();
		index = model->index(k, 1, QModelIndex());
		int j = index.model()->data(index, Qt::EditRole).toInt();
		index = model->index(k, 7, QModelIndex());
		obj.kep.omega = index.model()->data(index, Qt::EditRole).toDouble();

		obj.kep.t_epoch = _dattim->dateTime();
        obj.kep.name=QString("%1-%2-%3").arg(obj.nameSys).arg(i).arg(j);
        //obj.kep.name = QString("%1-%2").arg(i).arg(j);

		list_obj.push_back(obj);
	}
//	qDebug() << "end";
	//

	//
	//


	QDialog::accept();
}
void CNewOrbSys::formstruct()
{
	//col plosk
	sender.clear();
    if(_kolplosk->value()==0) return;
    if(_kolKA_v_plosk->value()==0) return;
	double delta_L = 360. / _kolplosk->value();//delta plosk
	double delta_U = 360. / _kolKA_v_plosk->value();//delta U v plosk
	double T_per = 2. * M_PI * pow(_H->value(), 0.5) / sqrt(398602.5);
	double faza = T_per / _kolplosk->value() / _kolKA_v_plosk->value();
	//qDebug()<<"faza="<<faza*180./M_PI<<T_per*180./M_PI<<"du="<<delta_U;
	for (int j = 0; j < _kolplosk->value(); j++)
	{
		double fazeof = 0.;
		if (j % 2 == 0)
			fazeof = (360. - delta_U) / _kolplosk->value();
		for (int i = 0; i < _kolKA_v_plosk->value(); i++)
		{
			double l = _LVU->value() + delta_L * j;
			if (l > 360)
				l -= 360.;
			double u = delta_U * i;//-fazeof;//faza*j*180./M_PI;
			//          set T [expr ($T_per * $i / $SATS_PER_PLANE - $phase_offset*$j)]
			//qDebug()<<"faza="<<fazeof<<"du="<<u;
			if (u > 360)
				u -= 360.;
			for (int ij = 0; ij < 8; ij++)
			{

				if (ij == 0)
					sender.append(QString("%1").arg(j + 1));
				if (ij == 1)
					sender.append(QString("%1").arg(i + 1));
				if (ij == 2)
					sender.append(QString("%1").arg(l));
				if (ij == 3)
					sender.append(QString("%1").arg(_H->value()));
				if (ij == 4)
					sender.append(QString("%1").arg(_E->value()));
				if (ij == 5)
					sender.append(QString("%1").arg(u));
				if (ij == 6)
					sender.append(QString("%1").arg(_naklon->value()));
				if (ij == 7)
					sender.append(QString("%1").arg(_Per->value()));
			}
		}
	}
}
void CNewOrbSys::formviewplot()
{
	/* QVector<QWidget*> plots;
	 //t_point* pnt;
	 QList<t_point*> lpnt;
	 int k=0;
	 posKA point_kep;

	 QMap<int,posKA> l_point_kep;
	 for(int j=0;j<_kolplosk->value();j++)
	 {
	 for(int i=0;i<_kolKA_v_plosk->value();i++)
	 {
	 double _latDeg=j*40+i*15.;
	 double _lonDeg=i*50+j*15.;
	 //
	 point_kep.i_pl=j+1;
	 point_kep.j_plane=i+1;


	 loaddat(k,&_lonDeg,&_latDeg,&point_kep.a,&point_kep.e,&point_kep.l,
	 &point_kep.u,&point_kep.w,&point_kep.nakl,&point_kep.M);
	 l_point_kep.insertMulti(j,point_kep);
	 QColor color = QColor::fromHsv((j)*(359.0/_kolplosk->value()), 255, 255);
	 t_point* pnt=new t_point(color,QString("%1-%2").arg(i+1).arg(j+1),_latDeg,_lonDeg);
	 // pnt->_color=QColor(Qt::red);
	 // pnt->_name=QString("%1-%2").arg(i).arg(j);

	 lpnt.append(pnt);
	 k+=1;
	 }
	 }
	 */
	/*
	 t_worldPlot* viz=new t_worldPlot();
	 viz->slotNewPoints(lpnt);
	 plots<<viz;

	 SceneWidget* glwig=new SceneWidget();
	 glwig->setdan(l_point_kep);
	 dialog3d* viz3d= new dialog3d(0,glwig);
	 viz3d->exec();

	 //plots<<glwig;
	 QString fileName=QObject::trUtf8("Расположение КА сиcтемы")+":"+_namesys->text();
	 t_graphWin* graphWin = new t_graphWin(0, fileName, plots,
	 0, 0);
	 graphWin->setMaximumSize(850,600);
	 graphWin->exec();
	 viz3d->setFocus();
	 */
}
void CNewOrbSys::loaddat(int k, double* lon, double* lat, double* a1,
		double* e1, double* l1, double* u1, double* w1, double* nakl1,
		double* M1)
{
	int n = _kolplosk->value() * _kolKA_v_plosk->value();
	double la = 0.;
	double lo = 0.;
	double nakl = 0.;
	QAbstractItemModel *model = tableView->model();
	QModelIndex index = model->index(k, 2, QModelIndex());
	lo = index.model()->data(index, Qt::EditRole).toDouble();
	*l1 = lo;
	// //qDebug()<<"lon=="<<lo<< index.model()->data(index, Qt::EditRole).toDouble()<<"k="<<k;
	index = model->index(k, 5, QModelIndex());
	la = index.model()->data(index, Qt::EditRole).toDouble();
	*u1 = la;
	index = model->index(k, 6, QModelIndex());
	nakl = index.model()->data(index, Qt::EditRole).toDouble();
	*nakl1 = nakl;
	index = model->index(k, 3, QModelIndex());
	double a = index.model()->data(index, Qt::EditRole).toDouble();
	*a1 = a;
	index = model->index(k, 7, QModelIndex());
	*M1 = index.model()->data(index, Qt::EditRole).toDouble();
	index = model->index(k, 4, QModelIndex());
	*e1 = index.model()->data(index, Qt::EditRole).toDouble();
	// //qDebug()<<"nakl=="<<nakl<< index.model()->data(index, Qt::EditRole).toDouble()<<"k="<<k;


	double MU = 398602.5;

	double x = cos(la * M_PI / 180.) * cos(lo * M_PI / 180.) - sin(la * M_PI
			/ 180.) * cos(nakl * M_PI / 180.) * sin(lo * M_PI / 180.);
	double y = cos(la * M_PI / 180.) * sin(lo * M_PI / 180.) + sin(la * M_PI
			/ 180.) * cos(nakl * M_PI / 180.) * cos(lo * M_PI / 180.);
	double z = sin(la * M_PI / 180.) * sin(nakl * M_PI / 180.);
	x *= a;
	y *= a;
	z *= a;
	double T_per = 2 * M_PI * pow(a, 1.5) / sqrt(MU);
	double omega_z = 7292115e-11;
	double t = T_per / (2 * M_PI) * la * M_PI / 180.;

	double lon1 = atan2(y, x) - t * omega_z;
	if (lon1 > 2 * M_PI)
	{
		lon1 -= M_PI * 2.;
	}
	// if (lon1 < 0.0) {
	//   lon1 += M_PI*2.;
	//   }

	double r = sqrt(x * x + y * y);
	double lat1 = atan2(z, r);

	*lat = lat1 * 180. / M_PI;
	*lon = lon1 * 180. / M_PI;

}
void CNewOrbSys::setdatpl()
{
	if (radioButton_pavn->isChecked() == true)
	{
		grsvdPL->setEnabled(false);

	}
	else
	{
		grsvdPL->setEnabled(true);
		_npl->setMaximum(_kolplosk->value());
		_npl->setMinimum(1);

	}

}
void CNewOrbSys::setdatKApl()
{
	if (radioButton_pavn1->isChecked() == true)
	{
		grsvdKA->setEnabled(false);

	}
	else
	{
		grsvdKA->setEnabled(true);
		_nKApl->setMaximum(_kolKA_v_plosk->value());
		_nKApl->setMinimum(0);

	}

}
void CNewOrbSys::setdatKAplz()
{

}
//void CNewOrbSys::setdatKASUN()
//{
//    double ab=_H->value()*(1.-_E->value()*_E->value());
//  double  tt=-(pow((ab/12343.47),3.5));
//    if (radioButton_sun->isChecked() == true)
//    {
//       // double T_per = 2. * M_PI * pow(_H->value(), 0.5) / sqrt(398602.5);

//          if(_H->value()>6471)
//          {

//              if(fabs(tt)>1) tt=1.;
//         _naklon->setValue(acos(tt)*RAD_TO_DEG);
//                 _naklon->update();


// double c20=-1082.6e-6;
//// double pi20=-1.77e10;
//                 const double n = sqrt(K_EARTH / pow(ab, 3));
//                 double Tq= 2.0 * M_PI / n*(1.-3./4.*c20*(R_EARTH/ab)*(1.+5.*pow(cos(tt),2)));//Период
//                 double lv=2.0 * M_PI*Tq /86400.;
//                 double lvv=150.;
//                 SunPosition sun;

//                 double aee=sun.getRightAscension(_dattim->dateTime());
//                 lvv=fmod((360.-(aee*180/M_PI+150)),360);
//                 if(lvv<0) lvv+=360.;
//                //lvv=360-(aee*RAD_TO_DEG+150);

//_LVU->setValue(lvv);
//_LVU->update();
// Lvit->setText(QString::fromUtf8("Межвитковое расстояние =")+QString("%1").arg(lv*RAD_TO_DEG));
// Lvit->update();
//           }


//    }
//    else
//    {
//          tt=_naklon->value();
//          double c20=-1082.6e-6;
//         // double pi20=-1.77e10;
//                          const double n = sqrt(K_EARTH / pow(ab, 3));
//                          double Tq= 2.0 * M_PI / n*(1.-3./4.*c20*(R_EARTH/ab)*(1.+5.*pow(cos(tt),2)));//Период
//                          double lv=2.0 * M_PI*Tq /86400.;


//          Lvit->setText(QString::fromUtf8("Межвитковое расстояние =")+QString("%1").arg(lv*RAD_TO_DEG));
//          Lvit->update();

//    }
//}
