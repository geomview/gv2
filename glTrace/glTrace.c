#include "glTraceProtos.h"

void trace_glClearIndex( GLfloat c ) {
  printf("%20s(", "glClearIndex");
  printf("%10s = %f", "c", c);
  printf(");\n");
  glClearIndex ( c );
}


void trace_glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ) {
  printf("%20s(", "glClearColor");
  printf("%10s = %f", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %f", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %f", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = %f", "alpha", alpha);
  printf(");\n");
  glClearColor ( red, green, blue, alpha );
}


void trace_glClear( GLbitfield mask ) {
  printf("%20s(", "glClear");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glClear ( mask );
}


void trace_glIndexMask( GLuint mask ) {
  printf("%20s(", "glIndexMask");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glIndexMask ( mask );
}


void trace_glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha ) {
  printf("%20s(", "glColorMask");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "alpha", alpha);
  printf(");\n");
  glColorMask ( red, green, blue, alpha );
}


void trace_glAlphaFunc( GLenum func, GLclampf ref ) {
  printf("%20s(", "glAlphaFunc");
  printf("%10s = %d", "func", func);
  printf("\n%20s ", "");
  printf("%10s = %f", "ref", ref);
  printf(");\n");
  glAlphaFunc ( func, ref );
}


void trace_glBlendFunc( GLenum sfactor, GLenum dfactor ) {
  printf("%20s(", "glBlendFunc");
  printf("%10s = %d", "sfactor", sfactor);
  printf("\n%20s ", "");
  printf("%10s = %d", "dfactor", dfactor);
  printf(");\n");
  glBlendFunc ( sfactor, dfactor );
}


void trace_glLogicOp( GLenum opcode ) {
  printf("%20s(", "glLogicOp");
  printf("%10s = %d", "opcode", opcode);
  printf(");\n");
  glLogicOp ( opcode );
}


void trace_glCullFace( GLenum mode ) {
  printf("%20s(", "glCullFace");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glCullFace ( mode );
}


void trace_glFrontFace( GLenum mode ) {
  printf("%20s(", "glFrontFace");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glFrontFace ( mode );
}


void trace_glPointSize( GLfloat size ) {
  printf("%20s(", "glPointSize");
  printf("%10s = %f", "size", size);
  printf(");\n");
  glPointSize ( size );
}


void trace_glLineWidth( GLfloat width ) {
  printf("%20s(", "glLineWidth");
  printf("%10s = %f", "width", width);
  printf(");\n");
  glLineWidth ( width );
}


void trace_glLineStipple( GLint factor, GLushort pattern ) {
  printf("%20s(", "glLineStipple");
  printf("%10s = %d", "factor", factor);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pattern", pattern);
  printf(");\n");
  glLineStipple ( factor, pattern );
}


void trace_glPolygonMode( GLenum face, GLenum mode ) {
  printf("%20s(", "glPolygonMode");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glPolygonMode ( face, mode );
}


void trace_glPolygonOffset( GLfloat factor, GLfloat units ) {
  printf("%20s(", "glPolygonOffset");
  printf("%10s = %f", "factor", factor);
  printf("\n%20s ", "");
  printf("%10s = %f", "units", units);
  printf(");\n");
  glPolygonOffset ( factor, units );
}


void trace_glPolygonStipple( const GLubyte * mask ) {
  printf("%20s(", "glPolygonStipple");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glPolygonStipple ( mask );
}


void trace_glGetPolygonStipple( GLubyte * mask ) {
  printf("%20s(", "glGetPolygonStipple");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glGetPolygonStipple ( mask );
}


void trace_glEdgeFlag( GLboolean flag ) {
  printf("%20s(", "glEdgeFlag");
  printf("%10s = 0X%x", "flag", flag);
  printf(");\n");
  glEdgeFlag ( flag );
}


void trace_glEdgeFlagv( const GLboolean * flag ) {
  printf("%20s(", "glEdgeFlagv");
  printf("%10s = 0X%x", "flag", flag);
  printf(");\n");
  glEdgeFlagv ( flag );
}


void trace_glScissor( GLint x, GLint y, GLsizei width, GLsizei height ) {
  printf("%20s(", "glScissor");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf(");\n");
  glScissor ( x, y, width, height );
}


void trace_glClipPlane( GLenum plane, const GLdouble * equation ) {
  printf("%20s(", "glClipPlane");
  printf("%10s = %d", "plane", plane);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "equation", equation);
  printf(");\n");
  glClipPlane ( plane, equation );
}


void trace_glGetClipPlane( GLenum plane, GLdouble * equation ) {
  printf("%20s(", "glGetClipPlane");
  printf("%10s = %d", "plane", plane);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "equation", equation);
  printf(");\n");
  glGetClipPlane ( plane, equation );
}


void trace_glDrawBuffer( GLenum mode ) {
  printf("%20s(", "glDrawBuffer");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glDrawBuffer ( mode );
}


void trace_glReadBuffer( GLenum mode ) {
  printf("%20s(", "glReadBuffer");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glReadBuffer ( mode );
}


void trace_glEnable( GLenum cap ) {
  printf("%20s(", "glEnable");
  printf("%10s = %d", "cap", cap);
  printf(");\n");
  glEnable ( cap );
}


void trace_glDisable( GLenum cap ) {
  printf("%20s(", "glDisable");
  printf("%10s = %d", "cap", cap);
  printf(");\n");
  glDisable ( cap );
}


GLboolean trace_glIsEnabled( GLenum cap ) {
  printf("%20s(", "glIsEnabled");
  printf("%10s = %d", "cap", cap);
  printf(");\n");
  return glIsEnabled ( cap );
}


void trace_glEnableClientState( GLenum cap ) {
  printf("%20s(", "glEnableClientState");
  printf("%10s = %d", "cap", cap);
  printf(");\n");
  glEnableClientState ( cap );
}


void trace_glDisableClientState( GLenum cap ) {
  printf("%20s(", "glDisableClientState");
  printf("%10s = %d", "cap", cap);
  printf(");\n");
  glDisableClientState ( cap );
}


void trace_glGetBooleanv( GLenum pname, GLboolean * params ) {
  printf("%20s(", "glGetBooleanv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetBooleanv ( pname, params );
}


void trace_glGetDoublev( GLenum pname, GLdouble * params ) {
  printf("%20s(", "glGetDoublev");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetDoublev ( pname, params );
}


void trace_glGetFloatv( GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetFloatv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetFloatv ( pname, params );
}


void trace_glGetIntegerv( GLenum pname, GLint * params ) {
  printf("%20s(", "glGetIntegerv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetIntegerv ( pname, params );
}


void trace_glPushAttrib( GLbitfield mask ) {
  printf("%20s(", "glPushAttrib");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glPushAttrib ( mask );
}


void trace_glPopAttrib( void ) {
  printf("%20s(", "glPopAttrib");
  printf(");\n");
  glPopAttrib (  );
}


void trace_glPushClientAttrib( GLbitfield mask ) {
  printf("%20s(", "glPushClientAttrib");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glPushClientAttrib ( mask );
}


void trace_glPopClientAttrib( void ) {
  printf("%20s(", "glPopClientAttrib");
  printf(");\n");
  glPopClientAttrib (  );
}


GLint trace_glRenderMode( GLenum mode ) {
  printf("%20s(", "glRenderMode");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  return glRenderMode ( mode );
}


GLenum trace_glGetError( void ) {
  printf("%20s(", "glGetError");
  printf(");\n");
  return glGetError (  );
}


void trace_glFinish( void ) {
  printf("%20s(", "glFinish");
  printf(");\n");
  glFinish (  );
}


void trace_glFlush( void ) {
  printf("%20s(", "glFlush");
  printf(");\n");
  glFlush (  );
}


void trace_glHint( GLenum target, GLenum mode ) {
  printf("%20s(", "glHint");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glHint ( target, mode );
}


void trace_glClearDepth( GLclampd depth ) {
  printf("%20s(", "glClearDepth");
  printf("%10s = %d", "depth", depth);
  printf(");\n");
  glClearDepth ( depth );
}


void trace_glDepthFunc( GLenum func ) {
  printf("%20s(", "glDepthFunc");
  printf("%10s = %d", "func", func);
  printf(");\n");
  glDepthFunc ( func );
}


void trace_glDepthMask( GLboolean flag ) {
  printf("%20s(", "glDepthMask");
  printf("%10s = 0X%x", "flag", flag);
  printf(");\n");
  glDepthMask ( flag );
}


void trace_glDepthRange( GLclampd near_val, GLclampd far_val ) {
  printf("%20s(", "glDepthRange");
  printf("%10s = %d", "near_val", near_val);
  printf("\n%20s ", "");
  printf("%10s = %d", "far_val", far_val);
  printf(");\n");
  glDepthRange ( near_val, far_val );
}


void trace_glClearAccum( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) {
  printf("%20s(", "glClearAccum");
  printf("%10s = %f", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %f", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %f", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = %f", "alpha", alpha);
  printf(");\n");
  glClearAccum ( red, green, blue, alpha );
}


void trace_glAccum( GLenum op, GLfloat value ) {
  printf("%20s(", "glAccum");
  printf("%10s = %d", "op", op);
  printf("\n%20s ", "");
  printf("%10s = %f", "value", value);
  printf(");\n");
  glAccum ( op, value );
}


void trace_glMatrixMode( GLenum mode ) {
  printf("%20s(", "glMatrixMode");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glMatrixMode ( mode );
}


void trace_glOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val ) {
  printf("%20s(", "glOrtho");
  printf("%10s = %f", "left", left);
  printf("\n%20s ", "");
  printf("%10s = %f", "right", right);
  printf("\n%20s ", "");
  printf("%10s = %f", "bottom", bottom);
  printf("\n%20s ", "");
  printf("%10s = %f", "top", top);
  printf("\n%20s ", "");
  printf("%10s = %f", "near_val", near_val);
  printf("\n%20s ", "");
  printf("%10s = %f", "far_val", far_val);
  printf(");\n");
  glOrtho ( left, right, bottom, top, near_val, far_val );
}


void trace_glFrustum( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val ) {
  printf("%20s(", "glFrustum");
  printf("%10s = %f", "left", left);
  printf("\n%20s ", "");
  printf("%10s = %f", "right", right);
  printf("\n%20s ", "");
  printf("%10s = %f", "bottom", bottom);
  printf("\n%20s ", "");
  printf("%10s = %f", "top", top);
  printf("\n%20s ", "");
  printf("%10s = %f", "near_val", near_val);
  printf("\n%20s ", "");
  printf("%10s = %f", "far_val", far_val);
  printf(");\n");
  glFrustum ( left, right, bottom, top, near_val, far_val );
}


void trace_glViewport( GLint x, GLint y, GLsizei width, GLsizei height ) {
  printf("%20s(", "glViewport");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf(");\n");
  glViewport ( x, y, width, height );
}


void trace_glPushMatrix( void ) {
  printf("%20s(", "glPushMatrix");
  printf(");\n");
  glPushMatrix (  );
}


void trace_glPopMatrix( void ) {
  printf("%20s(", "glPopMatrix");
  printf(");\n");
  glPopMatrix (  );
}


void trace_glLoadIdentity( void ) {
  printf("%20s(", "glLoadIdentity");
  printf(");\n");
  glLoadIdentity (  );
}


void trace_glLoadMatrixd( const GLdouble * m ) {
  printf("%20s(", "glLoadMatrixd");
  printf("%10s = 0X%x", "m", m);
  printf(");\n");
  glLoadMatrixd ( m );
}


void trace_glLoadMatrixf( const GLfloat * m ) {
  printf("%20s(", "glLoadMatrixf");
  printf("%10s = 0X%x", "m", m);
  printf(");\n");
  glLoadMatrixf ( m );
}


void trace_glMultMatrixd( const GLdouble * m ) {
  printf("%20s(", "glMultMatrixd");
  printf("%10s = 0X%x", "m", m);
  printf(");\n");
  glMultMatrixd ( m );
}


void trace_glMultMatrixf( const GLfloat * m ) {
  printf("%20s(", "glMultMatrixf");
  printf("%10s = 0X%x", "m", m);
  printf(");\n");
  glMultMatrixf ( m );
}


void trace_glRotated( GLdouble angle, GLdouble x, GLdouble y, GLdouble z ) {
  printf("%20s(", "glRotated");
  printf("%10s = %f", "angle", angle);
  printf("\n%20s ", "");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glRotated ( angle, x, y, z );
}


void trace_glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z ) {
  printf("%20s(", "glRotatef");
  printf("%10s = %f", "angle", angle);
  printf("\n%20s ", "");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glRotatef ( angle, x, y, z );
}


void trace_glScaled( GLdouble x, GLdouble y, GLdouble z ) {
  printf("%20s(", "glScaled");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glScaled ( x, y, z );
}


void trace_glScalef( GLfloat x, GLfloat y, GLfloat z ) {
  printf("%20s(", "glScalef");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glScalef ( x, y, z );
}


void trace_glTranslated( GLdouble x, GLdouble y, GLdouble z ) {
  printf("%20s(", "glTranslated");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glTranslated ( x, y, z );
}


void trace_glTranslatef( GLfloat x, GLfloat y, GLfloat z ) {
  printf("%20s(", "glTranslatef");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glTranslatef ( x, y, z );
}


GLboolean trace_glIsList( GLuint list ) {
  printf("%20s(", "glIsList");
  printf("%10s = 0X%x", "list", list);
  printf(");\n");
  return glIsList ( list );
}


void trace_glDeleteLists( GLuint list, GLsizei range ) {
  printf("%20s(", "glDeleteLists");
  printf("%10s = 0X%x", "list", list);
  printf("\n%20s ", "");
  printf("%10s = %d", "range", range);
  printf(");\n");
  glDeleteLists ( list, range );
}


GLuint trace_glGenLists( GLsizei range ) {
  printf("%20s(", "glGenLists");
  printf("%10s = %d", "range", range);
  printf(");\n");
  return glGenLists ( range );
}


void trace_glNewList( GLuint list, GLenum mode ) {
  printf("%20s(", "glNewList");
  printf("%10s = 0X%x", "list", list);
  printf("\n%20s ", "");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glNewList ( list, mode );
}


void trace_glEndList( void ) {
  printf("%20s(", "glEndList");
  printf(");\n");
  glEndList (  );
}


void trace_glCallList( GLuint list ) {
  printf("%20s(", "glCallList");
  printf("%10s = 0X%x", "list", list);
  printf(");\n");
  glCallList ( list );
}


void trace_glCallLists( GLsizei n, GLenum type, const GLvoid * lists ) {
  printf("%20s(", "glCallLists");
  printf("%10s = %d", "n", n);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "lists", lists);
  printf(");\n");
  glCallLists ( n, type, lists );
}


