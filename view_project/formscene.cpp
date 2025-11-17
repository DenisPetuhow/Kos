#include "formscene.h"
#include <math.h>
#include <QFuture>
#include <QFutureWatcher>
#include <QThreadPool>
#include <QGraphicsItem>
#include <QPixmap>
#include "ASD/clipper.hpp"
static double DEG2PXHZ;
static double DEG2PXVT;
static const double T360 = 360.;
static const double DEG2RAD = M_PI / 180.;
static const double RAD2DEG = 1. / DEG2RAD;

QVector<QPointF> CalculZoneVisibilitef(double _latitude,double _longitude,double H,double gammlim  )
{
    QVector<QPointF> _zone;
    /* Declarations des variables locales */
    double lo1;

    static const double PI = 3.14159265358979323846264;
    static const double DEUX_PI = 2. * PI;
    static const double PI_SUR_DEUX = 0.5 * PI;
    static const double DEUX_TIERS = 2. / 3.;


    static const double ARCMIN_PAR_DEG = 60.;
    static const double ARCSEC_PAR_MIN = 60.;
    static const double ARCSEC_PAR_DEG = 3600.;

    // static const double DEG2RAD = PI / 180.;
    static const double ARCSEC2RAD = PI / 648000.;
    static const double HEUR2RAD = PI / 12.;

    static const double DEUX_SUR_PI = 1. / PI_SUR_DEUX;
    static const double DEG_PAR_ARCMIN = 1. / ARCMIN_PAR_DEG;
    static const double DEG_PAR_ARCSEC = 1. / ARCSEC_PAR_DEG;
    static const double RAD2DEG = 1. / DEG2RAD;
    static const double RAD2HEUR = 1. / HEUR2RAD;
    /* Initialisations */
    double lo0 = _longitude;
    if (lo0 > 0.)
        lo0 -= DEUX_PI;
    const double cl0 = cos(_latitude);
    const double sl0 = sin(_latitude);
    // double beta = acos((6371.0 - 5.) / (6371.0+H))-5.0*DEG2RAD;
    double beta = acos((6371.0+50 ) / (6371.0+H));
    if( gammlim >0)
    {
        beta=gammlim;
    }
    //  if(beta<5.0*DEG2RAD) beta=22.0*DEG2RAD;
    // beta = acos(sin(25.0*DEG2RAD)*(6371.0+H)/R_EARTH);
    // beta*=0.5;
    //double betaLIM = asin((6371.0+650)/(6371.0+H )  );
    // //qDebug()<<"h="<<H<<"BETA=="<<beta*RAD_TO_DEG<<beta*RAD_TO_DEG*110.<<betaLIM*RAD_TO_DEG<<betaLIM*RAD_TO_DEG*110.;
    // if (std::isnan(beta))
    //    beta = 0.;
    // beta=asin(H*sin(10.0*DEG2RAD)/6371.0)-10.*DEG2RAD;
    const double cb = cos(beta);
    const double sb = sin(beta);

    /* Corps de la methode */

    for(int i=0; i<360; i++) {

        const double az = DEG2RAD * i;
        const double la1 = asin(sl0 * cb + cos(az) * sb * cl0);

        if (i == 0 && beta > PI_SUR_DEUX - _latitude) {
            lo1 = lo0 + PI;
        } else {
            if (i == 180 && beta > PI_SUR_DEUX + _latitude) {
                lo1 = lo0 + PI;
            } else {
                const double numden = (cb - sl0 * sin(la1)) / (cl0 * cos(la1));
                if (fabs(numden > 1.)) {
                    lo1 = lo0;
                } else {
                    lo1 = (i <= 180) ? lo0 + acos(numden) : lo0 - acos(numden);
                }
            }
        }
        //const QPointF pt(fmod(PI - lo1, DEUX_PI) * RAD2DEG, (PI_SUR_DEUX - la1) * RAD2DEG);
        // const QPointF pt(fmod(lo1, DEUX_PI) * RAD2DEG, (PI_SUR_DEUX - la1) * RAD2DEG);
        double lon=fmod(lo1, DEUX_PI);
        if(lon>M_PI) lon-=2.*M_PI;
        if(lon<M_PI) lon+=2.*M_PI;
        const QPointF pt(lon * RAD2DEG, (PI_SUR_DEUX - la1) * RAD2DEG);
        // ppp oooo;

        _zone.append(pt);
    }
    _zone.append(_zone.at(0));


    return _zone;
}
Formscene::Formscene(QWidget *parent) :
    QWidget(parent)

{
    setupUi(this);
    DEG2PXHZ = 1. / 0.45;
    DEG2PXVT = 1. / 0.45;
    this->connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
                  this, SLOT(visibilObj()));


    scene = new QGraphicsScene(this);
    //setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    this->showMaximized();
    // this->show();
    scene->installEventFilter(this);

    // this->show();
    QResizeEvent *event;
    offSize=graphicsView->size();
    composedOffscreenImage = QPixmap(offSize);

    const QString nomMap = ":/images/map0.png" ;


    resizeEvent(event);
    m_carte=QPixmap(nomMap).scaled(graphicsView->size());
    scene->setSceneRect(graphicsView->rect());
    treeWidget->hideColumn(1);

    //    // группа выбор объекта
    //    itemKA = new QTreeWidgetItem(treeWidget);
    //    itemKA->setText(0, QObject::trUtf8("КА"));
    //    itemKA->setText(1, QObject::trUtf8("0"));
    //    itemREG = new QTreeWidgetItem(treeWidget);
    //    itemREG->setText(0, QObject::trUtf8("Район"));
    //    itemREG->setText(1, QObject::trUtf8("1"));
    loadscene();

}

Formscene::~Formscene()
{
    //delete ui;
}
void Formscene::clear()
{
    treeWidget->clear();
    scene->clear();
    m_satobz.clear();

    if(m_reg.size()>0) m_reg.clear();
    m_checkedbool.clear();
    m_checkeregdbool.clear();
    m_checkePPIdbool.clear();
    m_checkePPUdbool.clear();

    if(m_currentKA.size()>0) m_currentKA.clear();
    if(m_currentKAZon.size()>0) m_currentKAZon.clear();
    if(m_currentKAZon2.size()>0) m_currentKAZon2.clear();

}

