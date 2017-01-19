#ifndef INC_DEVXML_H
#define INC_DEVXML_H

#include <string>
#include <deque>

#include "tree.h"
#include "xmlwriter.h"


class UIState
{
	public:
		UIState(const char* width, const char* height, const char* title);
		
		void StartObject(const char* widget_class, const char* name);
		void EndObject();
		
		void SetProperty(const char* attrs, const char* prop_class, const char* prop_text, const char* prop_vals);
		void SetAttribute(const char* attrs, const char* attr_class, const char* attr_text, const char* attr_vals);
		void SetLayout(const char* layout_class, const char* layout_name);
		
		void Close(const char* output_location);
		
	private:
		xmlBufferPtr     buffer;
		xmlTextWriterPtr printer;
		
		int depth;
		
		std::deque<int> active_layouts;
};


#endif
