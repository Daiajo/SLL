#include <stdio.h>
#include <stdbool.h>
#include <string.h>	// strdup
#include <stdlib.h>	// atoi

#include "SLL.h"

#define VERSION	"0.0.2"

int SinkSize = 5 ;
//int SinkSelect = 3 ;
int InSize = 3 ;
int InSelect = 2 ;

SLL SinkTop ;
SLL InTop ;

typedef struct SINK
{
  SLL_Next Next ;
  int Index ;
} SINK ;

typedef struct INPUT
{
  SLL_Next Next ;
  int Index ;
  int Sink ;
} IN ;

void InPrint ( void * Node )
{
  IN * In = Node ;
  printf ( "Input # %d Sink # %d\n" , In -> Index , In -> Sink ) ;
}

void SinkPrint ( void * Node )
{
  SINK * Sink = Node ;
  printf ( "Sink # %d\n" , Sink -> Index ) ;
}

// InputIndex#,InputSink#
void DoInSpec ( String Param )
{
//String Dup = strdup ( Param ) ;
  String S = Param ;
  while ( ( * S != ',' ) &&  ( * S != '\0' ) ) S ++ ;
  if ( ! * S )
  {
    fprintf ( stderr , "Badly formed Input specification!\n\tUsage: -I index,sink\n" ) ;
    return ;
  }
  * S = '\0' ;
  int Index = atoi ( Param ) ;
  S ++ ;
  int Sink = atoi ( S ) ;
  IN * New = SLL_New ( sizeof ( IN ) ) ;
  New -> Index = Index ;
  New -> Sink = Sink ;
//printf ( "DoInSpec: %s -> Input # %d, Sink # %d\n" , Dup , Index , Sink ) ; free ( Dup ) ;
  SLL_Link ( & InTop , ( void * ) New ) ;
}

void GetOption ( String Key , String Param )
{
  if ( ! Param )
  {
    printf ( "For option %c, no parameter given\n" , Key [ 1 ] ) ;
    return ;
  }
  switch ( Key [ 1 ] )
  {
    case 'S' : SinkSize = atoi ( Param ) ; break ;
//  case 's' : SinkSelect = atoi ( Param ) ; break ;
    case 'I' : DoInSpec ( Param ) ; break ;
    case 'i' : InSelect = atoi ( Param ) ; break ;
    default : printf ( "Unknown option %c\n" , Key [ 1 ] ) ;
  }
  if ( SinkSize < 0 ) SinkSize = 0 ;
//if ( SinkSelect < 0 ) SinkSelect = 0 ;
  if ( InSelect < 0 ) InSelect = 0 ;
}

int InMatch ( void * Node , void * Match )
{
  IN * In = Node ;
  int Sink = * ( int * ) Match ;
  return In -> Index == Sink ;
}
int SinkMatch ( void * Node , void * Match )
{
  SINK * Sink = Node ;
  IN * In = Match ;
  return Sink -> Index == In -> Sink ;
}

int main ( int argc , String * argv )
{
  String me = * argv ++ ;
  printf ( "%s: arg count = %d\n" , me , argc ) ;
  if ( argc <= 1 )
  {
    printf ( "Usage: %s [-i input] [-S #sink] [-I input,sink]\n" , me ) ;
    return 1 ;
  }
  for ( int C = 1 ; C < argc ; C += 2 )
  {
    String P = * argv ++ ;
    if ( * P == '-' ) GetOption ( P , * argv ++ ) ;
  }
  SLL_List ( & InTop , "In Begin" , InPrint ) ;
  
  for ( int N = 0 ; N < SinkSize ; N ++ )
  {
    SINK * Sink = SLL_New ( sizeof ( SINK ) ) ;
    Sink -> Index = N ;
    SLL_Link ( & SinkTop , Sink ) ;
  }
  SLL_List ( & SinkTop , "Sink Before" , SinkPrint ) ;
  printf ( "Input select = %d\n" , InSelect ) ;

  IN * In = SLL_Get ( & InTop , InMatch , & InSelect ) ;
  if ( ! In )
  {
    printf ( "Input # %d was not found!\n" , InSelect ) ;
    return 1 ;
  }
  SINK * Sink = SLL_Get ( & SinkTop , SinkMatch , In ) ;
  if ( Sink )
  {
    printf ( "Got Input # %d = Sink # %d\n" , InSelect  , Sink -> Index ) ;
    SLL_Break ( & SinkTop , ( void * ) Sink ) ;
  }
  else
    printf ( "Get Input # %d - not found!\n" , InSelect ) ;
  SLL_List ( & InTop , "In End" , InPrint ) ;
  SLL_List ( & SinkTop , "Sink After" , SinkPrint ) ;
}
