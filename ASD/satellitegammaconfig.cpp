#include "satellitegammaconfig.h"
#include "asdconst.h"
#include <cmath>

SatelliteGammaConfig::SatelliteGammaConfig()
    : m_loaded(false)
{
}

bool SatelliteGammaConfig::loadFromXML(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Не удалось открыть файл конфигурации gamma:" << filename;
        return false;
    }

    QXmlStreamReader xml(&file);
    m_groups.clear();

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "satellite_group")
            {
                parseSatelliteGroup(xml);
            }
        }
    }

    if (xml.hasError())
    {
        qWarning() << "Ошибка парсинга XML:" << xml.errorString();
        file.close();
        return false;
    }

    file.close();
    m_loaded = true;

    qDebug() << "Загружено" << m_groups.size() << "групп спутников из конфигурации gamma";
    return true;
}

void SatelliteGammaConfig::parseSatelliteGroup(QXmlStreamReader& xml)
{
    SatelliteGroupConfig group;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "satellite_group"))
    {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            QString elementName = xml.name().toString();

            if (elementName == "name")
            {
                group.name = xml.readElementText();
            }
            else if (elementName == "pattern")
            {
                group.pattern = xml.readElementText();
            }
            else if (elementName == "orbit_altitude")
            {
                group.orbit_altitude = xml.readElementText().toDouble();
            }
            else if (elementName == "gamma")
            {
                group.gamma = xml.readElementText().toDouble();
            }
            else if (elementName == "description")
            {
                group.description = xml.readElementText();
            }
        }

        xml.readNext();
    }

    if (!group.name.isEmpty() && !group.pattern.isEmpty() && group.gamma > 0)
    {
        m_groups.append(group);
        qDebug() << "  Загружена группа:" << group.name
                 << "| pattern:" << group.pattern
                 << "| gamma:" << group.gamma << "°";
    }
}

const SatelliteGroupConfig* SatelliteGammaConfig::findSatelliteGroup(const QString& satelliteName) const
{
    if (satelliteName.isEmpty())
        return nullptr;

    // Поиск по регулярному выражению
    for (const SatelliteGroupConfig& group : m_groups)
    {
        QRegularExpression regex(group.pattern, QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch match = regex.match(satelliteName);

        if (match.hasMatch())
        {
            return &group;
        }
    }

    return nullptr;
}

double SatelliteGammaConfig::getGammaForSatellite(const QString& satelliteName, double altitude_km) const
{
    // Попытка найти в конфигурации
    const SatelliteGroupConfig* group = findSatelliteGroup(satelliteName);

    if (group != nullptr)
    {
        qDebug() << "КА" << satelliteName << "→ группа:" << group->name
                 << "| gamma:" << group->gamma << "° (из конфигурации)";
        return group->gamma;
    }

    // Если не найдено - автоматический расчет
    double gamma_auto = calculateGeometricGamma(altitude_km);
    qDebug() << "КА" << satelliteName << "→ gamma:" << gamma_auto
             << "° (автоматический расчет, h=" << altitude_km << "км)";
    return gamma_auto;
}

double SatelliteGammaConfig::calculateGeometricGamma(double altitude_km)
{
    if (altitude_km <= 0)
        altitude_km = 500.0; // По умолчанию

    double gamma_rad = asin(R_EARTH / (R_EARTH + altitude_km));
    double gamma_deg = gamma_rad * RAD_TO_DEG;

    return gamma_deg;
}
