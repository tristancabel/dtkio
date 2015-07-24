// dtkIoDataModelTest.cpp --- 
// 
// Version: 
// 
// 

// Commentary: 
// 
// 

// Change log:
// 
// 

#include "dtkIoDataModelTest.h"

#include <dtkIo>

void dtkIoDataModelTestCase::initTestCase(void)
{
    dtkIoSettings settings;
    settings.beginGroup("io");
    qDebug() << "plugins path:" << settings.value("plugins").toString();
    dtkIo::dataModel::pluginManager().setVerboseLoading(true);
    dtkLogger::instance().attachConsole();
    dtkLogger::instance().setLevel("trace");
    dtkIo::dataModel::initialize(settings.value("plugins").toString());
    dtkLogger::instance().setLevel("info");
    settings.endGroup();
}

void dtkIoDataModelTestCase::init(void)
{

}

void dtkIoDataModelTestCase::testPluginManager(void)
{
    qDebug() << dtkIo::dataModel::pluginManager().plugins();
}

void dtkIoDataModelTestCase::testPluginFactory(void)
{
    qDebug() << dtkIo::dataModel::pluginFactory().keys();
}

void dtkIoDataModelTestCase::testPlugin(void)
{
    dtkIoDataModel *dataModel = dtkIo::dataModel::pluginFactory().create("Hdf5");
    qDebug() << dataModel->metaObject()->className();
    delete dataModel;
}

void dtkIoDataModelTestCase::cleanupTestCase(void)
{
    dtkIo::dataModel::pluginManager().uninitialize();
}

void dtkIoDataModelTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkIoDataModelTest, dtkIoDataModelTestCase)
