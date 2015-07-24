// Version: $Id: 447bbe07fa943e3970bc4828b2b96190f7b17811 $
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkIoExport.h"

#include <dtkCore>

#include "dtkIoDataModel.h"

// ///////////////////////////////////////////////////////////////////
// dtkIo factories and managers
// ///////////////////////////////////////////////////////////////////

namespace dtkIo
{
//    namespace pluginManager {
//        DTKIO_EXPORT void initialize(const QString& path = "");
//    }

    namespace dataModel {
        DTKIO_EXPORT void                          initialize(const QString& path);
        DTKIO_EXPORT dtkIoDataModelPluginFactory&  pluginFactory(void);
        DTKIO_EXPORT dtkIoDataModelPluginManager&  pluginManager(void);
//        DTKIO_EXPORT dtkIoDataModelPluginFactoryTemplate& pluginFactoryTemplate(void);

    }

//    namespace dataModelFactory {
//        dtkIoDataModel *create(const QString& dataModel_type);
//    }
}

// ///////////////////////////////////////////////////////////////////
// dtkIo template implementations
// ///////////////////////////////////////////////////////////////////

/* inline dtkIoDataModelPluginFactory& dtkIo::dataModel::pluginFactory(void) */
/* { */
/*     return *dtkIo::dataModel::pluginFactoryTemplate().pluginFactory<dtkIoDataModelPluginFactory<T> >(); */
/* } */

/* inline dtkIoDataModel *dtkIo::dataModelFactory::create(const QString& dataModel_type) */
/* { */
/*     dtkIoDataModel *dataModel = dtkIo::dataModel::pluginFactory().create(dataModel_type); */
/*     if (!dataModel) { */
/*         qDebug() << Q_FUNC_INFO << "Error, dataModel " << dataModel_type << " does not exist or is not registered."; */
/*     } */

/*     return dataModel; */
/* } */

//
// dtkIo.h ends here
