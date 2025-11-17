#include "orbinput.h"

COrbInput::COrbInput(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);

	connect(toolButtonAddObj, SIGNAL(clicked()), this, SLOT(addOrbitObj()));

	connect(toolButtonDelObj, SIGNAL(clicked()), this, SLOT(delOrbitObj()));

	connect(pushButtonCreateObj, SIGNAL(clicked()), this,
			SLOT(createOrbitObj()));
	connect(pushButtonSystemCreateObj, SIGNAL(clicked()), this,
			SLOT(createSystemOrbitObj()));

	connect(pushButtonSaveObj, SIGNAL(clicked()), this,
			SLOT(saveOrbitObjFile()));
	connect(pushButtonLoadFile, SIGNAL(clicked()), this,
			SLOT(loadOrbitObjFile()));

	connect(treeWidget_sysKA, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this,
			SLOT(findParamKA()));
	connect(treeWidget_sysKA, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
			this, SLOT(addOrbitObj()));

	connect(listWidget_rezKA, SIGNAL(doubleClicked(QModelIndex)), this,
			SLOT(delOrbitObj()));
	connect(listWidget_rezKA, SIGNAL(clicked(QModelIndex)), this,
			SLOT(fillListWidgetBsk()));

	connect(listWidgetBsa, SIGNAL(clicked(QModelIndex)), this,
			SLOT(viewParamBsk()));

	connect(pushButtonAddBsa, SIGNAL(clicked()), this, SLOT(addParamBsa()));
	connect(pushButtonEditBsa, SIGNAL(clicked()), this, SLOT(editParamBsa()));
	connect(pushButtonDelBsa, SIGNAL(clicked()), this, SLOT(delParamBsa()));
	connect(pushButtonSaveBsa, SIGNAL(clicked()), this, SLOT(saveParamBsa()));

	m_selectOrbitObj.clear();
	tableWidget_par->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

COrbInput::~COrbInput()
{

}

QVector<ASDOrbitalObjectPar> COrbInput::getOrbitalObjectPar()
{
	return m_selectOrbitObj;
}

void COrbInput::createOrbitObj()
{
	//отдельный ка
	CNewOrbObj* obj = new CNewOrbObj();
	obj->exec();
	if (obj->obj_rez.size() > 0)
	{
		QVector<ASDOrbitalObjectPar>::iterator p1 = tempv_obj.end();
		tempv_obj << obj->obj_rez;
		QString syst = obj->obj_rez.at(0).nameSys;
		QTreeWidgetItem *item1 = new QTreeWidgetItem(treeWidget_sysKA);
		item1->setText(0, obj->obj_rez.at(0).nameSys);
		for (int i = 0; i < obj->obj_rez.size(); i++)
		{
			//				qDebug() << "i=" << obj->obj_rez.at(i).stle.satName;
			QTreeWidgetItem *item = new QTreeWidgetItem(item1);
			//item->setText(0,obj->list_obj.at(i).nameSys);
			if (obj->obj_rez.at(i).type_dat == 0)
				item->setText(1, obj->obj_rez.at(i).kep.name);
			if (obj->obj_rez.at(i).type_dat == 1)
				item->setText(1, obj->obj_rez.at(i).ags.name);
			if (obj->obj_rez.at(i).type_dat == 2)
				item->setText(1, obj->obj_rez.at(i).stle.satName);
		}
	}
	obj = 0;
}

void COrbInput::createSystemOrbitObj()
{
	CNewOrbSys* obj = new CNewOrbSys(this);

	obj->exec();
	QVector<ASDOrbitalObjectPar>::iterator p1 = tempv_obj.end();
	tempv_obj << obj->list_obj;

	if (obj->list_obj.size() > 0)
	{
		QString syst = obj->list_obj.at(0).nameSys;
		QTreeWidgetItem *item1 = new QTreeWidgetItem(treeWidget_sysKA);//treeWidget->topLevelItem(0);
		item1->setText(0, obj->list_obj.at(0).nameSys);
		for (int i = 0; i < obj->list_obj.size(); i++)
		{
			if (obj->list_obj.at(i).nameSys == syst)
			{
				QTreeWidgetItem *item = new QTreeWidgetItem(item1);
				item->setText(1, obj->list_obj.at(i).kep.name);
			}
			else
			{

			}
		}
	}

	obj = 0;
}

