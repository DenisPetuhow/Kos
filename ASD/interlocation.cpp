/******************************************************************************
 ** Название: Комплекс программных средств моделирования применения сил и средств ВКО.\n
 ** Разработчик: Военный институт (научно-исследовательский) Военно-космической
 ** академии имени А.Ф.Можайского.\n
 ** Файл: asdinterlocation.cpp.\n
 ** Описание:\n
 ** Платформа: Независимо.\n
 ** Дата создания:\n
 ** История:\n
 ** Проверено: Windows 7, Ubuntu 13.04.\n
 ** Замечания:\n
 **
 **
 *****************************************************************************/

#include "interlocation.h"

//bool ASDInterLocation::dump(ostream& s) const
//{
//	QVector<double> LLA(3, 0.0);
//	LLA = getLLA();
//	s << "Position in XYZ data:" << endl << endl << "X: " << m_xyz(0)
//			<< endl << "Y: " << m_xyz(1) << endl << "Z: " << m_xyz(2)
//			<< endl << endl << "Position in LLA data:" << endl
//			<< endl << "Latitude:  " << LLA(0) << endl
//			<< "Longitude: " << LLA(1) << endl << "Altitude:  " << LLA(2)
//			<< endl << "\nDatum used:\n" << m_currentDatum << endl;
//	return true;
//}

//ostream& operator<<(ostream& s, const ASDInterLocation& myPosition)
//{
//	myPosition.dump(s);
//	return s;
//}

ASDInterLocation::ASDInterLocation(const double& rx, const double& ry,
		const double& rz, const CDatum& c_dat) :
	m_currentDatum(c_dat)
{
	// Установка размера вектора r
	m_xyz.resize(3);

	// Устаовка параметров
	m_xyz[0] = rx;
	m_xyz[1] = ry;
	m_xyz[2] = rz;
}

ASDInterLocation ASDInterLocation::operator+(ASDInterLocation right) const
{
	// Устанавливаем единый датум для обоих положений
	right.setDatum(m_currentDatum);

	// Вычисление суммы позиций
	right.setXYZ(((*this).getXYZ() + right.getXYZ()));
	return right;
}

ASDInterLocation ASDInterLocation::operator-(ASDInterLocation right) const
{
	// Устанавливаем единый датум для обоих положений
	right.setDatum(m_currentDatum);

	// Вычисление разницы позиций
	right.setXYZ(vecMinus((*this).getXYZ(), right.getXYZ()));
	return right;
}

ASDInterLocation& ASDInterLocation::operator=(ASDInterLocation right)
{
	m_currentDatum = right.getDatum();
	m_xyz = right.getXYZ();

	return (*this);
}

bool ASDInterLocation::operator==(ASDInterLocation right) const
{
	// Впеменный вектор
	QVector<double> temp(3, 0.0);
	// Ошибка в метрах для компонент XYZ, 5 см по умолчанию
	const double err(0.05);
	// По умолчанию возвращаем true
	bool to_return(true);

	// Для сравнения приводим к одному датуму
	right.setDatum(m_currentDatum);
	temp = right.getXYZ();

	// Если разницаменьше погрешности, возвращаем true, иначе false
	for (int i = 0; i < 3; i++)
	{
		if ((m_xyz[i] >= (temp[i] - err)) && (m_xyz[i] <= (temp[i] + err)))
		{
			to_return = true;
		}
		else
		{
			to_return = false;
		}

		if (to_return == false)
		{
			return to_return;
		}
	}

	return to_return;
}

ASDInterLocation& ASDInterLocation::setXYZ(const double& rx,
		const double& ry, const double& rz, const CDatum& n_dat)
{
	QVector<double> temporal(3, 0.0);
	temporal[0] = rx;
	temporal[1] = ry;
	temporal[2] = rz;

	return ((*this).setXYZ(temporal, n_dat));
}

