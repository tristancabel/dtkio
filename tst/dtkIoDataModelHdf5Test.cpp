// Version: $Id:
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkIoDataModelHdf5Test.h"

#include <dtkIo>


// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

void dtkIoDataModelHdf5TestCase::initTestCase(void)
{
    dtkIoSettings settings;
    settings.beginGroup("io");
    dtkIo::pluginManager::initialize(settings.value("plugins").toString());
    settings.endGroup();
}

void dtkIoDataModelHdf5TestCase::init(void)
{
}

void dtkIoDataModelHdf5TestCase::testOpen(void)
{

    dtkIoDataModel *data_model = dtkIo::dataModelFactory::create("dtkIoDataModelHdf5");
    QString file_name = "fileCreationTest.h5";
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);
    data_model->fileClose();

}

void dtkIoDataModelHdf5TestCase::cleanupTestCase(void)
{

}

void dtkIoDataModelHdf5TestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkIoDataModelHdf5Test, dtkIoDataModelHdf5TestCase)

//
// dtkIoDataModelHdf5Test.cpp ends here