void trace_glListBase( GLuint base ) {
  printf("%20s(", "glListBase");
  printf("%10s = 0X%x", "base", base);
  printf(");\n");
  glListBase ( base );
}


void trace_glBegin( GLenum mode ) {
  printf("%20s(", "glBegin");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glBegin ( mode );
}


void trace_glEnd( void ) {
  printf("%20s(", "glEnd");
  printf(");\n");
  glEnd (  );
}


void trace_glVertex2d( GLdouble x, GLdouble y ) {
  printf("%20s(", "glVertex2d");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf(");\n");
  glVertex2d ( x, y );
}


void trace_glVertex2f( GLfloat x, GLfloat y ) {
  printf("%20s(", "glVertex2f");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf(");\n");
  glVertex2f ( x, y );
}


void trace_glVertex2i( GLint x, GLint y ) {
  printf("%20s(", "glVertex2i");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf(");\n");
  glVertex2i ( x, y );
}


void trace_glVertex2s( GLshort x, GLshort y ) {
  printf("%20s(", "glVertex2s");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf(");\n");
  glVertex2s ( x, y );
}


void trace_glVertex3d( GLdouble x, GLdouble y, GLdouble z ) {
  printf("%20s(", "glVertex3d");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glVertex3d ( x, y, z );
}


void trace_glVertex3f( GLfloat x, GLfloat y, GLfloat z ) {
  printf("%20s(", "glVertex3f");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glVertex3f ( x, y, z );
}


void trace_glVertex3i( GLint x, GLint y, GLint z ) {
  printf("%20s(", "glVertex3i");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf(");\n");
  glVertex3i ( x, y, z );
}


void trace_glVertex3s( GLshort x, GLshort y, GLshort z ) {
  printf("%20s(", "glVertex3s");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf(");\n");
  glVertex3s ( x, y, z );
}


void trace_glVertex4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ) {
  printf("%20s(", "glVertex4d");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %f", "w", w);
  printf(");\n");
  glVertex4d ( x, y, z, w );
}


void trace_glVertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) {
  printf("%20s(", "glVertex4f");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %f", "w", w);
  printf(");\n");
  glVertex4f ( x, y, z, w );
}


void trace_glVertex4i( GLint x, GLint y, GLint z, GLint w ) {
  printf("%20s(", "glVertex4i");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %d", "w", w);
  printf(");\n");
  glVertex4i ( x, y, z, w );
}


void trace_glVertex4s( GLshort x, GLshort y, GLshort z, GLshort w ) {
  printf("%20s(", "glVertex4s");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %d", "w", w);
  printf(");\n");
  glVertex4s ( x, y, z, w );
}