void COrbInput::loadOrbitObjFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QObject::trUtf8(
			"Загрузить файл с параметрами орбительного объекта"), "",
            QObject::trUtf8("Файл с TLE параметрами (*.txt);;XBEL файл (*.xml);;INI файл (*.ini)"));
	QFileInfo fileInfo(fileName);

	if (!fileName.isEmpty())
	{
		CObjFileParser dat;
		if (fileInfo.suffix() == "xml")
		{
			dat.readOrbitObjXml(fileName);
		}
		else if (fileInfo.suffix() == "ini")
		{
			dat.readOrbitObjIni(fileName);
		}
		else if (fileInfo.suffix() == "txt")
		{
			dat.readOrbitObjTle(fileName);
		}

		tempv_obj << dat.m_paramOrbitObj;

		QString sysName;
		QTreeWidgetItem *item1 = new QTreeWidgetItem();

		for (int i = 0; i < dat.m_paramOrbitObj.size(); ++i)
		{
			sysName = dat.m_paramOrbitObj[i].nameSys;
			if (treeWidget_sysKA->findItems(sysName, Qt::MatchFixedString).count())
			{
				item1 = treeWidget_sysKA->findItems(sysName,
						Qt::MatchFixedString).at(0);
			}
			else
			{
				item1 = new QTreeWidgetItem(treeWidget_sysKA);
				item1->setText(0, dat.m_paramOrbitObj[i].nameSys);
			}

			QTreeWidgetItem *item = new QTreeWidgetItem(item1);

			if (dat.m_paramOrbitObj[i].type_dat == 0)
				item->setText(1, dat.m_paramOrbitObj[i].kep.name);
			if (dat.m_paramOrbitObj[i].type_dat == 1)
				item->setText(1, dat.m_paramOrbitObj[i].ags.name);
			if (dat.m_paramOrbitObj[i].type_dat == 2)
				item->setText(1, dat.m_paramOrbitObj[i].stle.satName);
		}

	}
}

void COrbInput::loadDefaultParam(QString strFile)
{

    CObjFileParser dat;

    dat.readOrbitObjTle(strFile);

    tempv_obj << dat.m_paramOrbitObj;

    QString sysName;
    QTreeWidgetItem *item1 = new QTreeWidgetItem();

    for (int i = 0; i < dat.m_paramOrbitObj.size(); ++i)
    {
        sysName = dat.m_paramOrbitObj[i].nameSys;
        if (treeWidget_sysKA->findItems(sysName, Qt::MatchFixedString).count())
        {
            item1= treeWidget_sysKA->findItems(sysName, Qt::MatchFixedString).at(0);
        }
        else
        {
            item1 = new QTreeWidgetItem(treeWidget_sysKA);
            item1->setText(0, dat.m_paramOrbitObj[i].nameSys);
        }

        QTreeWidgetItem *item = new QTreeWidgetItem(item1);

        if (dat.m_paramOrbitObj[i].type_dat == 0)
            item->setText(1, dat.m_paramOrbitObj[i].kep.name);
        if (dat.m_paramOrbitObj[i].type_dat == 1)
            item->setText(1, dat.m_paramOrbitObj[i].ags.name);
        if (dat.m_paramOrbitObj[i].type_dat == 2)
            item->setText(1, dat.m_paramOrbitObj[i].stle.satName);
        treeWidget_sysKA->setCurrentItem(item);
        addOrbitObj();
    }

}


void COrbInput::saveOrbitObjFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, QObject::trUtf8(
            "Сохраниь файл с параметрами орбительного объекта"), "",
            QObject::trUtf8("XBEL файл (*.xml);;INI файл (*.ini)"));
    QFileInfo fileInfo(fileName);

    if (m_selectOrbitObj.size() > 0)
    {
        CObjFileParser dat;
        if (fileInfo.suffix() == "xml")
        {
            dat.writeOrbitObjXml(fileName, m_selectOrbitObj);
        }
        else if (fileInfo.suffix() == "ini")
        {
            dat.writeOrbitObjIni(fileName, m_selectOrbitObj);
        }

    }
}

