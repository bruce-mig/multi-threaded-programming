/*
 * =====================================================================================
 *
 *       Filename:  rt.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  20/04/2025 10:18:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BRUCE MIGERI , bmigeri@gmail.com
 *
 *      This file is part of the bruce-mig distribution
 *      (https://github.com/bruce-mig) Copyright (c) 2025 Bruce Migeri. This
 *      program is free software: you can redistribute it and/or modify it under
 *      the terms of the GNU General Public License as published by the Free
 *      Software Foundation, version 3.
 *
 *      This program is distributed in the hope that it will be useful, but
 *      WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *      General Public License for more details.
 * =====================================================================================
 */

#ifndef __RT__
#define __RT__

#include "notif.h"
#include <stdbool.h>

typedef struct rt_entry_keys_ {

   char dest[16];
   char mask;
} rt_entry_keys_t;

typedef struct rt_entry_ {

   /* A Structure which represents only the keys of the
    * Routing Table.*/
   rt_entry_keys_t rt_entry_keys;

   char gw_ip[16];
   char oif[32];
   bool created;
   struct rt_entry_ *prev;
   struct rt_entry_ *next;
   notif_chain_t *nfc;
} rt_entry_t;

typedef struct rt_table_ {

   rt_entry_t *head;
} rt_table_t;

void rt_init_rt_table(rt_table_t *rt_table);

rt_entry_t *rt_add_or_update_rt_entry(rt_table_t *rt_table, char *dest_ip,
                                      char mask, char *gw_ip, char *oif);

bool rt_delete_rt_entry(rt_table_t *rt_table, char *dest_ip, char mask);

bool rt_update_rt_entry(rt_table_t *rt_table, char *dest_ip, char mask,
                        char *new_gw_ip, char *new_oif);

rt_entry_t *rt_look_up_rt_entry(rt_table_t *rt_table, char *dest, char mask);

void rt_clear_rt_table(rt_table_t *rt_table);

void rt_free_rt_table(rt_table_t *rt_table);

void rt_dump_rt_table(rt_table_t *rt_table);

static inline void rt_entry_remove(rt_table_t *rt_table, rt_entry_t *rt_entry) {

   if (!rt_entry->prev) {
      if (rt_entry->next) {
         rt_entry->next->prev = 0;
         rt_table->head = rt_entry->next;
         rt_entry->next = 0;
         return;
      }
      rt_table->head = 0;
      return;
   }
   if (!rt_entry->next) {
      rt_entry->prev->next = 0;
      rt_entry->prev = 0;
      return;
   }

   rt_entry->prev->next = rt_entry->next;
   rt_entry->next->prev = rt_entry->prev;
   rt_entry->prev = 0;
   rt_entry->next = 0;
}

#define ITERATE_RT_TABLE_BEGIN(rt_table_ptr, rt_entry_ptr)                     \
   {                                                                           \
      rt_entry_t *_next_rt_entry;                                              \
      for ((rt_entry_ptr) = (rt_table_ptr)->head; (rt_entry_ptr);              \
           (rt_entry_ptr) = _next_rt_entry) {                                  \
         _next_rt_entry = (rt_entry_ptr)->next;

#define ITERATE_RT_TABLE_END(rt_table_ptr, rt_entry_ptr)                       \
   }                                                                           \
   }

void rt_table_register_for_notification(rt_table_t *rt_table,
                                        rt_entry_keys_t *key, size_t key_size,
                                        nfc_app_cb app_cb, uint32_t subs_id);

#endif /* __RT__ */
