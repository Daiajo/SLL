#include <stdio.h>
#include <stdlib.h>	// malloc

#define VERSION	"0.0.3"
// 0.0.3 Get returns Head if no Check
//	Added Tail, Kill, Destroy

#include "SLL.h"

struct SLL_TOP
{
  void * Head ;
  void * Tail ;
  void ( * Kill ) ( void * Node ) ;
} ;

void * SLL_New ( int Size , void ( * Kill ) ( void * Node ) )
{
  if ( Size < sizeof ( SLL_Next ) ) return NULL ;
  SLL * New = malloc ( Size ) ;
  if ( ! New )
  {
    fprintf ( stderr , "SLL_New: %d malloc failed\n" , Size ) ;
    return NULL ;
  }
  New -> Kill = Kill ;
  return New ;
}

void SLL_Kill ( SLL * Top , void * Old )
{
  SLL_Break ( Top , Old ) ;
  Top -> Kill ( Old ) ;
  free ( Old ) ;
}

void SLL_Link ( SLL * Top , void * New )
{
  if ( ! Top ) return ;
  SLL_Next * This = Top -> Tail ;
  if ( This ) This -> Next = New ;
  Top -> Tail = New ;
  if ( ! Top -> Head ) Top -> Head = New ;
}

void * SLL_Get ( SLL * Top , int ( * Check ) ( void * Node , void * UserData ) , void * UserData )
{
  if ( ! Top ) return NULL ;
  if ( ! Check ) return Top -> Head ;
  for ( SLL_Next * This = Top -> Head ; This ; This = This -> Next )
    if ( Check ( This , UserData ) ) return This ;
  return NULL ;
}

void * SLL_Tail ( SLL * Top )
{
  if ( ! Top ) return NULL ;
  return Top -> Tail ;
}

void SLL_Break ( SLL * Top , SLL_Next * Old )
{
  if ( ! Top ) return ;
  if ( ! Old ) return ;
  SLL_Next * Last = NULL ;
  for ( SLL_Next * This = Top -> Head ; This ; This = This -> Next )
  {
    if ( This == Old )
    {
      if ( ! Last )
        Top -> Head = This -> Next ;
      else
	Last -> Next = This -> Next ;
      if ( Top -> Tail == This ) Top -> Tail = Last ;
    }
    Last = This ;
  }
}

void SLL_Destroy ( SLL * Top )
{
  SLL_Next * This ;
  for ( This = Top -> Head ; This ; This = This -> Next )
    SLL_Kill ( Top , ( void * ) This ) ;
  Top -> Head = NULL ;
  Top -> Tail = NULL ;
}

void SLL_List ( SLL * Top , String Name , void ( * Print ) ( void * Data ) )
{
  if ( ! Top ) return ;
  if ( Name ) printf ( "%s\n" , Name ) ;
  int Count = 0 ;
  SLL_Next * This ;
  for ( This = Top -> Head ; This ; This = This -> Next )
  {
    if ( Print ) Print ( This ) ;
    Count ++ ;
  }
  printf ( " %d in list\n" , Count ) ;
}