void COrbInput::addOrbitObj()
{
	//listWidget_rezKA
	//tableWidget_par
	QTreeWidgetItem *_item = treeWidget_sysKA->currentItem();
	QString str_find = _item->text(1);

	int k = -1;
	for (int i = 0; i < tempv_obj.size(); i++)
	{
		if ((tempv_obj.at(i).type_dat == 0) && (tempv_obj.at(i).kep.name
				== str_find))
			k = i;
		if ((tempv_obj.at(i).type_dat == 1) && (tempv_obj.at(i).ags.name
				== str_find))
			k = i;
		if ((tempv_obj.at(i).type_dat == 2) && (tempv_obj.at(i).stle.satName
				== str_find))
			k = i;

	}
	if (k >= 0)
	{
		if (tempv_obj.at(k).type_dat == 0)
			listWidget_rezKA->addItem(tempv_obj.at(k).nameSys + ":"
					+ tempv_obj.at(k).kep.name);
		if (tempv_obj.at(k).type_dat == 1)
			listWidget_rezKA->addItem(tempv_obj.at(k).nameSys + ":"
					+ tempv_obj.at(k).ags.name);
		if (tempv_obj.at(k).type_dat == 2)
			listWidget_rezKA->addItem(tempv_obj.at(k).nameSys + ":"
					+ tempv_obj.at(k).stle.satName);

		m_selectOrbitObj.push_back(tempv_obj.at(k));

	}

	this->update();
}

void COrbInput::delOrbitObj()
{
	QListWidgetItem *___qlistwidgetitem = listWidget_rezKA->currentItem();
	int row = listWidget_rezKA->currentRow();
	if (row < 0)
		return;
	// QString str_f=___qlistwidgetitem->text();
	int pos = ___qlistwidgetitem->text().indexOf(":");
	QString str_f = ___qlistwidgetitem->text().mid(pos + 1);
	// qDebug()<<"pos="<<pos<<str_f;

	listWidget_rezKA->takeItem(row);
	listWidget_rezKA->removeItemWidget(___qlistwidgetitem);

	// довать удаление из списка данных
	QVector<ASDOrbitalObjectPar>::iterator p, p1;
	ASDOrbitalObjectPar par;
	for (p = m_selectOrbitObj.begin(); p != m_selectOrbitObj.end(); p++)
	{

		par = *p;
		if (par.kep.name == str_f)
			p1 = p;

		if (par.ags.name == str_f)
			p1 = p;

		if (par.stle.satName == str_f)
			p1 = p;

	}
	m_selectOrbitObj.erase(p1);
	// for(int j=0;j<m_selectOrbitObj.size();j++)
	// qDebug()<<"j="<<j<<m_selectOrbitObj.at(j).kep.name;


}

