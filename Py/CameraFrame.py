#! /usr/local/bin/python
#-*- mode: python -*-

from wxPython.wx       import *
#from OpenGL.GL import *
from time              import time

from CameraCanvas import CameraCanvas

ID_OPEN      = 201
ID_CLOSE     = 204
ID_TRANSLATE = 205
ID_ROTATE    = 206
ID_SCALE     = 207
ID_ORBIT     = 208
ID_ABOUT     = 209

class CameraFrame(wxFrame):

    def SetStatusKey(self, string):
	self.statusKey = string
	self.SetStatusText(("%3d fps    " % (.5+self.statusFPS)) + self.statusKey)

    def SetStatusFPS(self, FPS):
	self.statusFPS = FPS
	self.SetStatusText(("%3d fps    " % (.5+self.statusFPS)) + self.statusKey)

    def __init__(self, app):
	wxFrame.__init__(self, NULL, -1,
			 "Camera",
                         wxDefaultPosition, wxSize(300,300))
	self.app    = app
        self.canvas = CameraCanvas(self, app)

	self.statusFPS = 0
	self.statusKey = ""

        self.CreateStatusBar()

        cameraMenu = wxMenu()
        cameraMenu.Append(ID_CLOSE,  "C&lose",       "Close this camera window")

        motionMenu = wxMenu()
        motionMenu.Append(ID_TRANSLATE, "&Translate",   "Switch to Translate Mode")
        motionMenu.Append(ID_ROTATE,    "&Rotate",      "Switch to Rotate Mode")
        motionMenu.Append(ID_SCALE,     "&Scale",       "Switch to Scale Mode")
        motionMenu.Append(ID_ORBIT,     "&Orbit",       "Switch to Orbit Mode")


        menuBar = wxMenuBar()
        menuBar.Append(cameraMenu,   "&Camera")
        menuBar.Append(motionMenu,   "&Motion")
        self.SetMenuBar(menuBar)

        EVT_MENU(self, ID_CLOSE,   self.OnClose)

        EVT_MENU(self, ID_TRANSLATE,   self.OnTranslate)
        EVT_MENU(self, ID_ROTATE,      self.OnRotate)
        EVT_MENU(self, ID_SCALE,       self.OnScale)
        EVT_MENU(self, ID_ORBIT,       self.OnOrbit)

        EVT_MENU(self, ID_ABOUT,   self.OnAbout)
	self.lastPaintTime = time()

        self.Show(TRUE)
#        self.SetTopWindow(self)
    

    def Render(self):
	self.canvas.Render()
	t = time()
	dt = t - self.lastPaintTime
	self.lastPaintTime = t
	self.SetStatusFPS(1/dt)

    def OnAbout(self, event):
        dlg = wxMessageDialog(self,
                              "Geomview lives!",
                              "About Me", wxOK | wxICON_INFORMATION | wxCENTRE)
        dlg.ShowModal()
        dlg.Destroy()


    def OnClose(self, event):
        self.Close(true)

    def OnTranslate(self, event):
        print "Translate Mode"
	self.canvas.eventHandler.SetMotionMode("translate")

    def OnRotate(self, event):
        print "Rotate Mode"
	self.canvas.eventHandler.SetMotionMode("rotate")

    def OnScale(self, event):
        print "Scale Mode"
	self.canvas.eventHandler.SetMotionMode("scale")

    def OnOrbit(self, event):
        print "OnOrbit [orbit mode not yet implemented]"

    #def setGeom(self, geom):
    #	self.canvas.setGeom(geom)

    def Close(self, bool):
	self.app.RemoveCameraFrame(self)
	wxFrame.Close(self, bool)    


# if __name__ == '__main__':
#     app = CameraFrame(0)
#     app.MainLoop()


