/*
 * rwx.cpp
 *
 *  Created on: 07.02.2012
 *      Author: hanmac
 */

#include "wxError.hpp"

#include "wxSize.hpp"
#include "wxRect.hpp"
#include "wxPoint.hpp"

#include "wxColor.hpp"
#include "wxFont.hpp"
#include "wxPen.hpp"
#include "wxBrush.hpp"

#include "wxCursor.hpp"

#include "wxImage.hpp"
#include "wxBitmap.hpp"

#include "wxEvent.hpp"
#include "wxScrollEvent.hpp"
#include "wxKeyEvent.hpp"
#include "wxMouseEvent.hpp"
#include "wxEvtHandler.hpp"

#include "wxMenu.hpp"
#include "wxMenuItem.hpp"

#include "wxToolBarTool.hpp"

#include "wxApp.hpp"
#include "wxWindow.hpp"

#include "wxMenuBar.hpp"
#include "wxPanel.hpp"
#include "wxControl.hpp"
#include "wxToplevel.hpp"


#include "wxFrame.hpp"
#include "wxDialog.hpp"

#include "wxColorDialog.hpp"
#include "wxFontDialog.hpp"

#include "wxFileDialog.hpp"
#include "wxDirDialog.hpp"
#include "wxProgressDialog.hpp"

#include "wxWizard.hpp"


#include "wxAui.hpp"

#include "wxAnyButton.hpp"
#include "wxButton.hpp"
#include "wxBitmapButton.hpp"

#include "wxToolBarBase.hpp"
#include "wxToolBar.hpp"

#include "wxStatusBar.hpp"

#include "wxGauge.hpp"


#include "wxCheckBox.hpp"
#include "wxRadioButton.hpp"

#include "wxStaticBitmap.hpp"
#include "wxStaticBitmapGeneric.hpp"

#include "wxStaticLine.hpp"

#include "wxStaticText.hpp"
#include "wxStaticBox.hpp"

#include "wxItemContainer.hpp"

#include "wxChoice.hpp"

#include "wxSlider.hpp"

#include "wxSpinButton.hpp"
#include "wxSpinCtrl.hpp"

#include "wxTextCtrl.hpp"
#include "wxSearchCtrl.hpp"


#include "wxTimePicker.hpp"
#include "wxFontPicker.hpp"
#include "wxColorPicker.hpp"
#include "wxFilePicker.hpp"
#include "wxDirPicker.hpp"

#include "wxTreeCtrl.hpp"

#include "wxFileCtrlBase.hpp"
#include "wxFileCtrl.hpp"
#include "wxFileCtrlGeneric.hpp"

#include "wxCalendarCtrlBase.hpp"
#include "wxCalendarCtrl.hpp"
#include "wxCalendarCtrlGeneric.hpp"


#include "wxDataView.hpp"
#include "wxDataViewList.hpp"

#include "wxHyperLink.hpp"

#include "wxBookCtrl.hpp"

#include "wxSTC.hpp"


#include "wxAboutDlg.hpp"
#include "wxStartUpTip.hpp"

#include "wxFileHistory.hpp"
#include "wxConfig.hpp"

#include "wxDC.hpp"
#include "wxSizer.hpp"
#include "wxSizerItem.hpp"

#include "wxGridTable.hpp"
#include "wxGridCellRenderer.hpp"
#include "wxGridCellAttr.hpp"

#include "wxPropertyGrid.hpp"
#include "wxPropertyGridManager.hpp"
#include "wxPropertyGridInterface.hpp"


#include "wxProperty.hpp"
#include "wxFileProperty.hpp"
#include "wxFontProperty.hpp"
#include "wxStringProperty.hpp"
#include "wxArrayStringProperty.hpp"
#include "wxCategoryProperty.hpp"


VALUE rb_mWX;

void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE))
{
	rb_define_method(klass,name.c_str(),RUBY_METHOD_FUNC(get),0);
	rb_define_method(klass,(name + "=").c_str(),RUBY_METHOD_FUNC(set),1);
}



