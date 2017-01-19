#include <map>
#include <string>

#include <iocsh.h>
#include <epicsExport.h>

#include "UIState.h"

static std::map<std::string, UIState* > storage;

static void UIStartObject(const char* id_name, const char* object_type, const char* object_attrs)
{
	storage[std::string(id_name)]->StartObject(object_type, object_attrs);
}

static void UIEndObject(const char* id_name)
{ 
	storage[std::string(id_name)]->EndObject();
}

static void UISetProperty(const char* id_name, const char* attrs, const char* prop_class, const char* prop_text, const char* prop_vals)
{	
	storage[std::string(id_name)]->SetProperty(attrs, prop_class, prop_text, prop_vals);
}

static void UISetLayout(const char* id_name, const char* layout_class, const char* layout_name)
{
	storage[std::string(id_name)]->SetLayout(layout_class, layout_name);
}

static void UICreate(const char* id_name, const char* width, const char* height, const char* title)
{	
	storage[std::string(id_name)] = new UIState(width, height, title);
}

static void UIWrite(const char* id_name, const char* doc_name)
{
	storage[std::string(id_name)]->Close(doc_name);
	storage.erase(std::string(id_name));
}

static void UISetAttribute(const char* id_name, const char* attrs, const char* attr_class, const char* attr_text, const char* attr_vals)
{	
	storage[std::string(id_name)]->SetAttribute(attrs, attr_class, attr_text, attr_vals);
}


static bool checkLayoutArgs(const iocshArgBuf* args)
{
	if (args[0].sval == NULL)    { return false; }
	if (args[1].sval == NULL)    { return false; }
	else if (storage.find(std::string(args[0].sval)) == storage.end())    { return false; }
	
	return true;
}

static void callLayoutFunc(const iocshArgBuf* args)
{
	if (checkLayoutArgs(args))    { UISetLayout(args[0].sval, args[1].sval, args[2].sval); }
}

static const iocshArg     layout_arg0   = {"ID String",    iocshArgString};
static const iocshArg     layout_arg1   = {"Layout Class", iocshArgString};
static const iocshArg     layout_arg2   = {"Layout Name",  iocshArgString};
static const iocshArg*    layout_args[] = {&layout_arg0, &layout_arg1, &layout_arg2};
static const iocshFuncDef layout_func   = {"UISetLayout", 3, layout_args};



static bool checkObjectArgs(const iocshArgBuf* args)
{
	if (args[0].sval == NULL)    { return false; }
	if (args[1].sval == NULL)    { return false; }
	else if (storage.find(std::string(args[0].sval)) == storage.end())    { return false; }
	
	return true;
}

static void callObjectFunc(const iocshArgBuf* args)
{
	if (checkObjectArgs(args))    { UIStartObject(args[0].sval, args[1].sval, args[2].sval); }
}

static const iocshArg     start_arg0   = {"ID String",    iocshArgString};
static const iocshArg     start_arg1   = {"Widget Class", iocshArgString};
static const iocshArg     start_arg2   = {"Widget Name",  iocshArgString};
static const iocshArg*    start_args[] = {&start_arg0, &start_arg1, &start_arg2};
static const iocshFuncDef start_func   = {"UIStartObject", 3, start_args};



static bool checkPropArgs(const iocshArgBuf* args)
{
	if      (args[0].sval == NULL)    { return false; }
	else if (args[1].sval == NULL)    { return false; }
	else if (args[2].sval == NULL)    { return false; }
	else if (storage.find(std::string(args[0].sval)) == storage.end())    { return false; }
	
	return true;
}

static void callPropFunc(const iocshArgBuf* args)
{
	if (checkPropArgs(args))    { UISetProperty(args[0].sval, args[1].sval, args[2].sval, args[3].sval, args[4].sval); }
}

static const iocshArg     prop_arg0   = {"ID String",      iocshArgString};
static const iocshArg     prop_arg1   = {"Property Attributes",  iocshArgString};
static const iocshArg     prop_arg2   = {"Value Class",    iocshArgString};
static const iocshArg     prop_arg3   = {"Value Text",     iocshArgString};
static const iocshArg     prop_arg4   = {"Value Elements", iocshArgString};
static const iocshArg*    prop_args[] = {&prop_arg0, &prop_arg1, &prop_arg2, &prop_arg3, &prop_arg4};
static const iocshFuncDef prop_func   = {"UISetProperty", 5, prop_args};




