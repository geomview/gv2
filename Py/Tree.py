from wxPython.wx import *

import string

#---------------------------------------------------------------------------

class MyTreeCtrl(wxTreeCtrl):
    def __init__(self, parent, id, pos, size, style):
        wxTreeCtrl.__init__(self, parent, id, pos, size, style)


    def OnCompareItems(self, item1, item2):
        t1 = self.GetItemText(item1)
        t2 = self.GetItemText(item2)
        if t1 < t2: return -1
        if t1 == t2: return 0
        return 1

#---------------------------------------------------------------------------

class TestTreeCtrlPanel(wxPanel):
    def __init__(self, parent, app):
        # Use the WANTS_CHARS style so the panel doesn't eat the Return key.
        wxPanel.__init__(self, parent, -1, style=wxWANTS_CHARS)
        EVT_SIZE(self, self.OnSize)
	self.app = app

        #self.log = log
        tID = NewId()

        self.tree = MyTreeCtrl(self, tID, wxDefaultPosition, wxDefaultSize,
                               wxTR_HAS_BUTTONS
			       )

        #il = wxImageList(16, 16)
        #idx1 = il.Add(wxBitmap('bitmaps/smiles.bmp', wxBITMAP_TYPE_BMP))
        #idx2 = il.Add(wxBitmap('bitmaps/open.bmp', wxBITMAP_TYPE_BMP))
        #idx3 = il.Add(wxBitmap('bitmaps/new.bmp', wxBITMAP_TYPE_BMP))
        #idx4 = il.Add(wxBitmap('bitmaps/copy.bmp', wxBITMAP_TYPE_BMP))
        #idx5 = il.Add(wxBitmap('bitmaps/paste.bmp', wxBITMAP_TYPE_BMP))

        #self.tree.SetImageList(il)
        #self.il = il

        # NOTE:  For some reason tree items have to have a data object in
        #        order to be sorted.  Since our compare just uses the labels
        #        we don't need any real data, so we'll just use None.

        self.root = self.tree.AddRoot("u0 Universe")
        self.tree.SetPyData(self.root, None)
        #self.tree.SetItemImage(self.root, idx1)




        #for x in range(15):
        #    child = self.tree.AppendItem(self.root, "Item %d" % x)
        #    self.tree.SetPyData(child, None)
        #    #self.tree.SetItemImage(child, idx2)
        #    #self.tree.SetItemSelectedImage(child, idx3)
        #    for y in range(5):
        #        last = self.tree.AppendItem(child, "item %d-%s" % (x, chr(ord("a")+y)))
        #        self.tree.SetPyData(last, None)
        #        #self.tree.SetItemImage(last, idx4)
        #        #self.tree.SetItemSelectedImage(last, idx5)
        #        for z in range(5):
        #            item = self.tree.AppendItem(last,  "item %d-%s-%d" % (x, chr(ord("a")+y), z))
        #            self.tree.SetPyData(item, None)

        self.tree.Expand(self.root)
        #self.tree.Expand(worldRoot)
        EVT_TREE_ITEM_EXPANDED  (self, tID, self.OnItemExpanded)
        EVT_TREE_ITEM_COLLAPSED (self, tID, self.OnItemCollapsed)
        EVT_TREE_SEL_CHANGED    (self, tID, self.OnSelChanged)

        EVT_RIGHT_DOWN          (self.tree, self.OnRightClick)

    def AddWorld(self,    geom, name):
	#print "AddWorld"
        self.worldRoot = self.tree.AppendItem(self.root, name)
        self.tree.SetPyData(self.worldRoot, geom)

    def AddGeometry(self, geom, name):
	#print "AddGeometry"
        child = self.tree.AppendItem(self.worldRoot, name)
        self.tree.SetPyData(child, geom)

    def AddCamera(self,   geom, name):
	#print "AddCamera"
        child = self.tree.AppendItem(self.root, name)
        self.tree.SetPyData(child, geom)

    def SelectItem(self, geom):
	dummy = 0
	# Put code here later to select the item whose client data
	# is a pointer to geom.  Need to find way to find the item.

    def OnRightClick(self, event):
	dummy = 0
        #pt = event.GetPosition();
        #item, flags = self.tree.HitTest(pt)
        #print("OnRightClick: %s, %s\n" % (self.tree.GetItemText(item),
        #                                               type(item)))
        #self.tree.SelectItem(item)

    def OnSize(self, event):
        w,h = self.GetClientSizeTuple()
        self.tree.SetDimensions(0, 0, w, h)

    def OnItemExpanded(self, event):
	dummy = 0
        #item = event.GetItem()
        #print("OnItemExpanded: %s\n" % self.tree.GetItemText(item))

    def OnItemCollapsed(self, event):
	dummy = 0
        #item = event.GetItem()
        #print("OnItemCollapsed: %s\n" % self.tree.GetItemText(item))

    def OnSelChanged(self, event):
        self.item = event.GetItem()
        #print("OnSelChanged: %s\n" % self.tree.GetItemText(self.item))
	self.app.SetTarget(self.tree.GetPyData(self.item), false)
        event.Skip()
