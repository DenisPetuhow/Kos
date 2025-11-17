#include "objfileparser.h"
QStringList SParamBSKOpticT1(QStringList()<< QString::fromUtf8("площадь элементов, 10<sup>-10</sup>*м<sup>2</sup>")<< QString::fromUtf8("спектр. диапазон, мкм") << QString::fromUtf8("фокус, м")   << QString::fromUtf8("относ. отверстие объектива")  << QString::fromUtf8("время экспозиции, 10<sup>-6</sup>*с")<< QString::fromUtf8("квантовая эффективность 10<sup>-5</sup>")<< QString::fromUtf8("световая экспозиция 10<sup>-5</sup>")<< QString::fromUtf8(" к-т пропускаяния OC"));
QStringList SParamBSKOpticF1(QStringList() << QString::fromUtf8("спектр. диапазон, мкм") << QString::fromUtf8("фокус, м") << QString::fromUtf8("разреш. способность,лин/мм")<< QString::fromUtf8(" к-т пропускания OC"));
QStringList SParamBSKPLSF1(QStringList() << QString::fromUtf8("диапазон PB, ГГц")<< QString::fromUtf8("мощность излучения, кВт")<< QString::fromUtf8("угол выноса ближней границы, град")<< QString::fromUtf8("угол выноса дальней границы, град")<< QString::fromUtf8("разрешение, м")<< QString::fromUtf8("порог. чувствительность,дБ")<< QString::fromUtf8("канал передачи РЛИ, Мбит/с"));
QStringList SParamGSO(QStringList()<< QString::fromUtf8("Мощность передатчика, Вт")<< QString::fromUtf8("Частота (прием), ГГц")<< QString::fromUtf8("Частота (передача), ГГц")<< QString::fromUtf8("Ширина спектра, МГц")<< QString::fromUtf8("Чувств. приемника, ДБ")<< QString::fromUtf8("Количество каналов")<< QString::fromUtf8("Ширина ДН луча, град")<< QString::fromUtf8("КНД антенны"));
QStringList SParamBSKRTR1(QStringList() << QString::fromUtf8("минимальная частота приема сигналов, МГц")<< QString::fromUtf8("максимальная частота приема сигналов, МГц")<< QString::fromUtf8("чувствительность приемника,dB")<< QString::fromUtf8("ширина диаграммы направленности, град")<< QString::fromUtf8("СКО ошибки пеленгации,угл. мин"));
CObjFileParser::CObjFileParser()
{

}

bool CObjFileParser::writeOrbitObjXml(const QString fileName, const QVector<
                                      ASDOrbitalObjectPar> data)
{
    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("Satelite");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("type", QString::number(data.at(i).type));
        xml.writeTextElement("nameSys", data.at(i).nameSys);
        xml.writeTextElement("type_dat", QString::number(data.at(i).type_dat));

        if (data.at(i).type_dat == 0)
        {
            xml.writeTextElement("name", data.at(i).kep.name);
            xml.writeTextElement("epoch", data.at(i).kep.t_epoch.toString(
                                     "hh:mm:ss yyyy.MM.dd"));
            xml.writeTextElement("a", QString::number(data.at(i).kep.a));
            xml.writeTextElement("i", QString::number(data.at(i).kep.i));
            xml.writeTextElement("l", QString::number(data.at(i).kep.l));
            xml.writeTextElement("e", QString::number(data.at(i).kep.e));
            xml.writeTextElement("omega", QString::number(data.at(i).kep.omega));
            xml.writeTextElement("u", QString::number(data.at(i).kep.u));
        }
        if (data.at(i).type_dat == 1)
        {
            xml.writeTextElement("name", data.at(i).ags.name);
            xml.writeTextElement("epoch", data.at(i).ags.t_epoch.toString(
                                     "hh:mm:ss yyyy.MM.dd"));
            xml.writeTextElement("x", QString::number(data.at(i).ags.x));
            xml.writeTextElement("y", QString::number(data.at(i).ags.y));
            xml.writeTextElement("z", QString::number(data.at(i).ags.z));
            xml.writeTextElement("vx", QString::number(data.at(i).ags.vx));
            xml.writeTextElement("vy", QString::number(data.at(i).ags.vy));
            xml.writeTextElement("vz", QString::number(data.at(i).ags.vz));
        }
        if (data.at(i).type_dat == 2)
        {
            xml.writeTextElement("name", data.at(i).stle.satName);
            xml.writeTextElement("str1", data.at(i).stle.firstString);
            xml.writeTextElement("str2", data.at(i).stle.secondString);
        }
if(data.at(i).bsa.size()>0)
        {
        for (int j = 0; j < data.at(i).bsa.size(); ++j)
        {
            xml.writeTextElement("bsa_type", QString::number(data.at(i).bsa.at(
                                                                 j).type));
            xml.writeTextElement("bsa_name", data.at(i).bsa.at(j).name);
            xml.writeTextElement("bsa_gamma", QString::number(
                                     data.at(i).bsa.at(j).gamma));
            xml.writeTextElement("bsa_alfaMounting", QString::number(
                                     data.at(i).bsa.at(j).alfaMounting));
            xml.writeTextElement("bsa_etaMounting", QString::number(
                                     data.at(i).bsa.at(j).etaMounting));
            xml.writeTextElement("bsa_betaMounting", QString::number(
                                     data.at(i).bsa.at(j).betaMounting));
            xml.writeTextElement("bsa_deltaTau", QString::number(
                                     data.at(i).bsa.at(j).deltaTau));
            xml.writeTextElement("bsa_deltaN", QString::number(
                                     data.at(i).bsa.at(j).deltaN));
            xml.writeTextElement("bsa_deltaB", QString::number(data.at(i).bsa.at(j).deltaB));
            xml.writeTextElement("bsa_deltaH", QString::number(data.at(i).bsa.at(j).deltaH));
            xml.writeTextElement("bsa_deltaV", QString::number(data.at(i).bsa.at(j).deltaV));
            xml.writeTextElement("bsa_deltaL", QString::number(data.at(i).bsa.at(j).deltaL));
            // доп ОЭС
            //double deltaVr;//!< скорость перенацеливания,с (для систем обзора).
           // double skor;//!< Точность позиционирования, м
           // double Pr;//!< Производительность, млн кв км/сут
          //  double fmem;//!<Емкость ПЗУ, Гбайт
                                   xml.writeTextElement("bsa_deltaVr", QString::number(data.at(i).bsa.at(j).deltaVr));
                                  xml.writeTextElement("bsa_skor", QString::number(data.at(i).bsa.at(j).skor));
                                   xml.writeTextElement("bsa_Pr", QString::number(data.at(i).bsa.at(j).Pr));
                                  xml.writeTextElement("bsa_fmem", QString::number(data.at(i).bsa.at(j).fmem));

            if(data.at(i).bsa.at(j).type==OERT)
            { if(data.at(i).bsa.at(j).param_value.size()==8)
                {
                    xml.writeTextElement("bsa_name_param1", data.at(i).bsa.at(j).name_param.at(0));
                    xml.writeTextElement("bsa_Dpar1", QString::number(data.at(i).bsa.at(j).param_value.at(0)));
                    xml.writeTextElement("bsa_name_param2", data.at(i).bsa.at(j).name_param.at(1));
                    xml.writeTextElement("bsa_Dpar2", QString::number(data.at(i).bsa.at(j).param_value.at(1)));
                    xml.writeTextElement("bsa_name_param3", data.at(i).bsa.at(j).name_param.at(2));
                    xml.writeTextElement("bsa_Dpar3", QString::number(data.at(i).bsa.at(j).param_value.at(2)));
                    xml.writeTextElement("bsa_name_param4", data.at(i).bsa.at(j).name_param.at(3));
                    xml.writeTextElement("bsa_Dpar4", QString::number(data.at(i).bsa.at(j).param_value.at(3)));
                    xml.writeTextElement("bsa_name_param5", data.at(i).bsa.at(j).name_param.at(4));
                    xml.writeTextElement("bsa_Dpar5", QString::number(data.at(i).bsa.at(j).param_value.at(4)));
                    xml.writeTextElement("bsa_name_param6", data.at(i).bsa.at(j).name_param.at(5));
                    xml.writeTextElement("bsa_Dpar6", QString::number(data.at(i).bsa.at(j).param_value.at(5)));
                    xml.writeTextElement("bsa_name_param7", data.at(i).bsa.at(j).name_param.at(6));
                    xml.writeTextElement("bsa_Dpar7", QString::number(data.at(i).bsa.at(j).param_value.at(6)));
                    xml.writeTextElement("bsa_name_param8", data.at(i).bsa.at(j).name_param.at(7));
                    xml.writeTextElement("bsa_Dpar8", QString::number(data.at(i).bsa.at(j).param_value.at(7)));
                }
                else
                {
                    xml.writeTextElement("bsa_name_param1", SParamBSKOpticT1.at(0));
                    xml.writeTextElement("bsa_Dpar1", "0.0");
                    xml.writeTextElement("bsa_name_param2", SParamBSKOpticT1.at(1));
                    xml.writeTextElement("bsa_Dpar2", "0.0");
                    xml.writeTextElement("bsa_name_param3", SParamBSKOpticT1.at(2));
                    xml.writeTextElement("bsa_Dpar3", "0.0");
                    xml.writeTextElement("bsa_name_param4", SParamBSKOpticT1.at(3));
                    xml.writeTextElement("bsa_Dpar4", "0.0");
                    xml.writeTextElement("bsa_name_param5", SParamBSKOpticT1.at(4));
                    xml.writeTextElement("bsa_Dpar5", "0.0");
                    xml.writeTextElement("bsa_name_param6", SParamBSKOpticT1.at(5));
                    xml.writeTextElement("bsa_Dpar6", "0.0");
                    xml.writeTextElement("bsa_name_param7", SParamBSKOpticT1.at(6));
                    xml.writeTextElement("bsa_Dpar7", "0.0");
                    xml.writeTextElement("bsa_name_param8", SParamBSKOpticT1.at(7));
                    xml.writeTextElement("bsa_Dpar8", "0.0");
                }
            }
            if(data.at(i).bsa.at(j).type==OERF)
            { if(data.at(i).bsa.at(j).param_value.size()==4)
                {
                    xml.writeTextElement("bsa_name_param1", data.at(i).bsa.at(j).name_param.at(0));
                    xml.writeTextElement("bsa_Dpar1", QString::number(data.at(i).bsa.at(j).param_value.at(0)));
                    xml.writeTextElement("bsa_name_param2", data.at(i).bsa.at(j).name_param.at(1));
                    xml.writeTextElement("bsa_Dpar2", QString::number(data.at(i).bsa.at(j).param_value.at(1)));
                    xml.writeTextElement("bsa_name_param3", data.at(i).bsa.at(j).name_param.at(2));
                    xml.writeTextElement("bsa_Dpar3", QString::number(data.at(i).bsa.at(j).param_value.at(2)));
                    xml.writeTextElement("bsa_name_param4", data.at(i).bsa.at(j).name_param.at(3));
                    xml.writeTextElement("bsa_Dpar4", QString::number(data.at(i).bsa.at(j).param_value.at(3)));
                }
                else
                {
                    xml.writeTextElement("bsa_name_param1", SParamBSKOpticF1.at(0));
                    xml.writeTextElement("bsa_Dpar1", "0.0");
                    xml.writeTextElement("bsa_name_param2", SParamBSKOpticF1.at(1));
                    xml.writeTextElement("bsa_Dpar2", "0.0");
                    xml.writeTextElement("bsa_name_param3", SParamBSKOpticF1.at(2));
                    xml.writeTextElement("bsa_Dpar3", "0.0");
                    xml.writeTextElement("bsa_name_param4", SParamBSKOpticF1.at(3));
                    xml.writeTextElement("bsa_Dpar4", "0.0");

                }

            }
            if(data.at(i).bsa.at(j).type==RLRF)
            { if(data.at(i).bsa.at(j).param_value.size()==6)
                {
                    xml.writeTextElement("bsa_name_param1", data.at(i).bsa.at(j).name_param.at(0));
                    xml.writeTextElement("bsa_Dpar1", QString::number(data.at(i).bsa.at(j).param_value.at(0)));
                    xml.writeTextElement("bsa_name_param2", data.at(i).bsa.at(j).name_param.at(1));
                    xml.writeTextElement("bsa_Dpar2", QString::number(data.at(i).bsa.at(j).param_value.at(1)));
                    xml.writeTextElement("bsa_name_param3", data.at(i).bsa.at(j).name_param.at(2));
                    xml.writeTextElement("bsa_Dpar3", QString::number(data.at(i).bsa.at(j).param_value.at(2)));
                    xml.writeTextElement("bsa_name_param4", data.at(i).bsa.at(j).name_param.at(3));
                    xml.writeTextElement("bsa_Dpar4", QString::number(data.at(i).bsa.at(j).param_value.at(3)));
                    xml.writeTextElement("bsa_name_param5", data.at(i).bsa.at(j).name_param.at(4));
                    xml.writeTextElement("bsa_Dpar5", QString::number(data.at(i).bsa.at(j).param_value.at(4)));
                    xml.writeTextElement("bsa_name_param6", data.at(i).bsa.at(j).name_param.at(5));
                    xml.writeTextElement("bsa_Dpar6", QString::number(data.at(i).bsa.at(j).param_value.at(5)));
                }
                if(data.at(i).bsa.at(j).param_value.size()==7)
                                {
                                    xml.writeTextElement("bsa_name_param1", data.at(i).bsa.at(j).name_param.at(0));
                                    xml.writeTextElement("bsa_Dpar1", QString::number(data.at(i).bsa.at(j).param_value.at(0)));
                                    xml.writeTextElement("bsa_name_param2", data.at(i).bsa.at(j).name_param.at(1));
                                    xml.writeTextElement("bsa_Dpar2", QString::number(data.at(i).bsa.at(j).param_value.at(1)));
                                    xml.writeTextElement("bsa_name_param3", data.at(i).bsa.at(j).name_param.at(2));
                                    xml.writeTextElement("bsa_Dpar3", QString::number(data.at(i).bsa.at(j).param_value.at(2)));
                                    xml.writeTextElement("bsa_name_param4", data.at(i).bsa.at(j).name_param.at(3));
                                    xml.writeTextElement("bsa_Dpar4", QString::number(data.at(i).bsa.at(j).param_value.at(3)));
                                    xml.writeTextElement("bsa_name_param5", data.at(i).bsa.at(j).name_param.at(4));
                                    xml.writeTextElement("bsa_Dpar5", QString::number(data.at(i).bsa.at(j).param_value.at(4)));
                                    xml.writeTextElement("bsa_name_param6", data.at(i).bsa.at(j).name_param.at(5));
                                    xml.writeTextElement("bsa_Dpar6", QString::number(data.at(i).bsa.at(j).param_value.at(5)));
                                    xml.writeTextElement("bsa_name_param7", data.at(i).bsa.at(j).name_param.at(6));
                                    xml.writeTextElement("bsa_Dpar7", QString::number(data.at(i).bsa.at(j).param_value.at(6)));
                                }
                else
                {
                    xml.writeTextElement("bsa_name_param1", SParamBSKPLSF1.at(0));
                    xml.writeTextElement("bsa_Dpar1", "0.0");
                    xml.writeTextElement("bsa_name_param2", SParamBSKPLSF1.at(1));
                    xml.writeTextElement("bsa_Dpar2", "0.0");
                    xml.writeTextElement("bsa_name_param3", SParamBSKPLSF1.at(2));
                    xml.writeTextElement("bsa_Dpar3", "0.0");
                    xml.writeTextElement("bsa_name_param4", SParamBSKPLSF1.at(3));
                    xml.writeTextElement("bsa_Dpar4", "0.0");
                    xml.writeTextElement("bsa_name_param5", SParamBSKPLSF1.at(4));
                    xml.writeTextElement("bsa_Dpar5", "0.0");
                    xml.writeTextElement("bsa_name_param6", SParamBSKPLSF1.at(5));
                    xml.writeTextElement("bsa_Dpar6", "0.0");
                    xml.writeTextElement("bsa_name_param7", SParamBSKPLSF1.at(6));
                    xml.writeTextElement("bsa_Dpar7", "0.0");

                }

            }
            if(data.at(i).bsa.at(j).type==COMMUNICATION)
            { if(data.at(i).bsa.at(j).param_value.size()==8)
                {
                    xml.writeTextElement("bsa_name_param1", data.at(i).bsa.at(j).name_param.at(0));
                    xml.writeTextElement("bsa_Dpar1", QString::number(data.at(i).bsa.at(j).param_value.at(0)));
                    xml.writeTextElement("bsa_name_param2", data.at(i).bsa.at(j).name_param.at(1));
                    xml.writeTextElement("bsa_Dpar2", QString::number(data.at(i).bsa.at(j).param_value.at(1)));
                    xml.writeTextElement("bsa_name_param3", data.at(i).bsa.at(j).name_param.at(2));
                    xml.writeTextElement("bsa_Dpar3", QString::number(data.at(i).bsa.at(j).param_value.at(2)));
                    xml.writeTextElement("bsa_name_param4", data.at(i).bsa.at(j).name_param.at(3));
                    xml.writeTextElement("bsa_Dpar4", QString::number(data.at(i).bsa.at(j).param_value.at(3)));
                    xml.writeTextElement("bsa_name_param5", data.at(i).bsa.at(j).name_param.at(4));
                    xml.writeTextElement("bsa_Dpar5", QString::number(data.at(i).bsa.at(j).param_value.at(4)));
                    xml.writeTextElement("bsa_name_param6", data.at(i).bsa.at(j).name_param.at(5));
                    xml.writeTextElement("bsa_Dpar6", QString::number(data.at(i).bsa.at(j).param_value.at(5)));
                    xml.writeTextElement("bsa_name_param7", data.at(i).bsa.at(j).name_param.at(6));
                    xml.writeTextElement("bsa_Dpar7", QString::number(data.at(i).bsa.at(j).param_value.at(6)));
                    xml.writeTextElement("bsa_name_param8", data.at(i).bsa.at(j).name_param.at(7));
                    xml.writeTextElement("bsa_Dpar8", QString::number(data.at(i).bsa.at(j).param_value.at(7)));
                }
                else
                {
                    xml.writeTextElement("bsa_name_param1", SParamGSO.at(0));
                    xml.writeTextElement("bsa_Dpar1", "0.0");
                    xml.writeTextElement("bsa_name_param2", SParamGSO.at(1));
                    xml.writeTextElement("bsa_Dpar2", "0.0");
                    xml.writeTextElement("bsa_name_param3", SParamGSO.at(2));
                    xml.writeTextElement("bsa_Dpar3", "0.0");
                    xml.writeTextElement("bsa_name_param4", SParamGSO.at(3));
                    xml.writeTextElement("bsa_Dpar4", "0.0");
                    xml.writeTextElement("bsa_name_param5", SParamGSO.at(4));
                    xml.writeTextElement("bsa_Dpar5", "0.0");
                    xml.writeTextElement("bsa_name_param6", SParamGSO.at(5));
                    xml.writeTextElement("bsa_Dpar6", "0.0");
                    xml.writeTextElement("bsa_name_param7", SParamGSO.at(6));
                    xml.writeTextElement("bsa_Dpar7", "0.0");
                    xml.writeTextElement("bsa_name_param8", SParamGSO.at(7));
                    xml.writeTextElement("bsa_Dpar8", "0.0");
                }
            }

            if(data.at(i).bsa.at(j).type==RTR)
            { if(data.at(i).bsa.at(j).param_value.size()==5)
                {
                    xml.writeTextElement("bsa_name_param1", data.at(i).bsa.at(j).name_param.at(0));
                    xml.writeTextElement("bsa_Dpar1", QString::number(data.at(i).bsa.at(j).param_value.at(0)));
                    xml.writeTextElement("bsa_name_param2", data.at(i).bsa.at(j).name_param.at(1));
                    xml.writeTextElement("bsa_Dpar2", QString::number(data.at(i).bsa.at(j).param_value.at(1)));
                    xml.writeTextElement("bsa_name_param3", data.at(i).bsa.at(j).name_param.at(2));
                    xml.writeTextElement("bsa_Dpar3", QString::number(data.at(i).bsa.at(j).param_value.at(2)));
                    xml.writeTextElement("bsa_name_param4", data.at(i).bsa.at(j).name_param.at(3));
                    xml.writeTextElement("bsa_Dpar4", QString::number(data.at(i).bsa.at(j).param_value.at(3)));
                    xml.writeTextElement("bsa_name_param5", data.at(i).bsa.at(j).name_param.at(4));
                    xml.writeTextElement("bsa_Dpar5", QString::number(data.at(i).bsa.at(j).param_value.at(4)));
                    }
                else
                {
                    xml.writeTextElement("bsa_name_param1", SParamBSKRTR1.at(0));
                    xml.writeTextElement("bsa_Dpar1", "30.0");
                    xml.writeTextElement("bsa_name_param2", SParamBSKRTR1.at(1));
                    xml.writeTextElement("bsa_Dpar2", "1000.0");
                    xml.writeTextElement("bsa_name_param3", SParamBSKRTR1.at(2));
                    xml.writeTextElement("bsa_Dpar3", "10.0");
                    xml.writeTextElement("bsa_name_param4", SParamBSKRTR1.at(3));
                    xml.writeTextElement("bsa_Dpar4", "60.0");
                    xml.writeTextElement("bsa_name_param5", SParamBSKRTR1.at(4));
                    xml.writeTextElement("bsa_Dpar5", "3.0");

                }
            }


        }
       }
xml.writeTextElement("end", "1");

        xml.writeEndElement();

    }
    xml.writeEndDocument();

    //	if (xml.hasError())
    //	{
    //		return false;
    //	}

    return true;
}