ASDInterLocation& ASDInterLocation::setXYZ(const QVector<double>& vect,
		const CDatum& n_dat)
{
	if (vect.size() == 3)
	{
		m_xyz[0] = vect[0];
		m_xyz[1] = vect[1];
		m_xyz[2] = vect[2];
		m_currentDatum = n_dat;
	}
	return (*this);
}

ASDInterLocation& ASDInterLocation::setLLA(const QVector<double>& LLA,
		const CDatum& n_dat)
{
	double X, Y, Z;
	double N;

	// Назначение используемого датума
	m_currentDatum = n_dat;

	// Получение радиуса кривизны для текущих высоты и датума
	N = getN(LLA[0]);

	// Переход от широты, долготы и высоты к координатам XYZ
	double cosLLA0(cos(LLA[0] * DEG_TO_RAD));
	X = (N + LLA[2]) * cosLLA0 * cos(LLA[1] * DEG_TO_RAD);
	Y = (N + LLA[2]) * cosLLA0 * sin(LLA[1] * DEG_TO_RAD);
	double a(m_currentDatum.get_a());
	double b(m_currentDatum.get_b());
	Z = ((((b * b) / (a * a)) * N) + LLA[2]) * sin(LLA[0] * DEG_TO_RAD);

	// Записываем полученные значения
	m_xyz[0] = X;
	m_xyz[1] = Y;
	m_xyz[2] = Z;

	return (*this);

}

ASDInterLocation& ASDInterLocation::setLLA(const double& lat,
		const double& lon, const double& alt, const CDatum& n_dat)
{
	QVector<double> LLA(3, 0.0);
	LLA[0] = lat;
	LLA[1] = lon;
	LLA[2] = alt;

	return ((*this).setLLA(LLA, n_dat));
}

ASDInterLocation& ASDInterLocation::setX(const double& x)
{
	m_xyz[0] = x;
	return (*this);
}

ASDInterLocation& ASDInterLocation::setY(const double& y)
{
	m_xyz[1] = y;
	return (*this);
}

ASDInterLocation& ASDInterLocation::setZ(const double& z)
{
	m_xyz[2] = z;
	return (*this);
}

ASDInterLocation& ASDInterLocation::setDatum(const CDatum& n_dat)
{
	QVector<double> n_epsilon(3);
	QVector<double> c_epsilon(3);
	ASDMatrix3x3 n_Rot;
	ASDMatrix3x3 c_Inv_Rot;

	c_epsilon = m_currentDatum.get_epsilon(); // Поворот текущего датума
	n_epsilon = n_dat.get_epsilon(); // Поворот нового датума

	//Задание матрицы вращения для нового датума
	n_Rot(0, 0) = 1.0;
	n_Rot(0, 1) = n_epsilon[2];
	n_Rot(0, 2) = -n_epsilon[1];
	n_Rot(1, 0) = -n_epsilon[2];
	n_Rot(1, 1) = 1.0;
	n_Rot(1, 2) = n_epsilon[0];
	n_Rot(2, 0) = n_epsilon[1];
	n_Rot(2, 1) = -n_epsilon[0];
	n_Rot(2, 2) = 1.0;

	// Задание матрицы вращения для текущего датума
	c_Inv_Rot(0, 0) = 1.0;
	c_Inv_Rot(0, 1) = c_epsilon[2];
	c_Inv_Rot(0, 2) = -c_epsilon[1];
	c_Inv_Rot(1, 0) = -c_epsilon[2];
	c_Inv_Rot(1, 1) = 1.0;
	c_Inv_Rot(1, 2) = c_epsilon[0];
	c_Inv_Rot(2, 0) = c_epsilon[1];
	c_Inv_Rot(2, 1) = -c_epsilon[0];
	c_Inv_Rot(2, 2) = 1.0;

	// Получение обратной матрицы для матрицы вращения текущего датума
    //if ((c_epsilon[0] == c_epsilon[1] == c_epsilon[2]) != 0)
 //   c_Inv_Rot.inverse(c_Inv_Rot);

	// Уравнение преобразования датума

	QVector<double> t_t = vecMinus(m_xyz, c_Inv_Rot * m_currentDatum.get_delta());
	double t_w = (1.0 + n_dat.get_m()) / (1.0- m_currentDatum.get_m());
	ASDMatrix3x3 t_e = n_Rot * t_w;


	m_xyz = n_dat.get_delta() + t_e * t_t;

	// Присвоение значения датума
	m_currentDatum = n_dat;
	return (*this);
}