void trace_glVertex2dv( const GLdouble * v ) {
  printf("%20s(", "glVertex2dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex2dv ( v );
}


void trace_glVertex2fv( const GLfloat * v ) {
  printf("%20s(", "glVertex2fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex2fv ( v );
}


void trace_glVertex2iv( const GLint * v ) {
  printf("%20s(", "glVertex2iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex2iv ( v );
}


void trace_glVertex2sv( const GLshort * v ) {
  printf("%20s(", "glVertex2sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex2sv ( v );
}


void trace_glVertex3dv( const GLdouble * v ) {
  printf("%20s(", "glVertex3dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex3dv ( v );
}


void trace_glVertex3fv( const GLfloat * v ) {
  printf("%20s(", "glVertex3fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex3fv ( v );
}


void trace_glVertex3iv( const GLint * v ) {
  printf("%20s(", "glVertex3iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex3iv ( v );
}


void trace_glVertex3sv( const GLshort * v ) {
  printf("%20s(", "glVertex3sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex3sv ( v );
}


void trace_glVertex4dv( const GLdouble * v ) {
  printf("%20s(", "glVertex4dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex4dv ( v );
}


void trace_glVertex4fv( const GLfloat * v ) {
  printf("%20s(", "glVertex4fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex4fv ( v );
}


void trace_glVertex4iv( const GLint * v ) {
  printf("%20s(", "glVertex4iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex4iv ( v );
}


void trace_glVertex4sv( const GLshort * v ) {
  printf("%20s(", "glVertex4sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glVertex4sv ( v );
}


void trace_glNormal3b( GLbyte nx, GLbyte ny, GLbyte nz ) {
  printf("%20s(", "glNormal3b");
  printf("%10s = 0X%x", "nx", nx);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "ny", ny);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "nz", nz);
  printf(");\n");
  glNormal3b ( nx, ny, nz );
}


void trace_glNormal3d( GLdouble nx, GLdouble ny, GLdouble nz ) {
  printf("%20s(", "glNormal3d");
  printf("%10s = %f", "nx", nx);
  printf("\n%20s ", "");
  printf("%10s = %f", "ny", ny);
  printf("\n%20s ", "");
  printf("%10s = %f", "nz", nz);
  printf(");\n");
  glNormal3d ( nx, ny, nz );
}


void trace_glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz ) {
  printf("%20s(", "glNormal3f");
  printf("%10s = %f", "nx", nx);
  printf("\n%20s ", "");
  printf("%10s = %f", "ny", ny);
  printf("\n%20s ", "");
  printf("%10s = %f", "nz", nz);
  printf(");\n");
  glNormal3f ( nx, ny, nz );
}


void trace_glNormal3i( GLint nx, GLint ny, GLint nz ) {
  printf("%20s(", "glNormal3i");
  printf("%10s = %d", "nx", nx);
  printf("\n%20s ", "");
  printf("%10s = %d", "ny", ny);
  printf("\n%20s ", "");
  printf("%10s = %d", "nz", nz);
  printf(");\n");
  glNormal3i ( nx, ny, nz );
}


void trace_glNormal3s( GLshort nx, GLshort ny, GLshort nz ) {
  printf("%20s(", "glNormal3s");
  printf("%10s = %d", "nx", nx);
  printf("\n%20s ", "");
  printf("%10s = %d", "ny", ny);
  printf("\n%20s ", "");
  printf("%10s = %d", "nz", nz);
  printf(");\n");
  glNormal3s ( nx, ny, nz );
}


void trace_glNormal3bv( const GLbyte * v ) {
  printf("%20s(", "glNormal3bv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glNormal3bv ( v );
}


void trace_glNormal3dv( const GLdouble * v ) {
  printf("%20s(", "glNormal3dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glNormal3dv ( v );
}


void trace_glNormal3fv( const GLfloat * v ) {
  printf("%20s(", "glNormal3fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glNormal3fv ( v );
}


void trace_glNormal3iv( const GLint * v ) {
  printf("%20s(", "glNormal3iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glNormal3iv ( v );
}


void trace_glNormal3sv( const GLshort * v ) {
  printf("%20s(", "glNormal3sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glNormal3sv ( v );
}


void trace_glIndexd( GLdouble c ) {
  printf("%20s(", "glIndexd");
  printf("%10s = %f", "c", c);
  printf(");\n");
  glIndexd ( c );
}


void trace_glIndexf( GLfloat c ) {
  printf("%20s(", "glIndexf");
  printf("%10s = %f", "c", c);
  printf(");\n");
  glIndexf ( c );
}


void trace_glIndexi( GLint c ) {
  printf("%20s(", "glIndexi");
  printf("%10s = %d", "c", c);
  printf(");\n");
  glIndexi ( c );
}


void trace_glIndexs( GLshort c ) {
  printf("%20s(", "glIndexs");
  printf("%10s = %d", "c", c);
  printf(");\n");
  glIndexs ( c );
}


void trace_glIndexub( GLubyte c ) {
  printf("%20s(", "glIndexub");
  printf("%10s = 0X%x", "c", c);
  printf(");\n");
  glIndexub ( c );
}


void trace_glIndexdv( const GLdouble * c ) {
  printf("%20s(", "glIndexdv");
  printf("%10s = 0X%x", "c", c);
  printf(");\n");
  glIndexdv ( c );
}


void trace_glIndexfv( const GLfloat * c ) {
  printf("%20s(", "glIndexfv");
  printf("%10s = 0X%x", "c", c);
  printf(");\n");
  glIndexfv ( c );
}


void trace_glIndexiv( const GLint * c ) {
  printf("%20s(", "glIndexiv");
  printf("%10s = 0X%x", "c", c);
  printf(");\n");
  glIndexiv ( c );
}


void trace_glIndexsv( const GLshort * c ) {
  printf("%20s(", "glIndexsv");
  printf("%10s = 0X%x", "c", c);
  printf(");\n");
  glIndexsv ( c );
}


void trace_glIndexubv( const GLubyte * c ) {
  printf("%20s(", "glIndexubv");
  printf("%10s = 0X%x", "c", c);
  printf(");\n");
  glIndexubv ( c );
}


void trace_glColor3b( GLbyte red, GLbyte green, GLbyte blue ) {
  printf("%20s(", "glColor3b");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf(");\n");
  glColor3b ( red, green, blue );
}


void trace_glColor3d( GLdouble red, GLdouble green, GLdouble blue ) {
  printf("%20s(", "glColor3d");
  printf("%10s = %f", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %f", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %f", "blue", blue);
  printf(");\n");
  glColor3d ( red, green, blue );
}


void trace_glColor3f( GLfloat red, GLfloat green, GLfloat blue ) {
  printf("%20s(", "glColor3f");
  printf("%10s = %f", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %f", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %f", "blue", blue);
  printf(");\n");
  glColor3f ( red, green, blue );
}


void trace_glColor3i( GLint red, GLint green, GLint blue ) {
  printf("%20s(", "glColor3i");
  printf("%10s = %d", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %d", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %d", "blue", blue);
  printf(");\n");
  glColor3i ( red, green, blue );
}


void trace_glColor3s( GLshort red, GLshort green, GLshort blue ) {
  printf("%20s(", "glColor3s");
  printf("%10s = %d", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %d", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %d", "blue", blue);
  printf(");\n");
  glColor3s ( red, green, blue );
}


void trace_glColor3ub( GLubyte red, GLubyte green, GLubyte blue ) {
  printf("%20s(", "glColor3ub");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf(");\n");
  glColor3ub ( red, green, blue );
}


void trace_glColor3ui( GLuint red, GLuint green, GLuint blue ) {
  printf("%20s(", "glColor3ui");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf(");\n");
  glColor3ui ( red, green, blue );
}


void trace_glColor3us( GLushort red, GLushort green, GLushort blue ) {
  printf("%20s(", "glColor3us");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf(");\n");
  glColor3us ( red, green, blue );
}


void trace_glColor4b( GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha ) {
  printf("%20s(", "glColor4b");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "alpha", alpha);
  printf(");\n");
  glColor4b ( red, green, blue, alpha );
}


void trace_glColor4d( GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha ) {
  printf("%20s(", "glColor4d");
  printf("%10s = %f", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %f", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %f", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = %f", "alpha", alpha);
  printf(");\n");
  glColor4d ( red, green, blue, alpha );
}


void trace_glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) {
  printf("%20s(", "glColor4f");
  printf("%10s = %f", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %f", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %f", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = %f", "alpha", alpha);
  printf(");\n");
  glColor4f ( red, green, blue, alpha );
}


void trace_glColor4i( GLint red, GLint green, GLint blue, GLint alpha ) {
  printf("%20s(", "glColor4i");
  printf("%10s = %d", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %d", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %d", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = %d", "alpha", alpha);
  printf(");\n");
  glColor4i ( red, green, blue, alpha );
}


void trace_glColor4s( GLshort red, GLshort green, GLshort blue, GLshort alpha ) {
  printf("%20s(", "glColor4s");
  printf("%10s = %d", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %d", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %d", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = %d", "alpha", alpha);
  printf(");\n");
  glColor4s ( red, green, blue, alpha );
}


void trace_glColor4ub( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha ) {
  printf("%20s(", "glColor4ub");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "alpha", alpha);
  printf(");\n");
  glColor4ub ( red, green, blue, alpha );
}


void trace_glColor4ui( GLuint red, GLuint green, GLuint blue, GLuint alpha ) {
  printf("%20s(", "glColor4ui");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "alpha", alpha);
  printf(");\n");
  glColor4ui ( red, green, blue, alpha );
}


void trace_glColor4us( GLushort red, GLushort green, GLushort blue, GLushort alpha ) {
  printf("%20s(", "glColor4us");
  printf("%10s = 0X%x", "red", red);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "green", green);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "alpha", alpha);
  printf(");\n");
  glColor4us ( red, green, blue, alpha );
}


void trace_glColor3bv( const GLbyte * v ) {
  printf("%20s(", "glColor3bv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3bv ( v );
}


void trace_glColor3dv( const GLdouble * v ) {
  printf("%20s(", "glColor3dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3dv ( v );
}


void trace_glColor3fv( const GLfloat * v ) {
  printf("%20s(", "glColor3fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3fv ( v );
}


void trace_glColor3iv( const GLint * v ) {
  printf("%20s(", "glColor3iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3iv ( v );
}


void trace_glColor3sv( const GLshort * v ) {
  printf("%20s(", "glColor3sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3sv ( v );
}


void trace_glColor3ubv( const GLubyte * v ) {
  printf("%20s(", "glColor3ubv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3ubv ( v );
}


void trace_glColor3uiv( const GLuint * v ) {
  printf("%20s(", "glColor3uiv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3uiv ( v );
}


void trace_glColor3usv( const GLushort * v ) {
  printf("%20s(", "glColor3usv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor3usv ( v );
}


void trace_glColor4bv( const GLbyte * v ) {
  printf("%20s(", "glColor4bv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4bv ( v );
}


void trace_glColor4dv( const GLdouble * v ) {
  printf("%20s(", "glColor4dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4dv ( v );
}


void trace_glColor4fv( const GLfloat * v ) {
  printf("%20s(", "glColor4fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4fv ( v );
}


void trace_glColor4iv( const GLint * v ) {
  printf("%20s(", "glColor4iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4iv ( v );
}


void trace_glColor4sv( const GLshort * v ) {
  printf("%20s(", "glColor4sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4sv ( v );
}


void trace_glColor4ubv( const GLubyte * v ) {
  printf("%20s(", "glColor4ubv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4ubv ( v );
}


void trace_glColor4uiv( const GLuint * v ) {
  printf("%20s(", "glColor4uiv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4uiv ( v );
}


void trace_glColor4usv( const GLushort * v ) {
  printf("%20s(", "glColor4usv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glColor4usv ( v );
}


void trace_glTexCoord1d( GLdouble s ) {
  printf("%20s(", "glTexCoord1d");
  printf("%10s = %f", "s", s);
  printf(");\n");
  glTexCoord1d ( s );
}


void trace_glTexCoord1f( GLfloat s ) {
  printf("%20s(", "glTexCoord1f");
  printf("%10s = %f", "s", s);
  printf(");\n");
  glTexCoord1f ( s );
}


void trace_glTexCoord1i( GLint s ) {
  printf("%20s(", "glTexCoord1i");
  printf("%10s = %d", "s", s);
  printf(");\n");
  glTexCoord1i ( s );
}


void trace_glTexCoord1s( GLshort s ) {
  printf("%20s(", "glTexCoord1s");
  printf("%10s = %d", "s", s);
  printf(");\n");
  glTexCoord1s ( s );
}


void trace_glTexCoord2d( GLdouble s, GLdouble t ) {
  printf("%20s(", "glTexCoord2d");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf(");\n");
  glTexCoord2d ( s, t );
}


void trace_glTexCoord2f( GLfloat s, GLfloat t ) {
  printf("%20s(", "glTexCoord2f");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf(");\n");
  glTexCoord2f ( s, t );
}


void trace_glTexCoord2i( GLint s, GLint t ) {
  printf("%20s(", "glTexCoord2i");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf(");\n");
  glTexCoord2i ( s, t );
}


void trace_glTexCoord2s( GLshort s, GLshort t ) {
  printf("%20s(", "glTexCoord2s");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf(");\n");
  glTexCoord2s ( s, t );
}


void trace_glTexCoord3d( GLdouble s, GLdouble t, GLdouble r ) {
  printf("%20s(", "glTexCoord3d");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf(");\n");
  glTexCoord3d ( s, t, r );
}


void trace_glTexCoord3f( GLfloat s, GLfloat t, GLfloat r ) {
  printf("%20s(", "glTexCoord3f");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf(");\n");
  glTexCoord3f ( s, t, r );
}


void trace_glTexCoord3i( GLint s, GLint t, GLint r ) {
  printf("%20s(", "glTexCoord3i");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf(");\n");
  glTexCoord3i ( s, t, r );
}


void trace_glTexCoord3s( GLshort s, GLshort t, GLshort r ) {
  printf("%20s(", "glTexCoord3s");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf(");\n");
  glTexCoord3s ( s, t, r );
}


void trace_glTexCoord4d( GLdouble s, GLdouble t, GLdouble r, GLdouble q ) {
  printf("%20s(", "glTexCoord4d");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %f", "q", q);
  printf(");\n");
  glTexCoord4d ( s, t, r, q );
}


void trace_glTexCoord4f( GLfloat s, GLfloat t, GLfloat r, GLfloat q ) {
  printf("%20s(", "glTexCoord4f");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %f", "q", q);
  printf(");\n");
  glTexCoord4f ( s, t, r, q );
}


void trace_glTexCoord4i( GLint s, GLint t, GLint r, GLint q ) {
  printf("%20s(", "glTexCoord4i");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %d", "q", q);
  printf(");\n");
  glTexCoord4i ( s, t, r, q );
}


void trace_glTexCoord4s( GLshort s, GLshort t, GLshort r, GLshort q ) {
  printf("%20s(", "glTexCoord4s");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %d", "q", q);
  printf(");\n");
  glTexCoord4s ( s, t, r, q );
}


void trace_glTexCoord1dv( const GLdouble * v ) {
  printf("%20s(", "glTexCoord1dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord1dv ( v );
}


void trace_glTexCoord1fv( const GLfloat * v ) {
  printf("%20s(", "glTexCoord1fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord1fv ( v );
}


void trace_glTexCoord1iv( const GLint * v ) {
  printf("%20s(", "glTexCoord1iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord1iv ( v );
}


void trace_glTexCoord1sv( const GLshort * v ) {
  printf("%20s(", "glTexCoord1sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord1sv ( v );
}


void trace_glTexCoord2dv( const GLdouble * v ) {
  printf("%20s(", "glTexCoord2dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord2dv ( v );
}


void trace_glTexCoord2fv( const GLfloat * v ) {
  printf("%20s(", "glTexCoord2fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord2fv ( v );
}


void trace_glTexCoord2iv( const GLint * v ) {
  printf("%20s(", "glTexCoord2iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord2iv ( v );
}


void trace_glTexCoord2sv( const GLshort * v ) {
  printf("%20s(", "glTexCoord2sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord2sv ( v );
}


void trace_glTexCoord3dv( const GLdouble * v ) {
  printf("%20s(", "glTexCoord3dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord3dv ( v );
}


void trace_glTexCoord3fv( const GLfloat * v ) {
  printf("%20s(", "glTexCoord3fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord3fv ( v );
}


void trace_glTexCoord3iv( const GLint * v ) {
  printf("%20s(", "glTexCoord3iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord3iv ( v );
}


void trace_glTexCoord3sv( const GLshort * v ) {
  printf("%20s(", "glTexCoord3sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord3sv ( v );
}


void trace_glTexCoord4dv( const GLdouble * v ) {
  printf("%20s(", "glTexCoord4dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord4dv ( v );
}


void trace_glTexCoord4fv( const GLfloat * v ) {
  printf("%20s(", "glTexCoord4fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord4fv ( v );
}


void trace_glTexCoord4iv( const GLint * v ) {
  printf("%20s(", "glTexCoord4iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord4iv ( v );
}


void trace_glTexCoord4sv( const GLshort * v ) {
  printf("%20s(", "glTexCoord4sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glTexCoord4sv ( v );
}


void trace_glRasterPos2d( GLdouble x, GLdouble y ) {
  printf("%20s(", "glRasterPos2d");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf(");\n");
  glRasterPos2d ( x, y );
}


void trace_glRasterPos2f( GLfloat x, GLfloat y ) {
  printf("%20s(", "glRasterPos2f");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf(");\n");
  glRasterPos2f ( x, y );
}


void trace_glRasterPos2i( GLint x, GLint y ) {
  printf("%20s(", "glRasterPos2i");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf(");\n");
  glRasterPos2i ( x, y );
}


void trace_glRasterPos2s( GLshort x, GLshort y ) {
  printf("%20s(", "glRasterPos2s");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf(");\n");
  glRasterPos2s ( x, y );
}


void trace_glRasterPos3d( GLdouble x, GLdouble y, GLdouble z ) {
  printf("%20s(", "glRasterPos3d");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glRasterPos3d ( x, y, z );
}


void trace_glRasterPos3f( GLfloat x, GLfloat y, GLfloat z ) {
  printf("%20s(", "glRasterPos3f");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf(");\n");
  glRasterPos3f ( x, y, z );
}


void trace_glRasterPos3i( GLint x, GLint y, GLint z ) {
  printf("%20s(", "glRasterPos3i");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf(");\n");
  glRasterPos3i ( x, y, z );
}


void trace_glRasterPos3s( GLshort x, GLshort y, GLshort z ) {
  printf("%20s(", "glRasterPos3s");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf(");\n");
  glRasterPos3s ( x, y, z );
}


void trace_glRasterPos4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ) {
  printf("%20s(", "glRasterPos4d");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %f", "w", w);
  printf(");\n");
  glRasterPos4d ( x, y, z, w );
}


void trace_glRasterPos4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) {
  printf("%20s(", "glRasterPos4f");
  printf("%10s = %f", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %f", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %f", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %f", "w", w);
  printf(");\n");
  glRasterPos4f ( x, y, z, w );
}


void trace_glRasterPos4i( GLint x, GLint y, GLint z, GLint w ) {
  printf("%20s(", "glRasterPos4i");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %d", "w", w);
  printf(");\n");
  glRasterPos4i ( x, y, z, w );
}


void trace_glRasterPos4s( GLshort x, GLshort y, GLshort z, GLshort w ) {
  printf("%20s(", "glRasterPos4s");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "z", z);
  printf("\n%20s ", "");
  printf("%10s = %d", "w", w);
  printf(");\n");
  glRasterPos4s ( x, y, z, w );
}


void trace_glRasterPos2dv( const GLdouble * v ) {
  printf("%20s(", "glRasterPos2dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos2dv ( v );
}


void trace_glRasterPos2fv( const GLfloat * v ) {
  printf("%20s(", "glRasterPos2fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos2fv ( v );
}


void trace_glRasterPos2iv( const GLint * v ) {
  printf("%20s(", "glRasterPos2iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos2iv ( v );
}


void trace_glRasterPos2sv( const GLshort * v ) {
  printf("%20s(", "glRasterPos2sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos2sv ( v );
}


void trace_glRasterPos3dv( const GLdouble * v ) {
  printf("%20s(", "glRasterPos3dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos3dv ( v );
}


void trace_glRasterPos3fv( const GLfloat * v ) {
  printf("%20s(", "glRasterPos3fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos3fv ( v );
}


void trace_glRasterPos3iv( const GLint * v ) {
  printf("%20s(", "glRasterPos3iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos3iv ( v );
}


void trace_glRasterPos3sv( const GLshort * v ) {
  printf("%20s(", "glRasterPos3sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos3sv ( v );
}


void trace_glRasterPos4dv( const GLdouble * v ) {
  printf("%20s(", "glRasterPos4dv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos4dv ( v );
}


void trace_glRasterPos4fv( const GLfloat * v ) {
  printf("%20s(", "glRasterPos4fv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos4fv ( v );
}


void trace_glRasterPos4iv( const GLint * v ) {
  printf("%20s(", "glRasterPos4iv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos4iv ( v );
}


void trace_glRasterPos4sv( const GLshort * v ) {
  printf("%20s(", "glRasterPos4sv");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glRasterPos4sv ( v );
}


void trace_glRectd( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 ) {
  printf("%20s(", "glRectd");
  printf("%10s = %f", "x1", x1);
  printf("\n%20s ", "");
  printf("%10s = %f", "y1", y1);
  printf("\n%20s ", "");
  printf("%10s = %f", "x2", x2);
  printf("\n%20s ", "");
  printf("%10s = %f", "y2", y2);
  printf(");\n");
  glRectd ( x1, y1, x2, y2 );
}


void trace_glRectf( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) {
  printf("%20s(", "glRectf");
  printf("%10s = %f", "x1", x1);
  printf("\n%20s ", "");
  printf("%10s = %f", "y1", y1);
  printf("\n%20s ", "");
  printf("%10s = %f", "x2", x2);
  printf("\n%20s ", "");
  printf("%10s = %f", "y2", y2);
  printf(");\n");
  glRectf ( x1, y1, x2, y2 );
}


void trace_glRecti( GLint x1, GLint y1, GLint x2, GLint y2 ) {
  printf("%20s(", "glRecti");
  printf("%10s = %d", "x1", x1);
  printf("\n%20s ", "");
  printf("%10s = %d", "y1", y1);
  printf("\n%20s ", "");
  printf("%10s = %d", "x2", x2);
  printf("\n%20s ", "");
  printf("%10s = %d", "y2", y2);
  printf(");\n");
  glRecti ( x1, y1, x2, y2 );
}


void trace_glRects( GLshort x1, GLshort y1, GLshort x2, GLshort y2 ) {
  printf("%20s(", "glRects");
  printf("%10s = %d", "x1", x1);
  printf("\n%20s ", "");
  printf("%10s = %d", "y1", y1);
  printf("\n%20s ", "");
  printf("%10s = %d", "x2", x2);
  printf("\n%20s ", "");
  printf("%10s = %d", "y2", y2);
  printf(");\n");
  glRects ( x1, y1, x2, y2 );
}


void trace_glRectdv( const GLdouble * v1, const GLdouble * v2 ) {
  printf("%20s(", "glRectdv");
  printf("%10s = 0X%x", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v2", v2);
  printf(");\n");
  glRectdv ( v1, v2 );
}


void trace_glRectfv( const GLfloat * v1, const GLfloat * v2 ) {
  printf("%20s(", "glRectfv");
  printf("%10s = 0X%x", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v2", v2);
  printf(");\n");
  glRectfv ( v1, v2 );
}


void trace_glRectiv( const GLint * v1, const GLint * v2 ) {
  printf("%20s(", "glRectiv");
  printf("%10s = 0X%x", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v2", v2);
  printf(");\n");
  glRectiv ( v1, v2 );
}


void trace_glRectsv( const GLshort * v1, const GLshort * v2 ) {
  printf("%20s(", "glRectsv");
  printf("%10s = 0X%x", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v2", v2);
  printf(");\n");
  glRectsv ( v1, v2 );
}


void trace_glVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid * ptr ) {
  printf("%20s(", "glVertexPointer");
  printf("%10s = %d", "size", size);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "ptr", ptr);
  printf(");\n");
  glVertexPointer ( size, type, stride, ptr );
}


void trace_glNormalPointer( GLenum type, GLsizei stride, const GLvoid * ptr ) {
  printf("%20s(", "glNormalPointer");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "ptr", ptr);
  printf(");\n");
  glNormalPointer ( type, stride, ptr );
}


void trace_glColorPointer( GLint size, GLenum type, GLsizei stride, const GLvoid * ptr ) {
  printf("%20s(", "glColorPointer");
  printf("%10s = %d", "size", size);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "ptr", ptr);
  printf(");\n");
  glColorPointer ( size, type, stride, ptr );
}


void trace_glIndexPointer( GLenum type, GLsizei stride, const GLvoid * ptr ) {
  printf("%20s(", "glIndexPointer");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "ptr", ptr);
  printf(");\n");
  glIndexPointer ( type, stride, ptr );
}


void trace_glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid * ptr ) {
  printf("%20s(", "glTexCoordPointer");
  printf("%10s = %d", "size", size);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "ptr", ptr);
  printf(");\n");
  glTexCoordPointer ( size, type, stride, ptr );
}


void trace_glEdgeFlagPointer( GLsizei stride, const GLvoid * ptr ) {
  printf("%20s(", "glEdgeFlagPointer");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "ptr", ptr);
  printf(");\n");
  glEdgeFlagPointer ( stride, ptr );
}


void trace_glGetPointerv( GLenum pname, void ** params ) {
  printf("%20s(", "glGetPointerv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetPointerv ( pname, params );
}


void trace_glArrayElement( GLint i ) {
  printf("%20s(", "glArrayElement");
  printf("%10s = %d", "i", i);
  printf(");\n");
  glArrayElement ( i );
}


void trace_glDrawArrays( GLenum mode, GLint first, GLsizei count ) {
  printf("%20s(", "glDrawArrays");
  printf("%10s = %d", "mode", mode);
  printf("\n%20s ", "");
  printf("%10s = %d", "first", first);
  printf("\n%20s ", "");
  printf("%10s = %d", "count", count);
  printf(");\n");
  glDrawArrays ( mode, first, count );
}


void trace_glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid * indices ) {
  printf("%20s(", "glDrawElements");
  printf("%10s = %d", "mode", mode);
  printf("\n%20s ", "");
  printf("%10s = %d", "count", count);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "indices", indices);
  printf(");\n");
  glDrawElements ( mode, count, type, indices );
}


void trace_glInterleavedArrays( GLenum format, GLsizei stride, const GLvoid * pointer ) {
  printf("%20s(", "glInterleavedArrays");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pointer", pointer);
  printf(");\n");
  glInterleavedArrays ( format, stride, pointer );
}


void trace_glShadeModel( GLenum mode ) {
  printf("%20s(", "glShadeModel");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glShadeModel ( mode );
}


void trace_glLightf( GLenum light, GLenum pname, GLfloat param ) {
  printf("%20s(", "glLightf");
  printf("%10s = %d", "light", light);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glLightf ( light, pname, param );
}


void trace_glLighti( GLenum light, GLenum pname, GLint param ) {
  printf("%20s(", "glLighti");
  printf("%10s = %d", "light", light);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glLighti ( light, pname, param );
}


void trace_glLightfv( GLenum light, GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glLightfv");
  printf("%10s = %d", "light", light);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glLightfv ( light, pname, params );
}


void trace_glLightiv( GLenum light, GLenum pname, const GLint * params ) {
  printf("%20s(", "glLightiv");
  printf("%10s = %d", "light", light);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glLightiv ( light, pname, params );
}


void trace_glGetLightfv( GLenum light, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetLightfv");
  printf("%10s = %d", "light", light);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetLightfv ( light, pname, params );
}


void trace_glGetLightiv( GLenum light, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetLightiv");
  printf("%10s = %d", "light", light);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetLightiv ( light, pname, params );
}


void trace_glLightModelf( GLenum pname, GLfloat param ) {
  printf("%20s(", "glLightModelf");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glLightModelf ( pname, param );
}


void trace_glLightModeli( GLenum pname, GLint param ) {
  printf("%20s(", "glLightModeli");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glLightModeli ( pname, param );
}


void trace_glLightModelfv( GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glLightModelfv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glLightModelfv ( pname, params );
}


void trace_glLightModeliv( GLenum pname, const GLint * params ) {
  printf("%20s(", "glLightModeliv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glLightModeliv ( pname, params );
}


void trace_glMaterialf( GLenum face, GLenum pname, GLfloat param ) {
  printf("%20s(", "glMaterialf");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glMaterialf ( face, pname, param );
}


void trace_glMateriali( GLenum face, GLenum pname, GLint param ) {
  printf("%20s(", "glMateriali");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glMateriali ( face, pname, param );
}


void trace_glMaterialfv( GLenum face, GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glMaterialfv");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glMaterialfv ( face, pname, params );
}


void trace_glMaterialiv( GLenum face, GLenum pname, const GLint * params ) {
  printf("%20s(", "glMaterialiv");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glMaterialiv ( face, pname, params );
}


void trace_glGetMaterialfv( GLenum face, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetMaterialfv");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetMaterialfv ( face, pname, params );
}


void trace_glGetMaterialiv( GLenum face, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetMaterialiv");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetMaterialiv ( face, pname, params );
}


void trace_glColorMaterial( GLenum face, GLenum mode ) {
  printf("%20s(", "glColorMaterial");
  printf("%10s = %d", "face", face);
  printf("\n%20s ", "");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glColorMaterial ( face, mode );
}


void trace_glPixelZoom( GLfloat xfactor, GLfloat yfactor ) {
  printf("%20s(", "glPixelZoom");
  printf("%10s = %f", "xfactor", xfactor);
  printf("\n%20s ", "");
  printf("%10s = %f", "yfactor", yfactor);
  printf(");\n");
  glPixelZoom ( xfactor, yfactor );
}


void trace_glPixelStoref( GLenum pname, GLfloat param ) {
  printf("%20s(", "glPixelStoref");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glPixelStoref ( pname, param );
}


void trace_glPixelStorei( GLenum pname, GLint param ) {
  printf("%20s(", "glPixelStorei");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glPixelStorei ( pname, param );
}


void trace_glPixelTransferf( GLenum pname, GLfloat param ) {
  printf("%20s(", "glPixelTransferf");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glPixelTransferf ( pname, param );
}


void trace_glPixelTransferi( GLenum pname, GLint param ) {
  printf("%20s(", "glPixelTransferi");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glPixelTransferi ( pname, param );
}


void trace_glPixelMapfv( GLenum map, GLint mapsize, const GLfloat * values ) {
  printf("%20s(", "glPixelMapfv");
  printf("%10s = %d", "map", map);
  printf("\n%20s ", "");
  printf("%10s = %d", "mapsize", mapsize);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glPixelMapfv ( map, mapsize, values );
}


void trace_glPixelMapuiv( GLenum map, GLint mapsize, const GLuint * values ) {
  printf("%20s(", "glPixelMapuiv");
  printf("%10s = %d", "map", map);
  printf("\n%20s ", "");
  printf("%10s = %d", "mapsize", mapsize);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glPixelMapuiv ( map, mapsize, values );
}


void trace_glPixelMapusv( GLenum map, GLint mapsize, const GLushort * values ) {
  printf("%20s(", "glPixelMapusv");
  printf("%10s = %d", "map", map);
  printf("\n%20s ", "");
  printf("%10s = %d", "mapsize", mapsize);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glPixelMapusv ( map, mapsize, values );
}


void trace_glGetPixelMapfv( GLenum map, GLfloat * values ) {
  printf("%20s(", "glGetPixelMapfv");
  printf("%10s = %d", "map", map);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glGetPixelMapfv ( map, values );
}


void trace_glGetPixelMapuiv( GLenum map, GLuint * values ) {
  printf("%20s(", "glGetPixelMapuiv");
  printf("%10s = %d", "map", map);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glGetPixelMapuiv ( map, values );
}


void trace_glGetPixelMapusv( GLenum map, GLushort * values ) {
  printf("%20s(", "glGetPixelMapusv");
  printf("%10s = %d", "map", map);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glGetPixelMapusv ( map, values );
}


void trace_glBitmap( GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap ) {
  printf("%20s(", "glBitmap");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %f", "xorig", xorig);
  printf("\n%20s ", "");
  printf("%10s = %f", "yorig", yorig);
  printf("\n%20s ", "");
  printf("%10s = %f", "xmove", xmove);
  printf("\n%20s ", "");
  printf("%10s = %f", "ymove", ymove);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "bitmap", bitmap);
  printf(");\n");
  glBitmap ( width, height, xorig, yorig, xmove, ymove, bitmap );
}


void trace_glReadPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels ) {
  printf("%20s(", "glReadPixels");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glReadPixels ( x, y, width, height, format, type, pixels );
}


void trace_glDrawPixels( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels ) {
  printf("%20s(", "glDrawPixels");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glDrawPixels ( width, height, format, type, pixels );
}


void trace_glCopyPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum type ) {
  printf("%20s(", "glCopyPixels");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf(");\n");
  glCopyPixels ( x, y, width, height, type );
}


void trace_glStencilFunc( GLenum func, GLint ref, GLuint mask ) {
  printf("%20s(", "glStencilFunc");
  printf("%10s = %d", "func", func);
  printf("\n%20s ", "");
  printf("%10s = %d", "ref", ref);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glStencilFunc ( func, ref, mask );
}


void trace_glStencilMask( GLuint mask ) {
  printf("%20s(", "glStencilMask");
  printf("%10s = 0X%x", "mask", mask);
  printf(");\n");
  glStencilMask ( mask );
}


void trace_glStencilOp( GLenum fail, GLenum zfail, GLenum zpass ) {
  printf("%20s(", "glStencilOp");
  printf("%10s = %d", "fail", fail);
  printf("\n%20s ", "");
  printf("%10s = %d", "zfail", zfail);
  printf("\n%20s ", "");
  printf("%10s = %d", "zpass", zpass);
  printf(");\n");
  glStencilOp ( fail, zfail, zpass );
}


void trace_glClearStencil( GLint s ) {
  printf("%20s(", "glClearStencil");
  printf("%10s = %d", "s", s);
  printf(");\n");
  glClearStencil ( s );
}


void trace_glTexGend( GLenum coord, GLenum pname, GLdouble param ) {
  printf("%20s(", "glTexGend");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glTexGend ( coord, pname, param );
}


void trace_glTexGenf( GLenum coord, GLenum pname, GLfloat param ) {
  printf("%20s(", "glTexGenf");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glTexGenf ( coord, pname, param );
}


void trace_glTexGeni( GLenum coord, GLenum pname, GLint param ) {
  printf("%20s(", "glTexGeni");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glTexGeni ( coord, pname, param );
}


void trace_glTexGendv( GLenum coord, GLenum pname, const GLdouble * params ) {
  printf("%20s(", "glTexGendv");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glTexGendv ( coord, pname, params );
}


void trace_glTexGenfv( GLenum coord, GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glTexGenfv");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glTexGenfv ( coord, pname, params );
}


void trace_glTexGeniv( GLenum coord, GLenum pname, const GLint * params ) {
  printf("%20s(", "glTexGeniv");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glTexGeniv ( coord, pname, params );
}


void trace_glGetTexGendv( GLenum coord, GLenum pname, GLdouble * params ) {
  printf("%20s(", "glGetTexGendv");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexGendv ( coord, pname, params );
}


void trace_glGetTexGenfv( GLenum coord, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetTexGenfv");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexGenfv ( coord, pname, params );
}


void trace_glGetTexGeniv( GLenum coord, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetTexGeniv");
  printf("%10s = %d", "coord", coord);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexGeniv ( coord, pname, params );
}


void trace_glTexEnvf( GLenum target, GLenum pname, GLfloat param ) {
  printf("%20s(", "glTexEnvf");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glTexEnvf ( target, pname, param );
}


void trace_glTexEnvi( GLenum target, GLenum pname, GLint param ) {
  printf("%20s(", "glTexEnvi");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glTexEnvi ( target, pname, param );
}


void trace_glTexEnvfv( GLenum target, GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glTexEnvfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glTexEnvfv ( target, pname, params );
}


void trace_glTexEnviv( GLenum target, GLenum pname, const GLint * params ) {
  printf("%20s(", "glTexEnviv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glTexEnviv ( target, pname, params );
}


void trace_glGetTexEnvfv( GLenum target, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetTexEnvfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexEnvfv ( target, pname, params );
}


void trace_glGetTexEnviv( GLenum target, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetTexEnviv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexEnviv ( target, pname, params );
}


void trace_glTexParameterf( GLenum target, GLenum pname, GLfloat param ) {
  printf("%20s(", "glTexParameterf");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glTexParameterf ( target, pname, param );
}


void trace_glTexParameteri( GLenum target, GLenum pname, GLint param ) {
  printf("%20s(", "glTexParameteri");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glTexParameteri ( target, pname, param );
}


void trace_glTexParameterfv( GLenum target, GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glTexParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glTexParameterfv ( target, pname, params );
}


void trace_glTexParameteriv( GLenum target, GLenum pname, const GLint * params ) {
  printf("%20s(", "glTexParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glTexParameteriv ( target, pname, params );
}


void trace_glGetTexParameterfv( GLenum target, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetTexParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexParameterfv ( target, pname, params );
}


void trace_glGetTexParameteriv( GLenum target, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetTexParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexParameteriv ( target, pname, params );
}


void trace_glGetTexLevelParameterfv( GLenum target, GLint level, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetTexLevelParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexLevelParameterfv ( target, level, pname, params );
}


void trace_glGetTexLevelParameteriv( GLenum target, GLint level, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetTexLevelParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetTexLevelParameteriv ( target, level, pname, params );
}


void trace_glTexImage1D( GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels ) {
  printf("%20s(", "glTexImage1D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalFormat", internalFormat);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "border", border);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glTexImage1D ( target, level, internalFormat, width, border, format, type, pixels );
}


void trace_glTexImage2D( GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels ) {
  printf("%20s(", "glTexImage2D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalFormat", internalFormat);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "border", border);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glTexImage2D ( target, level, internalFormat, width, height, border, format, type, pixels );
}


void trace_glGetTexImage( GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels ) {
  printf("%20s(", "glGetTexImage");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glGetTexImage ( target, level, format, type, pixels );
}


void trace_glGenTextures( GLsizei n, GLuint * textures ) {
  printf("%20s(", "glGenTextures");
  printf("%10s = %d", "n", n);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "textures", textures);
  printf(");\n");
  glGenTextures ( n, textures );
}


void trace_glDeleteTextures( GLsizei n, const GLuint * textures ) {
  printf("%20s(", "glDeleteTextures");
  printf("%10s = %d", "n", n);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "textures", textures);
  printf(");\n");
  glDeleteTextures ( n, textures );
}


void trace_glBindTexture( GLenum target, GLuint texture ) {
  printf("%20s(", "glBindTexture");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "texture", texture);
  printf(");\n");
  glBindTexture ( target, texture );
}


void trace_glPrioritizeTextures( GLsizei n, const GLuint * textures, const GLclampf * priorities ) {
  printf("%20s(", "glPrioritizeTextures");
  printf("%10s = %d", "n", n);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "textures", textures);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "priorities", priorities);
  printf(");\n");
  glPrioritizeTextures ( n, textures, priorities );
}


GLboolean trace_glAreTexturesResident( GLsizei n, const GLuint * textures, GLboolean * residences ) {
  printf("%20s(", "glAreTexturesResident");
  printf("%10s = %d", "n", n);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "textures", textures);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "residences", residences);
  printf(");\n");
  return glAreTexturesResident ( n, textures, residences );
}


GLboolean trace_glIsTexture( GLuint texture ) {
  printf("%20s(", "glIsTexture");
  printf("%10s = 0X%x", "texture", texture);
  printf(");\n");
  return glIsTexture ( texture );
}


void trace_glTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels ) {
  printf("%20s(", "glTexSubImage1D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "xoffset", xoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glTexSubImage1D ( target, level, xoffset, width, format, type, pixels );
}


void trace_glTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels ) {
  printf("%20s(", "glTexSubImage2D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "xoffset", xoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "yoffset", yoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glTexSubImage2D ( target, level, xoffset, yoffset, width, height, format, type, pixels );
}


void trace_glCopyTexImage1D( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border ) {
  printf("%20s(", "glCopyTexImage1D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "border", border);
  printf(");\n");
  glCopyTexImage1D ( target, level, internalformat, x, y, width, border );
}


void trace_glCopyTexImage2D( GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border ) {
  printf("%20s(", "glCopyTexImage2D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "border", border);
  printf(");\n");
  glCopyTexImage2D ( target, level, internalformat, x, y, width, height, border );
}


void trace_glCopyTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width ) {
  printf("%20s(", "glCopyTexSubImage1D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "xoffset", xoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf(");\n");
  glCopyTexSubImage1D ( target, level, xoffset, x, y, width );
}


void trace_glCopyTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height ) {
  printf("%20s(", "glCopyTexSubImage2D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "xoffset", xoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "yoffset", yoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf(");\n");
  glCopyTexSubImage2D ( target, level, xoffset, yoffset, x, y, width, height );
}


void trace_glMap1d( GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points ) {
  printf("%20s(", "glMap1d");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = %d", "order", order);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "points", points);
  printf(");\n");
  glMap1d ( target, u1, u2, stride, order, points );
}


void trace_glMap1f( GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points ) {
  printf("%20s(", "glMap1f");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf("\n%20s ", "");
  printf("%10s = %d", "stride", stride);
  printf("\n%20s ", "");
  printf("%10s = %d", "order", order);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "points", points);
  printf(");\n");
  glMap1f ( target, u1, u2, stride, order, points );
}


void trace_glMap2d( GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points ) {
  printf("%20s(", "glMap2d");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf("\n%20s ", "");
  printf("%10s = %d", "ustride", ustride);
  printf("\n%20s ", "");
  printf("%10s = %d", "uorder", uorder);
  printf("\n%20s ", "");
  printf("%10s = %f", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = %f", "v2", v2);
  printf("\n%20s ", "");
  printf("%10s = %d", "vstride", vstride);
  printf("\n%20s ", "");
  printf("%10s = %d", "vorder", vorder);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "points", points);
  printf(");\n");
  glMap2d ( target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points );
}


void trace_glMap2f( GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points ) {
  printf("%20s(", "glMap2f");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf("\n%20s ", "");
  printf("%10s = %d", "ustride", ustride);
  printf("\n%20s ", "");
  printf("%10s = %d", "uorder", uorder);
  printf("\n%20s ", "");
  printf("%10s = %f", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = %f", "v2", v2);
  printf("\n%20s ", "");
  printf("%10s = %d", "vstride", vstride);
  printf("\n%20s ", "");
  printf("%10s = %d", "vorder", vorder);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "points", points);
  printf(");\n");
  glMap2f ( target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points );
}


void trace_glGetMapdv( GLenum target, GLenum query, GLdouble * v ) {
  printf("%20s(", "glGetMapdv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "query", query);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glGetMapdv ( target, query, v );
}


void trace_glGetMapfv( GLenum target, GLenum query, GLfloat * v ) {
  printf("%20s(", "glGetMapfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "query", query);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glGetMapfv ( target, query, v );
}


void trace_glGetMapiv( GLenum target, GLenum query, GLint * v ) {
  printf("%20s(", "glGetMapiv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "query", query);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glGetMapiv ( target, query, v );
}


void trace_glEvalCoord1d( GLdouble u ) {
  printf("%20s(", "glEvalCoord1d");
  printf("%10s = %f", "u", u);
  printf(");\n");
  glEvalCoord1d ( u );
}


void trace_glEvalCoord1f( GLfloat u ) {
  printf("%20s(", "glEvalCoord1f");
  printf("%10s = %f", "u", u);
  printf(");\n");
  glEvalCoord1f ( u );
}


void trace_glEvalCoord1dv( const GLdouble * u ) {
  printf("%20s(", "glEvalCoord1dv");
  printf("%10s = 0X%x", "u", u);
  printf(");\n");
  glEvalCoord1dv ( u );
}


void trace_glEvalCoord1fv( const GLfloat * u ) {
  printf("%20s(", "glEvalCoord1fv");
  printf("%10s = 0X%x", "u", u);
  printf(");\n");
  glEvalCoord1fv ( u );
}


void trace_glEvalCoord2d( GLdouble u, GLdouble v ) {
  printf("%20s(", "glEvalCoord2d");
  printf("%10s = %f", "u", u);
  printf("\n%20s ", "");
  printf("%10s = %f", "v", v);
  printf(");\n");
  glEvalCoord2d ( u, v );
}


void trace_glEvalCoord2f( GLfloat u, GLfloat v ) {
  printf("%20s(", "glEvalCoord2f");
  printf("%10s = %f", "u", u);
  printf("\n%20s ", "");
  printf("%10s = %f", "v", v);
  printf(");\n");
  glEvalCoord2f ( u, v );
}


void trace_glEvalCoord2dv( const GLdouble * u ) {
  printf("%20s(", "glEvalCoord2dv");
  printf("%10s = 0X%x", "u", u);
  printf(");\n");
  glEvalCoord2dv ( u );
}


void trace_glEvalCoord2fv( const GLfloat * u ) {
  printf("%20s(", "glEvalCoord2fv");
  printf("%10s = 0X%x", "u", u);
  printf(");\n");
  glEvalCoord2fv ( u );
}


void trace_glMapGrid1d( GLint un, GLdouble u1, GLdouble u2 ) {
  printf("%20s(", "glMapGrid1d");
  printf("%10s = %d", "un", un);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf(");\n");
  glMapGrid1d ( un, u1, u2 );
}


void trace_glMapGrid1f( GLint un, GLfloat u1, GLfloat u2 ) {
  printf("%20s(", "glMapGrid1f");
  printf("%10s = %d", "un", un);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf(");\n");
  glMapGrid1f ( un, u1, u2 );
}


void trace_glMapGrid2d( GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2 ) {
  printf("%20s(", "glMapGrid2d");
  printf("%10s = %d", "un", un);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf("\n%20s ", "");
  printf("%10s = %d", "vn", vn);
  printf("\n%20s ", "");
  printf("%10s = %f", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = %f", "v2", v2);
  printf(");\n");
  glMapGrid2d ( un, u1, u2, vn, v1, v2 );
}


void trace_glMapGrid2f( GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2 ) {
  printf("%20s(", "glMapGrid2f");
  printf("%10s = %d", "un", un);
  printf("\n%20s ", "");
  printf("%10s = %f", "u1", u1);
  printf("\n%20s ", "");
  printf("%10s = %f", "u2", u2);
  printf("\n%20s ", "");
  printf("%10s = %d", "vn", vn);
  printf("\n%20s ", "");
  printf("%10s = %f", "v1", v1);
  printf("\n%20s ", "");
  printf("%10s = %f", "v2", v2);
  printf(");\n");
  glMapGrid2f ( un, u1, u2, vn, v1, v2 );
}


void trace_glEvalPoint1( GLint i ) {
  printf("%20s(", "glEvalPoint1");
  printf("%10s = %d", "i", i);
  printf(");\n");
  glEvalPoint1 ( i );
}


void trace_glEvalPoint2( GLint i, GLint j ) {
  printf("%20s(", "glEvalPoint2");
  printf("%10s = %d", "i", i);
  printf("\n%20s ", "");
  printf("%10s = %d", "j", j);
  printf(");\n");
  glEvalPoint2 ( i, j );
}


void trace_glEvalMesh1( GLenum mode, GLint i1, GLint i2 ) {
  printf("%20s(", "glEvalMesh1");
  printf("%10s = %d", "mode", mode);
  printf("\n%20s ", "");
  printf("%10s = %d", "i1", i1);
  printf("\n%20s ", "");
  printf("%10s = %d", "i2", i2);
  printf(");\n");
  glEvalMesh1 ( mode, i1, i2 );
}


void trace_glEvalMesh2( GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2 ) {
  printf("%20s(", "glEvalMesh2");
  printf("%10s = %d", "mode", mode);
  printf("\n%20s ", "");
  printf("%10s = %d", "i1", i1);
  printf("\n%20s ", "");
  printf("%10s = %d", "i2", i2);
  printf("\n%20s ", "");
  printf("%10s = %d", "j1", j1);
  printf("\n%20s ", "");
  printf("%10s = %d", "j2", j2);
  printf(");\n");
  glEvalMesh2 ( mode, i1, i2, j1, j2 );
}


void trace_glFogf( GLenum pname, GLfloat param ) {
  printf("%20s(", "glFogf");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "param", param);
  printf(");\n");
  glFogf ( pname, param );
}


void trace_glFogi( GLenum pname, GLint param ) {
  printf("%20s(", "glFogi");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "param", param);
  printf(");\n");
  glFogi ( pname, param );
}


void trace_glFogfv( GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glFogfv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glFogfv ( pname, params );
}


void trace_glFogiv( GLenum pname, const GLint * params ) {
  printf("%20s(", "glFogiv");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glFogiv ( pname, params );
}


void trace_glFeedbackBuffer( GLsizei size, GLenum type, GLfloat * buffer ) {
  printf("%20s(", "glFeedbackBuffer");
  printf("%10s = %d", "size", size);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "buffer", buffer);
  printf(");\n");
  glFeedbackBuffer ( size, type, buffer );
}


void trace_glPassThrough( GLfloat token ) {
  printf("%20s(", "glPassThrough");
  printf("%10s = %f", "token", token);
  printf(");\n");
  glPassThrough ( token );
}


void trace_glSelectBuffer( GLsizei size, GLuint * buffer ) {
  printf("%20s(", "glSelectBuffer");
  printf("%10s = %d", "size", size);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "buffer", buffer);
  printf(");\n");
  glSelectBuffer ( size, buffer );
}


void trace_glInitNames( void ) {
  printf("%20s(", "glInitNames");
  printf(");\n");
  glInitNames (  );
}


void trace_glLoadName( GLuint name ) {
  printf("%20s(", "glLoadName");
  printf("%10s = 0X%x", "name", name);
  printf(");\n");
  glLoadName ( name );
}


void trace_glPushName( GLuint name ) {
  printf("%20s(", "glPushName");
  printf("%10s = 0X%x", "name", name);
  printf(");\n");
  glPushName ( name );
}


void trace_glPopName( void ) {
  printf("%20s(", "glPopName");
  printf(");\n");
  glPopName (  );
}


void trace_glDrawRangeElements( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices ) {
  printf("%20s(", "glDrawRangeElements");
  printf("%10s = %d", "mode", mode);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "start", start);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "end", end);
  printf("\n%20s ", "");
  printf("%10s = %d", "count", count);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "indices", indices);
  printf(");\n");
  glDrawRangeElements ( mode, start, end, count, type, indices );
}


void trace_glTexImage3D( GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels ) {
  printf("%20s(", "glTexImage3D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalFormat", internalFormat);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "depth", depth);
  printf("\n%20s ", "");
  printf("%10s = %d", "border", border);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glTexImage3D ( target, level, internalFormat, width, height, depth, border, format, type, pixels );
}


void trace_glTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels ) {
  printf("%20s(", "glTexSubImage3D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "xoffset", xoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "yoffset", yoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "zoffset", zoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "depth", depth);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "pixels", pixels);
  printf(");\n");
  glTexSubImage3D ( target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels );
}


void trace_glCopyTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height ) {
  printf("%20s(", "glCopyTexSubImage3D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "level", level);
  printf("\n%20s ", "");
  printf("%10s = %d", "xoffset", xoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "yoffset", yoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "zoffset", zoffset);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf(");\n");
  glCopyTexSubImage3D ( target, level, xoffset, yoffset, zoffset, x, y, width, height );
}


void trace_glColorTable( GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table ) {
  printf("%20s(", "glColorTable");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "table", table);
  printf(");\n");
  glColorTable ( target, internalformat, width, format, type, table );
}


void trace_glColorSubTable( GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data ) {
  printf("%20s(", "glColorSubTable");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "start", start);
  printf("\n%20s ", "");
  printf("%10s = %d", "count", count);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "data", data);
  printf(");\n");
  glColorSubTable ( target, start, count, format, type, data );
}


void trace_glColorTableParameteriv( GLenum target, GLenum pname, const GLint * params ) {
  printf("%20s(", "glColorTableParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glColorTableParameteriv ( target, pname, params );
}


void trace_glColorTableParameterfv( GLenum target, GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glColorTableParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glColorTableParameterfv ( target, pname, params );
}


void trace_glCopyColorSubTable( GLenum target, GLsizei start, GLint x, GLint y, GLsizei width ) {
  printf("%20s(", "glCopyColorSubTable");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "start", start);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf(");\n");
  glCopyColorSubTable ( target, start, x, y, width );
}


void trace_glCopyColorTable( GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width ) {
  printf("%20s(", "glCopyColorTable");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf(");\n");
  glCopyColorTable ( target, internalformat, x, y, width );
}


void trace_glGetColorTable( GLenum target, GLenum format, GLenum type, GLvoid * table ) {
  printf("%20s(", "glGetColorTable");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "table", table);
  printf(");\n");
  glGetColorTable ( target, format, type, table );
}


void trace_glGetColorTableParameterfv( GLenum target, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetColorTableParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetColorTableParameterfv ( target, pname, params );
}


void trace_glGetColorTableParameteriv( GLenum target, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetColorTableParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetColorTableParameteriv ( target, pname, params );
}


void trace_glBlendEquation( GLenum mode ) {
  printf("%20s(", "glBlendEquation");
  printf("%10s = %d", "mode", mode);
  printf(");\n");
  glBlendEquation ( mode );
}


void trace_glBlendColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ) {
  printf("%20s(", "glBlendColor");
  printf("%10s = %f", "red", red);
  printf("\n%20s ", "");
  printf("%10s = %f", "green", green);
  printf("\n%20s ", "");
  printf("%10s = %f", "blue", blue);
  printf("\n%20s ", "");
  printf("%10s = %f", "alpha", alpha);
  printf(");\n");
  glBlendColor ( red, green, blue, alpha );
}


void trace_glHistogram( GLenum target, GLsizei width, GLenum internalformat, GLboolean sink ) {
  printf("%20s(", "glHistogram");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "sink", sink);
  printf(");\n");
  glHistogram ( target, width, internalformat, sink );
}


void trace_glResetHistogram( GLenum target ) {
  printf("%20s(", "glResetHistogram");
  printf("%10s = %d", "target", target);
  printf(");\n");
  glResetHistogram ( target );
}


void trace_glGetHistogram( GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values ) {
  printf("%20s(", "glGetHistogram");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "reset", reset);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glGetHistogram ( target, reset, format, type, values );
}


void trace_glGetHistogramParameterfv( GLenum target, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetHistogramParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetHistogramParameterfv ( target, pname, params );
}


void trace_glGetHistogramParameteriv( GLenum target, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetHistogramParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetHistogramParameteriv ( target, pname, params );
}


void trace_glMinmax( GLenum target, GLenum internalformat, GLboolean sink ) {
  printf("%20s(", "glMinmax");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "sink", sink);
  printf(");\n");
  glMinmax ( target, internalformat, sink );
}


void trace_glResetMinmax( GLenum target ) {
  printf("%20s(", "glResetMinmax");
  printf("%10s = %d", "target", target);
  printf(");\n");
  glResetMinmax ( target );
}


void trace_glGetMinmax( GLenum target, GLboolean reset, GLenum format, GLenum types, GLvoid * values ) {
  printf("%20s(", "glGetMinmax");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "reset", reset);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "types", types);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "values", values);
  printf(");\n");
  glGetMinmax ( target, reset, format, types, values );
}


void trace_glGetMinmaxParameterfv( GLenum target, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetMinmaxParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetMinmaxParameterfv ( target, pname, params );
}


void trace_glGetMinmaxParameteriv( GLenum target, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetMinmaxParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetMinmaxParameteriv ( target, pname, params );
}


void trace_glConvolutionFilter1D( GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image ) {
  printf("%20s(", "glConvolutionFilter1D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "image", image);
  printf(");\n");
  glConvolutionFilter1D ( target, internalformat, width, format, type, image );
}


void trace_glConvolutionFilter2D( GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image ) {
  printf("%20s(", "glConvolutionFilter2D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "image", image);
  printf(");\n");
  glConvolutionFilter2D ( target, internalformat, width, height, format, type, image );
}


void trace_glConvolutionParameterf( GLenum target, GLenum pname, GLfloat params ) {
  printf("%20s(", "glConvolutionParameterf");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %f", "params", params);
  printf(");\n");
  glConvolutionParameterf ( target, pname, params );
}


void trace_glConvolutionParameterfv( GLenum target, GLenum pname, const GLfloat * params ) {
  printf("%20s(", "glConvolutionParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glConvolutionParameterfv ( target, pname, params );
}


void trace_glConvolutionParameteri( GLenum target, GLenum pname, GLint params ) {
  printf("%20s(", "glConvolutionParameteri");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = %d", "params", params);
  printf(");\n");
  glConvolutionParameteri ( target, pname, params );
}


void trace_glConvolutionParameteriv( GLenum target, GLenum pname, const GLint * params ) {
  printf("%20s(", "glConvolutionParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glConvolutionParameteriv ( target, pname, params );
}


void trace_glCopyConvolutionFilter1D( GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width ) {
  printf("%20s(", "glCopyConvolutionFilter1D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf(");\n");
  glCopyConvolutionFilter1D ( target, internalformat, x, y, width );
}


void trace_glCopyConvolutionFilter2D( GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height ) {
  printf("%20s(", "glCopyConvolutionFilter2D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "x", x);
  printf("\n%20s ", "");
  printf("%10s = %d", "y", y);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf(");\n");
  glCopyConvolutionFilter2D ( target, internalformat, x, y, width, height );
}


void trace_glGetConvolutionFilter( GLenum target, GLenum format, GLenum type, GLvoid * image ) {
  printf("%20s(", "glGetConvolutionFilter");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "image", image);
  printf(");\n");
  glGetConvolutionFilter ( target, format, type, image );
}


void trace_glGetConvolutionParameterfv( GLenum target, GLenum pname, GLfloat * params ) {
  printf("%20s(", "glGetConvolutionParameterfv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetConvolutionParameterfv ( target, pname, params );
}


void trace_glGetConvolutionParameteriv( GLenum target, GLenum pname, GLint * params ) {
  printf("%20s(", "glGetConvolutionParameteriv");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "pname", pname);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "params", params);
  printf(");\n");
  glGetConvolutionParameteriv ( target, pname, params );
}


void trace_glSeparableFilter2D( GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column ) {
  printf("%20s(", "glSeparableFilter2D");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "internalformat", internalformat);
  printf("\n%20s ", "");
  printf("%10s = %d", "width", width);
  printf("\n%20s ", "");
  printf("%10s = %d", "height", height);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "row", row);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "column", column);
  printf(");\n");
  glSeparableFilter2D ( target, internalformat, width, height, format, type, row, column );
}


void trace_glGetSeparableFilter( GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span ) {
  printf("%20s(", "glGetSeparableFilter");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "format", format);
  printf("\n%20s ", "");
  printf("%10s = %d", "type", type);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "row", row);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "column", column);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "span", span);
  printf(");\n");
  glGetSeparableFilter ( target, format, type, row, column, span );
}


void trace_glActiveTextureARB( GLenum texture ) {
  printf("%20s(", "glActiveTextureARB");
  printf("%10s = %d", "texture", texture);
  printf(");\n");
  glActiveTextureARB ( texture );
}


void trace_glClientActiveTextureARB( GLenum texture ) {
  printf("%20s(", "glClientActiveTextureARB");
  printf("%10s = %d", "texture", texture);
  printf(");\n");
  glClientActiveTextureARB ( texture );
}


void trace_glMultiTexCoord1dARB( GLenum target, GLdouble s ) {
  printf("%20s(", "glMultiTexCoord1dARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf(");\n");
  glMultiTexCoord1dARB ( target, s );
}


void trace_glMultiTexCoord1dvARB( GLenum target, const GLdouble * v ) {
  printf("%20s(", "glMultiTexCoord1dvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord1dvARB ( target, v );
}


void trace_glMultiTexCoord1fARB( GLenum target, GLfloat s ) {
  printf("%20s(", "glMultiTexCoord1fARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf(");\n");
  glMultiTexCoord1fARB ( target, s );
}


void trace_glMultiTexCoord1fvARB( GLenum target, const GLfloat * v ) {
  printf("%20s(", "glMultiTexCoord1fvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord1fvARB ( target, v );
}


void trace_glMultiTexCoord1iARB( GLenum target, GLint s ) {
  printf("%20s(", "glMultiTexCoord1iARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf(");\n");
  glMultiTexCoord1iARB ( target, s );
}


void trace_glMultiTexCoord1ivARB( GLenum target, const GLint * v ) {
  printf("%20s(", "glMultiTexCoord1ivARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord1ivARB ( target, v );
}


void trace_glMultiTexCoord1sARB( GLenum target, GLshort s ) {
  printf("%20s(", "glMultiTexCoord1sARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf(");\n");
  glMultiTexCoord1sARB ( target, s );
}


void trace_glMultiTexCoord1svARB( GLenum target, const GLshort * v ) {
  printf("%20s(", "glMultiTexCoord1svARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord1svARB ( target, v );
}


void trace_glMultiTexCoord2dARB( GLenum target, GLdouble s, GLdouble t ) {
  printf("%20s(", "glMultiTexCoord2dARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf(");\n");
  glMultiTexCoord2dARB ( target, s, t );
}


void trace_glMultiTexCoord2dvARB( GLenum target, const GLdouble * v ) {
  printf("%20s(", "glMultiTexCoord2dvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord2dvARB ( target, v );
}


void trace_glMultiTexCoord2fARB( GLenum target, GLfloat s, GLfloat t ) {
  printf("%20s(", "glMultiTexCoord2fARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf(");\n");
  glMultiTexCoord2fARB ( target, s, t );
}


void trace_glMultiTexCoord2fvARB( GLenum target, const GLfloat * v ) {
  printf("%20s(", "glMultiTexCoord2fvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord2fvARB ( target, v );
}


void trace_glMultiTexCoord2iARB( GLenum target, GLint s, GLint t ) {
  printf("%20s(", "glMultiTexCoord2iARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf(");\n");
  glMultiTexCoord2iARB ( target, s, t );
}


void trace_glMultiTexCoord2ivARB( GLenum target, const GLint * v ) {
  printf("%20s(", "glMultiTexCoord2ivARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord2ivARB ( target, v );
}


void trace_glMultiTexCoord2sARB( GLenum target, GLshort s, GLshort t ) {
  printf("%20s(", "glMultiTexCoord2sARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf(");\n");
  glMultiTexCoord2sARB ( target, s, t );
}


void trace_glMultiTexCoord2svARB( GLenum target, const GLshort * v ) {
  printf("%20s(", "glMultiTexCoord2svARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord2svARB ( target, v );
}


void trace_glMultiTexCoord3dARB( GLenum target, GLdouble s, GLdouble t, GLdouble r ) {
  printf("%20s(", "glMultiTexCoord3dARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf(");\n");
  glMultiTexCoord3dARB ( target, s, t, r );
}


void trace_glMultiTexCoord3dvARB( GLenum target, const GLdouble * v ) {
  printf("%20s(", "glMultiTexCoord3dvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord3dvARB ( target, v );
}


void trace_glMultiTexCoord3fARB( GLenum target, GLfloat s, GLfloat t, GLfloat r ) {
  printf("%20s(", "glMultiTexCoord3fARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf(");\n");
  glMultiTexCoord3fARB ( target, s, t, r );
}


void trace_glMultiTexCoord3fvARB( GLenum target, const GLfloat * v ) {
  printf("%20s(", "glMultiTexCoord3fvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord3fvARB ( target, v );
}


void trace_glMultiTexCoord3iARB( GLenum target, GLint s, GLint t, GLint r ) {
  printf("%20s(", "glMultiTexCoord3iARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf(");\n");
  glMultiTexCoord3iARB ( target, s, t, r );
}


void trace_glMultiTexCoord3ivARB( GLenum target, const GLint * v ) {
  printf("%20s(", "glMultiTexCoord3ivARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord3ivARB ( target, v );
}


void trace_glMultiTexCoord3sARB( GLenum target, GLshort s, GLshort t, GLshort r ) {
  printf("%20s(", "glMultiTexCoord3sARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf(");\n");
  glMultiTexCoord3sARB ( target, s, t, r );
}


void trace_glMultiTexCoord3svARB( GLenum target, const GLshort * v ) {
  printf("%20s(", "glMultiTexCoord3svARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord3svARB ( target, v );
}


void trace_glMultiTexCoord4dARB( GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q ) {
  printf("%20s(", "glMultiTexCoord4dARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %f", "q", q);
  printf(");\n");
  glMultiTexCoord4dARB ( target, s, t, r, q );
}


void trace_glMultiTexCoord4dvARB( GLenum target, const GLdouble * v ) {
  printf("%20s(", "glMultiTexCoord4dvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord4dvARB ( target, v );
}


void trace_glMultiTexCoord4fARB( GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q ) {
  printf("%20s(", "glMultiTexCoord4fARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %f", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %f", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %f", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %f", "q", q);
  printf(");\n");
  glMultiTexCoord4fARB ( target, s, t, r, q );
}


void trace_glMultiTexCoord4fvARB( GLenum target, const GLfloat * v ) {
  printf("%20s(", "glMultiTexCoord4fvARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord4fvARB ( target, v );
}


void trace_glMultiTexCoord4iARB( GLenum target, GLint s, GLint t, GLint r, GLint q ) {
  printf("%20s(", "glMultiTexCoord4iARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %d", "q", q);
  printf(");\n");
  glMultiTexCoord4iARB ( target, s, t, r, q );
}


void trace_glMultiTexCoord4ivARB( GLenum target, const GLint * v ) {
  printf("%20s(", "glMultiTexCoord4ivARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord4ivARB ( target, v );
}


void trace_glMultiTexCoord4sARB( GLenum target, GLshort s, GLshort t, GLshort r, GLshort q ) {
  printf("%20s(", "glMultiTexCoord4sARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = %d", "s", s);
  printf("\n%20s ", "");
  printf("%10s = %d", "t", t);
  printf("\n%20s ", "");
  printf("%10s = %d", "r", r);
  printf("\n%20s ", "");
  printf("%10s = %d", "q", q);
  printf(");\n");
  glMultiTexCoord4sARB ( target, s, t, r, q );
}


void trace_glMultiTexCoord4svARB( GLenum target, const GLshort * v ) {
  printf("%20s(", "glMultiTexCoord4svARB");
  printf("%10s = %d", "target", target);
  printf("\n%20s ", "");
  printf("%10s = 0X%x", "v", v);
  printf(");\n");
  glMultiTexCoord4svARB ( target, v );
}


