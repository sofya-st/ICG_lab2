

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO;
float Scale = 0.0f;


static void RenderSceneCB()
{
    // очистка окна
    glClear(GL_COLOR_BUFFER_BIT);
   // glColor3f(1.0f, 0.64f, 0.0f);
    glm::mat4 WorldMat = glm::mat4{ 1.0f };
    //перемещение
    /*glm::mat4 myMatrix;
    myMatrix[0][0] = 1.0f; myMatrix[0][1] = 0.0f; myMatrix[0][2] = 0.0f; myMatrix[3][0] = sinf(Scale);
    myMatrix[1][0] = 0.0f; myMatrix[1][1] = 1.0f; myMatrix[1][2] = 0.0f; myMatrix[1][3] = 0.0f;
    myMatrix[2][0] = 0.0f; myMatrix[2][1] = 0.0f; myMatrix[2][2] = 1.0f; myMatrix[2][3] = 0.0f;
    myMatrix[0][3] = 0.0f; myMatrix[3][1] = 0.0f; myMatrix[3][2] = 0.0f; myMatrix[3][3] = 1.0f;*/

    //вращение
    glm::mat4 myMatrix{
    cosf(Scale),  sinf(Scale), 0.0f, 0.0f,
    -sinf(Scale), cosf(Scale), 0.0f, 0.0f,
     0.0f,        0.0f,        1.0f, 0.0f,
     0.0f,        0.0f,        0.0f, 1.0f
    };
    //Масштаб
   /* glm::mat4 myMatrix;
    myMatrix[0][0] = abs(sinf(Scale)); myMatrix[0][1] = 0.0f; myMatrix[0][2] = 0.0f; myMatrix[3][0] = 0.0f;
    myMatrix[1][0] = 0.0f; myMatrix[1][1] = abs(cosf(Scale)); myMatrix[1][2] = 0.0f; myMatrix[1][3] = 0.0f;
    myMatrix[2][0] = 0.0f; myMatrix[2][1] = 0.0f; myMatrix[2][2] = abs(sinf(Scale)); myMatrix[2][3] = 0.0f;
    myMatrix[0][3] = 0.0f; myMatrix[3][1] = 0.0f; myMatrix[3][2] = 0.0f; myMatrix[3][3] = 1.0f;*/

    glm::mat4 WorldMat2 = myMatrix * WorldMat;
    glLoadMatrixf(static_cast<const float*>(glm::value_ptr(WorldMat2)));
    Scale += 0.001f;
    // Разрешаем использование каждого атрибута вершины в конвейере 
   glEnableVertexAttribArray(0);
    // Обратно привязываем буфер, приготавливая для отрисовки
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Говорим конвейеру, как воспринимать данные внутри буфера (индекс атрибута, количество аттрибутов,
    // тип данных каждого компонента, нормализировать ли данные перед использованием, шаг - число байтов
    // между двумя экземплярами атрибута, смещение первого компонента первого универсального атрибута вершины)
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //Вызов функции отрисовки
     glDrawArrays(GL_TRIANGLES, 0, 3);
    // Отключение использования каждого атрибута вершины в конвейере (необязятельно, но является хорошим тоном)
     glDisableVertexAttribArray(0);
    // меняем фоновый буфер и буфер кадра местами
    
    glutSwapBuffers();
    glutPostRedisplay();
  
}

static void CreateVertexBuffer() {
    // создание вектора вершины 
    glm::vec4 vertices[3];
    // создаем векторы с координатами x, y, z 
    vertices[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vertices[1] = glm::vec4(-0.4f, 0.4f, 0.0f, 1.0f);
    vertices[2] = glm::vec4(0.4f, 0.4f, 0.0f, 1.0f);

    // Генерация объекта переменного типа (количество объектов, ссылка на массив для хранения)
    glGenBuffers(1, &VBO);
    // Указываем OpenGL, что в VBO будет храниться массив вершин
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // заполнение буфера
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

int main(int argc, char** argv)
{
    // инициализация glut
    glutInit(&argc, argv);
    // установка двойной буферизации и буфера цвета
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    // задание размеров окна
    glutInitWindowSize(1024, 768);
    // задание начальной позиции
    glutInitWindowPosition(100, 100);
    // создание окна с заголовком "Tutorial 01"
    glutCreateWindow("Tutorial 01"); 
    // функция отрисовки 
    glutDisplayFunc(RenderSceneCB);
    // задаем цвет фона окна 
    glClearColor(0.7f, 1.0f, 0.7f, 0.0f);

  

    /*glm::mat4 myMatrix;
    myMatrix[0][0] = 1.0f; myMatrix[0][1] = 0.0f; myMatrix[0][2] = 0.0f; myMatrix[0][3] = sinf(Scale);
    myMatrix[1][0] = 0.0f; myMatrix[1][1] = 1.0f; myMatrix[1][2] = 0.0f; myMatrix[1][3] = 0.0f;
    myMatrix[2][0] = 0.0f; myMatrix[2][1] = 0.0f; myMatrix[2][2] = 1.0f; myMatrix[2][3] = 0.0f;
    myMatrix[3][0] = 0.0f; myMatrix[3][1] = 0.0f; myMatrix[3][2] = 0.0f; myMatrix[3][3] = 1.0f;
    glm::vec4 myVector;
    glm::mat4 myMatrix = glm::translate(glm::mat4(), glm::vec3(10.0f, 0.0f, 0.0f));
    glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
    glm::vec4 transformedVector = myMatrix * myVector;*/

    GLenum res = glewInit();
    // вывод ошибки при неуспешной инициализации
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    CreateVertexBuffer();


    glutMainLoop();
}
