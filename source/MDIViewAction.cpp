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
#include "MDIViewAction.h"
#include "MDIView.h"
#include "MDIClientView.h"

// ==== CMDIMouseAction ====

const float CMDIMouseAction::dblClickWidth		= 2;
const float CMDIMouseAction::dblClickHeight		= 2;

//: Constructor
CMDIMouseAction::CMDIMouseAction(BView *mdiView) :
	CViewMouseAction(mdiView)
{
	mouseAction = MDI_MA_NONE;
}

//: Returns the MDI client view.
// Returns the MDI client view which the target view is attached to.
CMDIClientView *CMDIMouseAction::ClientView()
{
	return dynamic_cast<CMDIClientView *>(Controled()->Parent());
}

//: Returns the target view
// Returns the target view casted to CMDIView.
CMDIView *CMDIMouseAction::MDIView()
{
	return dynamic_cast<CMDIView *>(Controled());
}

//: Moves the controled view.
// Overwrites the default implementation to call CMDIClientView::MoveViewTo instead of
// BView::MoveTo.
void CMDIMouseAction::MoveControledTo(float x, float y)
{
	CMDIView *mdiView = MDIView();
	CMDIClientView *client = ClientView();

	client->MoveViewTo(mdiView, x, y);
}

//: Moves the controled view.
// Overwrites the default implementation to call CMDIClientView::ResizeViewTo instead of
// BView::ResizeTo.
void CMDIMouseAction::ResizeControledTo(float width, float height)
{
	ClientView()->ResizeViewTo(MDIView(), width, height);
}

//: Handles a mouse down event.
// <P>Determines the 'mouseAction' from the 'hitTestArea'. It respects the restrictions set
// for the MDI view. If the MDI view has set the MDI_NOT_RESIZABLE flag, no resize
// operation is started etc.</P>
//!param: point - Current mouse position in screen coordinates.
//!param: hitTestArea - Value returned by IHitTest::HitTest. The remarks section 
//!param:               contains a list possible values.
//!param: buttons - Combination of B_PRIMARY_MOUSE_BUTTON, B_SECONDARY_MOUSE_BUTTON and B_TERTIARY_MOUSE_BUTTON.
//!param: clicks - Number of mouse clicks. 1 for single click; 2 for double click etc.
// Possible values for 'hitTestArea':
// <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="2">
// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_NC_NONE</TD>
// <TD CLASS="descr" BGCOLOR="#CCCCCC">Invalid point.</TD></TR>
// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_NC_SIZE_EDGE</TD>
// <TD CLASS="descr" BGCOLOR="#CCCCCC">Mouse is over the resize edge. Starts a resize operation.</TD></TR>
// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_NC_BORDER</TD>
// <TD CLASS="descr" BGCOLOR="#CCCCCC">Mouse is over the border. A double click minimizes the view, 
// a single click starts a move operation.</TD></TR>
// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_NC_CLOSE_BOX</TD>
// <TD CLASS="descr" BGCOLOR="#CCCCCC">Mouse is over the close box. 
// This value is ignored by this class.</TD></TR>
// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_NC_MAXIMIZE_BOX</TD>
// <TD CLASS="descr" BGCOLOR="#CCCCCC">Mouse is over the maximize box. Ignored.</TD></TR>
// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_NC_TITLE_TAB</TD>
// <TD CLASS="descr" BGCOLOR="#CCCCCC">Mouse is over the title tab. This class handles this
// value like MDI_NC_BORDER.</TD></TR>
// </TABLE>
void CMDIMouseAction::HandleMouseDown(BPoint point, int32 hitTestArea, int32 buttons, int32 clicks)
{
	CMDIView *mdiView = MDIView();
	CMDIClientView *client = ClientView();
	
	int32 mdiFlags = mdiView->MDIFlags();

	if(buttons == B_PRIMARY_MOUSE_BUTTON) {
		if(clicks >= 2) {
			switch(hitTestArea) {
				case MDI_NC_TITLE_TAB:
				case MDI_NC_BORDER:
					if(!(mdiView->MDIFlags() & MDI_NOT_MINIMIZABLE)) {
						client->MinimizeView(mdiView);
					}
					break;
			}
		} else {
			switch(hitTestArea) {
				case MDI_NC_SIZE_EDGE:
					if(!(mdiFlags & MDI_NOT_RESIZABLE)) {
						// start size, if view is resizable
						mouseAction = MDI_MA_SIZE;
		
						client->BeginViewResize(mdiView);
					}
					
					break;
				case MDI_NC_TITLE_TAB:
				case MDI_NC_BORDER:
					if(!(mdiFlags & MDI_NOT_MOVABLE)) {
						// start move if view is movable
						mouseAction = MDI_MA_MOVE;
						
						client->BeginViewMove(mdiView);
					}
			
					break;
				default:
					// nothing to do
					break;
			}
		}
	} else if(buttons == B_SECONDARY_MOUSE_BUTTON) {
		switch(hitTestArea) {
			case MDI_NC_TITLE_TAB:
			case MDI_NC_BORDER:
				client->SendToBack(mdiView);
				break;
			default:
				// nothing.
				break;
		}
	}
}

