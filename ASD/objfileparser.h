#ifndef OBJFILEPARSER_H
#define OBJFILEPARSER_H

#include <QString>
#include <QDateTime>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QTextCodec>
#include <QtXml/qxml.h>
#include <QDebug>

#include <string>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <QDir>

#include "ASD/asdtype.h"

class QMessageBox;

using namespace std;

/*!
 * \brief класс для формирования данных моделирования
 */
class CObjFileParser
{
public:
	//! \brief Конструктор по умолчанию.
	CObjFileParser();

	/*!
	 * \brief Сохранение в XML файле параметров орбиты и установленной аппаратуры
	 * для орбитального объекта.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами орбитальных объектов.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeOrbitObjXml(const QString fileName, const QVector<
			ASDOrbitalObjectPar> data);

	/*!
	 * \brief Сохранение в INI файле параметров орбиты и установленной аппаратуры
	 * для орбитального объекта.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами орбитальных объектов.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeOrbitObjIni(const QString fileName, const QVector<
			ASDOrbitalObjectPar> data);

	/*!
	 * \brief Сохранение в XML файле параметров объекта наблюдения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами объектов наблюдения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeRkoObjXml(const QString fileName, const QVector<
			ParamGrBaseInter> data);

	/*!
	 * \brief Сохранение в INI файле параметров объекта наблюдения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами объектов наблюдения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeRkoObjIni(const QString fileName, const QVector<
			ParamGrBaseInter> data);

	/*!
	 * \brief Сохранение в XML файле параметров районов наблюдения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами районов наблюдения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeRegionObjXml(const QString fileName, const QVector<
			Paramregion> data);
    bool writeRegionOObjXml(const QString fileName, const QVector<
            ParamregionO> data);

	/*!
	 * \brief Сохранение в INI файле параметров районов наблюдения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами районов наблюдения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	static bool writeRegionObjIni(const QString fileName, const QVector<
			Paramregion> data);

        /*!
         * \brief Сохранение в XML файле параметров районов наблюдения с объектами..
         *
         * \param fileName - имя файла с параметрами.
         * \param data - вектор с параметрами районов наблюдения.
         * \return 0 если произошла ошибка во время записи.
         */
        bool writeRegionObjNXml(const QString fileName, const QVector<
                        ParamregionOBJ> data);

        /*!
         * \brief Сохранение в INI файле параметров районов наблюдения с объектами.
         *
         * \param fileName - имя файла с параметрами.
         * \param data - вектор с параметрами районов наблюдения.
         * \return 0 если произошла ошибка во время записи.
         */
        static bool writeRegionObjNIni(const QString fileName, const QVector<
                        ParamregionOBJ> data);

	/*!
	 * \brief Сохранение в XML файле параметров лазерного комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами лазерного комплекса поражения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeLbiObjXml(const QString fileName,
			QVector<ParamGrBaseInter> data);

	/*!
	 * \brief Сохранение в INI файле параметров лазерного комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами лазерного комплекса поражения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeLbiObjIni(const QString fileName,
			QVector<ParamGrBaseInter> data);

	/*!
	 * \brief Сохранение в XML файле параметров кинетического комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами кинетического комплекса поражения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeGbiObjXml(const QString fileName,
			QVector<ParamGrBaseInter> data);

	/*!
	 * \brief Сохранение в INI файле параметров кинетического комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами кинетического комплекса поражения.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeGbiObjIni(const QString fileName,
			QVector<ParamGrBaseInter> data);

	/*!
	 * \brief Сохранение в XML файле параметров баллистчекого объекта.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \param data - вектор с параметрами баллистического объекта.
	 * \return 0 если произошла ошибка во время записи.
	 */
	bool writeBallisticObjXml(const QString fileName,
                        QVector<ASDBallisticVichleParam> data);

        /*!
         * \brief Сохранение в XML файле параметров противобаллистического объекта.
         *
         * \param fileName - имя файла с параметрами.
         * \param data - вектор с параметрами баллистического объекта.
         * \return 0 если произошла ошибка во время записи.
         */
        bool writeAntiBallisticObjXml(const QString fileName,
                        QVector<ASDAntiBallisticVichleParam> data);
        bool writeGRCObjXml(const QString fileName, QVector<
                        ParamGrContrCentr> data);
        bool writeGRCObjIni(const QString fileName, QVector<ParamGrContrCentr> data);

        bool writeGRRObjXml(const QString fileName, QVector<
                        ParamGrContrRec> data);
	/*!
	 * \brief Чтение из XML файла  параметров орбиты и установленной аппаратуры
	 * для орбитального объекта.
	 *
	 * \param fileName - имя файла с параметрами.
	 * \return 0 если произошла ошибка во время чтениня.
	 */
	bool readOrbitObjXml(QString fileName);

