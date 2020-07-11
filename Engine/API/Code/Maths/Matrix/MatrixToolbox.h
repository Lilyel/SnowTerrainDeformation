#ifndef _MATRIX_TOOLBOX_AERO_H_
#define _MATRIX_TOOLBOX_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../../Maths/Functions/MathsFunctions.h"

namespace ae
{
	/// \ingroup math
	/// <summary>How to fill the matrix in the constructor with row and column count.</summary>
	enum class MatrixInitMode : Uint8
	{
        /// <summary>Set the matrix as identity ( ones on diagonal ).</summary>
		Identity,

        /// <summary>Fill the matrix with zeros.</summary>
		Zeros,

        /// <summary>Fill the matrix with ones.</summary>
		Ones,

        /// <summary>Float default value.</summary>
		Default
	};

	namespace priv
	{
		namespace MatrixToolbox
		{

			template<typename T>
			void Init( AE_Out T* const _Data, const Uint32 _CountRow, const Uint32 _CountCol, const MatrixInitMode _InitMode )
			{
				const Uint32 CountTotal = _CountRow * _CountCol;

				switch( _InitMode )
				{
				case MatrixInitMode::Identity:
				{
					const T& ZeroInit = Cast( T, 0 );
					const T& OneInit = Cast( T, 1 );

					for( Uint32 Index = 0; Index < CountTotal; Index++ )
						_Data[Index] = T( ZeroInit );

					for( Uint32 Row = 0; Row < _CountRow; Row++ )
						_Data[Row * _CountCol + Row] = T( OneInit );
				}
				break;

				case MatrixInitMode::Zeros:
				{
					const T& ZeroInit = Cast( T, 0 );

					for( Uint32 Index = 0; Index < CountTotal; Index++ )
						_Data[Index] = T( ZeroInit );
				}
				break;

				case MatrixInitMode::Ones:
				{
					const T& OneInit = Cast( T, 1 );

					for( Uint32 Index = 0; Index < CountTotal; Index++ )
						_Data[Index] = T( OneInit );
				}
				break;

				case MatrixInitMode::Default:
				default:
				{
					for( Uint32 Index = 0; Index < CountTotal; Index++ )
						_Data[Index] = T();
				}
				break;
				}
			}

			template<typename T>
			void Multiply( AE_Out T* const _Result, const T* const _Data, const T& _Scalar, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				const Uint32 CountTotal = _CountRow * _CountCol;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = _Data[Index] * _Scalar;
			}

			template<typename T>
			void Divide( AE_Out T* const _Result, const T* const _Data, const T& _Scalar, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				const Uint32 CountTotal = _CountRow * _CountCol;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = _Data[Index] / _Scalar;
			}

			template<typename T>
			void Add( AE_Out T* const _Result, const T* const _Data, const T& _Scalar, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				const Uint32 CountTotal = _CountRow * _CountCol;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = _Data[Index] + _Scalar;
			}

			template<typename T>
			void Subtract( AE_Out T* const _Result, const T* const _Data, const T& _Scalar, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				const Uint32 CountTotal = _CountRow * _CountCol;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = _Data[Index] - _Scalar;
			}

			template<typename T>
			void Pow( AE_Out T* const _Result, const T* const _Data, const T& _Power, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				const Uint32 CountTotal = _CountRow * _CountCol;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = Math::Pow( _Data[Index], _Power );
			}


			template<typename T>
			void Multiply( AE_Out T* const _Result, const T* const _A, const Uint32 _CountRowA, const Uint32 _CountColA, const T* const _B, const Uint32 _CountColB )
			{
				const T& Zero = Cast( T, 0 );

				const Uint32 ResultRow = _CountRowA;
				const Uint32 ResultCol = _CountColB;

				for( Uint32 Row = 0; Row < ResultRow; Row++ )
				{
					for( Uint32 Col = 0; Col < ResultCol; Col++ )
					{
						_Result[Row * ResultCol + Col] = Zero;

						for( Uint32 K = 0; K < ResultCol; K++ )
							_Result[Row * ResultCol + Col] += _A[Row * _CountColA + K] * _B[K * _CountColB + Col];
					}
				}
			}

			template<typename T>
			void Divide( AE_Out T* const _Result, const T* const _A, const Uint32 _CountRowA, const Uint32 _CountColA, const T* const _B )
			{
				const Uint32 CountTotal = _CountRowA * _CountColA;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = _A[Index] / _B[Index];
			}

			template<typename T>
			void Add( AE_Out T* const _Result, const T* const _A, const Uint32 _CountRowA, const Uint32 _CountColA, const T* const _B )
			{
				const Uint32 CountTotal = _CountRowA * _CountColA;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = _A[Index] + _B[Index];
			}

			template<typename T>
			void Subtract( AE_Out T* const _Result, const T* const _A, const Uint32 _CountRowA, const Uint32 _CountColA, const T* const _B )
			{
				const Uint32 CountTotal = _CountRowA * _CountColA;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = _A[Index] - _B[Index];
			}


			template<typename T>
			void Transpose( AE_Out T* const _Result, const T* _Data, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				for( Uint32 Row = 0; Row < _CountRow; Row++ )
				{
					for( Uint32 Col = 0; Col < _CountCol; Col++ )
						_Result[Col * _CountRow + Row] = _Data[Row * _CountCol + Col];
				}
			}

			template<typename T>
			void Abs( AE_Out T* const _Result, const T* _Data, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				const Uint32 CountTotal = _CountRow * _CountCol;

				for( Uint32 Index = 0; Index < CountTotal; Index++ )
					_Result[Index] = Math::Abs( _Data[Index] );
			}

			template<typename T>
			T Trace( const T* const _Data, const Uint32 _CountRow, const Uint32 _CountCol )
			{
				T Trace = Cast( T, 0 );

				const Uint32 CountDiagonalElements = Math::Min( _CountRow, _CountCol );

				for( Uint32 Index = 0; Index < CountDiagonalElements; Index++ )
					Trace += _Data[Index * _CountCol + Index];

				return Trace;
			}

		} // MatrixToolbox

	} // priv

} // ae

#endif // _MATRIX_TOOLBOX_AERO_H_
