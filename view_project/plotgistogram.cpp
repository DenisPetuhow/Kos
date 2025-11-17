#include "plotgistogram.h"
#include <qwt_plot_renderer.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_multi_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_histogram.h>
#include <QApplication>
#include <qt_windows.h>
#include <QPalette>



class DistroScaleDraw: public QwtScaleDraw
{
public:
    DistroScaleDraw( Qt::Orientation orientation, const QVector<QString> &labels ):
        d_labels( labels )
    {
        setTickLength( QwtScaleDiv::MinorTick, 0 );
        setTickLength( QwtScaleDiv::MediumTick, 0 );
        setTickLength( QwtScaleDiv::MajorTick, 4 );
        
        enableComponent( QwtScaleDraw::Backbone, false );
        
        if ( orientation == Qt::Vertical )
        {
            setLabelRotation( 0.0 );
        }
        else
        {
            setLabelRotation( -90.0 );
        }
        
        setLabelAlignment( Qt::AlignLeft | Qt::AlignBottom );
    }
    
    virtual QwtText label( double value ) const
    {
        QwtText lbl;
        
        const int index = qRound( value );
        if ( index >= 0 && index <= d_labels.size() )
        {
            lbl = d_labels[ index ];
        }
        
        return lbl;
    }
    
private:
    const QVector<QString>  d_labels;
};

CPlotGistogram::CPlotGistogram( QWidget *parent ):
    QwtPlot( parent )
{
    setAutoFillBackground( true );

    setPalette( Qt::white );
    canvas()->setPalette( QColor( "LemonChiffon" ) );

    setTitle( QString::fromUtf8("Доступность КА ") );

    setAxisTitle( QwtPlot::yLeft, QString::fromUtf8("Количество КА") );
    setAxisTitle( QwtPlot::xBottom,QString::fromUtf8("Время сеанса связи от начала пуска БпЛА, с"));

    d_barChartItem = new QwtPlotMultiBarChart( "Bar Chart " );
    d_barChartItem->setLayoutPolicy( QwtPlotMultiBarChart::AutoAdjustSamples );
    d_barChartItem->setSpacing( 20 );
    d_barChartItem->setMargin( 3 );

    d_barChartItem->attach( this );

    QList<QwtText> titles;
    //for ( int i = 0; i < 3; i++ )

    //QString title(QString::fromUtf8("Общее количество"));
    // titles.append(QwtText(QString::fromUtf8("Общее количество")));
    // titles.append(QwtText(QString::fromUtf8("количество обнаруженных")));
    //titles.append(QwtText(QString::fromUtf8("количество необнаруженных")));
    // titles[0].setColor(Qt::green);
    //titles[1].setColor(Qt::red);
    // titles[2].setColor(Qt::blue);
    d_barChartItem->setBarTitles( titles );
    d_barChartItem->setLegendIconSize( QSize( 10, 14 ) );

    insertLegend( new QwtLegend() );

    populate();
    // setOrientation( 0 );

    setAutoReplot( true );
    this->setFocusPolicy(Qt::StrongFocus );
    installEventFilter(this);
    setAutoDelete(true);






    

}

