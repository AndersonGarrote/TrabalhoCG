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

        //Gerar o primeiro objeto
        QString fileName = "./objFiles/boneco/boneco.obj";
        objetos[0].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[0].genNormals ();
        objetos[0].createVBOs ();
        objetos[0].createShaders ();

        //Gerar o segundo objeto
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
    //Limpando a tela 
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //Configuracao da matriz
    QMatrix4x4 modelViewMatrix ; //Matriz auxiliar
    modelViewMatrix.setToIdentity ();
    modelViewMatrix.lookAt ( camera.eye , camera.at , camera.up);
    modelViewMatrix.translate (0, 0, zoom );
    modelViewMatrix.rotate ( trackBall.getRotation ());

    objetos[0].setModelViewMatrix(modelViewMatrix);
    objetos[0].setMaterial(material);
    objetos[0].setLight(light);

    objetos[0].setTranslation(playerPos.x(),0.0,playerPos.z());
    objetos[0].setRotation(playerRot.y(),0,1,0);
    objetos[0].setScale(0.25,0.25,0.25);

    objetos[0].setPosition(0.0, 32.0, 0.0);
    objetos[0].paintGL(projectionMatrix);

    objetos[1].setModelViewMatrix(modelViewMatrix);
    objetos[1].setMaterial(material);
    objetos[1].setLight(light);
    objetos[1].setPosition(0.0, 0.0, 0.0);
    objetos[1].paintGL(projectionMatrix);
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
    zoom += 0.0001 * event -> delta ();

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
    //Configurando a câmera atual para a câmera i do vetor de câmeras
    camera.setCamera(cameras[i].eye, cameras[i].at, cameras[i].up);

    updateGL();
}

void GLWidget::interact(bool * keyDirection)
{
    qreal result = 0.0, directions=0;
    if(keyDirection[0]){
        result+=180;
        directions++;
    }
    if(keyDirection[1]) {
        result+=270.0;
        directions++;
    }
    if(keyDirection[2]){
        result+=360.0;
        directions++;
    }
    if(keyDirection[3]){
        result+=90.0;
        directions++;
    }

    playerRot.setY(result/directions);

    if(keyDirection[0]) playerPos.setZ(playerPos.z()-0.005);
    if(keyDirection[1]) playerPos.setX(playerPos.x()-0.005);
    if(keyDirection[2]) playerPos.setZ(playerPos.z()+0.005);
    if(keyDirection[3]) playerPos.setX(playerPos.x()+0.005);

    double sinX = sin(playerPos.x()*50);
    double sinZ = sin(playerPos.z()*50);

    playerRot.setY(playerRot.y()+20.0*( sinX * sinX + sinZ * sinZ )-10.0);

    updateGL();
}
