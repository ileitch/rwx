/*
 * wxApp.cpp
 *
 *  Created on: 07.02.2012
 *      Author: hanmac
 */

#include "wxApp.hpp"

#define _self wrap<wxApp*>(self)
VALUE rb_cWXApp;

bool ruby_app_inited;

RubyApp::RubyApp(VALUE klass)
{
	mRuby = Data_Wrap_Struct(klass, 0, 0, this);
}
bool RubyApp::OnInit()
{
  wxApp::OnInit();
  ruby_app_inited = true;
  return RTEST(rb_funcall(mRuby, rb_intern("on_init"), 0));
}


int RubyApp::OnRun()
{
  wxApp::OnRun();
  rb_funcall(mRuby, rb_intern("on_run"), 0);
  return 0;
}


int RubyApp::OnExit()
{
  wxApp::OnExit();
  ruby_app_inited = false;
  rb_funcall(mRuby, rb_intern("on_exit"), 0);
  return 0;
}


namespace RubyWX {
namespace App {

macro_attr(AppName,wxString)
macro_attr(AppDisplayName,wxString)
macro_attr(ClassName,wxString)
macro_attr(VendorName,wxString)
macro_attr(VendorDisplayName,wxString)


VALUE _alloc(VALUE self)
{
	return wrap(new RubyApp(self));
}


VALUE _main_loop(VALUE self)
{
	wxChar* argv[] = { NULL};
	int argc = 0;
	return INT2NUM(wxEntry(argc, argv));
}

VALUE _on_init(VALUE self)
{
	return Qtrue; //For wxWidgets to continue
}

VALUE _on_run(VALUE self)
{
	return Qnil;
}

VALUE _on_exit(VALUE self)
{
	return Qnil;
}
}
}

void Init_WXApp(VALUE rb_mWX)
{
	using namespace RubyWX::App;
	rb_cWXApp = rb_define_class_under(rb_mWX,"App",rb_cObject);
	rb_define_alloc_func(rb_cWXApp,_alloc);

	rb_define_attr_method(rb_cWXApp,"appName",_getAppName,_setAppName);
	rb_define_attr_method(rb_cWXApp,"appDisplayName",_getAppDisplayName,_setAppDisplayName);

	rb_define_attr_method(rb_cWXApp,"vendorName",_getVendorName,_setVendorName);
	rb_define_attr_method(rb_cWXApp,"vendorDisplayName",_getVendorDisplayName,_setVendorDisplayName);


	rb_define_method(rb_cWXApp,"main_loop",RUBY_METHOD_FUNC(_main_loop),0);

	rb_define_method(rb_cWXApp,"on_init",RUBY_METHOD_FUNC(_on_init),0);
	rb_define_method(rb_cWXApp,"on_run",RUBY_METHOD_FUNC(_on_run),0);
	rb_define_method(rb_cWXApp,"on_exit",RUBY_METHOD_FUNC(_on_exit),0);
}
