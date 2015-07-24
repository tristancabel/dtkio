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
    //QString type;
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
    ;    
}

/*!
 *  Destructor
 */
dtkIoDataModel::~dtkIoDataModel(void)
{
    delete d;

    d = NULL;
}


