#include "osgviewerQt.h"
#include <QMessageBox>
#include <QDebug>


#define R_EARTH 6371

ViewerWidget::ViewerWidget(QWidget* parent, Qt::WindowFlags f, osgViewer::ViewerBase::ThreadingModel threadingModel) : QWidget(parent, f)
{
    setThreadingModel(threadingModel);

    // disable the default setting of viewer.done() by pressing Escape.
    setKeyEventSetsDone(0);
    m_root_agsk = new osg::Group();
    m_root_agsk->setName("m_root_agsk");
    m_root_gsk = new osg::Group();
    m_root_gsk->setName("m_root_gsk");
    QWidget* window = addViewWidget( createGraphicsWindow(0,0,600,600), m_root_agsk);
    grid = new QVBoxLayout;
    grid->addWidget(window);
    setLayout( grid );

    osg::ref_ptr<PickHandler> picker = new PickHandler();
    m_root_gsk->addChild( picker->getOrCreateSelectionBox() );
    view->addEventHandler( picker.get() );

    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
    _timer.start( 40 );
    m_angel_earth = 0;
}

ViewerWidget::~ViewerWidget()
{
    delete grid;
}

QWidget* ViewerWidget::addViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
{
    view = new osgViewer::Viewer;
    addView( view );
    camera = view->getCamera();
    camera->setGraphicsContext( gw );

    const osg::GraphicsContext::Traits* traits = gw->getTraits();

    camera->setClearColor( osg::Vec4(0., 0., 0., 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(30.0, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 100.0 );

    view->setSceneData( scene );
    view->addEventHandler(new osgViewer::StatsHandler);
    view->setThreadingModel(osgViewer::Viewer::SingleThreaded);

    manipulator = new EarthManip;
    EarthManip::Settings *settings = manipulator->getSettings();


    settings->bindMouse(EarthManip::ACTION_ROTATE,
                        osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON,
                        osgGA::GUIEventAdapter::MODKEY_ALT);
    EarthManip::ActionOptions options;
    options.clear();
    options.add(EarthManip::OPTION_CONTINUOUS, true);
    settings->bindMouse(EarthManip::ACTION_ZOOM,
                        osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON,
                        osgGA::GUIEventAdapter::MODKEY_ALT, options);
    settings->setMinMaxDistance(5.0e5, 1.0e8);
    //manipulator->setViewpoint(osgEarth :: Util :: Viewpoint(116,40,0,0,-90,6371*4),5);
    manipulator->applySettings(settings);



    view->setCameraManipulator( manipulator);

    osgDB::Registry::instance()->getObjectWrapperManager()->findWrapper("osg::Image");
    view->getCamera()->setSmallFeatureCullingPixelSize(-1.0f);
    view->getCamera()->setNearFarRatio(0.0001);
    gw->setTouchEventsEnabled(true);



    return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* ViewerWidget::createGraphicsWindow( int x, int y, int w, int h, const std::string& name, bool windowDecoration )
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = name;
    traits->windowDecoration = windowDecoration;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    if (traits->height == 0)
        traits->height = 1;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    return new osgQt::GraphicsWindowQt(traits.get());
}

osg::ref_ptr<osg::Group> ViewerWidget::addPoint(osg::ref_ptr<osg::Group> node_perant,QVector<double> coord, QString image_name)
{
    osg::ref_ptr<osg::Node> geode1 = new osg::Node();
    geode1 = osgDB::readNodeFile("satelite.3ds");
    osg::StateSet* state_satellite = geode1->getOrCreateStateSet();
    state_satellite->setMode( GL_LIGHTING, osg::StateAttribute::ON); //включение освещения
    state_satellite->setMode( GL_RESCALE_NORMAL, osg::StateAttribute::ON );
    osg::ref_ptr<osg::Material> mat = new osg::Material;
    mat->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    state_satellite->setAttribute( mat.get() );

    osg::ref_ptr<osg::PositionAttitudeTransform> transform_satellite = new osg::PositionAttitudeTransform();
    transform_satellite->addChild(geode1);
    osg::BoundingSphere sphere = transform_satellite->computeBound();
    transform_satellite->setPosition(-sphere.center());
    transform_satellite->setScale(osg::Vec3d(10e1,10e1,10e1));
    transform_satellite->setPosition(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));

    //создание плоскости
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( osg::Vec3(-5.0f, -5.0f,0.0f) );
    vertices->push_back( osg::Vec3( 5.0f, -5.0f,0.0f) );
    vertices->push_back( osg::Vec3( 5.0f, 5.0f, 0.0f) );
    vertices->push_back( osg::Vec3(-5.0f, 5.0f, 0.0f) );
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back( osg::Vec3(0.0f,0.0f, 0.0f) );

    //создание координат текстурной привязки
    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
    texcoords->push_back( osg::Vec2(0.0f, 0.0f) );
    texcoords->push_back( osg::Vec2(0.0f, 1.0f) );
    texcoords->push_back( osg::Vec2(1.0f, 1.0f) );
    texcoords->push_back( osg::Vec2(1.0f, 0.0f) );

    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;

    quad->setVertexArray( vertices.get() );
    quad->setNormalArray( normals.get() );
    quad->setNormalBinding( osg::Geometry::BIND_OVERALL );
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    quad->setColorArray( c.get(),  osg::Array::BIND_OVERALL );
    quad->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    quad->setTexCoordArray( 0, texcoords.get() );
    quad->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, 0, 4) );

    osg::ref_ptr<osg::Image> image =  osgDB::readImageFile( image_name.toStdString());
    osg::ref_ptr<osg::Texture2D> textureKA = new osg::Texture2D;
    textureKA->setImage( image );
    textureKA-> setWrap (osg :: Texture :: WRAP_S, osg :: Texture :: CLAMP_TO_EDGE );
    textureKA-> setWrap (osg :: Texture :: WRAP_T, osg :: Texture :: CLAMP_TO_EDGE);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( quad.get() );
    osg::StateSet* state = geode->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    state->setAttributeAndModes( blendFunc );
    state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    state->setTextureAttributeAndModes( 0, textureKA.get() );

    //Настройки автомаштабирования
    osg::ref_ptr<osg::PositionAttitudeTransform> matrix_scale = new osg::PositionAttitudeTransform;
    matrix_scale->addChild(geode);
    matrix_scale->setScale(osg::Vec3d(3,3,3));
    osg::AutoTransform* at = new osg::AutoTransform;
    at->addChild(matrix_scale);
    at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
    at->setAutoScaleToScreen(true);
    at->setMinimumScale(0);
    at->setMaximumScale(5000);
    //----------------------------------
    osg::ref_ptr<osg::PositionAttitudeTransform> matrix_rectangle = new osg::PositionAttitudeTransform;
    matrix_rectangle->addChild(at);
    matrix_rectangle->setScale(osg::Vec3d(3e10,3e10,3e10));
    matrix_rectangle->setAttitude(osg::Quat(osg::PI, osg::Y_AXIS));
    matrix_rectangle->setPosition(osg::Vec3d(coord[0]*1000,coord[1]*1000,coord[2]*1000));

    osg::ref_ptr<osg::LOD> lod = new osg::LOD;
    lod->addChild(matrix_rectangle,50e4,float(10e10));
    lod->addChild(transform_satellite,float(0.1),50e4);

    node_perant->addChild(lod);
    return( node_perant.get());
}

