from wxPython.wx       import *
from PyGv              import *

class EventHandler:

    def __init__(self,app,canvas,frame):
        self.app          = app
        self.frame        = frame
	self.canvas       = canvas
        self.keyState     = 0
	self.leftIsDown   = 0
        self.x            = 0
        self.y            = 0
        self.t            = 0
        self.last_x       = 0
        self.last_y       = 0
        self.last_t       = 0
	self.motionConstructor = GvRotateMotion

    def SetMotionMode(self, mode):
	if (mode == "translate"):
	    self.motionConstructor = GvTranslateMotion
	elif (mode == "scale"):
	    self.motionConstructor = GvScaleMotion
	else:
	    self.motionConstructor = GvRotateMotion

    def OnLeftDown(self, event):
        [junk, self.x, self.y] = self.canvas.mgWindow.MapToStandardSquare(event.m_x, event.m_y)
        #self.x       = event.m_x
	#self.y       = event.m_y
	self.t       = event.GetTimestamp()
	self.last_x  = self.x
	self.last_y  = self.y
	self.last_t  = self.t
	self.last_dx = 0
	self.last_dy = 0
	self.last_dt = 0
	dx = 0
	dy = 0
	dt = 0
        self.leftIsDown = 1
        motion = self.motionConstructor(GvMotion.ONESHOT,
			        self.app.GetTarget(),
			        self.app.GetCenter(),
			        self.canvas.gvCameraPath,
			        self.t,
			        dx,
			        dy,
			        dt)
	self.app.addAction(motion)

    def OnMotion(self, event):
        if (self.leftIsDown):
            [junk, self.x, self.y] = self.canvas.mgWindow.MapToStandardSquare(event.m_x, event.m_y)
            #self.x = event.m_x
	    #self.y = event.m_y
	    self.t = event.GetTimestamp()
            dx = self.x - self.last_x
            dy = self.y - self.last_y
	    dt = self.t - self.last_t
            motion = self.motionConstructor(GvMotion.ONESHOT,
                                    self.app.GetTarget(),
                                    self.app.GetCenter(),
			            self.canvas.gvCameraPath,
                                    self.t,
                                    dx,
                                    dy,
                                    dt)
	    self.app.addAction(motion)
	    self.last_x  = self.x;
	    self.last_y  = self.y;
	    self.last_t  = self.t;
	    self.last_dx = dx
	    self.last_dy = dy
	    self.last_dt = dt

    def OnLeftUp(self, event):
        [junk, self.x, self.y] = self.canvas.mgWindow.MapToStandardSquare(event.m_x, event.m_y)
        #self.x = event.m_x
	#self.y = event.m_y
	self.t = event.GetTimestamp()
        dx = self.x - self.last_x
        dy = self.y - self.last_y
	dt = self.t - self.last_t
        if ( dt < 100 ):
            motion = self.motionConstructor(GvMotion.INERTIAL,
                                    self.app.GetTarget(),
                                    self.app.GetCenter(),
			            self.canvas.gvCameraPath,
                                    self.t,
                                    self.last_dx,
                                    self.last_dy,
                                    dt)
            self.app.addAction(motion)
        self.leftIsDown = 0

    def confirmQuit(self):
	self.frame.SetStatusKey("")
	self.keyState = 0
        confirm = wxMessageDialog(self.frame,
                                  'Really Quit Geomview?',
                                  'A Message Box',
                                  wxOK | wxCANCEL)
        if (confirm.ShowModal() == wxID_OK):
	    self.app.ExitMainLoop()
        else:
            confirm.Destroy()

    def OnKeyPress(self, event):
	key = event.GetKeyCode()
        if (self.keyState == 0):
            if (key == 27):
                self.keyState = 1
                self.frame.SetStatusKey("ESC")
            else:
                self.keyState = 0
                self.frame.SetStatusKey(`key`)
        elif (self.keyState == 1):
            if (key == 27):
                self.confirmQuit()
            else:
                self.keyState = 0
                self.frame.SetStatusKey(`key`)
        else:
            self.frame.SetStatusKey(`key`)


