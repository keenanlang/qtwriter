#Makefile at top of application tree
TOP = .
include $(TOP)/configure/CONFIG
DIRS += configure xmlApp
scriptApp_DEPEND_DIRS = configure
include $(TOP)/configure/RULES_TOP