void ViewerWidget::moveEarth(QDateTime time2)
{






    time_current = time2;
    m_angel_earth = ASDCoordConvertor::compSiderealTime(time2);
    manipulator->angleMoveEarth(m_angel_earth);
    osg::Matrix mt1;
    mt1 = osg::Matrix::rotate(osg::Quat(m_angel_earth, osg::Z_AXIS));
    m_matrix_rotate_earth->setMatrix(mt1);

    if(date_current != time_current.date())
    {
        DateTime time(time_current.date().year(),time_current.date().month(),time_current.date().day(),time_current.time().hour()-3);
        sky_node->setDateTime(time);
        m_matrix_rotate_sky->setMatrix(mt1);
        date_current = time_current.date();
    }




}

void ViewerWidget::addPointAGSK(QVector<double> coord, QString image)
{
    addPoint(m_root_agsk,coord,image);
}

void ViewerWidget::addAxesOSGT(osg::ref_ptr<osg::Group> node_perant)
{
    osg::ref_ptr<osg::Node>  axes  =  osgDB :: readNodeFile ("axes.osgt");
    atAxes = new osg::AutoTransform;
    axes->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF );
    atAxes->addChild(axes);
    atAxes->setAutoScaleToScreen(true);
    atAxes->setMaximumScale(2e7);
    atAxes->setMinimumScale(1e7);
    node_perant->addChild(atAxes.get());
}

void ViewerWidget::clearScene(osg::ref_ptr<osg::Group> node_perant)
{
    node_perant->removeChild(atAxes.get());
}

void ViewerWidget::addPointAGSK(QVector<QVector<double> > coord, QVector<QColor> color)
{
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    for(int i = 0; i<color.size(); i++)
        colors->push_back(osg::Vec4( color[i].red(), color[i].green(), color[i].blue(), color[i].alpha()));
    osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
    for(int i = 0; i<coord.size(); i++)
        coords->push_back(osg::Vec3d( coord[i][0], coord[i][1], coord[i][2]));
    osg::ref_ptr<osg::Geometry> geometr= new osg::Geometry;
    geometr->setDataVariance( osg::Object::DYNAMIC );
    geometr->setUseDisplayList( false );
    geometr->setUseVertexBufferObjects( true );
    geometr->setVertexArray( coords);
    geometr->setColorArray( colors);
    geometr->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    geometr->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, coord.size()) );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( geometr.get() );
    geode->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(3.0f) );
    m_root_agsk->addChild(geode.get());
}

