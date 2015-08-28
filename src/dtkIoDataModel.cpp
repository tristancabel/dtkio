// dtkIoDataModel.cpp --- 
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

#include "dtkIoDataModel.h"

class dtkIoDataModelPrivate
{
public:
    QString type;
};


// /////////////////////////////////////////////////////////////////
// dtkIoDataModel
// /////////////////////////////////////////////////////////////////


/*!
  \class dtkIoDataModel
  \inmodule dtkIo
  \brief dtkIoDataModel is the interface for input/output Data Model (ASCII, Hdf5, ..).
  
  long description

  \code
  dtkIoDataModel *data_model = dtkIo::dataModel::pluginFactory().create("Hdf5");
  QString file_name = "fileCreationTest.h5";
  data_model->fileOpen(file_name, dtkIoDataModel::Trunc);
  data_model->fileClose();
  \endcode

*/

/*! \enum dtkIoDataModel::FileMode
    \value Trunc
    \value Existing
    \value ReadOnly
    \value ReadWrite

/*!
 *  Constructor
 */
dtkIoDataModel::dtkIoDataModel(void) : QObject(), d(new dtkIoDataModelPrivate)
{
    d->type = "dtkIoDataModel";    
}

/*!
 *  Destructor
 */
dtkIoDataModel::~dtkIoDataModel(void)
{
    delete d;

    d = NULL;
}


#if defined(DTK_BUILD_DISTRIBUTED)
/*!
 * set the IO communicator
 */
void dtkIoDataModel::setCommunicator(dtkDistributedCommunicator *comm)
{
    qDebug() << __func__ << "not implemented";
}
#endif

/*!
 *  open a file using a fileMode
 */
void dtkIoDataModel::fileOpen(const QString &name, const dtkIoDataModel::FileMode& mode)
{
    qDebug() << __func__ << "not implemented";
}

/*!
 *  close the open file
 */
void dtkIoDataModel::fileClose(void)
{
    qDebug() << __func__ << "not implemented";
}

/*!
 *  Read a dataset from its name and type into buffer values
 * values has to be allocated before
 */
void dtkIoDataModel::read(const QString& dataset_name, const dtkIoDataModel::DataType& type,
                          void *values)
{
    qDebug() << __func__ << "not implemented";
}

/*!
 *  write a dataset from its name and type into the open file
 * if you call this function with nullptr in values, it will create a dataset but not write any data in it
 * type : type of data
 * dimension : number of dimensions of the data to be written and dimension of shape
 * shape : number of elements in each dimension : ex dimension = 2 , shape = {3,4} .
 * values : data to be written
 */
void dtkIoDataModel::write(const QString& dataset_name, const dtkIoDataModel::DataType& type, const int& dimension, quint64 *shape, void *values)
{
    qDebug() << __func__ << "not implemented";
}

/*! write using a hyperslab doesn't support overlapping blocks!
 *  write a subset of a dataset from its name and type into an existing dataset in the open file
 * count, offset, stride and block must be of the same size as the dimension of the dataspace. if dim = 2 , each of these parameters must be a 1-dimension array of size 2
 * offset : offset of the starting element
 * stride : determine how many elements to move from between blocks to write. 1=contiguous, 2 skip one element out of two
 * count : number of blocks to select from the dataspace in each dimension
 * block : array to determine the size of the element block selected from the dataspace
 * values_shape : number of elements in each dimension of values. must be of the dimension of the dataset dataspace
 * values : values to be written
 */
void dtkIoDataModel::writeHyperslab(const QString &dataset_name,const dtkIoDataModel::DataType& type, quint64 *offset, quint64 *stride, quint64 *count, quint64 *block, quint64 *values_shape, void *values)
{
    qDebug() << __func__ << "not implemented";
}

/*! write using coordinates.
 * dataset_name : name of the dataset
 * type : type of the dataset
 * nb_points : number of values to write
 * points_coord : pointer to a 2D array [NB_POINTS][DIMENSIONS] . points_coord[0][0]=1, points_coord[0][1]=2 means that the point 0 to write have coordinates {1,2} in the file
 * values : values to write . values to write need to be contiguous
 */
void dtkIoDataModel::writeByCoord(const QString &dataset_name, const dtkIoDataModel::DataType& type, const quint64& nb_points, quint64* points_coord, void *values)
{
    qDebug() << __func__ << "not implemented";
}