void Formscene::settrassa( QMap<int, facilitypoint> trassa,QList<facilitypoint> KA)
{

    //   treeWidget->clear();
    //    scene->clear();
    //itemKA->c>removeChild(treeWidget);
    itemKA = new QTreeWidgetItem(treeWidget);
    itemKA->setText(0, QObject::trUtf8("КА"));
    itemKA->setText(1, QObject::trUtf8("0"));
    if(m_trassa.size()>0) m_trassa.clear();
    m_trassa=trassa;
    if(m_currentKA.size()>0) m_currentKA.clear();
    m_currentKA=KA;
    if(itemKA->childCount()>0)
    {
        //qDebug()<<"pos treew="<<itemKA->childCount();
        for(int k=0;k<itemKA->childCount();k++)
        {
            //itemKA->takeChild(k);
            itemKA->takeChild(itemKA->indexOfChild(itemKA->child(k)));
        }
    }



    if(KA.size()>0)
    {

        m_checkedbool.clear();
        //
        for(int k=0;k<KA.size();k++)
        {
            QTreeWidgetItem* item_1 = new QTreeWidgetItem(itemKA);//item1->child(0);
            item_1->setText(0, KA.at(k).name);
            QColor color = QColor::fromHsv(k * (359/KA.size()), 255, 255);
            item_1->setTextColor(0,color);


            // m_checkedbool.append(false);
            if(k==0)
            {
                m_checkedbool.append(true);
                item_1->setCheckState(0,Qt::Checked);
            }
            else
            {

                m_checkedbool.append(false);
                item_1->setCheckState(0,Qt::Unchecked);

            }
            item_1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsTristate| Qt::ItemIsUserCheckable| Qt::ItemIsEnabled );
        }

        //
        //  satDecorator->setviz(m_checkedbool);
        //  satDecorator->enable(true);
        //  TrassaAction->setDisabled(false);
        //  satDecorator->enablez(false);
        //TrassaObzorAction->setDisabled(false);

        // trassaset();

        //        // paintr=QPainter(painter.device());
        //       QFuture<void> future;
        //       QFutureWatcher<void>* fw;
        //       fw = new QFutureWatcher<void>(this);
        //       QThreadPool* pool = QThreadPool::globalInstance();

        //       int numth = pool->activeThreadCount();
        //       int maxth = pool->maxThreadCount();
        //       if ( numth == maxth ) {
        //           pool->setMaxThreadCount(++numth);
        //       }
        //      // //qDebug()<<"CALLIISA  run start"<<QTime().currentTime();
        //       connect( fw, SIGNAL( finished() ), fw, SLOT( deleteLater() ) );

        //       future = QtConcurrent::run( this, &Formscene::trassaset );

        //       fw->setFuture(future);
        //trassaset();
        calcposKA();

    }
    loadscene();
}
void Formscene::trassaset()
{
    QPen pen;

    //  scene->clear();
    //loadscene();
    const int hcarte = graphicsView->height() ;
    const int lcarte = graphicsView->width();
    // const int hcarte2 = qRound(hcarte * 0.5);
    const int lcarte2 = qRound(lcarte * 0.5);
    int isiz=0;
    if(m_currentKA.size()==0) return;
    m_satobz.clear();
    for(int k=0;k<m_currentKA.size();k++)
    {

        //facilitypoint kat= m_trassa[k];
        QVector<QPointF> ztr;


        if(m_checkedbool.at(k))
        {
            pen.setColor(QColor::fromHsv(k * (359/m_currentKA.size()), 255, 255));
            pen.setWidth(2);
            pen.setCosmetic(true);
            QMap<int,facilitypoint>::Iterator tr=m_trassa.find(k);
            while (tr != m_trassa.end() && tr.key() == k) {

                facilitypoint postr=tr.value();
                ztr.append(QPointF((180-postr.lon)*DEG2PXHZ, (90-postr.lat)*DEG2PXVT));
                // scene->addEllipse((180-postr.lon)*DEG2PXHZ, (90-postr.lat)*DEG2PXVT,2,2,pen,Qt::NoBrush);
                //painter.drawText((180-m_currentKA.at(i).lon)*DEG2PXHZ+6, (90-m_currentKA.at(i).lat)*DEG2PXVT+8, m_currentKA.at(i).name);
                // painter.drawPixmap(m_currentKA.at(i).x(),m_currentKA.at(i).y(),pm);
                //QPolygonF polka1=map_zonKA[i];
                //      //qDebug()<<"pos=ka ="<<m_currentKA.at(k).lon<<m_currentKA.at(k).lat<<m_currentKA.at(k).name<<m_currentKA.size();
                ++tr;

                isiz+=1;
            }
        }

        if(ztr.size()>0)
        {
            ////qDebug()<<"pos=m_currentKAZon.size() ="<<m_currentKAZon.size();
            for(int i=1;i<ztr.size();i++)
            {
                int lsat1 = qRound(ztr.at(i-1).x() );
                int bsat1 = qRound(ztr.at(i-1).y()  + 1);
                int lsat2 = qRound(ztr.at(i).x());
                int bsat2 = qRound(ztr.at(i).y() + 1) ;

                int ils = 99999;

                if (fabs(lsat2 - lsat1) > lcarte2) {
                    if (lsat2 < lsat1)
                        lsat2 += lcarte;
                    else
                        lsat1 += lcarte;
                    ils = i;

                }

                QGraphicsLineItem* gr=new QGraphicsLineItem();
                gr->setLine(lsat1, bsat1, lsat2, bsat2);
                gr->setPen(pen);

                m_satobz.append(gr);

                if (ils == i) {
                    lsat1 -= lcarte;
                    lsat2 -= lcarte;
                    // scene->addLine(lsat1, bsat1, lsat2, bsat2, pen);
                    QGraphicsLineItem* gr=new QGraphicsLineItem();
                    gr->setLine(lsat1, bsat1, lsat2, bsat2);
                    gr->setPen(pen);

                    m_satobz.append(gr);
                    ils = 0;
                }

                // scene->addLine(lsat1, bsat1, lsat2, bsat2, pen);
                QGraphicsLineItem* gre=new QGraphicsLineItem();
                gre->setLine(lsat1, bsat1, lsat2, bsat2);
                gre->setPen(pen);

                m_satobz.append(gre);

            }
        }
    }
    if(m_currentKAZon.size()>0)
    {
        for (int j=0;j<m_currentKAZon.size();++j)
        {
            QVector<QPointF> zoneF=m_currentKAZon[j];
            for (int i=1;i<zoneF.size();++i)
            {
                QPen crayon(Qt::yellow);
                crayon.setWidth(4);


                int lsat1 = qRound(zoneF.at(i-1).x() * DEG2PXHZ);
                int bsat1 = qRound(zoneF.at(i-1).y() * DEG2PXVT + 1);
                int lsat2 = qRound(zoneF.at(i).x() * DEG2PXHZ);
                int bsat2 = qRound(zoneF.at(i).y() * DEG2PXVT + 1) ;


                int ils = 99999;

                if (fabs(lsat2 - lsat1) > lcarte2) {
                    if (lsat2 < lsat1)
                        lsat2 += lcarte;
                    else
                        lsat1 += lcarte;
                    ils = i;

                }


                scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                if (ils == i) {
                    lsat1 -= lcarte;
                    lsat2 -= lcarte;
                    scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                    ils = 0;
                }



                scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

            }


        }
    }
    //scene->update(graphicsView->rect());
    //graphicsView->setScene(scene);
    //graphicsView->update();

    //  QGraphicsView view(scene);
    //   view.setRenderHints(QPainter::Antialiasing);

}