void ViewerWidget::addPointGSK(QVector<double> coord, QString image)
{
    addPoint(m_root_gsk,coord,image);
}

void ViewerWidget::addLight()
{
    osg::ref_ptr<osg::Light> light = new osg::Light;
    light->setAmbient( osg::Vec4(.1f, .1f, .1f, 1.f ));
    light->setDiffuse( osg::Vec4( 0.8f, 0.8f, 0.8f, 0.8f ));
    light->setSpecular( osg::Vec4( 1.f, 1.f, 1.f, 1.f ));
    light->setPosition( osg::Vec4( 1.f, 0.f, 0.f,1.f ));
    light->setDirection( osg::Vec3( 0.f, 0.f, 0.f ));
    light->setLightNum( 1 );
    osg::ref_ptr<osg::PositionAttitudeTransform> mt = new osg::PositionAttitudeTransform;
    mt->setPosition(osg::Vec3(3e7, 0, 0));
    osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
    mt->addChild( ls.get() );
    ls->setLight( light.get() );
    osg::ref_ptr< osg::AutoTransform> at = new osg::AutoTransform;
    at->addChild(mt);
    at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_CAMERA);
    m_root_agsk->getOrCreateStateSet()->setMode( GL_LIGHT1,osg::StateAttribute::ON );
    m_root_agsk->addChild(at.get());
}

void ViewerWidget::createEarth(osg::ref_ptr<osg::Group> node_perant, QString file)
{

    osg::ref_ptr<osgDB::Options> options = new osgDB::Options;
    options->setObjectCacheHint(osgDB::Options::CACHE_NONE);
    options->setBuildKdTreesHint( osgDB::Options::BUILD_KDTREES );

    globe  =  osgDB :: readNodeFile ( file.toStdString());
    if(globe==nullptr)
    {
        QMessageBox::critical(nullptr, QObject::trUtf8("Ошибка"), QObject::trUtf8("Ошибка при загрузке Земли"));
        return;
    }
    mapNode = MapNode::get( globe );
    node_perant->addChild(globe);
    m_matrix_rotate_earth = new osg::MatrixTransform();
    m_matrix_rotate_earth->addChild(node_perant);
    m_root_agsk->addChild(m_matrix_rotate_earth);



}

void ViewerWidget::createGlobe(osg::ref_ptr<osg::Group> node_perantGSK, QString file)
{
    globe  =  osgDB :: readNodeFile ( file.toStdString());
    if(globe==nullptr)
    {
        QMessageBox::critical(nullptr, QObject::trUtf8("Ошибка2"), QObject::trUtf8("Ошибка при загрузке Земли"));
        return;
    }
    mapNode = MapNode::get( globe );
    node_perantGSK->addChild(globe);
    m_matrix_rotate_earth->addChild(node_perantGSK);

    coordMouse();
}

void ViewerWidget::clearGlobe(osg::ref_ptr<osg::Group> node_perantGSK)
{
    mapNode->removeChild(globe);
    node_perantGSK->removeChild(globe);
    m_matrix_rotate_earth->removeChild(node_perantGSK);

    view->removeEventHandler(toolcoordMouse);
}

osg::ref_ptr<osgEarth::MapNode> ViewerWidget::getMapEarth()
{
    return(mapNode);
}

void ViewerWidget::createSky(osg::ref_ptr<osg::Group> node_perant, QDateTime time)
{
    osgEarth::DateTime dt(time.date().year(), time.date().month(), time.date().day(), time.time().hour()-3);
    sky_node = osgEarth::Util::SkyNode::create(osgEarth::MapNode::findMapNode(mapNode));

    sky_node->setDateTime(dt);
    sky_node = SkyNode::create();
    sky_node->setAtmosphereVisible(false);
    sky_node->setMoonVisible(true);
    sky_node->setSunVisible(true);
    m_matrix_rotate_sky = new osg::MatrixTransform();
    m_matrix_rotate_sky->addChild(sky_node);

    node_perant->addChild(m_matrix_rotate_sky);
}

void ViewerWidget::clearSky(osg::ref_ptr<osg::Group> node_perant)
{
    node_perant->removeChild(m_matrix_rotate_sky);
}

void ViewerWidget::createSun()
{
    sky_node->setSunVisible(true);
}

void ViewerWidget::clearSun()
{
    sky_node->setSunVisible(false);
}

void ViewerWidget::createStars()
{
    sky_node->setStarsVisible(true);
}