bool CObjFileParser::writeOrbitObjIni(const QString fileName, const QVector<
                                      ASDOrbitalObjectPar> data)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginWriteArray("orbitobj");
    if (data.size() == 0)
        return false;
    for (int i = 0; i < data.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("type", data.at(i).type);
        settings.setValue("nameSys", data.at(i).nameSys);
        settings.setValue("type_dat", data.at(i).type_dat);
        if (data.at(i).type_dat == 0)
        {
            settings.setValue("name", data.at(i).kep.name);
            settings.setValue("epoch", data.at(i).kep.t_epoch);
            settings.setValue("a", data.at(i).kep.a);
            settings.setValue("i", data.at(i).kep.i);
            settings.setValue("l", data.at(i).kep.l);
            settings.setValue("e", data.at(i).kep.e);
            settings.setValue("omega", data.at(i).kep.omega);
            settings.setValue("u", data.at(i).kep.u);

        }
        if (data.at(i).type_dat == 1)
        {
            settings.setValue("name", data.at(i).ags.name);
            settings.setValue("epoch", data.at(i).ags.t_epoch);
            settings.setValue("x", data.at(i).ags.x);
            settings.setValue("y", data.at(i).ags.y);
            settings.setValue("z", data.at(i).ags.z);
            settings.setValue("vx", data.at(i).ags.vx);
            settings.setValue("vy", data.at(i).ags.vy);
            settings.setValue("vz", data.at(i).ags.vz);
        }
        if (data.at(i).type_dat == 2)
        {
            settings.setValue("name", data.at(i).stle.satName);
            settings.setValue("str1", data.at(i).stle.firstString);
            settings.setValue("str2", data.at(i).stle.secondString);
        }

        for (int j = 0; j < data.at(i).bsa.size(); ++j)
        {
            settings.setValue("bsa_type", data.at(i).bsa.at(j).type);
            settings.setValue("bsa_name", data.at(i).bsa.at(j).name);
            settings.setValue("bsa_gamma", data.at(i).bsa.at(j).gamma);
            settings.setValue("bsa_alfaMounting",
                              data.at(i).bsa.at(j).alfaMounting);
            settings.setValue("bsa_etaMounting",
                              data.at(i).bsa.at(j).etaMounting);
            settings.setValue("bsa_betaMounting",
                              data.at(i).bsa.at(j).betaMounting);
            settings.setValue("bsa_deltaTau", data.at(i).bsa.at(j).deltaTau);
            settings.setValue("bsa_deltaN", data.at(i).bsa.at(j).deltaN);
            settings.setValue("bsa_deltaB", data.at(i).bsa.at(j).deltaB);
            settings.setValue("bsa_deltaH", data.at(i).bsa.at(j).deltaH);
            settings.setValue("bsa_deltaV", data.at(i).bsa.at(j).deltaV);
            settings.setValue("bsa_deltaL", data.at(i).bsa.at(j).deltaL);
            //                        // доп ОЭС
            //                         settings.setValue("bsa_resonving_Power", data.at(i).bsa.at(j).resonving_Power);
            //                         settings.setValue("bsa_length_line", data.at(i).bsa.at(j).length_line);
            //                         settings.setValue("bsa_focus", data.at(i).bsa.at(j).focus);
            //                         settings.setValue("bsa_countN_PZS", data.at(i).bsa.at(j).countN_PZS);
        }
    }

    settings.endArray();
    return true;
}

