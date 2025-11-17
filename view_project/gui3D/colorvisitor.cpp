#include "colorvisitor.h"

ColorVisitor::ColorVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
    m_color.set(1.0, 1.0, 1.0, 1.0);
    m_colorArrays = new osg::Vec4Array;
    m_colorArrays->push_back(m_color);
}

ColorVisitor::ColorVisitor(const osg::Vec4 &color):osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
    m_color = color;
    m_colorArrays = new osg::Vec4Array;
    m_colorArrays->push_back(m_color);
}

ColorVisitor::~ColorVisitor()
{

}

void ColorVisitor::apply(osg::Node &node)
{
    traverse(node);
};

void ColorVisitor::apply(osg::Geode &geode)
{
    unsigned int numGeoms = geode.getNumDrawables();
    for (unsigned int geodeIdx = 0; geodeIdx < numGeoms; geodeIdx++)
    {
        osg::Geometry *curGeom = geode.getDrawable(geodeIdx)->asGeometry();
        if (curGeom)
        {
            osg::Vec4Array *colorArrays = dynamic_cast<osg::Vec4Array *>(curGeom->getColorArray());
            if (colorArrays) {
//                for (unsigned int i = 0; i < colorArrays->size(); i++)
//                {
//                    osg::Vec4 *color = &colorArrays->operator [](i);
//                    color->set(m_color._v[0], m_color._v[1], m_color._v[2], m_color._v[3]);


//                }
                curGeom->setColorArray(m_colorArrays.get());
                curGeom->setColorBinding(osg::Geometry::BIND_OVERALL);

            }
            else
              { curGeom->setColorArray(m_colorArrays.get());
            curGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
            }
            //return;
        }
        //osg::ref_ptr<osg::Drawable> *geom=geode.getDrawable(geodeIdx)->asDrawable();
        //geom->get()->set
    }
}

void ColorVisitor::setColor(const float r, const float g, const float b, const float a)
{

    osg::Vec4 *c = &m_colorArrays->operator [](0); m_color.set(r, g, b, a);
    *c = m_color;
}

void ColorVisitor::setColor(const osg::Vec4 &color)
{
    osg::Vec4 *c = &m_colorArrays->operator [](0); m_color = color;
    *c = m_color;
};
