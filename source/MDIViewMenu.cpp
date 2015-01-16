/***********************************************************************/
/*                                NOTICE                               */
/*                                ------                               */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/*                    This software was developed by                   */
/*                            3rd-Evolution                            */
/*                                                                     */
/* Any reproduction of this software in whole or in part must contain  */
/*                   this notice in its entirety.                      */
/*                                                                     */
/* 3rd-Evolution  is  providing this  software "as is"  and  makes no  */
/* warranty, express or  implied,  as  to  the  accuracy,  capability, */
/* efficiency,  merchantability,  or  functioning  of  this  software  */
/* and/or documentation. In no event will 3rd-evolution be liable for  */
/* any  general,  consequential,   indirect,  incidental,   exemplary, */
/* or special damages, even  if 3rd-evolution has been advised of the  */
/* possibility  of such damages,  irrespective  of  the cause of such  */
/* damages.  For short: 3rd-evolution is impeccable and so any damage  */
/* is your fault.                                                      */
/*                                                                     */
/* Permission  to use, copy, modify, and distribute this software for  */
/* any purpose and without  fee is hereby  granted. For  any comments, */
/* bugs or thanks, please email us: info@3rd-evolution.de              */
/*                                                                     */
/***********************************************************************/

#include "pch.h"
#include "icons.h"
#include "GlyphMenuItem.h"
#include "MDIClientView.h"
#include "MDIViewMenu.h"

using namespace std;

//: Constructor
//!param:  client    - MDI client view.
//!param:  name      - Name of this menu.
//!param:  layout    - BeOS menu layout value (e.g. B_ITEMS_IN_COLUMN).
CMDIViewMenu::CMDIViewMenu(CMDIClientView *client, const char *name, menu_layout layout) :
	BMenu(name, layout)
{
	clientView = client;
}

//: Updates the list of views.
// This function updates the view list which is appended to the menu. You should call this method
// in your implementation of BWindow::MenusBeginning.
void CMDIViewMenu::UpdateViewItems()
{
	RemoveViewItems();
	AddViewItems();
}

void CMDIViewMenu::AddViewItems()
{
	typedef vector< pair<string, CMDIView *> > t_item_vector; 
	t_item_vector item_vector;
	
	CMDIView *currentView=NULL;
	
	while((currentView = clientView->GetNextMDIView(currentView)) != NULL) {
		item_vector.push_back(make_pair(string(currentView->Title()), currentView));
	}
		
	sort(item_vector.begin(), item_vector.end());

	if(item_vector.size() > 0)
		AddSeparatorItem();
	
	for(t_item_vector::iterator i=item_vector.begin() ; i!=item_vector.end() ; i++) {
		BMessage *message = new BMessage(MDI_MSG_ACTIVATE_VIEW);
		message->AddPointer(MDI_MSG_DATA_VIEW, (*i).second);

		BBitmap *glyph = new BBitmap(BRect(0, 0, icon_width-1, icon_height-1), B_RGB32);

		CMDIView *view = (*i).second;
		
		if(view->Active())
			glyph->SetBits(icon_active_view, icon_active_view_size, 0, B_RGB32);
		else if(view->IsHidden())
			glyph->SetBits(icon_hidden_view, icon_hidden_view_size, 0, B_RGB32);
		else
			glyph->SetBits(icon_visible_view, icon_visible_view_size, 0, B_RGB32);

		BMenuItem *menuItem = new CGlyphMenuItem((*i).first.c_str(), glyph, false, message, 0, 0, BPoint(-15, 0));
		menuItem->SetTarget(clientView);

		AddItem(menuItem);
	}
}

//: Removes the list of MDI views.
// Removes all items between the last separator and the end of the menu.
void CMDIViewMenu::RemoveViewItems()
{
	for(int32 i=CountItems()-1 ; i>=0 ; i--) {
		BSeparatorItem *separator = dynamic_cast<BSeparatorItem *>(ItemAt(i));
		
		if(separator) {
			// The current item is a separator.
			// Delete separator and all items below.
			
			int32 numItems = CountItems() - i;
			
			for(int32 k=0 ; k<numItems ; k++) {
				delete RemoveItem(i);
			}
		}
	}
}
