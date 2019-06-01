#include <QApplication>

#include <QGLFormat>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	//A main desse programa faz a configuracao inicial e abre a janela para ser exibido o objeto posteriormente
    QGLFormat format = QGLFormat :: defaultFormat ();
    format . setSampleBuffers ( true );
    
    if (! format . sampleBuffers ())
        qWarning ("Multisample buffer is not supported .");
    QGLFormat :: setDefaultFormat ( format );


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
