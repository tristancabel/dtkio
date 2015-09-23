// Version: $Id:
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkIoDataModelPHdf5Test.h"
#include "dtkIoDataModelPHdf5Runnable.h"

#include <dtkDistributed/dtkDistributedPolicy>

#include <QFileInfo>
#include <dtkIo>

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

void dtkIoDataModelPHdf5TestCase::initTestCase(void)
{
    dtkDistributedSettings dsettings;
    dsettings.beginGroup("communicator");
    dtkDistributed::communicator::pluginManager().initialize(dsettings.value("plugins").toString());
    dsettings.endGroup();
    dtkDistributed::policy()->setType("mpi3");

    dtkIoSettings settings;
    settings.beginGroup("io");
    dtkIo::dataModel::initialize(settings.value("plugins").toString());
    settings.endGroup();

    for (int i = 1; i < NPROC; ++i) {
        dtkDistributed::policy()->addHost("localhost");
    }

    dtkDistributed::spawn();
}

void dtkIoDataModelPHdf5TestCase::init(void)
{
}

void dtkIoDataModelPHdf5TestCase::testCreate(void)
{
    QRunnable *test = new testCreateRunnable();
    dtkDistributed::exec(test);
    delete test;
    
}

void dtkIoDataModelPHdf5TestCase::testRead(void)
{
    QRunnable *test = new testReadRunnable();
    dtkDistributed::exec(test);
    delete test;    
}

void dtkIoDataModelPHdf5TestCase::testWriteHyperslabRow(void)
{
    QRunnable *test = new testWriteHyperslabRowRunnable();
    dtkDistributed::exec(test);
    delete test;    
}

void dtkIoDataModelPHdf5TestCase::testWriteByCoord(void)
{
    QRunnable *test = new testWriteByCoordRunnable();
    dtkDistributed::exec(test);
    delete test;    
}

void dtkIoDataModelPHdf5TestCase::testWriteByCoordGroup(void)
{
    QRunnable *test = new testWriteByCoordGroupRunnable();
    dtkDistributed::exec(test);
    delete test;    
}

void dtkIoDataModelPHdf5TestCase::cleanupTestCase(void)
{
    dtkDistributed::unspawn();
    dtkDistributed::communicator::pluginManager().uninitialize();
    //  dtkIo::dataModel::uninitialize();
}

void dtkIoDataModelPHdf5TestCase::cleanup(void)
{

}

DTKDISTRIBUTEDTEST_MAIN_NOGUI(dtkIoDataModelPHdf5Test, dtkIoDataModelPHdf5TestCase)

//
// dtkIoDataModelPHdf5Test.cpp ends here
