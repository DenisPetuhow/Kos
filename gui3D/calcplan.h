#ifndef CALCPLAN_H
#define CALCPLAN_H

#include <QCoreApplication>
#include <QFile>
#include <QObject>
#include <QMap>
#include <tr1/memory>
#include <math.h>
#include <QFile>
#include <motion/orbitalmotion.h>
#include <common/asdcoordconvertor.h>
#include <common/asdtype.h>

#include "common/objfileparser.h"


class CalcPlan: public QObject
{
   Q_OBJECT
public:

	/*!
	 * \brief Конструктор по умолча

	 */
      explicit   CalcPlan(QObject* parent = 0);
     ~CalcPlan();


    void setfilName(QString sfil);
	/*!
	 * \brief Установка данных
	 * \param orbitalVehicle - орбитальные средства с координатами
	 * \param eathVehicle - наземное средства с координатами
	 * \param startTime - время начала операции
	 * \param endTime - время окончания операции
	 */
	void setDat(QVector<ASDOrbitalObjectPar> orbitalVehicle, QVector<
                        ParamGrBaseInter>eartVehicle,  QDateTime startTime,
			QDateTime endTime, int timestep);

	/*!
	 * \brief Расчет плана применения

	 * \return возращает план применения представляющий
	 * QMap<int, QMap<int, QVector<QVector<QDateTime> > > >, где первый int - номер КА, второй - номер средства
	 * QVector <QVector <QDateTime> > - список всех зoн видимости для выбранных средств
	 * QVector <QDateTime> представляет собой вектор состоящий из двух времен,
	 * времни входа и выхода из зоны наземного средства
	 */
	QMap<int, mapTime_plan> getPlan();

//   std::tr1::shared_ptr<CalcPlan> getptr()
//    {
//        return ptr;
//    }


        /*!
         * \brief Расчет плана применения

         * \return возращает план применения представляющий
         * QMap<int, QMap<int, QVector<QVector<QDateTime> > > >, где первый int - номер КА, второй - номер средства
         * QVector <QVector <QDateTime> > - список всех зoн видимости для выбранных средств
         * QVector <QDateTime> представляет собой вектор состоящий из двух времен,
         * времни входа и выхода из зоны наземного средства
         */
        QMap<int, mapTime_plan> getVizOrb();

        void getPlanf();
signals:

void progress(int);

protected:
	bool iszone(QDateTime curr_time, QVector<double> posOrb,
			QVector<double> param, QVector<double> posGBI);
        bool iszoneOrb(QDateTime curr_time, QVector<double> posOrb,
                        QVector<double> posOrbfirst);

        void SolarPosition(int doy, double hod, double& lat, double& lon);
        // восход заход Солнца
        void Sunrise(double lat, double lon, double ht, int doy, double& rise, double& sets);
        /*!
         * \brief Расчёт углового расстояния между двумя точками (географические координаты)
         * \param geo1 Первая точка
         * \param geo2 Вторая точка
         * \return Возвращаемое угловое расстояние, радиан
         */
        double geoDistance(const double lat1,const double lon1, const double lat2,const double lon2);

private:
       // std::tr1::shared_ptr<CalcPlan> ptr;
        // Q_DISABLE_COPY(CalcPlan);
	QVector<ASDOrbitalObjectPar> m_orbitalVehicle;
	QVector<ParamGrBaseInter> m_eathVehicle;
        QDateTime m_startTime;
	QDateTime m_endTime;
	int m_timestep;
	double ell;
    QString m_fil;
	t_plan search_AOS_LOS(QDateTime startTime, ASDOrbitalObjectPar posorb,
			ParamGrBaseInter posBGI, QDateTime aos, QDateTime los);
	QVector<double> toTPS(QDateTime curr_time, QVector<double> posOrb, QVector<
			double> posGBI);

	double toLGMST(double longitude, double jdat);
   //CalcPlan *  d_ptr;


};

#endif // CALCPLAN_H
