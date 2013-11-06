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

// ====== globals ======

//: Compares two CColor objects. Returns true if 
//: every color component and the alpha channel are identical.
bool operator == (const CColor &o1, const CColor &o2)
{
	return (const rgb_color &)o1 == (const rgb_color &)o2;
}

//: Compares two rgb_colors structures. Returns true if 
//: every color component and the alpha channel are identical.
bool operator == (const rgb_color &o1, const rgb_color &o2)
{
	return o1.red   == o2.red   &&
		   o1.green == o2.green &&
		   o1.blue  == o2.blue  &&
		   o1.alpha == o2.alpha;
}

bool operator != (const CColor &o1, const CColor &o2)
{
	return !((const rgb_color &)o1 == (const rgb_color &)o2);
}

bool operator != (const rgb_color &o1, const rgb_color &o2)
{
	return !(o1 == o2);
}

// ====== CColor ======

//: Default constructor
// Sets the color to black.
CColor::CColor()
{
	red = green = blue = 0;
	alpha = 255;
}

//: Copy constructor
CColor::CColor(const CColor &other)
{
	(rgb_color &)(*this) = other;
}

//: Copy constructor
CColor::CColor(const rgb_color &other)
{
	(rgb_color &)(*this) = other;
}

//: Construct a CColor object from color and "tint level".
// <P>Fills a CColor object with a darker or lighter copy of 'other' depending
// on 'tint'.</P>
// <P>Possible values for 'tint':</P>
// <TABLE>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_LIGHTEN_MAX_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_LIGHTEN_2_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_LIGHTEN_1_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_NO_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_1_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_2_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_3_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_4_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_MAX_TINT</TD></TR>
// </TABLE>
CColor::CColor(const rgb_color &other, float tint)
{
	(rgb_color &)(*this) = tint_color(other, tint);

	// because tint_color sets alpha to 252 (bug??)
	alpha = 255;
}

//: Construct a CColor object from default UI color.
// <P>Fills a CColor object with a default UI color.
// Uses the BeOS functions ui_color and tint_color.</P>
// <P>Possible values for 'tint':</P>
// <TABLE>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_LIGHTEN_MAX_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_LIGHTEN_2_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_LIGHTEN_1_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_NO_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_1_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_2_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_3_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_4_TINT</TD></TR>
//   <TR><TD CLASS="descr" BGCOLOR="#DDDDDD">B_DARKEN_MAX_TINT</TD></TR>
// </TABLE>
CColor::CColor(color_which uiColor, float tint)
{
	(rgb_color &)(*this) = ui_color(uiColor);
	(rgb_color &)(*this) = tint_color(*this, tint);

	// because tint_color sets alpha to 252 (bug??)
	alpha = 255;
}

//: Constructs a color from color components and alpha channel.
CColor::CColor(uchar r, uchar g, uchar b, uchar a)
{
	red 	= r;
	green 	= g;
	blue	= b;
	alpha 	= a;
}

const CColor &CColor::operator = (const rgb_color &other)
{
	(rgb_color &)(*this) = other;
	return *this;
}

const CColor &CColor::operator = (const CColor &other)
{
	(rgb_color &)(*this) = (const rgb_color &)other;
	return *this;
}

CColor CColor::operator + (const CColor &other)
{
	CColor result = *this;
	return result += other;
}

CColor CColor::operator - (const CColor &other)
{
	CColor result = *this;
	return result -= other;
}

const CColor &CColor::operator += (const CColor &other)
{
	red   = MIN(red + other.red, 255);
	green = MIN(green + other.green, 255);
	blue  = MIN(blue + other.blue, 255);
	
	alpha = 255;
	
	return *this;
}

const CColor &CColor::operator -= (const CColor &other)
{
	red   = MAX(red - other.red, 0);
	green = MAX(green - other.green, 0);
	blue  = MAX(blue - other.blue, 0);

	alpha = 255;
	
	return *this;
}

//: Prints a color to stdout
// This function is normally only used for debugging purposes.
void CColor::PrintToStream() const
{
	printf("CColor(red: %d green: %d blue: %d alpha: %d)\n", 
			red, green, blue, alpha);
}

// ------ static color definitions ------

const CColor CColor::BeBackgroundGray(B_PANEL_BACKGROUND_COLOR);
const CColor CColor::BeInactiveControlGray(B_PANEL_BACKGROUND_COLOR, B_DISABLED_MARK_TINT);

// keyboard_navigation_color() isn't working if be_app isn't initialized.
const CColor CColor::BeFocusBlue(0, 0, 229);
const CColor CColor::BeHighlight(B_PANEL_BACKGROUND_COLOR, B_LIGHTEN_MAX_TINT);
const CColor CColor::BeShadow(B_PANEL_BACKGROUND_COLOR, B_DARKEN_2_TINT);
const CColor CColor::BeDarkShadow(B_PANEL_BACKGROUND_COLOR, 1.49);	// 216 --> 108
const CColor CColor::BeLightShadow(B_PANEL_BACKGROUND_COLOR, 1.1);	// 216 --> 194
const CColor CColor::BeButtonGray(B_PANEL_BACKGROUND_COLOR, B_LIGHTEN_1_TINT);
const CColor CColor::BeInactiveGray(B_PANEL_BACKGROUND_COLOR, B_DISABLED_MARK_TINT);
const CColor CColor::BeListSelectGray(178, 178, 178);
const CColor CColor::BeTitleBarYellow(B_WINDOW_TAB_COLOR);

// B_MENU_BACKGROUND_COLOR isn't working in BeOS 4.52
const CColor CColor::BeMenuBackgroundGray(B_PANEL_BACKGROUND_COLOR /*B_MENU_BACKGROUND_COLOR*/);
const CColor CColor::BeMenuSelectGray(B_PANEL_BACKGROUND_COLOR /*B_MENU_BACKGROUND_COLOR*/, B_DARKEN_2_TINT);

const CColor CColor::Transparent(B_TRANSPARENT_COLOR);

const CColor CColor::Red(255, 0, 0);
const CColor CColor::Green(0, 255, 0);
const CColor CColor::Blue(0, 0, 255);
const CColor CColor::White(255, 255, 255);
const CColor CColor::Black(0, 0, 0);
const CColor CColor::Yellow(255, 255, 0);
const CColor CColor::Cyan(0, 255, 255);
const CColor CColor::Magenta(255, 0, 255);
