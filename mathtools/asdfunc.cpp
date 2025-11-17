/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdfunc.cpp.\n
 ** Описание: Файл содержит общие функции.\n
 ** Платформа: Независимо.\n
 ** Дата создания: 05.09.2014 г.\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#include "asdfunc.h"


QVector<double> cross(QVector<double>& l, QVector<double>& r)
{
	QVector<double> toReturn(3);

	if ((l.size() != 3) && (r.size() != 3))
	{
		//VectorException e("Cross product requires vectors of size 3");
		//throw(e);
		toReturn.resize(0);
		return toReturn;
	}

	toReturn[0] = l[1] * r[2] - l[2] * r[1];
	toReturn[1] = l[2] * r[0] - l[0] * r[2];
	toReturn[2] = l[0] * r[1] - l[1] * r[0];
	return toReturn;

}

QVector<double> normalize(QVector<double> l)
{
	double m = norm(l);
    QVector<double> t(l.size());

	for (int i = 0; i < l.size(); i++)

		t[i] /= m;
	return t;
}

double dot(QVector<double>& l, QVector<double>& r)
{

	double sum(0);
	size_t i, n = (l.size() > r.size() ? r.size() : l.size());
	for (i = 0; i < n; i++)
	{
		sum += l[i] * r[i];
	}
	return sum;

}

QVector<double> vecMinus(QVector<double> vec1, QVector<double> vec2)
{

	int i, n = (vec2.size() > vec1.size() ? vec1.size() : vec2.size());
	QVector<double> t(n);
	for (i = 0; i < n; i++)
        t[i] = vec1[i] - vec2[i];
	return t;

}

QVector<double> vecSum(QVector<double>& vec1, QVector<double>& vec2)
{

	int i, n = (vec2.size() > vec1.size() ? vec1.size() : vec2.size());
	QVector<double> t(n);
	for (i = 0; i < n; i++)
        t[i] = vec1[i] + vec2[i];
	return t;

}

double norm(QVector<double> v)
{

	double mag = 0.;
	if (v.size() == 0)
		return mag;
	mag = fabs(v[0]);
	for (int i = 1; i < v.size(); i++)
	{
		if (mag > fabs(v[i]))
			mag *= sqrt(1. + (v[i] / mag) * (v[i] / mag));
		else if (fabs(v[i]) > mag)
			mag = fabs(v[i]) * sqrt(1. + (mag / v[i]) * (mag / v[i]));
		else
			mag *= sqrt(2.);
	}
	return mag;

}

double cosGammaVec(const QVector<double> vec1, const QVector<double> vec2)
{

	double na = norm(vec1), nb = norm(vec2), c(0);
	int i, n = (vec2.size() > vec1.size() ? vec1.size() : vec2.size());
	for (i = 0; i < n; i++)
		c += (vec1[i] / na) * (vec2[i] / nb);
	return c;

}

QVector<double> sputnik_distance(const QVector<double>& pos,
		const double alpha, const double azimut)
{
	QVector<double> acoord(3);
	double b, c1, c2;
	double MEAN_RAD = 6371.;//средний радиус Земли
	b = pos[3] + MEAN_RAD;
	if (0 > teorCosC(MEAN_RAD, b, alpha, &c1, &c2))
		return acoord;
	double inner_distance = teorCosAlpha(MEAN_RAD, b, c1);
	acoord = findSecondCoord(pos, inner_distance, azimut);
	return acoord;
}

QVector<double> findSecondCoord(const QVector<double>& geo1, const double d,
		const double a)
{
	QVector<double> pos(2);
	double divider = cos(geo1[0]) * cos(d) - sin(geo1[0]) * sin(d) * cos(a);
	pos[0] = spAsin(sin(geo1[0]) * cos(d) + cos(geo1[0]) * sin(d) * cos(a));
	// pos(1) = PiToPi(atan2( sin(d)*sin(a), divider ) + geo1(1));//????? -PI PI
	pos[1] = (atan2(sin(d) * sin(a), divider) + geo1[1]);//????? 0 2PI
	return pos;
}

double spAsin(double x)
{
	if (x > 1.0)
		x = 1.0;
	if (x < -1.0)
		x = -1.0;

	return asin(x);
}

double spAcos(double x)
{
	if (x > 1.0)
		x = 1.0;
	if (x < -1.0)
		x = -1.0;

	return acos(x);
}

double teorCosA(double b, double c, double alpha)
{
	double a;
	a = b * b + c * c - 2. * b * c * cos(alpha);
	if (a < 0.)
		return -999999.;
	return sqrt(a);
}

double teorCosAlpha(double a, double b, double c)
{
	return spAcos((b * b + c * c - a * a) * 0.5 / (b * c));
}

int teorCosC(double a, double b, double alpha, double *c1, double *c2)
{
	double b1, c, d, x1, x2;
	b1 = -2. * b * cos(alpha);
	c = b * b - a * a;
	d = b * b - 4. * c;
	if (d > 0.)
	{
		x1 = (-b1 + sqrt(d)) * 0.5;
		x2 = (-b1 - sqrt(d)) * 0.5;
	}
	else
	{
		if (d < 0.)
		{
			return -1;
		}
		else
		{
			x1 = (-b1 + sqrt(d)) * 0.5;
			*c1 = x1;
			*c2 = x1;
			return 1;
		}
	}
	*c1 = x1 < x2 ? x1 : x2;
	*c2 = x1 < x2 ? x2 : x1;
	return 0;
}

QVector <double> flatKoef (QVector <float> coords)
{
    //переводим координаты в гринвичскую систему координат


    QVector <double> koef(4);
    koef[0] = coords[1]*coords[5] - coords[4]*coords[2];//A
    koef[1] = -(coords[0]*coords[5] - coords[3]*coords[2]);//B
    koef[2] = coords[0]*coords[4] - coords[3]*coords[1];//C
    koef[3] = 0;//D

    return koef;
}

double methodBisection(double x0, double x1, double (*F)(double), double delta)
{
    double F_;
    double x_;
    do
    {
        double F0 = F(x0);
        double F1 = F(x1);
        if(F1*F0 < 0)
        {
            x_ = (x0 + x1)/2.;
            F_ = F(x_);
            if(F0 * F_ < 0)
            {
                x1 = x_;
            }

            if(F1 * F_ < 0)
            {
                x0 = x_;
            }
        }
        else return 1000;
    }
    while (fabs(F_) > delta);

    return x_;

}