bool CObjFileParser::writeRkoObjXml(const QString fileName, const QVector<
                                    ParamGrBaseInter> data)
{

    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("RKOobj");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("region_name", data.at(i).region.name);
        xml.writeTextElement("region_max_lat", QString::number(
                                 data.at(i).region.maxlat));
        xml.writeTextElement("region_min_lat", QString::number(
                                 data.at(i).region.minlat));
        xml.writeTextElement("region_max_lon", QString::number(
                                 data.at(i).region.maxlong));
        xml.writeTextElement("region_min_lon", QString::number(
                                 data.at(i).region.minlong));
        xml.writeTextElement("point_name", data.at(i).point.name);
        xml.writeTextElement("point_lat", QString::number(data.at(i).point.lat));
        xml.writeTextElement("point_lon", QString::number(data.at(i).point.lon));
        xml.writeTextElement("point_h", QString::number(data.at(i).point.h));
        xml.writeTextElement("max_az", QString::number(data.at(i).maxaz));
        xml.writeTextElement("min_az", QString::number(data.at(i).minaz));
        xml.writeTextElement("max_el", QString::number(data.at(i).maxelev));
        xml.writeTextElement("min_el", QString::number(data.at(i).minelev));
        xml.writeTextElement("max_dist", QString::number(data.at(i).maxdist));
        xml.writeTextElement("min_dist", QString::number(data.at(i).mindist));
        xml.writeTextElement("tauselect", QString::number(data.at(i).tauselect));
        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;
}

bool CObjFileParser::writeRkoObjIni(const QString fileName, const QVector<
                                    ParamGrBaseInter> data)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginWriteArray("RKOobj");
    if (data.size() == 0)
        return false;

    for (int i = 0; i < data.size(); ++i)
    {

        settings.setArrayIndex(i);
        settings.setValue("region_name", data.at(i).region.name);
        settings.setValue("region_maxlat", data.at(i).region.maxlat);
        settings.setValue("region_minlat", data.at(i).region.minlat);
        settings.setValue("region_maxlon", data.at(i).region.maxlong);
        settings.setValue("region_minlon", data.at(i).region.minlong);
        settings.setValue("point_name", data.at(i).point.name);
        settings.setValue("point_lat", data.at(i).point.lat);
        settings.setValue("point_lon", data.at(i).point.lon);
        settings.setValue("point_h", data.at(i).point.h);
        settings.setValue("max_az", data.at(i).maxaz);
        settings.setValue("min_az", data.at(i).minaz);
        settings.setValue("max_el", data.at(i).maxelev);
        settings.setValue("min_el", data.at(i).minelev);
        settings.setValue("max_dist", data.at(i).maxdist);
        settings.setValue("min_dist", data.at(i).mindist);
        settings.setValue("tauselect", data.at(i).tauselect);
    }
    settings.endArray();
    return true;

}
bool CObjFileParser::writeRegionOObjXml(const QString fileName, const QVector<
                                       ParamregionO> data)
{
    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");


    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("RegobjO");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("name", data.at(i).name);
        xml.writeTextElement("mlat", QString::number(data.at(i).mlat));
        xml.writeTextElement("dllat", QString::number(data.at(i).dllat));
        xml.writeTextElement("mlong", QString::number(data.at(i).mlong));
        xml.writeTextElement("dllon", QString::number(data.at(i).dllon));
        xml.writeTextElement("countR", QString::number(data.at(i).countR));
        xml.writeTextElement("type", QString::number(data.at(i).type));
        xml.writeTextElement("ldir", QString::number(data.at(i).ldir));
        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;
}

bool CObjFileParser::writeRegionObjXml(const QString fileName, const QVector<
                                       Paramregion> data)
{
    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("Regobj");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("name", data.at(i).name);
        xml.writeTextElement("max_lat", QString::number(data.at(i).maxlat));
        xml.writeTextElement("min_lat", QString::number(data.at(i).minlat));
        xml.writeTextElement("max_long", QString::number(data.at(i).maxlong));
        xml.writeTextElement("min_long", QString::number(data.at(i).minlong));
        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;

}
bool CObjFileParser::writeRegionObjNXml(const QString fileName, const QVector<
                                        ParamregionOBJ> data)
{
    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("RegobjN");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("name", data.at(i).name);
        xml.writeTextElement("max_lat", QString::number(data.at(i).maxlat));
        xml.writeTextElement("min_lat", QString::number(data.at(i).minlat));
        xml.writeTextElement("max_long", QString::number(data.at(i).maxlong));
        xml.writeTextElement("min_long", QString::number(data.at(i).minlong));
        if(data.at(i).vecOBJ.size()>0)
        {
            ParamOBJOPTIC opt;
            for (int j = 0; j < data.at(i).vecOBJ.size(); ++j)
            {

                opt= data.at(i).vecOBJ.at(j);

                xml.writeTextElement("NameOBJ", opt.name);
                xml.writeTextElement("LatOBJ", QString::number(opt.point.lat));
                xml.writeTextElement("LonOBJ", QString::number(opt.point.lon));
                xml.writeTextElement("hOBJ", QString::number(opt.point.h));
                xml.writeTextElement("HOBJ", QString::number(opt.HObj));
                xml.writeTextElement("LengtOBJ", QString::number(opt.LengthObj));
                xml.writeTextElement("WidthOBJ", QString::number(opt.WidthObj));
                xml.writeTextElement("type_Obj", QString::number(opt.type_Obj));
                xml.writeTextElement("type_M", QString::number(opt.type_M));
                xml.writeTextElement("LumL04", QString::number(opt.lumL04));
                xml.writeTextElement("LumL05", QString::number(opt.lumL05));
                xml.writeTextElement("LumL06", QString::number(opt.lumL06));
                xml.writeTextElement("LumL07", QString::number(opt.lumL07));
                xml.writeTextElement("LumL08", QString::number(opt.lumL08));
                xml.writeTextElement("LumL09", QString::number(opt.lumL09));
                xml.writeTextElement("type_PP", QString::number(opt.type_PP));
                xml.writeTextElement("type_VV", QString::number(opt.type_VV));
                xml.writeTextElement("type_CL", QString::number(opt.type_CL));

                xml.writeTextElement("endOBJ", "1");
            }
        }




        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;

}
bool CObjFileParser::writeRegionObjIni(const QString fileName, const QVector<
                                       Paramregion> data)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginWriteArray("Regobj");
    if (data.size() == 0)
        return false;
    for (int i = 0; i < data.size(); ++i)
    {

        settings.setArrayIndex(i);
        settings.setValue("name", data.at(i).name);
        settings.setValue("maxlat", data.at(i).maxlat);
        settings.setValue("minlat", data.at(i).minlat);
        settings.setValue("maxlong", data.at(i).maxlong);
        settings.setValue("minlong", data.at(i).minlong);

    }
    settings.endArray();
    return true;

}

bool CObjFileParser::writeRegionObjNIni(const QString fileName, const QVector<
                                        ParamregionOBJ> data)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginWriteArray("RegobjN");
    if (data.size() == 0)
        return false;
    for (int i = 0; i < data.size(); ++i)
    {

        settings.setArrayIndex(i);
        settings.setValue("name", data.at(i).name);
        settings.setValue("maxlat", data.at(i).maxlat);
        settings.setValue("minlat", data.at(i).minlat);
        settings.setValue("maxlong", data.at(i).maxlong);
        settings.setValue("minlong", data.at(i).minlong);

    }
    settings.endArray();
    return true;

}
bool CObjFileParser::writeLbiObjXml(const QString fileName, QVector<
                                    ParamGrBaseInter> data)
{

    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("LBIobj");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("region_name", data.at(i).region.name);
        xml.writeTextElement("region_max_lat", QString::number(
                                 data.at(i).region.maxlat));
        xml.writeTextElement("region_min_lat", QString::number(
                                 data.at(i).region.minlat));
        xml.writeTextElement("region_max_lon", QString::number(
                                 data.at(i).region.maxlong));
        xml.writeTextElement("region_min_lon", QString::number(
                                 data.at(i).region.minlong));
        xml.writeTextElement("point_name", data.at(i).point.name);
        xml.writeTextElement("point_lat", QString::number(data.at(i).point.lat));
        xml.writeTextElement("point_lon", QString::number(data.at(i).point.lon));
        xml.writeTextElement("point_h", QString::number(data.at(i).point.h));
        xml.writeTextElement("max_az", QString::number(data.at(i).maxaz));
        xml.writeTextElement("min_az", QString::number(data.at(i).minaz));
        xml.writeTextElement("max_el", QString::number(data.at(i).maxelev));
        xml.writeTextElement("min_el", QString::number(data.at(i).minelev));
        xml.writeTextElement("max_dist", QString::number(data.at(i).maxdist));
        xml.writeTextElement("min_dist", QString::number(data.at(i).mindist));
        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;
}

bool CObjFileParser::writeLbiObjIni(const QString fileName, QVector<
                                    ParamGrBaseInter> data)
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginWriteArray("LBIobj");
    if (data.size() == 0)
        return false;
    for (int i = 0; i < data.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("region_name", data.at(i).region.name);
        settings.setValue("region_maxlat", data.at(i).region.maxlat);
        settings.setValue("region_minlat", data.at(i).region.minlat);
        settings.setValue("region_maxlon", data.at(i).region.maxlong);
        settings.setValue("region_minlon", data.at(i).region.minlong);
        settings.setValue("point_name", data.at(i).point.name);
        settings.setValue("point_lat", data.at(i).point.lat);
        settings.setValue("point_lon", data.at(i).point.lon);
        settings.setValue("point_h", data.at(i).point.h);
        settings.setValue("max_az", data.at(i).maxaz);
        settings.setValue("min_az", data.at(i).minaz);
        settings.setValue("max_el", data.at(i).maxelev);
        settings.setValue("min_el", data.at(i).minelev);
        settings.setValue("max_dist", data.at(i).maxdist);
        settings.setValue("min_dist", data.at(i).mindist);
    }
    settings.endArray();
    return true;

}

bool CObjFileParser::writeGbiObjXml(const QString fileName, QVector<
                                    ParamGrBaseInter> data)
{

    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("GBIobj");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("region_name", data.at(i).region.name);
        xml.writeTextElement("region_max_lat", QString::number(
                                 data.at(i).region.maxlat));
        xml.writeTextElement("region_min_lat", QString::number(
                                 data.at(i).region.minlat));
        xml.writeTextElement("region_max_lon", QString::number(
                                 data.at(i).region.maxlong));
        xml.writeTextElement("region_min_lon", QString::number(
                                 data.at(i).region.minlong));
        xml.writeTextElement("point_name", data.at(i).point.name);
        xml.writeTextElement("point_lat", QString::number(data.at(i).point.lat));
        xml.writeTextElement("point_lon", QString::number(data.at(i).point.lon));
        xml.writeTextElement("point_h", QString::number(data.at(i).point.h));
        xml.writeTextElement("max_az", QString::number(data.at(i).maxaz));
        xml.writeTextElement("min_az", QString::number(data.at(i).minaz));
        xml.writeTextElement("max_el", QString::number(data.at(i).maxelev));
        xml.writeTextElement("min_el", QString::number(data.at(i).minelev));
        xml.writeTextElement("max_dist", QString::number(data.at(i).maxdist));
        xml.writeTextElement("min_dist", QString::number(data.at(i).mindist));
        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;
}

bool CObjFileParser::writeGbiObjIni(const QString fileName, QVector<
                                    ParamGrBaseInter> data)
{
    QString dirzap = QDir::currentPath();

    QString file_res = dirzap + "/data/" + "qkms_rezgbi.ini";
    QSettings settings(file_res, QSettings::IniFormat);
    settings.beginWriteArray("GBIobj");
    if (data.size() == 0)
        return false;
    for (int i = 0; i < data.size(); ++i)
    {

        settings.setArrayIndex(i);
        settings.setValue("region_name", data.at(i).region.name);
        settings.setValue("region_maxlat", data.at(i).region.maxlat);
        settings.setValue("region_minlat", data.at(i).region.minlat);
        settings.setValue("region_maxlon", data.at(i).region.maxlong);
        settings.setValue("region_minlon", data.at(i).region.minlong);
        settings.setValue("point_name", data.at(i).point.name);
        settings.setValue("point_lat", data.at(i).point.lat);
        settings.setValue("point_lon", data.at(i).point.lon);
        settings.setValue("point_h", data.at(i).point.h);
        settings.setValue("max_az", data.at(i).maxaz);
        settings.setValue("min_az", data.at(i).minaz);
        settings.setValue("max_el", data.at(i).maxelev);
        settings.setValue("min_el", data.at(i).minelev);
        settings.setValue("max_dist", data.at(i).maxdist);
        settings.setValue("min_dist", data.at(i).mindist);
    }
    settings.endArray();
    return true;

}
//PPI
bool CObjFileParser::writeGRRObjXml(const QString fileName, QVector<
                ParamGrContrRec> data)
{

    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

    if (data.size() == 0)
            return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
            xml.writeStartElement("GRRobj");
            xml.writeAttribute("number", "number" ? QString::number(i)
                            : QString::number(i));
//		xml.writeTextElement("region_name", data.at(i).region.name);
//		xml.writeTextElement("region_max_lat", QString::number(
//				data.at(i).region.maxlat));
//		xml.writeTextElement("region_min_lat", QString::number(
//				data.at(i).region.minlat));
//		xml.writeTextElement("region_max_lon", QString::number(
//				data.at(i).region.maxlong));
//		xml.writeTextElement("region_min_lon", QString::number(
//				data.at(i).region.minlong));
            xml.writeTextElement("point_name", data.at(i).point.name);
            xml.writeTextElement("point_lat", QString::number(data.at(i).point.lat));
            xml.writeTextElement("point_lon", QString::number(data.at(i).point.lon));
            xml.writeTextElement("point_h", QString::number(data.at(i).point.h));
            xml.writeTextElement("min_el", QString::number(data.at(i).minelev));
            xml.writeTextElement("count_tipe1", QString::number(data.at(i).tipe1));
            xml.writeTextElement("count_tipe2", QString::number(data.at(i).tipe2));
            xml.writeTextElement("count_tipe3", QString::number(data.at(i).tipe3));
            xml.writeTextElement("min_tau", QString::number(data.at(i).tauMinZPV));
            xml.writeTextElement("end", "1");
            xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;

}