static bool checkCreateArgs(const iocshArgBuf* args)
{
	if (args[0].sval == NULL)    { return false; }
	
	return true;
}

static void callCreateFunc(const iocshArgBuf* args)
{
	if (checkCreateArgs(args))    { UICreate(args[0].sval, args[1].sval, args[2].sval, args[3].sval); }
}

static const iocshArg     create_arg0   = {"ID String",   iocshArgString};
static const iocshArg     create_arg1   = {"Width",       iocshArgString};
static const iocshArg     create_arg2   = {"Height",      iocshArgString};
static const iocshArg     create_arg3   = {"Window Name", iocshArgString};
static const iocshArg*    create_args[] = {&create_arg0, &create_arg1, &create_arg2, &create_arg3};
static const iocshFuncDef create_func   = {"UICreate", 4, create_args};



static bool checkWriteArgs(const iocshArgBuf* args)
{
	if      (args[0].sval == NULL)    { return false; }
	else if (args[1].sval == NULL)    { return false; }
	else if (storage.find(std::string(args[0].sval)) == storage.end())    { return false; }
	
	return true;
}

static void callWriteFunc(const iocshArgBuf* args)
{
	if (checkWriteArgs(args))    { UIWrite(args[0].sval, args[1].sval); }
}

static const iocshArg     write_arg0   = {"ID String", iocshArgString};
static const iocshArg     write_arg1   = {"Filename",  iocshArgString};
static const iocshArg*    write_args[] = {&write_arg0, &write_arg1};
static const iocshFuncDef write_func   = {"UIWrite", 2, write_args};


static bool checkEndArgs(const iocshArgBuf* args)
{
	if (args[0].sval == NULL)    { return false; }
	else if (storage.find(std::string(args[0].sval)) == storage.end())    { return false; }
	
	return true;
}

static void callEndFunc(const iocshArgBuf* args) 
{ 
	if (checkEndArgs(args))     { UIEndObject(args[0].sval); }
}

static const iocshArg     end_arg0   = {"ID String", iocshArgString};
static const iocshArg*    end_args[] = {&end_arg0};
static const iocshFuncDef end_func   = {"UIEndObject",   1, end_args};



static bool checkAttrArgs(const iocshArgBuf* args)
{
	if      (args[0].sval == NULL)    { return false; }
	else if (args[1].sval == NULL)    { return false; }
	else if (args[2].sval == NULL)    { return false; }
	else if (storage.find(std::string(args[0].sval)) == storage.end())    { return false; }
	
	return true;
}

static void callAttrFunc(const iocshArgBuf* args)
{
	if (checkAttrArgs(args))    { UISetAttribute(args[0].sval, args[1].sval, args[2].sval, args[3].sval, args[4].sval); }
}

static const iocshArg     attr_arg0   = {"ID String",      iocshArgString};
static const iocshArg     attr_arg1   = {"Attribute Attributes",  iocshArgString};
static const iocshArg     attr_arg2   = {"Value Class",    iocshArgString};
static const iocshArg     attr_arg3   = {"Value Text",     iocshArgString};
static const iocshArg     attr_arg4   = {"Value Elements", iocshArgString};
static const iocshArg*    attr_args[] = {&attr_arg0, &attr_arg1, &attr_arg2, &attr_arg3, &attr_arg4};
static const iocshFuncDef attr_func   = {"UISetAttribute", 5, attr_args};


extern "C"
{
	static void createUIRegistrar(void)     { iocshRegister(&create_func, callCreateFunc); }
	static void writeUIRegistrar(void)      { iocshRegister(&write_func,  callWriteFunc); }
	static void startObjectRegistrar(void)  { iocshRegister(&start_func,  callObjectFunc); }
	static void setPropRegistrar(void)      { iocshRegister(&prop_func,   callPropFunc); }
	static void setLayoutRegistrar(void)    { iocshRegister(&layout_func, callLayoutFunc); }
	static void endObjectRegistrar(void)    { iocshRegister(&end_func,    callEndFunc); }
	static void setAttributeRegistrar(void) { iocshRegister(&attr_func,   callAttrFunc); }
}

epicsExportRegistrar(createUIRegistrar);
epicsExportRegistrar(writeUIRegistrar);
epicsExportRegistrar(startObjectRegistrar);
epicsExportRegistrar(setPropRegistrar);
epicsExportRegistrar(setLayoutRegistrar);
epicsExportRegistrar(endObjectRegistrar);
epicsExportRegistrar(setAttributeRegistrar);
