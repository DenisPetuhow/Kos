#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);



    connect(m_startAction, SIGNAL(clicked()), this, SLOT(slotStart()));

    connect(m_pauseAction, SIGNAL(clicked()), this, SLOT(slotPause()));

    connect(m_stopAction, SIGNAL(clicked()), this, SLOT(slotStop()));

    connect(this, SIGNAL(currentTimeUpdated()), this, SLOT(updatecurTime()));

    connect(dateTimeEdit_curr, SIGNAL(dateTimeChanged(QDateTime)), this,
            SLOT(setInterval()));

    connect(spinBox_step, SIGNAL(valueChanged(int)), this,
            SLOT(onStepChanged()));

    connect(comboBox_step, SIGNAL(currentIndexChanged(int)), this,
            SLOT(onTimeTypeChanged()));

    connect(horizontalSlider, SIGNAL(sliderMoved(int)), this,
            SLOT(setTimeEdit()));


    connect(pushButton_Run, SIGNAL(clicked()), this, SLOT(calc()));

    connect(runBPLA, SIGNAL(clicked()), this, SLOT(calcBPLA()));


    //paint3d.set3D(m_scene);
    paint3d_2.set3D(m_scene2);

    //////////////////////////////////////////////////////////////////
    QVariant tmp;


    m_startAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setEnabled(false);

    QString dirzap=QDir::currentPath()+"/"+"razdan.ini";
    QSettings mSetting(dirzap, QSettings::IniFormat);

    QString StrOrbobj=mSetting.value("Orbobj", tmp).toString();
    QString StrRegobj=mSetting.value("Regobj", tmp).toString();
    QString StrGRCobj=mSetting.value("GRCobj", tmp).toString();
    QString StrGRCRobj=mSetting.value("GRCRobj", tmp).toString();
    QDateTime tim1=mSetting.value("BegMod", tmp).toDateTime();
    QDateTime tim2=mSetting.value("EndMod", tmp).toDateTime();
    FileName = mSetting.value("Polygon",tmp).toString();

    setDateTime(tim1, tim2);
    tab_orbInput->loadDefaultParam(QDir::currentPath()+"/"+StrOrbobj);

    initMap();
    createActions();


    this->update();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initMap()
{
    m_map_control =  new QMapControl(QSizeF(tabWidget->width(), tabWidget->height()));
    m_map_control->moveToThread(&m_head);
    m_head.start();
    m_map_control->setZoomMinimum(1);
    m_map_control->setZoomMaximum(10);

    // Create/add a layer with the default OSM map adapter.
    m_map_control->addLayer(std::make_shared<LayerMapAdapter>("OpenStreetMap-Layer", std::make_shared<MapAdapterOSM>()));

    gridLayout_6->addWidget(m_map_control, 0, 0, 1, 1);

    QObject::connect(m_map_control, &QMapControl::mouseEventPressCoordinate, this, &MainWindow::main_mouseEventPressCoordinate);
    QObject::connect(m_map_control, &QMapControl::mouseEventDoubleClickCoordinate, this, &MainWindow::drawPolygon);


    m_map_control->setZoom(6);
    m_map_control->setMapFocusPoint(PointWorldCoord(34.184,43.1361));

    region_layer= std::make_shared<LayerGeometry>("Notes");
    m_map_control->addLayer(region_layer);

}
void MainWindow::resizeEvent(QResizeEvent * resize_event)
{
    // Set the new viewport size.
    m_map_control->setViewportSize(resize_event->size());
    m_map_control->updateGeometry();

}