ASDInterLocation& ASDInterLocation::rotateX(const double& beta)
{
	double temp;
	ASDMatrix3x3 R1;
	QVector<double> pos(3, 0.0);

	// Переход от градусов к радианам
    temp = beta;

	// задание матрицы R1
	R1(0, 0) = 1.0;
	R1(0, 1) = 0.0;
	R1(0, 2) = 0.0;
	R1(1, 0) = 0.0;
	R1(1, 1) = cos(temp);
	R1(1, 2) = sin(temp);
	R1(2, 0) = 0.0;
	R1(2, 1) = -sin(temp);
	R1(2, 2) = cos(temp);

	// Вычисление нового положения
	m_xyz = R1 * m_xyz;

	return (*this);
}

ASDInterLocation& ASDInterLocation::rotateY(const double& beta)
{
	double temp;
	ASDMatrix3x3 R2;
	QVector<double> pos(3, 0.0);

    temp = beta;

	R2(0, 0) = cos(temp);
	R2(0, 1) = 0.0;
	R2(0, 2) = -sin(temp);
	R2(1, 0) = 0.0;
	R2(1, 1) = 1.0;
	R2(1, 2) = 0.0;
	R2(2, 0) = sin(temp);
	R2(2, 1) = 0.0;
	R2(2, 2) = cos(temp);

	m_xyz = R2 * m_xyz;

	return (*this);
}

ASDInterLocation& ASDInterLocation::rotateZ(const double& beta)
{
	double temp;
	ASDMatrix3x3 R3;

    temp = beta;

	R3(0, 0) = cos(temp);
	R3(0, 1) = sin(temp);
	R3(0, 2) = 0.0;
	R3(1, 0) = -sin(temp);
	R3(1, 1) = cos(temp);
	R3(1, 2) = 0.0;
	R3(2, 0) = 0.0;
	R3(2, 1) = 0.0;
	R3(2, 2) = 1.0;

	m_xyz = R3 * m_xyz;

	return (*this);
}

ASDInterLocation& ASDInterLocation::reflectX()
{
	ASDMatrix3x3 S1;

	// Задание матрицы отражения
	S1(0, 0) = -1.0;
	S1(1, 1) = 1.0;
	S1(2, 2) = 1.0;

	m_xyz = S1 * m_xyz;

	return (*this);
}

ASDInterLocation& ASDInterLocation::reflectY()
{
	ASDMatrix3x3 S2;

	S2(0, 0) = 1.0;
	S2(1, 1) = -1.0;
	S2(2, 2) = 1.0;

	m_xyz = S2 * m_xyz;

	return (*this);
}

ASDInterLocation& ASDInterLocation::reflectZ()
{
	ASDMatrix3x3 S3;

	S3(0, 0) = 1.0;
	S3(1, 1) = 1.0;
	S3(2, 2) = -1.0;

	m_xyz = S3 * m_xyz;

	return (*this);
}

