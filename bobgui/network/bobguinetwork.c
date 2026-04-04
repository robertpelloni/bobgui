/* bobgui/network/bobguinetwork.c */
#include "bobguinetwork.h"
#include <libsoup/soup.h>

struct _BobguiNetworkAccessManager {
  GObject parent_instance;
  SoupSession *session;
};

G_DEFINE_TYPE (BobguiNetworkAccessManager, bobgui_network_access_manager, G_TYPE_OBJECT)

static void
bobgui_network_access_manager_init (BobguiNetworkAccessManager *self)
{
  self->session = soup_session_new ();
}

static void
bobgui_network_access_manager_finalize (GObject *object)
{
  BobguiNetworkAccessManager *self = BOBGUI_NETWORK_ACCESS_MANAGER (object);
  g_object_unref (self->session);
  G_OBJECT_CLASS (bobgui_network_access_manager_parent_class)->finalize (object);
}

static void
bobgui_network_access_manager_class_init (BobguiNetworkAccessManagerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  object_class->finalize = bobgui_network_access_manager_finalize;
}

BobguiNetworkAccessManager *
bobgui_network_access_manager_new (void)
{
  return g_object_new (BOBGUI_TYPE_NETWORK_ACCESS_MANAGER, NULL);
}

void
bobgui_network_get (BobguiNetworkAccessManager *self, const char *url, GAsyncReadyCallback callback, gpointer user_data)
{
  SoupMessage *msg = soup_message_new (SOUP_METHOD_GET, url);
  soup_session_send_and_read_async (self->session, msg, G_PRIORITY_DEFAULT, NULL, callback, user_data);
  g_object_unref (msg);
}

void
bobgui_network_post (BobguiNetworkAccessManager *self, const char *url, const char *data, GAsyncReadyCallback callback, gpointer user_data)
{
  SoupMessage *msg = soup_message_new (SOUP_METHOD_POST, url);
  GBytes *body = g_bytes_new (data, strlen (data));
  soup_message_set_request_body_from_bytes (msg, "application/json", body);
  soup_session_send_and_read_async (self->session, msg, G_PRIORITY_DEFAULT, NULL, callback, user_data);
  g_object_unref (msg);
  g_bytes_unref (body);
}
