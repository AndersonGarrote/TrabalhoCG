#include "GLWidget.h"

GLWidget :: GLWidget ( QWidget * parent) :
    QGLWidget ( parent )
{
	//Construtor, inicializando os valores das variaveis
    zoom = 0;
    objetos = new Objeto[8];
    blocos = new Objeto[4];
    orbitas = new Objeto[4];
	  flagAbertura = 1;
    for(int i = 0; i < 4; i++){
      flagAparecer[i] = 0;
    }
    //Inicialização do vetor de câmeras
    cameras.push_back(camera);
    cameras.push_back(camera);

    //Configurando posição da segunda câmera (câmera 1 configurada no construtor do objeto Camera)
    cameras[1].setCamera(QVector3D (0.0 , 2.0 , 0.0), QVector3D (0.0 , 0.0 , 0.0), QVector3D (0.0 , 2.0 , -1.0));

    //Configurando camera inicial
    camera.setCamera(cameras[0].eye, cameras[0].at, cameras[0].up);

    //Setando Timer de 20 milisegundos para atualizar a cena
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(20);
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
        player.setPosition(0.0, 0.054, 0.05);
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
        objetos[2].setPosition(0.0, 0.050, -0.15);
        objetos[2].setScale(0.22,0.05,0.18);
        objetos[2].setRotation(90, 0, 1, 0);

        //Gerar o quarto objeto
        fileName = "./objFiles/outros/foguete.obj";
        objetos[3].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[3].genNormals ();
        objetos[3].createVBOs ();
        objetos[3].createShaders ();
        objetos[3].setPosition(-0.15, 0.07, -0.12);
        objetos[3].setScale(0.3,0.5,0.3);

        //Gerar o quinto objeto
        fileName = "./objFiles/outros/laptop.obj";
        objetos[4].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[4].genNormals ();
        objetos[4].createVBOs ();
        objetos[4].createShaders ();
        objetos[4].setPosition(0.0, 0.099, -0.08);
        objetos[4].setScale(0.2,0.2,0.2);

        //Gerar o sexto objeto
        fileName = "./objFiles/mobilia/escrivaninha.obj";
        objetos[5].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[5].genNormals ();
        objetos[5].createVBOs ();
        objetos[5].createShaders ();
        objetos[5].setPosition(0.0, 0.04, -0.08);
        objetos[5].setScale(0.4,0.7,0.4);

        //Gerar o setimo objeto
        fileName = "./objFiles/mobilia/lampada.obj";
        objetos[6].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[6].genNormals ();
        objetos[6].createVBOs ();
        objetos[6].createShaders ();
        objetos[6].setPosition(0.1, 0.078, -0.15);
        objetos[6].setScale(0.3,0.3,0.3);

        //Gerar o oitavo objeto
        fileName = "./objFiles/mobilia/poltrona.obj";
        objetos[7].readOBJFile ( fileName ); //funcao para leitura do arquivo obj
        objetos[7].genNormals ();
        objetos[7].createVBOs ();
        objetos[7].createShaders ();
        objetos[7].setPosition(-0.13, 0.045, 0.1);
        objetos[7].setScale(0.3,0.3,0.3);
        objetos[7].setRotation(270, 0, 1, 0);

        for (int i = 0; i < 4; i++) {
            orbitas[i].genMagicCube();
            orbitas[i].genMagicCubeNormals ();
            orbitas[i].createVBOs ();
            orbitas[i].createTextureShaders();
            orbitas[i].setScale(0.05,0.05,0.05);

            blocos[i].genMagicCube();
            blocos[i].genMagicCubeNormals ();
            blocos[i].createVBOs ();
            blocos[i].createTextureShaders ();
            blocos[i].setScale(0.1,0.1,0.1);
        }


        blocos[0].setPosition(0.15, 0.045, 0.15);
        blocos[1].setPosition(-0.15, 0.045, 0.02);
        blocos[2].setPosition(-0.06, 0.045, 0.14);
        blocos[3].setPosition(0.12, 0.045, -0.13);

        orbitas[0].setPosition(player.getPlayerPos().x(),player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05);
        orbitas[1].setPosition(player.getPlayerPos().x() + 0.05 ,player.getPlayerPos().y(), player.getPlayerPos().z());
        orbitas[2].setPosition(player.getPlayerPos().x(),player.getPlayerPos().y(), player.getPlayerPos().z() - 0.05);
        orbitas[3].setPosition(player.getPlayerPos().x() - 0.05 ,player.getPlayerPos().y(), player.getPlayerPos().z());

        paintGL();
    }
}

