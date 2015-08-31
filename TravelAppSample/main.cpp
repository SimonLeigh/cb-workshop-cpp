#include <QApplication>
#include <QDebug>
#include <stdio.h>
#include "mainwindow.h"
#include "demo/democouchbaseconnect.h"
#include "demo/democouchbaseget.h"
#include "demo/democouchbaseupsert.h"
#include "demo/democouchbasedelete.h"
#include "demo/democouchbaseincr.h"
#include "demo/democouchbasemultiget.h"
#include "demo/democouchbaseview.h"
#include "demo/democouchbasen1cl.h"

int main(int argc, char *argv[])
{
    qDebug() << "Starting demo application ...";

    CBDataSourceFactory::Create("couchbase://localhost/travel-sample");

//    //Demos/Test
//    DemoCouchbaseConnect connectDemo;
//    connectDemo.test();

//    DemoCouchbaseGet getDemo;
//    getDemo.test();
    
//    DemoCouchbaseUpsert upsertDemo;
//    upsertDemo.test();
    
//    DemoCouchbaseDelete deleteDemo;
//    deleteDemo.test();

//    DemoCouchbaseIncr incrDemo;
//    incrDemo.test();

//    DemoCouchbaseMultiGet multiGetDemo;
//    multiGetDemo.test();

//    DemoCouchbaseView viewDemo;
//    viewDemo.test();

//    DemoCouchbaseN1cl n1clDemo;
//    n1clDemo.test();

    //Window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int applicationresult = a.exec();
    CBDataSourceFactory::Instance().Destroy();
    return applicationresult;
}
