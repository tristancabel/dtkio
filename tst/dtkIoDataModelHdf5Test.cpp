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

#include <QFileInfo>
#include <dtkIo>

bool fileExists(QString file) {
    QFileInfo checkFile(file);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

void dtkIoDataModelHdf5TestCase::initTestCase(void)
{
    dtkIoSettings settings;
    settings.beginGroup("io");
    dtkIo::dataModel::initialize(settings.value("plugins").toString());
    settings.endGroup();
}

void dtkIoDataModelHdf5TestCase::init(void)
{
}

void dtkIoDataModelHdf5TestCase::testCreate(void)
{

    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "fileCreationTest.h5";
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);
    data_model->fileClose();

    QVERIFY(fileExists(file_name));
}

void dtkIoDataModelHdf5TestCase::testRead(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "example.h5";
    data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);

    int dset_data[6][15];
    QString dataset_name = "/dset";
    data_model->read(dataset_name, dtkIoDataModel::Int, dset_data);
    
    data_model->fileClose();

    QCOMPARE(dset_data[0][0], 1);
    QCOMPARE(dset_data[0][1], 2);
    QCOMPARE(dset_data[1][0], 16);
    QCOMPARE(dset_data[5][0], 76);
    QCOMPARE(dset_data[5][14], 90);
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
