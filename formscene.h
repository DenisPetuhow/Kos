#ifndef FORMSCENE_H
#define FORMSCENE_H
#include <QtGui>
#include <QGraphicsScene>
#include <QWidget>
#include <QWheelEvent>
#include "ui_formscene.h"
#include <ASD/orbitalmotion.h>
#include <ASD/asdcoordconvertor.h>
#include <ASD/asdtype.h>

class Formscene : public QWidget,public Ui_Formscene
{
    Q_OBJECT

public:
    explicit Formscene(QWidget *parent = 0);
    ~Formscene();
    void clear();
    void settrassa( QMap<int, facilitypoint> trassa,QList<facilitypoint> KA);
    void setObjPoint(QList<facilitypoint> Obj);
    void setParamKA(QVector<ASDOrbitalObjectPar> kapar);
    void setCurrentTimepos(QDateTime tim);
    void setRegion(QVector<Paramregion > reg);

    void setPPI( QVector<ParamGrBaseInter> eathVehiclePPI);
    void setPPU( QVector<ParamGrBaseInter> eathVehiclePPU);
protected:
    void resizeEvent(QResizeEvent *event);

    void scaleView(qreal scaleFactor);
    /*!
 * \brief Обработка колеса прокрутки.
 * \param pe данные, передаваемые обработчику события
 */
    void wheelEvent(QWheelEvent* pe);

    // Обработка событий
    /*!
 * \brief Обработка нажатия клавиши мыши.
 * \param pe данные, передаваемые обработчику события
 */
    void mousePressEvent(QMouseEvent* pe);
protected slots:

    //void setenabletrassa(bool tt);
    //void setenabletrassaOBZ(bool tt);
    //void setenableRegionOBJ(bool tt);
    //void setenableRegion(bool tt);
    //void setenableZona(bool tt);
    void visibilObj();
private:
    void loadscene();
    QPoint ptrMousePosition; //!< Позиция указателя мыши
    QGraphicsScene* scene;
    QSize offSize; // size of the offscreen image
    QPixmap composedOffscreenImage;
    QList<bool> m_checkedbool;
    QList<bool> m_checkeregdbool;
    QList<bool> m_checkePPIdbool;
    QList<bool> m_checkePPUdbool;
    QVector<ParamGrBaseInter> m_eathVehiclePPI;
    QVector<ParamGrBaseInter> m_eathVehiclePPU;

    QVector<ASDOrbitalObjectPar> m_kapar;
    QList<facilitypoint> m_currentKA;
    QList< QVector<QPointF> > m_currentKAZon;
    QList< QVector<QPointF> > m_currentKAZon2;
    QDateTime m_currenttime;
    QMap<int, facilitypoint> m_trassa;
    QPixmap  m_carte;
    QList<QGraphicsLineItem *> m_satobz;
    QVector<Paramregion > m_reg;
    void trassaset();
    void postka();

    void calcposKA();
    QTreeWidgetItem* itemKA ;
    QTreeWidgetItem* itemREG;
    QTreeWidgetItem* itemPPI;
    QTreeWidgetItem* itemPPU;
signals:
    void sendcursat(QList<facilitypoint>);
};

#endif // FORMSCENE_H
