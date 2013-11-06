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
#include "MDIViewAction.h"
#include "MDIView.h"
#include "MDIClientView.h"

// ==== CMDIView ====

const float CMDIView::sizeEdgeWidth	 = 17;
const float CMDIView::sizeEdgeHeight = 17;

const float CMDIView::defaultMinWidth   = 70;
const float CMDIView::defaultMinHeight  = 70;
const float CMDIView::defaultMaxWidth   = 2096;
const float CMDIView::defaultMaxHeight  = 2096;

//: Constructor
//!param: frame        - Position inside the parent view.
//!param: name         - Internal name and title of this MDI view.
//!param: _mdiFlags    - Flags. See remarks section for details.
//!param: resizingMode - BeOS resizing mode. Should be B_FOLLOW_NONE.
//!param: flags        - BeOS flag combination. B_WILL_DRAW, B_FULL_UPDATE_ON_RESIZE and B_FRAME_EVENTS are
//!param:                automatically added, before the flags are passed to the
//!param:                CTitledView constructor.
// The parameter '_mdiFlags' can be combination of following values:
// <TABLE>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NOT_MOVABLE</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       View isn't movable.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NOT_CLOSABLE</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       The title tab doesn't contain a close button. The user can't
//       close MDI views which have this flag set.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NOT_RESIZABLE</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       View isn't resizable. Set this flag if your MDI child view isn't
//       resizable. Should be combinated with the MDI_NOT_MAXIMIZABLE flag.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NO_TITLE_TAB</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       Don't create a title tab for this view. The user can't close a
//       a view without a title tab.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_REDRAW_BELOW</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//        Force redraw for views below, whenever this view is moved
//        or resized. Set this flag, if your view has a view color
//        other than TRANSPARENT. You should avoid this,
//        because it's a lot slower. (And flickers).
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NOT_MINIMIZABLE</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">View isn't minimizable.</TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NOT_MAXIMIZABLE</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       View isn't maximizable. You should set this flag if you have also
//       set MDI_NOT_RESIZABLE.
//     </TD>
//   </TR>
// </TABLE>
CMDIView::CMDIView(BRect frame, const char *name, uint32 _mdiFlags, uint32 resizingMode, uint32 flags) :
	CTitledView(frame, name, resizingMode, flags | B_FULL_UPDATE_ON_RESIZE | B_WILL_DRAW | B_FRAME_EVENTS)
{
	mdiFlags	= _mdiFlags;

	Init();	
}

//: Constructor
//!param: frame          - Position inside the parent view.
//!param: name           - Internal name and title of this MDI view.
//!param: client         - Client view. Is added as child view.
//!param: _mdiFlags      - Flags. See other constructor for details.
//!param: resizeToClient - If this parameter is set to true the MDI view is
//!param:                  is resized to be big enough to hold the client view.
CMDIView::CMDIView(BRect frame, const char *name, BView *client, uint32 _mdiFlags, bool resizeToClient) :
	CTitledView(frame, name, B_FOLLOW_NONE, B_FULL_UPDATE_ON_RESIZE | B_WILL_DRAW | B_FRAME_EVENTS)
{
	mdiFlags	= _mdiFlags;

	Init();	

	if(resizeToClient) {
		ResizeTo(client->Bounds().Width() + 10, client->Bounds().Height() + 10);
		client->MoveTo(ClientRect().LeftTop());
	}

	AddChild(client);
}

//: Common initializer
// Called by the constructors to do all common initialization.
void CMDIView::Init()
{
	active		= false;

	minWidth	= defaultMinWidth;
	maxWidth	= defaultMaxWidth;
	minHeight	= defaultMinHeight;
	maxHeight	= defaultMaxHeight;
	
	mouseAction = new CMDIMouseAction(this);
}

CMDIView::~CMDIView()
{
	delete mouseAction;
}

