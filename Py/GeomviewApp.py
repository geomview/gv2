#! /usr/local/bin/python
#-*- mode: python -*-

from wxPython.wx       import *
from CameraFrame       import *
from PyGv              import *
from TestTimer         import *
from Tree              import *

#from time             import sleep

ID_LOAD      = 101
ID_NEWCAMERA = 102
ID_EXIT      = 104
ID_ABOUT     = 109
ID_DOIT      = 120

class GeomviewApp(wxApp):

    def __init__(self, n):
        wxApp.__init__(self, n)
	self.cameraFrameList = []
	self.actionList   = []
	self.universe  = GvUniverse()
	g = self.universe.GetWorldList()
	self.target = GvPath(self.universe, g);
	self.center = GvPath(self.universe, g);

    def LoadFile(self, file):
        gop = GeomOoglParser()
        try:
            print "loading " + file
            object = gop.Load(file)
        except RuntimeError:
            print "got an exception!"
            sys.exit()
	self.universe.AddGeometry( object )
	self.target = GvPath(self.universe, object )

    def OnAbout(self, event):
        dlg = wxMessageDialog(self.frame,
                              "This is Geomview 2.0",
                              "About Me", wxOK | wxICON_INFORMATION | wxCENTRE)
        dlg.ShowModal()
        dlg.Destroy()


    def OnDoit(self, event):
	print "Doit!"
	self.universe.GetUniverseBase().Save("", "universe.out")
	print "wrote universe.out"
        #motion = GvRotateMotion(GvMotion.ONESHOT,
        #                       self.GetTarget(),
        #                       self.GetCenter(),
        #                       self.cameraFrameList[0].canvas.gvCameraPath,
        #                       0,
        #                       0.02,
        #                       0.02,
        #                       0)
        #self.addAction(motion)
        #print "have ", len(self.cameraFrameList), " cameras right now:"
        #for cf in self.cameraFrameList:
        #    print cf

    def OnExit(self, event):
        self.ExitMainLoop()

    def OnLoad(self, event):
        dlg = wxFileDialog(self.frame,
                           "Choose a file",
                           "",
                           "",
                           "*.*",
                           wxOPEN,
                           wxDefaultPosition)
        if (dlg.ShowModal() == wxID_OK):
            path = dlg.GetPath()
            self.LoadFile(path)
        dlg.Destroy()

    def OnNewCamera(self, event):
	self.NewCameraFrame(self.universe)

    def GetTarget(self):
	return self.target

    def GetCenter(self):
	return self.center

    def RemoveCameraFrame(self, cameraFrame):
	while (self.cameraFrameList.count(cameraFrame) > 0):
	    self.cameraFrameList.remove(cameraFrame)
	print "RemoveCameraFrame!"

    def Tick(self):
	for action in self.actionList:
	    action.Execute()
	    if (action.IsFinished()):
		self.actionList.remove(action)
	for cameraFrame in self.cameraFrameList:
	    cameraFrame.Render()

    def addAction(self, action):
	for a in self.actionList:
	    if (a.IsLike(action) and a.IsFragile()):
	        self.actionList.remove(a)
	self.actionList.append(action)

    def NewCameraFrame(self, universe):
        gvCamera          = GvCamera()
	gvCamera.thisown  = 0
        mgContext         = MgOpenGlContext()
        mgContext.thisown = 0
        mgWindow          = MgWindow()
        mgWindow.thisown  = 0
        cameraFrame       = CameraFrame(self)
        mgContext.SetCamera( gvCamera.GetMgCamera() )
        gvCamera.SetMgContext( mgContext )
        mgContext.SetWindow( mgWindow )
        mgContext.SetBackgroundColor(.2, .2, .8)
        mgWindow.SetCurrentPosition(0, 200, 0, 200)
	gvCamera.SetTarget( universe.GetUniverseBase() )
        universe.AddFreeCamera( gvCamera )
	gvCameraPath = GvPath( universe, gvCamera )
	T = gvCameraPath.GetLocalTransform()
	T.Translate(0, 0, -3)
	cameraFrame.canvas.SetGvCameraPath( gvCameraPath )
	cameraFrame.canvas.SetMgContext( mgContext )
	cameraFrame.canvas.SetMgWindow( mgWindow )
	cameraFrame.canvas.OnSize(0)
        self.cameraFrameList.append(cameraFrame)


    def OnInit(self):
        self.frame = wxFrame(NULL, -1,
                             "Geomview 2.0",
                             wxDefaultPosition, wxSize(200,300))

        self.frame.CreateStatusBar()
        self.frame.SetStatusText("Geomview for a New Millennium!")

        fileMenu = wxMenu()
        fileMenu.Append(ID_LOAD,      "&Load",        "Load a Geom")
        fileMenu.AppendSeparator()
        fileMenu.Append(ID_NEWCAMERA, "&New Camera",  "Create a new camera")
        fileMenu.AppendSeparator()
        fileMenu.Append(ID_DOIT,      "&Doit",        "Doit!")
        fileMenu.Append(ID_EXIT,      "E&xit",        "Terminate the program")

        helpMenu = wxMenu()
        #helpMenu.AppendSeparator()
        helpMenu.Append(ID_ABOUT, "&About",  "More information about this program")

        menuBar = wxMenuBar()
        menuBar.Append(fileMenu,   "&File")
        menuBar.Append(helpMenu,   "&Help")
        self.frame.SetMenuBar(menuBar)

	treePanel = TestTreeCtrlPanel(self.frame)

        EVT_MENU(self, ID_LOAD,      self.OnLoad)
        EVT_MENU(self, ID_NEWCAMERA, self.OnNewCamera)
        EVT_MENU(self, ID_DOIT,      self.OnDoit)
        EVT_MENU(self, ID_EXIT,      self.OnExit)

        EVT_MENU(self, ID_ABOUT,   self.OnAbout)

        self.frame.Show(TRUE)
        self.SetTopWindow(self.frame)
        self.timer = TestTimer(self)
        self.timer.Start(30)

        return TRUE



if __name__ == '__main__':
    app = GeomviewApp(0)
    app.MainLoop()