void Formscene::setObjPoint(QList<facilitypoint> Obj)
{

}

void Formscene::setParamKA(QVector<ASDOrbitalObjectPar> kapar)
{
    // scene->clear();
    //  graphicsView->clearMask();
    m_kapar=kapar;
}

void Formscene::setCurrentTimepos(QDateTime tim)
{

    m_currenttime=tim;
    scene->clear();
    graphicsView->clearMask();

    calcposKA();

    loadscene();





}
void Formscene::postka()
{
    const int hcarte = graphicsView->height() ;
    const int lcarte = graphicsView->width();

    const int lcarte2 = qRound(lcarte * 0.5);
    if(m_currentKAZon.size()==0) return;
    for (int j=0;j<m_currentKAZon.size();++j)
    {
        QVector<QPointF> zoneF=m_currentKAZon[j];
        // //qDebug()<<"zoneF=="<<zoneF.size();
        for (int i=1;i<zoneF.size();++i)
        {
            QPen crayon(Qt::yellow);
            crayon.setWidth(4);


            int lsat1 = qRound(zoneF.at(i-1).x() * DEG2PXHZ);
            int bsat1 = qRound(zoneF.at(i-1).y() * DEG2PXVT + 1);
            int lsat2 = qRound(zoneF.at(i).x() * DEG2PXHZ);
            int bsat2 = qRound(zoneF.at(i).y() * DEG2PXVT + 1) ;


            int ils = 99999;

            if (fabs(lsat2 - lsat1) > lcarte2) {
                if (lsat2 < lsat1)
                    lsat2 += lcarte;
                else
                    lsat1 += lcarte;
                ils = i;

            }


            scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

            if (ils == i) {
                lsat1 -= lcarte;
                lsat2 -= lcarte;
                scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                ils = 0;
            }



            scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

        }


    }


    //graphicsView->setScene(scene);
    //graphicsView->update();
}


void Formscene::calcposKA()
{
    if(m_currentKA.size()>0) m_currentKA.clear();
    if(m_currentKAZon.size()>0) m_currentKAZon.clear();
    if(m_currentKAZon2.size()>0) m_currentKAZon2.clear();
    for (int j=0;j<m_kapar.size();++j)
    {
        ASDOrbitalObjectPar posorb = m_kapar.at(j);
        posorb.kep.i *= DEG_TO_RAD;
        posorb.kep.l *= DEG_TO_RAD;
        posorb.kep.omega *= DEG_TO_RAD;
        posorb.kep.u *= DEG_TO_RAD;
        double gammaMax=15.* DEG_TO_RAD;
        facilitypoint tt;
        QString strnam;


        //  t_seans.clear();
        QVector<double> pos(6);

        ASDOrbitalMotion OrbitMotion;
        if (posorb.type_dat == 0)

        {

            OrbitMotion.setBeginParam(posorb.kep);
            OrbitMotion.setIntegrateParam(0);
            strnam=posorb.kep.name;

        }
        if (posorb.type_dat == 1)
        {
            posorb.forcedan.grvModel = 0;
            OrbitMotion.setBeginParam(posorb.ags);
            OrbitMotion.setEquationOfParam(posorb.forcedan);
            OrbitMotion.setIntegrateParam(1);
            strnam=posorb.ags.name;

        }
        if (posorb.type_dat == 2)
        {
            OrbitMotion.setBeginParam(posorb.stle);
            OrbitMotion.setIntegrateParam(2);
            strnam=posorb.stle.satName;

        }

        pos = OrbitMotion.getPosition(m_currenttime);
        QVector<double> post=ASDCoordConvertor::convGscToGeo(ASDCoordConvertor::convAgescToGsc(pos,m_currenttime));

        double r = pow(pow(pos[0],2)+pow(pos[1],2)+pow(pos[2],2),0.5);
        tt.name=strnam;
        tt.lat=post[0]*RAD_TO_DEG;
        tt.lon=post[1]*RAD_TO_DEG;
        tt.h=r;
        if(tt.lon>180) tt.lon-=360;

        QVector<QPointF> zoneF=  CalculZoneVisibilitef(post[0],post[1],post[2],-1. );
        m_currentKAZon.append(zoneF);
        //    if(j<5)
        //    {
        //      QVector<QPointF> zoneF2=  CalculZoneVisibilitef(post[0],post[1],post[2],gammaMax );
        //      m_currentKAZon2.append(zoneF2);
        //    }
        // //qDebug()<<"zone ka=="<<zoneF.size();
        m_currentKA.append(tt);
    }
    //emit sendcursat(m_currentKA);
}
void Formscene::setRegion(QVector<Paramregion > reg)
{
    m_reg.clear();
    m_reg=reg;
    itemREG = new QTreeWidgetItem(treeWidget);
    itemREG->setText(0, QObject::trUtf8("Район"));
    itemREG->setText(1, QObject::trUtf8("1"));
    if(itemREG->childCount()>0)
    {
        ////qDebug()<<"pos treew="<<itemKA->childCount();
        for(int k=0;k<itemREG->childCount();k++)
        {
            //itemKA->takeChild(k);
            itemREG->takeChild(itemREG->indexOfChild(itemREG->child(k)));
        }
    }



    if(reg.size()>0)
    {

        m_checkeregdbool.clear();
        //
        for(int k=0;k<reg.size();k++)
        {
            QTreeWidgetItem* item_1 = new QTreeWidgetItem(itemREG);//item1->child(0);
            item_1->setText(0, reg.at(k).name);
            QColor color = QColor::fromHsv(20, 255, 235,255);
            item_1->setTextColor(0,color);


            // m_checkedbool.append(false);
            if(k==0)
            {
                m_checkeregdbool.append(true);
                item_1->setCheckState(0,Qt::Checked);
            }
            else
            {

                m_checkeregdbool.append(false);
                item_1->setCheckState(0,Qt::Unchecked);

            }
            item_1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsTristate| Qt::ItemIsUserCheckable| Qt::ItemIsEnabled );
        }



    }
    loadscene();


}

