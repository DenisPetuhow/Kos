/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: datum.cpp.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#include "asddatum.h"

//using namespace std;

CDatum::CDatum(const QString& n, const QString& d, const double& k1,
		const double& k2, const double& k3, const double& k4, const double& k5,
		const double& k6, const double& k70, const double& k71,
		const double& k72, const double& k80, const double& k81,
		const double& k82) :
	name(n), description(d), a(k1), f(1.0 / k2), m(k3), gm(k4), c(k5),
			omega(k6)
{
	// Установка размеров массивов
	delta.resize(3);
	epsilon.resize(3);

	// Установка параметров
	delta[0] = k70;
	delta[1] = k71;
	delta[2] = k72;

	epsilon[0] = k80;
	epsilon[1] = k81;
	epsilon[2] = k82;
}

//void CDatum::dump(std::ostream& s) const
//{
//	s << "CDatum code:             " << name << std::endl
//			<< "CDatum name:             " << description << std::endl
//			<< "Major axis:             " << a << std::endl
//			<< "Flattening (1/f):       " << f << std::endl
//			<< "Scale factor:           " << m << std::endl
//			<< "Gravitational constant: " << gm << std::endl
//			<< "Speed of light:         " << c << std::endl
//			<< "Angular velocity:       " << omega << std::endl
//			<< "Center traslation:      " << delta << std::endl
//			<< "Center rotation:        " << epsilon << std::endl;
//}

//std::ostream& operator<<(std::ostream& s, const CDatum& myCDatum)
//{
////	myCDatum.dump(s);
//	return s;
//}

