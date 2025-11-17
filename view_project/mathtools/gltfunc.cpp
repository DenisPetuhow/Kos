#include "gltfunc.h"

void gltRotateVector(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vOut)
{
    vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4] * vSrcVector[1] + mMatrix[8] *  vSrcVector[2];
    vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5] * vSrcVector[1] + mMatrix[9] *  vSrcVector[2];
    vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6] * vSrcVector[1] + mMatrix[10] * vSrcVector[2];
}

void gltScaleVector(GLTVector3 vVector, const GLfloat fScale)
{
    vVector[0] *= fScale; vVector[1] *= fScale; vVector[2] *= fScale;
}

void gltNormalizeVector(GLTVector3 vNormal)
{
    GLfloat fLength = 1.0f / gltGetVectorLength(vNormal);
    gltScaleVector(vNormal, fLength);
}

GLfloat gltGetVectorLength(const GLTVector3 vVector)
{
    return (GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
}

GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector)
{
    return (vVector[0]*vVector[0]) + (vVector[1]*vVector[1]) + (vVector[2]*vVector[2]);
}

void gltRotationMatrix(float angle, float x, float y, float z, GLTMatrix mMatrix)
{
    float vecLength, sinSave, cosSave, oneMinusCos;
    float xx, yy, zz, xy, yz, zx, xs, ys, zs;

    // If NULL vector passed in, this will blow up...
    if(x == 0.0f && y == 0.0f && z == 0.0f)
    {
        gltLoadIdentityMatrix(mMatrix);
        return;
    }

    // Scale vector
    vecLength = (float)sqrt( x*x + y*y + z*z );

    // Rotation matrix is normalized
    x /= vecLength;
    y /= vecLength;
    z /= vecLength;

    sinSave = (float)sin(angle);
    cosSave = (float)cos(angle);
    oneMinusCos = 1.0f - cosSave;

    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * sinSave;
    ys = y * sinSave;
    zs = z * sinSave;

    mMatrix[0] = (oneMinusCos * xx) + cosSave;
    mMatrix[4] = (oneMinusCos * xy) - zs;
    mMatrix[8] = (oneMinusCos * zx) + ys;
    mMatrix[12] = 0.0f;

    mMatrix[1] = (oneMinusCos * xy) + zs;
    mMatrix[5] = (oneMinusCos * yy) + cosSave;
    mMatrix[9] = (oneMinusCos * yz) - xs;
    mMatrix[13] = 0.0f;

    mMatrix[2] = (oneMinusCos * zx) - ys;
    mMatrix[6] = (oneMinusCos * yz) + xs;
    mMatrix[10] = (oneMinusCos * zz) + cosSave;
    mMatrix[14] = 0.0f;

    mMatrix[3] = 0.0f;
    mMatrix[7] = 0.0f;
    mMatrix[11] = 0.0f;
    mMatrix[15] = 1.0f;
}

void gltLoadIdentityMatrix(GLTMatrix m)//функция загрузки единичной матрицы
{
    static GLTMatrix identity = { 1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f };

    memcpy(m, identity, sizeof(GLTMatrix));//копирует из переданного массива матрицы в единичную всю матрицу
}

void gltGetMatrixFromFrame(GLTFrame *pFrame, GLTMatrix mMatrix)
{
    GLTVector3 vXAxis;       // Derived X Axis

    // Calculate X Axis
    gltVectorCrossProduct(pFrame->vUp, pFrame->vForward, vXAxis);

    // Just populate the matrix
    // X column vector
    memcpy(mMatrix, vXAxis, sizeof(GLTVector3));
    mMatrix[3] = 0.0f;

    // y column vector
    memcpy(mMatrix+4, pFrame->vUp, sizeof(GLTVector3));
    mMatrix[7] = 0.0f;

    // z column vector
    memcpy(mMatrix+8, pFrame->vForward, sizeof(GLTVector3));
    mMatrix[11] = 0.0f;

    // Translation/Location vector
    memcpy(mMatrix+12, pFrame->vLocation, sizeof(GLTVector3));
    mMatrix[15] = 1.0f;
}

//восстанавливает единичный вектор Х матрицы по имеющимся векторам у(вверх) и Z(вперед)
void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult)
{
    vResult[0] = vU[1]*vV[2] - vV[1]*vU[2];
    vResult[1] = -vU[0]*vV[2] + vV[0]*vU[2];
    vResult[2] = vU[0]*vV[1] - vV[0]*vU[1];
}

