#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMapControl/QMapControl.h>
#include <QFuture>
#include <QFutureWatcher>
#include <QThreadPool>
#include <QtConcurrentRun>
#include "progressbar.h"
#include "ui_mainwindow.h"
#include "paint3d.h"
#include "calc_bpla_plan.h"
#include <QMapControl/LayerMapAdapter.h>
#include <QMapControl/MapAdapterOSM.h>
#include <QMapControl/MapAdapterOTM.h>
#include <QMapControl/MapAdapterGoogle.h>
#include <QMapControl/MapAdapterBing.h>
#include <QMapControl/GeometryLineString.h>
#include <QMapControl/GeometryPointCircle.h>
#include <QMapControl/GeometryPointImage.h>
#include <QMapControl/GeometryPolygon.h>
#include <QMapControl/Geometry.h>
#include <QMapControl/LayerGeometry.h>
#include <QMapControl/GeometryWidget.h>
#include <QMapControl/Layer.h>
#include <QMapControl/LayerMapAdapter.h>
#include <QMapControl/GeometryPoint.h>
#include <QMapControl/GeometryPointImage.h>
#include <QMapControl/GeometryPointImageScaled.h>
#include <QMapControl/Point.h>
#include <QThread>

using namespace qmapcontrol;

class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QDateTime m_curtime;
    QDateTime m_begintime;
    QDateTime m_endtime;
    int m_timerID;
    int time_step;
    int timeType;
    int countBpLA = 0;
    int countPoint = -1;
    QMap<int,facilitypoint> m_trassa;
    QList<facilitypoint> m_KA ;
    CPaint3D paint3d;
    CPaint3D paint3d_2;
    CProgressBar m_prgrun;
    Calc_bpla_plan planBpLA; //сводная таблица видимости КА для беспилотников
    QThread m_head;
    QMapControl*  m_map_control;
    std::vector<PointWorldCoord> view_points;
    std::shared_ptr<LayerGeometry> region_layer;
    void initMap();
    bool setDateTime(QDateTime begintime, QDateTime endtime);
    bool flag = true;
    
    bool flag_Polygon = false;
    bool flag_create_Point = false;

    virtual void timerEvent(QTimerEvent *t);
    void contextMenuEvent(QContextMenuEvent *event);

    void createActions();
    QAction *Create_Point;
    QAction *Create_Polygon;
    QAction *Load_Polygon;

    QVector<ASDOrbitalObjectPar> m_VecOrbobj;
    QVector<ASD_bpla_struct> m_VecBpLA;
    std::shared_ptr<LayerGeometry> region_layer_Orb;
    std::vector<PointWorldCoord> raw_points;
    
    std::shared_ptr<GeometryPolygon> polygon;

    PointWorldCoord current_Point_world;
    std::vector<PointWorldCoord> points_Polygon;


    QString FileName;


signals:
    //! \brief Сигнал обновления текущего времени.
    void currentTimeUpdated();



private slots:
    void slotStart();
    void slotPause();
    void slotStop();
    void updatecurTime();
    void setInterval();
    void onStepChanged();
    void onTimeTypeChanged();

    void setTimeEdit();
    void calc();
    void calcBPLA();
    void calcraspprog(int pp);
    void main_mouseEventPressCoordinate(QMouseEvent* mouse_event, PointWorldCoord press_coordinate);

public slots:
    void resizeEvent(QResizeEvent* resize_event);
    void new_Point();
    void new_Polygon();
    void load_Polygon();
    void drawPolygon();

};

#endif // MAINWINDOW_H
