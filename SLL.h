#ifndef SLL_H
#define SLL_H

typedef unsigned char * String ;

typedef struct SLL
{
  void * Head ;
  void * Tail ;
} SLL ;

typedef struct SLL_NEXT
{
  void * Next ;
} SLL_Next ;

// Define a user data structure with SLL_Next as first entry
// UserData * Node = SLL_New ( sizeof ( UserData ) , UserInit )
void * SLL_New ( int Size ) ;

// Declare a SLL Top structure with name matching the List
// Adds the new Node to the end of the List
void SLL_Link ( SLL * Top , void * New ) ;

// Loops though the List until Check returns true, then that Node is returned
void * SLL_Get ( SLL * Top , int ( * Check ) ( void * Node , void * UserData ) , void * UserData ) ;

// Removes the selected Node from the List
void SLL_Break ( SLL * Top , SLL_Next * Old ) ;

// Prints Name once, then calls Print for each Node in the List
void SLL_List ( SLL * Top , String Name , void ( * Print ) ( void * Node ) ) ;

#endif // SLL_H