//: BeOS hook function
// Draws the border and the resize edge.
void CMDIView::Draw(BRect updateRect)
{
	Window()->BeginViewTransaction();

	float width  = Bounds().Width();
	float height = Bounds().Height();

	// The border changes its color, if the view is active!!
	CColor fillColor = Active() ? CColor::BeBackgroundGray : CColor::BeButtonGray;

	SetHighColor(CColor::BeShadow);
	MovePenTo(BPoint(0,0));
	StrokeLine(BPoint(0,height-1));
	StrokeLine(BPoint(width-1,height-1));
	StrokeLine(BPoint(width-1, 0));

	MovePenTo(3, height-3);
	StrokeLine(BPoint(3,3));
	StrokeLine(BPoint(width-4, 3));

	MovePenTo(4, height-4);
	StrokeLine(BPoint(4,4));
	StrokeLine(BPoint(width-4, 4));
	
	StrokeLine(BPoint(width-4, height-4));
	StrokeLine(BPoint(4, height-4));
	
	SetHighColor(CColor::BeDarkShadow);
	MovePenTo(0,height);
	StrokeLine(BPoint(width, height));
	StrokeLine(BPoint(width, 0));

	SetHighColor(CColor::BeHighlight);
	StrokeLine(BPoint(1,0), BPoint(1,height-2));
	StrokeLine(BPoint(4,height-3), BPoint(width-3, height-3));
	StrokeLine(BPoint(width-3, 3));

	SetHighColor(fillColor);
	StrokeLine(BPoint(2, 2), BPoint(2, height-2));
	StrokeLine(BPoint(width-2, height-2));
	StrokeLine(BPoint(width-2, 2));
	StrokeLine(BPoint(2,2));

	if(!(mdiFlags & MDI_NO_TITLE_TAB) && titleView) {
		// This view has a title tab
	
		float titleTabWidth = titleView->Bounds().Width();
		
		// Draw area below of title tab
		SetHighColor(fillColor);
		StrokeLine(BPoint(2, 0), BPoint(MIN(titleTabWidth-1, width-2), 0));
		StrokeLine(BPoint(2, 1), BPoint(MIN(titleTabWidth-1, width-2), 1));
		
		// The upper highlight area starts after the title tab		
		SetHighColor(CColor::BeHighlight);
		StrokeLine(BPoint(width-2, 1), BPoint(MIN(titleTabWidth, width-2), 1));
		
		// One pixel shadow between highlight and fill area.
		SetHighColor(CColor::BeDarkShadow);
		StrokeLine(BPoint(titleTabWidth, 0), BPoint(titleTabWidth, 0));
	
		// End top shadow at title tab
		SetHighColor(CColor::BeShadow);	
		StrokeLine(BPoint(width-1, 0), BPoint(titleTabWidth, 0));
	} else {
		// Draw upper highlight
		SetHighColor(CColor::BeHighlight);
		StrokeLine(BPoint(width-2, 1), BPoint(2, 1));
		
		// Draw top shadow
		SetHighColor(CColor::BeShadow);
		StrokeLine(BPoint(width-1, 0), BPoint(0, 0));
	}
	
	if(!(mdiFlags & MDI_NOT_RESIZABLE)) {
		// Draw size edge
		SetHighColor(CColor::BeShadow);
		StrokeLine(BPoint(width-sizeEdgeWidth, height-4), BPoint(width-sizeEdgeWidth, height-1));
		StrokeLine(BPoint(width-4, height-sizeEdgeHeight), BPoint(width-1, height-sizeEdgeHeight));
	}
	
	Window()->EndViewTransaction();
}

//: Sets the size limits.
// Constrains the user, not the programmer. It's legal for an application to
// set a MDI view size that falls outside the permitted range. 
// The limits are imposed only when the user attempts to resize the window; 
// at that time, the window will jump to a size that's within range. 
void CMDIView::SetSizeLimits(float _minWidth, float _maxWidth, float _minHeight, float _maxHeight)
{
	minWidth  = _minWidth;
	maxWidth  = _maxWidth;
	minHeight = _minHeight;
	maxHeight = _maxHeight;
}

