#ifndef SLL_H
#define SLL_H	"0.0.3"

typedef unsigned char * String ;

typedef struct SLL_TOP SLL ;

typedef struct SLL_NEXT
{
  void * Next ;
} SLL_Next ;

// Define a user data structure with SLL_Next as first entry
// If you data has heap storage, create a Kill function to deallocate it
// UserData * Node = SLL_New ( sizeof ( UserData ) , Kill )
void * SLL_New ( int Size , void ( * Kill ) ( void * Node ) ) ;

// Break's the Old Node from the list (if it is there)
// Calls the user Kill function on the Node
// frees the Node.
void SLL_Kill ( SLL * Top , void * Node ) ;

// Declare a SLL Top structure with name matching the List
// Adds the new Node to the end of the List
void SLL_Link ( SLL * Top , void * New ) ;

// Loops though the List until Check returns true, then that Node is returned
// If Check is NULL, returns the Head node
void * SLL_Get ( SLL * Top , int ( * Check ) ( void * Node , void * UserData ) , void * UserData ) ;
// returns the Tail Node of the List, without removing it from the list
void * SLL_Tail ( SLL * Top ) ;

// Removes the selected Node from the List
void SLL_Break ( SLL * Top , SLL_Next * Old ) ;

// Prints Name once, then calls Print for each Node in the List
void SLL_List ( SLL * Top , String Name , void ( * Print ) ( void * Node ) ) ;

// Interates Kill over the whole list
void SLL_Destroy ( SLL * Top ) ;

#endif // SLL_H