void ViewerWidget::clearStars()
{
    sky_node->setStarsVisible(false);
}

void ViewerWidget::createAtmosphere()
{
    sky_node->setAtmosphereVisible(true);
}

void ViewerWidget::clearAtmosphere()
{
    sky_node->setAtmosphereVisible(false);
}

osg::ref_ptr<osg::Group> ViewerWidget::addEarthPicture( double lat, double lon, QString icon)
{
    osg::ref_ptr<osg::Group> m_group = new osg::Group;
    osg::Image* image = osgDB::readImageFile(icon.toStdString());
    ImageOverlay* imageOverlay = nullptr;
    imageOverlay = new ImageOverlay(mapNode, image);
    imageOverlay->setBounds(Bounds(lat/M_PI*180-2, lon/M_PI*180-2, lat/M_PI*180+2, lon/M_PI*180+2));
    m_group->addChild(imageOverlay);
    return(m_group);
}

void ViewerWidget::addConus(QVector<double> coord, QVector<double> coordEnd, double h, double gamma, QColor color)
{
    QVector <double> coord1(3);
    coord1[0] = coordEnd[0]-coord[0];
    coord1[1] = coordEnd[1]-coord[1];
    coord1[2] = coordEnd[2]-coord[2];
    double h1 = pow(coord1[0]*coord1[0]+coord1[1]*coord1[1]+coord1[2]*coord1[2],0.5);
    double h2 = pow(coord1[0]*coord1[0]+coord1[1]*coord1[1],0.5);
    double r = h*tan(gamma);
    double beta = asin(coord1[2]/h1);
    double alfa=0;
    if(h2 != 0.0)
    {
        alfa = ASDCoordConvertor::angle(coord1[1]/h2,coord1[0]/h2);
    }

    osg::ref_ptr<osg::Cone> model = new osg::Cone(osg::Vec3d(0.0,0.0,-0.75*h1),float(r), float(h1));
    osg::ref_ptr<osg::ShapeDrawable> geom = new osg::ShapeDrawable();
    geom->setShape(model);
    geom->setColor(osg::Vec4f(color.red(),color.green(),color.blue(),color.alpha()));
    osg::ref_ptr<osg::Geode> geod = new osg::Geode();
    geod->addDrawable(geom);

    osg::StateSet* state = geod->getOrCreateStateSet();
    osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    state->setAttributeAndModes( blendFunc );
    state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON  );

    osg::ref_ptr<osg::MatrixTransform> matrix_rotate = new osg::MatrixTransform;
    osg::Matrix mt1,mt2,mt3,mt4,mt_sum;
    mt1 = osg::Matrix::rotate(osg::Quat(-M_PI/2., osg::Y_AXIS));
    mt2 = osg::Matrix::rotate(osg::Quat(alfa, osg::Z_AXIS));
    mt3 = osg::Matrix::rotate(osg::Quat(-beta, osg::Y_AXIS));
    mt4 = osg::Matrix::translate(osg::Vec3d(coord[0],coord[1],coord[2]));
    mt_sum = mt1*mt3*mt2*mt4;
    matrix_rotate->setMatrix(mt_sum);
    matrix_rotate->addChild(geod);
    m_root_gsk->addChild(matrix_rotate);
}

void ViewerWidget::addAxisXYZ(osg::ref_ptr<osg::Group> node_perant)
{
    osg::Vec3 x0(0,0,0);
    osg::Vec3 x1(3*1e8,0,0);
    osg::ref_ptr<osg::Geometry> axisX (new osg::Geometry);
    osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array;
    points->push_back(x0);
    points->push_back(x1);
    osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
    color->push_back(osg::Vec4(1.0,0,0,1));
    axisX->setVertexArray(points);
    axisX->setColorArray(color);
    axisX->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
    axisX->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,2));
    osg::ref_ptr<osg::Geode> g_axisX = new osg::Geode;
    g_axisX->addDrawable(axisX.get());
    osg::StateSet* state = g_axisX->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
    node_perant->addChild(g_axisX.get());

    osg::Vec3 y0(0,0,0);
    osg::Vec3 y1(0,3*1e8,0);
    osg::ref_ptr<osg::Geometry> axisY (new osg::Geometry);
    osg::ref_ptr<osg::Vec3Array> pointsY = new osg::Vec3Array;
    pointsY->push_back(y0);
    pointsY->push_back(y1);
    osg::ref_ptr<osg::Vec4Array> colorY = new osg::Vec4Array;
    colorY->push_back(osg::Vec4(0,1,0,1));
    axisY->setVertexArray(pointsY);
    axisY->setColorArray(colorY);
    axisY->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
    axisY->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,2));
    osg::ref_ptr<osg::Geode> g_axisY = new osg::Geode;
    g_axisY->addDrawable(axisY.get());
    state = g_axisY->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
    node_perant->addChild(g_axisY.get());

    osg::Vec3 z0(0,0,0);
    osg::Vec3 z1(0,0,3*1e8);
    osg::ref_ptr<osg::Geometry> axisZ (new osg::Geometry);
    osg::ref_ptr<osg::Vec3Array> pointsZ = new osg::Vec3Array;
    pointsZ->push_back(z0);
    pointsZ->push_back(z1);
    osg::ref_ptr<osg::Vec4Array> colorZ = new osg::Vec4Array;
    colorZ->push_back(osg::Vec4(0,0,1,1));
    axisZ->setVertexArray(pointsZ);
    axisZ->setColorArray(colorZ);
    axisZ->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
    axisZ->addPrimitiveSet(new osg::DrawArrays(GL_LINES,0,2));
    osg::ref_ptr<osg::Geode> g_axisZ = new osg::Geode;
    g_axisZ->addDrawable(axisZ.get());
    state = g_axisZ->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
    g_axisZ->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(3.0f) );
    node_perant->addChild(g_axisZ.get());
}