void Formscene::setPPI(QVector<ParamGrBaseInter> eathVehiclePPI)
{

    m_eathVehiclePPI=eathVehiclePPI;

    itemPPI = new QTreeWidgetItem(treeWidget);
    itemPPI->setText(0, QObject::trUtf8("ППИ"));
    itemPPI->setText(1, QObject::trUtf8("2"));
    if(itemPPI->childCount()>0)
    {
        // //qDebug()<<"pos treew="<<itemPPI->childCount();
        for(int k=0;k<itemPPI->childCount();k++)
        {
            //itemKA->takeChild(k);
            itemPPI->takeChild(itemPPI->indexOfChild(itemPPI->child(k)));
        }
    }



    if(eathVehiclePPI.size()>0)
    {

        m_checkePPIdbool.clear();
        //
        for(int k=0;k<eathVehiclePPI.size();k++)
        {
            QTreeWidgetItem* item_1 = new QTreeWidgetItem(itemPPI);//item1->child(0);
            item_1->setText(0, eathVehiclePPI.at(k).point.name);
            QColor color =QColor::fromRgb(24, 252, 30,255);
            item_1->setTextColor(0,color);


            // m_checkedbool.append(false);
            if(k==0)
            {
                m_checkePPIdbool.append(true);
                item_1->setCheckState(0,Qt::Checked);
            }
            else
            {

                m_checkePPIdbool.append(false);
                item_1->setCheckState(0,Qt::Unchecked);

            }
            item_1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsTristate| Qt::ItemIsUserCheckable| Qt::ItemIsEnabled );
        }



    }
    loadscene();


}

void Formscene::setPPU( QVector<ParamGrBaseInter> eathVehiclePPU)
{

    m_eathVehiclePPU=eathVehiclePPU;
    itemPPU = new QTreeWidgetItem(treeWidget);
    itemPPU->setText(0, QObject::trUtf8("ПУ"));
    itemPPU->setText(1, QObject::trUtf8("3"));
    if(itemPPU->childCount()>0)
    {
        //qDebug()<<"pos treew="<<itemPPU->childCount();
        for(int k=0;k<itemPPU->childCount();k++)
        {
            //itemKA->takeChild(k);
            itemPPU->takeChild(itemPPU->indexOfChild(itemPPU->child(k)));
        }
    }



    if(eathVehiclePPU.size()>0)
    {

        m_checkePPUdbool.clear();
        //
        for(int k=0;k<eathVehiclePPU.size();k++)
        {
            QTreeWidgetItem* item_1 = new QTreeWidgetItem(itemPPU);//item1->child(0);
            item_1->setText(0, eathVehiclePPU.at(k).point.name);
            QColor color = QColor::fromRgb(124, 92, 230, 255);
            item_1->setTextColor(0,color);


            // m_checkedbool.append(false);
            if(k==0)
            {
                m_checkePPUdbool.append(true);
                item_1->setCheckState(0,Qt::Checked);
            }
            else
            {

                m_checkePPUdbool.append(false);
                item_1->setCheckState(0,Qt::Unchecked);

            }
            item_1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsTristate| Qt::ItemIsUserCheckable| Qt::ItemIsEnabled );
        }



    }
    loadscene();


}