//: Handles a mouse move event.
// The action taken depends on the current 'mouseAction'. If the target is moved
// it calls MoveTargetBy, if the target is resized it calls ResizeTargetTo.
// The resize operation respects the size limits set for the MDI view.
void CMDIMouseAction::HandleMouseMove(BPoint point, BPoint screenPoint, float dx, float dy)
{
	CMDIView *mdiView = MDIView();

	switch(mouseAction) {
		case MDI_MA_SIZE:
			{
				float newWidth  = mdiView->Bounds().Width() + dx;
				float newHeight = mdiView->Bounds().Height() + dy;
				
				BPoint viewTopLeft = B_ORIGIN;
				Controled()->ConvertToScreen(&viewTopLeft);
				
				bool restricted_x = false;
				bool restricted_y = false;
			
				float minWidth, maxWidth, minHeight, maxHeight;

				mdiView->GetSizeLimits(&minWidth, &maxWidth, &minHeight, &maxHeight);
				
				if(newWidth < minWidth)		{ newWidth = minWidth; restricted_x = true; }
				if(newWidth > maxWidth)		{ newWidth = maxWidth; restricted_x = true; }
				
				if(newHeight < minHeight)	{ newHeight = minHeight; restricted_y = true; }
				if(newHeight > maxHeight)	{ newHeight = maxHeight; restricted_y = true; }

				if(restricted_x && restricted_y) {
					// don't change start point
				} else if(restricted_x) {
					startPoint.x = viewTopLeft.x + newWidth;
					startPoint.y = screenPoint.y;
				} else if(restricted_y) {
					startPoint.x = screenPoint.x;
					startPoint.y = viewTopLeft.y + newHeight;
				} else {
					startPoint = screenPoint;
				}
			
				// Resize view
				ResizeControledTo(newWidth, newHeight);
			}
			break;
		case MDI_MA_MOVE:
			// Move view
			MoveControledBy(dx, dy);

			startPoint = screenPoint;
			
			break;
		default:
			// to quiet compiler
			break;
	}
}

//: Handles a mouse up event.
// This implementation simply calls CMDIClientView::EndViewMove, if the target was moved
// or CMDIClientView::EndViewResize if the target was resized.
void CMDIMouseAction::HandleMouseUp(BPoint point)
{
	CMDIClientView *client = ClientView();
	CMDIView *mdiView = MDIView();

	switch(mouseAction) {
		case MDI_MA_MOVE:
			client->EndViewMove(mdiView);
			break;
		case MDI_MA_SIZE:
			client->EndViewResize(mdiView);
			break;
		default:
			break;
	}
}

