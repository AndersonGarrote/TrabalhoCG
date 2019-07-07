#include "GLWidget.h"

GLWidget :: GLWidget ( QWidget * parent) :
    QGLWidget ( parent )
{
	//Construtor, inicializando os valores das variaveis
    zoom = 0;
    objetos = new Objeto[4];
    orbitas = new Objeto[4];
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

        //Gerar o terceiro objeto
        fileName = "./objFiles/mobilia/cadeira.obj";
        objetos[2].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[2].genNormals ();
        objetos[2].createVBOs ();
        objetos[2].createShaders ();
        objetos[2].setPosition(0.0, 0.040, -0.1);
        objetos[2].setScale(0.22,0.17,0.18);
        objetos[2].setRotation(90, 0, 1, 0);

        //Gerar o segundo objeto
        fileName = "./objFiles/blocos/bloco2x2.obj";
        objetos[3].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[3].genNormals ();
        objetos[3].createVBOs ();
        objetos[3].createShaders ();
        objetos[3].setPosition(0.0, 0.018, 0.0);
        objetos[3].setScale(0.13,0.13,0.13);
        //objetos[3].setRotation(90, 0, 1, 0);

        //Gerar o primeiro objeto que vai orbitar o player
        fileName = "./objFiles/blocos/bloco2x2.obj";
        orbitas[0].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        orbitas[0].genNormals ();
        orbitas[0].createVBOs ();
        orbitas[0].createShaders ();
        orbitas[0].setPosition(player.getPlayerPos().x(),player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05);
        orbitas[0].setScale(0.05,0.05,0.05);

        //Gerar o segundo objeto que vai orbitar o player
        fileName = "./objFiles/blocos/bloco2x2.obj";
        orbitas[1].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        orbitas[1].genNormals ();
        orbitas[1].createVBOs ();
        orbitas[1].createShaders ();
        orbitas[1].setPosition(player.getPlayerPos().x() + 0.05 ,player.getPlayerPos().y(), player.getPlayerPos().z());
        orbitas[1].setScale(0.05,0.05,0.05);

        //Gerar o terceiro objeto que vai orbitar o player
        fileName = "./objFiles/blocos/bloco2x2.obj";
        orbitas[2].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        orbitas[2].genNormals ();
        orbitas[2].createVBOs ();
        orbitas[2].createShaders ();
        orbitas[2].setPosition(player.getPlayerPos().x(),player.getPlayerPos().y(), player.getPlayerPos().z() - 0.05);
        orbitas[2].setScale(0.05,0.05,0.05);

        //Gerar o segundo objeto que vai orbitar o player
        fileName = "./objFiles/blocos/bloco2x2.obj";
        orbitas[3].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        orbitas[3].genNormals ();
        orbitas[3].createVBOs ();
        orbitas[3].createShaders ();
        orbitas[3].setPosition(player.getPlayerPos().x() - 0.05 ,player.getPlayerPos().y(), player.getPlayerPos().z());
        orbitas[3].setScale(0.05,0.05,0.05);

//        //Gerar o segundo objeto que vai orbitar o player
//        fileName = "./objFiles/blocos/bloco2x2.obj";
//        objetos[5].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
//        objetos[5].genNormals ();
//        objetos[5].createVBOs ();
//        objetos[5].createShaders ();
//        objetos[5].setPosition(player.getPlayerPos().x() + 0.05,player.getPlayerPos().y(), player.getPlayerPos().z());
//        objetos[5].setScale(0.05,0.05,0.05);

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

    objetos[2].setModelViewMatrix(worldViewMatrix);
    objetos[2].setMaterial(material.setMaterial("yellow_plastic"));
    objetos[2].setLight(light);
    objetos[2].paintGL(projectionMatrix);

    objetos[3].setModelViewMatrix(worldViewMatrix);
    objetos[3].setMaterial(material.setMaterial("green_plastic"));
    objetos[3].setLight(light);
    objetos[3].paintGL(projectionMatrix);

    orbitas[0].setModelViewMatrix(worldViewMatrix);
    orbitas[0].setMaterial(material.setMaterial("other_material"));
    orbitas[0].setLight(light);
    orbitas[0].paintGL(projectionMatrix);

    orbitas[1].setModelViewMatrix(worldViewMatrix);
    orbitas[1].setMaterial(material.setMaterial("brown_paper"));
    orbitas[1].setLight(light);
    orbitas[1].paintGL(projectionMatrix);

    orbitas[2].setModelViewMatrix(worldViewMatrix);
    orbitas[2].setMaterial(material.setMaterial("green_plastic"));
    orbitas[2].setLight(light);
    orbitas[2].paintGL(projectionMatrix);

    orbitas[3].setModelViewMatrix(worldViewMatrix);
    orbitas[3].setMaterial(material.setMaterial("yellow_plastic"));
    orbitas[3].setLight(light);
    orbitas[3].paintGL(projectionMatrix);
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
    camera.at.setX(4*player.getPlayerPos().x());
    camera.eye.setX(4*player.getPlayerPos().x());
    if(cameraIdx == 1){
        camera.at.setZ(4*player.getPlayerPos().z());
        camera.eye.setZ(4*player.getPlayerPos().z());
    }
    updateGL();
}

void GLWidget::interact(bool *keyDirection)
{

    if(keyDirection[4]){
        player.jump();
    }else{
        player.fall();
        if( keyDirection[0] ||  keyDirection[1] || keyDirection[2] || keyDirection[3]){
            player.move(keyDirection);
        }
    }

    camera.at.setX(4*player.getPlayerPos().x());
    camera.eye.setX(4*player.getPlayerPos().x());

    if(cameraIdx == 1){
        camera.at.setZ(4*player.getPlayerPos().z());
        camera.eye.setZ(4*player.getPlayerPos().z());

    } else{
        camera.at.setY(4*player.getPlayerPos().y());
        camera.eye.setY(4*player.getPlayerPos().y());
    }

    orbitas[0].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(0)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(0)));
    orbitas[1].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(90)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(90)));
    orbitas[2].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(180)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(180)));
    orbitas[3].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(270)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(270)));
    player.anguloOrbitaIncrement(2.5);

    updateGL();
}