bool CObjFileParser::readGrBPLAObjXml(QString fileName)
{
    ParamGrBPLA obj;
 // QVector<ParamGrContrRec> m_paramGRCObj;//!< вектор параметров ППИ
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezBPLA.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
//            facilitypoint point;//!< название и координаты БПЛА
//            double V;//!< скорость, км/ч
//            double maxH;//!< максимальная высота, км
//            double maxdist;//!< максимальная дальность, км
//            double maxTau;//!< максимальное время продолжительности полета, ч
//            double taustart;//!< время подготовки, сек
//            int type;//!< тип комплекса  !!!!!!!
//             ASDBsePar bsa;
             if (xml.name() == "point_name")
                obj.point.name = xml.readElementText();
            else if (xml.name() == "point_lat")
                obj.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "point_lon")
                obj.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "point_h")
                obj.point.h = xml.readElementText().toDouble();
            else if (xml.name() == "V")
                obj.V = xml.readElementText().toDouble();
            else if (xml.name() == "maxH")
                obj.maxH = xml.readElementText().toDouble();
            else if (xml.name() == "maxdist")
                obj.maxdist = xml.readElementText().toDouble();
            else if (xml.name() == "maxTau")
                obj.maxTau = xml.readElementText().toDouble();
            else if (xml.name() == "type")
                obj.type= xml.readElementText().toInt();

            if (obj.type == 0)
            {
             if (xml.name() == "bsa_param1")
                obj.bsas.gamma= xml.readElementText().toDouble();
            else if (xml.name() == "bsa_param2")
                obj.bsas.deltaL= xml.readElementText().toDouble();
            else if (xml.name() == "bsa_param3")
                obj.bsas.Pr= xml.readElementText().toDouble();
            }
            if (obj.type == 1)
            {
                 if (xml.name() == "bsa_param1")
                    obj.bsas.gamma= xml.readElementText().toDouble();
                else if (xml.name() == "bsa_param2")
                    obj.bsas.deltaL= xml.readElementText().toDouble();
                else if (xml.name() == "bsa_param3")
                    obj.bsas.Pr= xml.readElementText().toDouble();
                else if (xml.name() == "bsa_param4")
                    obj.bsas.alfaMounting= xml.readElementText().toDouble();

            }


            else if (xml.name() == "end")
                m_paramBPLAObj.push_back(obj);
        }

    return true;

}
bool CObjFileParser::readGrZRKObjXml(QString fileName)
{
    ParamZRV obj;
 // QVector<ParamGrContrRec> m_paramGRCObj;//!< вектор параметров ППИ
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezZRK.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
//            facilitypoint point;//!< название и координаты БПЛА
//            double V;//!< скорость, км/ч
//            double maxH;//!< максимальная высота, км
//            double maxdist;//!< максимальная дальность, км
//            double maxTau;//!< максимальное время продолжительности полета, ч
//            double taustart;//!< время подготовки, сек
//            int type;//!< тип комплекса  !!!!!!!
//             ASDBsePar bsa;
             if (xml.name() == "point_name")
                obj.point.name = xml.readElementText();
            else if (xml.name() == "point_lat")
                obj.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "point_lon")
                obj.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "point_h")
                obj.point.h = xml.readElementText().toDouble();

            else if (xml.name() == "maxH")
                obj.maxH = xml.readElementText().toDouble();
            else if (xml.name() == "maxdist")
                obj.maxdist = xml.readElementText().toDouble();
            else if (xml.name() == "taus")
                obj.taus = xml.readElementText().toDouble();
             else if (xml.name() == "freq")
                 obj.fr = xml.readElementText().toDouble();
            else if (xml.name() == "type")
                obj.type= xml.readElementText().toInt();
             else if (xml.name() == "EPR")
                 obj.EPR= xml.readElementText().toDouble();


            else if (xml.name() == "end")
                m_paramZRKObj.push_back(obj);
        }

    return true;
}
bool CObjFileParser::writeGrZRKObjXml(QString fileName,QVector<ParamZRV> data)
{
    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("ZRKobj");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));

        xml.writeTextElement("point_name", data.at(i).point.name);
        xml.writeTextElement("point_lat", QString::number(data.at(i).point.lat));
        xml.writeTextElement("point_lon", QString::number(data.at(i).point.lon));
        xml.writeTextElement("point_h", QString::number(data.at(i).point.h));
       xml.writeTextElement("maxH", QString::number(data.at(i).maxH));
      xml.writeTextElement("maxdist", QString::number(data.at(i).maxdist));
      xml.writeTextElement("taus", QString::number(data.at(i).taus));
      xml.writeTextElement("freq", QString::number(data.at(i).fr));
       xml.writeTextElement("type", QString::number(data.at(i).type));
        xml.writeTextElement("EPR", QString::number(data.at(i).EPR));
        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;

}

   bool CObjFileParser::writeGrBPLAObjXml(QString fileName,QVector<ParamGrBPLA> data)
   {
       QXmlStreamWriter xml;
       xml.setAutoFormatting(true);

       QFile file(fileName);
       if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return false;

       if (data.size() == 0)
           return false;

       xml.setDevice(&file);

       xml.writeStartDocument();
       xml.writeDTD("<!DOCTYPE xbel>");
       xml.writeStartElement("xbel");
       xml.writeAttribute("version", "1.0");

       for (int i = 0; i < data.size(); ++i)
       {
           xml.writeStartElement("BPLAobj");
           xml.writeAttribute("number", "number" ? QString::number(i)
                                                 : QString::number(i));

           xml.writeTextElement("point_name", data.at(i).point.name);
           xml.writeTextElement("point_lat", QString::number(data.at(i).point.lat));
           xml.writeTextElement("point_lon", QString::number(data.at(i).point.lon));
           xml.writeTextElement("point_h", QString::number(data.at(i).point.h));
         //  xml.writeTextElement("max_az", QString::number(data.at(i).maxaz));
         //  xml.writeTextElement("min_az", QString::number(data.at(i).minaz));
         //  xml.writeTextElement("max_el", QString::number(data.at(i).maxelev));
         //  xml.writeTextElement("min_el", QString::number(data.at(i).minelev));
        //   xml.writeTextElement("max_dist", QString::number(data.at(i).maxdist));
        //   xml.writeTextElement("min_dist", QString::number(data.at(i).mindist));
           xml.writeTextElement("end", "1");
           xml.writeEndElement();
       }
       xml.writeEndDocument();
       //
       ////	if (xml.hasError())
       ////	{
       ////		return false;
       ////	}
       //
       return true;

   }
bool CObjFileParser::readGrContrRecObjXml(QString fileName)
{
    ParamGrContrRec obj;
 // QVector<ParamGrContrRec> m_paramGRCObj;//!< вектор параметров ППИ
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezRKO.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "region_name")
                obj.region.name = xml.readElementText();
            else if (xml.name() == "region_max_lat")
                obj.region.maxlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lat")
                obj.region.minlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_max_lon")
                obj.region.maxlong = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lon")
                obj.region.minlong = xml.readElementText().toDouble();
            else if (xml.name() == "point_name")
                obj.point.name = xml.readElementText();
            else if (xml.name() == "point_lat")
                obj.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "point_lon")
                obj.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "point_h")
                obj.point.h = xml.readElementText().toDouble();
            else if (xml.name() == "min_el")
                obj.minelev = xml.readElementText().toDouble();
            else if (xml.name() == "count_tipe1")
                obj.tipe1 = xml.readElementText().toInt();
            else if (xml.name() == "count_tipe2")
                obj.tipe2 = xml.readElementText().toInt();
            else if (xml.name() == "count_tipe3")
                obj.tipe3 = xml.readElementText().toInt();
            else if (xml.name() == "min_tau")
                obj.tauMinZPV= xml.readElementText().toInt();

            else if (xml.name() == "end")
                m_paramGRRObj.push_back(obj);
        }

    return true;
}


//ОКИК
bool CObjFileParser::writeGRCObjXml(const QString fileName, QVector<
                ParamGrContrCentr> data)
{

        QXmlStreamWriter xml;
        xml.setAutoFormatting(true);

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return false;

        if (data.size() == 0)
                return false;

        xml.setDevice(&file);

        xml.writeStartDocument();
        xml.writeDTD("<!DOCTYPE xbel>");
        xml.writeStartElement("xbel");
        xml.writeAttribute("version", "1.0");

        for (int i = 0; i < data.size(); ++i)
        {
                xml.writeStartElement("GRCobj");
                xml.writeAttribute("number", "number" ? QString::number(i)
                                : QString::number(i));

                xml.writeTextElement("point_name", data.at(i).point.name);
                xml.writeTextElement("point_lat", QString::number(data.at(i).point.lat));
                xml.writeTextElement("point_lon", QString::number(data.at(i).point.lon));
                xml.writeTextElement("point_h", QString::number(data.at(i).point.h));
                xml.writeTextElement("min_el", QString::number(data.at(i).minelev));
                xml.writeTextElement("count_fazan", QString::number(data.at(i).fazan));
                xml.writeTextElement("count_cubK", QString::number(data.at(i).CubK));
                xml.writeTextElement("count_MA9", QString::number(data.at(i).MA9));
                xml.writeTextElement("count_MPRS", QString::number(data.at(i).MPRS));
                xml.writeTextElement("count_tamB", QString::number(data.at(i).TamB));
                xml.writeTextElement("min_tau", QString::number(data.at(i).tauMinZPV));
                xml.writeTextElement("end", "1");
                xml.writeEndElement();
        }
        xml.writeEndDocument();
        //
        ////	if (xml.hasError())
        ////	{
        ////		return false;
        ////	}
        //
        return true;
}

bool CObjFileParser::writeGRCObjIni(const QString fileName, QVector<
                ParamGrContrCentr> data)
{
        QString dirzap = QDir::currentPath();

        QString file_res = dirzap + "/data/" + "qkms_rezgrc.ini";
        QSettings settings(file_res, QSettings::IniFormat);
        settings.beginWriteArray("GRCobj");
        if (data.size() == 0)
                return false;
        for (int i = 0; i < data.size(); ++i)
        {

                settings.setArrayIndex(i);

                settings.setValue("point_name", data.at(i).point.name);
                settings.setValue("point_lat", data.at(i).point.lat);
                settings.setValue("point_lon", data.at(i).point.lon);
                settings.setValue("point_h", data.at(i).point.h);

                settings.setValue("min_el", data.at(i).minelev);
                settings.setValue("count_fazan", data.at(i).fazan);
                settings.setValue("count_cubK", data.at(i).CubK);
                settings.setValue("count_MA9", data.at(i).MA9);
                settings.setValue("count_MPRS", data.at(i).MPRS);
                settings.setValue("count_tamB", data.at(i).TamB);
                settings.setValue("min_tau", data.at(i).tauMinZPV);


        }
        settings.endArray();
        return true;

}

