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


// /////////////////////////////////////////////////////////////////
// dtkIoDataModelHdf5Private
// /////////////////////////////////////////////////////////////////
class dtkIoDataModelHdf5Private
{
public:
    hid_t file_id;
    herr_t status;
    bool file_open;

public:
    bool fileExists(QString file);
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

// /////////////////////////////////////////////////////////////////
// dtkIoDataModelHdf5
// /////////////////////////////////////////////////////////////////
dtkIoDataModelHdf5::dtkIoDataModelHdf5(void) : dtkIoDataModel(), d(new dtkIoDataModelHdf5Private)
{
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
    d->status = H5Fclose(d->file_id);
    d->file_open = false;
}
