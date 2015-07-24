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
#include <dtkCore/dtkCorePlugin.h>

class dtkIoDataModelPrivate;

class DTKIO_EXPORT dtkIoDataModel : public QObject
{

public:
    enum FileMode {
        Trunc     = 0x001,
        Existing  = 0x002,
        ReadOnly  = 0x003,
        ReadWrite = 0x004
    };
    
public:
    dtkIoDataModel(void);
    virtual ~dtkIoDataModel(void);

/* public: */
/*     virtual dtkIoDataModel *clone(void) const = 0; */
/* public: */
/* virtual void *copy(dtkIoDataModel *other) 0; */

public:
    virtual void fileOpen(QString &name, FileMode mode);
    virtual void fileClose(void);

public:
    virtual void datasetCreate(QString &name, int dimension);
    virtual void datasetOpen(QString &name, FileMode mode);
    virtual void datasetClose(QString &name);
    virtual void datasetRead(QString &name);
    virtual void datasetWrite(QString &name, void *data);

public:
    dtkIoDataModelPrivate *d;
};

DTK_DECLARE_OBJECT(dtkIoDataModel*)
DTK_DECLARE_PLUGIN(dtkIoDataModel, DTKIO_EXPORT)
DTK_DECLARE_PLUGIN_FACTORY(dtkIoDataModel, DTKIO_EXPORT)
DTK_DECLARE_PLUGIN_MANAGER(dtkIoDataModel, DTKIO_EXPORT)

// 
// dtkIoDataModel.h ends here