void CPlotGistogram::setOrientation(int orientation)
{
    QwtPlot::Axis axis1, axis2;

    if ( orientation == 0 )
    {
        axis1 = QwtPlot::xBottom;
        axis2 = QwtPlot::yLeft;

        d_barChartItem->setOrientation( Qt::Vertical );
    }
    else
    {
        axis1 = QwtPlot::yLeft;
        axis2 = QwtPlot::xBottom;

        d_barChartItem->setOrientation( Qt::Horizontal );
    }

    setAxisScale( axis1, 0, d_barChartItem->dataSize() - 1, 1.0 );
    setAxisAutoScale( axis2 );

    QwtScaleDraw *scaleDraw1 = axisScaleDraw( axis1 );
    scaleDraw1->enableComponent( QwtScaleDraw::Backbone, false );
    scaleDraw1->enableComponent( QwtScaleDraw::Ticks, false );

    QwtScaleDraw *scaleDraw2 = axisScaleDraw( axis2 );
    scaleDraw2->enableComponent( QwtScaleDraw::Backbone, true );
    scaleDraw2->enableComponent( QwtScaleDraw::Ticks, true );

    plotLayout()->setAlignCanvasToScale( axis1, true );
    plotLayout()->setAlignCanvasToScale( axis2, false );

    plotLayout()->setCanvasMargin( 0 );
    updateCanvasMargins();

    replot();

}
void CPlotGistogram::setDat(QVector<QVector<double> > series, QStringList titles, QString titl)
{



    m_series.clear();
    m_series=series;
    m_titles=titles;
    setTitle(titl);
    const QwtPlotItemList &plotItems = this->itemList();
    
    for (int itemIndex = plotItems.size() - 1; itemIndex >= 0; itemIndex--)
    {
        QwtPlotItem *item = plotItems[itemIndex];
        
        if (item->rtti() == QwtPlotItem::Rtti_PlotMarker)
        {
            item->detach();
        }
        if (item->rtti() == QwtPlotItem::Rtti_PlotBarChart)
        {
            item->detach();
        }
        else        {
            item->detach();
        }
        
    }
    populate();
    
}

void CPlotGistogram::populate()
{

    QColor colors = QColor::fromHsv(0, 255, 255);
    const int numSamples = m_titles.size();
    if(m_titles.size() == 0)
        return;

    int numBars=m_series.size();
    QVector<QString> d_distros( m_titles.size());// надписи интервала
    QVector<double> regObjCountid(m_series[0].size(),0);//// количество обнаруженных по районам

    //QList<QwtText> titles;
    //titles.append(QwtText(m_tile));
    //titles.append(QwtText(QString::fromUtf8("Эффективная периодичность")));
    //titles.append(QwtText(QString::fromUtf8("количество необнаруженных")));
    //titles[0].setColor(QColor(32,143,255));
    //titles[1].setColor(Qt::cyan);
    //titles[2].setColor(Qt::blue);
    //d_barChartItem->setBarTitles( titles );
    d_barChartItem->setLegendIconSize( QSize( 10, 14 ) );


    int numCurves = m_series[0].size();

    if (numCurves > 0)
    {

        //
        QVector<QVector<double> > mass(numSamples);
        for ( int i1 = 0; i1 < numSamples; ++i1 )
        {
            QVector<double> mm(numBars);

            mass[i1]=mm;
        }

        //       //  QVector< QVector<double> > series1;
        for (int k = 0; k <numSamples; ++k)
        {

            mass[k][0]=m_series[0][k];

            d_distros[k]=m_titles.at(k);//QString("Район %1").arg(k);

        }
        //  вывод данных на график

        QVector< QVector<double> > series;
        for ( int i = 0; i < numSamples; i++ )
        {
            QVector<double> values;
            for ( int j = 0; j < numBars; j++ )
                values += mass[i][j];

            series += values;
        }

        d_barChartItem->setSamples( series );
        d_barChartItem->setStyle( QwtPlotMultiBarChart::Grouped );
        QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
        symbol->setLineWidth( 2 );
        symbol->setFrameStyle( QwtColumnSymbol::Raised );
        symbol->setPalette( QPalette( colors ) );
        d_barChartItem->setSymbol(0, symbol );
        d_barChartItem->attach(this);

    }

    QwtPlot::Axis axis1, axis2;

    axis1 = QwtPlot::xBottom;
    axis2 = QwtPlot::yLeft;
    setAxisScaleDraw( axis1, new DistroScaleDraw( Qt::Horizontal , d_distros ) );

    plotLayout()->setCanvasMargin( 0 );
    updateCanvasMargins();

    replot();
}
void CPlotGistogram::exportChart()
{
    this->setFocusPolicy(Qt::StrongFocus );
    QApplication::sendPostedEvents( this, QEvent::LayoutRequest );
    
    replot();
    if(m_series.size()>0)
    {
        QString file_name("dost.png");
        
        QwtPlotRenderer renderer;
        renderer.installEventFilter(this);
        renderer.renderDocument(this, file_name, QSizeF(150, 100), 85);
        
    }
}
