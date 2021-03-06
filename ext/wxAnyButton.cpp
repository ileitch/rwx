/*
 * wxAnyButton.cpp
 *
 *  Created on: 13.02.2012
 *      Author: hanmac
 */


#include "wxAnyButton.hpp"

VALUE rb_cWXAnyButton;

#define _self wrap<wxAnyButton*>(self)

namespace RubyWX {
namespace AnyButton {

macro_attr(LabelText,wxString)
macro_attr(BitmapLabel,wxBitmap)
macro_attr(BitmapPressed,wxBitmap)
macro_attr(BitmapDisabled,wxBitmap)
macro_attr(BitmapCurrent,wxBitmap)
macro_attr(BitmapFocus,wxBitmap)

macro_attr(BitmapSelected,wxBitmap)
macro_attr(BitmapHover,wxBitmap)

macro_attr(BitmapMargins,wxSize)

singlereturn(GetBitmap)

VALUE _alloc(VALUE self)
{
	return wrap(new wxAnyButton,self);
}

}
}

void Init_WXAnyButton(VALUE rb_mWX)
{
	using namespace RubyWX::AnyButton;
	rb_cWXAnyButton = rb_define_class_under(rb_mWX,"AnyButton",rb_cWXControl);
	rb_define_alloc_func(rb_cWXAnyButton,_alloc);

	rb_define_attr_method(rb_cWXAnyButton,"label_text",_getLabelText,_setLabelText);

	rb_define_attr_method(rb_cWXAnyButton,"bitmap_label",_getBitmapLabel,_setBitmapLabel);
	rb_define_attr_method(rb_cWXAnyButton,"bitmap_pressed",_getBitmapPressed,_setBitmapPressed);
	rb_define_attr_method(rb_cWXAnyButton,"bitmap_disabled",_getBitmapDisabled,_setBitmapDisabled);
	rb_define_attr_method(rb_cWXAnyButton,"bitmap_current",_getBitmapCurrent,_setBitmapCurrent);
	rb_define_attr_method(rb_cWXAnyButton,"bitmap_focus",_getBitmapFocus,_setBitmapFocus);
	rb_define_attr_method(rb_cWXAnyButton,"bitmap_selected",_getBitmapSelected,_setBitmapSelected);
	rb_define_attr_method(rb_cWXAnyButton,"bitmap_hover",_getBitmapHover,_setBitmapHover);

}