bool CObjFileParser::readGRCObjXml(QString fileName)
{
    ParamGrContrCentr obj;
 // QVector<ParamGrContrRec> m_paramGRCObj;//!< вектор параметров ППИ
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezRKO.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "region_name")
                obj.region.name = xml.readElementText();
            else if (xml.name() == "region_max_lat")
                obj.region.maxlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lat")
                obj.region.minlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_max_lon")
                obj.region.maxlong = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lon")
                obj.region.minlong = xml.readElementText().toDouble();
            else if (xml.name() == "point_name")
                obj.point.name = xml.readElementText();
            else if (xml.name() == "point_lat")
                obj.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "point_lon")
                obj.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "point_h")
                obj.point.h = xml.readElementText().toDouble();
            else if (xml.name() == "min_el")
                obj.minelev = xml.readElementText().toDouble();
            else if (xml.name() == "count_fazan")
                obj.fazan = xml.readElementText().toInt();
            else if (xml.name() == "count_cubK")
                obj.CubK = xml.readElementText().toInt();
            else if (xml.name() == "count_MA9")
                obj.MA9 = xml.readElementText().toInt();
            else if (xml.name() == "count_MPRS")
                obj.MPRS = xml.readElementText().toInt();
            else if (xml.name() == "count_tamB")
                obj.TamB = xml.readElementText().toInt();
            else if (xml.name() == "min_tau")
                obj.tauMinZPV= xml.readElementText().toInt();

            else if (xml.name() == "end")
                m_paramGRCObj.push_back(obj);
        }

    return true;
}


 bool CObjFileParser::writeAntiBallisticObjXml(const QString fileName,
                                              QVector<ASDAntiBallisticVichleParam> data)
{
    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("AntiBallisticObj");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("name", data.at(i).name);
        xml.writeTextElement("dateTimeStart", data.at(i).dateTimeStart.toString("hh:mm:ss yyyy.MM.dd"));
        xml.writeTextElement("longth", QString::number(data.at(i).longth));
        xml.writeTextElement("lat", QString::number(data.at(i).lat));
        xml.writeTextElement("MaxDist", QString::number(data.at(i).MaxDist));
        xml.writeTextElement("MinDist", QString::number(data.at(i).MinDist));
        xml.writeTextElement("Vaut", QString::number(data.at(i).Vaut));
        xml.writeTextElement("TettaAut", QString::number(data.at(i).TettaAut));
        xml.writeTextElement("TimeAut", QString::number(data.at(i).TimeAut));
        xml.writeTextElement("RangeAut", QString::number(data.at(i).RangeAut));
        xml.writeTextElement("HAut", QString::number(data.at(i).HAut));
        xml.writeTextElement("timePreparation", QString::number(data.at(i).timePreparation));

        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    return true;

}

bool CObjFileParser::writeBallisticObjXml(const QString fileName,
                                          QVector<ASDBallisticVichleParam> data)
{
    QXmlStreamWriter xml;
    xml.setAutoFormatting(true);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    if (data.size() == 0)
        return false;

    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE xbel>");
    xml.writeStartElement("xbel");
    xml.writeAttribute("version", "1.0");

    for (int i = 0; i < data.size(); ++i)
    {
        xml.writeStartElement("BallisticObj");
        xml.writeAttribute("number", "number" ? QString::number(i)
                                              : QString::number(i));
        xml.writeTextElement("name", data.at(i).name);
        xml.writeTextElement("quantityStage", QString::number(data.at(i).quantityStage));
        xml.writeTextElement("dateTimeStart", data.at(i).dateTimeStart.toString("hh:mm:ss yyyy.MM.dd"));
        xml.writeTextElement("typeTrassa", QString::number(data.at(i).typeTrassa));
        xml.writeTextElement("longth", QString::number(data.at(i).longth));
        xml.writeTextElement("lat", QString::number(data.at(i).lat));
        xml.writeTextElement("longthEnd", QString::number(data.at(i).longthEnd));
        xml.writeTextElement("latEnd", QString::number(data.at(i).latEnd));
        xml.writeTextElement("launchAzimuth", QString::number(data.at(i).launchAzimuth));
        xml.writeTextElement("massWarhead", QString::number(data.at(i).autPar.massWarhead));
        xml.writeTextElement("massFirstStage", QString::number(data.at(i).autPar.massFirstStage));
        xml.writeTextElement("massTwoStage", QString::number(data.at(i).autPar.massTwoStage));
        xml.writeTextElement("massThreeStage", QString::number(data.at(i).autPar.massThreeStage));
        xml.writeTextElement("massFuelFirstStage", QString::number(data.at(i).autPar.massFuelFirstStage));
        xml.writeTextElement("massFuelTwoStage", QString::number(data.at(i).autPar.massFuelTwoStage));
        xml.writeTextElement("massFuelThreeStage", QString::number(data.at(i).autPar.massFuelThreeStage));
        xml.writeTextElement("massSecFirstStage", QString::number(data.at(i).autPar.massSecFirstStage));
        xml.writeTextElement("massSecTwoStage", QString::number(data.at(i).autPar.massSecTwoStage));
        xml.writeTextElement("massSecThreeStage", QString::number(data.at(i).autPar.massSecThreeStage));
        xml.writeTextElement("specificImpulseEngineFirstStage", QString::number(data.at(i).autPar.specificImpulseEngineFirstStage));
        xml.writeTextElement("specificImpulseEngineTwoStage", QString::number(data.at(i).autPar.specificImpulseEngineTwoStage));
        xml.writeTextElement("specificImpulseEngineThreeStage", QString::number(data.at(i).autPar.specificImpulseEngineThreeStage));
        xml.writeTextElement("diameterRocket", QString::number(data.at(i).autPar.diameterRocket));
        xml.writeTextElement("lenghtRocket", QString::number(data.at(i).autPar.lenghtRocket));
        xml.writeTextElement("lenghFairing", QString::number(data.at(i).autPar.lenghFairing));
        xml.writeTextElement("radiusFairing", QString::number(data.at(i).autPar.radiusFairing));
        xml.writeTextElement("areaNozzleEnginesFirstStage", QString::number(data.at(i).autPar.areaNozzleEnginesFirstStage));
        xml.writeTextElement("areaNozzleEnginesTwoStage", QString::number(data.at(i).autPar.areaNozzleEnginesTwoStage));
        xml.writeTextElement("areaNozzleEnginesThreeStage", QString::number(data.at(i).autPar.areaNozzleEnginesThreeStage));
        xml.writeTextElement("timeWorkEngineFirstStage", QString::number(data.at(i).autPar.timeWorkEngineFirstStage));
        xml.writeTextElement("timeWorkEngineTwoStage", QString::number(data.at(i).autPar.timeWorkEngineTwoStage));
        xml.writeTextElement("timeWorkEngineThreeStage", QString::number(data.at(i).autPar.timeWorkEngineThreeStage));
        xml.writeTextElement("timeFullFlight", QString::number(data.at(i).autPar.timeFullFlight));
        xml.writeTextElement("integrationStepFirst", QString::number(data.at(i).autPar.integrationStepFirst));
        xml.writeTextElement("integrationStepTwo", QString::number(data.at(i).autPar.integrationStepTwo));
        xml.writeTextElement("timeVertical", QString::number(data.at(i).motionProgramPar.timeVertical));
        xml.writeTextElement("factorVertic", QString::number(data.at(i).motionProgramPar.factorVertic));
        xml.writeTextElement("angleAttack", QString::number(data.at(i).motionProgramPar.angleAttack));
        xml.writeTextElement("derTangageTwoStage", QString::number(data.at(i).motionProgramPar.derTangageTwoStage));
        xml.writeTextElement("derTangageThreeStage", QString::number(data.at(i).motionProgramPar.derTangageThreeStage));
        xml.writeTextElement("rangeMax", QString::number(data.at(i).rangeMax));
        xml.writeTextElement("range", QString::number(data.at(i).range));
        xml.writeTextElement("end", "1");
        xml.writeEndElement();
    }
    xml.writeEndDocument();
    //
    ////	if (xml.hasError())
    ////	{
    ////		return false;
    ////	}
    //
    return true;
}

//bool CObjFileParser::readOpticdefine(QString fileName)
//{
//    if (fileName.isEmpty())
//    {
//        QString dirzap = QDir::currentPath();
//        fileName = dirzap + "/data/" + "qkms_Opticdefine.xml";
//    }
//    QFile file(fileName);
//    if (!file.open(QFile::ReadOnly | QFile::Text))
//        return false;
//    QXmlStreamReader xml(&file);

//    while (!xml.atEnd())
//        if (xml.readNextStartElement())
//        {
//    //if (xml.name() == "type")
//            if (xml.name() == "end")
//            {
//               // m_paramOrbitObj.push_back(obj);
//               // obj.bsa.resize(0);
//            }

//        }

//    return true;

//}
/*
bool CObjFileParser::readOrbitObjXml(QString fileName)
{
    ASDOrbitalObjectPar obj;
    ASDBsePar bsad;

    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezorb.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "type")
                obj.type = static_cast<BseType> (xml.readElementText().toInt());
            if (xml.name() == "nameSys")
                obj.nameSys = xml.readElementText();
            if (xml.name() == "type_dat")
                obj.type_dat
                        = static_cast<InitDataType> (xml.readElementText().toInt());
            if (obj.type_dat == 0)
            {
                if (xml.name() == "name")
                    obj.kep.name = xml.readElementText();
                if (xml.name() == "epoch")
                    obj.kep.t_epoch = QDateTime::fromString(
                                xml.readElementText(), "hh:mm:ss yyyy.MM.dd");
                if (xml.name() == "a")
                    obj.kep.a = xml.readElementText().toDouble();
                if (xml.name() == "i")
                    obj.kep.i = xml.readElementText().toDouble();
                if (xml.name() == "l")
                    obj.kep.l = xml.readElementText().toDouble();
                if (xml.name() == "e")
                    obj.kep.e = xml.readElementText().toDouble();
                if (xml.name() == "omega")
                    obj.kep.omega = xml.readElementText().toDouble();
                if (xml.name() == "u")
                    obj.kep.u = xml.readElementText().toDouble();
            }
            else if (obj.type_dat == 1)
            {
                if (xml.name() == "name")
                    obj.ags.name = xml.readElementText();
                if (xml.name() == "epoch")
                    obj.ags.t_epoch = QDateTime::fromString(
                                xml.readElementText(), "hh:mm:ss yyyy.MM.dd");
                if (xml.name() == "x")
                    obj.ags.x = xml.readElementText().toDouble();
                if (xml.name() == "y")
                    obj.ags.y = xml.readElementText().toDouble();
                if (xml.name() == "z")
                    obj.ags.z = xml.readElementText().toDouble();
                if (xml.name() == "vx")
                    obj.ags.vx = xml.readElementText().toDouble();
                if (xml.name() == "vy")
                    obj.ags.vy = xml.readElementText().toDouble();
                if (xml.name() == "vz")
                    obj.ags.vz = xml.readElementText().toDouble();
            }
            else if (obj.type_dat == 2)
            {
                if (xml.name() == "name")
                    obj.stle.satName = xml.readElementText();
                if (xml.name() == "str1")
                    obj.stle.firstString = xml.readElementText();
                if (xml.name() == "str2")
                    obj.stle.secondString = xml.readElementText();
            }

            if (xml.name() == "bsa_type")
            {
                bsad.type
                        = static_cast<BseType> (xml.readElementText().toDouble());
          if(bsad.type==OERT)
          {
          bsad.param_value.resize(8);
          bsad.name_param.resize(8);
          }
          if(bsad.type==OERF)
          {
           bsad.name_param.resize(4);
           bsad.param_value.resize(4);
          }
            }
            if (xml.name() == "bsa_name")
                bsad.name = xml.readElementText();
            if (xml.name() == "bsa_gamma")
                bsad.gamma = xml.readElementText().toDouble();
            if (xml.name() == "bsa_alfaMounting")
                bsad.alfaMounting = xml.readElementText().toDouble();
            if (xml.name() == "bsa_etaMounting")
                bsad.etaMounting = xml.readElementText().toDouble();
            if (xml.name() == "bsa_betaMounting")
                bsad.betaMounting = xml.readElementText().toDouble();
            if (xml.name() == "bsa_deltaTau")
                bsad.deltaTau = xml.readElementText().toDouble();
            if (xml.name() == "bsa_deltaN")
            {
                bsad.deltaN = xml.readElementText().toDouble();
                //obj.bsa.push_back(bsad);
            }
            if (xml.name() == "bsa_deltaB")

                bsad.deltaB = xml.readElementText().toDouble();

            if (xml.name() == "bsa_deltaH")

                bsad.deltaH = xml.readElementText().toDouble();

            if (xml.name() == "bsa_deltaV")
            {
                bsad.deltaV = xml.readElementText().toDouble();

            }
            if (xml.name() == "bsa_deltaL")
            {
                bsad.deltaL = xml.readElementText().toDouble();

            }
            //       xml.writeTextElement("bsa_name_param1", QString::number(data.at(i).bsa.at(j).name_param.at(0)));
            //xml.writeTextElement("bsa_Dpar1", QString::number(data.at(i).bsa.at(j).param_value.at(0)));
            if (xml.name() == "bsa_name_param1")
            {
                    bsad.name_param[0]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar1")
            {
                    bsad.param_value[0]= xml.readElementText().toDouble();

            }
            if (xml.name() == "bsa_name_param2")
            {
                    bsad.name_param[1]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar2")
            {
                    bsad.param_value[1]= xml.readElementText().toDouble();

            }
            if (xml.name() == "bsa_name_param3")
            {
                    bsad.name_param[2]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar3")
            {
                    bsad.param_value[2]= xml.readElementText().toDouble();

            }
            if (xml.name() == "bsa_name_param4")
            {
                    bsad.name_param[3]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar4")
            {
                    bsad.param_value[3]= xml.readElementText().toDouble();
                 if(bsad.type==OERF)  obj.bsa.push_back(bsad);
            }
            if (xml.name() == "bsa_name_param5")
            {
                    bsad.name_param[4]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar5")
            {
                    bsad.param_value[4]= xml.readElementText().toDouble();

            }
            if (xml.name() == "bsa_name_param6")
            {
                    bsad.name_param[5]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar6")
            {
                    bsad.param_value[5]= xml.readElementText().toDouble();

            }
            if (xml.name() == "bsa_name_param7")
            {
                    bsad.name_param[6]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar7")
            {
                    bsad.param_value[6]= xml.readElementText().toDouble();

            }
            if (xml.name() == "bsa_name_param8")
            {
                    bsad.name_param[7]= xml.readElementText();

            }
            if (xml.name() == "bsa_Dpar8")
            {
                    bsad.param_value[7]= xml.readElementText().toDouble();
                 if(bsad.type==OERT)     obj.bsa.push_back(bsad);

            }
            //                                                // доп ОЭС
            //                                                if (xml.name() == "bsa_resonving_Power")
            //                                                {
            //                                                        bsad.resonving_Power = xml.readElementText().toDouble();

            //                                                }

            //                                                if (xml.name() == "bsa_length_line")
            //                                                {
            //                                                        bsad.length_line = xml.readElementText().toDouble();

            //                                                }
            //                                                if (xml.name() == "bsa_focus")
            //                                                {
            //                                                        bsad.focus = xml.readElementText().toDouble();

            //                                                }
            //                                                if (xml.name() == "bsa_countN_PZS")
            //                                                {
            //                                                        bsad.countN_PZS = xml.readElementText().toDouble();
            //                                                        obj.bsa.push_back(bsad);
            //                                                }



            if (xml.name() == "end")
            {
                m_paramOrbitObj.push_back(obj);
                obj.bsa.resize(0);
            }

        }

    return true;
}
*/