void ViewerWidget::addSphereSegment(double latitude, double longitude, double radius, double minAzim, double maxAzim, double minElev, double maxElev, QColor color)
{
    QVector<double> coord = ASDCoordConvertor::convGeoToGsc(latitude, longitude,0);
    osg::Vec3d center(coord[0]*1000+6000000,coord[1]*1000+6000000,coord[2]*1000+600000);
    osg::ref_ptr<osgSim::SphereSegment> segment  = new osgSim::SphereSegment(center, float(radius*1000), float(minAzim), float(maxAzim), float(minElev), float(maxElev), 1000);
    osg::StateSet* state = segment->getOrCreateStateSet();
    osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    state->setAttributeAndModes( blendFunc );
    state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON );
    osg::ref_ptr<osg::LineWidth> line = new osg::LineWidth;
    line->setWidth(2); //установление ширины линии
    state->setAttributeAndModes( line);
    segment->setDrawMask(osgSim::SphereSegment::SPOKES | osgSim::SphereSegment::EDGELINE);
    segment->setAllColors(osg::Vec4f(color.red(),color.green(),color.blue(),color.alpha()));
    m_root_gsk->addChild(segment.get());
}

osg::ref_ptr<osg::MatrixTransform> ViewerWidget::addObject( QString name_3dx)
{
    osg::ref_ptr<osg::Node> geode1 = new osg::Node();

    geode1 = osgDB::readNodeFile(name_3dx.toStdString());
    osg::StateSet* state_satellite = geode1->getOrCreateStateSet();

    state_satellite->setMode( GL_RESCALE_NORMAL, osg::StateAttribute::ON );

    osg::ref_ptr<osg::MatrixTransform> transform_satellite = new osg::MatrixTransform();
    transform_satellite->addChild(geode1);
    osg::Matrix mt,mt1;
    mt1 = mt1.rotate(osg::Quat(-M_PI/2, osg::Z_AXIS));

    mt = mt.scale(osg::Vec3d(2500,2500,2500));
    transform_satellite->setMatrix(mt*mt1);
    return transform_satellite;
}

osg::ref_ptr<osg::MatrixTransform> ViewerWidget::addObjectIconPoint(QString name_image)
{
    //создание плоскости
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( osg::Vec3(-10.0f, -10.0f,0.0f) );
    vertices->push_back( osg::Vec3( 10.0f, -10.0f,0.0f) );
    vertices->push_back( osg::Vec3( 10.0f, 10.0f, 0.0f) );
    vertices->push_back( osg::Vec3(-10.0f, 10.0f, 0.0f) );
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back( osg::Vec3(0.0f,0.0f, 0.0f) );
    //создание координат текстурной привязки
    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
    texcoords->push_back( osg::Vec2(0.0f, 0.0f) );
    texcoords->push_back( osg::Vec2(0.0f, 1.0f) );
    texcoords->push_back( osg::Vec2(1.0f, 1.0f) );
    texcoords->push_back( osg::Vec2(1.0f, 0.0f) );
    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;

    quad->setVertexArray( vertices.get() );
    quad->setNormalArray( normals.get() );
    quad->setNormalBinding( osg::Geometry::BIND_OVERALL );
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    quad->setColorArray( c.get(),  osg::Array::BIND_OVERALL );
    quad->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    quad->setTexCoordArray( 0, texcoords.get() );
    quad->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, 0, 4) );

    osg::ref_ptr<osg::Image> image =  osgDB::readImageFile( name_image.toStdString());
    osg::ref_ptr<osg::Texture2D> textureKA = new osg::Texture2D;

    textureKA->setImage( image );
    textureKA-> setWrap (osg :: Texture :: WRAP_S, osg :: Texture :: CLAMP_TO_EDGE );
    textureKA-> setWrap (osg :: Texture :: WRAP_T, osg :: Texture :: CLAMP_TO_EDGE);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( quad.get() );
    osg::StateSet* state = geode->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    state->setAttributeAndModes( blendFunc );
    state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    state->setTextureAttributeAndModes( 0, textureKA.get() );
    //Настройки автомаштабирования
    osg::ref_ptr<osg::PositionAttitudeTransform> matrix_scale = new osg::PositionAttitudeTransform;
    matrix_scale->addChild(geode);
    matrix_scale->setScale(osg::Vec3d(3,3,3));
    //----------------------------------
    osg::ref_ptr<osg::MatrixTransform> matrix_rectangle = new osg::MatrixTransform;
    matrix_rectangle->addChild(matrix_scale);
    return matrix_rectangle;
}

