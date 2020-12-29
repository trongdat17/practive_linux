#ifndef EXCELEXPORTER_H
#define EXCELEXPORTER_H

#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

#include "Common.h"

using namespace std;

class ExcelExporter : public QObject
{
public:
    /**
     * @brief Constructor of ExcelExporter
     * @param [in] parent parent of this class
     */
    explicit ExcelExporter(QObject *parent = 0);
    /**
     * @brief Destructor of ExcelExporter
     * @param [in] parent parent of this class
     */
    ~ExcelExporter();

    /**
     * @brief Set cell value
     * @param [in] nSheetPosition Position of sheet
     * @param [in] row Row of cell
     * @param [in] col Column of cell
     * @param [in] sValue Value of cell
     */
    void setCellValue(int nSheetPosition, int row, int col, const QString& sValue);
    /**
     * @brief Set cell color
     * @param [in] nSheetPosition Position of sheet
     * @param [in] row Row of cell
     * @param [in] col Column of cell
     * @param [in] nColorIndex Color index of cell
     */
    void setCellColor(int nSheetPosition, int row, int col, const int& nColorIndex);

    /**
     * @brief Add new sheet to excel file
     */
    void addNewSheet();
    /**
     * @brief Delete a sheet in excel file
     * @param [in] nSheetPosition Position of sheet
     */
    void deleteSheet(int nSheetPosition);
    /**
     * @brief Set sheet name
     * @param [in] nSheetPosition Position of sheet
     * @param [in] sName Name of sheet
     */
    void setSheetName(int nSheetPosition, QString sName);
    /**
     * @brief Set sheet data
     * @param [in] nSheetPosition Position of sheet
     * @param [in] data Data of sheet
     */
    void setSheetData(int nSheetPosition, QList<QStringList> data);
    /**
     * @brief Set cells color
     * @param [in] nSheetPosition Position of sheet
     * @param [in] sRange Range of cells
     * @param [in] nColorIndex Color index of cells
     */
    void setCellsColor(int nSheetPosition, QString sRange, const int& nColorIndex);
    /**
     * @brief Set preeze pane for a sheet in excel file
     * @param [in] nSheetPosition Position of sheet
     * @param [in] sRange Range of cells will be preezed
     */
    void setFreezePane(int nSheetPosition, QString sRange);

    /**
     * @brief Save excel file
     * @param [in] sFilePath Path to save excel file
     * @retval true Save file successfully
     * @retval false Save file error
     */
    bool saveAs(const QString& sFilePath);

    /**
     * @brief Check if Old is initialized or not
     * @retval true Ole is initialized
     * @retval false Ole is not initialized
     */
    bool isOleInitialized();
    /**
     * @brief Check if Excel is started or not
     * @retval true Excel is started
     * @retval false Excel is not started
     */
    bool isExcelStarted();
    /**
     * @brief Check if Word books can controlled or not
     * @retval true Word books can controlled
     * @retval false Word books can not controlled
     */
    bool isWorkBooksCanControlled();
    /**
     * @brief Check if Word book added or not
     * @retval true Word book added
     * @retval false Word book is not addeds
     */
    bool isWorkBookAdded();
    /**
     * @brief Check if Word sheets can controlled or not
     * @retval true Word sheets can controlled
     * @retval false Word sheets can not controlled
     */
    bool isWorkSheetsCanControlled();

    /**
     * @brief Convert column number to column name
     * @param [in] colNumber Column number
     * @retval Column name after convert
     */
    QString columnNumberToName(int colNumber);

private:
    bool m_bOleInitialized;             /**< Flag to notity that ole is initialized */
    bool m_bExcelStarted;               /**< Flag to notity that excel is started */
    bool m_bWorkBooksCanControlled;     /**< Flag to notity that word books can controlled */
    bool m_bWorkBookAdded;              /**< Flag to notity that word book added */
    bool m_bWorkSheetsCanControlled;    /**< Flag to notity that word sheets can controlled */

    QAxObject* m_pExcelApp;             /**< Excel object */
    QAxObject* m_pWorkBooks;            /**< WorkBooks object */
    QAxObject* m_pWorkBook;             /**< WorkBook object */
    QAxObject* m_pSheets;               /**< Sheets object */
};

#endif // EXCELEXPORTER_H
