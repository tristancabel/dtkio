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
               const int& dimension, quint64 *shape, void *values);
    void writeHyperslab(const QString &dataset_name, const dtkIoDataModel::DataType& type, quint64 *offset, quint64 *stride, quint64 *count, quint64 *block, quint64 *values_shape, void *values);
    void writeByCoord(const QString &dataset_name, const dtkIoDataModel::DataType& type, const quint64& nb_points, quint64* points_coord, void *values);
    
public:
    dtkIoDataModelHdf5Private *d;
};


static dtkIoDataModel *dtkIoDataModelHdf5Creator(void)
{
    return new dtkIoDataModelHdf5();
}

//
// dtkIoDataModelHdf5.h ends here