QVector<double> calcCoordObjInIsc(ASDAngleMounting angle, double D)
{
    QVector <double> X(6,0);
    double D_xy = D*cos(angle.pitch);

    X[0] = D_xy*cos(angle.yaw);
    X[1] = D*sin(angle.pitch);
    X[2] = D_xy*sin(angle.yaw);
    X[3] = 0.0;
    X[4] = 0.0;
    X[5] = 0.0;

    return X;
}

osg::ref_ptr<osg::MatrixTransform> ViewerWidget::addObjectPyramid(double roll, double deltaV, double deltaH, double dist)
{
    osg::ref_ptr<osg::MatrixTransform> m_pyramid = new osg::MatrixTransform();
    ASDAngleMounting angle;
    angle.roll = roll;
    angle.pitch = -deltaV/2;
    angle.yaw = -deltaH/2;
    QVector <double> coord_Ics1;
    coord_Ics1 = calcCoordObjInIsc(angle, dist*1000);

    angle.pitch = - deltaV/2;
    angle.yaw = deltaH/2;
    QVector <double> coord_Ics2;
    coord_Ics2 = calcCoordObjInIsc(angle, dist*1000);

    angle.pitch = deltaV/2;
    angle.yaw =  - deltaH/2;
    QVector <double> coord_Ics3;
    coord_Ics3 = calcCoordObjInIsc(angle, dist*1000);

    angle.pitch = deltaV/2;
    angle.yaw = deltaH/2;
    QVector <double> coord_Ics4;
    coord_Ics4 = calcCoordObjInIsc(angle, dist*1000);

    osg::ref_ptr<osg::Geode> pyramidGeode = new osg::Geode();
    osg::ref_ptr<osg::Geometry> pyramidGeometry = new osg::Geometry();
    osg::ref_ptr<osg::DrawElementsUInt> pyramidBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    pyramidBase->push_back(3);
    pyramidBase->push_back(2);
    pyramidBase->push_back(1);
    pyramidBase->push_back(0);
    pyramidGeometry->addPrimitiveSet(pyramidBase);

    osg::ref_ptr<osg::Vec3Array> pyramidVertices = new osg::Vec3Array;
    pyramidVertices->push_back( osg::Vec3d( coord_Ics1[0], coord_Ics1[1], coord_Ics1[2]));   // front left
    pyramidVertices->push_back( osg::Vec3d(coord_Ics2[0], coord_Ics2[1], coord_Ics2[2]));    // front right
    pyramidVertices->push_back( osg::Vec3d(coord_Ics4[0], coord_Ics4[1], coord_Ics4[2]));    // back left
    pyramidVertices->push_back( osg::Vec3d(coord_Ics3[0], coord_Ics3[1], coord_Ics3[2]));    // back right
    pyramidVertices->push_back( osg::Vec3d( 0, 0, 0) );                                     // peak
    pyramidGeometry->setVertexArray( pyramidVertices );

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceOne = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceOne->push_back(0);
    pyramidFaceOne->push_back(1);
    pyramidFaceOne->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceOne);

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceTwo = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceTwo->push_back(1);
    pyramidFaceTwo->push_back(2);
    pyramidFaceTwo->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceTwo);

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceThree = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceThree->push_back(2);
    pyramidFaceThree->push_back(3);
    pyramidFaceThree->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceThree);

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceFour = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceFour->push_back(3);
    pyramidFaceFour->push_back(0);
    pyramidFaceFour->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceFour);

    pyramidGeode->addDrawable(pyramidGeometry);
    m_pyramid->addChild(pyramidGeode);

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 0.2f) );
    pyramidGeometry->setColorArray(colors);
    pyramidGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    osg::ref_ptr<osg::StateSet> state = pyramidGeode->getOrCreateStateSet();
    osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    state->setAttributeAndModes( blendFunc );
    state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    state->setAttributeAndModes( pm, osg::StateAttribute::OVERRIDE | osg::StateAttribute::OFF  );

    osg::ref_ptr<osg::Geode> pyramidGeode2 = new osg::Geode();
    osg::ref_ptr<osg::Geometry> pyramidGeometry2 = new osg::Geometry();
    pyramidGeode2->addDrawable(pyramidGeometry2);
    m_pyramid->addChild(pyramidGeode2);

    osg::ref_ptr<osg::Vec4Array> colors2 = new osg::Vec4Array;
    colors2->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f) );
    pyramidGeometry2->setVertexArray( pyramidVertices );
    pyramidGeometry2->addPrimitiveSet(pyramidBase);
    pyramidGeometry2->addPrimitiveSet(pyramidFaceOne);
    pyramidGeometry2->addPrimitiveSet(pyramidFaceTwo);
    pyramidGeometry2->addPrimitiveSet(pyramidFaceThree);
    pyramidGeometry2->addPrimitiveSet(pyramidFaceFour);
    pyramidGeometry2->setColorArray(colors2);
    pyramidGeometry2->setColorBinding(osg::Geometry::BIND_OVERALL);
    osg::ref_ptr<osg::StateSet> state2 = pyramidGeode2->getOrCreateStateSet();
    osg::ref_ptr<osg::PolygonMode> pm2 = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
    state2->setMode( GL_LIGHTING, osg::StateAttribute::OFF);
    osg::ref_ptr<osg::BlendFunc> blendFunc2 = new osg::BlendFunc;
    blendFunc2->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    state2->setAttributeAndModes( blendFunc2 );
    state2->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    state2->setAttributeAndModes( pm2, osg::StateAttribute::OVERRIDE | osg::StateAttribute::OFF  );

    return m_pyramid.get();
}

