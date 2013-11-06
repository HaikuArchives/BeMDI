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

// ==== globals ====

IDecorationFactory *global_DecorationFactory = NULL;

void SetDecorationFactory(IDecorationFactory *factory)
{
	delete global_DecorationFactory;
	global_DecorationFactory = factory;
}

IDecorationFactory *DecorationFactory()
{
	if(global_DecorationFactory == NULL)
		global_DecorationFactory = new CDefaultDecorationFactory;
		
	return global_DecorationFactory;
}

// ==== CMaximizeButton ====

//: Constructor
CMaximizeButton::CMaximizeButton(BView *v) : view(v)
{
	bgColor = CColor::BeTitleBarYellow;
	pressed = false;
}

//: Set pressed state.
// If the new state is identical to the current state this method does
// nothing. Otherwise the MaximizeButtonRect is invalidated.
void CMaximizeButton::SetPressed(bool p)
{
	if(pressed != p) {
		view->Invalidate(Bounds());
		pressed = p;
	}
}

//: Draw the maximize button.
void CMaximizeButton::Draw()
{
	BPoint oldOrigin = view->Origin();

	view->SetOrigin(Bounds().LeftTop());

	CColor background	= BackgroundColor();

	CColor light		= background + CColor(63, 63, 63);
	CColor shadow		= background - CColor(45, 45, 45);
	CColor middle		= background + CColor(33, 33, 33);
	CColor dark			= background - CColor(21, 21, 21);

	view->BeginLineArray(35);

	view->AddLine( BPoint(0,0),   BPoint(7,0),   shadow);
	view->AddLine( BPoint(0,0),   BPoint(0,7),   shadow);
	view->AddLine( BPoint(9,3),   BPoint(13,3),  shadow);
	view->AddLine( BPoint(3,9),   BPoint(3,13),  shadow);
	view->AddLine( BPoint(8,8),   BPoint(8,1),   light); 
	view->AddLine( BPoint(8,1),   BPoint(8,8),   light);
	view->AddLine( BPoint(1,8),   BPoint(8,8),   light);
	view->AddLine( BPoint(13,4),  BPoint(13,13), light);
	view->AddLine( BPoint(12,13), BPoint(4,13),  light);

	if(!Pressed()) {
		view->AddLine( BPoint(7,2),   BPoint(7,7),   shadow);
		view->AddLine( BPoint(2,7),   BPoint(6,7),   shadow);
		view->AddLine( BPoint(12,5),  BPoint(12,12), shadow);
		view->AddLine( BPoint(5,12),  BPoint(11,12), shadow);

		view->AddLine( BPoint(1,1),   BPoint(7,1),   light);
		view->AddLine( BPoint(1,1),   BPoint(1,7),   light);
		view->AddLine( BPoint(9,4),   BPoint(12,4),  light);
		view->AddLine( BPoint(4,9),   BPoint(4,12),  light);

		view->AddLine( BPoint(2,2),   BPoint(2,2),  light);
		
		view->AddLine( BPoint(2,3),   BPoint(3,2),  middle);
		view->AddLine( BPoint(2,4),   BPoint(4,2),  middle);
		view->AddLine( BPoint(3,5),   BPoint(5,3),  middle);

		view->AddLine( BPoint(5,9),   BPoint(5,11),  middle);
		view->AddLine( BPoint(6,9),   BPoint(6,10),  middle);
		view->AddLine( BPoint(7,9),   BPoint(7,9),  middle);
		view->AddLine( BPoint(9,5),   BPoint(11,5),  middle);
		view->AddLine( BPoint(9,6),   BPoint(10,6),  middle);
		view->AddLine( BPoint(9,7),   BPoint(9,7),  middle);
		view->AddLine( BPoint(8,10),   BPoint(10,8),  middle);

		view->AddLine( BPoint(4,6),   BPoint(6,6),  dark);
		view->AddLine( BPoint(6,4),   BPoint(6,6),  dark);
		view->AddLine( BPoint(6,11),  BPoint(11,11),  dark);
		view->AddLine( BPoint(11,6),   BPoint(11,11),  dark);
	} else {
		view->AddLine( BPoint(7,2),   BPoint(7,7),   light);
		view->AddLine( BPoint(2,7),   BPoint(6,7),   light);
		view->AddLine( BPoint(12,5),  BPoint(12,12), light);
		view->AddLine( BPoint(5,12),  BPoint(11,12), light);

		view->AddLine( BPoint(1,1),   BPoint(7,1),   shadow);
		view->AddLine( BPoint(1,1),   BPoint(1,7),   shadow);
		view->AddLine( BPoint(9,4),   BPoint(12,4),  shadow);
		view->AddLine( BPoint(4,9),   BPoint(4,12),  shadow);
		
		view->AddLine( BPoint(2,2),   BPoint(2,4),   dark);
		view->AddLine( BPoint(2,2),   BPoint(4,2),   dark);

		view->AddLine( BPoint(3,6),   BPoint(6,3),   middle);
		view->AddLine( BPoint(4,6),   BPoint(6,4),   middle);
		view->AddLine( BPoint(5,6),   BPoint(6,5),   middle);
		view->AddLine( BPoint(6,6),   BPoint(6,6),   middle);

		view->AddLine( BPoint(5,11),  BPoint(10,11),   middle);
		view->AddLine( BPoint(11,5),  BPoint(11,11),   middle);
		view->AddLine( BPoint(10,10),   BPoint(10,10),   middle);
		view->AddLine( BPoint(8,10),   BPoint(10,8),   middle);
		view->AddLine( BPoint(6,10),   BPoint(7,9),   middle);
		view->AddLine( BPoint(10,6),   BPoint(9,7),   middle);
	}

	view->EndLineArray();
	
	view->SetOrigin(oldOrigin);
}

