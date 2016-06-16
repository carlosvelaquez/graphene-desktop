/*
 * This file is part of graphene-desktop, the desktop environment of VeltOS.
 * Copyright (C) 2016 Velt Technologies, Aidan Shafran <zelbrium@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * main.c
 * Main file for the panel application.
 * Initializes a GtkApplication with one window, the GraphenePanel.
 * Cannot be a part of panel.c since panel.c is compiled into libgraphene.
 */

#include "panel.h"

static void activate(GtkApplication *app, gpointer userdata);

int main(int argc, char **argv)
{
  GtkApplication *app = gtk_application_new("io.velt.graphene-panel", G_APPLICATION_FLAGS_NONE);
  g_object_set(G_OBJECT(app), "register-session", TRUE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(graphene_panel_get_default());
  g_object_unref(app);
  return status;
}

static void activate(GtkApplication *app, gpointer userdata)
{
  GraphenePanel *panel = graphene_panel_get_default(); // First call will create it
  gtk_application_add_window(app, GTK_WINDOW(panel));
  gtk_widget_show(GTK_WIDGET(panel));  
}