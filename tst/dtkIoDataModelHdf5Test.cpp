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

/*
#define DIM0_TESTSUBSET 8
#define DIM1_TESTSUBSET 10
void dtkIoDataModelHdf5TestCase::testWriteSubset(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "testWriteSubset.h5";
    if(fileExists(file_name)) {
        //delete the file
        QFile::remove(file_name);
    }
    
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);

    //initial write
    double w_data[DIM0_TESTSUBSET][DIM1_TESTSUBSET] ;
    QString dataset_name = "/testsubset";
    qlonglong shape[2] = {DIM0_TESTSUBSET, DIM1_TESTSUBSET};
    
    for(int i=0; i<DIM0_TESTSUBSET; ++i) {
        for(int j=0; j<DIM1_TESTSUBSET; ++j)
        {
            if(j< (DIM0_TESTSUBSET/2))
                w_data[i][j] = 1.0;
            else
                w_data[i][j] = 2.0;
        }
    }
    
    data_model->write(dataset_name, dtkIoDataModel::Double, 2, shape, w_data);
    data_model->fileClose();

    QVERIFY(fileExists(file_name));

    //change subset verification
    data_model->fileOpen(file_name, dtkIoDataModel::ReadWrite);

    double w_subdata[2][2] = { {5.0, 6.0} , {7.0, 8.0} };
    int offset[2] = {3,4};
    int count[2] = {2,2};
    int block[2] = {1,1};
    int stride[2] = {1,1};

    data_model->write(dataset_name, offset, stride, count, block, w_subdata);
    data_model->fileClose();

    double r_data[DIM0_TESTSUBSET][DIM1_TESTSUBSET] ;
    data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);
    data_model->read(dataset_name, dtkIoDataModel::Double, r_data);
    data_model->fileClose();
    
    QCOMPARE(r_data[0][0], 1);
    QCOMPARE(r_data[0][1], 1);
    QCOMPARE(r_data[0][8], 2);
    QCOMPARE(r_data[0][9], 2);
    QCOMPARE(r_data[7][0], 1);
    QCOMPARE(r_data[7][1], 1);
    QCOMPARE(r_data[7][8], 2);
    QCOMPARE(r_data[7][9], 2);
    QCOMPARE(r_data[3][4], w_subdata[0][0]);
    QCOMPARE(r_data[3][5], w_subdata[0][1]);
    QCOMPARE(r_data[4][4], w_subdata[1][0]);
    QCOMPARE(r_data[4][5], w_subdata[1][1]);

}
*/

void dtkIoDataModelHdf5TestCase::cleanupTestCase(void)
{

}

void dtkIoDataModelHdf5TestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkIoDataModelHdf5Test, dtkIoDataModelHdf5TestCase)

//
// dtkIoDataModelHdf5Test.cpp ends here