QVector<double> ASDInterLocation::getLLA() const
{
	QVector<double> LLA(3, 0.0); // Возвращаемый вектор
	double lon, lat, alt; // Долгота, широта и высота
	double p;
	double N;
	double alt0;
	double e2(m_currentDatum.get_e() * m_currentDatum.get_e());

	// Вычисление долготы и вспомогательной переменной p
	lon = atan2(m_xyz[1], m_xyz[0]);
	p = sqrt(m_xyz[0] * m_xyz[0] + m_xyz[1] * m_xyz[1]);

	// Первое приближение широты
	lat = atan(m_xyz[2] / (p * (1.0 - e2)));
	alt = 0.0;

	// Вычисление широты и высоты итерационным методом
	alt0 = 1.0;
	while (fabs(alt0 - alt) > 0.0001)
	{
        N = getN(lat);
		alt0 = alt;
		alt = (p / cos(lat)) - N;
		lat = atan(m_xyz[2] / (p * (1.0 - (e2 * (N / (N + alt))))));
	}

	// Запись вычисленных значений
    LLA[0] = lat;
    LLA[1] = lon;
	LLA[2] = alt;

	return LLA;
}

QVector<double> ASDInterLocation::getDistance(const ASDInterLocation& pos) const
{

	// Auxiliar parameters
	bool i(false);
	double F, G, lambda, S, C, omega;
	double r1, D, H1, H2;

    double dist; // Расстояние в километрах
	double e_dist; // Оценка ошибки
	QVector<double> to_return(2, 0.0);

	ASDInterLocation n_pos;
	QVector<double> c_LLA; // LLA для текущей позиции 'r'
	QVector<double> pos_LLA; // LLA для позиции 'pos'

	double f(m_currentDatum.get_f());

	// Создании копии передаваемого параметра
	n_pos = pos;

	// Приводим к единому датуму
	n_pos.setDatum(m_currentDatum);
	// Поучаем вектор LLA
	c_LLA = getLLA();
	pos_LLA = n_pos.getLLA();

	// Если оба положения одинаковы, возвращаем расстояние 0.0 и ошибку
	// 0.087 (0.05 метра для каждой оси).
	if (*this == n_pos)
	{
		to_return[0] = 0.0;
		to_return[1] = 0.087;
		return (to_return);
	}
	else
	{
		// При вычислении расстояния между двумя полюсами возникает ошибка
		// Во избежание этого, вычисляем расстояние от одного полюса до экватора
		// и умножаем полученное значение на 2
		if ((c_LLA[0] + pos_LLA[0] == 0.0) && (fabs(c_LLA[0] - pos_LLA[0])
                == M_PI))
		{
			pos_LLA[0] = 0.0;
			i = true;
		}

        F = (c_LLA[0] + pos_LLA[0]) / 2.0;
        G = (c_LLA[0] - pos_LLA[0] ) / 2.0;
        lambda = (c_LLA[1] - pos_LLA[1]) / 2.0;

		double sinG(sin(G));
		double sinG2(sinG * sinG);
		double cosG(cos(G));
		double cosG2(cosG * cosG);
		double sinLambda(sin(lambda));
		double sinLambda2(sinLambda * sinLambda);
		double cosLambda(cos(lambda));
		double cosLambda2(cosLambda * cosLambda);
		double sinF(sin(F));
		double sinF2(sinF * sinF);
		double cosF(cos(F));
		double cosF2(cosF * cosF);

		S = sinG2 * cosLambda2 + cosF2 * sinLambda2;
		C = cosG2 * cosLambda2 + sinF2 * sinLambda2;
		omega = atan(sqrt(S / C));
		r1 = (sqrt(S * C)) / omega;
        D = 2.0 * omega * (m_currentDatum.get_a());
		H1 = ((3.0 * r1) - 1.0) / (2.0 * C);
		H2 = ((3.0 * r1) + 1.0) / (2.0 * S);

		dist = D * (1.0 + f * (H1 * sinF2 * cosG2 - H2 * cosF2 * sinG2));

		// Если вычислялось расстояние между полюсами, умножаем полученное значение на 2
		if (i == true)
		{
			dist = dist * 2.0;
		}

		// Вычисляем оценку погрешности
		e_dist = dist * f * f;

		// Возвращаем полученные значения
		to_return[0] = dist; // Расстояние в метрах
		to_return[1] = e_dist; // Оценка погрешности
		return (to_return);
	}
}

