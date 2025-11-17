#ifndef ASDOBJECT3D_H
#define ASDOBJECT3D_H
#include <QDateTime>
#include <ASD/asdtype.h>
#include "scene3d.h"
#include "osg/Node"
class ASDScene3D;

class ASDObject3D: public osg::Node
{
public:
    virtual void repaint(QDateTime time, ASDScene3D* scene)=0;
    virtual bool remove(ASDScene3D* scene) = 0;
    protected:


};
class ASDPositionObj
{
protected:
    QVector<ASDPosObj> m_coord;
    QMap<QDateTime,ASDPosObj> m_coord_map;
    QDateTime m_time_begin;
    QDateTime m_time_end;

public:
    void setPosition(QVector<ASDPosObj> coord)
    {
        m_coord = coord;
        foreach (ASDPosObj pos, m_coord) {
            m_coord_map.insertMulti(pos.time_real,pos);
        }
        m_time_begin = m_coord_map.firstKey();
        m_time_end = m_coord_map.lastKey();
    }

    /*!
     * \brief ╨▓╨╛╨╖╤Ç╨░╤ë╨░╨╡╤é ╨┐╨╛╨╗╨╛╨╢╨╡╨╜╨╕╨╡ ╨╛╨▒╤è╨╡╨║╤é╨░ ╨╜╨░ ╨╖╨░╨┤╨░╨╜╨╜╨╛╨╡ ╨▓╤Ç╨╡╨╝╤Å
     * \param time - ╨▓╤Ç╨╡╨╝╤Å
     * \param pos - ╨┐╨╛╨╗╨╛╨╢╨╡╨╜╨╕╨╡
     * \return true - ╨╛╨▒╤è╨╡╨║╤é ╤ü╤â╤ë╨╡╤ü╤é╨▓╤â╨╡╤é ╨▓ ╨╖╨░╨┤╨░╨╜╨╜╤ï╨╣ ╨▓╤Ç╨╡╨╝╨╡╨╜╨╜╨╛╨╣ ╨╕╨╜╤é╨╡╤Ç╨▓╨░╨╗, false - ╨╛╨▒╤è╨╡╨║╤é╨░ ╨╜╨╡ ╤ü╤â╤ë╨╡╤ü╤é╨▓╤â╨╡╤é
     */
    bool getPosition(QDateTime time, ASDPosObj & pos)
    {
        QMap<QDateTime,ASDPosObj>::Iterator iter;

        if((time>m_time_begin)&&(time<m_time_end))
            for(iter = m_coord_map.begin(); iter != m_coord_map.end();iter++)
            {
                if(time<iter.key())
                {
                    pos = iter.value();
                    return true;
                }
            }
    }


};

#endif // ASDOBJECT3D_H
