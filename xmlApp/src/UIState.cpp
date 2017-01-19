#include <fstream>
#include <sstream>
//#include <iostream>

#include <macLib.h>

#include "UIState.h"

void UIState::StartObject(const char* object_type, const char* object_attrs)
{
	if (this->depth == this->active_layouts.front())
	{
		xmlTextWriterStartElement(this->printer, BAD_CAST "item");
	}
	
	xmlTextWriterStartElement(this->printer, BAD_CAST object_type);
	
	char** attr_pairs;
	
	macParseDefns(NULL, object_attrs, &attr_pairs);
	
	for ( ; attr_pairs && attr_pairs[0]; attr_pairs += 2)
	{
		xmlTextWriterWriteAttribute(this->printer, BAD_CAST attr_pairs[0], BAD_CAST attr_pairs[1]);
	}
	
	this->depth += 1;
}

void UIState::EndObject()
{	
	// End Layout
	if (this->depth == this->active_layouts.front())
	{
		xmlTextWriterEndElement(this->printer);
		this->active_layouts.pop_front();
	}

	xmlTextWriterEndElement(this->printer);
	
	// End Item
	if (this->depth == (this->active_layouts.front() + 1))
	{
		xmlTextWriterEndElement(this->printer);
	}
	
	this->depth -= 1;
}

void UIState::SetProperty(const char* attrs, const char* prop_class, const char* prop_text, const char* prop_vals)
{
	xmlTextWriterStartElement(  this->printer, BAD_CAST "property");
	
	char** attr_pairs;
	
	macParseDefns(NULL, attrs, &attr_pairs);
	
	for ( ; attr_pairs && attr_pairs[0]; attr_pairs += 2)
	{
		xmlTextWriterWriteAttribute(this->printer, BAD_CAST attr_pairs[0], BAD_CAST attr_pairs[1]);
	}
	
	xmlTextWriterStartElement(this->printer, BAD_CAST prop_class);
	
	if (prop_text)
	{
		std::string check(prop_text);
		
		if (not check.empty())
		{
			xmlTextWriterWriteString(this->printer, BAD_CAST prop_text);
		}
	}
	
	char** value_pairs;
	
	if (prop_vals)
	{
		macParseDefns(NULL, prop_vals, &value_pairs);
		
		for ( ; value_pairs && value_pairs[0]; value_pairs += 2)
		{
			xmlTextWriterStartElement(this->printer, BAD_CAST value_pairs[0]);
			xmlTextWriterWriteString( this->printer, BAD_CAST value_pairs[1]);
			xmlTextWriterEndElement(  this->printer);
		}
	}
	
	xmlTextWriterEndElement(this->printer);
	xmlTextWriterEndElement(this->printer);
}

void UIState::SetAttribute(const char* attrs, const char* attr_class, const char* attr_text, const char* attr_vals)
{
	xmlTextWriterStartElement(  this->printer, BAD_CAST "attribute");
	
	char** attr_pairs;
	
	macParseDefns(NULL, attrs, &attr_pairs);
	
	for ( ; attr_pairs && attr_pairs[0]; attr_pairs += 2)
	{
		xmlTextWriterWriteAttribute(this->printer, BAD_CAST attr_pairs[0], BAD_CAST attr_pairs[1]);
	}
	
	xmlTextWriterStartElement(this->printer, BAD_CAST attr_class);
	
	if (attr_text)
	{
		std::string check(attr_text);
		
		if (not check.empty())
		{
			xmlTextWriterWriteString(this->printer, BAD_CAST attr_text);
		}
	}
	
	char** value_pairs;
	
	if (attr_vals)
	{
		macParseDefns(NULL, attr_vals, &value_pairs);
		
		for ( ; value_pairs && value_pairs[0]; value_pairs += 2)
		{
			xmlTextWriterStartElement(this->printer, BAD_CAST value_pairs[0]);
			xmlTextWriterWriteString( this->printer, BAD_CAST value_pairs[1]);
			xmlTextWriterEndElement(  this->printer);
		}
	}
	
	xmlTextWriterEndElement(this->printer);
	xmlTextWriterEndElement(this->printer);
}


void UIState::SetLayout(const char* layout_class, const char* layout_name)
{
	xmlTextWriterStartElement(  this->printer, BAD_CAST "layout");
	xmlTextWriterWriteAttribute(this->printer, BAD_CAST "class", BAD_CAST layout_class);
	xmlTextWriterWriteAttribute(this->printer, BAD_CAST "name",  BAD_CAST layout_name);
	
	this->active_layouts.push_front(this->depth);
}

UIState::UIState(const char* width, const char* height, const char* title)
{
	this->depth = 0;
	this->active_layouts.push_front(-1);
	
	this->buffer = xmlBufferCreate();
	this->printer = xmlNewTextWriterMemory(this->buffer, 0);
	
	xmlTextWriterStartDocument(this->printer, NULL, "UTF-8", NULL);
	xmlTextWriterSetIndent(this->printer, 1);
	xmlTextWriterSetIndentString(this->printer, BAD_CAST "\t");
	
	xmlTextWriterStartElement(  this->printer, BAD_CAST "ui");
	xmlTextWriterWriteAttribute(this->printer, BAD_CAST "version", BAD_CAST "4.0");
	
	xmlTextWriterStartElement(this->printer, BAD_CAST "class");
	xmlTextWriterWriteString( this->printer, BAD_CAST "MainWindow");
	xmlTextWriterEndElement(  this->printer);
	
	this->StartObject("widget", "class=QMainWindow, name=MainWindow");
	
	std::stringstream values;
	values << "x=0, y=0, width=" << width << ", height=" << height;
	
	this->SetProperty("name=geometry", "rect", NULL, values.str().c_str());
	this->SetProperty("name=windowTitle", "string", title, NULL);
	this->StartObject("widget", "class=QWidget, name=centralwidget");
}

void UIState::Close(const char* output_location)
{	
	xmlTextWriterEndElement(this->printer);
	xmlTextWriterEndElement(this->printer);
	
	xmlTextWriterStartElement(this->printer, BAD_CAST "resources");
	xmlTextWriterEndElement(  this->printer);
	
	xmlTextWriterStartElement(this->printer, BAD_CAST "connections");
	xmlTextWriterEndElement(  this->printer);
	
	xmlTextWriterEndElement( this->printer);
	xmlTextWriterEndDocument(this->printer);
	
	std::ofstream file;
	file.open(output_location, std::ofstream::out | std::ofstream::trunc);
	
	if (file.is_open())
	{
		file << xmlBufferContent(this->buffer);
	}
	
	file.close();
	
	xmlFreeTextWriter(this->printer);
	xmlBufferFree(this->buffer);
}