//: Mouse position independent event handling.
// This method is called from CMDIView::MouseDown. 
// It calls CMDIView::HitTest and passes the returned value to HandleMouseDown.
void CMDIMouseAction::MouseDown(BPoint point) 
{
	BPoint screenPoint = Controled()->ConvertToScreen(point);

	CMDIClientView *client = ClientView();
	CMDIView *mdiView = MDIView();

	BMessage *message = Controled()->Window()->CurrentMessage();

	int32 clicks  = message->FindInt32("clicks");
	int32 buttons = message->FindInt32("buttons");
	
	client->ActivateView(mdiView);

	int32 hitTestArea = HitTest(point);

	if(clicks >= 2) {
		// BeOS reports a double click, even if the mouse was
		// moved between the clicks. Test if the mouse is in
		// a 2x2 pixel rectangle around the first mouse click.
		if(dblClickRect.Contains(screenPoint)) {
			// Accepted double click
		} else  {
			// Mouse was moved between clicks. 
			// This is a single click.
			clicks = 1;
		}
	}

	HandleMouseDown(point, hitTestArea, buttons, clicks);
	
	dblClickRect = BRect(screenPoint.x-dblClickWidth/2, screenPoint.y-dblClickHeight/2,
						 screenPoint.x+dblClickWidth/2, screenPoint.y+dblClickHeight/2);
	
	if(mouseAction != MDI_MA_NONE) {
		client->EnableMouseRedirect(false);
		
		startPoint = screenPoint;

		Controled()->SetMouseEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	}
}

//: Mouse action independet event handling.
// This method is called from CMDIView::MouseMoved. 
// It calculates the delta movement of the mouse and calls HandleMouseMove.
void CMDIMouseAction::MouseMoved(BPoint point, uint32 transit) 
{
	if(mouseAction != MDI_MA_NONE) {
		BPoint windowPoint;
		float dx, dy;
	
		BPoint location/*(ignored)*/;
		uint32 buttons;
	
		// From time-to-time some B_MOUSE_UP messages get lost.
		// Therefore I test, if the mouse button is still down.
		// It that isn't the case, I cancel any mouse operation.
		Controled()->GetMouse(&location, &buttons, false);
		
		if(buttons != 0) {
			// some button pressed
			
			BWindow  *window  = Controled()->Window();
			BMessage *message = window->CurrentMessage();
		
			// I'm using the window point here, because when the view is moving
			// the position in VIEW coordinates remains constant all the time.
			message->FindPoint("where", &windowPoint);
			window->ConvertToScreen(&windowPoint);
				
			dx = windowPoint.x - startPoint.x;
			dy = windowPoint.y - startPoint.y;
		
			HandleMouseMove(point, windowPoint, dx, dy);
		} else {
			// Cancel any outstanding mouse action.
			mouseAction = MDI_MA_NONE;
		}
	}
}

//: Mouse action independet event handling.
// This method is called from CMDIView::MouseUp. It calls HandleMouseUp and sets
// 'mouseAction' to MDI_MA_NONE afterwards.
void CMDIMouseAction::MouseUp(BPoint point) 
{
	HandleMouseUp(point);

	mouseAction = MDI_MA_NONE;
	ClientView()->EnableMouseRedirect(true);
}

// ==== CMDITitleMouseAction ====

//: Constructor
CMDITitleMouseAction::CMDITitleMouseAction(BView *titleView) :
	CMDIMouseAction(titleView)
{
}

