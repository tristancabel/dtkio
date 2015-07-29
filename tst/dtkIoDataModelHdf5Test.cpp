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
    quint64 shape[2] = {2,3};
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

void dtkIoDataModelHdf5TestCase::testTrunc(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "testTrunc.h5";
    if(fileExists(file_name)) {
        //delete the file
        QFile::remove(file_name);
    }
    
    data_model->fileOpen(file_name, dtkIoDataModel::NotExisting);

    double w_values[2][3] = { {0.4, 1.5, 2.6} , {7.7, 8.8, 9.9}};
    quint64 shape[2] = {2,3};
    QString dataset_name = "/smallarray";
    data_model->write(dataset_name, dtkIoDataModel::Double, 2, shape, w_values);
    data_model->fileClose();

    QVERIFY(fileExists(file_name));

    //modify the data
    shape[0] = 3;
    shape[1] = 4;
    double w_values2[3][4] = { {-0.4, -1.5, -2.6, 32.5} , {-76.733, 188.8, 569.9, 25.3},
                               {-76.733, 188.8, 569.9, 25.3}};
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);
    data_model->write(dataset_name, dtkIoDataModel::Double, 2, shape, w_values2);
    data_model->fileClose();

    //read verification
    double r_values[3][4] = { {0.0, 0.0, 0.0} , {0.0, 0.0, 0.0}};
    data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);
    data_model->read(dataset_name, dtkIoDataModel::Double, r_values);
    data_model->fileClose();
    
    QCOMPARE(r_values[0][0], w_values2[0][0]);
    QCOMPARE(r_values[0][1], w_values2[0][1]);
    QCOMPARE(r_values[0][2], w_values2[0][2]);
    QCOMPARE(r_values[0][3], w_values2[0][3]);
    QCOMPARE(r_values[1][0], w_values2[1][0]);
    QCOMPARE(r_values[1][1], w_values2[1][1]);
    QCOMPARE(r_values[1][2], w_values2[1][2]);
    QCOMPARE(r_values[1][3], w_values2[1][3]);
    QCOMPARE(r_values[2][0], w_values2[2][0]);
    QCOMPARE(r_values[2][1], w_values2[2][1]);
    QCOMPARE(r_values[2][2], w_values2[2][2]);
    QCOMPARE(r_values[2][3], w_values2[2][3]);
}


#define DIM0_TESTSUBSET 8
#define DIM1_TESTSUBSET 10
void dtkIoDataModelHdf5TestCase::testWriteHyperslab(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "testWriteSubset.h5";
    if(fileExists(file_name)) {
        //delete the file
        QFile::remove(file_name);
    }

    // Write initial data
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);
    double w_data[DIM0_TESTSUBSET][DIM1_TESTSUBSET] ;
    QString dataset_name = "/testsubset";
    quint64 shape[2] = {DIM0_TESTSUBSET, DIM1_TESTSUBSET};
    
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

    // Write Hyperslab changes
    data_model->fileOpen(file_name, dtkIoDataModel::ReadWrite);

    double w_subdata[2][2] = { {5.0, 6.0} , {7.0, 8.0} };
    quint64 offset[2] = {3,4};
    quint64 count[2] = {2,2};
    quint64 block[2] = {1,1};
    quint64 stride[2] = {1,1};
    quint64 values_shape[2] = {2,2};
    
    data_model->write(dataset_name, dtkIoDataModel::Double, offset, stride, count, block, values_shape, w_subdata);
    data_model->fileClose();


    //check written data
    double r_data[DIM0_TESTSUBSET][DIM1_TESTSUBSET] ;
    data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);
    data_model->read(dataset_name, dtkIoDataModel::Double, r_data);
    data_model->fileClose();
    
    QCOMPARE(r_data[0][0], 1.0);
    QCOMPARE(r_data[0][1], 1.0);
    QCOMPARE(r_data[0][8], 2.0);
    QCOMPARE(r_data[0][9], 2.0);
    QCOMPARE(r_data[7][0], 1.0);
    QCOMPARE(r_data[7][1], 1.0);
    QCOMPARE(r_data[7][8], 2.0);
    QCOMPARE(r_data[7][9], 2.0);
    QCOMPARE(r_data[3][4], w_subdata[0][0]);
    QCOMPARE(r_data[3][5], w_subdata[0][1]);
    QCOMPARE(r_data[4][4], w_subdata[1][0]);
    QCOMPARE(r_data[4][5], w_subdata[1][1]);

}


void dtkIoDataModelHdf5TestCase::testReadWriteGroups(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "testReadWriteGroups.h5";
    if(fileExists(file_name)) {
        //delete the file
        QFile::remove(file_name);
    }
    
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);

    double w_values[2][3] = { {0.4, 1.5, 2.6} , {7.7, 8.8, 9.9}};
    double r_values[2][3] = { {0.0, 0.0, 0.0} , {0.0, 0.0, 0.0}};
    quint64 shape[2] = {2,3};
    QString dataset_name = "/myGroup/smallarray";
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

void dtkIoDataModelHdf5TestCase::testReadWriteExistingGroups(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
    QString file_name = "testReadWriteExistingGroups.h5";
    if(fileExists(file_name)) {
        //delete the file
        QFile::remove(file_name);
    }
    
    data_model->fileOpen(file_name, dtkIoDataModel::Trunc);

    double w_values[2][3] = { {0.4, 1.5, 2.6} , {7.7, 8.8, 9.9}};
    double r_values[2][3] = { {0.0, 0.0, 0.0} , {0.0, 0.0, 0.0}};
    quint64 shape[2] = {2,3};
    QString dataset_name = "/myGroup/smallarray";
    data_model->write(dataset_name, dtkIoDataModel::Double, 2, shape, w_values);
    data_model->fileClose();

    QVERIFY(fileExists(file_name));

    //modify group
    data_model->fileOpen(file_name, dtkIoDataModel::ReadWrite);
    double w_values2[2][3] = { {-0.4, -1.5, -2.6} , {-7.7, -8.8, -9.9}};
    double r_values2[2][3] = { {0.0, 0.0, 0.0} , {0.0, 0.0, 0.0}};
    QString dataset_name2 = "/myGroup/negativearray";
    data_model->write(dataset_name2, dtkIoDataModel::Double, 2, shape, w_values2);
    data_model->fileClose();
    
    //read verification
    data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);
    data_model->read(dataset_name, dtkIoDataModel::Double, r_values);
    data_model->read(dataset_name2, dtkIoDataModel::Double, r_values2);
    data_model->fileClose();
    
    QCOMPARE(r_values[0][0], w_values[0][0]);
    QCOMPARE(r_values[0][1], w_values[0][1]);
    QCOMPARE(r_values[0][2], w_values[0][2]);
    QCOMPARE(r_values[1][0], w_values[1][0]);
    QCOMPARE(r_values[1][1], w_values[1][1]);
    QCOMPARE(r_values[1][2], w_values[1][2]);

    QCOMPARE(r_values2[0][0], w_values2[0][0]);
    QCOMPARE(r_values2[0][1], w_values2[0][1]);
    QCOMPARE(r_values2[0][2], w_values2[0][2]);
    QCOMPARE(r_values2[1][0], w_values2[1][0]);
    QCOMPARE(r_values2[1][1], w_values2[1][1]);
    QCOMPARE(r_values2[1][2], w_values2[1][2]);

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
