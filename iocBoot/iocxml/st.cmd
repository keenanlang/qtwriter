################################################################################
# Tell EPICS all about the record types, device-support modules, drivers,
# etc. in the software we just loaded (xxx.munch)
dbLoadDatabase("../../dbd/xmlioc.dbd")
xmlioc_registerRecordDeviceDriver(pdbbase)

#######
iocInit
#######

UICreate("TEST", "400", "370", "TestWindow")


UIStartObject("TEST", "widget", "class=QTabWidget, name=tabWidget")
UISetProperty("TEST", "name=geometry", "rect", "", "x=0, y=0, width=400, height=370")
UISetProperty("TEST", "name=tabPosition", "enum", "QTabWidget::West", "")

UIStartObject("TEST", "widget", "class=QWidget, name=tab")
UISetAttribute("TEST", "name=title", "string", "Labels", "")

< tab1.cmd

UIEndObject("TEST")

UIStartObject("TEST", "widget", "class=QWidget, name=tab_2")
UISetAttribute("TEST", "name=title", "string", "Gauges")

< tab2.cmd

UIEndObject("TEST")

UIEndObject("TEST")

UIWrite("TEST", "test.ui")