void GLWidget::timerUpdate()
{
    orbitas[0].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(0)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(0)));
    orbitas[1].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(90)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(90)));
    orbitas[2].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(180)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(180)));
    orbitas[3].setPosition(player.getPlayerPos().x() + 0.05*sin(player.getanguloOrbita(270)), player.getPlayerPos().y(), player.getPlayerPos().z() + 0.05*cos(player.getanguloOrbita(270)));

    player.anguloOrbitaIncrement(2.5);

    updateGL();
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

    objetos[4].setModelViewMatrix(worldViewMatrix);
    objetos[4].setLight(light);
    objetos[4].paintGL(projectionMatrix);

    objetos[5].setModelViewMatrix(worldViewMatrix);
    objetos[5].setMaterial(material.setMaterial("green_plastic"));
    objetos[5].setLight(light);
    objetos[5].paintGL(projectionMatrix);

    objetos[6].setModelViewMatrix(worldViewMatrix);
    objetos[6].setMaterial(material.setMaterial("brown_paper"));
    objetos[6].setLight(light);
    objetos[6].paintGL(projectionMatrix);

    objetos[7].setModelViewMatrix(worldViewMatrix);
    objetos[7].setMaterial(material.setMaterial("yellow_plastic"));
    objetos[7].setLight(light);
    objetos[7].paintGL(projectionMatrix);

    for (int i = 0; i < 4; i++) {
      if(flagAparecer[i] == 0){
        blocos[i].setModelViewMatrix(worldViewMatrix);
        blocos[i].setMaterial(material.setMaterial("white_plastic"));
        blocos[i].setLight(light);
        blocos[i].paintCubeGL(projectionMatrix, cubeTextures);
      }
      else{
        orbitas[i].setModelViewMatrix(worldViewMatrix);
        orbitas[i].setMaterial(material.setMaterial("white_plastic"));
        orbitas[i].setLight(light);
        orbitas[i].paintCubeGL(projectionMatrix, cubeTextures);
      }
    }
}

void GLWidget :: initializeGL ()
{
	//Funcao para inicializar o programa
    makeCurrent();
    glEnable ( GL_DEPTH_TEST );

    glEnable(GL_TEXTURE_2D);

    //Lendo texturas do cubo
    for (int j=0; j < 6; ++j) {
        this->cubeTextures[j] = bindTexture(QPixmap(QString(":/images/side%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }

    glClearColor (0.8f, 0.9f, 1, 1);

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

    double x, y, z, dist[4];
    for(int i = 0; i < 4; i++){
        x = player.getPlayerPos().x() - blocos[i].getObjetoPos().x();
        y = player.getPlayerPos().y() - blocos[i].getObjetoPos().y();
        z = player.getPlayerPos().z() - blocos[i].getObjetoPos().z();
        dist[i] = (x*x) + (y*y) + (z*z);
    }
    if(dist[0] < 0.001){
        flagAparecer[0] = 1;
    }
    if(dist[1] < 0.001){
        flagAparecer[1] = 1;
    }
    if(dist[2] < 0.001){
        flagAparecer[2] = 1;
    }
    if(dist[3] < 0.001){
        flagAparecer[3] = 1;
    }
    updateGL();
}

void GLWidget::setShader(int s)
{
    if( s < 2 && s >= 0){
        player.setCurrentShader(s);
        player.createShaders();
        for (int i = 0;i < 8; i++) {
            objetos[i].setCurrentShader(s);
            objetos[i].createShaders();
        }
        for (int i = 0; i < 4; i++) {
            orbitas[i].setCurrentShader(s);
            orbitas[i].createTextureShaders();
            blocos[i].setCurrentShader(s);
            blocos[i].createTextureShaders();
        }

        updateGL();
    }
}
