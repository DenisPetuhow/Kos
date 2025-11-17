#ifndef PLOTGISTOGRAM_H
#define PLOTGISTOGRAM_H

#include <qwt_plot.h>


class QwtPlotMultiBarChart;

class CPlotGistogram: public QwtPlot
{
    Q_OBJECT

public:
    CPlotGistogram( QWidget * = NULL );

public Q_SLOTS:
   // void setMode( int );
    void setOrientation( int  orientation);
    void exportChart();

void setDat(QVector <QVector<double> > series, QStringList titles, QString titl);

private:
    void populate();

    QwtPlotMultiBarChart *d_barChartItem;
    QVector < QVector <double> > m_series;
    QStringList m_titles;
};

#endif // PLOTGISTOGRAM_H
