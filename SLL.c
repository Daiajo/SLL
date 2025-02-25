#include <stdio.h>
#include <stdlib.h>	// malloc

#define VERSION	"0.0.2"

#include "SLL.h"

void * SLL_New ( int Size )
{
  if ( Size < sizeof ( SLL_Next ) ) return NULL ;
  void * New = malloc ( Size ) ;
  if ( ! New )
  {
    fprintf ( stderr , "SLL_New: %d malloc failed\n" , Size ) ;
    return NULL ;
  }
  return New ;
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
  if ( ! Check ) return NULL ;
  for ( SLL_Next * This = Top -> Head ; This ; This = This -> Next )
    if ( Check ( This , UserData ) ) return This ;
  return NULL ;
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
