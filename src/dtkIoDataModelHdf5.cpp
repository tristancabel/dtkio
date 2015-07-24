// dtkIoDataModelHdf5.cpp --- 
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

#include <QFileInfo>

#include "dtkIoDataModelHdf5.h"

#include "hdf5.h"

#define HDF5_DATATYPE(n) ( n==1 ? H5T_NATIVE_INT : ( n==2 ? H5T_NATIVE_LLONG : ( n==3 ? H5T_NATIVE_DOUBLE : -1)))
// other available types : H5T_NATIVE_HBOOL //hbool_t
//    H5T_NATIVE_FLOAT
//        H5T_NATIVE_B64  // 64-bit buffer in memory
//        H5T_C_S1  // c string size in bytes



// /////////////////////////////////////////////////////////////////
// dtkIoDataModelHdf5Private
// /////////////////////////////////////////////////////////////////
class dtkIoDataModelHdf5Private
{
public:
    hid_t file_id;
    herr_t status;
    bool file_open;
    QString type;

public:
    QHash<QString, hid_t> dataset_hash; // map of the open datasets

    
public:
    bool fileExists(QString file);
    hid_t initRead(QString &dataset_name);

};

bool dtkIoDataModelHdf5Private::fileExists(QString file) {
    QFileInfo checkFile(file);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

hid_t dtkIoDataModelHdf5Private::initRead(QString &dataset_name) {
    if(!file_open)
        dtkError() << "file is not open! ";

    hid_t dataset;
    //check if the dataset is open. if not, open it
    if(!dataset_hash.contains(dataset_name)) {
        //open the dataset
        dataset = H5Dopen2(file_id ,dataset_name.toUtf8().constData(), H5P_DEFAULT);

        if(dataset>0)
            dataset_hash[dataset_name] = dataset;
        else
            dtkError() << "Dataset" << dataset_name << "not existing, in file";
    }
    else
        dataset = dataset_hash[dataset_name];

    return dataset;
}

// /////////////////////////////////////////////////////////////////
// dtkIoDataModelHdf5
// /////////////////////////////////////////////////////////////////
dtkIoDataModelHdf5::dtkIoDataModelHdf5(void) : dtkIoDataModel(), d(new dtkIoDataModelHdf5Private)
{
    d->type = "HDF5";
    d->file_open=false;
}

dtkIoDataModelHdf5::~dtkIoDataModelHdf5(void)
{
    delete d;

    d = NULL;
}

// const dtkIoDataModelHdf5 *dtkIoDataModelHdf5::clone(void)
// {
//     other = new dtkIoDataModelHdf5(void);

//     return other;
// }

// void dtkIoDataModelHdf5::copy(dtkIoDataModelHdf5 *other)
// {
//     d = other->d;
// }


void dtkIoDataModelHdf5::fileOpen(QString &file_name, dtkIoDataModel::FileMode mode)
{
    //if file is already open tell it to the user and return 
    if(d->file_open) {
        qDebug() << "File" << file_name << "is already open, please close it before opening a new one";
    }
    else {
        switch (mode) {
        case dtkIoDataModel::Trunc:
            d->file_id = H5Fcreate(file_name.toUtf8().constData(), H5F_ACC_TRUNC,
                                   H5P_DEFAULT, H5P_DEFAULT);
            break;
        case dtkIoDataModel::Existing:
            d->file_id = H5Fcreate(file_name.toUtf8().constData(), H5F_ACC_EXCL,
                                   H5P_DEFAULT, H5P_DEFAULT);
            break;
        case dtkIoDataModel::ReadOnly:
            d->file_id = H5Fopen(file_name.toUtf8().constData(), H5F_ACC_RDONLY, H5P_DEFAULT);
            break;
        case dtkIoDataModel::ReadWrite:
            d->file_id = H5Fopen(file_name.toUtf8().constData(), H5F_ACC_RDWR, H5P_DEFAULT);
            break;
        default:
            dtkError() << "unsupported fileMode";
        };
        d->file_open = true;
    }
}

void dtkIoDataModelHdf5::fileClose(void)
{
    //close all the open datasets
    QHash<QString, hid_t>::iterator it;
    for(it = d->dataset_hash.begin(); it != d->dataset_hash.end(); ++it) {
        qDebug() << "closing dataset" << it.key();
        H5Dclose(it.value());
    }
    
    d->status = H5Fclose(d->file_id);
    d->file_open = false;
}


void dtkIoDataModelHdf5::read(QString &dataset_name, dtkIoDataModel::DataType type, void *values)
{
    hid_t dataset = d->initRead(dataset_name);
    
    //reading data into values
    if(H5Dread(dataset, HDF5_DATATYPE(type), H5S_ALL, H5S_ALL, H5P_DEFAULT, values) <0)
        dtkError() << "Error reading dataset" << dataset_name;
}


                                  

/*! write data in the open file
 * dimensions 
 */
/*void dtkIoDataModelHdf5::write(QString &dataset_name, int *dimensions, int *indexes, void *values)
{
    if(!d->file_open) {
        dtkError() << "file is not open! ";
    }

    if(!d->dataSet(dataset_name)) {
        dtkInfo() << "Dataset not existing, creating DataSet" << name;

    }

    //Set the values in the file;

}
*/
