#ifndef OSGVIEWERQT_H
#define OSGVIEWERQT_H

#include <QTimer>
#include <QBoxLayout>
#include <QStatusBar>
#include <QDateTime>

#include <osg/ShapeDrawable>
#include <osg/TexGenNode>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/AutoTransform>
#include <osg/BoundingSphere>
#include <osg/Plane>
#include <osg/CullFace>
#include <osg/ShadowVolumeOccluder>
#include <osgEarthAnnotation/GeoPositionNodeAutoScaler>
#include <osgEarthAnnotation/RectangleNode>
#include <osg/PolygonMode>
#include <osg/Point>
#include <osg/LineWidth>

#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>
#include <osgGA/CameraViewSwitchManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/SphericalManipulator>


#include <osgEarthUtil/MouseCoordsTool>
#include <osgEarthUtil/VerticalScale>
#include <osgEarth/TerrainEngineNode>

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgDB/Options>

#include <osgSim/SphereSegment>
#include <osgQt/GraphicsWindowQt>
#include <osgManipulator/Command>
#include <osgUtil/LineSegmentIntersector>

#include <osgEarth/Map>
#include <osgEarth/TerrainEngineNode>
#include <osgEarth/MapNode>
#include <osgEarth/Notify>
#include <osgEarth/Cache>
#include <osgEarth/StringUtils>
#include <osgEarth/VerticalDatum>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/ImageOverlayEditor>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/ModelNode>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/LatLongFormatter>
#include <osgEarthUtil/MouseCoordsTool>
#include <osgEarthUtil/MGRSFormatter>
#include <osgEarthUtil/GeodeticGraticule>
#include <osgEarthUtil/MGRSGraticule>
#include <osgEarthUtil/UTMGraticule>

#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthDrivers/cache_filesystem/FileSystemCache>

#include <ASD/asdcoordconvertor.h>
#include <gui3D/EarthManip.h>

using namespace osgEarth;
using namespace osgEarth::Drivers;
using namespace osgEarth::Util;
using namespace osgEarth::Util::Controls;
using namespace osgEarth::Annotation;


class PickHandler : public osgGA::GUIEventHandler
{
public:
    PickHandler(){}
    osg::Node *getOrCreateSelectionBox();
    virtual bool handle( const osgGA::GUIEventAdapter& ea,
                         osgGA::GUIActionAdapter& aa );
protected:
    osg::ref_ptr<osg::MatrixTransform> _selectionBox;
};

struct PrintCoordsToStatusBar : public MouseCoordsTool::Callback
{
public:
    void addTime(QDateTime * time) { current_time = time;}
    PrintCoordsToStatusBar(QStatusBar* sb) : _sb(sb) { }
    void set(const GeoPoint& p, osg::View* view, MapNode* mapNode)
    {
        double S = ASDCoordConvertor::compSiderealTime(*current_time);
        double p_x;
        p_x = p.x()+(360-S*RAD_TO_DEG);
        if(p_x > 180)
            p_x = p_x-360;
        std::string str = osgEarth::Stringify() << p.y() << ", " << p.x();
        _sb->clearMessage();
        _sb->showMessage( QString(str.c_str()) );
    }
    void reset(osg::View* view, MapNode* mapNode)
    {

        _sb->clearMessage();
        _sb->showMessage( QString::fromUtf8("Нет проекции на Землю") );
    }
    QStatusBar* _sb;
    QDateTime * current_time;
};

class CoordHandler : public MouseCoordsTool
{
public:


    CoordHandler(MapNode* mapNode, LabelControl* label =0L, Formatter* formatter =0L):MouseCoordsTool( mapNode, label,formatter )
    {

    }
    virtual bool handle( const osgGA::GUIEventAdapter& ea,
                         osgGA::GUIActionAdapter& aa );
};

class nodePick3D :public osgGA::GUIEventHandler
{
public:

    nodePick3D(osg::ref_ptr<osg::Group> nodeParent)
    {
        m_nodeParent=nodeParent;
    }
//    void setObjAll( QVector<ParamGrBase> station, QVector<ASDOrbitalObjectPar> ka, QVector <ASDZoneVisiblePoint> mapObzRegionKA, QDateTime curtime);

