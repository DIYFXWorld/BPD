#ifndef	FMEM_Base_h
#define	FMEM_Base_h

#include	<stdint.h>
#include	<utility>		// for swap

template <typename ElemT>
struct FMEM_Base
{
	ElemT						*Page_Main, *Page_Sub;
	ElemT						*Write_Pos;
	const uint16_t	Max_Count;
	uint8_t					Pages_Per_Segment;

	FMEM_Base( uint32_t Page, uint8_t pages_per_segment );
	virtual ~FMEM_Base(){}

	ElemT*	Find( ElemT* page_begin, uint16_t index ) const;
	ElemT*	Rfind( ElemT* page_end, uint16_t index ) const;
	ElemT		Read( uint16_t Index, const ElemT& Default_Value =ElemT() );
	void		Write( const ElemT& v );
	void		Realignment();
	void		Clear();

	uint32_t	Get_Segment_Size() const;
	bool			Empty( const ElemT* page ) const;

protected:

	virtual void WRITE( ElemT* ptr, const ElemT& v ) = 0;
	virtual void ERASE( ElemT* page ) = 0;
};

template <typename ElemT>
FMEM_Base<ElemT>::FMEM_Base( uint32_t page, uint8_t pages_per_segment ) :
	Page_Main( ( ElemT* )page ),
	Page_Sub( ( ElemT* )( page + FMEM_PAGE_BYTES * pages_per_segment ) ),
	Max_Count( FMEM_PAGE_BYTES * pages_per_segment / sizeof( ElemT ) ),
	Pages_Per_Segment( pages_per_segment )
{
	if( Page_Main->Index == 0xFF )
		std::swap( Page_Main, Page_Sub );

	Write_Pos = Find( Page_Main, 0xFF );
}

template <typename ElemT>
ElemT* FMEM_Base<ElemT>::Find( ElemT* page_begin, uint16_t index ) const
{
	for( int i( 0 ); i < Max_Count; ++i )
	{
		if( page_begin->Index == index )	return page_begin;
		++page_begin;
	}
	return 0;
}

template <typename ElemT>
ElemT* FMEM_Base<ElemT>::Rfind( ElemT* page_end, uint16_t index ) const
{
	for( int i( 0 ); i < Max_Count; ++i )
	{
		if( page_end->Index == index )	return page_end;
		--page_end;
	}
	return 0;
}

template <typename ElemT>
ElemT FMEM_Base<ElemT>::Read( uint16_t Index, const ElemT& Default_Value )
{
	ElemT* Result = Rfind( Page_Main + Max_Count - 1, Index );
	if( Result )	return *Result;

	ElemT	v( Default_Value );
	v.Index = 0xFF;
	return v;
}

template <typename ElemT>
void FMEM_Base<ElemT>::Write( const ElemT& v )
{
	WRITE( Write_Pos, v );
	++Write_Pos;

	if( Write_Pos >= Page_Main + Max_Count )
		Realignment();
}

template <typename ElemT>
void FMEM_Base<ElemT>::Realignment()
{
	std::swap( Page_Main, Page_Sub );	// �ŏ��Ƀ��C���ƃT�u�����ւ���
	Write_Pos = Page_Main;

	for( int i( 0 );  i < 255; ++i )	// index��255�����Ȃ��̂ŁA�S�Ă�index���`�F�b�N���ăf�[�^���E��
	{
		ElemT	*v = Rfind( Page_Sub + Max_Count - 1, i );

		if( v )
		{
			WRITE( Write_Pos, *v );
			++Write_Pos;
		}
	}

	ERASE( Page_Sub );
}

template <typename ElemT>
void FMEM_Base<ElemT>::Clear()
{
	ERASE( Page_Main );
	ERASE( Page_Sub );
	Write_Pos = Page_Main;
}

template <typename ElemT>
uint32_t FMEM_Base<ElemT>::Get_Segment_Size() const
{ 
	if( Page_Main < Page_Sub )
		return ( uint32_t )Page_Sub - ( uint32_t )Page_Main;
	return ( uint32_t )Page_Main - ( uint32_t )Page_Sub;
}

template <typename ElemT>
bool FMEM_Base<ElemT>::Empty( const ElemT* page ) const
{
	for( int i( 0 ); i < Max_Count; ++i )
	{
		if( page->Index != 0xFF )	return false;
		++page;
	}
	return true;
}

#endif
