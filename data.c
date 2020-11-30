#include "DataControl.h"


DataControl &DataControl::instance()
{
    static DataControl instance;     // Guaranteed to be destroyed.
    return instance;
}

DataControl::DataControl()
{
    initDefaultvalue();
}
DataControl::~DataControl()
{

}
