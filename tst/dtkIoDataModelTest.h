/* dtkIoDataModelTest.h --- 
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

#include <dtkTest>

class dtkIoDataModelTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testPluginManager(void);
    void testPluginFactory(void);
    void testPlugin(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
