#pragma once
#include "../../Toolbox/Toolbox.h"

#include "../../Debugging/Log/Log.h"

#include <string>

namespace ae
{
    /// \ingroup time
    /// <summary>
    /// Represents a date. <para/>
    /// Data available for a date : day, month, year, hours, minutes, seconds. <para/>
    /// Basic operations available like add or sub or comparisons.
    /// </summary>
    class AERO_CORE_EXPORT Date
    {
    public:
        /// <summary>Months of the year.</summary>
        enum Months
        {
            January = 0,
            February,
            March,
            April,
            May,
            June,
            July,
            August,
            September,
            October,
            November,
            December
        };

        /// <summary>Days of the week.</summary>
        enum Days
        {
            Sunday = 0,
            Monday,
            Tuesday,
            Wednesday,
            Thursday,
            Friday,
            Saturday
        };

    public:
        /// <summary>Default constructor. Empty date.</summary>
        Date();

        /// <summary>Create a date from seperate infos.</summary>
        /// <param name="_Seconds">Seconds of the date [0, 59].</param>
        /// <param name="_Minutes">Minutes of the date [0, 59].</param>
        /// <param name="_Hours">Hours of the date [0, 11].</param>
        /// <param name="_Day">Day of the date [1, 31].</param>
        /// <param name="_Month">Month of the date [0, 11].</param>
        /// <param name="_Year">Year of the date.</param>
        Date( Int32 _Seconds, Int32 _Minutes, Int32 _Hours, Int32 _Day, Int32 _Month, Int32 _Year );


        /// <summary>Copy constructor.</summary>
        /// <param name="_Copy">Other date to take values from.</param>
        Date( const Date& _Copy );


        /// <summary>Copy operator.</summary>
        /// <param name="_Copy">Date to copy.</param>
        /// <returns>Date of copy</returns>
        inline Date& operator=( const Date& _Copy );


        /// <summary>Add and assigment operator.</summary>
        /// <param name="_Date2">Date to add.</param>
        /// <returns>Date after operation</returns>
        inline Date& operator+=( const Date& _Date2 );

        /// <summary>Substract and assigment operator.</summary>
        /// <param name="_Date2">Date to sub.</param>
        /// <returns>Date after operation</returns>
        inline Date& operator-=( const Date& _Date2 );



        /// <summary>Comparison operator.</summary>
        /// <param name="_Date2">Date to compare with.</param>
        /// <returns>True if Both dates are the same, False otherwise.</returns>
        inline Bool operator==( const Date& _Date2 ) const;


        /// <summary>Comparison operator.</summary>
        /// <param name="_Date2">Date to compare with.</param>
        /// <returns>True if dates are different, False otherwise.</returns>
        inline Bool operator!=( const Date& _Date2 ) const;

 
        /// <summary>Get the current date.</summary>
        /// <returns>Date that correspond to the function call moment.</returns>
        static Date Now();



        /// <summary>Retrieve February count of day taking account of the leap year.</summary>
        /// <param name="_Year">Year of the February wanted, used to process leap year.</param>
        /// <returns>Count of day of February of the given year.</returns>
        static Uint8 GetFebruaryDayMax( const Int32 _Year );


        /// <summary>Determine if the year is a leap year.</summary>
        /// <param name="_Year">Year for which we want to know if it is a leap year.</param>
        /// <returns>True if <paramref name="_Year"/> is a leap year, False otherwise.</returns>
        static Bool IsLeapYear( const Int32 _Year );


        /// <summary>Retrieve the count of day of a month for a given year.</summary>
        /// <param name="_Month">Month for which we want to know the count of day.</param>
        /// <param name="_Year">Year of the month.</param>
        /// <returns>Count of day of the given month.</returns>
        static Uint8 GetMonthDayMax( const Int32 _Month, const Int32 _Year );


        /// <summary>Setter for seconds [0, 59].</summary>
        /// <param name="_Seconds">New value for seconds.</param>
        void SetSeconds( const Int32 _Seconds );


        /// <summary>Getter for seconds.</summary>
        /// <returns>Seconds of the date.</returns>
        Int32 GetSeconds() const;


        /// <summary>Increase seconds of the date.</summary>
        /// <param name="_Seconds">Amount of seconds to add ( can be negative ).</param>
        void IncSeconds( const Int32 _Seconds );