double ASDInterLocation::getN(const double& lat) const
{
	double N;
    double temp(m_currentDatum.get_e() * sin(lat));

	N = m_currentDatum.get_a() / (sqrt(1.0 - (temp * temp)));

	return N;
}

double ASDInterLocation::getStraightHoriz() const
{
    // Средний радиус Земли, километров
    double r1(6367.444657);

	QVector<double> LLA(3, 0.0);
	LLA = getLLA();

	// Возвращаем расстояние в метрах
	return (sqrt(LLA[2] * (2.0 * r1 + LLA[2])));
}

double ASDInterLocation::getCurveHoriz() const
{
    double r1(6367.444657);
	QVector<double> LLA(3, 0.0);

	LLA = getLLA();
	return (r1 * acos(r1 / (r1 + LLA[2])));
}

QVector<double> ASDInterLocation::fromECEFtoNEU(
		const ASDInterLocation& pos) const
{
	// Создание копии во избежание модификации
	ASDInterLocation Temp(pos);

	// Создание вектора с параметрами LLA
	QVector<double> LLA((*this).getLLA());

	// Приведение к единому датуму
	Temp.setDatum(m_currentDatum);

	// Записываем положение заданной точки относительно текущей
	Temp = Temp - (*this);

	// Переводим относительное положение в систему North-East-Down,
	// используя поворот и отражение
	Temp.rotateZ(LLA[1]);
    Temp.rotateY((-LLA[0] - M_PI/2.));
	Temp.reflectZ();

	// Возвращаем относительное положение
	return (Temp.getXYZ());
}

double ASDInterLocation::getElevation(const ASDInterLocation& pos) const
{
	// 'Вектор обзора' (север - восток - вверх)
	QVector<double> NEU((*this).fromECEFtoNEU(pos));

	double elevation; // Возвышение в градусах

	// Проверка, не выполняется ли условие,
	// что вектор север-восток намного меньше вектора вверх
	// Если условие выполняется, возвышение будет 90 или -90, в зависимости от знака
	if (sqrt(NEU[0] * NEU[0] + NEU[1] * NEU[1]) < (0.000000001 * NEU[2]))
	{
		if (NEU[2] > 0.0)
		{
            return (M_PI/2.);
		}
		else
		{
            return (-M_PI/2.);
		}
	}
	else
	{
		elevation = asin(NEU[2] / (sqrt(NEU[0] * NEU[0] + NEU[1]
				* NEU[1] + NEU[2] * NEU[2])));
        return (elevation);
	}
}

double ASDInterLocation::getAzimuth(const ASDInterLocation& pos) const
{
	// 'Вектор обзора' (север - восток - вверх)
	QVector<double> NEU((*this).fromECEFtoNEU(pos));
	// Если возвышение +/- 90 градусов, азимут не определен.
	// В этом случае возвращается значение 0.0.
    if (getElevation(pos) == (M_PI/2.) || getElevation(pos) == (-M_PI/2.))
	{
		return (0.0);
	}

	// Возвращается азимут в градусах.
    double azimuth(atan2(NEU[1], NEU[0]));
	if (azimuth < 0.0)
	{
        return azimuth + 2*M_PI;
	}
	else
	{
		return azimuth;
	}
}

double ASDInterLocation::getDot(const ASDInterLocation& b) const
{
	ASDInterLocation n_a, n_b;
	QVector<double> r_b(3, 0.0);
	double result = 0.0;
	int i;

	n_b = b;
	n_b.setDatum(m_currentDatum);
	r_b = n_b.getXYZ();

	for (i = 0; i < 3; i++)
	{
		result += m_xyz[i] * r_b[i];
	}

	return result;
}