bool CObjFileParser::readOrbitObjXml(QString fileName)
{
    ASDOrbitalObjectPar obj;
    ASDBsePar bsad;
    // дополнительные параметры
    QVector<QString> name_param;//!< Название параметра.
    QVector<double> param_value;//!< Значение параметра.
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezorb.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "type")
                obj.type = static_cast<BseType> (xml.readElementText().toInt());
            if (xml.name() == "nameSys")
                obj.nameSys = xml.readElementText();
            if (xml.name() == "type_dat")
                obj.type_dat
                        = static_cast<InitDataType> (xml.readElementText().toInt());
            if (obj.type_dat == 0)
            {
                if (xml.name() == "name")
                    obj.kep.name = xml.readElementText();
                if (xml.name() == "epoch")
                    obj.kep.t_epoch = QDateTime::fromString(
                                xml.readElementText(), "hh:mm:ss yyyy.MM.dd");
                if (xml.name() == "a")
                    obj.kep.a = xml.readElementText().toDouble();
                if (xml.name() == "i")
                    obj.kep.i = xml.readElementText().toDouble();
                if (xml.name() == "l")
                    obj.kep.l = xml.readElementText().toDouble();
                if (xml.name() == "e")
                    obj.kep.e = xml.readElementText().toDouble();
                if (xml.name() == "omega")
                    obj.kep.omega = xml.readElementText().toDouble();
                if (xml.name() == "u")
                    obj.kep.u = xml.readElementText().toDouble();
            }
            else if (obj.type_dat == 1)
            {
                if (xml.name() == "name")
                    obj.ags.name = xml.readElementText();
                if (xml.name() == "epoch")
                    obj.ags.t_epoch = QDateTime::fromString(
                                xml.readElementText(), "hh:mm:ss yyyy.MM.dd");
                if (xml.name() == "x")
                    obj.ags.x = xml.readElementText().toDouble();
                if (xml.name() == "y")
                    obj.ags.y = xml.readElementText().toDouble();
                if (xml.name() == "z")
                    obj.ags.z = xml.readElementText().toDouble();
                if (xml.name() == "vx")
                    obj.ags.vx = xml.readElementText().toDouble();
                if (xml.name() == "vy")
                    obj.ags.vy = xml.readElementText().toDouble();
                if (xml.name() == "vz")
                    obj.ags.vz = xml.readElementText().toDouble();
            }
            else if (obj.type_dat == 2)
            {
                if (xml.name() == "name")
                    obj.stle.satName = xml.readElementText();
                if (xml.name() == "str1")
                    obj.stle.firstString = xml.readElementText();
                if (xml.name() == "str2")
                    obj.stle.secondString = xml.readElementText();
            }

            if (xml.name() == "bsa_type")
                bsad.type
                        = static_cast<BseType> (xml.readElementText().toInt());
            if (xml.name() == "bsa_name")
                bsad.name = xml.readElementText();
            if (xml.name() == "bsa_gamma")
                bsad.gamma = xml.readElementText().toDouble();
            if (xml.name() == "bsa_alfaMounting")
                bsad.alfaMounting = xml.readElementText().toDouble();
            if (xml.name() == "bsa_etaMounting")
                bsad.etaMounting = xml.readElementText().toDouble();
            if (xml.name() == "bsa_betaMounting")
                bsad.betaMounting = xml.readElementText().toDouble();
            if (xml.name() == "bsa_deltaTau")
                bsad.deltaTau = xml.readElementText().toDouble();
            if (xml.name() == "bsa_deltaN")
            {
                bsad.deltaN = xml.readElementText().toDouble();
                //  obj.bsa.push_back(bsad);

                //qDebug()<<"ooooooo OERT";
            }
            if (xml.name() == "bsa_deltaL")
                 bsad.deltaL = xml.readElementText().toDouble();
            if (xml.name() == "bsa_deltaVr")
                 bsad.deltaVr = xml.readElementText().toDouble();
            if (xml.name() == "bsa_skor")
                 bsad.skor = xml.readElementText().toDouble();
            if (xml.name() == "bsa_Pr")
                 bsad.Pr = xml.readElementText().toDouble();
            if (xml.name() == "bsa_fmem")
                 bsad.fmem = xml.readElementText().toDouble();
            //xml.writeTextElement("bsa_deltaVr", QString::number(data.at(i).bsa.at(j).deltaVr));
           //xml.writeTextElement("bsa_skor", QString::number(data.at(i).bsa.at(j).skor));
           // xml.writeTextElement("bsa_Pr", QString::number(data.at(i).bsa.at(j).Pr));
          // xml.writeTextElement("bsa_fmem", QString::number(data.at(i).bsa.at(j).fmem));

            if(bsad.type==OERT)
            {
                name_param.resize(8);
                param_value.resize(8);
                if (xml.name() == "bsa_name_param1")
                    name_param[0]=xml.readElementText();
                if (xml.name() == "bsa_Dpar1")
                    param_value [0]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param2")
                    name_param[1]=xml.readElementText();
                if (xml.name() == "bsa_Dpar2")
                    param_value [1]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param3")
                    name_param[2]=xml.readElementText();
                if (xml.name() == "bsa_Dpar3")
                    param_value [2]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param4")
                    name_param[3]=xml.readElementText();
                if (xml.name() == "bsa_Dpar4")
                    param_value [3]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param5")
                    name_param[4]=xml.readElementText();
                if (xml.name() == "bsa_Dpar5")
                    param_value [4]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param6")
                    name_param[5]=xml.readElementText();
                if (xml.name() == "bsa_Dpar6")
                    param_value [5]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param7")
                    name_param[6]=xml.readElementText();
                if (xml.name() == "bsa_Dpar7")
                    param_value [6]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param8")
                    name_param[7]=xml.readElementText();
                if (xml.name() == "bsa_Dpar8")
                {

                    param_value [7]= xml.readElementText().toDouble();
                    bsad.name_param=name_param;
                    bsad.param_value=param_value;
                    obj.bsa.push_back(bsad);
                    qDebug()<<"oert 1"<<param_value [1];
                     qDebug()<<"oert 2"<<param_value [2];
                }
            }
            if(bsad.type==OERF)
            {
                name_param.resize(4);
                param_value.resize(4);
                if (xml.name() == "bsa_name_param1")
                    name_param[0]=xml.readElementText();
                if (xml.name() == "bsa_Dpar1")
                    param_value [0]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param2")
                    name_param[1]=xml.readElementText();
                if (xml.name() == "bsa_Dpar2")
                    param_value [1]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param3")
                    name_param[2]=xml.readElementText();
                if (xml.name() == "bsa_Dpar3")
                    param_value [2]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param4")
                    name_param[3]=xml.readElementText();
                if (xml.name() == "bsa_Dpar4")
                {
                    param_value [3]= xml.readElementText().toDouble();
                    bsad.name_param=name_param;
                    bsad.param_value=param_value;
                    obj.bsa.push_back(bsad);
                }
            }

            if(bsad.type==RLRF)
            {
                name_param.resize(7);
                param_value.resize(7);
                if (xml.name() == "bsa_name_param1")
                    name_param[0]=xml.readElementText();
                if (xml.name() == "bsa_Dpar1")
                    param_value [0]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param2")
                    name_param[1]=xml.readElementText();
                if (xml.name() == "bsa_Dpar2")
                    param_value [1]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param3")
                    name_param[2]=xml.readElementText();
                if (xml.name() == "bsa_Dpar3")
                    param_value [2]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param4")
                    name_param[3]=xml.readElementText();
                if (xml.name() == "bsa_Dpar4")
                    param_value [3]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param5")
                    name_param[4]=xml.readElementText();
                if (xml.name() == "bsa_Dpar5")
                    param_value [4]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param6")
                    name_param[5]=xml.readElementText();
                if (xml.name() == "bsa_Dpar6")
                    param_value [5]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param7")
                    name_param[6]=xml.readElementText();
                if (xml.name() == "bsa_Dpar7")
                {
                    param_value [6]= xml.readElementText().toDouble();
                    bsad.name_param=name_param;
                    bsad.param_value=param_value;
                    obj.bsa.push_back(bsad);
                }
            }
            //sbyazya
            if(bsad.type==COMMUNICATION)
            {
                name_param.resize(8);
                param_value.resize(8);
                if (xml.name() == "bsa_name_param1")
                    name_param[0]=xml.readElementText();
                if (xml.name() == "bsa_Dpar1")
                    param_value [0]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param2")
                    name_param[1]=xml.readElementText();
                if (xml.name() == "bsa_Dpar2")
                    param_value [1]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param3")
                    name_param[2]=xml.readElementText();
                if (xml.name() == "bsa_Dpar3")
                    param_value [2]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param4")
                    name_param[3]=xml.readElementText();
                if (xml.name() == "bsa_Dpar4")
                    param_value [3]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param5")
                    name_param[4]=xml.readElementText();
                if (xml.name() == "bsa_Dpar5")
                    param_value [4]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param6")
                    name_param[5]=xml.readElementText();
                if (xml.name() == "bsa_Dpar6")
                    param_value [5]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param7")
                    name_param[6]=xml.readElementText();
                if (xml.name() == "bsa_name_param8")
                    name_param[7]=xml.readElementText();
                if (xml.name() == "bsa_Dpar8")
                {
                    param_value [7]= xml.readElementText().toDouble();
                    bsad.name_param=name_param;
                    bsad.param_value=param_value;
                    obj.bsa.push_back(bsad);
                }
            }
//rtr
            if(bsad.type==RTR)
            {
                name_param.resize(5);
                param_value.resize(5);
                if (xml.name() == "bsa_name_param1")
                    name_param[0]=xml.readElementText();
                if (xml.name() == "bsa_Dpar1")
                    param_value [0]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param2")
                    name_param[1]=xml.readElementText();
                if (xml.name() == "bsa_Dpar2")
                    param_value [1]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param3")
                    name_param[2]=xml.readElementText();
                if (xml.name() == "bsa_Dpar3")
                    param_value [2]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param4")
                    name_param[3]=xml.readElementText();
                if (xml.name() == "bsa_Dpar4")
                    param_value [3]= xml.readElementText().toDouble();
                if (xml.name() == "bsa_name_param5")
                    name_param[4]=xml.readElementText();
                if (xml.name() == "bsa_Dpar5")

                {
                    param_value [4]= xml.readElementText().toDouble();
                    bsad.name_param=name_param;
                    bsad.param_value=param_value;
                    obj.bsa.push_back(bsad);
                }
            }

            //endrtr
            //			if (xml.name() == "bsa_deltaB")
            //			{
            //				bsad.deltaB = xml.readElementText().toDouble();
            //				obj.bsa.push_back(bsad);
            //			}

            //                        else if (xml.name() == "endOBJ")
            //                            vobj.append(opt);

            //                        else if (xml.name() == "end")

            //                        {
            //                            if(vobj.size()>0) obj.vecOBJ=vobj;
            //                                m_paramRegionObj.push_back(obj);
            //                                vobj.resize(0);


            //                        }

            if (xml.name() == "end")
            {
                if(bsad.type==OER)
                 {
                     name_param.resize(0);
                     param_value.resize(0);
                     bsad.name_param=name_param;
                     bsad.param_value=param_value;
                     obj.bsa.push_back(bsad);

                 }

                m_paramOrbitObj.push_back(obj);
                obj.bsa.resize(0);
                obj.bsa.clear();
            }

        }

    return true;
}

