/*
 * wxMenu.hpp
 *
 *  Created on: 17.02.2012
 *      Author: hanmac
 */

#ifndef WXMENU_HPP_
#define WXMENU_HPP_


#include "main.hpp"

extern VALUE rb_cWXMenu;
void Init_WXMenu(VALUE rb_mWX);


template <>
inline VALUE wrap< wxMenu >(wxMenu *menu )
{
	if(menu)
		return Data_Wrap_Struct(rb_cWXMenu, NULL, free, menu);
	return Qnil;
}

template <>
inline wxMenu* wrap< wxMenu* >(const VALUE &vmenu)
{
	return unwrapPtr<wxMenu>(vmenu, rb_cWXMenu);
}



#endif /* WXMENU_HPP_ */