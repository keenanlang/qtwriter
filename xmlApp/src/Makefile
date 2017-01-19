TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
# ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================
#=============================
# xxxRecord.h will be created from xxxRecord.dbd
DBD += xmlSupport.dbd

LIBRARY_IOC += xml

SRC_DIRS += ../libxml

xml_SRCS += buf.c
xml_SRCS += c14n.c
xml_SRCS += catalog.c
xml_SRCS += chvalid.c
xml_SRCS += dict.c
xml_SRCS += debugXML.c
xml_SRCS += DOCBparser.c
xml_SRCS += encoding.c
xml_SRCS += entities.c
xml_SRCS += error.c
xml_SRCS += globals.c
xml_SRCS += hash.c
xml_SRCS += HTMLparser.c
xml_SRCS += HTMLtree.c
xml_SRCS += legacy.c
xml_SRCS += list.c
xml_SRCS += nanoftp.c
xml_SRCS += nanohttp.c
xml_SRCS += parser.c
xml_SRCS += parserInternals.c
xml_SRCS += pattern.c
xml_SRCS += relaxng.c
xml_SRCS += runsuite.c
xml_SRCS += runxmlconf.c
xml_SRCS += SAX2.c
xml_SRCS += SAX.c
xml_SRCS += schematron.c
xml_SRCS += threads.c
xml_SRCS += tree.c
xml_SRCS += trio.c
xml_SRCS += trionan.c
xml_SRCS += triostr.c
xml_SRCS += uri.c
xml_SRCS += valid.c
xml_SRCS += xinclude.c
xml_SRCS += xlink.c
xml_SRCS += xmlcatalog.c
xml_SRCS += xmlIO.c
xml_SRCS += xmllint.c
xml_SRCS += xmlmemory.c
xml_SRCS += xmlmodule.c
xml_SRCS += xmlreader.c
xml_SRCS += xmlregexp.c
xml_SRCS += xmlsave.c
xml_SRCS += xmlschemas.c
xml_SRCS += xmlschemastypes.c
xml_SRCS += xmlstring.c
xml_SRCS += xmlunicode.c
xml_SRCS += xmlwriter.c
xml_SRCS += xpath.c
xml_SRCS += xpointer.c
xml_SRCS += xzlib.c

xml_SRCS += devxml.cpp
xml_SRCS += UIState.cpp

xml_LIBS += $(EPICS_BASE_IOC_LIBS)

PROD_IOC = xmlioc
DBD += xmlioc.dbd

xmlioc_DBD += base.dbd
xmlioc_DBD += xmlSupport.dbd

xmlioc_LIBS += xml
xmlioc_LIBS += $(EPICS_BASE_IOC_LIBS)

xmlioc_SRCS += xmlioc_registerRecordDeviceDriver.cpp

xmlioc_SRCS_DEFAULT += xmlMain.c
xmlioc_SRCS_vxWorks += -nil-
#=============================
# build an ioc application for testing
#===========================
include $(TOP)/configure/RULES
#----------------------------------------
# ADD RULES AFTER THIS LINE
