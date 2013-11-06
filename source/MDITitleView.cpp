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
#include "Color.h"
#include "Decoration.h"
#include "MDIViewAction.h"
#include "MDITitleView.h"
#include "MDIClientView.h"

// ==== CMDITitleView ====

const float CMDITitleView::distFromCloseBox     = 18;
const float CMDITitleView::distFromMaximizeBox	= 15;
const float CMDITitleView::distFromRightBorder  = 4;
const float CMDITitleView::distFromLeftBorder	= 4;
const float CMDITitleView::distFromTopBorder	= 4;
const float CMDITitleView::distFromBottomBorder = 2;

//: Constructor
//!param: frame  - Position of this view inside its parent.
//!param:          You should calculate this position from the
//!param:          targetView. This view should be above the parent
//!param:          and left aligned. You can use GetPreferredSize
//!param:          to calculate the width and height of this view.
//!param: targetView - Pointer to the target view. That view is moved,
//!param:          if this view is moved, minimized if this view
//!param:          is double-clicked and so on. Must be derived from
//!param:          CMDIView.
CMDITitleView::CMDITitleView(BRect frame, CTitledView *targetView) :
	CTitleView(frame, targetView, B_FOLLOW_NONE, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE)
{
	active			= false;
	mouseAction     = new CMDITitleMouseAction(this);
	
	closeButton		= DecorationFactory()->CreateCloseButton(this);
	maximizeButton  = DecorationFactory()->CreateMaximizeButton(this);
}

CMDITitleView::~CMDITitleView()
{
	delete mouseAction;
	delete closeButton;
	delete maximizeButton;
}

//: BeOS hook function
// Draws a BeOS style title tab. This method class the two attached
// decorations to draw the maximize and close buttons.
void CMDITitleView::Draw(BRect updateRect)
{
	Window()->BeginViewTransaction();

	// --- Calc colors

	CColor background = BackgroundColor();

	CColor highlight(	MIN(background.red+80, 255),
					 	MIN(background.green+80, 255),
					 	MIN(background.blue+80, 255) );
					 	
	CColor darkShadow(	MAX(background.red-81, 0),
						MAX(background.green-81, 0),
						MAX(background.blue-81, 0)	);

	CColor textColor = Active() ? CColor::Black : CColor(80, 80, 80);

	// --- Fill background
	
	SetHighColor(background);
	FillRect(updateRect);

	// --- Draw borders

	BRect bounds = Bounds();
	float width  = bounds.Width();
	float height = bounds.Height();

	SetHighColor(CColor::BeShadow);
	MovePenTo(0, height);
	StrokeLine(BPoint(0, 0));
	StrokeLine(BPoint(width, 0));
	SetHighColor(CColor::BeDarkShadow);
	MovePenTo(width, 1);
	StrokeLine(BPoint(width, height));

	SetHighColor(highlight);
	MovePenTo(1, height);
	StrokeLine(BPoint(1, 1));
	StrokeLine(BPoint(width-1, 1));
	SetHighColor(darkShadow);
	MovePenTo(width-1, 2);
	StrokeLine(BPoint(width-1, height));

	// --- Draw close button
	
	if(DisplayCloseButton()) {
		closeButton->SetPosition(CloseButtonRect().LeftTop());
		closeButton->SetBackgroundColor(background);
		closeButton->Draw();
	}

	// --- Draw maximize button
	
	if(DisplayMaximizeButton()) {
		maximizeButton->SetPosition(MaximizeButtonRect().LeftTop());
		maximizeButton->SetBackgroundColor(background);
		maximizeButton->Draw();
	}
	
	// --- Draw title
	
	BFont titleFont;
	GetTitleFont(&titleFont);	

	const char *title = target->Title();
	char *truncatedTitle = new char [strlen(title)+3];
	
	float titleWidth;
	BPoint titlePos;

	GetTitleWidthAndPos(titleWidth, titlePos);

	titleFont.GetTruncatedStrings(&title, 1, B_TRUNCATE_END, titleWidth, &truncatedTitle);

	SetHighColor(textColor);
	SetLowColor(background);
	SetFont(&titleFont);
	DrawString(truncatedTitle, strlen(truncatedTitle), titlePos);
	
	delete [] truncatedTitle;
	
	Window()->EndViewTransaction();
}

//: Returns true, if the close button should be displayed.
// If the target MDI view has the MDI_NOT_CLOSABLE flag
// set no close button is displayed.
bool CMDITitleView::DisplayCloseButton()
{
	CMDIView *mdiTarget = dynamic_cast<CMDIView *>(target);

	return !(mdiTarget->MDIFlags() & MDI_NOT_CLOSABLE);	
}

//: Bounding rectangle of the close button.
BRect CMDITitleView::CloseButtonRect()
{
	if(DisplayCloseButton())
		return BRect(distFromLeftBorder, distFromTopBorder,
						distFromLeftBorder+closeButton->Width(), distFromTopBorder+closeButton->Height());
	else
		return BRect(-1, -1, -1, -1);
}

//: Bounding rectangle of the maximize button.
bool CMDITitleView::DisplayMaximizeButton()
{
	CMDIView *mdiTarget = dynamic_cast<CMDIView *>(target);

	return !(mdiTarget->MDIFlags() & MDI_NOT_MAXIMIZABLE);	
}

//: Returns true, if the maximize button should be displayed.
// If the target MDI view has the MDI_NOT_MAXIMIZABLE flag
// set no maximize button is displayed.
BRect CMDITitleView::MaximizeButtonRect()
{
	if(DisplayMaximizeButton()) {
		float width = Bounds().Width();
	
		return BRect(width-distFromRightBorder-maximizeButton->Width(), distFromTopBorder,
					 width-distFromRightBorder, distFromTopBorder+maximizeButton->Height());
	} else
		return BRect(-1, -1, -1, -1);
}