void Formscene::visibilObj()
{
    int treew=-1;
    if(treeWidget->currentIndex().isValid()==false) return;
    QTreeWidgetItem *parent0 = treeWidget->currentItem()->parent();
    if (parent0)
    {

        treew=parent0->data(1, 0).toInt();

    }

    if(treew==0)
    {
        QTreeWidgetItem *parent = itemKA->treeWidget()->currentItem();
        if(parent)
        {
            // if(parent->text(0)==QObject::trUtf8("КА"))

            int ij=itemKA->treeWidget()->currentIndex().row();
            //int ij=treeWidget->indexOfTopLevelItem(itemKA->treeWidget()->currentIndex());
            //qDebug()<<"ien checked=="<<ij<<itemKA->treeWidget()->currentIndex();
            if(ij>-1)
            {

                if(m_checkedbool.size()==0) return;
                if(parent->checkState(0)){

                    m_checkedbool[ij]=true;
                }

                else {

                    m_checkedbool[ij]=false;
                }
            }
        }
    }
    if(treew==1)
    {
        QTreeWidgetItem *parent = itemREG->treeWidget()->currentItem();

        // if(parent->text(0)==QObject::trUtf8("КА"))
        if(parent)
        {
            // if(parent->text(0)==QObject::trUtf8("КА"))

            int ij=itemREG->treeWidget()->currentIndex().row();
            //int ij=treeWidget->indexOfTopLevelItem(itemKA->treeWidget()->currentIndex());
            //qDebug()<<"ien checked=="<<ij<<itemKA->treeWidget()->currentIndex();
            if(ij>-1)
            {

                if(m_checkeregdbool.size()==0) return;
                if(parent->checkState(0))

                    m_checkeregdbool[ij]=true;

                else m_checkeregdbool[ij]=false;
            }
        }
    }
    if(treew==2)
    {
        QTreeWidgetItem *parent = itemPPI->treeWidget()->currentItem();

        if(parent)
        {
            int ij=itemPPI->treeWidget()->currentIndex().row();

            if(ij>-1)
            {

                if(m_checkePPIdbool.size()==0) return;
                if(parent->checkState(0))

                    m_checkePPIdbool[ij]=true;

                else m_checkePPIdbool[ij]=false;
            }
        }
    }
    if(treew==3)
    {
        QTreeWidgetItem *parent = itemPPU->treeWidget()->currentItem();

        if(parent)
        {
            int ij=itemPPU->treeWidget()->currentIndex().row();

            if(ij>-1)
            {

                if(m_checkePPUdbool.size()==0) return;
                if(parent->checkState(0))

                    m_checkePPUdbool[ij]=true;

                else m_checkePPUdbool[ij]=false;
            }
        }
    }
    scene->clear();
    calcposKA();
    loadscene();
    graphicsView->update();

}

void Formscene::wheelEvent(QWheelEvent* pe)
{

  scaleView(pow((double)2, -pe->delta() / 240.0));



}
void Formscene::mousePressEvent(QMouseEvent* pe)
{

    if (pe->button() == Qt::LeftButton)
    {
        ptrMousePosition = pe->pos();
        float lat=90-(pe->pos().y()/DEG2PXVT);
        float lon=-180+pe->pos().x()/DEG2PXHZ;
        label->setText(QString("B=%1, L=%2").arg(lat).arg(lon));
        // scene->selectionChanged();
        //QList<QGraphicsItem*> itsel=scene->selectedItems();
        ////qDebug()<<"pos=="<<pe->pos().x()<<"y="<<pe->pos().y()<<"sel="<<itsel.size();
        // graphicsView->centerOn (ptrMousePosition);

    }
}
void Formscene::resizeEvent(QResizeEvent *event)
{
    const int hcarte = graphicsView->height();
    const int lcarte = graphicsView->width() ;

    DEG2PXHZ = lcarte / T360;
    DEG2PXVT = hcarte * 2. / T360;
    loadscene();
}

void Formscene::scaleView(qreal scaleFactor)
{
    qreal factor = graphicsView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    graphicsView->scale(scaleFactor, scaleFactor);




}

