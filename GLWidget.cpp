#include "GLWidget.h"

GLWidget :: GLWidget ( QWidget * parent) :
    QGLWidget ( parent )
{
	//Construtor, inicializando os valores das variaveis
    zoom = 0;
    vboVertices = nullptr;
    vboNormals = nullptr;
    vboIndices = nullptr;
    normals = nullptr;
    numFaces=0;
    numVertices=0;

    vertexShader = nullptr;
    fragmentShader = nullptr;

    shaderProgram = nullptr;

    currentShader = 0;
	flagAbertura = 1;
}

GLWidget ::~GLWidget ()
{
	//Destrutor
    destroyShaders ();
    destroyVBOs ();
}


void GLWidget :: showObj ()
{
	//Funcao para exibir o objeto na tela
    if (flagAbertura == 1) {
		flagAbertura = 0;
		QString fileName = "lego.obj";
        readOBJFile ( fileName ); //funcao para leitura do arquivo obj

        genNormals ();
        createVBOs ();
        createShaders ();
        updateGL ();
    }
}


void GLWidget :: genNormals ()
{
    delete [] normals ;
    normals = new QVector3D [numVertices];

    for ( unsigned int i = 0; i < numFaces ; i ++) {

        unsigned int i1 = indices [i * 3 ];
        unsigned int i2 = indices [i * 3 + 1];
        unsigned int i3 = indices [i * 3 + 2];
        QVector3D v1 = vertices [i1].toVector3D ();
        QVector3D v2 = vertices [i2].toVector3D ();
        QVector3D v3 = vertices [i3].toVector3D ();
        QVector3D faceNormal = QVector3D::crossProduct (v2 - v1 , v3 - v1);
        faceNormal.normalize();
        normals [i1] += faceNormal ;
        normals [i2] += faceNormal ;
        normals [i3] += faceNormal ;
    }

    for ( unsigned int i = 0; i < numVertices ; i ++) {
        normals[i].normalize ();
    }
}