//: Returns width and postion of the title.
//!param: width - In this parameter the available space
//!param:         for the title is returned.
//!param: pos   - In this parameter the position for the
//!param:         title is returned.
void CMDITitleView::GetTitleWidthAndPos(float &width, BPoint &pos)
{
	BFont titleFont;
	GetTitleFont(&titleFont);	

	font_height titleFontHeight;
	
	titleFont.GetHeight(&titleFontHeight);

	width = Bounds().Width() - distFromMaximizeBox - distFromCloseBox;

	if(DisplayCloseButton()) {
		pos.x = CloseButtonRect().right + distFromCloseBox;

		width -= CloseButtonRect().right;
	} else {
		pos.x = distFromCloseBox;
	}

	if(DisplayMaximizeButton()) {
		width -= MaximizeButtonRect().Width() - distFromRightBorder;
	}
	
	pos.y = titleFontHeight.ascent + 3;
}

//: Returns the preferred size of this view.
// The width and height depend on the depend on the width and height of
// the title. The method ensures thate the title tab never gets broader than
// its target.
void CMDITitleView::GetPreferredSize(float *width, float *height)
{
	BFont titleFont;
	font_height fh;
	
	GetTitleFont(&titleFont);

	titleFont.GetHeight(&fh);

	*height = MAX(fh.ascent + fh.descent, CloseButtonRect().Height()) + distFromTopBorder + distFromBottomBorder;

	float totalWidth;
	
	totalWidth =  	titleFont.StringWidth(target->Title()) +
					distFromCloseBox +
					distFromMaximizeBox +
					distFromRightBorder +
					distFromLeftBorder +
					CloseButtonRect().Width() +
					MaximizeButtonRect().Width() +
					1;

	*width = MIN(totalWidth, target->Bounds().Width());
}

//: BeOS hook function
// Forwards the event to 'viewAction'.
void CMDITitleView::MouseDown(BPoint point)
{
	mouseAction->MouseDown(point);
}

//: BeOS hook function
// Forwards the event to 'viewAction'.
void CMDITitleView::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	mouseAction->MouseMoved(point, transit);
}

//: BeOS hook function
// Forwards the event to 'viewAction'.
void CMDITitleView::MouseUp(BPoint point)
{
	mouseAction->MouseUp(point);
}

//: Returns the font which is used to draw the title.
//!param: font  - Is filled with the title font.
void CMDITitleView::GetTitleFont(BFont *font)
{
	if(font) {
		*font = *be_bold_font;
	}
}

//: Background color of the title tab.
// The title tab of the active view is displayed in yellow,
// the title tab of all other views in light gray.
CColor CMDITitleView::BackgroundColor()
{
	return Active() ? CColor::BeTitleBarYellow : CColor::BeButtonGray;
}

//: Returns the area the mouse is over.
// Returns one of the following values:
// <TABLE>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NC_CLOSE_BOX</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       Mouse is over the close box.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NC_MAXIMIZE_BOX</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       Mouse is over the maximize box.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NC_TITLE_TAB</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       Mouse if over any other area of the title view.
//     </TD>
//   </TR>
// </TABLE>
int32 CMDITitleView::HitTest(BPoint point)
{
	if(CloseButtonRect().Contains(point))
		return MDI_NC_CLOSE_BOX;
	
	if(MaximizeButtonRect().Contains(point))
		return MDI_NC_MAXIMIZE_BOX;
	
	return MDI_NC_TITLE_TAB;
}

//: Called when the target is activated.
// Invalidates this view to change the background color.
void CMDITitleView::Activate(bool activate)
{
	active = activate;
	
	Invalidate();
}

//: Called if the title of the target changed.
// Resizes the view to fit the new title.
void CMDITitleView::TargetTitleChanged()
{
	float preferredWidth, preferredHeight;
	
	GetPreferredSize(&preferredWidth, &preferredHeight);

	CMDIClientView *client = dynamic_cast<CMDIClientView *>(Parent());
	client->ResizeViewTo(this, preferredWidth, preferredHeight);
}

//: Called if the target was resized.
// Resizes this if it's broader than the target.
void CMDITitleView::TargetResized(float width, float height)
{
	float preferredWidth, preferredHeight;
	
	GetPreferredSize(&preferredWidth, &preferredHeight);

	CMDIClientView *client = dynamic_cast<CMDIClientView *>(Parent());
	client->ResizeViewTo(this, preferredWidth, preferredHeight);
}

//: Called if the target is moved.
// The current implemenation is empty.
void CMDITitleView::TargetMoved(BPoint point)
{
	// The following code is useless. CMDIClientView::MoveViewTo
	// automatically moves TitleView AND target view.
	
#if 0
	// If someone calls Hide() on the target, the target gets a frame moved
	// event. It calls TargetMoved() of this view. But the passed coordinates
	// are meaningless. They are VERY BIG random numbers. Therefore I ignore
	// that message. This seems like YET ANOTHER BEOS BUG!
	
	if(!target->IsHidden()) {
		// There is a documentation bug in the BeBook.
		// The point passed in FrameMoved is in window, not in parent, coordinates!
		point -= Parent()->Bounds().LeftTop();
		
		Window()->ConvertToScreen(&point);
		Parent()->ConvertFromScreen(&point);

		CMDIClientView *client = dynamic_cast<CMDIClientView *>(Parent());
		client->MoveViewTo(this, point.x, point.y-Bounds().Height());
	}
#endif // 0
}
