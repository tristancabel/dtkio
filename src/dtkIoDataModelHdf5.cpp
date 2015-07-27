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

#include "H5Cpp.h"

//#define HDF5_DATATYPE(n) ( n==1 ? H5T_NATIVE_INT : ( n==2 ? H5T_NATIVE_LLONG : ( n==3 ? H5T_NATIVE_DOUBLE : -1)))
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
    H5::H5File *file;
    herr_t status;
    QString type;

public:
    QHash<QString, H5::DataSet > dataset_hash; // map of the open datasets

    
public:
    bool fileExists(const QString& file);
    H5::DataSet& openDataset(const QString& dataset_name);
    H5::DataSet& createDataset(const QString &dataset_name, const dtkIoDataModel::DataType& type,
                               const int& dim, qlonglong *shape);
    
};

bool dtkIoDataModelHdf5Private::fileExists(const QString& file) {
    QFileInfo checkFile(file);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

//return the dataset to read from if it exist in the file
H5::DataSet& dtkIoDataModelHdf5Private::openDataset(const QString& dataset_name) {
    
    if(file == nullptr)
        dtkError() << "file is not open! ";

    H5::DataSet dataset;
    //check if the dataset is open. if not, open it
    if(!dataset_hash.contains(dataset_name)) {
        dtkInfo() << "opening dataset" << dataset_name;
        //open the dataset
        dataset = file->openDataSet(dataset_name.toUtf8().constData());

        if(dataset.getId()>0)
            dataset_hash[dataset_name] = dataset;
        else
            dtkError() << "Dataset" << dataset_name << "not existing, in file";
    }

    return dataset_hash[dataset_name];
}

// create a dataset or return the identifier if we already created it
H5::DataSet& dtkIoDataModelHdf5Private::createDataset(const QString& dataset_name,
                                                     const dtkIoDataModel::DataType& type,
                                                     const int& dim, qlonglong *shape)
{
    if(file == nullptr) {
        dtkError() << "file is not open! ";
    }

    H5::DataSet dataset;
    if(!dataset_hash.contains(dataset_name)) {
        dtkInfo() << "Dataset not existing, creating DataSet" << dataset_name;

        //create a dataspace
        //TODO a cast ?
        hsize_t h_shape[dim];
        for(int i=0; i<dim; ++i)
            h_shape[i]=shape[i];
        H5::DataSpace dataspace(dim, h_shape);

        switch(type) {
        case dtkIoDataModel::Int:
        {
            H5::DataType datatype( H5::PredType::NATIVE_INT);            
            //datatype.setOrder(H5T_ORDER_LE); //little endian order
            dataset_hash[dataset_name] = file->createDataSet(dataset_name.toUtf8().constData(), datatype, dataspace);
            break;
        }
        case dtkIoDataModel::LongLongInt:
        {
            H5::DataType datatype( H5::PredType::NATIVE_LLONG);            
            //datatype.setOrder(H5T_ORDER_LE); //little endian order
            dataset_hash[dataset_name] = file->createDataSet(dataset_name.toUtf8().constData(), datatype, dataspace);
            break;
        }
        case dtkIoDataModel::Double:
        {
            H5::DataType datatype( H5::PredType::NATIVE_DOUBLE);            
            //datatype.setOrder(H5T_ORDER_LE); //little endian order
            dataset_hash[dataset_name] = file->createDataSet(dataset_name.toUtf8().constData(), datatype, dataspace);
            break;
        }
        default:
            dtkError() <<" datatype not supported";
        };
    }
    
    return dataset_hash[dataset_name];
}

// /////////////////////////////////////////////////////////////////
// dtkIoDataModelHdf5
// /////////////////////////////////////////////////////////////////
dtkIoDataModelHdf5::dtkIoDataModelHdf5(void) : dtkIoDataModel(), d(new dtkIoDataModelHdf5Private)
{
    d->type = "HDF5";
    d->file = nullptr;
}

dtkIoDataModelHdf5::~dtkIoDataModelHdf5(void)
{
    if(d->file != nullptr)
        this->fileClose();
    
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


void dtkIoDataModelHdf5::fileOpen(const QString &file_name, const dtkIoDataModel::FileMode& mode)
{
    //if file is already open tell it to the user and return 
    if(d->file == nullptr) {
        switch (mode) {
        case dtkIoDataModel::Trunc:
            d->file = new H5::H5File(file_name.toUtf8().constData(), H5F_ACC_TRUNC);
            break;
        case dtkIoDataModel::Existing:
            d->file = new H5::H5File(file_name.toUtf8().constData(), H5F_ACC_EXCL);
            break;
        case dtkIoDataModel::ReadOnly:
            d->file = new H5::H5File(file_name.toUtf8().constData(), H5F_ACC_RDONLY);
            break;
        case dtkIoDataModel::ReadWrite:
            d->file = new H5::H5File(file_name.toUtf8().constData(), H5F_ACC_RDWR);
            break;
        default:
            dtkError() << "unsupported fileMode";
        };

        if(!d->file) {
            dtkError() << "error in fileOpen for file_name " << file_name;
        }
    }
    else {
        qDebug() << "File" << file_name << "is already open, please close it before opening a new one";
    }
}

void dtkIoDataModelHdf5::fileClose(void)
{
    //close all the open datasets
    QHash<QString, H5::DataSet>::iterator it;
    for(it = d->dataset_hash.begin(); it != d->dataset_hash.end(); ++it) {
        qDebug() << "closing dataset" << it.key();
        it.value().close();
     }
    
//    for(auto it: d->dataset_hash.keys()) {
//        qDebug() << "closing dataset" << it;
//        H5Dclose(d->dataset_hash.value(it));
//    }
    
    d->dataset_hash.clear();
    d->file->close();
    delete d->file;
    d->file = nullptr;
}


void dtkIoDataModelHdf5::read(const QString &dataset_name, const dtkIoDataModel::DataType& type, void *values)
{
    switch(type) {
    case dtkIoDataModel::Int:
    {
        H5::DataType datatype( H5::PredType::NATIVE_INT);      
        d->openDataset(dataset_name).read(values, datatype);
        break;
    }
    case dtkIoDataModel::LongLongInt:
    {
        H5::DataType datatype( H5::PredType::NATIVE_LLONG);
        d->openDataset(dataset_name).read(values, datatype);
        break;
    }
    case dtkIoDataModel::Double:
    {
        H5::DataType datatype( H5::PredType::NATIVE_DOUBLE);            
        d->openDataset(dataset_name).read(values, datatype);
        break;
    }
    default:
        dtkError() << "read method: Datatype not supported";
    };
}


                                  

/*! write data in the open file
 * dimensions 
 */
void dtkIoDataModelHdf5::write(const QString& dataset_name, const dtkIoDataModel::DataType& type,
                               const int& dimension, qlonglong *shape, void *values)
{
    switch(type) {
    case dtkIoDataModel::Int:
    {
        H5::DataType datatype( H5::PredType::NATIVE_INT);      
        d->createDataset(dataset_name, type, dimension, shape).write(values, datatype);
        break;
    }
    case dtkIoDataModel::LongLongInt:
    {
        H5::DataType datatype( H5::PredType::NATIVE_LLONG);
        d->createDataset(dataset_name, type, dimension, shape).write(values, datatype);
        break;
    }
    case dtkIoDataModel::Double:
    {
        H5::DataType datatype( H5::PredType::NATIVE_DOUBLE);            
        d->createDataset(dataset_name, type, dimension, shape).write(values, datatype);
        break;
    }
    default:
        dtkError() << "write method: Datatype not supported";
    };
}

/*
void dtkIoDataModelHdf5::write(QString &dataset_name, qlonglong *offset, int *stride, int *count,
                               int *block, void *values)
{
       if(block[0] != 1)
           qDebug() << " block size != 1 not supported!! ";

       hid_t dataset_id = d->openDataset(dataset_name);
       //original dataspace
       hid_t dataspace_id = H5Dget_space (dataset_id);
       
       // dataspace to write to
       status = H5Sselect_hyperslab (dataspace_id, H5S_SELECT_SET, offset,
                                     stride, count, block);
       hid_t memspace_id = H5Screate_simple (RANK, count, NULL); 




       // Write a subset of data to the dataset, then read the 
       //entire dataset back from the file.  

    printf ("\nWrite subset to file specifying:\n");
    printf ("    offset=1x2 stride=1x1 count=3x4 block=1x1\n");
    for (j = 0; j < DIM0_SUB; j++) {
	for (i = 0; i < DIM1_SUB; i++)
	   sdata[j][i] = 5;
    }     

    status = H5Dwrite (dataset_id, H5T_NATIVE_INT, memspace_id,
                       dataspace_id, H5P_DEFAULT, sdata);
       
}
*/
