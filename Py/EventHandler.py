from wxPython.wx       import *
from PyGv              import *

class EventHandler:

    def __init__(self,app,canvas,frame):
        self.app          = app
        self.frame        = frame
	self.canvas       = canvas
        self.keyState     = 0
	self.leftIsDown   = 0
        self.x0           = 0
        self.y0           = 0
        self.lastX        = 0
        self.lastY        = 0

    def OnLeftDown(self, event):
        self.x0 = event.m_x
        self.y0 = event.m_y
	self.lastX = 0
	self.lastY = 0
        self.leftIsDown = 1
	T = Transform3()
	T.Identity()
	moving = self.app.GetTarget()
	t0 = 0
	dx = 0
	dy = 0
	dt = 0
        motion = GvRotateMotion(GvMotion.ONESHOT,
			        self.app.GetTarget(),
			        self.app.GetCenter(),
			        self.canvas.gvCameraPath,
			        t0,
			        dx,
			        dy,
			        dt)
	self.app.addAction(motion)

    def OnLeftUp(self, event):
        x = event.m_x - self.x0
        y = event.m_y - self.y0
        self.x0 = event.m_x
        self.y0 = event.m_y
        if ( (self.lastX != 0) or (self.lastY != 0) ):
            t0 = 0
            dx = self.lastX
            dy = self.lastY
	    dt = 0
            motion = GvRotateMotion(GvMotion.INERTIAL,
                                    self.app.GetTarget(),
                                    self.app.GetCenter(),
			            self.canvas.gvCameraPath,
                                    t0,
                                    dx,
                                    dy,
                                    dt)
            self.app.addAction(motion)
        self.leftIsDown = 0

    def OnMotion(self, event):
        if (self.leftIsDown):
            x = event.m_x - self.x0
            y = event.m_y - self.y0
            self.x0 = event.m_x
            self.y0 = event.m_y
            t0 = 0
            dx = self.lastX
            dy = self.lastY
	    dt = 0
            motion = GvRotateMotion(GvMotion.ONESHOT,
                                    self.app.GetTarget(),
                                    self.app.GetCenter(),
			            self.canvas.gvCameraPath,
                                    t0,
                                    dx,
                                    dy,
                                    dt)
	    self.app.addAction(motion)
	    self.lastX = x;
	    self.lastY = y;

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