void GLWidget :: readOBJFile ( const QString & fileName )
{
	//Funcao para a leitura de um arquivo .obj 
	//Os dados extraidos do arquivo sao armazenados nas estruturas de dados desse programa
	std :: ifstream stream ;
	
	//Abertura do arquivo
	stream . open ( fileName . toLatin1 () , std :: ifstream :: in);

	if (! stream . is_open ()) {
		//Verifica se foi possivel abrir o arquivo
	  	qWarning (" Cannot open file .");
	  	return ;
	}

	//Cria variaveis auxiliares
	char linhaChar[2048];
	double x, y, z;
	int v[4], vn[4], vt[4];
	double minLim = std :: numeric_limits < double >:: min ();
	double maxLim = std :: numeric_limits < double >:: max ();
	QVector4D max ( minLim , minLim , minLim , 1.0) ;
	QVector4D min ( maxLim , maxLim , maxLim , 1.0) ;

	//Limpa os vector para armazenar os novos valores
	vertices.clear();
	indices.clear();

	//Enquanto o arquivo não acabar
	while(!stream.eof()){
		
		//Lê uma linha do arquivo
		stream.getline(linhaChar,2048,'\n');
		QString linha(linhaChar);

		//Separa a linha lida em tokens
		QStringList tokens = linha.split(" ");

		//Remove tokens vazios obtidos de espaçamento duplo
		tokens.removeAll("");

		//Caso a linha lida não seja um comentário e não esteja vazia
		if(linha[0]!='#'&&tokens.size()>1){ 
				
		//Vertices
		if(tokens[0]=="v"){
			numVertices++;

			//Recebe as coordenadas do vértice lido
			x = tokens[1].toDouble(); y = tokens[2].toDouble(); z = tokens[3].toDouble();

			//Calculo das coordenadas máximas e mínimas do objeto
			max . setX ( qMax ((double) max .x() , x));
			max . setY ( qMax ((double) max .y() , y));
			max . setZ ( qMax ((double) max .z() , z));
			min . setX ( qMin ((double) min .x() , x));
			min . setY ( qMin ((double) min .y() , y));
			min . setZ ( qMin ((double) min .z() , z));

			//Adiciona o vértice ao vetor de vértices
			vertices.push_back(QVector4D (x, y, z, 1.0));

		}
		//Normal
		else if(tokens[0]=="vn"){
		}
		//Texturas
		else if(tokens[0]=="vt"){
		}
		//Faces
		else if(tokens[0]=="f"){
			
		  	numFaces++;
			for (size_t j = 0; j < 3; j++) {
				//Divisão dos tokens em subtokens para a obtenção dos índices de vértices que formam as faces
				QStringList subTokens = tokens[j+1].split('/');

				//Recebe os indices dos vértices, normais e texturas, respectivamente
				v[j] = subTokens[0].toInt(); 
				vn[j] = subTokens[1].toInt(); 
				vt[j] = subTokens[2].toInt();

				//Deve-se subtrair em 1, pois os índices se iniciam em 1
				v[j]--;
				vn[j]--;
				vt[j]--;
		  	}

			//Adiciona os indices dos vértices no vetor de índices
			indices.push_back(v[0]);
			indices.push_back(v[1]);
			indices.push_back(v[2]);

		  	if(tokens.size()>=5){
		    	//Tenta dividir o ultimo ponto em subTokens
		    	QStringList subTokens = tokens[4].split('/');

		    if(subTokens.size()==3){
		        //Recebe o quarto ponto que forma a face
		        v[3] = subTokens[0].toDouble(); vn[3] = subTokens[1].toDouble(); vt[3] = subTokens[2].toDouble();

		        numFaces++;
		        v[3]--;
		        vn[3]--;
		        vt[3]--;

		        //Adiciona os índices de modo que o quadrilátero seja lido como dois triângulos
		        indices.push_back(v[0]);
		        indices.push_back(v[2]);
		        indices.push_back(v[3]);
		    }
		  }
		}
	  }
  	}

  	//Calculo do ponto central do objeto
  	midpoint = ( min + max ) * 0.5;

  	//Calculo da maior distância entre dois pontos no objeto
  	invdiag = 1 / ( max - min ). length ();

	//Fecha o arquivo que foi aberto
  	stream.close();
}

void GLWidget :: createVBOs (  )
{
    destroyVBOs ();

    vboVertices = new QGLBuffer( QGLBuffer :: VertexBuffer );
    vboVertices -> create ();
    vboVertices -> bind ();
    vboVertices -> setUsagePattern ( QGLBuffer :: StaticDraw );
    vboVertices -> allocate ( vertices.data() , numVertices * sizeof ( QVector4D ));

    vertices.clear();

    vboNormals = new QGLBuffer ( QGLBuffer :: VertexBuffer );
    vboNormals -> create ();
    vboNormals -> bind ();
    vboNormals -> setUsagePattern ( QGLBuffer :: StaticDraw );
    vboNormals -> allocate ( normals , numVertices * sizeof ( QVector3D ));

    delete [] normals;
    normals = NULL;

    vboIndices = new QGLBuffer ( QGLBuffer :: IndexBuffer );
    vboIndices -> create () ;
    vboIndices -> bind () ;
    vboIndices -> setUsagePattern ( QGLBuffer :: StaticDraw );
    vboIndices -> allocate ( indices.data() , numFaces * 3 * sizeof ( unsigned int ));

    indices.clear();
}

void GLWidget :: destroyVBOs ()
{
    if ( vboVertices ) {
        vboVertices -> release ();
        delete vboVertices ;
        vboVertices = NULL ;
    }

    if ( vboNormals ) {
        vboNormals -> release ();
        delete vboNormals ;
        vboNormals = NULL ;
    }

    if ( vboIndices ) {
        vboIndices -> release ();
        delete vboIndices ;
        vboIndices = NULL ;
    }
}

