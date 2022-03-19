#pragma once

#include <stddef.h>
#include <assert.h>
#include <iostream>

struct dll_node
{
  const char *key;
  void *val;
  struct dll_node *next;
  struct dll_node *prev;

  dll_node()
  {
    next = nullptr;
    prev = nullptr;
  }
};

struct DLL
{
  dll_node *head;
  dll_node *tail;
  size_t size;

  DLL()
  {
    size = 0;
  }

  void add_to_front(const char *key, void *val);
  void add_to_tail(const char *key, void *val);
  void print_list();
  void remove_from_tail();
  void remove_from_head();
  void remove_node(dll_node *node);
};