bool CObjFileParser::readOrbitObjIni(QString fileName)
{
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezorb.ini";
    }

    QSettings settings(fileName, QSettings::IniFormat);

    int size = settings.beginReadArray("orbitobj");
    if (size <= 0)
        return false;

    for (int i = 0; i < size; ++i)
    {
        ASDBsePar bsad;
        ASDOrbitalObjectPar obj;

        settings.setArrayIndex(i);

        obj.type = static_cast<BseType> (settings.value("type").toInt());

        obj.nameSys = settings.value("nameSys").toString();

        obj.type_dat
                = static_cast<InitDataType> (settings.value("type_dat").toInt());
        if (obj.type_dat == 0)
        {

            obj.kep.name = settings.value("name").toString();

            obj.kep.t_epoch = settings.value("epoch").toDateTime();

            obj.kep.a = settings.value("a").toDouble();
            obj.kep.i = settings.value("i").toDouble();
            obj.kep.l = settings.value("l").toDouble();
            obj.kep.e = settings.value("e").toDouble();
            obj.kep.omega = settings.value("omega").toDouble();
            obj.kep.u = settings.value("u").toDouble();

        }
        if (obj.type_dat == 1)
        {
            obj.ags.name = settings.value("name").toString();
            obj.ags.t_epoch = settings.value("epoch").toDateTime();
            obj.ags.x = settings.value("x").toDouble();
            obj.ags.y = settings.value("y").toDouble();
            obj.ags.z = settings.value("z").toDouble();
            obj.ags.vx = settings.value("vx").toDouble();
            obj.ags.vy = settings.value("vy").toDouble();
            obj.ags.vz = settings.value("vz").toDouble();

        }
        if (obj.type_dat == 2)
        {
            obj.stle.satName = settings.value("name").toString();
            obj.stle.firstString = settings.value("str1").toString();
            obj.stle.secondString = settings.value("str2").toString();

        }

        //for(int j=0;j<)
        {
            bsad.type
                    = static_cast<BseType> (settings.value("bsa_type").toInt());
            bsad.name = settings.value("bsa_name").toString();
            bsad.gamma = settings.value("bsa_gamma").toDouble();
            bsad.alfaMounting = settings.value("bsa_alfaMounting").toDouble();
            bsad.etaMounting = settings.value("bsa_etaMounting").toDouble();
            bsad.betaMounting = settings.value("bsa_betaMounting").toDouble();
            bsad.deltaTau = settings.value("bsa_deltaTau").toDouble();//deltaN
            bsad.deltaN = settings.value("bsa_deltaN").toDouble();
            bsad.deltaB = settings.value("bsa_deltaB").toDouble();
            bsad.deltaH = settings.value("bsa_deltaH").toDouble();
            bsad.deltaV = settings.value("bsa_deltaV").toDouble();
            bsad.deltaL = settings.value("bsa_deltaL").toDouble();

            //                        // доп ОЭС
            //                         bsad.resonving_Power = settings.value("bsa_resonving_Power").toDouble();
            //                         bsad.length_line = settings.value("bsa_length_line").toDouble();
            //                         bsad.focus = settings.value("bsa_focus").toDouble();
            //                         bsad.countN_PZS = settings.value("bsa_countN_PZS").toDouble();

            obj.bsa.push_back(bsad);
        }
        m_paramOrbitObj.push_back(obj);

    }
    settings.endArray();
    return true;

}

bool CObjFileParser::readOrbitObjTle(QString fileName)
{

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return (false);
    }

    QFileInfo fileInfo(fileName);

    QString lineTLE;
    QTextStream fileTLE(&file);

    ASDOrbitalObjectPar obj;

    while (!fileTLE.atEnd())
    {
        lineTLE = fileTLE.readLine();

        //если длинна строки 24 то это имя
        if (lineTLE.length() <= 24)
        {
            obj.type = COMMUNICATION;
            obj.nameSys = fileInfo.baseName();
            obj.type_dat = TLE;
            int ml=24;
            if(lineTLE.length()<24) ml=lineTLE.length();
            obj.stle.satName = lineTLE.mid(0, ml);
        }

        //чтение первой строки с параметрами
        lineTLE = fileTLE.readLine();
        if ((!lineTLE.isEmpty()) && (isValidLineTLE(lineTLE)))
        {
            obj.stle.firstString = lineTLE;
        }
        //чтение второй строки с параметрами
        lineTLE = fileTLE.readLine();
        if ((!lineTLE.isEmpty()) && (isValidLineTLE(lineTLE)))
        {
            obj.stle.secondString = lineTLE;
            m_paramOrbitObj.push_back(obj);
        }
    }

    file.close();
    return true;
}

bool CObjFileParser::readRkoObjXml(QString fileName)
{
    ParamGrBaseInter obj;

    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezRKO.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "region_name")
                obj.region.name = xml.readElementText();
            else if (xml.name() == "region_max_lat")
                obj.region.maxlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lat")
                obj.region.minlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_max_lon")
                obj.region.maxlong = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lon")
                obj.region.minlong = xml.readElementText().toDouble();
            else if (xml.name() == "point_name")
                obj.point.name = xml.readElementText();
            else if (xml.name() == "point_lat")
                obj.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "point_lon")
                obj.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "point_h")
                obj.point.h = xml.readElementText().toDouble();
            else if (xml.name() == "max_az")
                obj.maxaz = xml.readElementText().toDouble();
            else if (xml.name() == "min_az")
                obj.minaz = xml.readElementText().toDouble();
            else if (xml.name() == "max_el")
                obj.maxelev = xml.readElementText().toDouble();
            else if (xml.name() == "min_el")
                obj.minelev = xml.readElementText().toDouble();
            else if (xml.name() == "max_dist")
                obj.maxdist = xml.readElementText().toDouble();
            else if (xml.name() == "min_dist")
                obj.mindist = xml.readElementText().toDouble();
            else if (xml.name() == "tauselect")
                obj.tauselect = xml.readElementText().toDouble();
            else if (xml.name() == "end")
                m_paramRkoObj.push_back(obj);
        }

    return true;
}

bool CObjFileParser::readRkoObjIni(QString fileName)
{
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezRKO.ini";
    }

    QSettings settings(fileName, QSettings::IniFormat);

    int size = settings.beginReadArray("RKOobj");
    if (size <= 0)
        return false;

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        ParamGrBaseInter obj;
        obj.region.name = settings.value("region_name").toString();
        obj.region.maxlat = settings.value("region_maxlat").toDouble();
        obj.region.minlat = settings.value("region_minlat").toDouble();
        obj.region.maxlong = settings.value("region_maxlon").toDouble();
        obj.region.minlong = settings.value("region_minlon").toDouble();
        obj.point.name = settings.value("point_name").toString();
        obj.point.lat = settings.value("point_lat").toDouble();
        obj.point.lon = settings.value("point_lon").toDouble();
        obj.point.h = settings.value("point_hmax_az").toDouble();
        obj.maxaz = settings.value("max_az").toDouble();
        obj.minaz = settings.value("min_az").toDouble();
        obj.minelev = settings.value("min_el").toDouble();

        obj.maxelev = settings.value("max_el").toDouble();
        obj.maxdist = settings.value("max_dist").toDouble();
        obj.mindist = settings.value("min_dist").toDouble();
        obj.tauselect = settings.value("tauselect").toDouble();

        m_paramRkoObj.push_back(obj);

    }
    settings.endArray();
    return true;

}
    bool CObjFileParser::readRegionOObjXml(QString fileName)
    {
        ParamregionO obj;

        if (fileName.isEmpty())
        {
            QString dirzap = QDir::currentPath();
            fileName = dirzap + "/data/" + "qkms_rezreg.xml";
        }

        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            return false;
        QXmlStreamReader xml(&file);

        while (!xml.atEnd())
            if (xml.readNextStartElement())
            {
                if (xml.name() == "name")
                    obj.name = xml.readElementText();
                else if (xml.name() == "mlat")
                    obj.mlat = xml.readElementText().toDouble();
                else if (xml.name() == "dllat")
                    obj.dllat = xml.readElementText().toDouble();
                else if (xml.name() == "mlong")
                    obj.mlong = xml.readElementText().toDouble();
                else if (xml.name() == "dllon")
                    obj.dllon = xml.readElementText().toDouble();
                else if (xml.name() == "countR")
                    obj.countR = xml.readElementText().toInt();
                else if (xml.name() == "type")
                    obj.type = xml.readElementText().toInt();
                else if (xml.name() == "ldir")
                    obj.ldir = xml.readElementText().toDouble();
                else if (xml.name() == "end")
                    m_paramRegionO.push_back(obj);
            }

        return true;

    }

bool CObjFileParser::readRegionObjXml(QString fileName)
{
    Paramregion obj;

    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezreg.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "name")
                obj.name = xml.readElementText();
            else if (xml.name() == "max_lat")
                obj.maxlat = xml.readElementText().toDouble();
            else if (xml.name() == "min_lat")
                obj.minlat = xml.readElementText().toDouble();
            else if (xml.name() == "max_long")
                obj.maxlong = xml.readElementText().toDouble();
            else if (xml.name() == "min_long")
                obj.minlong = xml.readElementText().toDouble();
            else if (xml.name() == "end")
                m_paramRegion.push_back(obj);
        }

    return true;
}

bool CObjFileParser::readRegionObjNXml(QString fileName)
{
    ParamregionOBJ obj;
    ParamOBJOPTIC opt;
    QVector<ParamOBJOPTIC> vobj;
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezreg_obj.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "name")
                obj.name = xml.readElementText();
            else if (xml.name() == "max_lat")
                obj.maxlat = xml.readElementText().toDouble();
            else if (xml.name() == "min_lat")
                obj.minlat = xml.readElementText().toDouble();
            else if (xml.name() == "max_long")
                obj.maxlong = xml.readElementText().toDouble();
            else if (xml.name() == "min_long")
                obj.minlong = xml.readElementText().toDouble();
            //
            else if (xml.name() == "NameOBJ")
                opt.name= xml.readElementText();

            // points point; //!< координаты  объекта
            else if (xml.name() == "LatOBJ")
                opt.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "LonOBJ")
                opt.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "hOBJ")
                opt.point.h = xml.readElementText().toDouble();
            else if (xml.name() == "HOBJ")
                opt.HObj= xml.readElementText().toDouble();
            else if (xml.name() == "LengtOBJ")
                opt.LengthObj= xml.readElementText().toDouble();
            else if (xml.name() == "WidthOBJ")
                opt.WidthObj= xml.readElementText().toDouble();
            else if (xml.name() == "type_Obj")
                opt.type_Obj= xml.readElementText().toInt();
            else if (xml.name() == "type_M")
                opt.type_M= xml.readElementText().toInt();
             else if (xml.name() == "LumL04")
                opt.lumL04= xml.readElementText().toFloat();
            else if (xml.name() == "LumL05")
                opt.lumL05= xml.readElementText().toFloat();

            else if (xml.name() == "LumL06")
                opt.lumL06= xml.readElementText().toFloat();

            else if (xml.name() == "LumL07")
                opt.lumL07= xml.readElementText().toFloat();

            else if (xml.name() == "LumL08")
                opt.lumL08= xml.readElementText().toFloat();

            else if (xml.name() == "LumL09")
                opt.lumL09= xml.readElementText().toFloat();
            else if (xml.name() == "type_PP")
                opt.type_PP= xml.readElementText().toInt();
            else if (xml.name() == "type_VV")
                opt.type_VV= xml.readElementText().toInt();
            else if (xml.name() == "type_CL")
                opt.type_CL= xml.readElementText().toInt();


            else if (xml.name() == "endOBJ")
                vobj.append(opt);

            else if (xml.name() == "end")

            {
                if(vobj.size()>0) obj.vecOBJ=vobj;
                m_paramRegionObj.push_back(obj);
                vobj.resize(0);


            }


            //

        }

    return true;
}


bool CObjFileParser::readRegionObjIni(QString fileName)
{
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezreg_obj.ini";
    }

    QSettings settings(fileName, QSettings::IniFormat);
    int size = settings.beginReadArray("RegobjN");
    if (size <= 0)
        return false;

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        Paramregion obj;

        obj.name = settings.value("name").toString();
        obj.maxlat = settings.value("maxlat").toDouble();
        obj.minlat = settings.value("minlat").toDouble();
        obj.maxlong = settings.value("maxlong").toDouble();
        obj.minlong = settings.value("minlong").toDouble();
        m_paramRegion.push_back(obj);
    }

    return true;
}


