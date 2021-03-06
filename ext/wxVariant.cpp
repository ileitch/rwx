/*
 * wxVariant.cpp
 *
 *  Created on: 08.05.2012
 *      Author: hanmac
 */
#include "wxVariant.hpp"
#include "wxDataView.hpp"
#include "wxFont.hpp"
template <>
VALUE wrap< wxVariant >(const wxVariant &var)
{
	wxString type = var.GetType();
	if(type == "null")
		return Qnil;
	if(type == "bool")
		return wrap(var.GetBool());
	else if(type == "string")
		return wrap(var.GetString());

	else if(type == "arrstring")
		return wrap(var.GetArrayString());
	else if(type == "long")
		return LONG2NUM(var.GetLong());
	else if(type == "wxFont")
		return wrap((wxFont)var);
	else
		std::cout << type << std::endl;
	return Qnil;
}

wxVariant unwrapVariant(VALUE obj,const wxString &type)
{
	wxVariant result;
	if(type == "string")
		result = wrap<wxString>(obj);
	else if(type == "arrstring")
		result = wrap<wxArrayString>(obj);
	else if(type == "bool")
		result = wrap<bool>(obj);
	else if(type == "long")
		result = NUM2LONG(obj);
	else if(type == "wxFont")
		result = wxVariant(wrap<wxFont>(obj));
#if wxUSE_DATAVIEWCTRL
	else if(type == "wxDataViewIconText")
	{
		result = wxVariant(wxDataViewIconText(wxEmptyString,wrap<wxIcon>(obj)));
	}
#endif
	else
		std::cout << type << std::endl;
	return result;
}



