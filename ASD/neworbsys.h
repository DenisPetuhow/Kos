#ifndef NEWORBSYS_H
#define NEWORBSYS_H

#include <QtCore>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QHeaderView>
#include <QTableView>
#include <QVBoxLayout>
#include <QtGui>
#include <QVector>
#include "ASD/objfileparser.h"
//#include <QWhatsThis>
/**
 * @file cossysobj.h
 * форма для формирование системы КА
 * Выходные данные формируются в виде вектора
 * cо структурами ASDOrbitalObjectPar(см. structureswidget.h)
 */
class CNewOrbSys: public QDialog
{
    Q_OBJECT

public:
    CNewOrbSys(QWidget* parent);
    QVector<ASDOrbitalObjectPar> list_obj;
    ~CNewOrbSys();

private slots:
    virtual void accept();
    void formsys();
    void formviewplot();
    void setdatpl();
    void setdatKApl();
    void setdatKAplz();
    //void setdatKASUN();
    void    editTs();
private:
    QGroupBox* grsvdPL;
    QGroupBox* grsvdKA;
    QLineEdit* _namesys;
    QSpinBox* _kolplosk;
    QSpinBox* _npl;
    QSpinBox* _nKApl;
    QSpinBox* _kolKA_v_plosk;
    QDateTimeEdit* _dattim;
    QDoubleSpinBox* _LVU;
    QDoubleSpinBox* _naklon;
    QDoubleSpinBox* _H;
    QDoubleSpinBox* _E;
    QDoubleSpinBox* _Per;
    QDoubleSpinBox* _svdpl;
    QDoubleSpinBox* _svdKA;
    QDoubleSpinBox* _svdperKA;
    QTableView * tableView;
    QPushButton* _buttonCancel;
    QPushButton* _buttonOK;
    QPushButton* _buttonformThis;
    QPushButton* _buttonViewThis;
    QCheckBox *radioButton_pavn;
    QCheckBox *radioButton_pavn1;
    QCheckBox *radioButton_sun;
    QLabel* Lvit;
    QStringList sender;

    QGroupBox* BSA;
    QComboBox* typeBSA;
    QDoubleSpinBox* Gamma;
    QDoubleSpinBox* Gamma1;
    QDoubleSpinBox* Lz;
    QDoubleSpinBox* Pz;
    QLabel* labg1;
    QLabel* labg2;
    void formstruct();
    void loaddat(int k, double* lon, double* lat, double* a1, double* e1,
                 double* l1, double* u1, double* w1, double* nakl1, double* M1);
};

#endif // CREATEORBITSYS_H
