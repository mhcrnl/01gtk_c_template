#include <stdlib.h>
#include <gtk/gtk.h>

/*
*   GLOBAL VARIABLES:
*/
const gchar *title = "Gtk+2 C Template";
const gchar *authors[] = {"Mihai Cornel mhcrnl@gmail.com", NULL,};
const gchar *date  = "30 noe 2018";
const gchar *version = "0.01";
const gchar *license = "GPL3v";
const gchar *compile = "cc `pkg-config --cflags --libs gtk+-2.0` main.c -o main ";

GtkWidget *button = NULL;
GtkWidget *win = NULL;
GtkWidget *vbox = NULL;
GdkPixbuf *icon;

/* MENU */
GtkWidget *menubar      = NULL;
GtkWidget *file_menu = NULL;
GtkWidget *file = NULL;
GtkWidget *file_quit = NULL;
GtkWidget *help_menu = NULL ;
GtkWidget *help = NULL ;
GtkWidget *help_about = NULL;
GtkWidget *help_bzr = NULL;
GtkWidget *help_git = NULL;
/**********************************************************************
*   FUNCTIONS:
***********************************************************************/
static void helloWorld      (GtkWidget *wid, GtkWidget *win);
static void add_menu        (GtkWidget *wid);
static void about_show      (void);
static void bzr_push        (void);
static void git_push        (void);
GdkPixbuf   *create_pixbuf  (const gchar *filename);
//**********************************************************************
GdkPixbuf   *create_pixbuf  (const gchar *filename){
    GdkPixbuf *pixbuf;
    GError    *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf){
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}
//***********************************************************************
static void git_push(void) {
    system("./gitpush.sh");
}
//**********************************************************************
static void bzr_push(void) {
    system("./bzrpush.sh");
}
//***********************************************************************
static void about_show(void)
{
	GtkWidget * about_dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog), license);
	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_destroy(about_dialog);
}
//************************************************************************
static void add_menu   (GtkWidget *wid)
{   /** MENUBAR */
    menubar     = gtk_menu_bar_new();
    /** FILE MENU */
    file_menu   = gtk_menu_new();
    /* FILE ITEMS */
    file        = gtk_menu_item_new_with_label("File");
    file_quit   = gtk_menu_item_new_with_label("Quit");
    /* HELP MENU */
    help_menu    = gtk_menu_new();
    /* HELP ITEMS */
    help         = gtk_menu_item_new_with_label("Help");
    help_about   = gtk_menu_item_new_with_label("About");
    help_bzr     = gtk_menu_item_new_with_label("Bazaar");
    help_git     = gtk_menu_item_new_with_label("Github");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), help_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_about);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_bzr);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_git);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);

    /* ADD MENU TO vbox */
    gtk_box_pack_start(GTK_BOX(vbox), menubar,FALSE,FALSE,0);


}
//*****************************************************************************************************************


static void helloWorld (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, title);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}
//************************************************************************************************************************
int main (int argc, char *argv[])
{


  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), title);
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(win), 450, 300);

  icon = create_pixbuf("animal-monkey.png");
  gtk_window_set_icon(GTK_WINDOW(win), icon);

  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  /* Create a vertical box with buttons */
  vbox = gtk_vbox_new (TRUE, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  add_menu(NULL);
  /* SIGNALS */
  g_signal_connect(file_quit, "activate", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(help_about, "activate", G_CALLBACK(about_show), win);
  g_signal_connect(help_bzr, "activate", G_CALLBACK(bzr_push), NULL);
  g_signal_connect(help_git, "activate", G_CALLBACK(git_push), NULL);

  button = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (helloWorld), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", gtk_main_quit, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