bool CObjFileParser::readRegionObjNIni(QString fileName)
{
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezreg_obj.ini";
    }

    QSettings settings(fileName, QSettings::IniFormat);
    int size = settings.beginReadArray("RegobjN");
    if (size <= 0)
        return false;

    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        ParamregionOBJ obj;

        obj.name = settings.value("name").toString();
        obj.maxlat = settings.value("maxlat").toDouble();
        obj.minlat = settings.value("minlat").toDouble();
        obj.maxlong = settings.value("maxlong").toDouble();
        obj.minlong = settings.value("minlong").toDouble();
        m_paramRegionObj.push_back(obj);
    }

    return true;
}
bool CObjFileParser::readLbiObjXml(QString fileName)
{
    ParamGrBaseInter obj;

    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezLBI.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "region_name")
                obj.region.name = xml.readElementText();
            else if (xml.name() == "region_max_lat")
                obj.region.maxlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lat")
                obj.region.minlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_max_lon")
                obj.region.maxlong = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lon")
                obj.region.minlong = xml.readElementText().toDouble();
            else if (xml.name() == "point_name")
                obj.point.name = xml.readElementText();
            else if (xml.name() == "point_lat")
                obj.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "point_lon")
                obj.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "point_h")
                obj.point.h = xml.readElementText().toDouble();
            else if (xml.name() == "max_az")
                obj.maxaz = xml.readElementText().toDouble();
            else if (xml.name() == "min_az")
                obj.minaz = xml.readElementText().toDouble();
            else if (xml.name() == "max_el")
                obj.maxelev = xml.readElementText().toDouble();
            else if (xml.name() == "min_el")
                obj.minelev = xml.readElementText().toDouble();
            else if (xml.name() == "max_dist")
                obj.maxdist = xml.readElementText().toDouble();
            else if (xml.name() == "min_dist")
                obj.mindist = xml.readElementText().toDouble();
            else if (xml.name() == "end")
                m_paramLbiObj.push_back(obj);
        }

    return true;
}

bool CObjFileParser::readLbiObjIni(QString fileName)
{
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezLBI.ini";
    }

    QSettings settings(fileName, QSettings::IniFormat);
    int size = settings.beginReadArray("LBIobj");
    if (size <= 0)
        return false;
    // data.insert()
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        ParamGrBaseInter obj;
        obj.region.name = settings.value("region_name").toString();
        obj.region.maxlat = settings.value("region_maxlat").toDouble();
        obj.region.minlat = settings.value("region_minlat").toDouble();
        obj.region.maxlong = settings.value("region_maxlon").toDouble();
        obj.region.minlong = settings.value("region_minlon").toDouble();
        obj.point.name = settings.value("point_name").toString();
        obj.point.lat = settings.value("point_lat").toDouble();
        obj.point.lon = settings.value("point_lon").toDouble();
        obj.point.h = settings.value("point_h").toDouble();
        obj.maxaz = settings.value("max_az").toDouble();
        obj.minaz = settings.value("min_az").toDouble();
        obj.minelev = settings.value("min_el").toDouble();

        obj.maxelev = settings.value("max_el").toDouble();
        obj.maxdist = settings.value("max_dist").toDouble();
        obj.mindist = settings.value("min_dist").toDouble();
        m_paramLbiObj.push_back(obj);

    }
    settings.endArray();
    return true;

}

bool CObjFileParser::readGbiObjXml(QString fileName)
{
    ParamGrBaseInter obj;

    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezGBI.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "region_name")
                obj.region.name = xml.readElementText();
            else if (xml.name() == "region_max_lat")
                obj.region.maxlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lat")
                obj.region.minlat = xml.readElementText().toDouble();
            else if (xml.name() == "region_max_lon")
                obj.region.maxlong = xml.readElementText().toDouble();
            else if (xml.name() == "region_min_lon")
                obj.region.minlong = xml.readElementText().toDouble();
            else if (xml.name() == "point_name")
                obj.point.name = xml.readElementText();
            else if (xml.name() == "point_lat")
                obj.point.lat = xml.readElementText().toDouble();
            else if (xml.name() == "point_lon")
                obj.point.lon = xml.readElementText().toDouble();
            else if (xml.name() == "point_h")
                obj.point.h = xml.readElementText().toDouble();
            else if (xml.name() == "max_az")
                obj.maxaz = xml.readElementText().toDouble();
            else if (xml.name() == "min_az")
                obj.minaz = xml.readElementText().toDouble();
            else if (xml.name() == "max_el")
                obj.maxelev = xml.readElementText().toDouble();
            else if (xml.name() == "min_el")
                obj.minelev = xml.readElementText().toDouble();
            else if (xml.name() == "max_dist")
                obj.maxdist = xml.readElementText().toDouble();
            else if (xml.name() == "min_dist")
                obj.mindist = xml.readElementText().toDouble();
            else if (xml.name() == "end")
                m_paramGbiObj.push_back(obj);
        }

    return true;
}

bool CObjFileParser::readGbiObjIni(QString fileName)
{
    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_rezGBI.ini";
    }

    QSettings settings(fileName, QSettings::IniFormat);
    int size = settings.beginReadArray("GBIobj");
    if (size <= 0)
        return false;
    // data.insert()
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        ParamGrBaseInter obj;
        obj.region.name = settings.value("region_name").toString();
        obj.region.maxlat = settings.value("region_maxlat").toDouble();
        obj.region.minlat = settings.value("region_minlat").toDouble();
        obj.region.maxlong = settings.value("region_maxlon").toDouble();
        obj.region.minlong = settings.value("region_minlon").toDouble();
        obj.point.name = settings.value("point_name").toString();
        obj.point.lat = settings.value("point_lat").toDouble();
        obj.point.lon = settings.value("point_lon").toDouble();
        obj.point.h = settings.value("point_h").toDouble();
        obj.maxaz = settings.value("max_az").toDouble();
        obj.minaz = settings.value("min_az").toDouble();
        obj.minelev = settings.value("min_el").toDouble();

        obj.maxelev = settings.value("max_el").toDouble();
        obj.maxdist = settings.value("max_dist").toDouble();
        obj.mindist = settings.value("min_dist").toDouble();
        m_paramGbiObj.push_back(obj);

    }
    settings.endArray();
    return true;

}

bool CObjFileParser::readAntiBallisticObjXml(QString fileName)
{
    ASDAntiBallisticVichleParam obj;

    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_antiballistic.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "name")
                obj.name = xml.readElementText();

            else if (xml.name() == "dateTimeStart")
                obj.dateTimeStart = QDateTime::fromString(
                            xml.readElementText(), "hh:mm:ss yyyy.MM.dd");
            else if (xml.name() == "longth")
                obj.longth = xml.readElementText().toDouble();
            else if (xml.name() == "lat")
                obj.lat = xml.readElementText().toDouble();

            else if (xml.name() == "MaxDist")
                obj.MaxDist = xml.readElementText().toDouble();

            else if (xml.name() == "MinDist")
                obj.MinDist = xml.readElementText().toDouble();
            else if (xml.name() == "Vaut")
                obj.Vaut = xml.readElementText().toDouble();

            else if (xml.name() == "TettaAut")
                obj.TettaAut = xml.readElementText().toDouble();
            else if (xml.name() == "TimeAut")
                obj.TimeAut = xml.readElementText().toDouble();

            else if (xml.name() == "RangeAut")
                obj.RangeAut = xml.readElementText().toDouble();

            else if (xml.name() == "HAut")
                obj.HAut = xml.readElementText().toDouble();
            else if (xml.name() == "timePreparation")
                obj.timePreparation = xml.readElementText().toDouble();
            else if (xml.name() == "end")
                m_paramAntiBallisticVichle.push_back(obj);

        }

    return true;

}

bool CObjFileParser::readBallisticObjXml(QString fileName)
{
    ASDBallisticVichleParam obj;

    if (fileName.isEmpty())
    {
        QString dirzap = QDir::currentPath();
        fileName = dirzap + "/data/" + "qkms_ballistic.xml";
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
        if (xml.readNextStartElement())
        {
            if (xml.name() == "name")
                obj.name = xml.readElementText();
            else if (xml.name() == "quantityStage")
                obj.quantityStage = xml.readElementText().toInt();
            else if (xml.name() == "dateTimeStart")
                obj.dateTimeStart = QDateTime::fromString(
                            xml.readElementText(), "hh:mm:ss yyyy.MM.dd");
            else if (xml.name() == "typeTrassa")
                obj.typeTrassa = xml.readElementText().toInt();
            else if (xml.name() == "longth")
                obj.longth = xml.readElementText().toDouble();
            else if (xml.name() == "lat")
                obj.lat = xml.readElementText().toDouble();
            else if (xml.name() == "longthEnd")
                obj.longthEnd = xml.readElementText().toDouble();
            else if (xml.name() == "latEnd")
                obj.latEnd = xml.readElementText().toDouble();
            else if (xml.name() == "launchAzimuth")
                obj.launchAzimuth = xml.readElementText().toDouble();
            else if (xml.name() == "massWarhead")
                obj.autPar.massWarhead = xml.readElementText().toDouble();
            else if (xml.name() == "massFirstStage")
                obj.autPar.massFirstStage = xml.readElementText().toDouble();
            else if (xml.name() == "massTwoStage")
                obj.autPar.massTwoStage = xml.readElementText().toDouble();
            else if (xml.name() == "massThreeStage")
                obj.autPar.massThreeStage = xml.readElementText().toDouble();
            else if (xml.name() == "massFuelFirstStage")
                obj.autPar.massFuelFirstStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "massFuelTwoStage")
                obj.autPar.massFuelTwoStage = xml.readElementText().toDouble();
            else if (xml.name() == "massFuelThreeStage")
                obj.autPar.massFuelThreeStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "massSecFirstStage")
                obj.autPar.massSecFirstStage = xml.readElementText().toDouble();
            else if (xml.name() == "massSecTwoStage")
                obj.autPar.massSecTwoStage = xml.readElementText().toDouble();
            else if (xml.name() == "massSecThreeStage")
                obj.autPar.massSecThreeStage = xml.readElementText().toDouble();
            else if (xml.name() == "specificImpulseEngineFirstStage")
                obj.autPar.specificImpulseEngineFirstStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "specificImpulseEngineTwoStage")
                obj.autPar.specificImpulseEngineTwoStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "specificImpulseEngineThreeStage")
                obj.autPar.specificImpulseEngineThreeStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "diameterRocket")
                obj.autPar.diameterRocket = xml.readElementText().toDouble();
            else if (xml.name() == "lenghtRocket")
                obj.autPar.lenghtRocket = xml.readElementText().toDouble();
            else if (xml.name() == "lenghFairing")
                obj.autPar.lenghFairing = xml.readElementText().toDouble();
            else if (xml.name() == "radiusFairing")
                obj.autPar.radiusFairing = xml.readElementText().toDouble();
            else if (xml.name() == "areaNozzleEnginesFirstStage")
                obj.autPar.areaNozzleEnginesFirstStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "areaNozzleEnginesTwoStage")
                obj.autPar.areaNozzleEnginesTwoStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "areaNozzleEnginesThreeStage")
                obj.autPar.areaNozzleEnginesThreeStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "timeWorkEngineFirstStage")
                obj.autPar.timeWorkEngineFirstStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "timeWorkEngineTwoStage")
                obj.autPar.timeWorkEngineTwoStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "timeWorkEngineThreeStage")
                obj.autPar.timeWorkEngineThreeStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "timeFullFlight")
                obj.autPar.timeFullFlight = xml.readElementText().toDouble();
            else if (xml.name() == "integrationStepFirst")
                obj.autPar.integrationStepFirst
                        = xml.readElementText().toDouble();
            else if (xml.name() == "integrationStepTwo")
                obj.autPar.integrationStepTwo
                        = xml.readElementText().toDouble();
            else if (xml.name() == "timeVertical")
                obj.motionProgramPar.timeVertical
                        = xml.readElementText().toDouble();
            else if (xml.name() == "factorVertic")
                obj.motionProgramPar.factorVertic
                        = xml.readElementText().toDouble();
            else if (xml.name() == "angleAttack")
                obj.motionProgramPar.angleAttack
                        = xml.readElementText().toDouble();
            else if (xml.name() == "derTangageTwoStage")
                obj.motionProgramPar.derTangageTwoStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "derTangageThreeStage")
                obj.motionProgramPar.derTangageThreeStage
                        = xml.readElementText().toDouble();
            else if (xml.name() == "rangeMax")
                obj.rangeMax = xml.readElementText().toDouble();
            else if (xml.name() == "range")
                obj.range = xml.readElementText().toDouble();
            else if (xml.name() == "end")
                m_paramBallisticVichle.push_back(obj);
        }

    return true;
}

bool CObjFileParser::isValidLineTLE(const QString& line)
{
    int cs = 0;
    for (int i = 0; i < line.length() - 1; i++)
    {
        if (line[i].isDigit())
        {
            cs += line[i].digitValue();
        }
        else if (line[i] == '-')
        {
            cs++;
        }
    }
    cs %= 10;//последняя цифра получившейся суммы
    return (cs == line[line.length() - 1].digitValue());
}

