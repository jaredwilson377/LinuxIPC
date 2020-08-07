#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <dbus/dbus.h>

// You must enter the following information and make sure it
// matches your configuration file(s) in /etc/dbus-1/system.d
const char *const INTERFACE_NAME = "umn.inet.wil00352";
const char *const SERVER_BUS_NAME = "umn.inet.server"; //optional as per freedesktop.org
const char *const CLIENT_BUS_NAME = "umn.inet.client";
const char *const SERVER_OBJECT_PATH_NAME = "/umn/inet/server";
const char *const CLIENT_OBJECT_PATH_NAME = "/umn/inet/client";
const char *const METHOD_NAME = "method"; //optional as per freedesktop.org (maybe)

int main(int argc, char **argv)
{
  DBusMessage *msg;
  DBusMessageIter args, args1;
  DBusConnection *conn;
  DBusError err;
  DBusPendingCall *pending;
  int ret, level;
  char input[78];
  char *word;
  char *reply;
  fprintf(stderr, "Please type your message...\n");
  fgets (input, 78, stdin);
  word = input;
  dbus_error_init(&err); //initialize error VARIABLE
  fprintf(stderr, "Please type your message...\n");

  //connect
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
  ret = dbus_bus_request_name (conn, CLIENT_BUS_NAME, DBUS_NAME_FLAG_REPLACE_EXISTING, &err);

  if (dbus_error_is_set (&err))
  {
     fprintf(stderr, "dbus error during name request \n");
   }
   fprintf(stderr, "Please type your message...\n");

  msg = dbus_message_new_method_call(SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME, INTERFACE_NAME, METHOD_NAME);
  if (msg == NULL)
  {
    fprintf(stderr, "Message Null\n");
    exit(1);
  }
  dbus_message_iter_init_append(msg, &args);
  if (!dbus_message_iter_append_basic (&args, DBUS_TYPE_STRING, &word)) {
      fprintf (stderr, "Error in dbus_message_iter_append_basic\n");
      exit (1);
  }
  DBusPendingCall *pending_return;
  if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) {
      fprintf (stderr, "Error in dbus_connection_send_with_reply\n");
      exit (1);
  }
  fprintf(stderr, "sending message: %s\n", input);
  if (pending == NULL)
   {
      fprintf (stderr, "pending return is NULL");
      exit (1);
    }
  dbus_connection_flush(conn);
  dbus_message_unref(msg);
  dbus_pending_call_block(pending);
  msg = dbus_pending_call_steal_reply(pending);
  if (msg == NULL)
  {
    fprintf(stderr, "reply was null\n");
  }
  dbus_pending_call_unref(pending);
  if(!dbus_message_iter_init(msg, &args))
  {
    fprintf(stderr, "reply has no arguments\n");
  }
  dbus_message_iter_get_basic(&args, &reply);
  fprintf(stderr, "Got reply: %s\n", reply);

  dbus_message_unref(msg);
  //dbus_connection_close(conn);

  return 0;
}