void GLWidget :: createShaders ()
{
	//Funcao para a criação dos shaders

    destroyShaders (); //Primeiro destroi os shaders antigos

	//Vincula os novos shaders
    QString vertexShaderFile [] = {
        ":/shaders/vgouraud.glsl",
    };
    QString fragmentShaderFile [] = {
        ":/shaders/fgouraud.glsl",
    };

    vertexShader = new QGLShader( QGLShader::Vertex );
    if (! vertexShader -> compileSourceFile ( vertexShaderFile [currentShader]))
        qWarning () << vertexShader -> log ();

    fragmentShader = new QGLShader ( QGLShader::Fragment);
    if (! fragmentShader -> compileSourceFile (fragmentShaderFile [currentShader]))
        qWarning () << fragmentShader -> log ();

    shaderProgram = new QGLShaderProgram( ) ;
    shaderProgram -> addShader ( vertexShader );
    shaderProgram -> addShader ( fragmentShader );

    if (! shaderProgram -> link ())
        qWarning () << shaderProgram -> log () << endl ;
}

void GLWidget :: destroyShaders ()
{
	//Funcao para destruir os shaders antigos
    if( vertexShader ) {
        delete vertexShader ;
        vertexShader = NULL ;
    }
    if( fragmentShader ) {
        delete fragmentShader ;
        fragmentShader = NULL ;
    }
    if ( shaderProgram ) {
        shaderProgram -> release ();
        delete shaderProgram ;
        shaderProgram = NULL ;
    }
}

void GLWidget :: paintGL ()
{
	//Funcao para exibir o objeto na tela

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if (! vboVertices )
     return ;

	//Configuracao da matriz
    modelViewMatrix.setToIdentity ();
    modelViewMatrix.lookAt ( camera.eye , camera.at , camera.up);
    modelViewMatrix.translate (0, 0, zoom );

    //Realizacao da escala do objeto
    modelViewMatrix.scale(invdiag,invdiag,invdiag);
    //Realizacao da translação do objeto
    modelViewMatrix.translate (-midpoint.x(),-midpoint.y(),-midpoint.z());

    modelViewMatrix.rotate ( trackBall.getRotation ());

    shaderProgram -> bind ();

	//Atribuir os valores ao shader
    shaderProgram -> setUniformValue ("modelViewMatrix", modelViewMatrix );
    shaderProgram -> setUniformValue ("projectionMatrix", projectionMatrix );
    shaderProgram -> setUniformValue("normalMatrix", modelViewMatrix.normalMatrix ());

    QVector4D ambientProduct = light.ambient * material.ambient ;
    QVector4D diffuseProduct = light.diffuse * material.diffuse ;
    QVector4D specularProduct = light.specular * material.specular ;

	//Atribuir os valores ao shader
    shaderProgram -> setUniformValue ("lightPosition", light.position );
    shaderProgram -> setUniformValue ("ambientProduct", ambientProduct );
    shaderProgram -> setUniformValue ("diffuseProduct", diffuseProduct );
    shaderProgram -> setUniformValue ("specularProduct", specularProduct );
    shaderProgram -> setUniformValue ( "shininess", static_cast < GLfloat >( material.shininess ));

    vboNormals -> bind ();
	//Atribuir os valores ao shader
    shaderProgram -> enableAttributeArray ("vNormal");
    shaderProgram -> setAttributeBuffer ("vNormal", GL_FLOAT ,0, 3, 0);

    vboVertices -> bind ();
	//Atribuir os valores ao shader
    shaderProgram -> enableAttributeArray ("vPosition");
    shaderProgram -> setAttributeBuffer ("vPosition", GL_FLOAT ,0, 4, 0);

    vboIndices -> bind ();
    glDrawElements ( GL_TRIANGLES , numFaces * 3, GL_UNSIGNED_INT , 0);

    vboIndices -> release ();
    vboNormals -> release ();
    vboVertices -> release ();
    shaderProgram -> release ();
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

void GLWidget :: keyPressEvent ( QKeyEvent * event )
{

    switch (event ->key ())
    {
    case Qt :: Key_Escape :
        qApp -> quit ();
    }

    updateGL();

}
