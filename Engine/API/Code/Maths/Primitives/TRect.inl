#include "TRect.h"


template<typename T>
ae::TRect<T>::TRect() :
    Left( Cast( T, 0 ) ),
    Top( Cast( T, 0 ) ),
    Right( Cast( T, 0 ) ),
    Bottom( Cast( T, 0 ) )
{
}

template<typename T>
ae::TRect<T>::TRect( T _Left, T _Top, T _Right, T _Bottom ) :
    Left( _Left ),
    Top( _Top ),
    Right( _Right ),
    Bottom( _Bottom )
{
}

template<typename T>
inline Bool ae::TRect<T>::Intersects( const TRect<T>& _Other, Bool _WithBoundaries ) const
{
    // If we use boundaries, we must find intersection if other rectangle is touching the calling one.
    bool( *LessOperator )( T, T ) = _WithBoundaries ? &isless<T, T> : &islessequal<T, T>;
    bool( *GreaterOperator )( T, T ) = _WithBoundaries ? &isgreater<T, T> : &isgreaterequal<T, T>;

    const T&& Width = Right - Left;
    const T&& Height = Bottom - Top;

    const T&& OtherWidth = _Other.Right - _Other.Left;
    const T&& OtherHeight = _Other.Bottom - _Other.Top;

    // Too much at right.
    if( GreaterOperator( _Other.Left, Left + Width ) )
        return False;

    // Too much at left.
    if( LessOperator( _Other.Left + OtherWidth, Left ) )
        return False;

    // Too much at bottom.
    if( GreaterOperator( _Other.Top, Top + Height ) )
        return False;

    // Too much at top.
    if( LessOperator( _Other.Top + OtherHeight, Top ) )
        return False;

    return True;
}

template<typename T>
inline Bool ae::TRect<T>::Contains( const TRect<T>& _Other, Bool _WithBoundaries ) const
{
    // If we use boundaries then the calling rectangle can contains the other even if they have the exact same size.
    bool( *LessOperator )( T, T ) = _WithBoundaries ? &isless<T, T> : &islessequal<T, T>;
    bool( *GreaterOperator )( T, T ) = _WithBoundaries ? &isgreater<T, T> : &isgreaterequal<T, T>;

    const T&& Width = Right - Left;
    const T&& Height = Bottom - Top;

    const T&& OtherWidth = _Other.Right - _Other.Left;
    const T&& OtherHeight = _Other.Bottom - _Other.Top;

    // If we go over the right edge, the other rectangle is not contained.
    if( GreaterOperator( _Other.Left + OtherWidth, Left + Width ) )
        return False;

    // If we go over the left edge, the other rectangle is not contained.
    if( LessOperator( _Other.Left, Left ) )
        return False;

    // If we go over the bottom edge, the other rectangle is not contained.
    if( GreaterOperator( _Other.Top + OtherHeight, Top + Height ) )
        return False;

    // If we go over the top edge, the other rectangle is not contained.
    if( LessOperator( _Other.Top, Top ) )
        return False;

    return True;
}

template<typename T>
inline float ae::TRect<T>::GetWidth() const
{
    return Right - Left;
}

template<typename T>
inline float ae::TRect<T>::GetHeight() const
{
    return Bottom - Top;
}
