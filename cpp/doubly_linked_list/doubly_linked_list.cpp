#include <stddef.h>
#include <assert.h>
#include <iostream>
#include <doubly_linked_list.hpp>

using std::cout;

void DLL::add_to_front(const char *key, void *val)
{
  dll_node *new_node = new dll_node;
  new_node->key = key;
  new_node->val = val;
  new_node->prev = nullptr;

  if (size == 0)
  {
    new_node->next = nullptr;
    tail = new_node;
    head = new_node;
  }
  else
  {
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  }
  size++;
}

void DLL ::add_to_tail(const char *key, void *val)
{
  dll_node *new_node = new dll_node;
  new_node->key = key;
  new_node->val = val;
  new_node->next = nullptr;

  if (size == 0)
  {
    new_node->prev = nullptr;
    tail = new_node;
    head = new_node;
  }
  else
  {
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  }
  size++;
}

void DLL::print_list()
{
  auto node = head;
  auto prev = head;
  for (size_t _ = 0; _ < size; _++)
  {
    cout << node->key << ": " << node->val << std::endl;
    prev = node;
    node = node->next;
  }
  assert(prev == tail);
  assert(node == nullptr);
}

void DLL::remove_from_tail()
{
  remove_node(tail);
}

void DLL::remove_from_head()
{
  remove_node(head);
}

void DLL::remove_node(dll_node *node)
{

  if (size == 0 || node == nullptr)
  {
    return;
  }

  auto prev = node->prev;
  auto next = node->next;

  if (node->prev != nullptr)
  {
    node->prev->next = next;
  }

  if (node->next != nullptr)
  {
    node->next->prev = prev;
  }

  if (size == 1)
  {
    assert(tail == node);
    assert(head == node);
    tail = nullptr;
    head = nullptr;
  }

  else if (node == tail)
  {
    tail = node->prev;
  }

  else if (node == head)
  {
    head = node->next;
  }

  delete node;
  size--;
}

int main()
{
  DLL dll;
  char key1[] = "abc";
  char key2[] = "ghi";
  char key3[] = "xyz";
  char val[] = "onomatopoea";
  dll.add_to_tail(key1, val);
  dll.add_to_tail(key2, val);
  dll.add_to_tail(key3, val);
  dll.add_to_tail(key2, val);
  dll.print_list();
}