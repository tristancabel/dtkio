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


namespace dtkIo
{
    // namespace pluginManager {
    //     void initialize(const QString& path) {
    //         QString realpath=path;
    //         if (path.isEmpty()) {
    //             dtkIoSettings io_settings;
    //             io_settings.beginGroup("io");
    //             realpath = io_settings.value("plugins").toString();
    //             io_settings.endGroup();
    //         }
    //         dtkIo::dataModel::initialize(realpath);
    //     }
    // }
    
    namespace dataModel {

        namespace _private {
            dtkIoDataModelPluginFactory factory;
            dtkIoDataModelPluginManager manager;
        }
        
        void initialize(const QString& path) {
            pluginFactory().record("Hdf5", dtkIoDataModelHdf5Creator);
            pluginManager().initialize(path);
        }

        dtkIoDataModelPluginManager& pluginManager(void) {
            return _private::manager;
        }

        dtkIoDataModelPluginFactory& pluginFactory(void) {
            return _private::factory;
        }
    }

    // namespace solver {

    //     namespace _private {
    //         dtkSparseSolverPluginManager manager;
    //         dtkSparseSolverPluginFactoryTemplate factoryTemplate;
    //     }

    //     void initialize(const QString& path) {
    //         pluginFactory<double>().record("dtkSparseSolverJacobiGeneric", dtkSparseSolverJacobiGenericCreator);
    //         pluginFactory<double>().record("dtkSparseSolverSymmetricGaussSeidelGeneric", dtkSparseSolverSymmetricGaussSeidelGenericGenericCreator);
    //         pluginManager().initialize(path);
    //     }

    //     dtkSparseSolverPluginManager& pluginManager(void) {
    //         return _private::manager;
    //     }

    //     dtkSparseSolverPluginFactoryTemplate& pluginFactoryTemplate(void) {
    //         return _private::factoryTemplate;
    //     }
    // }

}


//
// dtkIo.cpp ends here
