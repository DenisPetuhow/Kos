
#include "SunPosition.hpp"



   QVector<double> SunPosition::getPosition(const QDateTime t)
   {
       /// Astronomical Unit value (AU), in meters
    const double AU_CONST(1.49597870e11);

       /// Mean Earth-Moon barycenter (EMB) distance (AU)
    const double MeanEarthMoonBary(3.12e-5);
         // Compute the years, and fraction of year, pased since J1900.0
       int y = t.date().year();    // Current year
      int doy = t.date().dayOfYear();   // Day of current year
      double fd = (t.time().second()+t.time().minute()*60+t.time().hour()*3600)/86400.0;   // Fraction of day
      int years( (y - 1900) );    // Integer number of years since J1900.0
      int iy4( ( ((y%4)+4)%4 ) ); // Is it a leap year?

         // Compute fraction of year
      double yearfrac = ( ( static_cast<double>(4*(doy-1/(iy4+1))
                            - iy4 - 2) + 4.0 * fd ) / 1461.0 );

      double time(years+yearfrac);

         // Compute the geometric mean longitude of the Sun
      //Средняя долгота Солнца
      double elm( fmod((4.881628 + 2*M_PI*yearfrac +
                        0.0001342*time), 2*M_PI) );

         // Mean longitude of perihelion
      //Средняя долгота Солнечного перигея
      double gamma(4.90823 + 0.00030005*time);

         // Mean anomaly
      double em(elm-gamma);

         // Mean obliquity
      //средний наклон эклиптики к экватору Земли
      double eps0(0.40931975 - 2.27e-6*time);
       m_inclin_sun = eps0;
         // Eccentricity
      double e(0.016751 - 4.2e-7*time);
      double esq(e*e);

         // True anomaly
      double v(em + 2.0*e*std::sin(em) + 1.25*esq*std::sin(2.0*em));

         // True ecliptic longitude
      //долгота Солнца
      double elt(v+gamma);
      m_longitude_sun = elt;
         // True distance
      double r( (1.0 - esq)/(1.0 + e*std::cos(v)) );

         // Moon's mean longitude
      double elmm( fmod((4.72 + 83.9971*time),2*M_PI) );

         // Useful definitions
      double coselt(std::cos(elt));
      double sineps(std::sin(eps0));
      double coseps(std::cos(eps0));
      double w1(-r*std::sin(elt));
      double selmm(std::sin(elmm));
      double celmm(std::cos(elmm));

     QVector <double> result;

         // Sun position is the opposite of Earth position
      result.append((r * coselt + MeanEarthMoonBary * celmm) * AU_CONST/1000. );
      result.append( (MeanEarthMoonBary * selmm - w1) * coseps * AU_CONST/1000. );
      result.append( (-w1 * sineps) * AU_CONST/1000. );

      return result;

   }

   double SunPosition::getRightAscension()
   {
       double enle = atan(sin(m_longitude_sun)*sin(m_inclin_sun)/pow(pow(m_longitude_sun,2)+pow(sin(m_longitude_sun)*cos(m_inclin_sun),2),0.5));

       double alfa = atan(tan(m_longitude_sun)*cos(m_inclin_sun));
       if((alfa>=0)&&(enle>=0))
           alfa = alfa;
       if((alfa>=0)&&(enle<0))
           alfa = alfa+M_PI;
       if((alfa<0)&&(enle>=0))
           alfa = alfa+M_PI;
       if((alfa<0)&&(enle<0))
           alfa = alfa+2*M_PI;
       return alfa;
   }


