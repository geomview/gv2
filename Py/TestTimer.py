#! /usr/local/bin/python2

from wxPython.wx import *
import time

class TestTimer(wxTimer):
    def __init__(self, app):
        wxTimer.__init__(self)
        self.app = app

    def Notify(self):
	self.app.Tick()
        #wxBell()
	#print "beep!"
