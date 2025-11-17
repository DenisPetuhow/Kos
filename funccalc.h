#ifndef FUNCCALC_H
#define FUNCCALC_H
#include <QMap>
#include <QVector>
#include <math.h>
#include <QDateTime>
#include <ASD/asdcoordconvertor.h>
#include <ASD/asdtype.h>

//Расчет разрывов в наблюдении
/*!
  * \briefРасчет разрывов в наблюдении от освещенности
  * \param  plan - список всех зoн видимости для выбранных средст и пунктов(регионов)
  * \param  reg - список пунктов(регионов)
  * \param  elevSun - минимальный угол солнца (град)
  * \return разрывы в наблюдении для заданных пунктов
*/

QMap<QDateTime, int> SortPlan(QMap<int, mapTime_plan> plan, QVector<Paramregion> reg,QDateTime m_begTime ,QDateTime m_endTime ,double elevSun);
struct facilitypointDrawZona
{
    QString name;
    double lat;//!< широта  в град
    double lon;//!< долгота  в град
    double h;//! <высота в метрах
    double dzon;//!< размер зоны  в град
    int typezon;//0-прямоугольная 1-крговая
    QColor color;//  цвет линии
    QColor brushcolor;//  цвет заливки
    facilitypointDrawZona()
    {
        lat = 0.;
        lon = 0.;
        h = 0.;
        name = "";
        dzon=0.;
    }
};

struct facilitypointVizZona
{
    QString nameKA;//!<название КА
    int ID_Ka;//!<номер КА
    double lat;//!< широта пункта  в рад
    double lon;//!< долгота пункта в рад
    double el;//!< угол места на КА в рад
    double Lzon;//!< ширина полосы захвата КА в км
    double Szon;//!< максимю длина полосы КА в км(Lzon х Szon =площадь кадра)
    QDateTime time;//!< время
    facilitypointVizZona()
    {
        lat = 0.;
        lon = 0.;
        ID_Ka = 0;
        nameKA = "";
        el=0.;
        Lzon = 0.;
        Szon = 0.;
        time=QDateTime();
    }
    
    
    
};

#endif // FUNCCALC_H
