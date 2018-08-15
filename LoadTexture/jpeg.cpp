#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <setjmp.h>

#include <jpeglib.h>
#include <jerror.h>
#include "image.h"


typedef struct my_error_mgr
{
  struct   jpeg_error_mgr pub;  /* "public" fields */

  jmp_buf  setjmp_buffer;       /* for return to caller */
} *my_error_ptr;


void
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp (myerr->setjmp_buffer, 1);
}

Image *
image_load_jpeg (const char *filename)
{
  Image          *image;
  struct          jpeg_decompress_struct cinfo;
  struct          my_error_mgr           jerr;
  FILE           *infile;
  unsigned char **rowbuf;
  int             image_type;
  int             i;

  /* We set up the normal JPEG error routines. */
  cinfo.err = jpeg_std_error (&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  if ((infile = fopen (filename, "r")) == NULL)
    {
      printf ("Could not open '%s' for reading: %s\n", filename, strerror (errno));
      return NULL;
    }

  image = NULL;

  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp (jerr.setjmp_buffer))
    {
      /* If we get here, the JPEG code has signaled an error.
       * We need to clean up the JPEG object, close the input file, and return.
       */
      jpeg_destroy_decompress (&cinfo);
      if (infile)
        fclose (infile);

      if (image)
        image_destroy (image);

      return NULL;
    }

  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress (&cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src (&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */

  (void) jpeg_read_header (&cinfo, TRUE);

  /* We can ignore the return value from jpeg_read_header since
   *   (a) suspension is not possible with the stdio data source, and
   *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
   * See libjpeg.doc for more info.
   */

  /* Step 5: Start decompressor */

  jpeg_start_decompress (&cinfo);

  /* We may need to do some setup of our own at this point before reading
   * the data.  After jpeg_start_decompress() we have the correct scaled
   * output image dimensions available, as well as the output colormap
   * if we asked for color quantization.
   * In this example, we need to make an output work buffer of the right size.
   */

  image = (Image*)malloc (sizeof *image);
  image->width  = cinfo.output_width;
  image->height = cinfo.output_height;
  image->data = (unsigned char *)malloc (image->width * image->height * cinfo.output_components);

  rowbuf = (unsigned char **)malloc (sizeof (unsigned char *) * image->height);

  for (i = 0; i < image->height; i++)
    rowbuf[i] = image->data + cinfo.output_width * cinfo.output_components * i;

  /* Create a new image of the proper size and associate the filename with it.

     Preview layers, not being on the bottom of a layer stack, MUST HAVE
     AN ALPHA CHANNEL!
   */
  switch (cinfo.output_components)
    {
    case 1:
      image_type = IMAGE_TYPE_GRAY;
      break;

    case 3:
      image_type = IMAGE_TYPE_RGB;
      break;

    default:
      printf ("Don't know how to load JPEG images "
              "with %d color channels, using colorspace %d (%d).\n",
              cinfo.output_components, cinfo.out_color_space,
              cinfo.jpeg_color_space);
      return NULL;
      break;
    }

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */
  for (i = 0; i < image->height; i++)
    jpeg_read_scanlines (&cinfo, (JSAMPARRAY) &rowbuf[i], 1);


  /* Step 7: Finish decompression */

  jpeg_finish_decompress (&cinfo);

  /* Step 8: Release JPEG decompression object */
  jpeg_destroy_decompress (&cinfo);

  /* free up the temporary buffers */
  free (rowbuf);

  fclose (infile);

  return image;
}
