#ifndef SATELLITEGAMMACONFIG_H
#define SATELLITEGAMMACONFIG_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

/**
 * @brief Структура для хранения параметров группы спутников
 */
struct SatelliteGroupConfig
{
    QString name;              // Название группы (например, "Иридиум")
    QString pattern;           // Регулярное выражение для поиска в имени спутника
    double orbit_altitude;     // Высота орбиты (км)
    double gamma;              // Угол радиовидимости (градусы)
    QString description;       // Описание группы

    SatelliteGroupConfig()
        : orbit_altitude(0.0), gamma(0.0) {}
};

/**
 * @brief Класс для загрузки и применения конфигурации gamma из XML
 */
class SatelliteGammaConfig
{
public:
    SatelliteGammaConfig();

    /**
     * @brief Загрузить конфигурацию из XML-файла
     * @param filename Путь к XML-файлу
     * @return true если загрузка успешна
     */
    bool loadFromXML(const QString& filename);

    /**
     * @brief Получить gamma для спутника по имени
     * @param satelliteName Имя спутника (из TLE)
     * @param altitude_km Высота орбиты (для автоматического расчета если не найдено)
     * @return Угол gamma в градусах
     */
    double getGammaForSatellite(const QString& satelliteName, double altitude_km) const;

    /**
     * @brief Получить информацию о группе спутника
     * @param satelliteName Имя спутника
     * @return Указатель на конфигурацию группы или nullptr если не найдено
     */
    const SatelliteGroupConfig* findSatelliteGroup(const QString& satelliteName) const;

    /**
     * @brief Получить список всех загруженных групп
     */
    QVector<SatelliteGroupConfig> getAllGroups() const { return m_groups; }

    /**
     * @brief Рассчитать геометрический gamma из высоты орбиты
     * @param altitude_km Высота орбиты в км
     * @return gamma в градусах
     */
    static double calculateGeometricGamma(double altitude_km);

    /**
     * @brief Проверить, загружена ли конфигурация
     */
    bool isLoaded() const { return m_loaded; }

private:
    QVector<SatelliteGroupConfig> m_groups;
    bool m_loaded;

    void parseSatelliteGroup(QXmlStreamReader& xml);
};

#endif // SATELLITEGAMMACONFIG_H