        /// <summary>Setter for minutes [0, 59].</summary>
        /// <param name="_Minutes">New value for minutes.</param>
        void SetMinutes( const Int32 _Minutes );
        

        /// <summary>Getter for minutes.</summary>
        /// <returns>Minutes of the date.</returns>
        Int32 GetMinutes() const;

        /// <summary>Increase minutes of the date.</summary>
        /// <param name="_Minutes">Amount of minutes to add ( can be negative ).</param>
        void IncMinutes( const Int32 _Minutes );



        /// <summary>Setter for hours [0, 11].</summary>
        /// <param name="_Hours">New value for hours.</param>
        void SetHours( const Int32 _Hours );


        /// <summary>Getter for hours.</summary>
        /// <returns>Hours of the date.</returns>
        Int32 GetHours() const;
        

        /// <summary>Increase hours of the date.</summary>
        /// <param name="_Hours">Amount of hours to add ( can be negative ).</param>
        void IncHours( const Int32 _Hours );


        /// <summary>Setter for days of month of the date</summary>
        /// <param name="_Day">New value for day of month.</param>
        void SetDay( const Int32 _Day );


        /// <summary>Getter for day of month.</summary>
        /// <returns>Day of month of the date.</returns>
        Int32 GetDay() const;


        /// <summary>Increase days of month of the date.</summary>
        /// <param name="_Day">Amount of days to add ( can be negative ).</param>
        void IncDay( const Int32 _Day );


        /// <summary>Retrieve the day of week as string ( no translation ).</summary>
        /// <param name="_ShortVersion">If True retrieve the short version of the day ( Mon. instead of Monday ).</param>
        /// <returns>Day as string.</returns>
        const std::string& GetDayAsString( const Bool _ShortVersion = False ) const;

   

        /// <summary>Setter of month of the date</summary>
        /// <param name="_Month">New value for month.</param>
        void SetMonth( const Int32 _Month );
        

        /// <summary>Getter for month.</summary>
        /// <returns>Month of the date.</returns>
        Int32 GetMonth() const;

        /// <summary>Increase the month of the date.</summary>
        /// <param name="_Month">Amount of months to add ( can be negative ).</param>
        void IncMonth( const Int32 _Month );


        /// <summary>Retrieve the month as string ( no translation ).</summary>
        /// <param name="_ShortVersion">If True retrieve the short version of the month ( Jan. instead of January ).</param>
        /// <returns>as string.</returns>
        const std::string& GetMonthAsString( const Bool _ShortVersion = False ) const;



        /// <summary>Setter for the year of the date</summary>
        /// <param name="_Year">New value for the year.</param>
        void SetYear( const Int32 _Year );
        

        /// <summary>Getter for the year.</summary>
        /// <returns>Year of the date.</returns>
        Int32 GetYear() const;


        /// <summary>Increase the year of the date.</summary>
        /// <param name="_Year">Amount of year to add ( can be negative ).</param>
        void IncYear( const Int32 _Year );


        /// <summary>Is the date has DST active ? ( Daylight Saving Time ).</summary>
        /// <returns>True if DST is active, False otherwise.</returns>
        Bool IsSummerTime() const;


        /// <summary>The date in 12-hours format is the morning ?</summary>
        /// <returns>True if the hours is in the morning, False otherwise.</returns>
        Bool IsAM() const;

        /// <summary>The date in 12-hours format is the afternoon ?</summary>
        /// <returns>True if the hours is in the afternoon, False otherwise.</returns>
        Bool IsPM() const;


        /// <summary>Getter for the day of the week. [0, 6], Sunday = 0.</summary>
        /// <returns>Day of the week ( Sunday = 0 ).</returns>
        Uint8 GetDayOfWeek() const;


        /// <summary>Getter for the day of the year [0, 365].</summary>
        /// <returns>Day of the year.</returns>
        Uint16 GetDayOfYear() const;


    private:
        /// <summary>Check if seconds are in [0, 59], fix it if not.</summary>
        void CheckSeconds();

        /// <summary>Check if minutes are in [0, 59], fix it if not.</summary>
        void CheckMinutes();

        /// <summary>Check if hours are in [0, 11], fix it if not.</summary>
        void CheckHours();