void gltRotateFrameLocalY(GLTFrame *pFrame, GLfloat fAngle)
{
    GLTMatrix mRotation;
    GLTVector3 vNewForward;

    gltRotationMatrix(fAngle, 0.0f, 1.0f, 0.0f, mRotation);
    gltRotationMatrix(fAngle, pFrame->vUp[0], pFrame->vUp[1], pFrame->vUp[2], mRotation);

    gltRotateVector(pFrame->vForward, mRotation, vNewForward);
    memcpy(pFrame->vForward, vNewForward, sizeof(GLTVector3));
}

//сдвигаем систему отсчета вперед на переданную величину шага
void gltMoveFrameUp(GLTFrame *pFrame, GLfloat fStep)
{
    //if(pFrame->vLocation[1]<-7)pFrame->vLocation[1]=-7;
    //if(pFrame->vLocation[1]>7)pFrame->vLocation[1]=7;
    pFrame->vLocation[0] += pFrame->vUp[0] * fStep;
    pFrame->vLocation[1] += pFrame->vUp[1] * fStep;
    pFrame->vLocation[2] += pFrame->vUp[2] * fStep;
}

void gltMoveFrameForward(GLTFrame *pFrame, GLfloat fStep)
{
    pFrame->vLocation[0] += pFrame->vForward[0] * fStep;
    pFrame->vLocation[1] += pFrame->vForward[1] * fStep;
    pFrame->vLocation[2] += pFrame->vForward[2] * fStep;
}

void gltMoveFrameLeft(GLTFrame *pFrame, GLfloat fStep)
{

    GLTVector3 vAxisX;
    GLTVector3 zFlipped;

    zFlipped[0] = -pFrame->vForward[0];
    zFlipped[1] = -pFrame->vForward[1];
    zFlipped[2] = -pFrame->vForward[2];

    // Derive X vector
    gltVectorCrossProduct(pFrame->vUp, zFlipped, vAxisX);


    //if(pFrame->vLocation[0]<-7)pFrame->vLocation[0]=-7;
    //if(pFrame->vLocation[0]>7)pFrame->vLocation[0]=7;
    pFrame->vLocation[0] += vAxisX[0] * fStep;
    pFrame->vLocation[1] += vAxisX[1] * fStep;
    pFrame->vLocation[2] += vAxisX[2]* fStep;
}



void gltInitFrame(GLTFrame *pFrame)//инициализация системы отсчета сферы-актера или камеры
{
    //точка начала координат
    pFrame->vLocation[0] = 0.0f;//х
    pFrame->vLocation[1] = 0.0f;//у
    pFrame->vLocation[2] = 0.0f;//z

    //направление вверх - ось у (координаты точки единичного вектора на этой оси)
    pFrame->vUp[0] = 0.0f;//х
    pFrame->vUp[1] = 1.0f;//у
    pFrame->vUp[2] = 0.0f;//z

    //направление вперед - ось z (координаты точки единичного вектора на этой оси)
    pFrame->vForward[0] = 0.0f;//х
    pFrame->vForward[1] = 0.0f;//у
    pFrame->vForward[2] = -1.0f;//z
}

void gltApplyActorTransform(GLTFrame *pFrame)
{
    GLTMatrix mTransform;
    gltGetMatrixFromFrame(pFrame, mTransform);
    glMultMatrixf(mTransform);
}

void gltApplyCameraTransform(GLTFrame *pCamera)
{
    GLTMatrix mMatrix;
    GLTVector3 vAxisX;
    GLTVector3 zFlipped;

    zFlipped[0] = -pCamera->vForward[0];
    zFlipped[1] = -pCamera->vForward[1];
    zFlipped[2] = -pCamera->vForward[2];

    // Derive X vector
    gltVectorCrossProduct(pCamera->vUp, zFlipped, vAxisX);//вычисляет ось Х

    // Populate matrix, note this is just the rotation and is transposed
    mMatrix[0] = vAxisX[0];
    mMatrix[4] = vAxisX[1];
    mMatrix[8] = vAxisX[2];
    mMatrix[12] = 0.0f;

    mMatrix[1] = pCamera->vUp[0];
    mMatrix[5] = pCamera->vUp[1];
    mMatrix[9] = pCamera->vUp[2];
    mMatrix[13] = 0.0f;

    mMatrix[2] = zFlipped[0];
    mMatrix[6] = zFlipped[1];
    mMatrix[10] = zFlipped[2];
    mMatrix[14] = 0.0f;

    mMatrix[3] = 0.0f;
    mMatrix[7] = 0.0f;
    mMatrix[11] = 0.0f;
    mMatrix[15] = 1.0f;

    // Do the rotation first
    glMultMatrixf(mMatrix);

    // Now, translate backwards
    glTranslatef(-pCamera->vLocation[0], -pCamera->vLocation[1], -pCamera->vLocation[2]);
}
