#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <dbus/dbus.h>

const char *const INTERFACE_NAME = "umn.inet.wil00352";
const char *const SERVER_BUS_NAME = "umn.inet.server";
const char *const OBJECT_PATH_NAME = "/umn/inet/client";
const char *const SERVER_OBJECT_PATH_NAME = "/umn/inet/server";
const char *const METHOD_NAME = "method";
int string_length(char*pointer);
int main(int argc, char ** argv)
{
  DBusMessage* msg;
  DBusMessageIter args;
  DBusConnection* conn;
  DBusError err;
  int ret, length;
  char* word;
  DBusMessage* reply;

  fprintf(stderr, "Waiting for connection...\n");

  dbus_error_init(&err);
  conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if(dbus_error_is_set(&err))
  {
    fprintf (stderr, "dbus_bus_get\n");
    dbus_error_free(&err);
  }
  if (conn == NULL)
  {
    fprintf (stderr, "connection null \n");
    exit(1);
  }
  ret = dbus_bus_request_name(conn, SERVER_BUS_NAME, DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
  if(dbus_error_is_set(&err))
  {
    fprintf (stderr, "error getting dbus name\n");
    dbus_error_free(&err);
  }
  while(true)
  {
    dbus_connection_read_write(conn, 0);
    msg = dbus_connection_pop_message(conn);
    if(msg == NULL)
    {
      sleep(2);
      fprintf(stderr, "still waiting...\n");
      continue;
    }
    if(dbus_message_has_interface(msg, INTERFACE_NAME))
    {
      DBusMessageIter iter;
      if(!dbus_message_iter_init(msg, &iter))
      {
        fprintf(stderr, "Message has no paramaters\n");
      }
      dbus_message_iter_get_basic(&iter, &word);
      fprintf(stderr, "Got message: %s\n", word);

      int length, c;
      char *begin, *end, temp;
      length = string_length(word);
      begin = word;
      end = word;
      for (c = 0; c < length -1; c++)
      {
        end++;
      }
      for (c = 0; c < length/2; c++)
      {
        temp = *end;
        *end = *begin;
        *begin = temp;

        begin++;
        end--;
      }

      reply = dbus_message_new_method_return(msg);;
      fprintf(stderr, "Sending reply: %s\n", word);
      dbus_message_iter_init_append(reply, &iter);
      if (!dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &word)) {
          fprintf (stderr, "Error in dbus_message_iter_append_basic\n");
          exit (1);
      }
      if(!dbus_connection_send(conn, reply, &length))
      {
        fprintf(stderr, "Could not reply\n");
        exit(1);
      }
      dbus_connection_flush(conn);
      dbus_message_unref(reply);

      dbus_message_unref(msg);
    }
  }
  dbus_connection_close(conn);
}
int string_length(char*pointer)
{
  int c = 0;

  while (*(pointer + c ) != '\0' )
  c++;

  return c;
}
