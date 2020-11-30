#ifndef DATACONTROL_H
#define DATACONTROL_H
#include <QObject>
#include <QMutex>
#include "MachineItem.h"
/**
 * The control data class. It is used to control all common data in iPAQET3 Client. It is static class.
 *
 * @author (TSDV) [iPAQET 3]
 * @date HienNL 2017-05-19  First Created
 * @copyright Copyright (C) 2020 SHIBAURA MACHINE CO.,LTD. All Rights Reserved
 */
class DataControl
{
public:
    /**
     * @brief Get instance of DataControl class
     */
    static DataControl& instance();
    /**
     * @brief Delete Copy method
     */
    DataControl(DataControl const& dataControl)            = delete;    // Copy constructor
    /**
     * @brief Delete Assigment operator
     */
    void operator=(DataControl const& dataControl)         = delete;    // Assignment operator
    /**
     * @brief Get MachineItem object follow machine number
     * @param [in] nMachineNumber Machine number
     * @return MachineItem object
     */
    MachineItem* getMachineItem(int nMachineNumber);
    
    private:
    int m_nCurrentMachineNum;               /**< Current machine number*/
    int m_nCurrentStorageMachineNum;        /**< Current storage machine num*/
    QDateTime m_productLastTime;            /**< Last time of Product message*/
    QDateTime m_statusLastTime;             /**< Last time of Status message*/
    QDateTime m_resinLastTime;              /**< Last time of Resin message*/
    QTime     m_dailyStartingTime;          /**< Daily Starting Time*/
    QHash<int, MachineItem*> m_machineHash; /**< Hash of machine item*/
    QMutex m_dataMutex;                     /**< Mutex for Hash data*/
    /**
     * @brief Constructor of DataControl object
     */
    DataControl();
    /**
     * @brief Destructor of DataControl object
     */
    ~DataControl();
