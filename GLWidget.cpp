#include "GLWidget.h"

GLWidget :: GLWidget ( QWidget * parent) :
    QGLWidget ( parent )
{
	//Construtor, inicializando os valores das variaveis
    zoom = 0;
    objetos = new Objeto[2];
	flagAbertura = 1;

    //Inicialização do vetor de câmeras
    cameras.push_back(camera);
    cameras.push_back(camera);

    //Configurando posição da segunda câmera (câmera 1 configurada no construtor do objeto Camera)
    cameras[1].setCamera(QVector3D (0.0 , 2.0 , 0.0), QVector3D (0.0 , 0.0 , 0.0), QVector3D (0.0 , 2.0 , -1.0));

    //Configurando camera inicial
    camera.setCamera(cameras[0].eye, cameras[0].at, cameras[0].up);
}

GLWidget ::~GLWidget ()
{
}

void GLWidget :: showObj ()
{
	//Funcao para exibir o objeto na tela
    if (flagAbertura == 1) {
		flagAbertura = 0;

        //Gerar o player
        QString fileName = "./objFiles/boneco/boneco.obj";
        player.readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        player.genNormals ();
        player.createVBOs ();
        player.createShaders ();
        player.setPosition(0.0, 0.054, 0.0);
        player.setScale(0.25,0.25,0.25);

        //Gerar o primeiro objeto
        fileName = "./objFiles/outros/caixaA.obj";
        objetos[0].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[0].genNormals ();
        objetos[0].createVBOs ();
        objetos[0].createShaders ();
        objetos[0].setPosition(0.1, 0.041, 0.1);
        objetos[0].setScale(0.25,0.25,0.25);

        //Gerar o segundo objeto
        fileName = "./objFiles/chao/chao16x16.obj";
        objetos[1].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[1].genNormals ();
        objetos[1].createVBOs ();
        objetos[1].createShaders ();
        objetos[1].setPosition(0.0, 0.0, 0.0);

        paintGL();
    }
}

void GLWidget :: paintGL ()
{
    //Limpando a tela 
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //Configuracao da matriz do Mundo
    worldViewMatrix.setToIdentity ();
    worldViewMatrix.lookAt ( camera.eye , camera.at , camera.up);
    worldViewMatrix.scale(4.0,4.0,4.0);
    worldViewMatrix.rotate ( trackBall.getRotation ());

    //Colocando objetos no mundo
    player.setModelViewMatrix(worldViewMatrix);
    player.setMaterial(material.setMaterial("yellow_plastic"));
    player.setLight(light);
    player.paintGL(projectionMatrix);

    objetos[0].setModelViewMatrix(worldViewMatrix);
    objetos[0].setMaterial(material.setMaterial("brown_paper"));
    objetos[0].setLight(light);
    objetos[0].paintGL(projectionMatrix);

    objetos[1].setModelViewMatrix(worldViewMatrix);
    objetos[1].setMaterial(material.setMaterial("green_plastic"));
    objetos[1].setLight(light);
    objetos[1].paintGL(projectionMatrix);
}

void GLWidget :: initializeGL ()
{
	//Funcao para inicializar o programa
    makeCurrent();
    glEnable ( GL_DEPTH_TEST );
    glClearColor (0.8, 0.9, 1, 1);
	showObj();
}

void GLWidget :: resizeGL ( int width , int height )
{
    makeCurrent();
    glViewport (0, 0, width , height );
    projectionMatrix.setToIdentity ();
    projectionMatrix.perspective (60.0 ,
                                  static_cast <qreal >( width ) /
                                  static_cast <qreal >( height ), 0.1 , 20.0) ;

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
    camera.zoom(0.0001 * event -> delta ());

    updateGL();
}

void GLWidget::zoomIn()
{
    camera.zoom(-0.1);

    updateGL();
}


void GLWidget::zoomOut()
{
    camera.zoom(0.1);

    updateGL();
}

void GLWidget::changeCamera(unsigned long i)
{
    //Configurando a câmera atual para a câmera i do vetor de câmeras
    camera.setCamera(cameras[i].eye, cameras[i].at, cameras[i].up);
    trackBall.resetRotation();
    cameraIdx = i;
    updateGL();
}

void GLWidget::interact(bool *keyDirection)
{
    player.move(keyDirection);

    camera.at.setX(4*player.getPlayerPos().x());
    camera.eye.setX(4*player.getPlayerPos().x());
    if(cameraIdx == 1){
        camera.at.setZ(4*player.getPlayerPos().z());
        camera.eye.setZ(4*player.getPlayerPos().z());
    }
    updateGL();
}
