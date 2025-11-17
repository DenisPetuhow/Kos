#ifndef COLORVISITOR_H
#define COLORVISITOR_H

#pragma once
#include <osg/Array>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/NodeVisitor>
#include <osg/Vec4>

class ColorVisitor : public osg::NodeVisitor
{
public:
    ColorVisitor();
    ColorVisitor(const osg::Vec4 &color);
    virtual ~ColorVisitor();
    virtual void apply(osg::Node &node);
    virtual void apply(osg::Geode &geode);
    virtual void setColor(const float r, const float g, const float b, const float a = 1.0f); virtual void setColor(const osg::Vec4 &color);
    private:
    osg::Vec4 m_color;
    osg::ref_ptr< osg::Vec4Array > m_colorArrays;
};

#endif // COLORVISITOR_H
