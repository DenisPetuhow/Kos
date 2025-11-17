/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической\n
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdmobilezone.cpp.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#include "mobilezone.h"

ASDMobileZone& ASDMobileZone::setData(double gamma, double tangage, double yaw)
{
	m_gamma = gamma;
    m_tangage = tangage;
    m_yaw = yaw;
    m_type = konuas;
    return (*this);
}

ASDMobileZone &ASDMobileZone::setData(double deltaV, double deltaH, double tangage, double yaw, double roll)
{
    m_deltaV = deltaV;
    m_deltaH = deltaH;
    m_tangage = tangage;
    m_yaw = yaw;
    m_roll = roll;
    m_type = pyramid;
    return (*this);
}

ASDMobileZone& ASDMobileZone::setGamma(double gamma)
{
	m_gamma = gamma;
	return (*this);
}

ASDMobileZone& ASDMobileZone::setTangage(double tangage)
{
    m_tangage = tangage;
    return (*this);
}

ASDMobileZone &ASDMobileZone::setYaw(double yaw)
{
    m_yaw = yaw;
    return (*this);
}

ASDMobileZone& ASDMobileZone::setRoll(double roll)
{
    m_roll = roll;
	return (*this);
}


bool ASDMobileZone::isSpacecraftInZone(QVector<double> vehicle, QVector<double> target)
{
    QVector <double> O(3,0);
    double distance = ASDInterLocation::calculateDistance(vehicle,target);
    double r_vehicle = ASDInterLocation::calculateDistance(O,vehicle);
    double r_target = ASDInterLocation::calculateDistance(O,target);
    double angle_target = acos((distance*distance+r_vehicle*r_vehicle-r_target*r_target)/(2*distance*r_vehicle)); //угол между направлением на цель и центр Земли;
    double angle_earth = acos(R_EARTH/r_vehicle); //угол между направлением на центр Земли и косательной к Земле;
    if(angle_target<angle_earth)
        if(distance>pow(pow(r_vehicle,2)-pow(R_EARTH,2),0.5))
            return false; //цель находится за Землей



    if(m_type == konuas) //если зона обзора конус
    {

        QVector <double>  coord_ort_instr(3,0);
//Определение направления единичного орта, совпадающего с направлением оптической оси аппаратуры
        coord_ort_instr[0] = cos(m_tangage) * cos(m_yaw);
        coord_ort_instr[1] = sin(m_tangage) * cos(m_yaw);
        coord_ort_instr[2] = sin(m_yaw);

        QVector <double> coord_target_Opsc(6,0);

        coord_target_Opsc = ASDCoordConvertor::convAgescToOpscRelative(vehicle,target);
        double r_coord_target_Opsc = ASDInterLocation::calculateDistance(O,coord_target_Opsc);

        double angle = acos((coord_target_Opsc[0]*coord_ort_instr[0]+coord_target_Opsc[1]*coord_ort_instr[1]+coord_target_Opsc[2]*coord_ort_instr[2])/r_coord_target_Opsc);
        if(angle>m_gamma) return false;
        else return true;
    }

    if(m_type == pyramid)
    {

    }
    else return false;


}




bool ASDMobileZone::isEarthPointInZone(QVector<double> current, QVector<
        double> lla, QDateTime time)
{

	//Вспомогателная переменная
	double r;

	//Находим координаты точки на земной поверхности в прямоугольной (гринвичской) СК
    QVector<double> earthGrinvich(ASDCoordConvertor::convGeoToGsc(lla[0],lla[1],lla[2]));
    QVector<double> earthAGESC(ASDCoordConvertor::convGscToAgesc(earthGrinvich,time));
	//Рассчитываем расстояние от КА до центра Земли
    double rE = ASDInterLocation::calculateDistance(current, QVector<double> (3, 0.0));
	//Рассчитываем расстояние от КА до точки на поверхности Земли
    double rP = ASDInterLocation::calculateDistance(current, earthAGESC);

    if (rP > sqrt(rE*rE-R_EARTH*R_EARTH))
        return false;
    if(m_type == konuas) //если зона обзора конус
{
    QVector<double>  viewDirectionNormalIsc(3,0);
    QVector<double>  earthDirectionNormal(3,0);
	//Задаем единичный вектор направлення зоны обзора в орбитальной подвижной СК
    viewDirectionNormalIsc[0] = cos(m_yaw) * cos(m_tangage);
    viewDirectionNormalIsc[1] = sin(m_yaw) * cos(m_tangage);
    viewDirectionNormalIsc[2] = sin(m_tangage);

	//Находим единичный вектор направления на точку земной поверхности в гринвичской СК

	//Координаты точки на земной поверхности переводим в орбитальную подвижную СК

    QVector<double> earthOSCRelative(ASDCoordConvertor::convAgescToOpscRelative(current, earthAGESC));
    QVector<double> earthIsc(ASDCoordConvertor::convOpscToIsc(rE,earthOSCRelative));

	//Находим единичный вектор направления на точку в орбитальной подвижной СК
    r = sqrt(pow(earthIsc[0], 2.0) + pow(earthIsc[1], 2.0) + pow(earthIsc[2], 2.0));

	for (int i = 0; i < 3; i++)
        earthDirectionNormal[i] = earthIsc[i] / r;

	//Расчет косинуса угла между направлением найденных единичных векторов
    double angleNP = acos(viewDirectionNormalIsc[0] * earthDirectionNormal[0]
            + viewDirectionNormalIsc[1] * earthDirectionNormal[1]
            + viewDirectionNormalIsc[2] * earthDirectionNormal[2]);
	//Сравниваем с косинусом угла полураствора
    //Если косинус угла полураствора больше или равен найденному, точка попадает в зону обзора СОМНИТЕЛЬНО!!!!
    if (m_gamma >= angleNP)
		return true;
	else
		return false;
    }

    if(m_type == pyramid)
    {
        ASDAngleMounting angle;
        angle.pitch = m_tangage;
        angle.yaw = m_yaw;
        angle.roll = m_roll;
        QVector<double> earthOSCRelative(ASDCoordConvertor::convAgescToOpscRelative(current, earthAGESC));
        QVector<double> earthIsc(ASDCoordConvertor::convOpscToIsc(rE,earthOSCRelative));
        QVector<double> earthConSc(ASDCoordConvertor::convIscToConSc(earthIsc,angle));
        double deltaV, deltaH;
        deltaV = atan(earthConSc[1]/earthConSc[0]);
        deltaH = atan(earthConSc[2]/earthConSc[0]);
        if((fabs(deltaV)>m_deltaV) ||(fabs(deltaH)>m_deltaH))
            return false;
        else
            return true;

    }

}

