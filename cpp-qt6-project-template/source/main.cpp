#include <QCoreApplication>

#include "sample.h"

int main(int argc, char **argv) 
{
    SampleObject sm;
    QCoreApplication app(argc,argv);

    return app.exec();
}