	/*!
	 * \brief Чтение из INI файла  параметров орбиты и установленной аппаратуры
	 * для орбитального объекта.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return 0 если произошла ошибка во время чтениня.
	 */
	bool readOrbitObjIni(QString fileName);

	/*!
	 * \brief Чтение из TLE файла  параметров орбиты и установленной аппаратуры
	 * для орбитального объекта.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return 0 если произошла ошибка во время чтениня.
	 */
	bool readOrbitObjTle(QString fileName);
	/*!
	 * \brief Чтение из XML файла  параметров объекта наблюдения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readRkoObjXml(QString fileName);

	/*!
	 * \brief Чтение из INI файла  параметров объекта наблюдения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readRkoObjIni(QString fileName);

	/*!
	 * \brief Чтение из XML файла  параметров районов наблюдения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readRegionObjXml(QString fileName);

    bool readRegionOObjXml(QString fileName);
	/*!
	 * \brief Чтение из INI файла  параметров районов наблюдения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readRegionObjIni(QString fileName);

        /*!
         * \brief Чтение из XML файла  параметров районов наблюдения c параметрами объектов.
         *
         * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
         * \return
         */
        bool readRegionObjNXml(QString fileName);

        /*!
         * \brief Чтение из INI файла  параметров районов наблюдения c параметрами объектов.
         *
         * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
         * \return
         */
        bool readRegionObjNIni(QString fileName);


	/*!
	 * \brief Чтение из XML файла  параметров лазерного комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readLbiObjXml(QString fileName);

	/*!
	 * \brief Чтение из INI файла  параметров лазерного комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readLbiObjIni(QString fileName);

	/*!
	 * \brief Чтение из XML файла  параметров кинетического комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readGbiObjXml(QString fileName);

	/*!
	 * \brief Чтение из INI файла  параметров кинетического комплекса поражения.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readGbiObjIni(QString fileName);

	/*!
	 * \brief Чтение из XML файла параметров баллистического объекта.
	 *
	 * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
	 * \return
	 */
	bool readBallisticObjXml(QString fileName);
        /*!
         * \brief Чтение из XML файла параметров противобаллистического объекта.
         *
         * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
         * \return
         */
        bool readAntiBallisticObjXml(QString fileName);
        /*!
         * \brief Чтение из XML файла параметров ППИ.
         *
         * \param fileName - имя файла с параметрами (если имя пустое то берется файл по умолчанию).
         * \return
         */
        bool readGrContrRecObjXml(QString fileName);
        bool readGRCObjXml(QString fileName);
        bool readGrBPLAObjXml(QString fileName);
        bool writeGrBPLAObjXml(QString fileName,QVector<ParamGrBPLA> data);
        bool readGrZRKObjXml(QString fileName);
        bool writeGrZRKObjXml(QString fileName,QVector<ParamZRV> data);



private:
	/*!
	 * \brief Проверка на правильность TLE строки.
	 *
	 * \param line - строка из файла.
	 * \return 1 если строка правильная, 0 - если не правильная
	 */
	bool isValidLineTLE( const QString& line );


public:

	QVector<ASDOrbitalObjectPar> m_paramOrbitObj;//!< Вектор параметров космического объекта.
	QVector<ParamGrBaseInter> m_paramRkoObj;//!< Вектор параметров информационного средства.
	QVector<ParamGrBaseInter> m_paramLbiObj;//!< Вектор параметров лазерного комплекса поражения.
	QVector<ParamGrBaseInter> m_paramGbiObj;//!< вектор параметров комплекса поражения
	QVector<Paramregion> m_paramRegion;//!< Вектор параметров района наблюдения.
    QVector<ParamregionO> m_paramRegionO;//!< Вектор параметров района наблюдения.
        QVector<ParamregionOBJ> m_paramRegionObj;//!< Вектор параметров района наблюдения с параметроами объектов.
        QVector<ParamGrContrCentr> m_paramGRCObj;//!< вектор параметров ОКИК
        QVector<ParamGrContrRec> m_paramGRRObj;//!< вектор параметров ППИ
        QVector<ASDAntiBallisticVichleParam> m_paramAntiBallisticVichle;//!< Вектор параметров района наблюдения.
        QVector<ASDBallisticVichleParam> m_paramBallisticVichle;//!< Вектор параметров района наблюдения.
        QVector<ParamGrBPLA> m_paramBPLAObj;//!< Вектор параметров района наблюдения.
         QVector<ParamZRV> m_paramZRKObj;//!< Вектор параметров ЗРК.




};

#endif // OBJFILEPARSER_H