double ASDInterLocation::calculateDistance(QVector<double> a,
		QVector<double> b)
{
	double result = 0.0;
	int i;

	for (i = 0; i < 3; i++)
	{
		result += pow(a[i] - b[i], 2.0);
	}

	return sqrt(result);
}

QVector<double> ASDInterLocation::calculateDirectionNormal(
		QVector<double> currentGrinvich, QVector<double> targetGrinvich)
{
	QVector<double> directionNormal(6, 0.0); //Возвращаемое значение
	QVector<double> currentGSC(6, 0.0); //Координаты первой точки в геоцентрической СК
	QVector<double> targetGSC(6, 0.0); //Координаты второй точки в геоцентрической СК

	// Пересчет координат из гринвичской СК в геоцентрическую
	currentGSC[0] = sqrt(currentGrinvich[0] * currentGrinvich[0] + //радиус-вектор
			currentGrinvich[1] * currentGrinvich[1] + currentGrinvich[2]
			* currentGrinvich[2]);
	currentGSC[1] = atan(currentGrinvich[1] / currentGrinvich[0]); //долгота
	currentGSC[2] = asin(currentGrinvich[2] / currentGSC[0]); //широта

	targetGSC[0] = sqrt(targetGrinvich[0] * targetGrinvich[0] + //радиус-вектор
			targetGrinvich[1] * targetGrinvich[1] + targetGrinvich[2]
			* targetGrinvich[2]);
	targetGSC[1] = atan(targetGrinvich[1] / targetGrinvich[0]); //долгота
	targetGSC[2] = asin(targetGrinvich[2] / targetGSC[0]); //широта

	//Расчет координат единичного вектора
	double r = sqrt(pow(targetGrinvich[0] - currentGrinvich[0], 2.0)
			+ pow(targetGrinvich[1] - currentGrinvich[1], 2.0) + pow(
			targetGrinvich[2] - currentGrinvich[2], 2.0));
	directionNormal[0] = (targetGSC[0] * cos(targetGSC[1]) * cos(
			targetGSC[2]) - currentGSC[0] * cos(currentGSC[1]) * cos(
			currentGSC[2])) / r;
	directionNormal[1] = (targetGSC[0] * sin(targetGSC[1]) * cos(
			targetGSC[2]) - currentGSC[0] * sin(currentGSC[1]) * cos(
			currentGSC[2])) / r;
	directionNormal[2] = (targetGSC[0] * sin(targetGSC[2]) - currentGSC[0]
			* sin(currentGSC[2])) / r;

    return directionNormal;
}

ASDCoordSphere ASDInterLocation::calcSphereCoord(QVector<double> coordVehicle, QVector<double> coordTarget)
{

    ASDCoordSphere angle;
    QVector <double> coord_target_rel;
    coord_target_rel = ASDCoordConvertor::convAgescToOpscRelative(coordVehicle,coordTarget);

    double r_Vehicle = pow(pow(coordVehicle[0],2)+ pow(coordVehicle[1],2)+pow(coordVehicle[2],2),0.5);
    coord_target_rel[0] -=r_Vehicle;
    double r_Target = pow(pow(coord_target_rel[0],2)+ pow(coord_target_rel[1],2)+pow(coord_target_rel[2],2),0.5);
    double r1 = pow(pow(coord_target_rel[0],2)+ pow(coord_target_rel[1],2),0.5);

    angle.azimuth = asin(coord_target_rel[2]/r_Target); //как широта ( от плоскоти орбиты)

    angle.elevation = ASDCoordConvertor::angle(coord_target_rel[1]/r1,-coord_target_rel[0]/r1);//от -90 до 90 от отрицательного направления оси х

    angle.distance = pow(pow(coord_target_rel[0],2)+pow(coord_target_rel[1],2)+pow(coord_target_rel[2],2),0.5);

   return angle;
}

