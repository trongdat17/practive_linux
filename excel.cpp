#include <windows.h>
#include "ExcelExporter.h"

ExcelExporter::ExcelExporter(QObject *parent) :
    QObject(parent)
{
    m_pExcelApp  = NULL;
    m_pWorkBooks = NULL;
    m_pWorkBook  = NULL;
    m_pSheets    = NULL;

    m_bOleInitialized          = false;
    m_bExcelStarted            = false;
    m_bWorkBooksCanControlled  = false;
    m_bWorkBookAdded           = false;
    m_bWorkSheetsCanControlled = false;

    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
        return;
    }
    m_bOleInitialized = true;

    m_pExcelApp = new QAxObject("Excel.Application", 0);
    if (m_pExcelApp == NULL)
    {
        return;
    }
    m_bExcelStarted = true;

    m_pExcelApp->dynamicCall("SetVisible(bool)", false); // hide excel
    m_pExcelApp->setProperty("DisplayAlerts", 0);        // disable alerts

    m_pWorkBooks = m_pExcelApp->querySubObject("Workbooks");
    if (m_pWorkBooks == NULL)
    {
        return;
    }
    m_bWorkBooksCanControlled = true;

    m_pWorkBook  = m_pWorkBooks->querySubObject("Add");
    if (m_pWorkBook == NULL)
    {
        return;
    }
    m_bWorkBookAdded = true;

    m_pSheets = m_pWorkBook->querySubObject("Worksheets");
    if (m_pSheets == NULL)
    {
        return;
    }
    m_bWorkSheetsCanControlled = true;
}

ExcelExporter::~ExcelExporter()
{
    if (m_pExcelApp != NULL)
    {
        if (m_pWorkBook != NULL)
        {            
            m_pWorkBook->dynamicCall("Close (Boolean)", false);  // close without save
        }
        m_pExcelApp->dynamicCall("Quit (void)");
    }
    delete m_pWorkBook;
    delete m_pWorkBooks;
    delete m_pExcelApp;

    OleUninitialize();
}

void ExcelExporter::setCellValue(int nSheetPosition, int row, int col, const QString &sValue)
{
    if (m_pWorkBook == NULL)
    {
        return;
    }
    QAxObject *sheet = m_pWorkBook->querySubObject("Worksheets(int)", nSheetPosition);
    if (sheet == NULL)
    {
        return;
    }
    QAxObject *cell = sheet->querySubObject("Cells(int,int)", row, col);
    if (cell != NULL)
    {
        cell->setProperty("Value", sValue);
        QAxObject *cellBorder = cell->querySubObject("Borders");
        if (cellBorder != NULL)
        {
            cellBorder->setProperty("LineStyle (const QString&)", QString("xlContinuous"));
            cellBorder->setProperty("Weight (const QString&)", QString("xlThin"));
            cellBorder->setProperty("ColorIndex", 1);
        }
        delete cell;
    }
    delete sheet;
}

void ExcelExporter::setCellColor(int nSheetPosition, int row, int col, const int& nColorIndex)
{
    if (m_pWorkBook == NULL)
    {
        return;
    }
    QAxObject *sheet = m_pWorkBook->querySubObject("Worksheets(int)", nSheetPosition);
    if (sheet == NULL)
    {
        return;
    }
    QAxObject *cell = sheet->querySubObject("Cells(int,int)", row, col);
    if (cell != NULL)
    {
        QAxObject *iterior = cell->querySubObject("Interior");
        if (iterior != NULL)
        {
            iterior->setProperty("ColorIndex", nColorIndex);
            delete iterior;
        }
        delete cell;
    }
    delete sheet;
}

void ExcelExporter::addNewSheet()
{
    if (m_pSheets == NULL)
    {
        return;
    }
    m_pSheets->dynamicCall("Add()");
}

void ExcelExporter::deleteSheet(int nSheetPosition)
{
    if (m_pWorkBook == NULL)
    {
        return;
    }
    QAxObject *sheet = m_pWorkBook->querySubObject("Worksheets(int)", nSheetPosition);
    if (sheet == NULL)
    {
        return;
    }
    sheet->dynamicCall("Delete()");
    delete sheet;
}

void ExcelExporter::setSheetName(int nSheetPosition, QString sName)
{
    if (m_pWorkBook == NULL)
    {
        return;
    }
    QAxObject *sheet = m_pWorkBook->querySubObject("Worksheets(int)", nSheetPosition);
    if (sheet == NULL)
    {
        return;
    }
    sheet->setProperty("Name", sName);
    delete sheet;
}

