/* image.c */

#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <stdio.h>

#include "image.h"


void
image_destroy (Image *image)
{
  free (image->data);
  free (image);
}

int
image_load_to_texture (const char *filename)
{
  const char *p;
  Image      *image;

  p = strrchr (filename, '.');
  if (!p)
    return -1;
  if (!strcmp (p, ".jpeg"))
    image = image_load_jpeg (filename);

  if (image)
    {
      gluBuild2DMipmaps (GL_TEXTURE_2D, 3, image->width, image->height, GL_RGB,
                         GL_UNSIGNED_BYTE, image->data);

      image_destroy (image);
    }
  return 0;
}
