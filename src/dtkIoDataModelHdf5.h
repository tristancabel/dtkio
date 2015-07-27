/* dtkIoDataModelHdf5.h --- 
 * 
 * Version: 
 * 
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <dtkCore>
#include "dtkIoDataModel.h"

class dtkIodataTypeHdf5;
class dtkIoDataModelHdf5Private;

class dtkIoDataModelHdf5 : public dtkIoDataModel
{
    Q_OBJECT
    
public:
    dtkIoDataModelHdf5(void);
    ~dtkIoDataModelHdf5(void);

/* public: */
/*     dtkIoDataModelHdf5 *clone(void) const; */

/* public: */
/*     void copy(dtkIoDataModelHdf5 *other); */

public:
    void fileOpen(const QString& name, const dtkIoDataModel::FileMode& mode);
    void fileClose(void);

    
public:
    void read(const QString& dataset_name, const dtkIoDataModel::DataType& type, void *values);
    void write(const QString& dataset_name, const dtkIoDataModel::DataType& type,
               const int& dimension, qlonglong *shape, void *values);
//    void write(QString &dataset_name, qlonglong *offset, int *stride, int *count,
//               int *block, void *values);
public:
    dtkIoDataModelHdf5Private *d;
};


static dtkIoDataModel *dtkIoDataModelHdf5Creator(void)
{
    return new dtkIoDataModelHdf5();
}

//
// dtkIoDataModelHdf5.h ends here
