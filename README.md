# Лабораторная работа № 2 
## 1) Изучение и написание матриц перемещения, вращения и изменения размера объекта:
### Инициализация переменной для изменения 
```с++
float Scale = 0.0f;
```
### Задание самих матриц
```с++
    //матрица перемещения
    glm::mat4 movingMat{
    1.0f, 0.0f,  0.0f, 0.0f,
    0.0f, 1.0f,  0.0f, 0.0f,
    0.0f, 0.0f,  1.0f, 0.0f,
    sinf(Scale), 0.0f, 0.0f, 1.0f
    };

    //Матрица вращения
   glm::mat4 rotationMat{
    cosf(Scale),  sinf(Scale), 0.0f, 0.0f,
    -sinf(Scale), cosf(Scale), 0.0f, 0.0f,
     0.0f,        0.0f,        1.0f, 0.0f,
     0.0f,        0.0f,        0.0f, 1.0f
    };

    //Матрица изменения масштаба
    glm::mat4 conversMat{
     abs(sinf(Scale)), 0.0f, 0.0f, 0.0f,
     0.0f, abs(cosf(Scale)), 0.0f, 0.0f,
     0.0f, 0.0f, abs(sinf(Scale)), 0.0f,
     0.0f, 0.0f, 0.0f, 1.0f
     };
    // Изменение при каждом обновлении экрана 
     Scale += 0.001f;
``` 
## 2) Проекция перспективы
### инициализвция необходимых переменных
```с++
const float zF = 1.0f;
const float zN = 100.0f;
const float zR = zN - zF;
const float fov = 90.0f;
const float tanhalfFOV = tanf(glm::radians(fov / 2));
```
###  Задание матрицы перспективы
```с++
glm::mat4 perspectMat{
        1.0f / (tanhalfFOV * 1024/ 768), 0.0f,             0.0f, 0.0f,
        0.0f,                1.0f / tanhalfFOV,      0.0f, 0.0f,
        0.0f, 0.0f,          (-zN - zF) / zR,  2.0f * zF * zN / zR,
        0.0f, 0.0f,          1.0f,              0.0f
    };
```
## 3) Пространство камеры
###  Задание позиции и базиса камеры
```с++
 glm::vec3 cameraPos = glm::vec3(0.3f, 0.3f, 0.3f);

 glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
 glm::vec3 cameraTarget = glm::vec3(0.45f, 0.0f, 1.0f);
 glm::vec3 cameraRight = glm::cross(cameraUp, cameraTarget);
```
###  Задание матрицы изменения позиции камеры
```с++
glm::mat4 camTransfMat{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
       -cameraPos.x, -cameraPos.y, -cameraPos.z, 1.0f,
    };
```
### Необходимые преобразования для вращения камеры и задание самой матрицы вращения
```с++
glm::vec3 N = cameraTarget;
    N = glm::normalize(N);
    glm::vec3 U = cameraUp;
    U = glm::normalize(U);
    U = glm::cross(U, cameraTarget);
    glm::vec3 V = glm::cross(N, U);
    
    glm::mat4 camRotationMat;
    camRotationMat[0][0] = U.x; camRotationMat[0][1] = U.y; camRotationMat[0][2] = U.z; camRotationMat[0][3] = 0.0f;
    camRotationMat[1][0] = V.x; camRotationMat[1][1] = V.y; camRotationMat[1][2] = V.z; camRotationMat[1][3] = 0.0f;
    camRotationMat[2][0] = N.x; camRotationMat[2][1] = N.y; camRotationMat[2][2] = N.z; camRotationMat[2][3] = 0.0f;
    camRotationMat[3][0] = 0.0f; camRotationMat[3][1] = 0.0f; camRotationMat[3][2] = 0.0f; camRotationMat[3][3] = 1.0f;
```
## 4) Применение всех преобразований
```с++
glm::mat4 WorldMat2 = perspectMat * camRotationMat * camTransfMat * conversMat * rotationMat * movingMat * WorldMat;
     glLoadMatrixf(static_cast<const float*>(glm::value_ptr(WorldMat2)));
```