// HoanVC 2018-11-30: Update performance for export data faster
// Start
void ExcelExporter::setSheetData(int nSheetPosition, QList<QStringList> data)
{
    if (m_pWorkBook == NULL)
    {
        return;
    }
    QAxObject *sheet = m_pWorkBook->querySubObject("Worksheets(int)", nSheetPosition);
    if (sheet == NULL || data.size() == 0)
    {
        return;
    }
    QList<QVariant> tableData;
    for (int i = 0; i < data.size(); i++)
    {
        QList<QVariant> row;
        for (int j = 0; j < data[i].size(); j++)
        {
            row.append(QVariant(data[i][j]));
        }
        tableData.append(QVariant(row));
    }
    QVariant   sheetTable(tableData);
    QString    sLastCellName = columnNumberToName(data.first().size() - 1) + QString::number(data.size());
    QAxObject *range         = sheet->querySubObject("Range(const QString&, const QString&)", "A1", sLastCellName);
    if (range != NULL)
    {
        range->dynamicCall("setValue(const QVariant&)", sheetTable);
        QAxObject *cellsBorder = range->querySubObject("Borders");
        if (cellsBorder != NULL)
        {
            cellsBorder->setProperty("LineStyle (const QString&)", QString("xlContinuous"));
            cellsBorder->setProperty("Weight (const QString&)", QString("xlThin"));
            cellsBorder->setProperty("ColorIndex", 1);
        }
        delete range;
    }
    QAxObject *range2 = sheet->querySubObject("Columns(const QString&)", QString("A:FF"));
    if (range2 != NULL)
    {
        range2->dynamicCall("AutoFit");
        delete range2;
    }
    delete sheet;
}

void ExcelExporter::setCellsColor(int nSheetPosition, QString sRange, const int& nColorIndex)
{
    if (m_pWorkBook == NULL)
    {
        return;
    }
    QAxObject *sheet = m_pWorkBook->querySubObject("Worksheets(int)", nSheetPosition);
    if (sheet == NULL)
    {
        return;
    }
    QAxObject *range = sheet->querySubObject("Range(const QString&)", sRange);
    if (range != NULL)
    {
        QAxObject *iterior = range->querySubObject("Interior");
        if (iterior != NULL)
        {
            iterior->setProperty("ColorIndex", nColorIndex);
            delete iterior;
        }
        delete range;
    }
    delete sheet;
}
// End

void ExcelExporter::setFreezePane(int nSheetPosition, QString sRange)
{
    if (m_pWorkBook == NULL)
    {
        return;
    }
    QAxObject *sheet = m_pWorkBook->querySubObject("Worksheets(int)", nSheetPosition);
    if (sheet == NULL)
    {
        return;
    }
    QAxObject *range = sheet->querySubObject("Range(const QString&)", sRange);
    if (range != NULL)
    {
        sheet->dynamicCall("Activate");
        QAxObject *activeWindow = m_pExcelApp->querySubObject("ActiveWindow");
        if (activeWindow != NULL)
        {
            activeWindow->setProperty("FreezePanes", false);
            range->dynamicCall("Select");
            activeWindow->setProperty("FreezePanes", true);
            delete activeWindow;
        }
        delete range;
    }
    delete sheet;
}

bool ExcelExporter::saveAs(const QString &sFilePath)
{
    if (sFilePath == "" || sFilePath.contains("/"))
    {
        return false;
    }
    if (QFile::exists(sFilePath))
    {
        if (!QFile::remove(sFilePath))
        {
            return false;
        }
    }
    if (m_pWorkBook == NULL)
    {
        return false;
    }
    QVariant var = m_pWorkBook->dynamicCall("SaveAs (const QString&)", sFilePath);
    if (!var.toBool())
    {
        return false;
    }
    return true;
}

bool ExcelExporter::isOleInitialized()
{
    return m_bOleInitialized;
}

bool ExcelExporter::isExcelStarted()
{
    return m_bExcelStarted;
}

bool ExcelExporter::isWorkBooksCanControlled()
{
    return m_bWorkBooksCanControlled;
}

bool ExcelExporter::isWorkBookAdded()
{
    return m_bWorkBookAdded;
}

bool ExcelExporter::isWorkSheetsCanControlled()
{
    return m_bWorkSheetsCanControlled;
}

QString ExcelExporter::columnNumberToName(int colNumber)
{
    // column count from 0
    if (colNumber < 26)
    {
        return QString((char)(65 + colNumber));
    }
    return columnNumberToName((colNumber/26) - 1 ) + columnNumberToName(colNumber % 26);
}
