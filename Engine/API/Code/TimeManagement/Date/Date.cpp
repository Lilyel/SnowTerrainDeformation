#include "Date.h"
#include "../../Maths/Maths.h"
#include "../../Debugging/Debugging.h"

#include <time.h>

namespace ae
{
    const std::string Date::MonthsStrings[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    const std::string Date::MonthsStringsShort[12] = { "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.", "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec." };
    const Uint8 Date::MonthsDaysMax[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    const std::string Date::DaysStrings[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    const std::string Date::DaysStringsShort[7] = { "Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat." };


    Date::Date() :
        m_Seconds( 0 ),
        m_Minutes( 0 ),
        m_Hours( 0 ),
        m_Day( 0 ),
        m_Month( 0 ),
        m_Year( 0 ),
        m_DayOfWeek( 0 ),
        m_DayOfYear( 0 ),
        m_IsSummerTime( False ),
        m_IsAM( m_Hours <= 12 )
    {

    }

    Date::Date( Int32 _Seconds, Int32 _Minutes, Int32 _Hours, Int32 _Day, Int32 _Month, Int32 _Year ) :
        m_Seconds( _Seconds ),
        m_Minutes( _Minutes ),
        m_Hours( _Hours ),
        m_Day( _Day ),
        m_Month( _Month ),
        m_Year( _Year )
    {
        CheckDay();
        CheckMinutes();
        CheckHours();
        CheckDay();
        CheckMonth();

        UpdateDayOfWeek();
        UpdateDayOfYear();
        UpdateIsSummerTime();
    }

    Date::Date( const Date& _Copy ) :
        Date( _Copy.m_Seconds, _Copy.m_Minutes, _Copy.m_Hours, _Copy.m_Day, _Copy.m_Month, _Copy.m_Year )
    {
    }

    Date& Date::operator=( const Date& _Copy )
    {
        m_Seconds = _Copy.m_Seconds;
        m_Minutes = _Copy.m_Minutes;
        m_Hours = _Copy.m_Hours;
        m_Day = _Copy.m_Day;
        m_Month = _Copy.m_Month;
        m_Year = _Copy.m_Year;
        m_DayOfWeek = _Copy.m_DayOfWeek;
        m_DayOfYear = _Copy.m_DayOfYear;
        m_IsSummerTime = _Copy.m_IsSummerTime;
        m_IsAM = _Copy.m_IsAM;

        return *this;
    }
    Date& Date::operator+=( const Date& _Date2 )
    {
        IncSeconds( _Date2.m_Seconds );
        IncMinutes( _Date2.m_Minutes );
        IncHours( _Date2.m_Hours );
        IncDay( _Date2.m_Day );
        IncMonth( _Date2.m_Month );
        IncYear( _Date2.m_Year );

        UpdateDayOfWeek();
        UpdateDayOfYear();
        UpdateIsSummerTime();

        return *this;
    }
    Date& Date::operator-=( const Date& _Date2 )
    {
        IncSeconds( -_Date2.m_Seconds );
        IncMinutes( -_Date2.m_Minutes );
        IncHours( -_Date2.m_Hours );
        IncDay( -_Date2.m_Day );
        IncMonth( -_Date2.m_Month );
        IncYear( -_Date2.m_Year );

        UpdateDayOfWeek();
        UpdateDayOfYear();
        UpdateIsSummerTime();

        return *this;
    }
    Bool Date::operator==( const Date& _Date2 ) const
    {
        return ( m_Seconds == _Date2.m_Seconds &&
                 m_Minutes == _Date2.m_Minutes &&
                 m_Hours == _Date2.m_Hours &&
                 m_Day == _Date2.m_Day &&
                 m_Month == _Date2.m_Month &&
                 m_Year == _Date2.m_Year &&
                 m_DayOfWeek == _Date2.m_DayOfWeek &&
                 m_DayOfYear == _Date2.m_DayOfYear &&
                 m_IsSummerTime == _Date2.m_IsSummerTime &&
                 m_IsAM == _Date2.m_IsAM );
    }
    Bool Date::operator!=( const Date& _Date2 ) const
    {
        return ( m_Seconds != _Date2.m_Seconds ||
                 m_Minutes != _Date2.m_Minutes ||
                 m_Hours != _Date2.m_Hours ||
                 m_Day != _Date2.m_Day ||
                 m_Month != _Date2.m_Month ||
                 m_Year != _Date2.m_Year ||
                 m_DayOfWeek != _Date2.m_DayOfWeek ||
                 m_DayOfYear != _Date2.m_DayOfYear ||
                 m_IsSummerTime != _Date2.m_IsSummerTime ||
                 m_IsAM != _Date2.m_IsAM );
    }

    Date Date::Now()
    {
        // Time ellapsed from 1st January 1970.
        // We take 64 to reach years 3000 instead of 2038 with 32.
        const __time64_t  TimeNow = _time64( 0 );

        tm LocalTimeNow;

        const errno_t&& Error = localtime_s( &LocalTimeNow, &TimeNow );
        AE_ErrorCheckErrno( Error );

        return Date( LocalTimeNow.tm_sec,
                     LocalTimeNow.tm_min,
                     LocalTimeNow.tm_hour,
                     LocalTimeNow.tm_mday,
                     LocalTimeNow.tm_mon,
                     1900 + LocalTimeNow.tm_year );
    }

    Uint8 Date::GetFebruaryDayMax( const Int32 _Year )
    {
        return ( IsLeapYear( _Year ) ? 29 : 28 );
    }

    Bool Date::IsLeapYear( const Int32 _Year )
    {
        // https://en.wikipedia.org/wiki/Leap_year

        float YearAsFloat = Cast( float, _Year );

        // If year is not divisible by 4 then it is a common year.
        if( Math::Modf( YearAsFloat / 4.0f ) != 0.0f )
            return False;

        // If year is not divisible by 100 then it is a leap year.
        else if( Math::Modf( YearAsFloat / 100.0f ) != 0.0f )
            return True;

        // If year is not divisible by 400 then it is a common year.
        else if( Math::Modf( YearAsFloat / 400.0f ) != 0.0f )
            return False;

        // Else it is a leap year.
        else
            return True;
    }

    Uint8 Date::GetMonthDayMax( const Int32 _Month, const Int32 _Year )
    {
        Uint8 MaxDays = MonthsDaysMax[_Month];

        if( MaxDays == MonthsDaysMax[Months::February] )
            MaxDays = GetFebruaryDayMax( _Year );

        return MaxDays;
    }

    void Date::SetSeconds( const Int32 _Seconds )
    {
        m_Seconds = _Seconds;

        CheckSeconds();
    }
    Int32 Date::GetSeconds() const
    {
        return m_Seconds;
    }
    void Date::IncSeconds( const Int32 _Seconds )
    {
        m_Seconds += _Seconds;

        CheckSeconds();
    }

    void Date::SetMinutes( const Int32 _Minutes )
    {
        m_Minutes = _Minutes;

        CheckMinutes();
    }
    Int32 Date::GetMinutes() const
    {
        return m_Minutes;
    }
    void Date::IncMinutes( const Int32 _Minutes )
    {
        m_Minutes += _Minutes;

        CheckMinutes();
    }

    void Date::SetHours( const Int32 _Hours )
    {
        m_Hours = _Hours;

        CheckHours();
    }
    Int32 Date::GetHours() const
    {
        return m_Hours;
    }
    void Date::IncHours( const Int32 _Hours )
    {
        m_Hours += _Hours;

        CheckHours();
    }

    void Date::SetDay( const Int32 _Day )
    {
        m_Day = _Day;

        CheckDay();
        UpdateDayOfWeek();
        UpdateDayOfYear();
        UpdateIsSummerTime();
    }
    Int32 Date::GetDay() const
    {
        return m_Day;
    }
    void Date::IncDay( const Int32 _Day )
    {
        m_Day += _Day;

        CheckDay();
        UpdateDayOfWeek();
        UpdateDayOfYear();
        UpdateIsSummerTime();
    }
    const std::string& Date::GetDayAsString( const Bool _ShortVersion ) const
    {
        return ( _ShortVersion ? DaysStringsShort[m_DayOfWeek] : DaysStrings[m_DayOfWeek] );
    }

    void Date::SetMonth( const Int32 _Month )
    {
        m_Month = _Month;

        CheckMonth();
    }
    Int32 Date::GetMonth() const
    {
        return m_Month;
    }
    void Date::IncMonth( const Int32 _Month )
    {
        m_Month += _Month;

        CheckMonth();
    }
    const std::string& Date::GetMonthAsString( const Bool _ShortVersion ) const
    {
        return ( _ShortVersion ? MonthsStringsShort[m_Month] : MonthsStrings[m_Month] );
    }

    void Date::SetYear( const Int32 _Year )
    {
        m_Year = _Year;

        // Check day in case the date is in february.
        CheckDay();
        // Update day according to the year.
        UpdateDayOfWeek();
        UpdateDayOfYear();
        UpdateIsSummerTime();
    }
    Int32 Date::GetYear() const
    {
        return m_Year;
    }
    void Date::IncYear( const Int32 _Year )
    {
        m_Year += _Year;

        // Check day in case the date is in february.
        CheckDay();
        // Update day according to the year.
        UpdateDayOfWeek();
        UpdateDayOfYear();
        UpdateIsSummerTime();
    }

    Bool Date::IsSummerTime() const
    {
        return m_IsSummerTime;
    }

    Bool Date::IsAM() const
    {
        return m_IsAM;
    }
    Bool Date::IsPM() const
    {
        return ( !m_IsAM );
    }

    Uint8 Date::GetDayOfWeek() const
    {
        return m_DayOfWeek;
    }
    Uint16 Date::GetDayOfYear() const
    {
        return m_DayOfYear;
    }
    
    void Date::CheckSeconds()
    {
        if( m_Seconds >= 60 )
        {
            const Int32 ExtraMinutes = m_Seconds / 60;
            m_Seconds -= ( ExtraMinutes * 60 );
            IncMinutes( ExtraMinutes );
        }
        else if( m_Seconds < 0 )
        {
            const Int32 ExtraMinutes = Math::Abs( m_Seconds ) / 60;
            m_Seconds += ( ExtraMinutes * 60 );
            m_Seconds = 59 - Math::Abs( m_Seconds );
            IncMinutes( -ExtraMinutes );
        }
    }
    void Date::CheckMinutes()
    {
        if( m_Minutes >= 60 )
        {
            const Int32 ExtraHours = m_Minutes / 60;
            m_Minutes -= ( ExtraHours * 60 );
            IncHours( ExtraHours );
        }
        else if( m_Minutes < 0 )
        {
            const Int32 ExtraHours = Math::Abs( m_Minutes ) / 60;
            m_Minutes += ( ExtraHours * 60 );
            m_Minutes = 59 - Math::Abs( m_Minutes );
            IncHours( -ExtraHours );
        }
    }
    void Date::CheckHours()
    {
        if( m_Hours >= 24 )
        {
            const Int32 ExtraDay = m_Hours / 24;
            m_Hours -= ( ExtraDay * 24 );
            IncDay( ExtraDay );
        }
        else if( m_Hours < 0 )
        {
            const Int32 ExtraDay = Math::Abs( m_Hours ) / 24;
            m_Hours += ( ExtraDay * 24 );
            m_Hours = 23 - Math::Abs( m_Hours );
            IncDay( -ExtraDay );
        }

        m_IsAM = m_Hours <= 12;
    }
    void Date::CheckDay()
    {
        CheckMonth();

        Int32 SafeWhile = _I32_MAX;
        Uint8 MaxDays = 0;
        Int32 ToInc = 0;

        do
        {
            MaxDays = GetMonthDayMax( m_Month, m_Year );

            if( m_Day > MaxDays )
            {
                m_Day -= MaxDays;
                ToInc++;
            }
            else if( m_Day < 0 )
            {
                m_Day += MaxDays;
                ToInc--;
            }
            else
                SafeWhile = 0;

        } while( ( SafeWhile-- ) > 0 );

        if( ToInc > 0 )
            IncMonth( ToInc );
    }
    void Date::CheckMonth()
    {
        if( m_Month >= 12 )
        {
            const Int32 ExtraYear = m_Month / 12;
            IncDay( ExtraYear );
            m_Year -= ( ExtraYear * 12 );
        }
        else if( m_Month >= 12 )
        {
            const Int32 ExtraYear = Math::Abs( m_Month ) / 12;
            m_Month += ( ExtraYear * 12 );
            m_Month = 11 - Math::Abs( m_Month );
            IncDay( -ExtraYear );
        }
    }

    void Date::UpdateDayOfWeek()
    {
        CheckDay();
        CheckMonth();

        // http://mathforum.org/dr.math/faq/faq.calendar.html

        Int32 CenturyDigit = m_Year % 100;
        CenturyDigit = CenturyDigit / 4;
        CenturyDigit += m_Day;

        Uint8 MonthsKeyValues[12] = { 1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6 };

        CenturyDigit += MonthsKeyValues[m_Month];

        if( m_Month == Months::January || ( m_Month == Months::February && IsLeapYear( m_Year ) ) )
            CenturyDigit--;

        // 0s 100s 200s 300s / Loop every 4 years.
        Uint16 YearsKeyValues[4] = { 6, 4, 2, 0 };

        // Process the year key ...
        Int16 CurrentYearKey = ( m_Year % 400 ) / 100;

        CenturyDigit += YearsKeyValues[CurrentYearKey];

        CenturyDigit += ( m_Year % 100 );
        m_DayOfWeek = CenturyDigit % 7;

        // 1 = Sunday, so we substrack 1.
        if( m_DayOfWeek > 0 )
            m_DayOfWeek--;
        else
            m_DayOfWeek = 6;
    }
    void Date::UpdateDayOfYear()
    {
        CheckDay();
        CheckMonth();

        m_DayOfYear = 0;

        for( Int32 m = 0; m < m_Month; m++ )
        {
            if( m == Months::February )
                m_DayOfYear += GetFebruaryDayMax( m_Year );
            else
                m_DayOfYear += MonthsDaysMax[m];
        }

        // Day of year [0, 365].
        m_DayOfYear += Cast(Uint16, m_Day - 1 );
    }

    void Date::UpdateIsSummerTime()
    {
        m_IsSummerTime = False;

        // January, February and December are not DST.
        if( m_Month <= Months::February || m_Month >= Months::December )
            m_IsSummerTime = False;

        // April to October are DST.
        else if( m_Month >= Months::April && m_Month <= Months::October )
            m_IsSummerTime = True;

        // March and november are the fontier.
        else
        {
            Int32 PreviousSunday = m_Day - m_DayOfWeek;

            // In March it is DST the first sunday of the second week.
            if( m_Month == Months::March && PreviousSunday >= 8 )
                m_IsSummerTime = True;
            // In November, it is DST before the first sunday.
            else if( m_Month == Months::November && PreviousSunday <= 0 )
                m_IsSummerTime = True;
        }
    }

    Date operator+( const Date& _Date1, const Date& _Date2 )
    {
        return Date( _Date1.GetSeconds() + _Date2.GetSeconds(),
                     _Date1.GetMinutes() + _Date2.GetMinutes(),
                     _Date1.GetHours() + _Date2.GetHours(),
                     _Date1.GetDay() + _Date2.GetDay(),
                     _Date1.GetMonth() + _Date2.GetMonth(),
                     _Date1.GetYear() + _Date2.GetYear() );

    }

    Date operator-( const Date& _Date1, const Date& _Date2 )
    {
        return Date( _Date1.GetSeconds() - _Date2.GetSeconds(),
                     _Date1.GetMinutes() - _Date2.GetMinutes(),
                     _Date1.GetHours() - _Date2.GetHours(),
                     _Date1.GetDay() - _Date2.GetDay(),
                     _Date1.GetMonth() - _Date2.GetMonth(),
                     _Date1.GetYear() - _Date2.GetYear() );
    }

    Bool operator==( const Date& _Date1, const Date& _Date2 )
    {
        return ( _Date1.GetSeconds() == _Date2.GetSeconds() &&
                 _Date1.GetMinutes() == _Date2.GetMinutes() &&
                 _Date1.GetHours() == _Date2.GetHours() &&
                 _Date1.GetDay() == _Date2.GetDay() &&
                 _Date1.GetMonth() == _Date2.GetMonth() &&
                 _Date1.GetYear() == _Date2.GetYear() &&
                 _Date1.GetDayOfWeek() == _Date2.GetDayOfWeek() &&
                 _Date1.GetDayOfYear() == _Date2.GetDayOfYear() &&
                 _Date1.IsSummerTime() == _Date2.IsSummerTime() &&
                 _Date1.IsAM() == _Date2.IsAM() );
    }

    Bool operator!=( const Date& _Date1, const Date& _Date2 )
    {
        return ( _Date1.GetSeconds() != _Date2.GetSeconds() ||
                 _Date1.GetMinutes() != _Date2.GetMinutes() ||
                 _Date1.GetHours() != _Date2.GetHours() ||
                 _Date1.GetDay() != _Date2.GetDay() ||
                 _Date1.GetMonth() != _Date2.GetMonth() ||
                 _Date1.GetYear() != _Date2.GetYear() ||
                 _Date1.GetDayOfWeek() != _Date2.GetDayOfWeek() ||
                 _Date1.GetDayOfYear() != _Date2.GetDayOfYear() ||
                 _Date1.IsSummerTime() != _Date2.IsSummerTime() ||
                 _Date1.IsAM() != _Date2.IsAM() );
    }

}


/*
    std::string Date::ToString( const std::string& _Format ) const
    {
        // Default format.
        if( _Format == L"" )
        {
            if( m_Month < 12 && m_DayOfWeek < 7 )
                return ( DaysStrings[m_DayOfWeek] + L" " + String( m_Day ) + L" " + MonthsStrings[m_Month] + L" " + String( m_Year ) );
            else
            {
                AE_LogError( "Date Invalid." );
                return L"";
            }
        }

        String Out = _Format;
        String TempTime;

        // Time
        TempTime.Format( L"%02d", m_Seconds );
        Out.Replace( L"%ss", TempTime );
        TempTime.Format( L"%02d", m_Minutes );
        Out.Replace( L"%mm", TempTime );
        Out.Replace( L"%hhAP", String( m_IsAM ? m_Hours : m_Hours - 12 ) );
        Out.Replace( L"%hh", String( m_Hours ) );
        Out.Replace( L"%AP", m_IsAM ? L"AM" : L"PM" );

        // Day
        if( m_DayOfWeek < 7 )
        {
            Out.Replace( L"%D", DaysStrings[m_DayOfWeek] );
            Out.Replace( L"%d", DaysStringsShort[m_DayOfWeek] );
            Out.Replace( L"%nd", m_Day );
            Out.Replace( L"%ndy", m_DayOfYear );
        }
        else
        {
            AE_LogError( "Date Invalid." );
            return L"";
        }

        // Month
        if( m_Month < 12 )
        {
            Out.Replace( L"%M", MonthsStrings[m_Month] );
            Out.Replace( L"%m", MonthsStringsShort[m_Month] );
            Out.Replace( L"%nm", String( m_Month ) );
        }
        else
        {
            AE_LogError( "Date Invalid." );
            return L"";
        }

        // Year
        Out.Replace( L"%Y", String( m_Year ) );

        return Out;
    }
    */
