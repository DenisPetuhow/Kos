/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdoverlandvehicle.cpp.\n
 ** Описание: Содержит класс наземного средства.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 01.01.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#include "overlandvehicle.h"

//#include "../libmath/libmodk_constants.hpp"

ASDOverlandVehicle::ASDOverlandVehicle(double latitude, double longitude,
		double altitude, double gamma, double azimuth, double elevation) :
	m_LLA(3, 0.0), m_zone(gamma, azimuth, elevation)
{
	m_LLA[0] = latitude;
	m_LLA[1] = longitude;
	m_LLA[2] = altitude;
}

/**************************************************************************************************/

ASDOverlandVehicle& ASDOverlandVehicle::operator=(ASDOverlandVehicle right)
{
	setLLA(right.getLLA());
	setZone(right.getZone());

	return (*this);
}

/**************************************************************************************************/

ASDOverlandVehicle& ASDOverlandVehicle::setData(const double& lat,
		const double& lon, const double& alt, const double& gamma,
		const double& azimuth, const double& elevation)
{
	m_LLA[0] = lat;
	m_LLA[1] = lon;
	m_LLA[2] = alt;
	m_zone.setData(gamma, azimuth, elevation);

	return (*this);
}

/**************************************************************************************************/

ASDOverlandVehicle& ASDOverlandVehicle::setLLA(const double& lat,
		const double& lon, const double& alt)
{
	m_LLA[0] = lat;
	m_LLA[1] = lon;
	m_LLA[2] = alt;

	return (*this);
}

/**************************************************************************************************/

ASDOverlandVehicle& ASDOverlandVehicle::setLLA(const QVector<double>& LLA)
{
	m_LLA[0] = LLA[0];
	m_LLA[1] = LLA[1];
	m_LLA[2] = LLA[2];

	return (*this);
}

/**************************************************************************************************/
ASDOverlandVehicle& ASDOverlandVehicle::setZone(const ASDStillZone& zone)
{
	m_zone.setData(zone.getAzimuth(), zone.getElevation(), zone.getGamma());

	return (*this);
}

/**************************************************************************************************/

bool ASDOverlandVehicle::isSpacecraftInZone(QVector<double> targetGSC)
{
	return m_zone.isSpacecraftInZone(m_LLA, targetGSC);
}

