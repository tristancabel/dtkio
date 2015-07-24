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

class dtkIodataTypeHdf5;
class dtkIoDataModelHdf5Private;

class dtkIoDataModelHdf5 : public dtkIoDataModel
{
    Q_OBJECT
    
public:
    dtkIoDataModelHdf5(void);
    ~dtkIoDataModelHdf5(void);

/* public: */
/*     dtkIoDataModelHdf5 *clone(void) const; */

/* public: */
/*     void copy(dtkIoDataModelHdf5 *other); */

public:
    void fileOpen(QString &name, dtkIoDataModel::FileMode mode);
    void fileClose(void);

    
public:
//    void read(QString &dataset_name, int *dimensions, int *indexes, void *values);
    void read(QString &dataset_name, dtkIoDataModel::DataType type, void *values);
//    void write(QString &dataset_name, int *dimensions, int *indexes, void *values);
//    void write(QString &dataset_name, int *nb_values, void *values);

public:
    dtkIoDataModelHdf5Private *d;
};


static dtkIoDataModel *dtkIoDataModelHdf5Creator(void)
{
    return new dtkIoDataModelHdf5();
}

//
// dtkIoDataModelHdf5.h ends here
