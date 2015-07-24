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
  \brief dtkIoDataModel is the interface for input/output Data Model (ASCII, hdf5, ..).
  
  long description

  \code
  exemple of code
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


void dtkIoDataModel::fileOpen(QString &name, dtkIoDataModel::FileMode mode)
{
    qDebug() << "dtkIoDataModel::fileOpen not implemented";
}

void dtkIoDataModel::fileClose(void)
{
       qDebug() << "dtkIoDataModel::fileClose not implemented";
}

void dtkIoDataModel::read(QString &dataset_name, dtkIoDataModel::DataType type, void *values)
{
       qDebug() << "dtkIoDataModel::read not implemented";
}


void dtkIoDataModel::write(QString &dataset_name, dtkIoDataModel::DataType type, int dimension,
                           qlonglong *shape, void *values)
{
    qDebug() << "dtkIoDataModel::write not implemented";
}