// ==== CCloseButton ====

//: Constructor
CCloseButton::CCloseButton(BView *v) : view(v)
{
	bgColor = CColor::BeTitleBarYellow;
	pressed = false;
}

//: Set pressed state.
// If the new state is identical to the current state this method does
// nothing. Otherwise the Bounds rectangle is invalidated.
void CCloseButton::SetPressed(bool p)
{
	if(pressed != p) {
		view->Invalidate(Bounds());
		pressed = p;
	}
}

//: Draw the close button.
void CCloseButton::Draw()
{
	CColor	background	= BackgroundColor();

	CColor light		= background + CColor(63, 63, 63);
	CColor shadow		= background - CColor(72, 72, 72);
	CColor middle		= background + CColor(33, 33, 33);
	CColor dark			= background - CColor(21, 21, 21);

	BPoint oldOrigin = view->Origin();

	view->SetOrigin(Bounds().LeftTop());

	view->BeginLineArray(25);

	view->AddLine( BPoint(0,0),   BPoint(0,13),  shadow);
	view->AddLine( BPoint(0,0),   BPoint(13,0),  shadow);
	view->AddLine( BPoint(1,13),  BPoint(13,13), light);
	view->AddLine( BPoint(13,1),  BPoint(13,13), light);
		
	if(!Pressed()) {
		view->AddLine( BPoint(1,13),  BPoint(1,1),   light);
		view->AddLine( BPoint(1,1),   BPoint(12,1),  light);
		view->AddLine( BPoint(2,12),  BPoint(12,12), shadow);
		view->AddLine( BPoint(12,12), BPoint(12,2),  shadow);

		view->AddLine( BPoint(2,2),   BPoint(2,2),   light );
		view->AddLine( BPoint(2,3),   BPoint(3,2),   middle );
		view->AddLine( BPoint(2,4),   BPoint(4,2),   light );
		view->AddLine( BPoint(2,5),   BPoint(5,2),   middle );
		view->AddLine( BPoint(2,6),   BPoint(6,2),   middle );
		view->AddLine( BPoint(2,7),   BPoint(7,2),   middle );
		view->AddLine( BPoint(2,8),   BPoint(8,2),   middle );
		view->AddLine( BPoint(2,9),   BPoint(2,9),   middle );
		view->AddLine( BPoint(9,2),   BPoint(9,2),   middle );
		view->AddLine( BPoint(2,10),  BPoint(10,2),  middle );
		view->AddLine( BPoint(3,11),  BPoint(4,10),  middle );
		view->AddLine( BPoint(11,3),  BPoint(10,4),  middle );
		view->AddLine( BPoint(7,9),   BPoint(9,7),   dark );
		view->AddLine( BPoint(8,11),  BPoint(11,8),  dark );
		view->AddLine( BPoint(9,11),  BPoint(11,9),  dark );
		view->AddLine( BPoint(10,11), BPoint(11,10), dark );
		view->AddLine( BPoint(11,11), BPoint(11,11), dark );
	} else {
		view->AddLine( BPoint(1,13),  BPoint(1,1),   shadow);
		view->AddLine( BPoint(1,1),   BPoint(12,1),  shadow);
		view->AddLine( BPoint(2,12),  BPoint(12,12), light);
		view->AddLine( BPoint(12,12), BPoint(12,2),  light);

		view->AddLine( BPoint(11,11), BPoint(11,11), light );
		view->AddLine( BPoint(11,10), BPoint(10,11), middle );
		view->AddLine( BPoint(11,9),  BPoint(9,11),  light );
		view->AddLine( BPoint(11,8),  BPoint(8,11),  middle );
		view->AddLine( BPoint(11,7),  BPoint(7,11),  middle );
		view->AddLine( BPoint(11,6),  BPoint(6,11),  middle );
		view->AddLine( BPoint(11,5),  BPoint(5,11),  middle );
		view->AddLine( BPoint(11,4),  BPoint(11,4),  middle );
		view->AddLine( BPoint(4,11),  BPoint(4,11),  middle );
		view->AddLine( BPoint(11,3),  BPoint(3,11),  middle );
		view->AddLine( BPoint(10,2),  BPoint(9,3),   middle );
		view->AddLine( BPoint(2,10),  BPoint(3,9),   middle );
		view->AddLine( BPoint(6,4),   BPoint(4,6),   dark );
		view->AddLine( BPoint(5,2),   BPoint(2,5),   dark );
		view->AddLine( BPoint(4,2),   BPoint(2,4),   dark );
		view->AddLine( BPoint(3,2),   BPoint(2,3),   dark );
		view->AddLine( BPoint(2,2),   BPoint(2,2),   dark );
	}

	view->EndLineArray();
	
	view->SetOrigin(oldOrigin);
}