//: Handles a mouse down event.
// If the mouse is over the close box, the close box is pressed. But the view is
// only closed if the mouse is still over the close box, if the mouse button is going up.
// If the mouse button is moved outside the close box rectangle while the mouse
// button is pressed, the close box toggles its state. The same is true for the
// maximize button.
void CMDITitleMouseAction::HandleMouseDown(BPoint point, int32 hitTestArea, int32 button, int32 clicks)
{
	switch(hitTestArea) {
		case MDI_NC_CLOSE_BOX:
			mouseAction	= MDI_MA_CLOSE_BOX_PRESSED;
			TitleView()->SetCloseButtonPressed(true);
			break;
		case MDI_NC_MAXIMIZE_BOX:
			mouseAction	= MDI_MA_MAXIMIZE_BOX_PRESSED;
			TitleView()->SetMaximizeButtonPressed(true);
			break;
		default:
			CMDIMouseAction::HandleMouseDown(point, hitTestArea, button, clicks);
			break;
	}
}

//: Handles a mouse move event.
// See HandleMouseDown for more information.
void CMDITitleMouseAction::HandleMouseMove(BPoint point, BPoint screenPoint, float dx, float dy)
{
	switch(mouseAction) {
		case MDI_MA_CLOSE_BOX_PRESSED:
			{
				CMDITitleView *titleView = TitleView();
			
				if(HitTest(point) != MDI_NC_CLOSE_BOX) {
					titleView->SetCloseButtonPressed(false);
				} else {
					titleView->SetCloseButtonPressed(true);
				}
			}
			
			break;
		case MDI_MA_MAXIMIZE_BOX_PRESSED:
			{
				CMDITitleView *titleView = TitleView();
			
				if(HitTest(point) != MDI_NC_MAXIMIZE_BOX) {
					titleView->SetMaximizeButtonPressed(false);
				} else {
					titleView->SetMaximizeButtonPressed(true);
				}
			}
			
			break;
		default:
			CMDIMouseAction::HandleMouseMove(point, screenPoint, dx, dy);
			break;
	}
}

//: Handles a mouse up event.
// This method closes the target view and its attached MDI view, if the mouse is over
// the close box.
// If the mouse is over the maximize button, the attached MDI view is maximized.
void CMDITitleMouseAction::MouseUp(BPoint point)
{
	CMDIClientView *client = ClientView();
	CMDIView *mdiView = MDIView();
	CMDITitleView *titleView = TitleView();

	client->EnableMouseRedirect(true);	
	
	switch(mouseAction) {
		case MDI_MA_CLOSE_BOX_PRESSED:
			{
				if(HitTest(point) == MDI_NC_CLOSE_BOX) {
	
					if(mdiView->CanClose()) {				
						// Remove target and title tab fom view hierachy.
						client->RemoveMDIView(mdiView);
				
						// delete views	
						delete Controled();
						delete mdiView;
					}
					
					return;
				}
				
				titleView->SetCloseButtonPressed(false);
			}			
			break;
		case MDI_MA_MAXIMIZE_BOX_PRESSED:
			{
				if(HitTest(point) == MDI_NC_MAXIMIZE_BOX) {
					client->MaximizeView(mdiView);
				}
				
				titleView->SetMaximizeButtonPressed(false);
			}			
			break;
		default:
			CMDIMouseAction::MouseUp(point);
			break;
	}		
	
	mouseAction = MDI_MA_NONE;
}

//: Moves the controled view.
// Overwrites the implementation of the base class. It moves the title view (target) as well as
// the attached MDI view.
void CMDITitleMouseAction::MoveControledTo(float x, float y)
{
	CMDIView *mdiView = MDIView();
	CTitleView *titleView = TitleView();
	CMDIClientView *client = ClientView();

	// MoveViewTo moves title view AND MDI view!
	client->MoveViewTo(mdiView, x, y+titleView->Bounds().Height());
}

//: Returns the target view.
// Returns the target casted to CMDITitleView.
CMDITitleView *CMDITitleMouseAction::TitleView()
{
	return dynamic_cast<CMDITitleView *>(Controled());
}
	
//: Returns the MDI view the target is attached to.
// The target view is a CMDITitleView. This method returns the MDI view the
// title view is attached to.
CMDIView *CMDITitleMouseAction::MDIView()
{
	return dynamic_cast<CMDIView *>(TitleView()->Target());
}
