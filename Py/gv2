#! /usr/bin/python2

# #! /usr/local/bin/python2

from GeomviewApp import GeomviewApp
import sys

app = GeomviewApp(0)
for arg in sys.argv[1:]:
    app.LoadFile(arg)
app.NewCameraFrame(app.universe)

app.MainLoop()