void MainWindow::new_Point()
{

    if(tabWidget->currentIndex()== 0 || tabWidget->currentIndex()== 1 ||
            tabWidget->currentIndex()== 2 || tabWidget->currentIndex()== 3){

        return;
    }

    if(tabWidget->currentIndex()== 4){

        //flag_create_Point = true;
        PointWorldCoord  pointWorld;
        QString str;
        str = ":/icons/2.png";

        countPoint *= -1;

        if(countPoint == 1){

            BPLA_lon_0->setText(QString::fromUtf8("%1").arg(current_Point_world.longitude()));
            BPLA_lat_0->setText(QString::fromUtf8("%1").arg(current_Point_world.latitude()));

            raw_points.clear();
            pointWorld = PointWorldCoord(BPLA_lon_0->text().toDouble(), BPLA_lat_0->text().toDouble());

        }else{

            BPLA_lon_fin->setText(QString::fromUtf8("%1").arg(current_Point_world.longitude()));
            BPLA_lat_fin->setText(QString::fromUtf8("%1").arg(current_Point_world.latitude()));

            pointWorld = PointWorldCoord(BPLA_lon_fin->text().toDouble(), BPLA_lat_fin->text().toDouble());

        }

        raw_points.push_back(pointWorld);

        std::shared_ptr<GeometryPointImage> pathBpLA(std::make_shared<GeometryPointImage>(pointWorld,str, 8, 10));
        pathBpLA->setAlignmentType(GeometryPoint::AlignmentType::Middle);

        view_points.emplace_back(pointWorld);
        m_map_control->setMapFocusPointAnimated(pointWorld);

        pathBpLA->setVisible(true);
        pathBpLA->setMetadata("name", "reg.name");

        region_layer->addGeometry(pathBpLA);

        if(countPoint != 1){

            std::shared_ptr<GeometryLineString> line_string(std::make_shared<GeometryLineString>(raw_points,8,10));
            QPen line_pen(QColor(0, 0,255, 70));
            line_pen.setWidth(3);
            line_pen.setStyle(Qt::DotLine);
            line_string->setPen(line_pen);
            line_string->setMetadata("name", "path bpla");

            double tp=M_PI/2.- BPLA_lat_0->text().toDouble()*DEG_TO_RAD;
            double ts=M_PI/2.- BPLA_lat_fin->text().toDouble()*DEG_TO_RAD;
            double fp= BPLA_lon_0->text().toDouble()*DEG_TO_RAD;
            double fs= BPLA_lon_fin->text().toDouble()*DEG_TO_RAD;

            double length_bpla=acos(cos(tp)*cos(ts)+sin(tp)*sin(ts)*cos(fs-fp))*R_EARTH;

            QPixmap* pixmap = new QPixmap(75,20);
            pixmap->fill(Qt::transparent);
            QPainter painter(pixmap);
            painter.setFont(QFont("Helvetiva", 10, QFont::Bold));

            painter.drawText(pixmap->rect(),  QString("%1 км").arg(length_bpla));
            painter.end();
            PointWorldCoord p_coord;
            p_coord.setLatitude(BPLA_lat_fin->text().toDouble());
            p_coord.setLongitude(BPLA_lon_fin->text().toDouble());
            std::shared_ptr<GeometryPointImage> point_end(std::make_shared<GeometryPointImage>(p_coord, *pixmap,8,10));
            point_end->setAlignmentType(GeometryPoint::AlignmentType::BottomMiddle);
            region_layer->addGeometry(point_end);

            region_layer->addGeometry(line_string,true);

        }

        region_layer->setVisible(true);

    }

}

void MainWindow::new_Polygon()
{
    if(tabWidget->currentIndex()== 0 || tabWidget->currentIndex()== 1 ||
            tabWidget->currentIndex()== 2 || tabWidget->currentIndex()== 3){

        return;
    }

    if(tabWidget->currentIndex()== 4){

        flag_Polygon = true;
        points_Polygon.clear();
        label_6->setText("РЕЖИМ СОЗДАНИЯ ОБЛАСТИ\nДвойной клик - добавление точки\nДля завершения нажмите среднюю кнопку мыши");

        qDebug()<<"Режим создания полигона";

    }

}

void MainWindow::load_Polygon()
{
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly)){

        return;

    }

    QFileInfo fileInfo(FileName);
    points_Polygon.clear();

    QString lineCoord;
    QTextStream fileCoord(&file);

    while (!fileCoord.atEnd())
    {
        lineCoord = fileCoord.readLine();
        QStringList list = lineCoord.split(' ');
        PointWorldCoord _pointCoord;
        _pointCoord.setLongitude(list[0].toDouble());
        _pointCoord.setLatitude(list[1].toDouble());

        points_Polygon.push_back(_pointCoord);
    }

    std::shared_ptr<GeometryPolygon> line_stringPolygon;
    line_stringPolygon= std::make_shared<GeometryPolygon>(points_Polygon,5,10);
    QPen line_pen(QColor(0, 0,255, 70));
    line_pen.setWidth(2);
    line_pen.setStyle(Qt::DotLine);
    line_stringPolygon->setPen(line_pen);
    line_stringPolygon->setBrush(QColor(0, 0, 255, 1));
    line_stringPolygon->setMetadata("name", "line_polygon");
    region_layer->addGeometry(line_stringPolygon,true);
    region_layer->setVisible(true);

}