QVector <double> ASDInterLocation::calcInterLineWithEarth(QVector<double> coord0,QVector<double> coord1)
{
    double A, B, C, D, K, A1, B1, C1, A_, B_;
    QVector <double> coord_reg1(3),coord_reg2(3), coord_reg_geo, coord_reg_agsk;
    double rro=R_EARTH;
    double r_p1;
    double X[2], r1, r2;

mm:   A = (coord1[0]-coord0[0])/(coord1[1]-coord0[1]);
    B = (coord1[2]-coord0[2])/(coord1[1]-coord0[1]);
    C = A*A + B*B;
    D = 2*A*coord0[0]+2*B*coord0[2];
    K = coord0[0]*coord0[0] + coord0[2]*coord0[2];
    A1 = C+1;
    B1 = D - 2*C*coord0[1];
    C1 = C*coord0[1]*coord0[1]-D*coord0[1]+K - rro*rro;
    A_ = B1/A1;
    B_ = C1/A1;


    int temp;
    if (B_==0)
    {
        X[0] = -A_;
        X[1] = 0.;
        temp=2;
    }
    else
    {
        A_ *= -0.5;
        double d = A_ * A_ - B_;
        if ( d < 0 )
            temp = 0;
        else
        {
            d = sqrt ( d );
            X[0] = A_ > 0 ? A_ + d : A_ - d;
            X[1] = B_ / X[0];
            temp = 2;
        }

    }

    if(temp ==2)
    {
        coord_reg1[1] = X[0];
        coord_reg2[1] = X[1];

        coord_reg1[0] = A*(coord_reg1[1]-coord0[1])+coord0[0];
        coord_reg1[2] = B*(coord_reg1[1]-coord0[1])+coord0[2];

        coord_reg2[0] = A*(coord_reg2[1]-coord0[1])+coord0[0];
        coord_reg2[2] = B*(coord_reg2[1]-coord0[1])+coord0[2];

        r1 = pow(pow(coord_reg1[0]-coord0[0],2)+pow(coord_reg1[1]-coord0[1],2)+pow(coord_reg1[2]-coord0[2],2),0.5);
        r2 = pow(pow(coord_reg2[0]-coord0[0],2)+pow(coord_reg2[1]-coord0[1],2)+pow(coord_reg2[2]-coord0[2],2),0.5);
        r_p1 = pow(pow(coord_reg1[0],2)+pow(coord_reg1[1],2)+pow(coord_reg1[2],2),0.5);

        if(r2>r1)
        {
            coord_reg_agsk = coord_reg1;
        }
        else
        {
            coord_reg_agsk = coord_reg2;
        }
        return coord_reg_agsk;
    }
    else
    {
        rro+=20.;
        goto mm;

    }

}

QVector<double> degreesToDMS(const double angle)
{
	// Будет возвращаться вектор (градусы, минуты, секунды)
	QVector<double> to_return(3, 0.0);

	// Проверка равенства угла 0.0
	if (fabs(angle) != 0.0)
	{
		// Работаем с положительными значениями
		double ang(fabs(angle));
		// Сохраняем знак: +1.0 или -1.0
		double sign(angle / ang);

		// Используем фунцию fmod, вычисляющую остаток от деления
		double remainder(fmod(ang, 1.0));
		to_return[0] = ang - remainder; // Градусы

		double minutes(remainder * 60.0);
		remainder = fmod(minutes, 1.0);
		to_return[1] = minutes - remainder; // Минуты
		to_return[2] = remainder * 60.0; // Секунды

		// Присвоение знака
		if (sign < 0.0)
		{
			if (to_return[0] > 0.0)
			{
				to_return[0] = -to_return[0]; // Asign sign to degrees
			}
			else
			{
				if (to_return[1] > 0.0)
				{
					to_return[1] = -to_return[1]; // Asign sign to minutes
				}
				else
				{
					to_return[2] = -to_return[2]; // Asign sign to seconds
				}
			}
		}
	}

	return to_return;
}