void Formscene::loadscene()
{

    //qDebug()<<"all ll="<< scene->AllLayers;
    scene->clear();
    //  graphicsView->clearMask();

    scene->addPixmap(m_carte.scaled(graphicsView->size()));
    scene->setSceneRect(graphicsView->rect());

    //composedOffscreenImage.copy()
    const int hcarte = graphicsView->height() ;
    const int lcarte = graphicsView->width();
    const int hcarte2 = qRound(hcarte * 0.5);
    const int lcarte2 = qRound(lcarte * 0.5);

    DEG2PXHZ = lcarte / T360;
    DEG2PXVT = hcarte * 2. / T360;
    // //qDebug()<<"hcarte="<<hcarte<<lcarte<<graphicsView->frameSize().height()<<graphicsView->frameSize().width();



    // Affichage de la grille de coordonnees
    // if (ui->affgrille->isChecked())


    scene->addLine(0, hcarte2, lcarte, hcarte2, QPen(Qt::white));
    scene->addLine(lcarte2, 0, lcarte2, hcarte, QPen(Qt::white));

    QPen style(Qt::lightGray);
    const int tablat[] = { hcarte / 6, hcarte / 3, (int) (hcarte / 1.5), (int) (hcarte / 1.2) };
    const int tablon[] = { lcarte / 12, lcarte / 6, (int) (lcarte * 0.25), lcarte / 3, (int) (lcarte / 2.4),
                           (int) (7. * lcarte / 12.), (int) (lcarte / 1.5), (int) (lcarte * 0.75), (int) (lcarte / 1.2),
                           (int) (11. * lcarte / 12.) };

    for(int j=0; j<4; j++)
        scene->addLine(0, tablat[j], lcarte, tablat[j], style);

    for(int j=0; j<10; j++)
        scene->addLine(tablon[j], 0, tablon[j], hcarte, style);

    // Tropiques
    style.setStyle(Qt::DashLine);
    scene->addLine(0, 66.55 * DEG2PXVT, lcarte, 66.55 * DEG2PXVT, style);
    scene->addLine(0, 113.45 * DEG2PXVT, lcarte, 113.45 * DEG2PXVT, style);
    //zonnn

    if(m_currentKAZon.size()>0)
    {

        if(m_currentKA.size()>0)
        {
            for (int j=0;j<m_currentKAZon.size();++j)
            {
                QVector<QPointF> zoneF=m_currentKAZon[j];
                // //qDebug()<<"zoneF=="<<zoneF.size();

                facilitypoint poska=   m_currentKA.at(j);
                //graphicsView->sepoaddText(poska.name)

                // QGraphicsItem *item;// = scene->itemAt(poska.lon*DEG2PXHZ, poska.lat*DEG2PXVT);
                // item->setPos(poska.lon*DEG2PXHZ, poska.lat*DEG2PXVT);
                //  QGraphicsSimpleTextItem tite(poska.name);
                //  tite.setPos(poska.lon*DEG2PXHZ, poska.lat*DEG2PXVT);
                //scene->addSimpleText(poska.name);

                //  scene->addItem(&tite);

                QGraphicsSimpleTextItem *txtCst = new QGraphicsSimpleTextItem(poska.name);
                txtCst->setVisible(true);
                txtCst->setActive(true);
                QPen crayon1(Qt::yellow);
                crayon1.setWidth(1);
                // crayon1.setColor(QColor::fromHsv(j * (359/m_currentKA.size()), 255, 255));
                crayon1.setColor(Qt::black);
                txtCst->setPen(crayon1);

                double lonK=poska.lon;
                if(lonK<-180) lonK+=360;
                if(lonK<-180) lonK+=360;
                lonK*=DEG2PXHZ;
                lonK+=lcarte2;
                if(lonK>lcarte) lonK-=lcarte;
                txtCst->setBrush(Qt::NoBrush);
                txtCst->setPos(QPointF((lonK), (90-poska.lat)*DEG2PXVT));
                txtCst->setFont(QFont("Times", 10));
                scene->addItem(txtCst);

                QGraphicsPixmapItem *satp= new QGraphicsPixmapItem(QPixmap(":/icons/satellite.png").scaled(20,20));
                satp->setPos(QPointF((lonK)-10, (90-poska.lat)*DEG2PXVT-10));
                scene->addItem(satp);
                if(m_checkedbool.size()>j)
                {
                    if(m_checkedbool.at(j))
                    {
                        for (int i=1;i<zoneF.size();++i)
                        {
                            QPen crayon(Qt::yellow);
                            crayon.setWidth(2);
                            double lon=zoneF.at(i).x();
                            double lon1=zoneF.at(i-1).x();
                            if(lon<-180) lon+=360;
                            if(lon1<-180) lon1+=360;
                            if(lon>180) lon-=360;
                            if(lon1>180) lon1-=360;

                            lon*=DEG2PXHZ;
                            lon1*=DEG2PXHZ;
                            lon+=lcarte2;
                            lon1+=lcarte2;




                            if(lon>lcarte) lon-=lcarte;

                            if(lon1>lcarte) lon1-=lcarte;
                            int lsat1 = qRound(lon );
                            //int bsat1 = qRound(zoneF.at(i-1).y()  + 1);
                            int lsat2 = qRound(lon1);

                            //int lsat1 = qRound(zoneF.at(i-1).x() * DEG2PXHZ);
                            int bsat1 = qRound(zoneF.at(i-1).y() * DEG2PXVT + 1);
                            //int lsat2 = qRound(zoneF.at(i).x() * DEG2PXHZ);
                            int bsat2 = qRound(zoneF.at(i).y() * DEG2PXVT + 1) ;


                            int ils = 99999;

                            if (fabs(lsat2 - lsat1) > lcarte2) {
                                if (lsat2 < lsat1)
                                    lsat2 += lcarte;
                                else
                                    lsat1 += lcarte;
                                ils = i;

                            }


                            scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                            if (ils == i) {
                                lsat1 -= lcarte;
                                lsat2 -= lcarte;
                                scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                                ils = 0;
                            }



                            scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                        }
                        //temp

                        //            if(j<5)
                        //            {
                        //                QVector<QPointF> zoneF2=m_currentKAZon2.at(j);
                        //             // m_currentKAZon2.append(zoneF2);
                        //                for (int i=1;i<zoneF2.size();++i)
                        //                {
                        //                       QPen crayon(Qt::yellow);
                        //                       crayon.setWidth(2);
                        //                       double lon=zoneF2.at(i).x();
                        //                       double lon1=zoneF2.at(i-1).x();
                        //                       if(lon<-180) lon+=360;
                        //                       if(lon1<-180) lon1+=360;
                        //                       if(lon>180) lon-=360;
                        //                       if(lon1>180) lon1-=360;

                        //                       lon*=DEG2PXHZ;
                        //                        lon1*=DEG2PXHZ;
                        //                       lon+=lcarte2;
                        //                        lon1+=lcarte2;




                        //                       if(lon>lcarte) lon-=lcarte;

                        //                         if(lon1>lcarte) lon1-=lcarte;
                        //                         int lsat1 = qRound(lon );
                        //                         //int bsat1 = qRound(zoneF.at(i-1).y()  + 1);
                        //                         int lsat2 = qRound(lon1);

                        //                           //int lsat1 = qRound(zoneF.at(i-1).x() * DEG2PXHZ);
                        //                           int bsat1 = qRound(zoneF2.at(i-1).y() * DEG2PXVT + 1);
                        //                          //int lsat2 = qRound(zoneF.at(i).x() * DEG2PXHZ);
                        //                          int bsat2 = qRound(zoneF2.at(i).y() * DEG2PXVT + 1) ;


                        //                           int ils = 99999;

                        //                            if (fabs(lsat2 - lsat1) > lcarte2) {
                        //                                if (lsat2 < lsat1)
                        //                                    lsat2 += lcarte;
                        //                                else
                        //                                    lsat1 += lcarte;
                        //                                ils = i;

                        //                            }


                        //                            scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                        //                            if (ils == i) {
                        //                                lsat1 -= lcarte;
                        //                                lsat2 -= lcarte;
                        //                               scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                        //                                ils = 0;
                        //                            }



                        //                             scene->addLine(lsat1, bsat1, lsat2, bsat2, crayon);

                        //                        }
                        //}
                    }
                }
            }
        }
    }
    if((m_trassa.size()>0)&&(m_currentKA.size()>0))
    {

        QPen pen;

        //  scene->clear();
        //loadscene();

        int isiz=0;


        for(int k=0;k<m_currentKA.size();k++)
        {

            //facilitypoint kat= m_trassa[k];
            QVector<QPointF> ztr;

            if(m_checkedbool.size()>k)
            {
                if(m_checkedbool.at(k))
                {
                    pen.setColor(QColor::fromHsv(k * (359/m_currentKA.size()), 255, 255));
                    pen.setWidth(1);
                    pen.setCosmetic(true);
                    QMap<int,facilitypoint>::Iterator tr=m_trassa.find(k);
                    while (tr != m_trassa.end() && tr.key() == k) {

                        facilitypoint postr=tr.value();

                        //double lont=180+postr.lon;
                        double lont=(postr.lon*DEG2PXHZ)+lcarte2;
                        if(lont>lcarte) lont-=lcarte;

                        // if(lont>360) lont-=360;
                        ztr.append(QPointF((lont), (90-postr.lat)*DEG2PXVT));
                        // scene->addEllipse((180-postr.lon)*DEG2PXHZ, (90-postr.lat)*DEG2PXVT,2,2,pen,Qt::NoBrush);
                        //painter.drawText((180-m_currentKA.at(i).lon)*DEG2PXHZ+6, (90-m_currentKA.at(i).lat)*DEG2PXVT+8, m_currentKA.at(i).name);
                        // painter.drawPixmap(m_currentKA.at(i).x(),m_currentKA.at(i).y(),pm);
                        //QPolygonF polka1=map_zonKA[i];
                        //      //qDebug()<<"pos=ka ="<<m_currentKA.at(k).lon<<m_currentKA.at(k).lat<<m_currentKA.at(k).name<<m_currentKA.size();
                        ++tr;

                        isiz+=1;
                    }
                }
            }

            if(ztr.size()>0)
            {
                // //qDebug()<<"pos=m_currentKAZon.size() ="<<m_currentKAZon.size();
                for(int i=1;i<ztr.size();i++)
                {

                    int lsat1 = qRound(ztr.at(i-1).x()+1 );
                    int bsat1 = qRound(ztr.at(i-1).y()  + 1);
                    int lsat2 = qRound(ztr.at(i).x()+1);
                    int bsat2 = qRound(ztr.at(i).y() + 1) ;

                    int ils = 99999;

                    if (fabs(lsat2 - lsat1) > lcarte2) {
                        if (lsat2 < lsat1)
                            lsat2 += lcarte;
                        else
                            lsat1 += lcarte;
                        ils = i;

                    }

                    scene->addLine(lsat1, bsat1, lsat2, bsat2, pen);

                    if (ils == i) {
                        lsat1 -= lcarte;
                        lsat2 -= lcarte;
                        scene->addLine(lsat1, bsat1, lsat2, bsat2, pen);

                        ils = 0;
                    }

                    scene->addLine(lsat1, bsat1, lsat2, bsat2, pen);


                }
            }
        }
    }
    // test

    if((m_checkeregdbool.size()>0)&&(m_reg.size()>0))
    {
        for(int k=0;k<m_reg.size();k++)
        {
            if(m_checkeregdbool.at(k))
            {
                double maxlat=90-m_reg.at(k).maxlat;
                double maxlong=m_reg.at(k).maxlong;
                double minlat=90-m_reg.at(k).minlat;
                double minlong=m_reg.at(k).minlong;
                // double name="Район";
                QPen penreg;
                // penreg.setColor(QColor::fromHsv(20, 255, 235,125));
                //penreg.setWidth(3);
                //  penreg.setColor(Qt::red);
                penreg.setColor(Qt::black);
                penreg.setWidth(3);
                penreg.setCosmetic(true);

                if(maxlong<-180) maxlong+=360;
                if(minlong<-180) minlong+=360;
                if(maxlong>180) maxlong-=360;
                if(minlong>180) minlong-=360;

                maxlong*=DEG2PXHZ;
                minlong*=DEG2PXHZ;
                maxlong+=lcarte2;
                minlong+=lcarte2;
                if(maxlong>lcarte) maxlong-=lcarte;
                if(minlong>lcarte) minlong-=lcarte;
                int lsat1 = qRound(minlong );
                int bsat1 = qRound(minlat * DEG2PXVT );
                int lsat2 = qRound(maxlong );
                int bsat2 = qRound(minlat * DEG2PXVT ) ;
                int lsat3 = qRound(minlong );
                int bsat3 = qRound(maxlat * DEG2PXVT );
                int lsat4 = qRound(maxlong );
                int bsat4 = qRound(maxlat * DEG2PXVT ) ;
                scene->addLine(lsat1, bsat1, lsat2, bsat2, penreg);
                scene->addLine(lsat2, bsat2, lsat2, bsat3, penreg);
                scene->addLine(lsat2, bsat3, lsat1, bsat3, penreg);
                scene->addLine(lsat1, bsat3, lsat1, bsat1, penreg);
            }
        }
    }
    // ppi

    if((m_checkePPIdbool.size()>0)&&(m_eathVehiclePPI.size()))
    {
        for(int k=0;k<m_eathVehiclePPI.size();k++)
        {
            if(m_checkePPIdbool.at(k))
            {
                double lonn=m_eathVehiclePPI.at(k).point.lon;
                double lonn0=m_eathVehiclePPI.at(k).point.lon;

                lonn*=DEG2PXHZ;

                lonn+=lcarte2;

                if(lonn>lcarte) lonn-=lcarte;
                if(lonn0>180) lonn0-=360;
                ////qDebug()<<"lon="<<lonn<<lonn0<<"ll="<<m_eathVehiclePPI.at(k).point.lon;

                QVector<QPointF> zoneF=  CalculZoneVisibilitef(m_eathVehiclePPI.at(k).point.lat*M_PI/180.,lonn0*M_PI/180.,1500.,-1. );

                double beta = acos((6371.0 - 5.) / (6371.0+1500.))-5.0*DEG2RAD;
                double betadn =(beta*RAD2DEG+65.0)* DEG2PXVT;


                QGraphicsSimpleTextItem *txtCst = new QGraphicsSimpleTextItem(m_eathVehiclePPI.at(k).point.name);
                txtCst->setVisible(true);
                txtCst->setActive(true);
                QPen crayon1(Qt::yellow);
                crayon1.setWidth(1);
                crayon1.setColor(QColor::fromRgb(24, 252, 30, 86));
                txtCst->setPen(crayon1);

                txtCst->setBrush(Qt::NoBrush);
                txtCst->setPos(QPointF((lonn), (90-m_eathVehiclePPI.at(k).point.lat)*DEG2PXVT));
                txtCst->setFont(QFont("Times", 8));
                scene->addItem(txtCst);

                // //qDebug()<<"setZONEEEE"<<zoneF.size();
                const QBrush alpha = QBrush(QColor::fromRgb(24, 252, 30, 86));


                ClipperLib::Clipper cloff;
                // ClipperLib::Paths subject;

                // subject.resize(kp);
                // ClipperLib::Paths clip;
                ClipperLib::Path subj;
                ClipperLib::Path subj2;
                ClipperLib::Paths solution;
                for(int i=0;i<zoneF.size();i++)
                {
                    double lon0=zoneF.at(i).x();
                    if(lon0>180) lon0-=360;


                    lon0*= DEG2PXHZ;

                    lon0+=lcarte2;
                    int lsat1 = qRound(lon0 );
                    int bsat1 = qRound(zoneF.at(i).y() * DEG2PXVT + 1);
                    if(fabs(lonn-lon0)>lcarte2) subj2.push_back(ClipperLib::IntPoint((ClipperLib::cInt)(lsat1),(ClipperLib::cInt)(bsat1)));
                    if(fabs(lonn-lon0)<lcarte2) subj.push_back(ClipperLib::IntPoint((ClipperLib::cInt)(lsat1),(ClipperLib::cInt)(bsat1)));

                }
                // subject.push_back(subj);
                if(subj2.size()>0) cloff.AddPath(subj2,ClipperLib::ptSubject,true);
                cloff.AddPath(subj,ClipperLib::ptSubject,true);

                subj.clear();
                subj2.clear();
                // cloff.Execute(ClipperLib::ctUnion,solution,ClipperLib::pftNonZero,ClipperLib::pftNonZero);
                cloff.Execute(ClipperLib::ctUnion,solution,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
                // cloff.Execute(solution,0);
                cloff.Clear();
                // //qDebug()<<"solution.size("<<solution.size();
                if(solution.size()>0)
                {

                    for (int i = 0; i < solution.size(); ++i)
                    {

                        if(solution[i].size()>0)
                        {
                            QPolygonF zon_f;
                            for (int j = 0; j < solution[i].size(); ++j)
                            {

                                QPointF ppoint(solution[i][j].X,solution[i][j].Y);
                                zon_f.append(ppoint);

                            }

                            if(zon_f.size()>0) scene->addPolygon(zon_f, QPen(Qt::NoBrush, 0), alpha);

                        }
                    }


                }


            }
        }
    }// end ppi

    //PPU
    if((m_checkePPUdbool.size()>0)&&(m_eathVehiclePPU.size()>0))
    {
        for(int k=0;k<m_eathVehiclePPU.size();k++)
        {
            if(m_checkePPUdbool.at(k))
            {
                double lonn=m_eathVehiclePPU.at(k).point.lon;
                double lonn0=m_eathVehiclePPU.at(k).point.lon;

                lonn*=DEG2PXHZ;

                lonn+=lcarte2;

                if(lonn>lcarte) lonn-=lcarte;
                if(lonn0>180) lonn0-=360;


                QVector<QPointF> zoneF=  CalculZoneVisibilitef(m_eathVehiclePPU.at(k).point.lat*M_PI/180.,lonn0*M_PI/180.,1500.,-1. );

                double beta = acos((6371.0 - 5.) / (6371.0+1500.))-5.0*DEG2RAD;
                double betadn =(beta*RAD2DEG+65.0)* DEG2PXVT;


                QGraphicsSimpleTextItem *txtCst = new QGraphicsSimpleTextItem(m_eathVehiclePPU.at(k).point.name);
                txtCst->setVisible(true);
                txtCst->setActive(true);
                QPen crayon1(Qt::yellow);
                crayon1.setWidth(1);
                crayon1.setColor(QColor::fromHsv(112, 155, 255));
                txtCst->setPen(crayon1);

                txtCst->setBrush(Qt::NoBrush);
                txtCst->setPos(QPointF((lonn), (90-m_eathVehiclePPU.at(k).point.lat)*DEG2PXVT));
                txtCst->setFont(QFont("Times", 8));
                scene->addItem(txtCst);


                ClipperLib::Clipper cloff;
                // ClipperLib::Paths subject;

                // subject.resize(kp);
                // ClipperLib::Paths clip;
                ClipperLib::Path subj;
                ClipperLib::Path subj2;
                ClipperLib::Paths solution;
                for(int i=0;i<zoneF.size();i++)
                {
                    double lon0=zoneF.at(i).x();
                    if(lon0>180) lon0-=360;


                    lon0*= DEG2PXHZ;

                    lon0+=lcarte2;
                    int lsat1 = qRound(lon0 );
                    int bsat1 = qRound(zoneF.at(i).y() * DEG2PXVT + 1);
                    if(fabs(lonn-lon0)>lcarte2) subj2.push_back(ClipperLib::IntPoint((ClipperLib::cInt)(lsat1),(ClipperLib::cInt)(bsat1)));
                    if(fabs(lonn-lon0)<lcarte2) subj.push_back(ClipperLib::IntPoint((ClipperLib::cInt)(lsat1),(ClipperLib::cInt)(bsat1)));

                }
                // subject.push_back(subj);
                if(subj2.size()>0) cloff.AddPath(subj2,ClipperLib::ptSubject,true);
                cloff.AddPath(subj,ClipperLib::ptSubject,true);

                subj.clear();
                subj2.clear();
                // cloff.Execute(ClipperLib::ctUnion,solution,ClipperLib::pftNonZero,ClipperLib::pftNonZero);
                cloff.Execute(ClipperLib::ctUnion,solution,ClipperLib::pftEvenOdd,ClipperLib::pftEvenOdd);
                // cloff.Execute(solution,0);
                cloff.Clear();
                ////qDebug()<<"solution.size("<<solution.size();
                if(solution.size()>0)
                {

                    for (int i = 0; i < solution.size(); ++i)
                    {

                        if(solution[i].size()>0)
                        {
                            QPolygonF zon_f;
                            for (int j = 0; j < solution[i].size(); ++j)
                            {

                                QPointF ppoint(solution[i][j].X,solution[i][j].Y);
                                zon_f.append(ppoint);

                            }
                            const QBrush alpha = QBrush(QColor::fromRgb(124, 92, 230, 86));
                            if(zon_f.size()>0) scene->addPolygon(zon_f, QPen(Qt::NoBrush, 0), alpha);

                        }
                    }


                }


            }

        }
    }


    scene->setSceneRect(graphicsView->rect());
    graphicsView->setScene(scene);

}
