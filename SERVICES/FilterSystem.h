/**
 * @file FilterSystem.h
 * @brief Defines the FilterSystem class used
 * to filter transaction records based on
 * user-specified criteria.
 */
#ifndef FILTERSYSTEM_H
#define FILTERSYSTEM_H

#include <string>
#include <vector>

using namespace std;

class FileManager;

/**
 * @class FilterSystem
 * @brief Provides transaction filtering
 * functionality for member accounts.
 */
class FilterSystem{
   
  public: 

/**
 * @brief Convert a date into a comparable format.
 *
 * Extracts the day, month, and year from
 * a date stored in DD-MM-YYYY format and
 * rearranges them into YYYYMMDD format.
 *
 * @param date Date in DD-MM-YYYY format.
 *
 * @return Date converted to YYYYMMDD format.
 */
string convertDate(string date);
 
/**
 * @brief Check whether a transaction date falls within a range.
 *
 * Compares the transaction date against
 * the user-specified start and end dates
 * and determines whether it lies within
 * the specified range.
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
bool dateRange(string transactionDate,string startDate,string endDate);

/**
 * @brief Filter transaction records using amount and date ranges.
 *
 * Searches the transaction history associated
 * with the specified account number and displays
 * all transactions whose amounts and dates fall
 * within the user-specified ranges.
 *
 * @param accno Account number whose transaction
 * history will be searched.
 *
 * @param minamount Minimum transaction amount.
 *
 * @param maxamount Maximum transaction amount.
 *
 * @param startDate Beginning of the date range.
 *
 * @param endDate End of the date range.
 */
void FilterByAmountDate(string accno ,double minamount, double maxamount, string startDate, string endDate);

  
};

#endif