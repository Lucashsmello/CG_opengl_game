/* image.h */

#ifndef IMAGE_H
#define IMAGE_H



enum _ImageType
{
  IMAGE_TYPE_GRAY,
  IMAGE_TYPE_GRAYA,
  IMAGE_TYPE_RGB,
  IMAGE_TYPE_RGBA
};

typedef enum   _ImageType ImageType;
typedef struct _Image     Image;

struct _Image
{
  int            width;
  int            height;
  ImageType      type;
  unsigned char *data;
};

//Image *image_load_png  (const char *filename);
Image *image_load_pnm  (const char *filename);
//Image *image_load_tga  (const char *filename);
Image *image_load_jpeg (const char *filename);
void   image_destroy   (Image *image);

int image_load_to_texture (const char *filename);

#endif
