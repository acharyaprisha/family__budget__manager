#include "FilterSystem.h"
#include "../REPOSITORIES/FileManager.h"

#include <iostream>
#include<sstream>
#include<fstream>
#include<vector>

/**
 * @brief Convert a date into a comparable format.
 *
 * Extracts the day, month, and year from
 * a date stored in DD-MM-YYYY format and
 * rearranges them into YYYYMMDD format.
 *
 * This enables chronological comparisons
 * using standard string comparison operators.
 *
 * @param date Date in DD-MM-YYYY format.
 *
 * @return Date converted to YYYYMMDD format.
 */
string FilterSystem::convertDate(string date)
{
    string day, month, year;

    // Extract day, month, and year using '-' as the delimiter.
    stringstream ss(date);

    getline(ss, day, '-');
    getline(ss, month, '-');
    getline(ss, year);

    // Rearrange the date components into YYYYMMDD format for comparison.
    return year + month + day;
}


/**
 * @brief Determine whether a date falls within a range.
 *
 * Converts the transaction date and the
 * user-specified start and end dates into
 * a comparable format and checks whether
 * the transaction date lies within the
 * specified range.
 *
 * @param transactionDate Date associated
 * with a transaction.
 *
 * @param startDate Beginning of the date range.
 *
 * @param endDate End of the date range.
 *
 * @return true if the transaction date falls
 * within the specified range, otherwise false.
 */
bool FilterSystem::dateRange(string transactionDate,string startDate,string endDate)
{
    // Convert dates into YYYYMMDD format
    // to enable chronological comparison.
    string txDate = convertDate(transactionDate);
    string start = convertDate(startDate);
    string end = convertDate(endDate);

    // Check whether the transaction date
    // lies within the specified range.
    return txDate >= start && txDate <= end;
}



 /**
 * @brief Filter transaction records using amount and date ranges.
 *
 * Opens the transaction history associated
 * with the specified account number and
 * displays all transactions whose amounts
 * and dates fall within the user-specified
 * ranges.
 *
 * If no matching transaction is found, an
 * appropriate message is displayed.
 *
 * @param accno Account number whose
 * transaction history will be searched.
 *
 * @param minamount Minimum transaction amount.
 *
 * @param maxamount Maximum transaction amount.
 *
 * @param startDate Beginning of the date range.
 *
 * @param endDate Ending of Date range.
 */
void FilterSystem::FilterByAmountDate(string accno, double minamount, double maxamount, string startDate, string endDate)
{
    if(minamount > maxamount)
    {
        cout << "Maximum amount must be greater than or equal to minimum amount."
             << endl;
        return;
    }

    FileManager fm;
    int index_of_amount = 2;
    int index_of_timestamp = 4;

    ifstream file(fm.getTransactionPath(accno));

    if(!file.is_open())
    {
        cout << "Unable to open transaction history." << endl;
        return;
    }

    bool found = false;
    string line;

    while(getline(file, line))
    {
        vector<string> fields;
        stringstream ss(line);
        string field;

        while(getline(ss, field, '|'))
        {
            fields.push_back(field);
        }

        if(fields.size() < 5)
        {
            continue;
        }

        double transactionAmount =stod(fields[index_of_amount]);

        string timestamp = fields[index_of_timestamp];

        string transactionDate;

        stringstream dateStream(timestamp);

        dateStream >> transactionDate;

        if(transactionAmount >= minamount &&
           transactionAmount <= maxamount &&
           dateRange(transactionDate,startDate,endDate))
           {
            found = true;
            cout << line << endl;
           }
    }

    if(!found)
    {
        cout << "No matching transaction found." << endl;
    }

    file.close();
}
