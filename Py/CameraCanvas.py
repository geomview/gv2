from wxPython.wx       import *
from wxPython.glcanvas import *
from EventHandler      import EventHandler
from PyGv              import *
from math              import *

class CameraCanvas(wxGLCanvas):
    def __init__(self, parent, app):
        ### Context parameter setup
        # Parameters are specified as arguments to the canvas initializer
        ### Instantiation
        wxGLCanvas.__init__(self, parent, -1)
        self.parent = parent
        ### Callback setup
        # Bind the wxPython background erase event
        # Without this binding, the canvas will tend to flicker
        EVT_ERASE_BACKGROUND(self, self.OnEraseBackground)
        # Handle resizing of the window
        EVT_SIZE(self, self.OnSize)
        # Handle requests to display this canvas
        EVT_PAINT(self, self.OnPaint)

	self.app = app
        self.eventHandler = EventHandler(app, self, self.parent)
        EVT_LEFT_DOWN(self,         self.eventHandler.OnLeftDown) 
        EVT_LEFT_UP(self,           self.eventHandler.OnLeftUp)
        EVT_MOTION(self,            self.eventHandler.OnMotion)
        EVT_KEY_DOWN(self,          self.eventHandler.OnKeyPress)

	self.gvCamera      = 0
	self.gvCameraPath  = 0
	self.mgContext     = 0
	self.mgWindow      = 0
	self.SetCurrent()

    def SetGvCameraPath(self, gvCameraPath):
	self.gvCameraPath = gvCameraPath
	self.gvCamera = gvCameraPath.Resolve().CastToGvCamera()

    def SetMgContext(self, mgContext):
	self.mgContext = mgContext

    def SetMgWindow(self, mgWindow):
	self.mgWindow = mgWindow

    def OnSize(self, event):
	if (self.mgWindow):
            size = self.GetClientSize()
	    self.mgWindow.SetCurrentPosition(0, size.width, 0, size.height)

    def Render(self):
	self.OnPaint(0)

    def OnPaint(self, event):
        ''' Called once for each paint event,
        this method needs to do all of the processing required
        to display the OpenGL scene in the context.  '''
	if (self.mgContext == 0): return

        ### Draw callback
        # If you don't create a device context things seem to get unstable
        dc = wxPaintDC(self)

        ### Capture rendering context
        self.SetCurrent()

	# I think this call would better belong in OnSize above, but
	# putting it there results in GL calls before GL has been
	# initialized.  Need to understand where things like glInit()
	# &etc get called and then maybe move this called to
	# ReshapeViewport to someplace more appropriate.
	self.mgContext.ReshapeViewport()

	T = Transform3()
	self.gvCameraPath.GetCumulativeTransform(T)
#	print "gvCameraPath cum = \n", T.ToLeakyString()
	self.gvCamera.SetW2C(T)
#	print "cam W2C = \n", T.ToLeakyString()

	self.gvCamera.Render()
	self.SwapBuffers()
	# Why do we need to call SwapBuffers() here?  (we do -- taking
	# it out breaks the program).  I thought mgc.WorldEnd() would
	# do that.  Check into this.

    def OnEraseBackground(self, event):
        pass # Do nothing, to avoid flashing.
