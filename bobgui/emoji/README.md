Emoji data
==========

We use Emoji data from Unicode and the CLDR, stored in a GVariant.
The immediate source for our data is the json files from

  https://github.com/milesj/emojibase.git

<<<<<<< HEAD:bobgui/emoji/README.md
To convert the data from that repository to a GVariant that BOBGUI
=======
To convert the data from that repository to a GVariant that GTK
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gtk/emoji/README.md
can use, the convert-emoji tool can be used:

  convert-emoji $emojibase/packages/data/de/data.raw.json de.data

for example (for German).

<<<<<<< HEAD:bobgui/emoji/README.md
To make these usable by BOBGUI, we wrap them in a resource bundle
that has the GVariant as

   /org/bobgui/libbobgui/emoji/de.data

and install the resulting resource bundle at this location:

  /usr/share/bobgui-4.0/emoji/de.gresource
=======
To make these usable by GTK, we wrap them in a resource bundle
that has the GVariant as

   /org/gtk/libgtk/emoji/de.data

and install the resulting resource bundle at this location:

  /usr/share/gtk-4.0/emoji/de.gresource
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gtk/emoji/README.md
