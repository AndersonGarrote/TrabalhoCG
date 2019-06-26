#include "Objeto.h"

Objeto :: Objeto ()
{
    numFaces=0;
    numVertices=0;
    currentShader = 0;
    vboVertices = 0;
    vboNormals = 0;
    vboIndices = 0;
    normals = 0;

    vertexShader = 0;
    fragmentShader = 0;
    shaderProgram = 0;

    posX = 0.0; posY = 0.0; posZ = 0.0;
    rotX = 0; rotY = 0; rotZ = 0;
    scaX = 1; scaY = 1; scaZ = 1;
}

Objeto ::~Objeto ()
{
	//Destrutor
    destroyShaders ();
    destroyVBOs ();
}

void Objeto :: readOBJFile ( const QString & fileName )
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
            max . setX ( qMax ( max .x() , x));
            max . setY ( qMax ( max .y() , y));
            max . setZ ( qMax ( max .z() , z));
            min . setX ( qMin ( min .x() , x));
            min . setY ( qMin ( min .y() , y));
            min . setZ ( qMin ( min .z() , z));

			//Adiciona o vértice ao vetor de vértices
			vertices.push_back(QVector4D (x, y, z, 1.0));

		}
		//Normal
		else if(tokens[0]=="vn"){
            //Recebe as coordenadas do vértice lido
			x = tokens[1].toDouble(); y = tokens[2].toDouble(); z = tokens[3].toDouble();

            vertNormals.push_back(QVector3D (x,y,z));
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
				vt[j] = subTokens[1].toInt();
				vn[j] = subTokens[2].toInt();

				//Deve-se subtrair em 1, pois os índices se iniciam em 1
				v[j]--;
				vt[j]--;
				vn[j]--;

                //Adiciona o vn para o respectivo vertice da face
                vertVn.push({v[j],vn[j]});
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
		        v[3] = subTokens[0].toInt();
                vt[3] = subTokens[1].toInt();
                vn[3] = subTokens[2].toInt();

		        numFaces++;
		        v[3]--;
		        vt[3]--;
		        vn[3]--;

		        //Adiciona os índices de modo que o quadrilátero seja lido como dois triângulos
		        indices.push_back(v[0]);
		        indices.push_back(v[2]);
		        indices.push_back(v[3]);

                //Adiciona o vn para o respectivo vertice da face
                vertVn.push({v[3],vn[3]});
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

void Objeto :: genNormals ()
{
    //Funcao para gerar as normais baseado nos vn informado pelo arquivo obj
    delete [] normals ;
    normals = new QVector3D [numVertices];
    intDoub vvn;

    while(!vertVn.empty()){
        vvn= vertVn.front();
        vertVn.pop();
        normals [vvn.first] += vertNormals[vvn.second];
    }

    for ( unsigned int i = 0; i < numVertices ; i ++) {
        normals[i].normalize ();
    }
}

void Objeto :: createVBOs (  )
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

void Objeto :: destroyVBOs ()
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

void Objeto :: createShaders ()
{
	//Funcao para a criação dos shaders

    destroyShaders (); //Primeiro destroi os shaders antigos

	//Vincula os novos shaders
    QString vertexShaderFile [] = {
        ":/shaders/vphong.glsl",
    };
    QString fragmentShaderFile [] = {
        ":/shaders/fphong.glsl",
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

void Objeto :: destroyShaders ()
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

void Objeto :: setModelViewMatrix(QMatrix4x4 matrix){
    modelViewMatrix = matrix;
}

void Objeto :: setMaterial(Material mat){
    material = mat;
}

void Objeto :: setLight(Light li){
    light = li;
}

void Objeto :: setPosition(double x, double y, double z){
    posX = x;
    posY = y;
    posZ = z;
}

void Objeto::setRotation(double angle, double x, double y, double z)
{
    rotX = x*angle;
    rotY = y*angle;
    rotZ = z*angle;
}

void Objeto::setTranslation(double x, double y, double z)
{
    posX += x;
    posY += y;
    posZ += z;
}

void Objeto :: setScale(double x, double y, double z){
    scaX = x;
    scaY = y;
    scaZ = z;
}

void Objeto :: paintGL (QMatrix4x4 projectionMatrix)
{
	//Funcao para exibir o objeto na tela
    if (! vboVertices ){
        return ;
    }

    //Realizacao da translação do objeto
    modelViewMatrix.translate (posX,posY,posZ);
    //Realização da rotação do objeto
    modelViewMatrix.rotate(rotX,1,0,0);
    modelViewMatrix.rotate(rotY,0,1,0);
    modelViewMatrix.rotate(rotZ,0,0,1);
    //Realizacao da escala do objeto
    modelViewMatrix.scale(scaX*invdiag/2,scaX*invdiag/2,scaX*invdiag/2);
    //Realizacao da translação para a origem
    modelViewMatrix.translate (-midpoint.x(),-midpoint.y(),-midpoint.z());

    shaderProgram -> bind ();

    //Atribuir os valores ao shader
    shaderProgram -> setUniformValue ("modelViewMatrix", modelViewMatrix );
    shaderProgram -> setUniformValue ("projectionMatrix", projectionMatrix );
    shaderProgram -> setUniformValue("normalMatrix", modelViewMatrix.normalMatrix() );

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

