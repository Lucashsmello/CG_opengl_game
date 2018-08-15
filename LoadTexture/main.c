///* main.c */
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <math.h>
//
//#include <GL/glut.h>
//
//#include "vectors.h"
//#include "image.h"
//#include "trackball.h"
//
//static void init             (void);
//static void display_callback (void);
//static void mouse_callback   (int button, int state, int x, int y);
//static void motion_callback  (int x, int y);
//
//typedef struct _GlobalState GlobalState;
//
//struct _GlobalState
//{
//  float beginx, beginy; /* position of mouse */
//  float quat[4];        /* orientation of object */
//  float dquat[4];
//  float zoom;           /* field of view in degrees */
//  int   width, height;  /* window size */
//  int   buttons;        /* which buttons are currently */
//};
//
//GlobalState info =
//{
//  1.0f, 1.0f,
//  { 0.0f, 0.0f, 0.0f, 1.0f },
//  { 0.0f, 0.0f, 0.0f, 1.0f },
//  45.0f,
//  400, 400,
//  0
//};
//
//static void
//init (void)
//{
//  Image  *image;
//  GLuint  texName;
//
//  /* We want to fill the color buffer with black */
//  glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
//
//  glEnable (GL_DEPTH_TEST);
//  glEnable (GL_TEXTURE_2D);
//
//  image = image_load_jpeg ("texture.jpeg");
//  if (image)
//    {
//      glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
//      glGenTextures (1, &texName);
//      glBindTexture (GL_TEXTURE_2D, texName);
//
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//      gluBuild2DMipmaps (GL_TEXTURE_2D, 3, image->width, image->height, GL_RGB,
//                         GL_UNSIGNED_BYTE, image->data);
//      glTexEnvi (GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//      image_destroy (image);
//    }
//  else
//    abort ();
//
//}
//
//static void
//display_callback (void)
//{
//  GLfloat  m[4][4];
//
//  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//  glMatrixMode (GL_PROJECTION);
//  glLoadIdentity ();
//  gluPerspective (info.zoom, (double)info.width / info.height, 1,100);
//  glTranslatef (0, 0, -3);
//
//
//  glMatrixMode (GL_MODELVIEW);
//  glLoadIdentity ();
//
//  add_quats (info.dquat, info.quat, info.quat);
//  build_rotmatrix (m, info.quat);
//  glMultMatrixf (&m[0][0]);
//
//  glBegin (GL_QUADS);
//    glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f, 0.5f);
//    glTexCoord2f (0.0f, 1.0f); glVertex3f ( 0.5f, -0.5f, 0.5f);
//    glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f, 0.5f);
//    glTexCoord2f (1.0f, 0.0f); glVertex3f (-0.5f,  0.5f, 0.5f);
//
//    glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,-0.5f);
//    glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f, -0.5f, 0.5f);
//    glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f, -0.5f, 0.5f);
//    glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f, -0.5f,-0.5f);
//
//    glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,-0.5f);
//    glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f, -0.5f, 0.5f);
//    glTexCoord2f (1.0f, 1.0f); glVertex3f (-0.5f,  0.5f, 0.5f);
//    glTexCoord2f (1.0f, 0.0f); glVertex3f (-0.5f,  0.5f,-0.5f);
//
//    glTexCoord2f (0.0f, 0.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
//    glTexCoord2f (0.0f, 1.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
//    glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f,  0.5f);
//    glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f,  0.5f, -0.5f);
//
//    glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
//    glTexCoord2f (0.0f, 1.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
//    glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f, -0.5f);
//    glTexCoord2f (1.0f, 0.0f); glVertex3f (-0.5f,  0.5f, -0.5f);
//
//    glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f,  0.5f, -0.5f);
//    glTexCoord2f (0.0f, 1.0f); glVertex3f (-0.5f,  0.5f,  0.5f);
//    glTexCoord2f (1.0f, 1.0f); glVertex3f ( 0.5f,  0.5f,  0.5f);
//    glTexCoord2f (1.0f, 0.0f); glVertex3f ( 0.5f,  0.5f, -0.5f);
//  glEnd ();
//
//  glFlush ();
//
//  glutSwapBuffers ();
//}
//
//static void
//reshape_callback (int width, int height)
//{
//  info.width  = width;
//  info.height = height;
//
//  glViewport (0, 0, width, height);
//  glutPostRedisplay ();
//}
//
//static void
//mouse_callback (int button, int state, int x, int y)
//{
//  info.beginx = x;
//  info.beginy = y;
//  info.dquat[0] = info.dquat[1] = info.dquat[2] = 0.0f;
//  info.dquat[3] = 1.0f;
//  if (state == GLUT_DOWN)
//    info.buttons |= (1 << button);
//  else
//    info.buttons &= ~(1 << button);
//
//  glutPostRedisplay ();
//}
//
//static void
//motion_callback (int x, int y)
//{
//  int width = info.width, height = info.height;
//
//  if (info.buttons & (1 << 0))
//    { /* drag in progress, simulate trackball */
//      trackball (info.dquat,
//                 (2.0 * info.beginx -             width) / width,
//                 (           height - 2.0 * info.beginy) / height,
//                 (          2.0 * x -             width) / width,
//                 (           height -           2.0 * y) / height );
//    }
//  else if (info.buttons & (1 << 2))
//    {
//      /* zooming drag */
//      info.zoom -= ( (y - info.beginy) / height) * 40.0;
//      info.zoom = CLAMP (info.zoom, 5.0, 120.0);
//    }
//
//  info.beginx = x;
//  info.beginy = y;
//
//  glutPostRedisplay ();
//}
//
//int
//main (int argc, char** argv)
//{
//  glutInit (&argc, argv);
//  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//  glutInitWindowPosition (0, 0);
//  glutInitWindowSize (info.width, info.height);
//  glutCreateWindow ("Texture (JPEG)");
//
//  init ();
//
//  glutDisplayFunc (display_callback);
//  glutReshapeFunc (reshape_callback);
//  glutMotionFunc (motion_callback);
//  glutMouseFunc (mouse_callback);
//
//  glutMainLoop ();
//
//  return 0;
//}
//
