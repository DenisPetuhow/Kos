/**
 * @file SunPosition.hpp
 * Returns the approximate position of the Sun at the given epoch in the
 * ECEF system.
 */

#ifndef SUNPOSITION_HPP
#define SUNPOSITION_HPP

#include <cmath>
#include <string>
#include <QDateTime>
#include <QVector>

class SunPosition
{
public:

	/// Default constructor
	SunPosition()
	{
	}
	;

	/// Destructor
	virtual ~SunPosition()
	{
	}
	;

    /** Function to compute Sun position in CIS system (координаты в км) в АГЭСК.
	 *
	 * @param t Epoch
	 */
     QVector<double> getPosition(const QDateTime t);

     double getRightAscension();

private:
   double m_longitude_sun;//долгота солнца

   double m_inclin_sun;//средний наклон эклиптики к экватору Земли


}; // End of class 'SunPosition'

#endif