void MainWindow::timerEvent(QTimerEvent *t)
{
    dateTimeEdit_curr->setDateTime(m_curtime.addSecs(time_step));
    m_curtime.setDate(dateTimeEdit_curr->date());
    m_curtime.setTime(dateTimeEdit_curr->time());

    //m_scene->repaintObjects3D(m_curtime);
    m_scene2->repaintObjects3D(m_curtime);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{

    if(tabWidget->currentIndex()== 4){
        QMenu menu(m_map_control);
        menu.addAction(Create_Point);
        menu.addAction(Create_Polygon);
        menu.addAction(Load_Polygon);
        menu.exec(event->globalPos());
    }
    else {
        return;
    }

}

void MainWindow::createActions()
{
    Create_Point = new QAction(tr("&Создать маршрутную точку"), this);
    connect(Create_Point, SIGNAL(triggered()), this, SLOT(new_Point()));

    Create_Polygon = new QAction(tr("&Создать область"),this);
    connect(Create_Polygon, SIGNAL(triggered()), this, SLOT(new_Polygon()));

    Load_Polygon = new QAction(tr("&Загрузить область"),this);
    connect(Load_Polygon, SIGNAL(triggered()), this, SLOT(load_Polygon()));

}

void MainWindow::drawPolygon()
{
    std::vector<PointWorldCoord> Line_Points;
    PointWorldCoord  pointWorld;
    QString str;
    str = ":/icons/2.png";
    std::shared_ptr<GeometryPolygon> line_stringPolygon;

    if(flag_Polygon == true){


        points_Polygon.push_back(current_Point_world);

        //добавление точки на карту
        std::shared_ptr<GeometryPointImage> pathPolygon(std::make_shared<GeometryPointImage>(current_Point_world,str, 8, 10));

        pathPolygon->setAlignmentType(GeometryPoint::AlignmentType::Middle);

        Line_Points.emplace_back(current_Point_world);
        m_map_control->setMapFocusPointAnimated(current_Point_world);

        pathPolygon->setVisible(true);
        pathPolygon->setMetadata("name", "polygon");

        region_layer->addGeometry(pathPolygon);
    }else{

        points_Polygon.push_back(points_Polygon[0]);

        line_stringPolygon= std::make_shared<GeometryPolygon>(points_Polygon,8,10);
        QPen line_pen(QColor(0, 0,255, 70));
        line_pen.setWidth(3);
        line_pen.setStyle(Qt::DotLine);
        line_stringPolygon->setPen(line_pen);
        line_stringPolygon->setBrush(QColor(220, 10,5, 40));

        line_stringPolygon->setMetadata("name", "line_polygon");
        region_layer->addGeometry(line_stringPolygon,true);
        region_layer->setVisible(true);
    }







}

void MainWindow::slotStart()
{
    m_timerID = startTimer(1 * 1000);
    m_curtime.setDate(dateTimeEdit_curr->date());
    m_curtime.setTime(dateTimeEdit_curr->time());

    m_startAction->setEnabled(false);
    m_pauseAction->setEnabled(true);
    m_stopAction->setEnabled(true);
}

void MainWindow::slotPause()
{
    killTimer(m_timerID);
    m_startAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setEnabled(false);
}

void MainWindow::slotStop()
{
    killTimer(m_timerID);
    m_startAction->setEnabled(true);
    m_stopAction->setEnabled(false);
    m_pauseAction->setEnabled(false);
    QVariant tmp = "2023-03-29 00:00:00";
    QDateTime tim1  = tmp.toDateTime();
    tmp = "2023-03-30 00:00:00";
    QDateTime tim2  = tmp.toDateTime();
    setDateTime(tim1,tim2);

}

void MainWindow::updatecurTime()
{
    vis2D->setCurrentTimepos(m_curtime);

}

void MainWindow::setInterval()
{
    int sec = m_begintime.secsTo(dateTimeEdit_curr->dateTime());
    m_curtime.setDate(dateTimeEdit_curr->date());
    m_curtime.setTime(dateTimeEdit_curr->time());
    onTimeTypeChanged();
    horizontalSlider->setValue(sec);

    if (m_startAction)
    {

        //m_scene->repaintObjects3D(m_curtime);
        //m_scene2->repaintObjects3D(m_curtime);
        vis2D->setCurrentTimepos(m_curtime);
        // page_reg->setcurrentTime(m_curtime);
        emit currentTimeUpdated();
    }
}

void MainWindow::onStepChanged()
{
    switch (comboBox_step->currentIndex())
    {
    case 0:
        time_step = 1;
        break;
    case 1:
        time_step = 60;
        break;
    case 2:
        time_step = 3600;
        break;
    case 3:
        time_step = 86400;
        break;
    }
    time_step *= spinBox_step->value();
}

void MainWindow::onTimeTypeChanged()
{
    timeType = comboBox_step->currentIndex();
    onStepChanged();
}

bool MainWindow::setDateTime(QDateTime begintime, QDateTime endtime)
{
    m_begintime = begintime;
    m_endtime = endtime;
    dateTimeEdit_begin->setDateTime(m_begintime);
    dateTimeEdit_end->setDateTime(m_endtime);
    horizontalSlider->setMaximum(m_begintime.secsTo(m_endtime));
    horizontalSlider->setMinimum(0);

    dateTimeEdit_curr->setDateTime(m_begintime);

    time_step = 1;
    spinBox_step->setValue(1);
    return true;
}

void MainWindow::setTimeEdit()
{
    dateTimeEdit_curr->setDateTime(m_begintime.addSecs(horizontalSlider->value()));
    dateTimeEdit_curr->update();
}

void MainWindow::calc()
{
    setDateTime(dateTimeEdit_begin->dateTime(),dateTimeEdit_end->dateTime());
    m_curtime=dateTimeEdit_begin->dateTime();
    m_VecOrbobj=tab_orbInput->getOrbitalObjectPar();

    facilitypoint tt;
    QVector<QString> ska;
    ska.resize(m_VecOrbobj.size());
    for (int j = 0; j < m_VecOrbobj.size(); j++)
    {

        QDateTime currtime0 =  dateTimeEdit_begin->dateTime();

        ASDOrbitalObjectPar posorb = m_VecOrbobj[j];
        posorb.kep.i *= DEG_TO_RAD;
        posorb.kep.l *= DEG_TO_RAD;
        posorb.kep.omega *= DEG_TO_RAD;
        posorb.kep.u *= DEG_TO_RAD;
        double gammaMax=0.;
        if (posorb.type_dat==2){
            posorb.kep.a=7371;
        }
        const double n = sqrt(K_EARTH / pow(posorb.kep.a, 3));

        double Tp=2.0 * M_PI / n;

        Tp=fabs(dateTimeEdit_begin->dateTime().secsTo(dateTimeEdit_begin->dateTime().addDays(1))/10.);
        for(int i=0;i<Tp;i+=10)

        {
            QDateTime currtime=currtime0.addSecs(10*i);

            QString strnam;
            QVector<double> pos(6);
            ASDOrbitalMotion OrbitMotion;

            if(posorb.type_dat==0)
                ska[j]=posorb.kep.name;
            if(posorb.type_dat==1)
                ska[j]=posorb.ags.name;
            if(posorb.type_dat==2)
                ska[j]=posorb.stle.satName;
            if (posorb.type_dat == 0){

                OrbitMotion.setBeginParam(posorb.kep);
                OrbitMotion.setIntegrateParam(0);
                strnam=posorb.kep.name;
                gammaMax=M_PI_2-asin(6370./ posorb.kep.a);
                gammaMax*=RAD_TO_DEG;
            }
            if (posorb.type_dat == 1){
                posorb.forcedan.grvModel = 0;
                OrbitMotion.setBeginParam(posorb.ags);
                OrbitMotion.setEquationOfParam(posorb.forcedan);
                OrbitMotion.setIntegrateParam(1);
                strnam=posorb.ags.name;

            }
            if (posorb.type_dat == 2){
                OrbitMotion.setBeginParam(posorb.stle);
                OrbitMotion.setIntegrateParam(2);
                strnam=posorb.stle.satName;

                gammaMax=M_PI_2-asin(6370./ (6371+800.));


            }

            pos = OrbitMotion.getPosition(currtime);

            double r_ka = pow(pos[0]*pos[0]+pos[1]*pos[1]+pos[2]*pos[2],0.5);
            double gamma_lim = asin(R_EARTH/r_ka);
            gammaMax=gamma_lim*RAD_TO_DEG;

            QVector<double> post=ASDCoordConvertor::convGscToGeo(ASDCoordConvertor::convAgescToGsc(pos,currtime));

            tt.name=strnam;
            tt.lat=post[0]*RAD_TO_DEG;
            tt.lon=post[1]*RAD_TO_DEG;

            if(tt.lon>180) tt.lon-=360;
            m_trassa.insertMulti(j,tt);
        }

        m_KA.append(tt);
    }

    qDebug()<<"trassa end";


    //paint3d.setKa(m_VecOrbobj);


    paint3d_2.setKa(m_VecOrbobj);
    /////////////////////////////////////////

    paint3d_2.calc();
    vis2D->setParamKA(m_VecOrbobj);
    vis2D->settrassa(m_trassa,m_KA);

    m_scene2->repaintObjects3D(m_curtime);
    vis2D->setCurrentTimepos(m_curtime);

    paint3d_2.repaint(m_curtime);
    m_startAction->setEnabled(true);
    m_pauseAction->setEnabled(false);
    m_stopAction->setEnabled(false);

}


void MainWindow::calcBPLA()
{

    countBpLA++;

    //задание начальных условий для БПЛА
    ASD_bpla_struct BPLA;

    BPLA.id_bpla = countBpLA;
    BPLA.speed_bpla = BPLA_speed->text().toDouble();
    BPLA.lon0_bpla = BPLA_lon_0->text().toDouble();
    BPLA.lat0_bpla = BPLA_lat_0->text().toDouble();
    BPLA.lon_fin_bpla = BPLA_lon_fin->text().toDouble();
    BPLA.lat_fin_bpla = BPLA_lat_fin->text().toDouble();
    BPLA.t0_runBPLA.setDate(dateTimeEdit_curr->date());
    BPLA.t0_runBPLA.setTime(dateTimeEdit_curr->time());
    BPLA.time_interval = info_period->text().toInt()*60;//в секунды

    m_VecBpLA.push_back(BPLA);


    paint3d_2.setBpLA(m_VecBpLA);
    paint3d_2.calc_bpla();

    //расчет плана
    planBpLA.set_KA(m_VecOrbobj);
    planBpLA.set_BpLA(BPLA); // расчет для текущего БпЛА


    QMap<int, t_plan_bpla> map;
    map= planBpLA.get_BpLA();
    tableWidget->setRowCount(map.size());
    QTableWidgetItem *it;
    QMap<int, t_plan_bpla>::Iterator it1 = map.begin();


    int k =0;
    for (; it1 != map.end(); ++it1)
    {
        t_plan_bpla _pl;
        _pl = it1.value();

        it = new QTableWidgetItem(QString("%1").arg(_pl.KA.stle.satName));
        tableWidget->setItem(k,0,new QTableWidgetItem(QString("%1").arg(it1.key())));
        tableWidget->setItem(k,1,it);
        k++;

        qDebug()<<k<<it1.key()<<_pl.time.date()<<_pl.time.time()<<_pl.KA.stle.satName;
    }


    QVector <QVector <double> > _vec;
    QStringList titles = planBpLA.get_result_list();
    QString str = QString::fromUtf8("Гистограмма доступности КА");
    _vec = planBpLA.get_result();

    qDebug()<<_vec;

    widget->setDat(_vec,titles,str);

}

void MainWindow::calcraspprog(int pp)
{
    m_prgrun.setValue(pp);
}

void MainWindow::main_mouseEventPressCoordinate(QMouseEvent *mouse_event, PointWorldCoord press_coordinate)
{

    label_5->setText(QString::fromUtf8("Широта=%1 град; Долгота =%2 град").arg(press_coordinate.latitude()).arg(press_coordinate.longitude()));
    current_Point_world.setLatitude(press_coordinate.latitude());
    current_Point_world.setLongitude(press_coordinate.longitude());


    if(mouse_event->button() == Qt::MouseButton::MiddleButton && flag_Polygon == true){

        flag_Polygon=false;
        label_6->setText("");

        emit m_map_control->mouseEventDoubleClickCoordinate(mouse_event, press_coordinate, press_coordinate);

        qDebug()<<"Создание полигона завершено!";

    }

};





