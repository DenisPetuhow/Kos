#ifndef GLTFUNC_H
#define GLTFUNC_H

#include <math.h>
#include <GL/glu.h>

//функции используются в 3d сцене

typedef GLfloat GLTVector3[3];//вектор из 3 значений столбца
typedef GLfloat GLTMatrix[16];//Матрица 4х4
typedef struct{               // используется в матрице 4х4 - начало координат, направление вверх, направление вперед
    GLTVector3 vLocation;
    GLTVector3 vUp;
    GLTVector3 vForward;
} GLTFrame;

/*!
     * \brief Инициализация системы отсчета.
     * \param pFrame структура параметров системы отсчета
     */
void gltInitFrame(GLTFrame *pFrame);

/*!
     * \brief создание матрицы трансформации для системы отсчета камеры и перемножение на текущую матрицу
     * \param pCamera структура параметров системы отсчета камеры
     */
void gltApplyCameraTransform(GLTFrame *pCamera);

/*!
     * \brief создание матрицы трансформации для системы отсчета объекта (Земли) и перемножение на текущую матрицу
     * \param pFrame структура параметров системы отсчета объекта (Земли)
     */
void gltApplyActorTransform(GLTFrame *pFrame);

/*!
     * \brief Сдвигание системы отсчета вверх
     * \param pFrame структура параметров системы отсчета объекта
     * \param fStep шаг сдвигания
     */
void gltMoveFrameUp(GLTFrame *pFrame, GLfloat fStep);

/*!
     * \brief Сдвигание системы отсчета вперед
     * \param pFrame структура параметров системы отсчета объекта
     * \param fStep шаг сдвигания
     */
void gltMoveFrameForward(GLTFrame *pFrame, GLfloat fStep);

/*!
     * \brief Сдвигание системы отсчета вбок
     * \param pFrame структура параметров системы отсчета объекта
     * \param fStep шаг сдвигания
     */
void gltMoveFrameLeft(GLTFrame *pFrame, GLfloat fStep);

/*!
     * \brief Вращение системы отсчета относительно оси Y
     * \param pFrame структура параметров системы отсчета объекта
     * \param fAngle угол поворота
     */
void gltRotateFrameLocalY(GLTFrame *pFrame, GLfloat fAngle);

/*!
     * \brief Нормализация вектора
     * \param vNormal нормализуемый вектор
     */
void gltNormalizeVector(GLTVector3 vNormal);

/*!
     * \brief вращение вектора
     * \param vSrcVector исходный вектор
     * \param mMatrix матрица вращения
     * \param vPointOut итоговый вектор
     */
void gltRotateVector(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vPointOut);

/*!
     * \brief Вычисление длины вектора
     * \param vVector измеряемый вектор
     * \return значение длины вектора
     */
GLfloat gltGetVectorLength(const GLTVector3 vVector);

/*!
     * \brief Вычисление длины вектора в квадрате
     * \param vVector измеряемый вектор
     * \return значение длины вектора в квадрате
     */
GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector);

/*!
     * \brief умножение вектора на скаляр
     * \param vVector изменяемый вектор
     * \param скалярная величина
     */
void gltScaleVector(GLTVector3 vVector, const GLfloat fScale);

/*!
     * \brief векторное произведение (по векторам направлений вверх и вперед получаем вектор по оси Х)
     * \param vU вектор направления вверх
     * \param vV вектор направления вперед
     * \param vResult результирующий вектор (по оси Х)
     */
void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult);

/*!
     * \brief формируем матрицу поворота
     * \param angle угол поворота
     * \param x значение по оси Х
     * \param y значение по оси У
     * \param z значение по оси Z
     * \param mMatrix итоговая матрица поворота
     */
void gltRotationMatrix(float angle, float x, float y, float z, GLTMatrix mMatrix);

/*!
     * \brief загрузка единичной матрицы
     * \param m матрица, в которую загружается единичная матрица
     */
void gltLoadIdentityMatrix(GLTMatrix m);

/*!
     * \brief формируем матрицу из системы отсчета
     * \param pFrame структура, содержащая данные по системе отсчета
     * \param mMatrix итоговая матрица
     */
void gltGetMatrixFromFrame(GLTFrame *pFrame, GLTMatrix mMatrix);

#endif // GLTFUNC_H
