// Version: $Id: $
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkIoExport.h"
#include "dtkIo.h"
#include "dtkIoSettings.h"
#include "dtkIoDataModel.h"

#include "dtkIoDataModelHdf5.h"

#ifdef ADD_PHDF5
#include "dtkIoDataModelPHdf5.h"
#endif

namespace dtkIo
{

    namespace dataModel {

        namespace _private {
            dtkIoDataModelPluginFactory factory;
            dtkIoDataModelPluginManager manager;
        }
        
        void initialize(const QString& path) {
            pluginFactory().record("Hdf5", dtkIoDataModelHdf5Creator);
#ifdef ADD_PHDF5
            pluginFactory().record("PHdf5", dtkIoDataModelPHdf5Creator);
#endif
            pluginManager().initialize(path);
        }

        dtkIoDataModelPluginManager& pluginManager(void) {
            return _private::manager;
        }

        dtkIoDataModelPluginFactory& pluginFactory(void) {
            return _private::factory;
        }
    }

}
//
// dtkIo.cpp ends here