osg::ref_ptr<osg::MatrixTransform> ViewerWidget::addObjectIcon(QString name_image)
{
    //создание плоскости
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( osg::Vec3(-10.0f, -10.0f,0.0f) );
    vertices->push_back( osg::Vec3( 10.0f, -10.0f,0.0f) );
    vertices->push_back( osg::Vec3( 10.0f, 10.0f, 0.0f) );
    vertices->push_back( osg::Vec3(-10.0f, 10.0f, 0.0f) );
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back( osg::Vec3(0.0f,0.0f, 0.0f) );
    //создание координат текстурной привязки
    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
    texcoords->push_back( osg::Vec2(0.0f, 0.0f) );
    texcoords->push_back( osg::Vec2(0.0f, 1.0f) );
    texcoords->push_back( osg::Vec2(1.0f, 1.0f) );
    texcoords->push_back( osg::Vec2(1.0f, 0.0f) );
    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;

    quad->setVertexArray( vertices.get() );
    quad->setNormalArray( normals.get() );
    quad->setNormalBinding( osg::Geometry::BIND_OVERALL );
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    quad->setColorArray( c.get(),  osg::Array::BIND_OVERALL );
    quad->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f  ) );
    quad->setTexCoordArray( 0, texcoords.get() );
    quad->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, 0, 4) );

    osg::ref_ptr<osg::Image> image =  osgDB::readImageFile( name_image.toStdString());
    osg::ref_ptr<osg::Texture2D> textureKA = new osg::Texture2D;

    textureKA->setImage( image );
    textureKA-> setWrap (osg :: Texture :: WRAP_S, osg :: Texture :: CLAMP_TO_EDGE );
    textureKA-> setWrap (osg :: Texture :: WRAP_T, osg :: Texture :: CLAMP_TO_EDGE);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->setName("qwrwqrqwrqw0");
    geode->addDrawable( quad.get() );
    osg::StateSet* state = geode->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF); //включение освещения
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
    blendFunc->setFunction( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
    state->setAttributeAndModes( blendFunc );
    state->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    state->setTextureAttributeAndModes( 0, textureKA.get() );
    //Настройки автомаштабирования
    osg::ref_ptr<osg::PositionAttitudeTransform> matrix_scale = new osg::PositionAttitudeTransform;
    matrix_scale->addChild(geode);
    matrix_scale->setScale(osg::Vec3d(5,5,5));
    osg::AutoTransform* at = new osg::AutoTransform;
    at->addChild(matrix_scale);
    at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
    at->setAutoScaleToScreen(true);
    at->setMinimumScale(0);
    at->setMaximumScale(10000);
    //----------------------------------
    osg::ref_ptr<osg::MatrixTransform> matrix_rectangle = new osg::MatrixTransform;
    matrix_rectangle->addChild(at);

    return matrix_rectangle;
}

void ViewerWidget::coordMouse()
{
    toolcoordMouse = new CoordHandler(mapNode);
    osg::ref_ptr<PrintCoordsToStatusBar> status_bar =  new PrintCoordsToStatusBar(sb);
    status_bar->addTime(&time_current);
    toolcoordMouse->addCallback(status_bar.get());
    view->addEventHandler( toolcoordMouse );
}