extern "C" void Init_rwx()
{
	//wxInitialize();


	rb_mWX = rb_define_module("WX");

	Init_WXError(rb_mWX);

	Init_WXColor(rb_mWX);
	Init_WXFont(rb_mWX);
	Init_WXPen(rb_mWX);
	Init_WXBrush(rb_mWX);

	Init_WXImage(rb_mWX);
	Init_WXBitmap(rb_mWX);

	Init_WXCursor(rb_mWX);

	Init_WXSize(rb_mWX);
	Init_WXRect(rb_mWX);
	Init_WXPoint(rb_mWX);

	Init_WXEvent(rb_mWX);
	Init_WXScrollEvent(rb_mWX);

	Init_WXKeyEvent(rb_mWX);
	Init_WXMouseEvent(rb_mWX);

	Init_WXEvtHandler(rb_mWX);
	Init_WXTimer(rb_mWX);
	Init_WXTaskBar(rb_mWX);


	Init_WXMenu(rb_mWX);
		Init_WXMenuItem(rb_mWX);

	Init_WXApp(rb_mWX);


	Init_WXWindow(rb_mWX);
	Init_WXPanel(rb_mWX);

	Init_WXTopLevel(rb_mWX);
	Init_WXFrame(rb_mWX);

	Init_WXDialog(rb_mWX);
	Init_WXColorDialog(rb_mWX);
	Init_WXFontDialog(rb_mWX);
	Init_WXFileDialog(rb_mWX);
	Init_WXDirDialog(rb_mWX);
	Init_WXProgressDialog(rb_mWX);
	Init_WXWizard(rb_mWX);
	Init_WXWizardPage(rb_mWX);

	Init_WXMenuBar(rb_mWX);

	Init_WXControl(rb_mWX);
	Init_WXToolBarBase(rb_mWX);
	Init_WXToolBar(rb_mWX);
	Init_WXToolBarTool(rb_mWX);

	Init_WXTimePicker(rb_mWX);
	Init_WXColorPicker(rb_mWX);
	Init_WXFontPicker(rb_mWX);
	Init_WXFilePicker(rb_mWX);

	Init_WXFileCtrlBase(rb_mWX);
	Init_WXFileCtrl(rb_mWX);
	Init_WXFileCtrlGeneric(rb_mWX);

	Init_WXCalendarCtrlBase(rb_mWX);
	Init_WXCalendarCtrl(rb_mWX);
	Init_WXCalendarCtrlGeneric(rb_mWX);

	Init_WXDataView(rb_mWX);
	Init_WXDataViewList(rb_mWX);

	Init_WXSlider(rb_mWX);
	Init_WXSpinButton(rb_mWX);
	Init_WXSpinCtrl(rb_mWX);

	Init_WXHyperLink(rb_mWX);

	Init_WXStaticBitmapBase(rb_mWX);
	Init_WXStaticBitmap(rb_mWX);
	Init_WXStaticBitmapGeneric(rb_mWX);

	Init_WXStaticLine(rb_mWX);
	Init_WXStaticText(rb_mWX);
	Init_WXStaticBox(rb_mWX);

	Init_WXItemContainer(rb_mWX);
	Init_WXChoice(rb_mWX);

	Init_WXAnyButton(rb_mWX);
	Init_WXButton(rb_mWX);
	Init_WXBitmapButton(rb_mWX);

	Init_WXCheckBox(rb_mWX);
	Init_WXRadioButton(rb_mWX);


	Init_WXTextCtrl(rb_mWX);

	Init_WXSearchCtrl(rb_mWX);

	Init_WXTreeCtrl(rb_mWX);
	Init_WXStatusBar(rb_mWX);

	Init_WXGauge(rb_mWX);

	Init_WXAboutDlg(rb_mWX);
	Init_ShowTip(rb_mWX);

	Init_WXFileHistory(rb_mWX);
	Init_WXConfig(rb_mWX);

	Init_WXDC(rb_mWX);

	Init_WXSizer(rb_mWX);
	Init_WXBoxSizer(rb_mWX);

	Init_WXSizerItem(rb_mWX);

	Init_WXAuiManager(rb_mWX);

	Init_WXBookCtrl(rb_mWX);
	Init_WXChoiceBookCtrl(rb_mWX);
	Init_WXToolBookCtrl(rb_mWX);
	Init_WXNoteBookCtrl(rb_mWX);
	Init_WXAuiNoteBookCtrl(rb_mWX);

	Init_WXAuiToolBar(rb_mWX);

	Init_WXSTC(rb_mWX);

	Init_WXGrid(rb_mWX);
	Init_WXGridTable(rb_mWX);
	Init_WXGridCellRenderer(rb_mWX);
	Init_WXGridCellAttr(rb_mWX);

	Init_WXProperty(rb_mWX);
	Init_WXFileProperty(rb_mWX);
	Init_WXFontProperty(rb_mWX);
	Init_WXStringProperty(rb_mWX);
	Init_WXArrayStringProperty(rb_mWX);
	Init_WXCategoryProperty(rb_mWX);


	Init_WXPropertyGridInterface(rb_mWX);
	Init_WXPropertyGrid(rb_mWX);
	Init_WXPropertyGridManager(rb_mWX);

//	for(klassholdertype::iterator it = klassholder.begin();
//			it != klassholder.end();++it)
//		std::cout << it->first << std::endl;

}
