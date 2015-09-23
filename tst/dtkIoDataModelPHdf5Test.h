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

#pragma once

#include <dtkTest>

class dtkIoDataModelPHdf5TestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreate(void);
    void testRead(void);
    void testWriteHyperslabRow(void);
    void testWriteByCoord(void);
    void testWriteByCoordGroup(void);    
private slots:
    virtual void cleanupTestCase(void);
    virtual void cleanup(void);
};


//
// dtkIoDataModelPHdf5Test.h ends here
