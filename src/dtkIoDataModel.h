/* dtkIoDataModel.h --- 
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

#include "dtkIoExport.h"

#include <QtCore>
#include <dtkCore>

#if defined(DTK_BUILD_DISTRIBUTED)
#include <dtkDistributed/dtkDistributedCommunicator.h>
#endif

class dtkIoDataModelPrivate;

class DTKIO_EXPORT dtkIoDataModel : public QObject
{
    Q_OBJECT
    
public:
    enum FileMode {
        Trunc     = 0x001,
        NotExisting  = 0x002,
        ReadOnly  = 0x003,
        ReadWrite = 0x004
    };

    enum DataType {
        Int = 1,
        LongLongInt = 2,
        Double = 3,
    };        
        
public:
    dtkIoDataModel(void);
    virtual ~dtkIoDataModel(void);

/* public: */
/*     virtual dtkIoDataModel *clone(void) const = 0; */
/* public: */
/* virtual void *copy(dtkIoDataModel *other) 0; */

#if defined(DTK_BUILD_DISTRIBUTED)
public:
    virtual void setCommunicator(dtkDistributedCommunicator *comm);
#endif
    
public:
    virtual void fileOpen(const QString& name, const FileMode& mode);
    virtual void fileClose(void);

public:
    virtual void read(const QString& dataset_name, const dtkIoDataModel::DataType& type,
                      void *values);
    virtual void write(const QString &dataset_name, const dtkIoDataModel::DataType& type, const int& dimension, quint64 *shape, void *values);
    virtual void writeHyperslab(const QString &dataset_name, const dtkIoDataModel::DataType& type, quint64 *offset, quint64 *stride, quint64 *count, quint64 *block, quint64 *values_shape, void *values);
    virtual void writeByCoord(const QString &dataset_name, const dtkIoDataModel::DataType& type, const quint64& nb_points, quint64* points_coord, void *values);
    
/* public: */
/*     virtual void datasetCreate(QString &name, int dimension); */
/*     virtual void datasetOpen(QString &name, FileMode mode); */
/*     virtual void datasetClose(QString &name); */
/*     virtual void datasetRead(QString &name); */
/*     virtual void datasetWrite(QString &name, void *data); */

public:
    dtkIoDataModelPrivate *d;
};

DTK_DECLARE_OBJECT(dtkIoDataModel*)
DTK_DECLARE_PLUGIN(dtkIoDataModel, DTKIO_EXPORT)
DTK_DECLARE_PLUGIN_FACTORY(dtkIoDataModel, DTKIO_EXPORT)
DTK_DECLARE_PLUGIN_MANAGER(dtkIoDataModel, DTKIO_EXPORT)

// 
// dtkIoDataModel.h ends here

