/***********************************************************************/
/* MDIViewMenu.h                                                       */
/*                                                                     */
/* Contains the definition for the class CMDIViewMenu. This menu       */
/* displays all CMDIViews in a CMDIClientView.                         */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MDI_VIEW_MENU_H
#define MDI_VIEW_MENU_H

//! file=MDIViewMenu.h

class CMDIClientView;

//: Displays a list of MDI views.
// <P>This menu displays the MDI views of a CMDIClientView. They are added
// after the last static entry of the menu. To update the menu before it
// is displayed call UpdateViewItems in your implementation of
// BWindow::MenusBeginning.</P>
// <P>When the user selects a MDI view in the menu a MDI_MSG_ACTIVATE_VIEW
// message is sent to the CMDIClientView. The client view responds to
// that message by bringing the MDI view to front and activating it.</P>
class CMDIViewMenu : public BMenu
{
	public:
	CMDIViewMenu(CMDIClientView *client, const char *name, menu_layout layout=B_ITEMS_IN_COLUMN);

	void UpdateViewItems();

	protected:
	//: Adds a list of MDI views to this menu.
	// Adds a separator in front of the added items. That separator is used by RemoveViewItems to find 
	// the frist added item. 
	virtual void AddViewItems();
	virtual void RemoveViewItems();

	//: Pointer to the client view.
	CMDIClientView *clientView;
};

#endif // MDI_VIEW_MENU_H