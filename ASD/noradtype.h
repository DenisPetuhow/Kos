/*!
 ******************************************************************************
 ** \file
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdnoradtype.h.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/
#ifndef ASDNORADTYPE_H
#define ASDNORADTYPE_H
#include <math.h>
#include <cmath>
/*************************************************************************
 * КОНСТАНТЫ ДЛЯ МОДЕЛИ NORAD
 *************************************************************************/

#define TWO_THRD     ( 2.0/3.0)
#define XKE   7.43669161E-2
#define CK2   5.413079E-4  //!< Вторая гармоника гравитационного поля Земли (WGS '72)
#define CK4   6.209887E-7  //!< Четвертая гармоника гравитационного поля Земли (WGS '72)
#define XJ3   -2.53881E-6  //!< Третья гармоника гравитационного поля Земли (WGS '72)
const double zns = 1.19459E-5;
const double c1ss = 2.9864797E-6;
const double zes = 0.01675;
const double znl = 1.5835218E-4;
const double c1l = 4.7968065E-7;
const double zel = 0.05490;
const double zcosis = 0.91744867;
const double zsinis = 0.39785416;
const double zsings = -0.98088458;
const double zcosgs = 0.1945905;
const double q22 = 1.7891679E-6;
const double q31 = 2.1460748E-6;
const double q33 = 2.2123015E-7;
const double g22 = 5.7686396;
const double g32 = 0.95240898;
const double g44 = 1.8014998;
const double g52 = 1.0508330;
const double g54 = 4.4108898;
const double root22 = 1.7891679E-6;
const double root32 = 3.7393792E-7;
const double root44 = 7.3636953E-9;
const double root52 = 1.1428639E-7;
const double root54 = 2.1765803E-9;
const double thdt = 4.3752691E-3;
const double EQUATOR_RAD = 6378.137;//!< Экваториальный радиус Земли - km (WGS '84)
const double AE = 1.0;

#define sqr(x) (x*x)
#define FromJan1_12h_2000  2451545.0
#define EPOCH_JAN0_12H_1900 2415020.0
/*!
 * \brief Вычисление юлианской эпохи
 *
 * \param year - год.
 * \param day - эпоха (день года и дробная часть дня).
 */
inline double Jd(int year, double day)
{

	double temp = 0.;

	year--;

	int A = (year / 100);
	int B = 2 - A + (A / 4);

	double NewYears = (int) (365.25 * year) + (int) (30.6001 * 14) + 1720994.5
			+ B; // 1720994.5 = Oct 30, year -1

	temp = NewYears + day;
	return temp;

}
/*!
 * \brief Преобразование Юлианской даты в гринвичевское сиредическое время (GMST).
 *
 * \param jdat - юлианская эпоха.
 * \return гринвичевское сиредическое время, в радианах (Theta GMST).
 */
inline double ToGmst(double jdat)
{
	const double UT = fmod(jdat + 0.5, 1.0);
	const double TU = (2451545.0 - UT) / 36525.0;

	double GMST = 24110.54841 + TU * (8640184.812866 + TU * (0.093104 - TU
			* 6.2e-06));

	GMST = fmod(GMST + 86400.0 * 1.00273790934 * UT, 86400.0);

	if (GMST < 0.0)
		GMST += 86400.0;

	return (2. * M_PI * (GMST / 86400.0));
}
/*!
 * \brief Преобразование значения в дапазон от 0 до 2 PI
 */

inline double fmod2p(double x)
{
	double modu = fmod(x, M_PI * 2.);

	if (modu < 0.0)
		modu += M_PI * 2.;

	return modu;
}

#endif // NORADCONST_H
