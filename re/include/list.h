/**
 @file

 A simple one-directional linked list.

 @verbatim
    +--------+  +--------+  +--------+       +----------+  +--------+
    | node 1 |  | node 2 |  | node 3 |       | node n-1 |  | node n |
    |        |  |        |  |        |  ...  |          |  |        |
    | next ---->| next ---->| next --->   -->| next ------>| next ---> NULL
    +--------+  +--------+  +--------+       +----------+  +--------+
         ^
         |
 head ---+
 @endverbatim

 Empty list has no nodes.

 @verbatim
 head ---> NULL
 @endverbatim

 A list with a single element has matching 'head' and 'last' pointers.

 @verbatim
       +--------+
       | node 1 |
       |        |
       | next ---> NULL
       +--------+
         ^    ^
         |    |
 head ---+    +--- last
 @endverbatim

 Reasons for having this simple structure:
   * Each node has exactly 1 pointer referencing it

 A list iterator is used to iterate over the elements of a list.
 The iterator knows the list it it iterating over, the current element, and
 the parent pointer, referencing the current node.

 In the following example, iterator 1 points to the first element of the list,
 iterator 3 points to the third

 @verbatim
  +------------+                             +------------+
  | iterator 1 |                             | iterator 3 |
  |            |                             |            |
  | current--------+                       +---current    |
  | parent_ptr---+  |         +----------------parent_ptr |
  +------------+ |  |         |            | +------------+
                 |  |         |            |
     +-----------+  |         |            |
     |              v         |            v
     |         +--------+  +--|-----+  +--------+  +--------+
     v         | node 1 |  | n|de 2 |  | node 3 |  | node 4 |
   head------->|        |  |  v     |  |        |  |        |
               | next ---->| next ---->| next ---> | next --->  ...
               +--------+  +--------+  +--------+  +--------+
 @endverbatim

*/

#ifndef _LIST_H_
#define _LIST_H_

/**
 * @brief The list structure
 *
 * An opaque structure, holding a list. You can obtain it using the list_create* functions.
 * You can use it to iterate over the list, and remove it.
 */
typedef struct list_t list_t;

/**
 * @brief Create list by element size
 *
 * @param[in] element_size Size of the element to be held in one
 * list node
 */
list_t * list_create_by_size(size_t element_size);

/**
 * @brief Create a new list by element type
 * 
 * @param[in] TYPE Type of elements to be held in the list
 */
#define list_create(TYPE) list_create_by_size(sizeof(TYPE))

/**
 * @brief Remove a list
 *
 * @param[in] list The list pointer. Must be non-null.
 *
 * Remove a list completely, freeing all resources associated with the list or
 * its nodes. The list pointer is invalid after this call.
 */
void list_kill(list_t *list);

/**
 * @brief Iterator over the list
 *
 * An opaque structure holding an iterator for a list. You can use it when iterating
 * over the list to insert, remove, or get values of list elements.
 */
typedef struct list_iter_t list_iter_t;

/**
 * @brief Begin iterating a list
 *
 * @param[in] list The list to be iterated over. Must be created with
 * list_create.
 *
 * The current value of the returned iterator is set to list's HEAD node, or NULL.
 * The parent reference is the list's HEAD pointer.
 */
list_iter_t * list_start_iter(list_t *list);

/**
 * @brief Finish iterating a list
 *
 * @param[in] it Iterator to kill
 */
void list_end_iter(list_iter_t *it);

/**
 * @brief Get next list element
 *
 * @param[in] it Iterator to update
 *
 * Move the iterator 1 position forward, making the current node's NEXT pointer the
 * parent reference, and the next pointer the current node.
 */
void list_next(list_iter_t *it);

/**
 * @brief Check if current list element is the last
 *
 * @param[in] it Iterator to check
 */
bool list_end(list_iter_t *it);

/**
 * @brief Get pointer to current list elment
 *
 * @param[in] it Iterator pointing to the node. Must not read list_end().
 */
void * list_pget(list_iter_t *it);

/**
 * @brief Get value of current list element
 *
 * @param[in] it Iterator pointing to the element to get.
 * @param[out] dst Address of the element to copy to.
 */
void list_get(list_iter_t *it, void *dst);

/**
 * @brief Add a new element to list
 *
 * @param[in] it Iterator pointing to the element to add before.
 * @param[in] value Value to insert before the node.
 *
 * Add a new node before the current node of the iterator. After insert,
 * the iterator is pointing to the inserted node, and its parent reference is
 * untouched.
 */
void list_add(list_iter_t *it, void *value);

/**
 * @brief Remove an element from the list
 *
 * @param[in] it Iterator at the element to be removed.
 *
 * Remove the current node of the iterator. After the removal, the current node
 * of the iterator is the removed node's NEXT node (may be NULL). The parent
 * reference is untouched.
 */
void list_rm(list_iter_t *it);

#endif
