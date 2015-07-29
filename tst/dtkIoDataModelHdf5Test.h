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

class dtkIoDataModelHdf5TestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreate(void);
    void testRead(void);
    void testWrite(void);
    void testTrunc(void);
    void testWriteHyperslab(void);
    void testReadWriteGroups(void);
    void testReadWriteExistingGroups(void);
    
private slots:
    virtual void cleanupTestCase(void);
    virtual void cleanup(void);
};


//
// dtkIoDataModelHdf5Test.h ends here
