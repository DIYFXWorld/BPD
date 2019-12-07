#ifndef	FMEM_Address_h
#define	FMEM_Address_h

#define	FMEM_PAGE_BYTES							( ( uint32_t )0x400 )
#define	FMEM_ADDRESS_BASE						( ( uint32_t )0x08000000 )
#define	FMEM_PAGE_ADDRESS( PAGE )		( FMEM_ADDRESS_BASE + ( FMEM_PAGE_BYTES * PAGE ) )

#endif