bool CoordHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    if ( ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT )
    {
        return MouseCoordsTool::handle(ea, aa);
    }
    return false;
}

osg::Node *PickHandler::getOrCreateSelectionBox()
{
    if ( !_selectionBox )
    {
        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(),1.0f)) );
        _selectionBox = new osg::MatrixTransform;
        _selectionBox->setNodeMask( 0x1 );
        _selectionBox->addChild( geode.get() );
        osg::StateSet* ss = _selectionBox->getOrCreateStateSet();
        ss->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
        ss->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE));
    }
    return _selectionBox.get();
}

bool PickHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    if ( ea.getEventType()!=osgGA::GUIEventAdapter::RELEASE || ea.getButton()!=osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
         || !(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL) )
        return false;
    osgViewer::Viewer* viewer =
            dynamic_cast<osgViewer::Viewer*>(&aa);
    if ( viewer )
    {
        osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(
                    osgUtil::Intersector::WINDOW, double(ea.getX()), double(ea.getY()));
        osgUtil::IntersectionVisitor iv( intersector.get() );
        iv.setTraversalMask( ~0x1 );
        viewer->getCamera()->accept( iv );
        if ( intersector->containsIntersections() )
        {
            const osgUtil::LineSegmentIntersector::Intersection& result =  *(intersector->getIntersections().begin());
            osg::BoundingBox bb = result.drawable->getBoundingBox();
            osg::Vec3 worldCenter = bb.center() * osg::computeLocalToWorld(result.nodePath); //координаты объекта в мировой системе координат

            osg::Matrixd mt;
            mt.makeLookAt(worldCenter*float(1.1),osg::Vec3d(0,0,0),osg::Vec3d(0,0,200000));

            viewer->getCameraManipulator()->setByInverseMatrix(mt);
        }
    }
    return false;
}

//void nodePick3D::setObjAll(QVector<ParamGrBase> station, QVector<ASDOrbitalObjectPar> ka, QVector <ASDZoneVisiblePoint> mapObzRegionKA, QDateTime curtime)
//{
//    m_station = station;
//    m_ka = ka;
//    m_mapObzRegionKA = mapObzRegionKA;
//    m_curtime = curtime;
//}

bool nodePick3D::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    if ( ea.getEventType()!=osgGA::GUIEventAdapter::RELEASE         ||
         ea.getButton()!=osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON  ||
         ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_SHIFT    ||
         ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL     ||
         ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_ALT)
        return false;

    return false;// ?????????? TEMP
    osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer*> (&aa);
    osgUtil::LineSegmentIntersector::Intersections intersections;
    osg::ref_ptr<osg::Node> node = new osg::Node();

    if (viewer->computeIntersections(ea.getX(), ea.getY(), intersections))
    {
        // Get the selected node
        osgUtil::LineSegmentIntersector::Intersection intersection = *intersections.begin();
        osg::NodePath& nodePath = intersection.nodePath;
        node = nodePath.back();

        osg::ref_ptr<osg::Group> group1 = dynamic_cast<osg::Group*>( nodePath[2]);
        osg::ref_ptr<osg::Group> group2 = dynamic_cast<osg::Group*>( nodePath[4]);

        //        if(QString::fromStdString(group2->getName())!=QString::fromStdString("osgEarth::MapNode"))
        //        {
        //            if (!QString::fromStdString(group2->getName()).isEmpty())
        //            {
        //                if(m_station.size()>0)
        //                {
        //                    CInfoSEV *inf = new CInfoSEV();
        //                    HDC hDCScreen = GetDC(NULL);
        //                    int Hpix = GetDeviceCaps(hDCScreen, HORZRES)-25;//ширина экрана, pix
        //                    inf->move(Hpix/2+20,30);
        //                    inf->raise();
        //                    inf->getSEVmap(QString::fromStdString(group2->getName()), m_station, m_ka, m_mapObzRegionKA, m_curtime);
        //                    inf->adjustSize();
        //                    inf->exec();
        //                }
        //            }
        //            if (!QString::fromStdString(group1->getName()).isEmpty())
        //            {
        //                if(m_ka.size()>0)
        //                {
        //                    CInfoKA *inf = new CInfoKA();
        //                    HDC hDCScreen = GetDC(NULL);
        //                    int Hpix = GetDeviceCaps(hDCScreen, HORZRES)-25;//ширина экрана, pix
        //                    inf->move(Hpix/2+20,30);
        //                    inf->raise();
        //                    inf->getKAmap(QString::fromStdString(group1->getName()), m_ka, m_curtime);
        //                    inf->adjustSize();
        //                    inf->exec();
        //                }
        //            }
        //        }
    }
    return false;
}
