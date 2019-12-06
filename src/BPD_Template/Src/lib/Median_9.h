#ifndef	Median_9_h
#define	Median_9_h

// ３×３メディアンフィルタの高速アルゴリズム
// A Fast Algorithm for 3x3 Median Filtering
// 浜村倫行 入江文平
// Tomoyuki Hamamura & Bunpei Irie
//
// を元にしたプログラムです。

template <typename T>
struct Median_9
{
	struct	Type_Unit
	{
		T	v0, v1, v2;
	};

	Type_Unit		Unit_A, Unit_B, Unit_C;

	T	Write_Pointer;
	T	Buffer[ 9 ];

	Median_9() : Write_Pointer( 0 )
	{
		for( int i( 0 ); i < 9; ++i )
			Buffer[ i ] = T();
	}

	int	Process( const int& v )
	{
		// 新しいデータをバッファにセット
		Buffer[ Write_Pointer ] = v;
		++Write_Pointer;
		if( Write_Pointer == 9 )	Write_Pointer = 0;

		// バッファからソート用データへコピー
		Unit_A.v0 = Buffer[ 0 ];		Unit_A.v1 = Buffer[ 1 ];		Unit_A.v2 = Buffer[ 2 ];
		Unit_B.v0 = Buffer[ 3 ];		Unit_B.v1 = Buffer[ 4 ];		Unit_B.v2 = Buffer[ 5 ];
		Unit_C.v0 = Buffer[ 6 ];		Unit_C.v1 = Buffer[ 7 ];		Unit_C.v2 = Buffer[ 8 ];

		// 各ユニットをソート
		Sort( Unit_A );
		Sort( Unit_B );
		Sort( Unit_C );

		// ユニットの中央値でソート
		Sort();

#define		_x_		Unit_B.v1
#define		_y_		Unit_A.v2
#define		_z_		Unit_C.v0
#define		_w_		Unit_B.v0
#define		_v_		Unit_B.v2

		// case 1
		{
			if( _y_ <= _x_ && _x_ <= _z_ )	return _x_;
			if( _z_ <= _x_ && _x_ <= _y_ )	return _x_;
		}

		// case 2
		{
			if( _x_ < _y_ && _x_ < _z_ )
			{
				int	min;

				if( _y_ < _z_ )	min = _y_;
				else						min = _z_;

				if( _w_ < min )	min = _w_;

				return min;
			}
		}
		// case 3
		{
			if( _x_ > _y_ && _x_ > _z_ )
			{
				int	max;

				if( _y_ > _z_ )	max = _y_;
				else						max = _z_;
				
				if( _v_ > max )	max = _v_;

				return max;
			}
		}

		return _x_;
	}

	void Sort( Type_Unit& Unit )
	{
		if( Unit.v0 < Unit.v1 )
		{
			T	temp( Unit.v0 );
			Unit.v0 = Unit.v1;
			Unit.v1 = temp;
		}

		if( Unit.v2 > Unit.v0 )
		{
			T	temp( Unit.v2 );
			Unit.v2 = Unit.v1;
			Unit.v1 = Unit.v0;
			Unit.v0 = temp;
		}
		else if( Unit.v2 > Unit.v1 )
		{
			T	temp( Unit.v1 );
			Unit.v1 = Unit.v2;
			Unit.v2 = temp;
		}
	}

	void Sort()
	{
		if( Unit_A.v1 < Unit_B.v1 )
		{
			Type_Unit	temp( Unit_A );
			Unit_A = Unit_B;
			Unit_B = temp;
		}

		if( Unit_C.v1 > Unit_A.v1 )
		{
			Type_Unit	temp( Unit_C );
			Unit_C = Unit_B;
			Unit_B = Unit_A;
			Unit_A = temp;
		}
		else if( Unit_C.v1 > Unit_B.v1 )
		{
			Type_Unit	temp( Unit_B );
			Unit_B = Unit_C;
			Unit_C = temp;
		}
	}
};

#endif