        /// <summary>Check if day are in [1, 31], fix it if not.</summary>
        void CheckDay();

        /// <summary>Check if month are in [0, 11], fix it if not.</summary>
        void CheckMonth();


        /// <summary>Update the day of the week. To call when day changes.</summary>
        void UpdateDayOfWeek();

        /// <summary>Update the day of the year. To call when day changes.</summary>
        void UpdateDayOfYear();


        /// <summary>Update the activity of DST. To call when day or month change.</summary>
        void UpdateIsSummerTime();

    private:
        /// <summary>Months names.</summary>
        static const std::string MonthsStrings[12];

        /// <summary>Months names in short version ( Jan. instean of January ).</summary>
        static const std::string MonthsStringsShort[12];

        /// <summary>Max day count for each month. Care has to be taken for February.</summary>
        static const Uint8 MonthsDaysMax[12];


        /// <summary>Days names.</summary>
        static const std::string DaysStrings[7];

        /// <summary>Days names in short version ( Mon. instead of Monday ).</summary>
        static const std::string DaysStringsShort[7];

    private:
        /// <summary>Seconds [0, 59].</summary>
        Int32 m_Seconds;

        /// <summary>Minutes [0, 59].</summary>
        Int32 m_Minutes;

        /// <summary>Hours [0, 23].</summary>
        Int32 m_Hours;

        /// <summary>Days of month [1, 31].</summary>
        Int32 m_Day;

        /// <summary>Month [0, 11], January = 0.</summary>
        Int32 m_Month;

        /// <summary>Year.</summary>
        Int32 m_Year;


        /// <summary>Day of week [0, 6], Sunday = 0.</summary>
        Uint8 m_DayOfWeek;

        /// <summary>Day of year [0, 365], January 1st = 0.</summary>
        Uint16 m_DayOfYear;


        /// <summary>Daylight Saving Time.</summary>
        Bool m_IsSummerTime;


        /// <summary>Daylight Saving Time.</summary>
        Bool m_IsAM;

    };



    /// <summary>Add two date together.</summary>
    /// <param name="_Date1">First date.</param>
    /// <param name="_Date2">Second date to add to the first one.</param>
    /// <returns>Result of _Date1 + _Date2.</returns>
    AERO_CORE_EXPORT inline Date operator+( const Date& _Date1, const Date& _Date2 );


    /// <summary>Substract two date together.</summary>
    /// <param name="_Date1">First date.</param>
    /// <param name="_Date2">Second date to sub to the first one.</param>
    /// <returns>Result of _Date1 - _Date2.</returns>
    AERO_CORE_EXPORT inline Date operator-( const Date& _Date1, const Date& _Date2 );



    /// <summary>Compare two date together.</summary>
    /// <param name="_Date1">First date.</param>
    /// <param name="_Date2">Second date to compare with the first one.</param>
    /// <returns>True if both dates are the same, False otherwise.</returns>
    AERO_CORE_EXPORT inline Bool operator==( const Date& _Date1, const Date& _Date2 );


    /// <summary>Compare two date together.</summary>
    /// <param name="_Date1">First date.</param>
    /// <param name="_Date2">Second date to compare with the first one.</param>
    /// <returns>True if dates are different, False otherwise.</returns>
    AERO_CORE_EXPORT inline Bool operator!=( const Date& _Date1, const Date& _Date2 );


    //// For potential ToString function.
    /// Convert a date to a string. <para/>
    /// Available format ( without the backslash ) :<para/>
    /// \%Y : Year as number.<para/>
    /// \%M : Month as string.<para/>
    /// \%m : Month as string, short version.<para/>
    /// \%nm : Month as number.<para/>
    /// \%D : Day as string.<para/>
    /// \%d : Day as string, short version.<para/>
    /// \%nd : Day as number.<para/>
    /// \%ndy : Day of the year as number.<para/>
    /// \%hh : Hours as number.<para/>
    /// \%hhAP : Hours as number, AM-PM format.<para/>
    /// \%mm : Minutes as number.<para/>
    /// \%ss : Seconds as number.<para/>
    /// \%AP : AM or PM according to hours.
    ///
    /// @param _Format Format to apply to float values.
    /// @return Date as a C++ string. ( Default Format : \%D \%nd \%M \%Y ).
    
}