    osg::ref_ptr<osg::Group> m_nodeParent;
    QVector<ParamGrBaseInter> m_station;
    QVector<ASDOrbitalObjectPar> m_ka;
//    QVector <ASDZoneVisiblePoint> m_mapObzRegionKA;
    QDateTime m_curtime;
    virtual bool handle(const osgGA::GUIEventAdapter& ea,
                        osgGA::GUIActionAdapter& aa);

};

class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
    ViewerWidget(QWidget* parent = 0, Qt::WindowFlags f = 0, osgViewer::ViewerBase::ThreadingModel threadingModel= osgViewer::ViewerBase::SingleThreaded);
    ~ViewerWidget();
    QWidget* addViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene );
    osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );

    /*!
     * \brief Создание Земли
     * \param node_perant - узловой предок
     * \return возращает адрес предка с добавленным потомкам ввиде Земли
     */
    void createEarth(osg::ref_ptr<osg::Group> node_perant, QString file);
    osg::ref_ptr<osgEarth::MapNode> getMapEarth();
    void coordMouse();

    osg::ref_ptr<osg::Group> addPoint(osg::ref_ptr<osg::Group> node_perant,QVector<double> coord, QString image_name);

    void addPointAGSK(QVector<double> coord, QString image);
    void addPointAGSK(QVector<QVector<double> > coord, QVector<QColor> color);

    void addPointGSK(QVector<double> coord, QString image);

    //Добавление главного источника освещения
    void addLight();
    void moveEarth(QDateTime);

    void clearScene(osg::ref_ptr<osg::Group> node_perant);

    void clearGlobe(osg::ref_ptr<osg::Group> node_perantGSK);
    void createGlobe(osg::ref_ptr<osg::Group> node_perantGSK, QString file);

    void createSky(osg::ref_ptr<osg::Group> node_perant, QDateTime time);
    void clearSky(osg::ref_ptr<osg::Group> node_perant) ;
    void createSun();
    void clearSun();
    void createMoon();
    void clearMoon();
    void createStars();
    void clearStars();
    void createAtmosphere();
    void clearAtmosphere();

    osg::ref_ptr<osg::Group> addEarthPicture(double lat, double lon, QString icon);

    /*!
     * \brief Зона в виде конуса
     * \param coord - координаты КА
     * \param pitch - тангаж (в плоскости КА)
     * \param rall - рыскание ( в плоскости перпенндикулярной КА)
     * \param gamma - угол полураствора
     */
    void addAxesOSGT(osg::ref_ptr<osg::Group> node_perant);

    static void addAxisXYZ(osg::ref_ptr<osg::Group> node_perant);

    void addConus(QVector<double> coord, QVector<double> coordEnd,  double h, double gamma, QColor color);

    void addSphereSegment(double latitude, double longitude, double radius, double minAzim, double maxAzim, double minElev, double maxElev, QColor color);

    osg::ref_ptr<osg::MatrixTransform> addObject(QString name_3dx);

    osg::ref_ptr<osg::MatrixTransform> addObjectIcon(QString name_image);
    osg::ref_ptr<osg::MatrixTransform> addObjectIconPoint(QString name_image);
    osg::ref_ptr<osg::MatrixTransform> addObjectPyramid(double roll, double deltaV, double deltaH, double dist);
    virtual void paintEvent( QPaintEvent* event )
    { frame(); }
    osg::ref_ptr<osg::Group> m_root_agsk;
    osg::ref_ptr<osg::Group> m_root_gsk;
    osg::ref_ptr<SkyNode> sky_node;
    osg::ref_ptr<osg::Node> globe;
    osg::ref_ptr<osg::AutoTransform> atAxes;

    QTimer _timer;
    QVBoxLayout* grid;
    QStatusBar* sb;
    osg::ref_ptr<CoordHandler>toolcoordMouse;

    QDateTime time_current;
    QDate date_current;
    osg::ref_ptr<osg::Camera> camera;
    osg::ref_ptr< osgViewer::Viewer> view;
//    osg::ref_ptr<osgEarth::Util::EarthManipulator> manipulator;
    osg::ref_ptr<EarthManip> manipulator;
    osg::ref_ptr< MapNode > mapNode;//карта Земли
    osg::ref_ptr<osg::MatrixTransform> m_matrix_rotate_earth; //матрица поворота вращения земли
    osg::ref_ptr<osg::MatrixTransform> m_matrix_rotate_sky;
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    double m_angel_earth;// угол поворота Земли
};


#endif // OSGVIEWERQT_H
