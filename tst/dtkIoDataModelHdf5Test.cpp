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

void dtkIoDataModelHdf5TestCase::testWrite(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "testWrite.h5";
    if(fileExists(file_name)) {
        //delete the file
        QFile::remove(file_name);
    }
    
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);

    double w_values[2][3] = { {0.4, 1.5, 2.6} , {7.7, 8.8, 9.9}};
    double r_values[2][3] = { {0.0, 0.0, 0.0} , {0.0, 0.0, 0.0}};
    qlonglong shape[2] = {2,3};
    QString dataset_name = "/smallarray";
    data_model->write(dataset_name, dtkIoDataModel::Double, 2, shape, w_values);
    data_model->fileClose();

    QVERIFY(fileExists(file_name));

    //read verification
    data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);
    data_model->read(dataset_name, dtkIoDataModel::Double, r_values);
    data_model->fileClose();
    
    QCOMPARE(r_values[0][0], w_values[0][0]);
    QCOMPARE(r_values[0][1], w_values[0][1]);
    QCOMPARE(r_values[0][2], w_values[0][2]);
    QCOMPARE(r_values[1][0], w_values[1][0]);
    QCOMPARE(r_values[1][1], w_values[1][1]);
    QCOMPARE(r_values[1][2], w_values[1][2]);

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
