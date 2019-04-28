#include "myglwidget.hpp"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

void MyGLWidget::initializeGL()
{
    Model* model = new Cylinder(72, 2.0, 8.0);
    scene = new Scene(model);
    scene->init();

    prevTransX = 0;
    prevTransY = 0;
    prevTransZ = 0;

    prevRotX = 0;
    prevRotY = 0;
    prevRotZ = 0;

    prevLightX = 0;
    prevLightY = 0;
    prevLightZ = 0;

    currentLoadedModelName = "monkey.obj";
}

void MyGLWidget::paintGL()
{
    scene->draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    scene->changePerspectiveRatio((float)width / (float)height);
}

void MyGLWidget::translateX(int value)
{
    int distance = value - prevTransX;
    scene->getModel()->translateX((float)distance);
    prevTransX = value;
    update();
}

void MyGLWidget::translateY(int value)
{
    int distance = value - prevTransY;
    scene->getModel()->translateY((float)distance);
    prevTransY = value;
    update();
}

void MyGLWidget::translateZ(int value)
{
    int distance = value - prevTransZ;
    scene->getModel()->translateZ((float)distance);
    prevTransZ = value;
    update();
}

void MyGLWidget::rotateX(int value)
{
    int angle = value - prevRotX;
    scene->getModel()->rotateX((float)angle);
    prevRotX = value;
    update();
}

void MyGLWidget::rotateY(int value)
{
    int angle = value - prevRotY;
    scene->getModel()->rotateY((float)angle);
    prevRotY = value;
    update();
}

void MyGLWidget::rotateZ(int value)
{
    int angle = value - prevRotZ;
    scene->getModel()->rotateZ((float)angle);
    prevRotZ = value;
    update();
}

void MyGLWidget::switchToRandomShader()
{
    scene->switchShaderProgram("randomshader");
    update();
}

void MyGLWidget::switchToPositionShader()
{
    scene->switchShaderProgram("positionshader");
    update();
}

void MyGLWidget::switchToNormalShader()
{
    scene->switchShaderProgram("normalshader");
    update();
}

void MyGLWidget::switchToLambertShader()
{
    scene->switchShaderProgram("lambertshader");
    update();
}

void MyGLWidget::switchToPhongShader()
{
    scene->switchShaderProgram("phongshader");
    update();
}

void MyGLWidget::switchToTextureShader()
{
    scene->switchShaderProgram("textureshader");
    update();
}

void MyGLWidget::switchToCombinedShader()
{
    scene->switchShaderProgram("combinedshader");
    update();
}

void MyGLWidget::switchToMTLShader()
{
    scene->switchShaderProgram("mtlshader");
    update();
}

void MyGLWidget::switchToCylinderModel(bool value)
{
    if (value)
    {
        Model* model = new Cylinder(72, 2.0, 8.0);
        scene->switchModel(model);
        update();
    }
}

void MyGLWidget::switchToLoadedModel(bool value)
{
    if (value)
    {
        Model* model = new LoadedModel(currentLoadedModelName);
        scene->switchModel(model);
        update();
    }
}

void MyGLWidget::changeLoadedModel(QString value)
{
    currentLoadedModelName = value.toUtf8().constData();
    switchToLoadedModel(true);
}

void MyGLWidget::moveLightX(int value)
{
    int distance = value - prevLightX;
    scene->getLight()->translateX((float)distance);
    prevLightX = value;
    update();
}

void MyGLWidget::moveLightY(int value)
{
    int distance = value - prevLightY;
    scene->getLight()->translateY((float)distance);
    prevLightY = value;
    update();
}

void MyGLWidget::moveLightZ(int value)
{
    int distance = value - prevLightZ;
    scene->getLight()->translateZ((float)distance);
    prevLightZ = value;
    update();
}

void MyGLWidget::changeN(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(scene->getModel());
    if (cylinder)
    {
        cylinder->changeN(value);
        update();
    }
}

void MyGLWidget::changeRadius(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(scene->getModel());
    if (cylinder)
    {
        cylinder->changeRadius((float)value);
        update();
    }
}

void MyGLWidget::changeHeight(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(scene->getModel());
    if (cylinder)
    {
        cylinder->changeHeight((float)value);
        update();
    }
}

void MyGLWidget::recompileShader()
{
    scene->getModel()->getShaderProgram()->reloadProgram();
    update();
}

void MyGLWidget::switchTexture(QString value)
{
    scene->getModel()->getMaterial()->switchTexture(value.toUtf8().constData());
    update();
}

void MyGLWidget::scaleTexture(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(scene->getModel());
    if (cylinder)
    {
        cylinder->changeUVScale((float)value / 10.0);
        update();
    }
}

void MyGLWidget::close()
{
    delete scene;
}
