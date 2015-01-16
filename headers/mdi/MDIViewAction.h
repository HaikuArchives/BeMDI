/***********************************************************************/
/* MDIViewAction.h                                                     */
/*                                                                     */
/* Mouse handling delegates for CMDIViews and CMDITitleViews.          */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef MDI_VIEW_ACTION_H
#define MDI_VIEW_ACTION_H

//! file=MDIViewAction.h

#include <mdi/ViewAction.h>
#include <mdi/MDICommon.h>

class CMDITitleView;
class CMDIClientView;
class CMDIView;

//: Mouse handler of CMDIView.
// <P>Like any IMouseAction object an object of this class is attached to
// a 'controled' view and handles its mouse messages. The controled view
// forwards its mouse messages to this object by calling MouseUp, MouseDown
// or MouseMoved.</P>
// <P>This class handles this cases:
// <UL>
// <LI>Move the view, if the user graps the border of the MDI view.
// <LI>Minimize the view, if the user double clicks the border.
// <LI>Size the view, if the user graps the size edge.
// </UL>
// </P>
class CMDIMouseAction : public CViewMouseAction
{
	public:
	CMDIMouseAction(BView *mdiView);
	
	virtual void MouseDown(BPoint point);
	virtual void MouseMoved(BPoint point, uint32 transit);
	virtual void MouseUp(BPoint point);

	virtual void MoveControledTo(float x, float y);
	virtual void ResizeControledTo(float width, float height);

	protected:
	virtual void HandleMouseDown(BPoint point, int32 hitTestArea, int32 buttons, int32 clicks);
	virtual void HandleMouseMove(BPoint point, BPoint screenPoint, float dx, float dy);
	virtual void HandleMouseUp(BPoint point);

	virtual CMDIView *MDIView();
	CMDIClientView *ClientView();
	
	//: Current operation.
	// Possible values:
	// <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="2">
	// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_MA_NONE</TD>
	// <TD CLASS="descr" BGCOLOR="#CCCCCC">No operation.</TD></TR>
	// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_MA_SIZE</TD>
	// <TD CLASS="descr" BGCOLOR="#CCCCCC">The user resizes the target view.</TD></TR>
	// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_MA_MOVE</TD>
	// <TD CLASS="descr" BGCOLOR="#CCCCCC">The user moves the target view.</TD></TR>
	// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_MA_CLOSE_BOX_PRESSED</TD>
	// <TD CLASS="descr" BGCOLOR="#CCCCCC">The user pressed the close box.</TD></TR>
	// <TR><TD CLASS="member" BGCOLOR="#CCCCCC">MDI_MA_MAXIMIZE_BOX_PRESSED</TD>
	// <TD CLASS="descr" BGCOLOR="#CCCCCC">The user pressed the maximize box.</TD></TR>
	// </TABLE>
	enumMouseAction mouseAction;

	//: Startpoint of the operation.
	// This point is in screen coordinates.
	BPoint startPoint;

	//: Double click rectangle.
	// The second click must be in this rect to be accepted as double click.
	// This rectangle is stored in screen coordinates.
	BRect				dblClickRect;
	
	//: Width of the double click rectangle.
	static const float  dblClickWidth;
	//: Height of the double click rectangle.
	static const float  dblClickHeight;
};

//: Mouse handler of CMDITitleView.
// <P>Like any IMouseAction object an object of this class is attached to
// a 'controled' view and handles its mouse messages. The controled view
// forwards its mouse messages to this object by calling MouseUp, MouseDown
// or MouseMoved.</P>
// <P>This class handles this cases:
// <UL>
// <LI>Close the view if the user pressed the close box.
// <LI>Maximize the view if the user pressed the maximize box.
// </UL>
// </P>
// <P>All other cases are handled by the base class.</P>
class CMDITitleMouseAction : public CMDIMouseAction
{
	public:
	CMDITitleMouseAction(BView *titleView);

	virtual void MouseUp(BPoint point);
	virtual void MoveControledTo(float x, float y);
	
	protected:
	virtual void HandleMouseDown(BPoint point, int32 hitTestArea, int32 buttons, int32 clicks);
	virtual void HandleMouseMove(BPoint point, BPoint screenPoint, float dx, float dy);
	
	CMDITitleView *TitleView();
	virtual CMDIView *MDIView();	
};

#endif // MDI_VIEW_ACTION_H
