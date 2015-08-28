
#pragma once

#include "mpi.h"

#include <QFileInfo>

#include <dtkDistributed>
#include <dtkIo>

#include <unistd.h>

/*

#define DTK_DISTRIBUTED_BEGIN_GLOBAL \
    dtkDistributed::app()->communicator()->barrier(); if (dtkDistributed::communicator::instance()->rank() == 0) {

#define DTK_DISTRIBUTED_END_GLOBAL \
    } ; dtkDistributed::app()->communicator()->barrier();

#define DTK_DISTRIBUTED_BEGIN_LOCAL \
    dtkDistributed::app()->communicator()->barrier();
#define DTK_DISTRIBUTED_END_LOCAL \
    ;
*/

#define NPROC 2

#define DTK_IO_PHDF5_INIT_PLUGIN \
        dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("PHdf5"); \
        data_model->setCommunicator(dtkDistributed::app()->communicator()); \
        int rank = dtkDistributed::app()->communicator()->rank(); \
        int size = dtkDistributed::app()->communicator()->size();

static bool fileExists(QString file) {
    QFileInfo checkFile(file);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}


class testCreateRunnable : public QRunnable
{
public:
    void run(void) 
    {
        DTK_IO_PHDF5_INIT_PLUGIN
        QString file_name = "fileCreationTestP.h5";
        data_model->fileOpen(file_name, dtkIoDataModel::Trunc);
        data_model->fileClose();

        DTK_DISTRIBUTED_BEGIN_GLOBAL
        QVERIFY(fileExists(file_name));
        DTK_DISTRIBUTED_END_GLOBAL

        delete data_model;
    }
    
};


class testReadRunnable : public QRunnable
{
public:
    void run(void)
    {
        DTK_IO_PHDF5_INIT_PLUGIN
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

        delete data_model;
    }
};

/*
void dtkIoDataModelPHdf5TestCase::testWrite(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("PHdf5");
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
*/
/*
void dtkIoDataModelPHdf5TestCase::testTrunc(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("PHdf5");
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
*/

#define HYSL_NX 8
#define HYSL_NY 8
class testWriteHyperslabRowRunnable : public QRunnable
{
public:
    void run(void)
    {
        DTK_IO_PHDF5_INIT_PLUGIN
        QString file_name = "testParalWriteHyperslabRow.h5";
        QString dataset_name = "/hyperslabRow";
        //first delete the file if it already exist
        DTK_DISTRIBUTED_BEGIN_GLOBAL
        if(fileExists(file_name)) {
            //delete the file
            QFile::remove(file_name);
        }
        DTK_DISTRIBUTED_END_GLOBAL
        
        // next write the Hyperslab
        data_model->fileOpen(file_name, dtkIoDataModel::Trunc);

        //call write with no values to create the dataset

        quint64 shape_global[2] = { HYSL_NX, HYSL_NY};
        data_model->write(dataset_name, dtkIoDataModel::Double, 2, shape_global);

        //now prepare the data and write the hyperslab
        quint64 count_local[2] = {HYSL_NX/NPROC, HYSL_NY};
        int local_size = (HYSL_NX/NPROC)* HYSL_NY;
        quint64 offset[2];
        offset[0] = rank*count_local[0];
        offset[1] = 0;
        quint64 block[2] = {1,1};
        quint64 stride[2] = {1,1};
        
        double *data_local = new double[local_size];
        for(int i=0; i<local_size; ++i)
        {
            data_local[i] = rank*10.0;
        }

/*        if(rank ==0) {
            int i = 0;
            printf("PID %d , rank %d ready for attach\n", getpid(), rank);
            while (0 == i)
                sleep(5);
        }
          
        if(rank == 1) {
            int i = 0;
            printf("PID %d , rank %d ready for attach\n", getpid(), rank);
            while (0 == i)
                sleep(5);
        }
*/      
        data_model->writeHyperslab(dataset_name, dtkIoDataModel::Double, offset, stride, count_local, block, count_local, data_local);
        data_model->fileClose();

        //lastly, check written data
        double r_data[HYSL_NX*HYSL_NY] ;
        data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);
        data_model->read(dataset_name, dtkIoDataModel::Double, r_data);
        data_model->fileClose();

        DTK_DISTRIBUTED_BEGIN_GLOBAL
        for(int proc=0; proc<NPROC; ++proc)
        {
            for(int i=0; i<count_local[0]*count_local[1]; ++i)
            {
                QCOMPARE(r_data[i + proc*count_local[0]*HYSL_NY], 10.0*proc);
            }
        }
        DTK_DISTRIBUTED_END_GLOBAL

        delete[] data_local;

    }
};

/*
void dtkIoDataModelPHdf5TestCase::testWriteByCoord(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("PHdf5");
    QString file_name = "testWriteByCoord.h5";
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

    double w_subdata[4] = { 50.0, 60.0, 70.0, 80.0 };
    quint64 nb_points = 4;
    quint64 points_coord[4][2] = { {0,0}, {3,5}, {2,3}, {4,1}} ;
    
    data_model->writeByCoord(dataset_name, dtkIoDataModel::Double, nb_points, &points_coord[0][0], w_subdata);
    data_model->fileClose();

    //check written data
    double r_data[DIM0_TESTSUBSET][DIM1_TESTSUBSET] ;
    data_model->fileOpen(file_name, dtkIoDataModel::ReadOnly);
    data_model->read(dataset_name, dtkIoDataModel::Double, r_data);
    data_model->fileClose();
    
    QCOMPARE(r_data[1][0], 1.0);
    QCOMPARE(r_data[0][1], 1.0);
    QCOMPARE(r_data[0][8], 2.0);
    QCOMPARE(r_data[0][9], 2.0);
    QCOMPARE(r_data[7][0], 1.0);
    QCOMPARE(r_data[7][1], 1.0);
    QCOMPARE(r_data[7][8], 2.0);
    QCOMPARE(r_data[7][9], 2.0);
    QCOMPARE(r_data[0][0], w_subdata[0]);
    QCOMPARE(r_data[3][5], w_subdata[1]);
    QCOMPARE(r_data[2][3], w_subdata[2]);
    QCOMPARE(r_data[4][1], w_subdata[3]);

}


void dtkIoDataModelPHdf5TestCase::testReadWriteGroups(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("PHdf5");
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

void dtkIoDataModelPHdf5TestCase::testReadWriteExistingGroups(void)
{
    dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("PHdf5");
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
*/
