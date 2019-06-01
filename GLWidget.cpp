#include "GLWidget.h"

GLWidget :: GLWidget ( QWidget * parent) :
    QGLWidget ( parent )
{
	//Construtor, inicializando os valores das variaveis
    zoom = 0;
    objetos = new Objeto[2];
	flagAbertura = 1;

    cameras.push_back(camera);
    cameras.push_back(camera);
    cameras[1].setCamera(QVector3D (0.0 , 2.0 , 0.0), QVector3D (-0.5 , 0.0 , 0.0), QVector3D (0.0 , 1.0 , 0.0));
}

GLWidget ::~GLWidget ()
{
	delete[] objetos;
}


void GLWidget :: showObj ()
{
	//Funcao para exibir o objeto na tela
    if (flagAbertura == 1) {
		flagAbertura = 0;
        
        QString fileName = "./objFiles/boneco/boneco.obj";
        objetos[0].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[0].genNormals ();
        objetos[0].createVBOs ();
        objetos[0].createShaders ();

        fileName = "./objFiles/chao/chao16x16.obj";
        objetos[1].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[1].genNormals ();
        objetos[1].createVBOs ();
        objetos[1].createShaders ();
     
        paintGL();
    }
}




void GLWidget :: paintGL ()
{
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //Configuracao da matriz
    QMatrix4x4 modelViewMatrix ;
    modelViewMatrix.setToIdentity ();
    modelViewMatrix.lookAt ( camera.eye , camera.at , camera.up);
    modelViewMatrix.translate (0, 0, zoom );
    modelViewMatrix.rotate ( trackBall.getRotation ());
    objetos[0].setModelViewMatrix(modelViewMatrix);
    objetos[0].setMaterial(material);
    objetos[0].setLight(light);
    objetos[0].setPosition(0.0,32.0,0.0);
	objetos[0].paintGL();

    objetos[1].setModelViewMatrix(modelViewMatrix);
    objetos[1].setMaterial(material);
    objetos[1].setLight(light);
    objetos[1].setPosition(0.0,0.0,0.0);
	objetos[1].paintGL();
}


void GLWidget :: initializeGL ()
{
	//Funcao para inicializar o programa
    makeCurrent();
    glEnable ( GL_DEPTH_TEST );
    glClearColor (0, 0, 0, 1);
	showObj();
}


void GLWidget :: resizeGL ( int width , int height )
{
    makeCurrent();
    objetos[0].resizeGL(width, height);
    objetos[1].resizeGL(width, height);
    trackBall.resizeViewport (width , height );
    updateGL();
}

/* Funcoes para tratar eventos de mouse */

void GLWidget :: mouseMoveEvent ( QMouseEvent * event )
{
    trackBall.mouseMove (event -> pos ());

    updateGL();
}

void GLWidget :: mousePressEvent ( QMouseEvent * event )
{
    if (event -> button () & Qt :: LeftButton )
        trackBall.mousePress (event -> pos ());

    updateGL();
}

void GLWidget :: mouseReleaseEvent ( QMouseEvent * event )
{
    if (event -> button () == Qt :: LeftButton )
        trackBall.mouseRelease (event -> pos ());

    updateGL();
}

void GLWidget :: wheelEvent ( QWheelEvent * event )
{

    zoom += 0.0001 * event -> delta ();

    updateGL();
}

void GLWidget :: keyPressEvent ( QKeyEvent * event )
{

    switch (event ->key ())
    {
    case Qt :: Key_Escape :
        qApp -> quit ();
    }

    updateGL();

}

void GLWidget::zoomIn()
{
    zoom += 0.1;

    updateGL();
}


void GLWidget::zoomOut()
{
    zoom -= 0.1;

    updateGL();
}

void GLWidget::changeCamera(unsigned long i)
{
    camera.setCamera(cameras[i].eye, cameras[i].at, cameras[i].up);

    updateGL();
}