void COrbInput::findParamKA()
{
	QTreeWidgetItem *_item = treeWidget_sysKA->currentItem();
	QTreeWidgetItem *parent = treeWidget_sysKA->currentItem()->parent();
	int index;

	if (parent)
	{ // если не корень
		//название заголовка
		index = treeWidget_sysKA->indexOfTopLevelItem(
				treeWidget_sysKA->currentItem());
		//delete treeWidget->takeTopLevelItem(index);
		//		qDebug() << "_item->childCount()ppppp if=" << index;
	}
	else
	{ //если по названию списка
		index = treeWidget_sysKA->indexOfTopLevelItem(
				treeWidget_sysKA->currentItem());//индекс в общей (1 колонка)


	}
	QTreeWidgetItem *_item0 = treeWidget_sysKA->currentItem();//childCount();//_item->child(treeWidget_sysKA->currentIndex().child(.data());
	QString as = _item0->text(0);//treeWidget_sysKA->currentIndex().data().toString());
	QList<QTreeWidgetItem*> items = treeWidget_sysKA->findItems("test",
			Qt::MatchContains);
	if (items.count() > 0)
	{

	}
	QString str_find = _item->text(1);

	int k = -1;
	for (int i = 0; i < tempv_obj.size(); i++)
	{
		if ((tempv_obj.at(i).type_dat == 0) && (tempv_obj.at(i).kep.name
				== str_find))
			k = i;
		if ((tempv_obj.at(i).type_dat == 1) && (tempv_obj.at(i).ags.name
				== str_find))
			k = i;
		if ((tempv_obj.at(i).type_dat == 2) && (tempv_obj.at(i).stle.satName
				== str_find))
			k = i;

	}

	for (int j = 0; j < 8; ++j)
		tableWidget_par->removeRow(j);
	tableWidget_par->setRowCount(8);
	tableWidget_par->setColumnCount(2);

	QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
	tableWidget_par->setHorizontalHeaderItem(0, __qtablewidgetitem);
	__qtablewidgetitem->setText(QObject::trUtf8("Параметр"));
	QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
	tableWidget_par->setHorizontalHeaderItem(1, __qtablewidgetitem1);
	// tableWidget_par->setAttribute(Qt::NoModifier);
	__qtablewidgetitem1->setText(QObject::trUtf8("Значение"));
	if (k >= 0)
	{

		QTableWidgetItem *i;
		if (tempv_obj.at(k).type_dat == 0)

		{
			i = new QTableWidgetItem(QObject::trUtf8("Название КА"));
			tableWidget_par->setItem(0, 0, i);

			i = new QTableWidgetItem(tempv_obj.at(k).kep.name);
			tableWidget_par->setItem(0, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Время"));
			tableWidget_par->setItem(1, 0, i);
			i = new QTableWidgetItem(tempv_obj.at(k).kep.t_epoch.toString(
					"yyyy.MM.dd hh:mm:ss"));
			tableWidget_par->setItem(1, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Долгота BУ, град"));
			tableWidget_par->setItem(2, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).kep.l,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(2, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Наклонение, град"));
			tableWidget_par->setItem(3, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).kep.i,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(3, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8(
					"Большая полуось орбиты, км"));
			tableWidget_par->setItem(4, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).kep.a,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(4, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Эксцентриситет"));
			tableWidget_par->setItem(5, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).kep.e,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(5, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Aргумент широты, град"));
			tableWidget_par->setItem(6, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).kep.u,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(6, 1, i);

		}
		if (tempv_obj.at(k).type_dat == 1)//ags
		{

			i = new QTableWidgetItem(QObject::trUtf8("Название КА"));
			tableWidget_par->setItem(0, 0, i);
			i = new QTableWidgetItem(tempv_obj.at(k).ags.name);
			tableWidget_par->setItem(0, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Время"));
			tableWidget_par->setItem(1, 0, i);
			i = new QTableWidgetItem(tempv_obj.at(k).ags.t_epoch.toString(
					"yyyy.MM.dd hh:mm:ss"));
			tableWidget_par->setItem(1, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("X, км"));
			tableWidget_par->setItem(2, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).ags.x,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(2, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Y, км"));
			tableWidget_par->setItem(3, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).ags.y,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(3, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Z, км"));
			tableWidget_par->setItem(4, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).ags.z,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(4, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Vx, м/c"));
			tableWidget_par->setItem(5, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).ags.vx,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(5, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Vy, м/c"));
			tableWidget_par->setItem(6, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).ags.vy,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(6, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Vz, м/c"));
			tableWidget_par->setItem(7, 0, i);
			i = new QTableWidgetItem(QString("%1").arg(tempv_obj.at(k).ags.vz,
					7, 'f', 5, '0'));
			tableWidget_par->setItem(7, 1, i);

		}
		if (tempv_obj.at(k).type_dat == 2)// tle

		{
			i = new QTableWidgetItem(QObject::trUtf8("Заголовок  tle"));
			tableWidget_par->setItem(0, 0, i);
			i = new QTableWidgetItem(tempv_obj.at(k).stle.satName);
			tableWidget_par->setItem(0, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Первая строка"));
			tableWidget_par->setItem(1, 0, i);
			i = new QTableWidgetItem(tempv_obj.at(k).stle.firstString);
			tableWidget_par->setItem(1, 1, i);
			i = new QTableWidgetItem(QObject::trUtf8("Вторая строка"));
			tableWidget_par->setItem(2, 0, i);
			i = new QTableWidgetItem(tempv_obj.at(k).stle.secondString);
			tableWidget_par->setItem(2, 1, i);
		}

	}
	tableWidget_par->setUpdatesEnabled(true);
	tableWidget_par->setEnabled(true);
	this->update();

}

void COrbInput::fillListWidgetBsk()
{
	int curRow = listWidget_rezKA->currentRow();
	listWidgetBsa->clear();

	for (int i = 0; i < m_selectOrbitObj.at(curRow).bsa.size(); ++i)
	{
		listWidgetBsa->addItem(QString::number(i) + " " + m_selectOrbitObj.at(
				curRow).bsa.at(i).name);
	}
	if (listWidgetBsa->count())
	{
		listWidgetBsa->setCurrentRow(0);
		viewParamBsk();
	}
}
void COrbInput::viewParamBsk()
{
	int curRow = listWidget_rezKA->currentRow();
	if ((curRow > listWidget_rezKA->count()) || (curRow < 0))
	{
		QMessageBox::warning(0, QObject::trUtf8("Предупреждение"),
				QObject::trUtf8("Выбрите КА"));
		return;
	}

	int curBsa = listWidgetBsa->currentRow();
	if ((curBsa > listWidgetBsa->count()) || (curBsa < 0))
	{
		QMessageBox::warning(0, QObject::trUtf8("Предупреждение"),
				QObject::trUtf8("Выбрите БСА"));
		return;
	}

	comboBoxType->setCurrentIndex(
			m_selectOrbitObj.at(curRow).bsa.at(curBsa).type);
	lineEditName->setText(m_selectOrbitObj.at(curRow).bsa.at(curBsa).name);
	doubleSpinBoxGamma->setValue(
			m_selectOrbitObj.at(curRow).bsa.at(curBsa).gamma);
	doubleSpinBoxAlfaMounting->setValue(m_selectOrbitObj.at(curRow).bsa.at(
			curBsa).alfaMounting);
	doubleSpinBoxEtaMounting->setValue(m_selectOrbitObj.at(curRow).bsa.at(
			curBsa).etaMounting);
    doubleSpinBoxBetaMounting->setValue(m_selectOrbitObj.at(curRow).bsa.at(
            curBsa).betaMounting);
	doubleSpinBoxDeltaTau->setValue(
			m_selectOrbitObj.at(curRow).bsa.at(curBsa).deltaTau);
	doubleSpinBoxDeltaN->setValue(
			m_selectOrbitObj.at(curRow).bsa.at(curBsa).deltaN);
	doubleSpinBoxDeltaB->setValue(
			m_selectOrbitObj.at(curRow).bsa.at(curBsa).deltaB);
}

void COrbInput::addParamBsa()
{
	pushButtonAddBsa->setEnabled(false);
	pushButtonEditBsa->setEnabled(false);
	pushButtonDelBsa->setEnabled(false);
	listWidgetBsa->setEnabled(false);

	pushButtonSaveBsa->setEnabled(true);
	comboBoxType->setEnabled(true);
	lineEditName->setEnabled(true);
	doubleSpinBoxGamma->setEnabled(true);
	doubleSpinBoxAlfaMounting->setEnabled(true);
	doubleSpinBoxEtaMounting->setEnabled(true);
    doubleSpinBoxBetaMounting->setEnabled(true);
	doubleSpinBoxDeltaTau->setEnabled(true);
	doubleSpinBoxDeltaN->setEnabled(true);
	doubleSpinBoxDeltaB->setEnabled(true);
	m_flagBsa = false;
}

void COrbInput::editParamBsa()
{
	int curRow = listWidget_rezKA->currentRow();
	if ((curRow > listWidget_rezKA->count()) || (curRow < 0))
	{
		QMessageBox::warning(0, QObject::trUtf8("Предупреждение"),
				QObject::trUtf8("Выбрите КА"));
		return;
	}

	int curBsa = listWidgetBsa->currentRow();
	if ((curBsa > listWidgetBsa->count()) || (curBsa < 0))
	{
		QMessageBox::warning(0, QObject::trUtf8("Предупреждение"),
				QObject::trUtf8("Выбрите БСА"));
		return;
	}

	pushButtonAddBsa->setEnabled(false);
	pushButtonEditBsa->setEnabled(false);
	pushButtonDelBsa->setEnabled(false);
	listWidgetBsa->setEnabled(false);

	pushButtonSaveBsa->setEnabled(true);
	comboBoxType->setEnabled(true);
	lineEditName->setEnabled(true);
	doubleSpinBoxGamma->setEnabled(true);
	doubleSpinBoxAlfaMounting->setEnabled(true);
	doubleSpinBoxEtaMounting->setEnabled(true);
    doubleSpinBoxBetaMounting->setEnabled(true);
	doubleSpinBoxDeltaTau->setEnabled(true);
	doubleSpinBoxDeltaN->setEnabled(true);
	doubleSpinBoxDeltaB->setEnabled(true);
	m_flagBsa = true;

}

void COrbInput::delParamBsa()
{
	int curRow = listWidget_rezKA->currentRow();
	int curBsa = listWidgetBsa->currentRow();
	m_selectOrbitObj[curRow].bsa.remove(curBsa);
	fillListWidgetBsk();
}

void COrbInput::saveParamBsa()
{
	pushButtonAddBsa->setEnabled(true);
	pushButtonEditBsa->setEnabled(true);
	pushButtonDelBsa->setEnabled(true);
	listWidgetBsa->setEnabled(true);

	pushButtonSaveBsa->setEnabled(false);
	comboBoxType->setEnabled(false);
	lineEditName->setEnabled(false);
	doubleSpinBoxGamma->setEnabled(false);
	doubleSpinBoxAlfaMounting->setEnabled(false);
	doubleSpinBoxEtaMounting->setEnabled(false);
    doubleSpinBoxBetaMounting->setEnabled(false);
	doubleSpinBoxDeltaTau->setEnabled(false);
	doubleSpinBoxDeltaN->setEnabled(false);
	doubleSpinBoxDeltaB->setEnabled(false);

	ASDBsePar bsad;
	int curRow = listWidget_rezKA->currentRow();
	int curBsa = listWidgetBsa->currentRow();

	if (m_flagBsa)
	{
		m_selectOrbitObj[curRow].bsa[curBsa].type
				= static_cast<BseType> (comboBoxType->currentIndex());
		m_selectOrbitObj[curRow].bsa[curBsa].name = lineEditName->text();
		m_selectOrbitObj[curRow].bsa[curBsa].gamma
				= doubleSpinBoxGamma->value();
		m_selectOrbitObj[curRow].bsa[curBsa].alfaMounting
				= doubleSpinBoxAlfaMounting->value();
		m_selectOrbitObj[curRow].bsa[curBsa].etaMounting
				= doubleSpinBoxEtaMounting->value();
        m_selectOrbitObj[curRow].bsa[curBsa].betaMounting
                = doubleSpinBoxBetaMounting->value();
		m_selectOrbitObj[curRow].bsa[curBsa].deltaTau
				= doubleSpinBoxDeltaTau->value();
		m_selectOrbitObj[curRow].bsa[curBsa].deltaN
				= doubleSpinBoxDeltaN->value();
		m_selectOrbitObj[curRow].bsa[curBsa].deltaB
				= doubleSpinBoxDeltaB->value();
	}
	else
	{
		bsad.type = static_cast<BseType> (comboBoxType->currentIndex());
		bsad.name = lineEditName->text();
		bsad.gamma = doubleSpinBoxGamma->value();
		bsad.alfaMounting = doubleSpinBoxAlfaMounting->value();
		bsad.etaMounting = doubleSpinBoxEtaMounting->value();
        bsad.betaMounting = doubleSpinBoxBetaMounting->value();
		bsad.deltaTau = doubleSpinBoxDeltaTau->value();
		bsad.deltaN = doubleSpinBoxDeltaN->value();
		bsad.deltaB = doubleSpinBoxDeltaB->value();
		m_selectOrbitObj[curRow].bsa.push_back(bsad);
	}

	fillListWidgetBsk();
}