//: Returns the size limits.
// See SetSizeLimits for details.
void CMDIView::GetSizeLimits(float *_minWidth, float *_maxWidth, float *_minHeight, float *_maxHeight) const
{
	if(_minWidth)	*_minWidth  = minWidth;
	if(_maxWidth)	*_maxWidth  = maxWidth;
	if(_minHeight)	*_minHeight = minHeight;
	if(_maxHeight)	*_maxHeight = maxHeight;
}

//: Returns the area the mouse is over.
// Returns one of the following values:
// <TABLE>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NC_SIZE_EDGE</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       Mouse is over the resize edge.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NC_BORDER</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       Mouse is over the border but not over the resize box.
//     </TD>
//   </TR>
//   <TR>
//     <TD CLASS="member" BGCOLOR="#DDDDDD">MDI_NC_NONE</TD>
//     <TD CLASS="descr" BGCOLOR="#DDDDDD">
//       Mouse is over the client area.
//     </TD>
//   </TR>
// </TABLE>
int32 CMDIView::HitTest(BPoint point)
{
	BRegion borderRegion = BorderRegion();
	
	if(borderRegion.Contains(point)) {
		if(!(mdiFlags & MDI_NOT_RESIZABLE)) {
			// View is resizable. Test for resize edge.
			// A view that's not resizable has no resize edge.
		
			// Size edge is also part of the border
			BRegion sizeEdgeRegion = SizeEdgeRegion(borderRegion);
		
			if(sizeEdgeRegion.Contains(point)) {
				return MDI_NC_SIZE_EDGE;
			}
		}
		
		return MDI_NC_BORDER;
	}
	
	return MDI_NC_NONE;
}

//: Returns the region occupied by the border.
// Updates 'borderRegion' and returns it.
BRegion CMDIView::BorderRegion()
{
	if(borderRegion.CountRects() == 0) {
		BRect bounds = Bounds();
	
		borderRegion.Include(bounds);
		borderRegion.Exclude(bounds.InsetBySelf(5, 5));
	}
	
	return borderRegion;
}

//: Returns the region occupied by the size edge.
// Updates 'sizeEdgeRegion' and returns it.
BRegion CMDIView::SizeEdgeRegion(BRegion &borderRegion)
{
	if(sizeEdgeRegion.CountRects() == 0) {
		float width  = Bounds().Width();
		float height = Bounds().Height();
	
		sizeEdgeRegion.Set(BRect(width-sizeEdgeWidth, height-sizeEdgeHeight, width, height));
		sizeEdgeRegion.IntersectWith(&borderRegion);
	}
	
	return sizeEdgeRegion;
}

//: BeOS hook function
// Forwards the event to 'mouseAction'.
void CMDIView::MouseDown(BPoint point)
{
	mouseAction->MouseDown(point);
}

//: BeOS hook function
// Forwards the event to 'mouseAction'.
void CMDIView::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	mouseAction->MouseMoved(point, transit);
}

//: BeOS hook function
// Forwards the event to 'mouseAction'.
void CMDIView::MouseUp(BPoint point)
{
	mouseAction->MouseUp(point);
}

//: Activates this view.
void CMDIView::Activate(bool activate)
{
	active = activate;
	
	Invalidate();
	
	CTitledView::Activate(active);
}

//: BeOS hook function
// Invalidates 'borderRegion' and 'sizeEdgeRegion'. They are
// recalculated the next time they are requested.
void CMDIView::FrameResized(float width, float height)
{
	CTitledView::FrameResized(width, height);

	// update cached screen rect
	screenRect = Bounds();
	ConvertToScreen(&screenRect);	
	
	// Recalc regions the next time they are requested.
	borderRegion.MakeEmpty();
	sizeEdgeRegion.MakeEmpty();
}

//: Returns the client area.
BRect CMDIView::ClientRect()
{
	return BRect(5, 5, Bounds().Width()-5, Bounds().Height()-5);
}
