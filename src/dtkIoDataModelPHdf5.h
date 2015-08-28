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

class dtkIodataTypePHdf5;
class dtkIoDataModelPHdf5Private;

class dtkIoDataModelPHdf5 : public dtkIoDataModel
{
    Q_OBJECT
    
public:
    dtkIoDataModelPHdf5(void);
    ~dtkIoDataModelPHdf5(void);

public:
    void setCommunicator(dtkDistributedCommunicator *comm) override;
public:
    void fileOpen(const QString& name, const dtkIoDataModel::FileMode& mode) override;
    void fileClose(void)  override;

    
public:
    void read(const QString& dataset_name, const dtkIoDataModel::DataType& type, void *values)  override;
//    void readHyperslab();
    
public:
    void write(const QString& dataset_name, const dtkIoDataModel::DataType& type,
               const int& dimension, quint64 *shape, void *values=nullptr)  override;
    void writeHyperslab(const QString &dataset_name, const dtkIoDataModel::DataType& type, quint64 *offset, quint64 *stride, quint64 *count, quint64 *block, quint64 *values_shape, void *values)  override;
//    void writeByCoord(const QString &dataset_name, const dtkIoDataModel::DataType& type, const quint64& nb_points, quint64* points_coord, void *values);
//        void writeByCoord(const QString &dataset_name, const dtkIoDataModel::DataType& type, const quint64& nb_points, quint64* points_coord, quint64* values_coord, void *values);
    
public:
    dtkIoDataModelPHdf5Private *d;
};


static dtkIoDataModel *dtkIoDataModelPHdf5Creator(void)
{
    return new dtkIoDataModelPHdf5();
}

//
// dtkIoDataModelPHdf5.h ends here
