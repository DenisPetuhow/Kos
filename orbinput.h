#ifndef ORBINPUT_H
#define ORBINPUT_H

#include <QtGui>
#include <QVector>
#include <QFileDialog>

#include "ASD/neworbobj.h"
#include "ASD/neworbsys.h"
#include "ASD/objfileparser.h"

#include "ASD/asdtype.h"

#include "ui_orbinput.h"


class COrbInput: public QWidget, public Ui_OrbInputClass
{
    Q_OBJECT
    
public:
    //! \brief Конструктор по умолчанию.
    COrbInput(QWidget *parent = 0);
    
    //! \brief Деструктор по умолчанию.
    ~COrbInput();
    
    /*!
     * \brief Возвращает итоговый вектор параметров КО.
     */
    QVector<ASDOrbitalObjectPar> getOrbitalObjectPar();
    
public slots:
    /*!
     * \brief Слот для добавления нового объекта.
     */
    void createOrbitObj();
    
    /*!
     * \brief Слот для добавления новой системы космических объектов.
     */
    void createSystemOrbitObj();
    
    /*!
     * \brief Загрузить параметры орбитальных объектов из XML или INI файла.
     */
    void loadOrbitObjFile();
    
    /*!
     * \brief Загрузить параметры по умолчанию из файла.
     */
    void loadDefaultParam(QString strFile);
    
    /*!
     * \brief Сохранить параметры выбранных орбитальных объектов в XML файл.
     */
    void saveOrbitObjFile();
    
    /*!
     * \brief Слот для вставки параметров выделенного элемента  из списка
     * орбитальных объектов в формируюмый список для расчетов.
     */
    void addOrbitObj();
    
    /*!
     * \brief Слот для удаления выделенного объекта из формируемого списка средств.
     */
    void delOrbitObj();
    
    /*!
     * \brief Слот для вставки параметров выделенного элемента  из treeWidget_sysKA
     * в таблицу параметров объекта tableWidget_par.
     */
    void findParamKA();
    
    /*!
     * \brief Слот заполняет список установленной бортовой аппаратурой.
     */
    void fillListWidgetBsk();
    
    /*!
     * \brief Отображает параметры бортовой аппаратуры в таблице.
     */
    void viewParamBsk();
    
    /*!
     * \brief Добавить параметры бортовой аппаратуры.
     */
    void addParamBsa();
    
    /*!
     * \brief Изменить параметры бортовой аппаратуры.
     */
    void editParamBsa();
    
    /*!
     * \brief Удаляет параметры бортовой аппаратуры.
     */
    void delParamBsa();
    
    /*!
     * \brief Сохранить параметры бортовой аппаратуры.
     */
    void saveParamBsa();
    
protected:
    QVector<ASDOrbitalObjectPar> tempv_obj;//!< внутренний вектор параметров КО.
    
private:
    bool m_flagBsa; //!< Флаг редактирования параметров бортовой аппаратуры. 0 - добавление, 1 - изменение.
    QVector<ASDOrbitalObjectPar> m_selectOrbitObj;//!< итоговый вектор параметров КО.
};

#endif // ORBINPUT_H
